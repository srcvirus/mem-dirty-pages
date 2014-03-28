import socket
from time import sleep

host = 'cn107' 
port = 9999

try:
        s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except socket.error, msg:
        print 'Failed to create socket. Error code: ', str(msg[0]), ' Message: ', msg[1]

s.sendto('clear', (host, port))
reply, addr = s.recvfrom(1024)
print reply
