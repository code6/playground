#coding=utf8

import os
import sys

reload(sys)
sys.setdefaultencoding('utf-8')

from BeautifulSoup import BeautifulSoup

if __name__ == "__main__":
    html = sys.stdin.read()
    soup = BeautifulSoup(html)
    date = soup.find('table', {'class':'gross_table'}).find('tr').find('h1').text
    print u"%s,今日票房(万元),累计票房(万元),今日排片(百分比),今日场次,上映天数" % (date)
    for tr in soup.find('table', {'class':'gross_table'}).findAll('tr'):
        line = []
        for td in tr.findAll('td'):
            line.append(td.text)
        table.append(line)
        if line:
            print ",".join(line)

