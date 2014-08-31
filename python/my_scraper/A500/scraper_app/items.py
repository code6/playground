#! -*- coding: utf-8 -*-

"""
Web Scraper Project

Scrape data from a regularly updated website livingsocial.com and
save to a database (postgres).

Scrapy item part - defines container for scraped data.
"""

from scrapy.item import Item, Field

class Match(Item):
    """ match """
    game_date = Field()
    season_id = Field()
    season_name = Field()
    match_id = Field()
    match_time = Field()
    teama_id = Field()
    teama = Field()
    teamb_id = Field()
    teamb = Field()
    score = Field()
    score_a = Field()
    score_b = Field()
    result = Field()

class AsiaOdds(Item):
    """ Asia match odd handicap data """
    match_id = Field()
    company_id = Field()
    company = Field()
    water_a  = Field()
    handicap = Field()
    handicap_val = Field()
    water_b  = Field()
    update_time = Field()
    handicap_his = Field()
