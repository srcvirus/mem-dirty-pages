#!/usr/bin/python

import sys
import datetime

if (len(sys.argv) != 2):
	print "Info: Usage python downtime.py <timestamp-file-name>"
	exit(1)

ts_file = open(sys.argv[1], 'r')

ts1 = ts_file.readline().strip()
#print ts1
downtime = 0
for line in ts_file.readlines():
	ts2 = line.strip()
	diff = int(ts2) - int(ts1)
	if diff > 500:
		downtime += diff 
	ts1 = ts2
ts_file.close()
print datetime.timedelta(milliseconds=downtime) 
