
import os
import os.path
import struct
import sys

class Asset:
	def __init__(self, name, offset, size):
		self.name = name
		self.offs = offset
		self.size = size

def dumpAsset(asset, f):
	f.seek(asset.offs)
	with open(asset.name, 'wb') as out:
		out.write(f.read(asset.size))
		out.close()

assert len(sys.argv) == 2
filesize = os.path.getsize(sys.argv[1])
with open(sys.argv[1], 'rb') as f:
	assets = []
	totalsize = 0
	offset = struct.unpack('<H', f.read(2))[0]
	while f.tell() < offset:
		size = struct.unpack('<I', f.read(4))[0]
		name = b''
		while True:
			c = f.read(1)
			if ord(c) == 0:
				break
			name += c
		print('filename %s size %d' % (name.decode('ascii'), size))
		if size == 0:
			break
		assets.append(Asset(name, offset + totalsize, size))
		totalsize += size
	print('filesize:%d totalsize:%d offset:%d' % (filesize, totalsize, offset))
	assert offset + totalsize == filesize
	for asset in assets:
		dumpAsset(asset, f)
