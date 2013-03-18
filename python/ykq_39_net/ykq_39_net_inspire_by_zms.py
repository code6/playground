#coding=utf8

import os
import sys
import time
import subprocess
import simplejson as json
from threading import Thread, Lock
from Queue import Queue
from time import sleep
from BeautifulSoup import BeautifulSoup
from datautil import db
import logging

WGET_CMD = 'wget %s -q -O %s'
WGET_USING_PROXY_CMD = 'wget %s -q -O %s -e use-proxy=yes -e http-proxy=127.0.0.1:8087'
ICONF_CMD = 'iconv -f gbk -t utf8 %s > %s'
DB_URI = "mysql://code6:123456@127.0.0.1/playground?auto_commit=true&charset=UTF8"

def build_wget_cmd(url, filename, using_proxy=False):
    """ build weget cmd """
    if using_proxy:
        return WGET_USING_PROXY_CMD % (url, filename)
    return WGET_CMD % (url, filename)

fetch_fail_time = 0
def fetch_web_page_by_wget(url, dir = "downloads/", sleeptime = 5, retries = 5):
    """ fetch web page using wget """
    global fetch_fail_time
    filename = dir + url.replace('/', '_')
    if not os.path.exists(filename) or os.path.getsize(filename) < 10:
        while retries > 0:
            #time.sleep(sleeptime)
            retries -= 1
            using_proxy = (retries == 0 or fetch_fail_time > 10) or 1
            cmd = build_wget_cmd(url, filename, using_proxy)
            try:
                subprocess.check_call(cmd, shell=True)
            except subprocess.CalledProcessError:
                logging.warn("error fetch page:retries=%s, fetch_fail_time=%s, url= [%s]", retries, fetch_fail_time, url)
                fetch_fail_time += 1
                if retries:
                    sleeptime += 1
                    continue
                else:
                    raise
            fetch_fail_time = max(0, fetch_fail_time - 1)
            break
    return open(filename).read().decode("gbk", "ignore")

def execute(query, args=None,  rowfactory=dict):
    """ execute sql """
    conn = db.connect_uri(DB_URI)
    conn.rowfactory = rowfactory
    cursor = conn.cursor()
    cursor.execute(query, args)
    return cursor.fetchall()

def get_city_list(url="http://yqk.39.net"):
    """ run all city """
    soup = BeautifulSoup(fetch_web_page_by_wget(url))
    sql = '''
        insert into yqk_city(fetch_url, name, status) values (%s, %s, %s)
        on duplicate key update fetch_url = values(fetch_url)
    '''
    for a in soup.find('div', {'class':'city_list'}).findAll('a'):
        logging.info("get new city %s[%s]", a.text, a['href'])
        execute(sql, (a['href'], a.text, 0))

def get_company_contact_info(url):
    """ return company contact info """
    ret = {}
    soup = BeautifulSoup(fetch_web_page_by_wget(url))
    for l in soup.find('div', {'class':'yqk_about'}).findAll('li'):
        k, v = l.text.split(u'：')[0],  u'：'.join(l.text.split(u'：')[1:])
        ret[k] = v
    return ret

def get_company_basic_info(url):
    """ return company basic info """
    ret = {}
    soup = BeautifulSoup(fetch_web_page_by_wget(url))
    ret[u'基本信息'] = soup.find('div', {'class':'info_cn'}).text
    return ret

def get_company_brand_info(url):
    """ return company brand info """
    ret = {}
    soup = BeautifulSoup(fetch_web_page_by_wget(url))
    ret['brandlist'] = ",".join(l.text for l in soup.find('div', {'class':'brand_pro'}).findAll('li'))
    return ret

def _fetch_one_company(url):
    """
        url: http://yqk.39.net/th/yaochang/6a51f.html
        联系方式: http://yqk.39.net/th/yaochang/contact/6a51f.html
        基本信息: http://yqk.39.net/th/yaochang/introduce/6a51f.html
        品牌产品: http://yqk.39.net/yaochang/brand/435487_0_1.shtml

        output:
        传真电话  =>   010-67860810
        品牌名称  =>  所有品牌,北大药业
        药企名称  =>   北京斯利安药业有限公司
        电子信箱  =>
        brand_url  =>  http://yqk.39.net/yaochang/brand/433124_0_1.shtml
        邮政编码  =>   100176
        联 系 人  =>
        联系电话  =>   010-67868885
        药企地址  =>   北京经济技术开发区运城街3号
        基本信息  =>  北京斯利安药业有限公司(原北京北大药业有限公司)
    """
    ret = {'fetch_url':url}
    soup = BeautifulSoup(fetch_web_page_by_wget(url))
    contact_url = url.replace('yaochang', 'yaochang/contact')
    introduce_url = url.replace('yaochang', 'yaochang/introduce')
    brand_url = "http://yqk.39.net%s" % soup.find('a', {'title':u'品牌及产品'})['href']
    ret['brand_url'] = brand_url
    ret.update(get_company_basic_info(introduce_url))
    ret.update(get_company_contact_info(contact_url))
    ret.update(get_company_brand_info(brand_url))
    output(ret)
    return ret

def output(d):
    """ output dict """
    print "output dict "
    for k, v in d.iteritems():
        print k, ' => ', v

def get_pattern(url):
    """ get pattern and limit from url 
        input: "http://yqk.39.net/DrugCompanyList/all_0_0_2_100.shtml"
        output: (http://yqk.39.net/DrugCompanyList/all_0_0_2_%s.shtml,  100)
    """
    arr = url.split('_')
    pat = "_".join(arr[:-1] + ["%s.shtml"])
    limit = int(arr[-1].split('.')[0])
    return pat, limit

def get_one_city_drugcompany_page(cityid, url):
    """ get all company page at one city """
    print "fetch cityid = ", cityid
    index_page = fetch_web_page_by_wget(url)
    soup = BeautifulSoup(index_page)

    sql = '''
        insert into yqk_city_drugcompany_page(fetch_url, cityid, status) values (%s, %s, %s)
        on duplicate key update cityid = values(cityid)
    '''

    start_page = url
    try:
        end_page = soup.find('a', {'class':'other1'})['href']
    except:
        end_page = start_page
    pat, limit = get_pattern(end_page)
    for i in xrange(1, limit + 1):
        cur_url = pat % i
        cur_page = fetch_web_page_by_wget(cur_url)
        execute(sql, (cur_url, cityid, 0))

def get_city_drupcompany_page():
    sql = '''
    select id cityid, fetch_url
    from yqk_city
    '''
    ret = execute(sql)
    for l in ret:
        get_one_city_drugcompany_page(l['cityid'], l['fetch_url'])

def get_drugcompany_detail():
    sql = '''
        select identity, name, fetch_url 
        from yqk_drugcompany
        where status = 0
    '''
    ret = execute(sql)

    sql = '''
    update yqk_drugcompany
    set 
        faxphone = %s, 
        brandlist = %s,
        name = %s,
        email = %s,
        brand_url = %s,
        postcode = %s,
        contact = %s,
        phone = %s,
        address = %s,
        basicinfo = %s,
        status = %s
    where identity = %s
    '''

    for l in ret:
        name = l['name']
        identity = l['identity']
        url = l['fetch_url']
        try:
           d =  _fetch_one_company(url)
           info = (
                      d[ u'传真电话'],
                      d[ u'brandlist'],
                      d[ u'药企名称'],
                      d[ u'电子信箱'],
                      d[ u'brand_url'],
                      d[ u'邮政编码'],
                      d[ u'联 系 人'],
                      d[ u'联系电话'],
                      d[ u'药企地址'],
                      d[ u'基本信息'],
                      2, identity)
           execute(sql, info)
           logging.info("fetch  %s success, url=[%s]", name, url)
        except Exception, ex:
            logging.warn("fetch  %s fail, url=[%s], err=[%s]", name, url, str(ex))
            execute("update yqk_drugcompany set status = 1 where identity = %s", (identity))

def get_drugcompany():
    sql = '''
        select fetch_url, cityid
        from yqk_city_drugcompany_page
        where status = 0
    '''
    ret = execute(sql)
    sql = '''
        insert into yqk_drugcompany(fetch_url, identity, name, cityid, basicinfo, brandlist, status) values (%s, %s, %s, %s,%s, %s, %s)
        on duplicate key update fetch_url = values(fetch_url), name = values(name)
    '''
    for l in ret:
        url = l['fetch_url']
        cityid = l['cityid']
        logging.info("get company_page url=[%s]", url)
        index_page = fetch_web_page_by_wget(url)
        soup = BeautifulSoup(index_page)
        if soup:
            for b in soup.find('div', {'class':'quote_list'}).findAll('b'):
                a = b.find('a')
                identity = a['href'].split('/')[-1].split('.')[0]
                execute(sql, (a['href'], identity, a.text, cityid, '', '', 0))
        execute("update yqk_city_drugcompany_page set status = 1 where fetch_url=%s", (url))

def get_drug_page():
    sql = '''
    select id drugcompany_id, brand_url fetch_url
    from yqk_drugcompany
    where status = 2
    '''
    ret = execute(sql)

    insert_sql = '''
        insert into yqk_drug_page(fetch_url, drugcompany_id, status) values (%s, %s, %s)
        on duplicate key update drugcompany_id = values(drugcompany_id)
    '''

    update_sql = '''
    update yqk_drugcompany set status = 3 where id = %s
    '''

    for l in ret:
        url = l['fetch_url']
        drugcompany_id = l['drugcompany_id']
        start_page = url
        index_page = fetch_web_page_by_wget(start_page)
        soup = BeautifulSoup(index_page)
        try:
            end_page = soup.find('a', {'class':'other1'})['href']
        except:
            end_page = start_page
        pat, limit = get_pattern(end_page)
        for i in xrange(1, limit + 1):
            cur_url = pat % i
            cur_page = fetch_web_page_by_wget(cur_url)
            execute(insert_sql, (cur_url, drugcompany_id, 0))
            logging.info("fetch drug page success [%s]", cur_url)
        execute(update_sql, (drugcompany_id))

def get_drug():
    sql = '''
        select fetch_url, drugcompany_id
        from yqk_drug_page
        where status = 0
    '''
    ret = execute(sql)
    sql = '''
        insert into yqk_drug(fetch_url, drugcompany_id, identity, name, company, specification, `usage`, indication, status) values (%s, %s, %s, %s, %s, %s, %s, %s, %s)
        on duplicate key update fetch_url = values(fetch_url), name = values(name)
    '''
    for l in ret:
        url = l['fetch_url']
        logging.info("fetch drug page url=[%s]", url)
        drugcompany_id = l['drugcompany_id']
        logging.info("get drug page url=[%s]", url)
        index_page = fetch_web_page_by_wget(url)
        soup = BeautifulSoup(index_page)
        if soup:
            soup = soup.findAll('div', {'class':'yqk_cn'})[1]
            for d in soup.findAll('div', {'class':'quote'}):
                a = d.find('li').find('a')
                name = a.text
                fetch_url = a['href']
                identity = fetch_url.split('/')[-1].split('.')[0]
                a = d.findAll('li')[1].find('a')
                company = a.text
                specification, usage, indication  = (u'：'.join(l.text.split(u'：')[1:]) for l in d.findAll('li')[2:])
                execute(sql, (
                                fetch_url, 
                                drugcompany_id,
                                identity,
                                name,
                                company,
                                specification,
                                usage,
                                indication,
                                0
                            )
                        )
        execute("update yqk_drug_page set status = 1 where fetch_url=%s", (url))

def init():
    logConfig = {
       'filename' : 'ykq.log',
       'filemode' : 'a',
       'format' : '%(asctime)s %(levelname)s %(message)s',
       'level' : logging.INFO
    }
    logging.basicConfig(**logConfig)

if __name__ == "__main__":
    init()
    #print fetch_web_page_by_wget("http://ypk.39.net/manual/863578/0/")
    #get_city_list()
    #get_city_drupcompany_page()
    #get_drugcompany_detail()
    #get_drug_page()
    get_drug()
    #get_drugcompany()
    #url = sys.argv[1]
    #name = sys.argv[2]
    #save_filename = "company_list_%s.dat" % name
    #get_all_company_at_one_city(url, name)
