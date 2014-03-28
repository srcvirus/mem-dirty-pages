import socket
import time

host = '' # listen on all interfaces
port = 9999

try:
	s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except socket.error, msg:
	print 'Failed to create socket. Error code: ', str(msg[0]), ' Message: ', msg[1]

try:
	s.bind((host, port)) 
except socket.error, msg:
	print 'Failed to bind socket. Error code: ', str(msg[0]), ' Message: ', msg[1]

last_timestamp = int(round(time.time() * 1000))
max_diff = 0
while 1:
	data, addr = s.recvfrom(1024)
	current_timestamp = int(round(time.time() * 1000))
	diff = current_timestamp - last_timestamp
	last_timestamp = current_timestamp

	if diff > max_diff:
		max_diff = diff

	print 'Max Diff: ', str(max_diff), ' ms'
