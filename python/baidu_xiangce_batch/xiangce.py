#coding=utf8
"""
Refer: https://gist.github.com/mikemedina/584df2d90922f66640a9
"""

import os
import sys
import time

from selenium import webdriver
from selenium.common.exceptions import NoSuchElementException
from selenium.webdriver.support.ui import WebDriverWait

def get_element_by_xpath(brower, xpath):
    wait = WebDriverWait(brower, 60)
    wait.until(lambda d : d.find_element_by_xpath(xpath).is_displayed())
    return brower.find_element_by_xpath(xpath)

def wait_for_download(download_dir):
    ## Wait for the download to begin
    while not any(name.endswith('.part') for name in os.listdir(download_dir)):
        time.sleep(0.1)
    # Wait for the download to complete
    while any(name.endswith('.part') for name in os.listdir(download_dir)):
        time.sleep(0.1)

def download_xiangce(brower):
    import config
    # goto download_page
    brower.get("http://xiangce.baidu.com/")

    # login
    get_element_by_xpath(brower, '//*[@id="userbar-login-btn"]').click()
    get_element_by_xpath(brower, '//*[@name="userName"]').send_keys(config.user)
    get_element_by_xpath(brower, '//*[@name="password"]').send_keys(config.passwd)
    get_element_by_xpath(brower, '//*[@id="TANGRAM__PSP_8__submit"]').click()

    # wait for CAPTCHA
    print "wait for inputing captha manully"
    time.sleep(3)

    # goto 我的相册
    # get_element_by_xpath(brower, '//a[contains(text(), "我的相册")]').click()
    # get_element_by_xpath(brower, '//a[contains(text(), "我知道了")]').click()
    print "goto my album"
    time.sleep(10)

    # open album by name.
    print "open album by name = %s"  % (config.album_name)
    get_element_by_xpath(brower, '//a[@title="%s"]' % config.album_name).click()
    get_element_by_xpath(brower, '//a[text()="批量下载"]').click()

    print "start download album..."
    while True:
        # download this page
        time.sleep(30)
        get_element_by_xpath(brower, '//a[@class="pager_current"]')
        print "click 本页全选"
        get_element_by_xpath(brower, '//input[@id="select-current"]').click()
        print "click 开始下载"
        #TODO: retry for download
        get_element_by_xpath(brower, '//div[contains(@class, "download-button download-button-upState")]').click()
        print "wait for download"
        wait_for_download(config.download_dir)
        get_element_by_xpath(brower, '//input[@id="select-current"]').click()
        time.sleep(30)
        # try to find next page
        try: 
            print "Finish download page %s" % (get_element_by_xpath(brower, '//a[@class="pager_current"]').text)
            brower.find_element_by_xpath('//a[@class="pager_next" and @style="display: inline-block;"]').click()
        except NoSuchElementException:
            print "No find next page, exit..."
            break

    print " finish download album %s" % (config.album_name)

def main():
    #brower = webdriver.Chrome()
    #brower = webdriver.Firefox()
    import config
    fp = webdriver.FirefoxProfile()
    fp.set_preference('browser.download.folderList', 2)
    fp.set_preference("browser.download.manager.showWhenStarting", False)
    fp.set_preference("browser.helperApps.alwaysAsk.force", False)
    fp.set_preference("browser.helperApps.neverAsk.saveToDisk", "application/octet-stream")
    fp.set_preference("browser.download.dir",config.download_dir)
    brower = webdriver.Firefox(firefox_profile=fp)
    try:
        download_xiangce(brower) 
    finally:
        brower.quit()

if __name__ == "__main__":
    main()
