#!/usr/bin/python

import sys
import datetime

if (len(sys.argv) < 1):
	print "Info: Usage python downtime.py <timestamp-file-name>"
	exit(1)

ts_file = open(sys.argv[1], 'r')
max_down = 0
ts1 = ts_file.readline().strip()
#print ts1
downtime = 0
for line in ts_file.readlines():
	ts2 = line.strip()
	diff = int(ts2) - int(ts1)
	if diff > max_down:
		max_down = diff 
	ts1 = ts2
ts_file.close()
#print datetime.timedelta(milliseconds=downtime) 
print max_down/1000.0 # return downtime in seconds
