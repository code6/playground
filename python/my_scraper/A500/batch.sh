#!/bin/bash
for i in `seq 401 1000`; do  ./scrape.sh  `date -v-"$i"d +%Y-%m-%d` ; sleep 5; done
