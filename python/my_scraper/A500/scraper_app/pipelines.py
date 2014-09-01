#! -*- coding: utf-8 -*-

"""
Web Scraper Project

Scrape data from a regularly updated website 500.com and
save to a database (postgres).

Scrapy pipeline part - stores scraped items in the database.
"""

from sqlalchemy.orm import sessionmaker
from models import db_connect, create_table, Match as MatchModel, AsiaOdds as AsiaOddsModel
from items import Match, AsiaOdds

class A500Pipeline(object):
    """A500 pipeline for storing scraped items in the database"""
    def __init__(self):
        """Initializes database connection and sessionmaker.

        Creates deals table.

        """
        engine = db_connect()
        create_table(engine)
        self.Session = sessionmaker(bind=engine)

    def save(self, item, cls):
        session = self.Session()
        item =  { k:item[k] for k in cls.__dict__.keys() if k in item }
        obj = cls(**item)

        try:
            session.merge(obj)
            session.commit()
        except:
            session.rollback()
            raise
        finally:
            session.close()

    def process_item(self, item, spider):
        """Save deals in the database.

        This method is called for every item pipeline component.

        """
        if isinstance(item, Match):
           self.save(item, MatchModel)
        elif isinstance(item, AsiaOdds):
           self.save(item, AsiaOddsModel)

        return item
