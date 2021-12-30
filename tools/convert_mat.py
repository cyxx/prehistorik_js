
from PIL import Image
import ctypes
import os.path
import struct
import sys

def decode_bitplanes(w, h, depth, data, start_offset = 0):
	plane_size = ((w * depth) / 8) / depth
	picture = [ 0 ] * (w * h)
	rd_offset = start_offset
	wr_offset = 0
	for y in range(h):
		for x in range(plane_size):
			for bit in range(8):
				color = 0
				mask = 1 << (7 - bit)
				for plane in range(depth):
					if (data[plane * (len(data) / depth) + rd_offset] & mask) != 0:
						color |= 1 << plane
				picture[wr_offset] = color & 15
				wr_offset += 1
			rd_offset += 1
	assert wr_offset == len(picture)
	return picture

class gfx:
	def __init__(self, w, h, data):
		self.w = w
		self.h = h
		self.data = data
	def decode(self, depth):
		size = ((self.w * depth) / 8) * self.h
		planes = [ 0 ] * size
		rd = 0
		wr = 0
		while wr < size:
			code = ord(self.data[rd])
			rd += 1
			if code == 0x80:
				print('end of data')
				break
			elif code & 0x80:
				code = 257 - code
				for i in range(code):
					planes[wr + i] = ord(self.data[rd])
				rd += 1
			else:
				code += 1
				for i in range(code):
					planes[wr + i] = ord(self.data[rd + i])
				rd += code
			wr += code
		assert wr == size
		assert rd == len(self.data)
		return decode_bitplanes(self.w, self.h, 5, planes)

SHEET_W = 128
SHEET_H = 128

class Rect(ctypes.Structure):
	_fields_ = ('x', ctypes.c_int), ('y', ctypes.c_int), ('w', ctypes.c_int), ('h', ctypes.c_int)

palette = []
for j in range(0, 256):
	palette.append((j * 31) & 255)
	palette.append((j * 31) & 255)
	palette.append((j * 31) & 255)

with open('level1.pal', 'rb') as f:
	r = f.read(16)
	g = f.read(16)
	b = f.read(16)
	for j in range(16):
		palette[j * 3]     = ord(r[j])
		palette[j * 3 + 1] = ord(g[j])
		palette[j * 3 + 2] = ord(b[j])

assert len(sys.argv) == 2
prefix = os.path.splitext(os.path.basename(sys.argv[1]))[0].lower()

CHARSET1_SIZE = 1346
ischarset = os.path.getsize(sys.argv[1]) == CHARSET1_SIZE
if ischarset:
	palette[3] = 0xe0
	palette[4] = 0xe0
	palette[5] = 0xe0

with open(sys.argv[1], 'rb') as f:
	count = struct.unpack('>H', f.read(2))[0]
	r = (Rect * count)()
	for i in range(count):
		if ischarset:
			w = 8
			h = 14
			sz = 0
			depth = 1
			skip = h - 8 # skip the top 6 scanlines
		else:
			w = struct.unpack('>H', f.read(2))[0]
			h = struct.unpack('>H', f.read(2))[0]
			sz = struct.unpack('>H', f.read(2))[0]
			depth = 5
			skip = 0
		#print('w:%d h:%d size:%d offset:0x%x' % (w, h, sz, f.tell()))
		packed = True
		if sz == 0:
			sz = (((w * depth) / 8) * h)
			packed = False
		if ischarset:
			h = 8
		g = gfx(w, h, f.read(sz))
		if not packed:
			picture = decode_bitplanes(w, h, depth, [ ord(b) for b in g.data ], skip)
		else:
			picture = g.decode(depth)
		image = Image.new('P', (w, h))
		image.putpalette(palette)
		image.putdata(picture)
		image.save('/tmp/%s-%03d.png' % (prefix, i), transparency=0)
		r[i].w = w
		r[i].h = h
	lib = ctypes.cdll.LoadLibrary('pack_rect.so')
	w = SHEET_W
	h = SHEET_H
	current = 0
	f = [ (2,1), (1,2) ]
	while lib.pack(ctypes.c_int(w), ctypes.c_int(h), ctypes.byref(r), ctypes.c_int(count)) == 0:
		w *= f[current][0]
		h *= f[current][1]
		current = (current + 1) % len(f)
	image = Image.new('P', (w, h))
	image.putpalette(palette)
	for i in range(count):
		with Image.open('/tmp/%s-%03d.png' % (prefix, i)) as img:
			image.paste(img, (r[i].x, r[i].y))
	image.save('sheet-%s.bmp' % prefix)
	with open('sheet-%s.bin' % prefix, 'wb') as o:
		o.write(struct.pack('<H', count))
		for i in range(count):
			o.write(struct.pack('<HHHH', r[i].x, r[i].y, r[i].w, r[i].h))
