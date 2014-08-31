#! -*- coding: utf-8 -*-

"""
Web Scraper Project

Scrapy spider part - it actually performs scraping.
"""

import json
import time
import scrapy
from scrapy.spider import BaseSpider
from scrapy.selector import Selector
from scrapy.contrib.loader import ItemLoader
from scrapy.contrib.loader.processor import Join, MapCompose
from scraper_app.items import Match, AsiaOdds


class A500(BaseSpider):
    """Spider for regularly updated 500 site"""
    name = "A500"
    allowed_domains = ["500.com"]
    game_date = ""
    UP_CHAR =  u'\u2191'
    DOWN_CHAR = u'\u2193'

    match_list_xpath = ".//table[@class='zs_tablelist']//tr[@data-mid]"

    match_fields = {
        "season_id" : ".//a[contains(@href, 'seasonid')]/@href",
        "season_name" : ".//a[contains(@href, 'seasonid')]/text()", 
        "match_id" : "./@data-fid",
        "match_time" : "./@date-dtime",
        "teama_id" : "(.//a[contains(@class, 'team_link')])[1]/@href",
        "teama" : "(.//a[contains(@class, 'team_link')])[1]/text()",
        "teamb_id" : "(.//a[contains(@class, 'team_link')])[2]/@href",
        "teamb" : "(.//a[contains(@class, 'team_link')])[2]/text()",
        "score" : ".//span//text()",
    }

    asia_odds__xpath = ".//tr[contains(@class, 'tr')]"
    asia_odds_url = "http://odds.500.com/fenxi1/yazhi.php?id=%s&ctype=1&start=%s&r=1&style=0&guojia=0"
    asia_odds_inc_url = "http://odds.500.com/fenxi1/inc/yazhiajax.php?fid=%s&id=%s&t=%s&r=1"
    asia_odds_fields = {
        "company_id" : "(.//a[contains(@href, 'cid')])[1]/@href",
        "company" : ".//span[contains(@class, 'quancheng')]/text()",
        "water_a" : "(.//table[contains(@class, 'pl_table_data')])[1]//td[1]/text()",
        "handicap" : "(.//table[contains(@class, 'pl_table_data')])[1]//td[2]/text()",
        "handicap_val" : "(.//table[contains(@class, 'pl_table_data')])[1]//td[2]/@ref",
        "water_b" : "(.//table[contains(@class, 'pl_table_data')])[1]//td[3]/text()",
        "update_time": ".//td[contains(@row, 1)][5]/text()",
    }

    def __init__(self, date=None, *args, **kwargs):
        super(A500, self).__init__(*args, **kwargs)
        self.game_date = date
        self.start_urls = [ "http://odds.500.com/index_jczq_%s.shtml" % date ]

    def parse(self, response):
        """
        Default callback used by Scrapy to process downloaded responses

        Testing contracts:
        @url http://odds.500.com/index_jczq_2014-08-29.shtml

        """
        selector = Selector(response)

        # iterate over matchs 
        for match in selector.select(self.match_list_xpath):
            loader = ItemLoader(Match(), selector=match)

            # define processors
            loader.default_input_processor = MapCompose(unicode.strip)
            loader.default_output_processor = Join()

            # iterate over fields and add xpaths to the loader
            for field, xpath in self.match_fields.iteritems():
                loader.add_xpath(field, xpath)

            match_item = loader.load_item()
            match_item["game_date"] = self.game_date
            match_item["season_id"] = match_item["season_id"].split('-')[-1]
            match_item["teama_id"] = match_item["teama_id"].split('-')[-1]
            match_item["teamb_id"] = match_item["teamb_id"].split('-')[-1]
            if "score" in match_item:
                sa, sb = match_item["score"].split(':')
                match_item["score_a"] = sa
                match_item["score_b"] = sb
                match_item["result"] = "win" if sa > sb else "draw" if sa == sb else "lost"
            else:
                match_item["score_a"] = match_item["score_b"] = -1
                match_item["result"] = "none"

            yield match_item

            #scrap asia odds
            #id=454359&ctype=1&start=60&r=1&style=0&guojia=0
            for i in xrange(3):
                url = self.asia_odds_url % (match_item["match_id"], i * 30)
                request = scrapy.Request(url, callback=self.parse_asia_odds)
                request.meta['match_item'] = match_item
                yield request

    def parse_asia_odds(self, response):
        match_item = response.meta['match_item']
        selector = Selector(response)
        # iterate over odds 
        for odds in selector.select(self.asia_odds__xpath):
            loader = ItemLoader(AsiaOdds(), selector=odds)

            # define processors
            loader.default_input_processor = MapCompose(unicode.strip)
            loader.default_output_processor = Join()

            # iterate over fields and add xpaths to the loader
            for field, xpath in self.asia_odds_fields.iteritems():
                loader.add_xpath(field, xpath)

            odds_item = loader.load_item()
            #http://odds.500.com/yazhi.php?cid=515
            odds_item["match_id"] = match_item["match_id"]
            odds_item["company_id"] = odds_item["company_id"].split('=')[-1]
            odds_item["water_a"] = odds_item["water_a"].replace(self.UP_CHAR, '').replace(self.DOWN_CHAR, '')
            odds_item["water_b"] = odds_item["water_b"].replace(self.UP_CHAR, '').replace(self.DOWN_CHAR, '')

            odds_item["handicap_his"] = []

            url = self.asia_odds_inc_url % (odds_item["match_id"], odds_item["company_id"], int(time.time() * 1000))
            request = scrapy.Request(url, headers={"X-Requested-With":"XMLHttpRequest"}, callback=self.parse_asia_odds_history)
            request.meta['odds_item'] = odds_item
            yield request
            #r = requests.get(url, headers={"X-Requested-With":"XMLHttpRequest"})
            #r.raise_for_status()

        def parse_asia_odds_history(self, response):
            odds_item = response.meta['odds_item']
            his_selector = Selector(response)
            tr_arr = his_selector.xpath(".//tr")
            tr_arr.reverse()
            for idx, tr in enumerate(tr_arr):
                print [v[:v.index("\\n\\t")] for v in tr.xpath(".//td/text()").extract()]
                d = dict(zip(["water_a", "handicap", "water_b", "update_time"], [v[:v.index("\\n\\t")] for v in tr.xpath(".//td/text()").extract()]))
                d["idx"] = idx
                odds_item["handicap_his"].append(d)

            odds_item["handicap_his"] = json.dumps(odds_item["handicap_his"])

            yield odds_item
