minfo = open('/proc/meminfo', 'r')
dirty = 0
for line in minfo.readlines():
	line = line.strip()
	if line.startswith('Dirty') or line.startswith('Writeback'):
		print line
		dirty += int(line.split()[1])
print dirty/4
minfo.close()
