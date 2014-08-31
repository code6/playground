#! -*- coding: utf-8 -*-

"""
Web Scraper Project

Scrape data from a regularly updated website livingsocial.com and
save to a database (postgres).

Database models part - defines table for storing scraped data.
Direct run will create the table.
"""

from sqlalchemy import create_engine, Column, Integer, String, Float, Text, DateTime, Date
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.engine.url import URL

import settings


DeclarativeBase = declarative_base()

def db_connect():
    """Performs database connection using database settings from settings.py.

    Returns sqlalchemy engine instance.

    """
    return create_engine(URL(**settings.DATABASE))

def create_table(engine):
    """"""
    DeclarativeBase.metadata.create_all(engine)

class Match(DeclarativeBase):
    """Sqlalchemy match model"""
    __tablename__ = "matchs"

    game_date = Column("game_date", Date, index=True)
    season_id = Column("season_id", Integer)
    season_name = Column("season_name", String(50))
    match_id = Column("match_id", Integer, primary_key=True)
    match_time = Column("match_time", DateTime)
    teama_id = Column("teama_id", Integer)
    teama = Column("teama", String(50))
    teamb_id = Column("teamb_id", Integer)
    teamb = Column("teamb", String(50))
    score_a = Column("score_a", Integer)
    score_b = Column("score_b", Integer)
    result = Column("result", String(50))


class AsiaOdds(DeclarativeBase):
    """Sqlalchemy  asia odds  model"""
    __tablename__ = "asia_odds"

    match_id = Column("match_id", Integer, primary_key=True)
    company_id = Column("company_id", Integer, primary_key=True)
    company = Column("company", String(50))
    water_a = Column("water_a", Float)
    handicap = Column("handicap", String(50))
    handicap_val = Column("handicap_val", Float)
    water_b = Column("water_b", Float)
    update_time = Column("update_time", String(50))
    handicap_his = Column("handicap_his", Text)
