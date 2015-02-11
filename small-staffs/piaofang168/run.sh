#!/bin/bash
delta=$1
date=`date -v-"$delta"d +%Y-%m-%d`
curl --data "riqi=$date" http://www.piaofang168.com/index.php/Jinzhun | python piaofang168.py > $date.csv
