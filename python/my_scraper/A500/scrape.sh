#!/bin/bash
# be sure to change both virtualenv directory and scrape/living_social
# directory to where your venv and code is.
date=$1
cd ~/git/playground/python/my_scraper/A500/scraper_app
scrapy crawl A500 -a date="$date"
