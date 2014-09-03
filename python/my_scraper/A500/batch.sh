#!/bin/bash
for i in `seq 301 400`; do  ./scrape.sh  `date -v-"$i"d +%Y-%m-%d` ; sleep 5; done
