# Scrapy settings for tutorial project
#
# For simplicity, this file contains only the most important settings by
# default. All the other settings are documented here:
#
#     http://doc.scrapy.org/topics/settings.html
#


BOT_NAME = 'A500'

#COOKIES_ENABLED = False 

SPIDER_MODULES = ['scraper_app.spiders']

ITEM_PIPELINES = {
        'scraper_app.pipelines.A500Pipeline' : 500
        }

DOWNLOADER_MIDDLEWARES = {  
        'scrapy.contrib.downloadermiddleware.useragent.UserAgentMiddleware' : None,  
        'scraper_app.rotate_ua.RotateUserAgentMiddleware' :400  
    }  

DATABASE = {'drivername': 'mysql',
            'host': '',
            'port': '',
            'username': '', # fill in your username here
            'password': '', # fill in your password here
            'database': 'scrape'}
