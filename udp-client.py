import socket
from time import sleep

host = 'cn107' 
port = 9999

try:
        s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except socket.error, msg:
        print 'Failed to create socket. Error code: ', str(msg[0]), ' Message: ', msg[1]

while 1:
        s.sendto('heartbeat', (host, port))
	sleep(0.5) # time is in seconds
