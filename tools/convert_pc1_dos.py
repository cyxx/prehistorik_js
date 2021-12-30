
import os.path
import struct
import sys

class bitstream:
	def __init__(self, f):
		self.mask = 0
		self.byte = 0
	def next_bit(self):
		if self.mask == 0:
			self.mask = 0x80
			self.byte = ord(f.read(1))
		ret = self.byte & self.mask
		self.mask >>= 1
		return ret
	def next_byte(self):
		ret = 0
		for i in range(8):
			ret <<= 1
			if self.next_bit() != 0:
				ret |= 1
		return ret

class buf:
	def __init__(self, size):
		self.data = [ chr(0) ] * size
		self.offset = 0
	def outbyte(self, byte):
		self.data[self.offset] = chr(byte)
		self.offset += 1
	def copyref(self, offset, count):
		for i in range(count):
			self.data[self.offset] = self.data[self.offset - offset]
			self.offset += 1

def decompress_lzss(totalsize, f):
	out = buf(totalsize)
	bs = bitstream(f)
	while totalsize > 0:
		if bs.next_bit() == 0:
			totalsize -= 1
			out.outbyte(bs.next_byte())
		else:
			count = 2
			if bs.next_bit() != 0:
				count += 2
			if bs.next_bit() != 0:
				count += 1
			offset = bs.next_byte() + 1
			out.copyref(offset, count)
			totalsize -= count
	return out

assert len(sys.argv) == 3
with open(sys.argv[1], 'rb') as f:
	totalsize = struct.unpack('>I', f.read(4))[0]
	out = decompress_lzss(totalsize, f)
	with open(sys.argv[2], 'wb') as f:
		for b in out.data:
			f.write(b)
