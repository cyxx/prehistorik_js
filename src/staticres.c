#include "game.h"

const uint32_t p1_level1_palette_colors[] = {
	0xff000000,
	0xffe0a080,
	0xffa06040,
	0xff804020,
	0xff40a0e0,
	0xffa00020,
	0xffe0c020,
	0xff000000,
	0xff008040,
	0xff20a060,
	0xff000000,
	0xff404040,
	0xff606060,
	0xff808080,
	0xffa0a0a0,
	0xffe0e0e0,
};
uint16_t p1_level1_screen_tbl[] = {
	0x0002,0x00d2,0x008f,0x0006,0x008c,0x0086,0x0002,0x0002,0x0000,0x0012,0x00b4,0x007e,
	0x0000,0x0012,0x0116,0x0052,0x0001,0x0001,0x008b,0x007e,0x0052,0x0001,0x00cb,0x0052,
	0x0026,0x000a,0x0000,0x0000,0x00aa,0x007e,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x000a,0x0000,0x0001,0x010c,0x0052,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0012,0x00c4,0x007e,0x0002,0x0012,0x0116,0x007e,0x0003,
	0x0005,0x00c8,0x0047,0xffce,0x0000,0x0000,0x0002,0x003c,0x008f,0x0002,0x0028,0x0063,
	0x0003,0x0032,0x002f,0x0002,0x0004,0x0113,0x0054,0x0003,0x000a,0x0000,0x0000,0x00bb,
	0x007e,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x000a,0x0000,0x0001,
	0x010d,0x007e,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0012,
	0x00a3,0x0095,0x0004,0x0001,0x00bb,0x0069,0x003d,0x0004,0x00ff,0x003f,0x0000,0x0004,
	0x0122,0x003f,0x0000,0x0004,0x00dc,0x003f,0x0000,0x000a,0x0000,0x0000,0x009b,0x0095,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0012,0x0065,0x0095,
	0x0005,0x0002,0x007d,0x007a,0x0002,0x0096,0x007a,0x0003,0x0046,0x0046,0x0000,0x0003,
	0x0064,0x0046,0x0000,0x0001,0x003a,0x0095,0x0069,0x000d,0x0003,0x0000,0x00f0,0x0071,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x000a,0x0000,0x0000,0x005c,
	0x0095,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0009,0x0096,
	0x00dc,0x0000,0x0000,0x0009,0x00d6,0x00dc,0x0000,0x0000,0x0000,0x0012,0x0045,0x0048,
	0x0006,0x0012,0x00e4,0x0048,0x0007,0x0012,0x0033,0x0074,0x0008,0x0012,0x00d6,0x0074,
	0x0009,0x0001,0x008b,0x0074,0x0048,0x000c,0x0000,0x0000,0x00d6,0x0073,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x000a,0x0000,0x0000,0x002d,0x0074,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x000c,0x0000,0x0000,0x0045,0x0047,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x000a,0x0000,0x0000,0x00db,
	0x0048,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0004,0x003f,
	0x004a,0x0000,0x000e,0x0000,0x00e3,0x006b,0x0000,0x0000,0x0000,0x000d,0x0003,0x0000,
	0x0064,0x0071,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0012,
	0x0094,0x0075,0x000a,0x0005,0x0078,0x003c,0xffce,0x0000,0x0000,0x0004,0x011a,0x008b,
	0x0000,0x0001,0x00ba,0x0075,0x0049,0x000b,0x0000,0x0000,0x0094,0x0079,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0008,0x010e,0x0079,0x0076,0x010c,
	0x009c,0x007d,0x000e,0x0000,0x00be,0x005b,0x0000,0x0000,0x0000,0x000e,0x0000,0x00ef,
	0x006b,0x0000,0x0000,0x0000,0x0000,0x0009,0x00a0,0x00dc,0x0000,0x0000,0x0009,0x0064,
	0x00dc,0x0000,0x0000,0x0009,0x0104,0x00dc,0x0000,0x0000,0x000f,0x0000,0x0000,0x0000,
	0x0000,0x0064,0x006e,0x003c,0x0064,0x0000,0x0009,0x00ba,0x00dc,0x0000,0x0000,0x0009,
	0x0046,0x00dc,0x0000,0x0000,0x0009,0x0104,0x00dc,0x0000,0x0000,0x000f,0x0000,0x0000,
	0x0000,0x0000,0x0032,0x0064,0x0064,0x003c,0x0000,0x0003,0x0070,0x0077,0x0000,0x000e,
	0x0000,0x0100,0x0063,0x0000,0x0000,0x0000,0x0000,0x0012,0x0104,0x0055,0x000b,0x0012,
	0x0064,0x0055,0x000c,0x0012,0x0044,0x0081,0x000d,0x0004,0x00cb,0x002b,0x0000,0x0001,
	0x009b,0x0081,0x0029,0x0001,0x00ca,0x0055,0x0029,0x000b,0x0000,0x0002,0x0065,0x0059,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x000c,0x0000,0x0000,0x0045,
	0x0080,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x000a,0x0000,0x0003,
	0x00fb,0x0055,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0012,
	0x0054,0x0055,0x000e,0x0005,0x0064,0x0018,0xfff6,0x0000,0x0000,0x0002,0x0070,0x0092,
	0x0002,0x002e,0x003a,0x0002,0x0090,0x003a,0x0003,0x005c,0x008a,0x0000,0x0001,0x002a,
	0x0081,0x0055,0x000c,0x0000,0x0001,0x0054,0x0054,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x000d,0x0003,0x0000,0x010e,0x007e,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0010,0x0050,0x00a0,0x0000,0x0082,0x00dc,0x0000,
	0x0002,0x0010,0x0080,0x007d,0x0000,0x0082,0x00dc,0x0000,0x0002,0x0010,0x00b0,0x00c8,
	0x0000,0x0082,0x00dc,0x0000,0x0002,0x0002,0x0119,0x0088,0x0002,0x012d,0x0088,0x0001,
	0x00fb,0x0077,0x004b,0x0000,0x0012,0x00c5,0x009a,0x000f,0x0012,0x00e4,0x006e,0x0010,
	0x0002,0x0078,0x00ab,0x0002,0x003a,0x0088,0x0003,0x0010,0x0080,0x0000,0x0003,0x00f5,
	0x004b,0x0000,0x0003,0x011f,0x004b,0x0000,0x0001,0x011b,0x009a,0x006e,0x0001,0x00ba,
	0x006e,0x0042,0x000f,0x0000,0x0000,0x0000,0x0000,0x0041,0x003c,0x0037,0x003c,0x000b,
	0x0000,0x0000,0x00c5,0x009e,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x000a,0x0000,0x0002,0x00da,0x006e,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0012,0x0055,0x009a,0x0011,0x0012,0x00c5,0x0042,0x0012,0x0012,0x00f4,
	0x006e,0x0013,0x0005,0x0050,0x0064,0xffe2,0x0000,0x0000,0x0001,0x009b,0x009a,0x0042,
	0x0001,0x00db,0x009a,0x006e,0x0002,0x00e6,0x0027,0x0002,0x0030,0x007f,0x0002,0x00c8,
	0x00ab,0x000a,0x0000,0x0003,0x00eb,0x006e,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x000c,0x0000,0x0002,0x00c7,0x0041,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x000b,0x0000,0x0000,0x0055,0x009e,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0012,0x0055,0x006e,0x0014,0x0012,0x0065,0x009a,
	0x0015,0x0008,0x0118,0x0082,0x0076,0x0115,0x00a4,0x007d,0x000c,0x0000,0x0000,0x0056,
	0x006d,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x000c,0x0000,0x0000,
	0x0065,0x0099,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x00ff,
};
uint16_t p1_level1_secret_tbl[] = {
	0x0007,0x0036,0x00a8,0x0000,0x0001,0x0007,0x0056,0x00a8,0x0001,0x0001,0x0007,0x0076,
	0x00a8,0x0002,0x0001,0x0007,0x0096,0x00a8,0x0003,0x0001,0x0007,0x00b6,0x00a8,0x0004,
	0x0001,0x0007,0x00d6,0x00a8,0x0005,0x0001,0x0007,0x00fa,0x00a8,0x0006,0x0001,0x0000,
	0x0007,0x0036,0x00a8,0x0000,0x0001,0x0007,0x0056,0x00a8,0x0001,0x0001,0x0007,0x0076,
	0x00a8,0x0002,0x0001,0x0007,0x0096,0x00a8,0x0003,0x0001,0x0007,0x00b6,0x00a8,0x0004,
	0x0001,0x0007,0x00d6,0x00a8,0x0005,0x0001,0x0007,0x00fa,0x00a8,0x0006,0x0001,0x0000,
	0x00ff,
};
uint16_t p1_level1_cave_tbl[] = {
	0x0013,0x0032,0x0000,0x0096,0x0007,0x005a,0x00a8,0x0001,0x0001,0x0000,0x0013,0x0032,
	0x0000,0x0096,0x0013,0x008c,0x0000,0x0096,0x0007,0x00aa,0x00a8,0x0000,0x0001,0x0007,
	0x00c3,0x00a8,0x0007,0x0001,0x0000,0x0013,0x0032,0x0000,0x0096,0x0007,0x00aa,0x00a8,
	0x0001,0x0001,0x0007,0x00b4,0x00a8,0x0000,0x0001,0x0015,0x0002,0x0116,0x007e,0x0016,
	0x005f,0x0000,0x004b,0x0000,0x0013,0x0064,0x0000,0x0096,0x0007,0x008c,0x00a8,0x0007,
	0x0001,0x0007,0x003c,0x00a8,0x0006,0x0001,0x0000,0x0013,0x0050,0x0000,0x0096,0x0007,
	0x0028,0x00a8,0x0007,0x0001,0x0007,0x00c8,0x00a8,0x0000,0x0001,0x0017,0x0050,0x006e,
	0x0000,0x0000,0x0000,0x0017,0x0096,0x0082,0x0000,0x0000,0x0000,0x0000,0x0013,0x004b,
	0x0000,0x0096,0x0013,0x00c8,0x0000,0x0096,0x0007,0x0032,0x00a8,0x0001,0x0001,0x0007,
	0x0096,0x00a8,0x0007,0x0001,0x0016,0x0096,0x0000,0x004b,0x0000,0x0013,0x0046,0x0000,
	0x0096,0x0013,0x0073,0x0000,0x0096,0x0007,0x00b4,0x00a8,0x0005,0x0001,0x0007,0x0091,
	0x00a8,0x0003,0x0001,0x0017,0x005a,0x0073,0x0000,0x0000,0x0000,0x0017,0x006e,0x0078,
	0x0000,0x0000,0x0000,0x0017,0x008c,0x0087,0x0000,0x0000,0x0000,0x0014,0x00d7,0x00a8,
	0x0005,0x0001,0x0000,0x0013,0x005a,0x0000,0x0096,0x0007,0x00dc,0x00a8,0x0007,0x0001,
	0x0007,0x00f5,0x00a8,0x0006,0x0001,0x0007,0x002d,0x00a8,0x0001,0x0001,0x0007,0x0037,
	0x00a8,0x0004,0x0001,0x0017,0x0046,0x0082,0x0000,0x0000,0x0000,0x0016,0x00b4,0x0000,
	0x004b,0x0000,0x0007,0x0050,0x00a8,0x0002,0x0001,0x0016,0x0023,0x0000,0x004b,0x0015,
	0x0006,0x00d6,0x0074,0x0000,0x0013,0x0046,0x0000,0x0096,0x0013,0x0082,0x0000,0x0096,
	0x0007,0x00af,0x00a8,0x0000,0x0001,0x0007,0x009b,0x00a8,0x0006,0x0001,0x0007,0x005f,
	0x00a8,0x0003,0x0001,0x0017,0x008c,0x0082,0x0000,0x0000,0x0000,0x0000,0x0013,0x0064,
	0x0000,0x0096,0x0007,0x0046,0x00a8,0x0007,0x0001,0x0007,0x008c,0x00a8,0x0006,0x0001,
	0x0007,0x00aa,0x00a8,0x0000,0x0001,0x0016,0x0046,0x0000,0x004b,0x0014,0x00be,0x00a8,
	0x0004,0x0001,0x0000,0x0013,0x00c8,0x0000,0x0096,0x0007,0x0032,0x00a8,0x0004,0x0001,
	0x0007,0x005a,0x00a8,0x0001,0x0001,0x0007,0x0096,0x00a8,0x0003,0x0001,0x0000,0x0016,
	0x002d,0x0000,0x004b,0x0016,0x0069,0x0000,0x004b,0x0016,0x00a0,0x0000,0x004b,0x0016,
	0x00c8,0x0000,0x004b,0x0007,0x00fa,0x00a8,0x0000,0x0001,0x0007,0x00c0,0x00a8,0x0007,
	0x0001,0x0007,0x0096,0x00a8,0x0002,0x0001,0x0014,0x0122,0x00a8,0x0003,0x0001,0x0000,
	0x0007,0x0050,0x00a8,0x0004,0x0001,0x0016,0x0032,0x0000,0x004b,0x0013,0x0032,0x0000,
	0x0096,0x0015,0x000d,0x0065,0x0055,0x0000,0x0013,0x004b,0x0000,0x0096,0x0013,0x0083,
	0x0000,0x0096,0x0017,0x004b,0x0082,0x0000,0x0000,0x0000,0x0017,0x007d,0x007d,0x0000,
	0x0000,0x0000,0x0016,0x0064,0x0000,0x004b,0x0007,0x00aa,0x00a8,0x0001,0x0001,0x0007,
	0x00be,0x00a8,0x0002,0x0001,0x0007,0x0064,0x00a8,0x0003,0x0001,0x0007,0x001e,0x00a8,
	0x0004,0x0001,0x0000,0x0016,0x00cf,0x0000,0x004b,0x0016,0x0064,0x0000,0x004b,0x0013,
	0x0069,0x0000,0x0096,0x0013,0x00e4,0x0000,0x0096,0x0007,0x008c,0x00a8,0x0005,0x0001,
	0x0007,0x003c,0x00a8,0x0006,0x0001,0x0007,0x0122,0x00a8,0x0007,0x0001,0x0007,0x00ff,
	0x00a8,0x0002,0x0001,0x0000,0x0016,0x0028,0x0000,0x004b,0x0016,0x0050,0x0000,0x004b,
	0x0013,0x0044,0x0000,0x0096,0x0007,0x001c,0x00a8,0x0000,0x0001,0x0007,0x0055,0x00a8,
	0x0001,0x0001,0x0007,0x0064,0x00a8,0x0002,0x0001,0x0000,0x0014,0x005e,0x00a8,0x0002,
	0x0001,0x0015,0x0010,0x00e5,0x006e,0x0000,0x0013,0x0050,0x0000,0x0096,0x0013,0x0064,
	0x0000,0x0096,0x0007,0x0096,0x00a8,0x0001,0x0001,0x0007,0x00aa,0x00a8,0x0000,0x0001,
	0x0007,0x00c3,0x00a8,0x0007,0x0001,0x0000,0x0007,0x0046,0x00a8,0x0007,0x0001,0x0007,
	0x0028,0x00a8,0x0003,0x0001,0x0000,0x0007,0x0037,0x00a8,0x0001,0x0001,0x0007,0x00b4,
	0x00a8,0x0000,0x0001,0x0007,0x00d2,0x00a8,0x0007,0x0001,0x0016,0x005f,0x0000,0x004b,
	0x0013,0x0050,0x0000,0x0096,0x0000,0x0013,0x0032,0x0000,0x0096,0x0016,0x004b,0x0000,
	0x004b,0x0016,0x0078,0x0000,0x004b,0x0007,0x008c,0x00a8,0x0007,0x0001,0x0007,0x00aa,
	0x00a8,0x0006,0x0001,0x0000,0x0013,0x008c,0x0000,0x00af,0x0007,0x00b9,0x0077,0x0005,
	0x0001,0x0007,0x00a0,0x00c2,0x0006,0x0001,0x0017,0x0096,0x008c,0x0000,0x0000,0x0000,
	0x0000,0x0014,0x00c8,0x0051,0x0003,0x0001,0x0013,0x0096,0x0000,0x00af,0x0007,0x00b4,
	0x00c1,0x0007,0x0001,0x0007,0x0082,0x006c,0x0006,0x0001,0x0016,0x0078,0x0000,0x006e,
	0x0000,0x0013,0x0096,0x0000,0x00af,0x0007,0x00a0,0x0078,0x0003,0x0001,0x0007,0x007d,
	0x0078,0x0007,0x0001,0x0017,0x0064,0x0096,0x0000,0x0000,0x0000,0x0017,0x0064,0x008c,
	0x0000,0x0000,0x0000,0x0000,0x0013,0x0092,0x0000,0x00af,0x0007,0x00b4,0x00c0,0x0005,
	0x0001,0x0007,0x0078,0x006c,0x0004,0x0001,0x0007,0x005f,0x006c,0x0006,0x0001,0x0016,
	0x0096,0x0000,0x000f,0x0000,0x0013,0x0032,0x0000,0x0096,0x0007,0x00b4,0x00a8,0x0000,
	0x0001,0x0016,0x005f,0x0000,0x004b,0x0000,0x0013,0x0032,0x0000,0x0096,0x0007,0x00a0,
	0x00a8,0x0006,0x0001,0x0007,0x00c8,0x00a8,0x0005,0x0001,0x0017,0x0050,0x006e,0x0000,
	0x0000,0x0000,0x0017,0x0096,0x0082,0x0000,0x0000,0x0000,0x0000,0x0013,0x0032,0x0000,
	0x0096,0x0007,0x0055,0x00a8,0x0007,0x0001,0x0000,0x0013,0x0046,0x0000,0x0096,0x0007,
	0x0064,0x00a8,0x0006,0x0001,0x0000,0x0013,0x0046,0x0000,0x0096,0x0017,0x0064,0x0078,
	0x0000,0x0000,0x0000,0x0017,0x0082,0x0082,0x0000,0x0000,0x0000,0x0017,0x00a0,0x0064,
	0x0000,0x0000,0x0000,0x0007,0x0078,0x00a8,0x0007,0x0001,0x0014,0x00dc,0x00a8,0x0000,
	0x0001,0x0000,0x0013,0x002d,0x0000,0x0096,0x0007,0x0050,0x00a8,0x0002,0x0001,0x0000,
	0x0013,0x0064,0x0000,0x0096,0x0007,0x008c,0x00a8,0x0000,0x0001,0x0007,0x00aa,0x00a8,
	0x0007,0x0001,0x0016,0x002d,0x0000,0x004b,0x0016,0x005f,0x0000,0x004b,0x0000,0x0013,
	0x0054,0x0000,0x0096,0x0007,0x00aa,0x00a8,0x0003,0x0001,0x0007,0x008c,0x00a8,0x0000,
	0x0001,0x0016,0x002d,0x0000,0x004b,0x0016,0x006e,0x0000,0x004b,0x0000,0x0013,0x0037,
	0x0000,0x0096,0x0013,0x003b,0x0000,0x0096,0x0007,0x005a,0x00a8,0x0004,0x0001,0x0000,
	0x0013,0x0064,0x0000,0x0096,0x0017,0x0064,0x0078,0x0000,0x0000,0x0000,0x0017,0x0096,
	0x0082,0x0000,0x0000,0x0000,0x0013,0x00c8,0x0000,0x0096,0x0017,0x00a0,0x0064,0x0000,
	0x0000,0x0000,0x0007,0x0082,0x00a8,0x0007,0x0001,0x0007,0x004a,0x00a8,0x0000,0x0001,
	0x0014,0x011d,0x00a8,0x0003,0x0001,0x0000,0x0007,0x0064,0x00a8,0x0006,0x0001,0x0000,
	0x0016,0x0032,0x0000,0x004b,0x0013,0x0028,0x0000,0x0096,0x0007,0x0046,0x00a8,0x0003,
	0x0001,0x0015,0x0005,0x00a2,0x0057,0x0014,0x0065,0x00a8,0x0005,0x0001,0x0000,0x0016,
	0x0064,0x0000,0x004b,0x0013,0x004b,0x0000,0x0096,0x0013,0x0083,0x0000,0x0096,0x0017,
	0x004b,0x0082,0x0000,0x0000,0x0000,0x0017,0x007d,0x007d,0x0000,0x0000,0x0000,0x0007,
	0x0096,0x00a8,0x0000,0x0001,0x0007,0x00b4,0x00a8,0x0001,0x0001,0x0007,0x00c8,0x00a8,
	0x0002,0x0001,0x0000,0x0013,0x0032,0x0000,0x0096,0x0007,0x005a,0x00a8,0x0001,0x0001,
	0x0000,0x0013,0x0032,0x0000,0x0096,0x0007,0x0064,0x00a8,0x0001,0x0001,0x0007,0x00b4,
	0x00a8,0x0000,0x0001,0x0016,0x005f,0x0000,0x004b,0x0015,0x0002,0x0101,0x007d,0x0000,
	0x0013,0x004b,0x0000,0x0096,0x0013,0x00c8,0x0000,0x0096,0x0007,0x0032,0x00a8,0x0001,
	0x0001,0x0007,0x0096,0x00a8,0x0007,0x0001,0x0016,0x0096,0x0000,0x004b,0x0000,0x0013,
	0x00b4,0x0000,0x0096,0x0017,0x005a,0x0073,0x0000,0x0000,0x0000,0x0017,0x0032,0x0078,
	0x0000,0x0000,0x0000,0x0017,0x008c,0x0087,0x0000,0x0000,0x0000,0x0007,0x0091,0x00a8,
	0x0003,0x0001,0x0007,0x004e,0x00a8,0x0005,0x0001,0x0014,0x00d7,0x00a8,0x0005,0x0001,
	0x0013,0x0073,0x0000,0x0096,0x0000,0x0013,0x005a,0x0000,0x0096,0x0017,0x0046,0x0082,
	0x0000,0x0000,0x0000,0x0016,0x0082,0x0000,0x004b,0x0016,0x00b4,0x0000,0x004b,0x0007,
	0x00dc,0x00a8,0x0007,0x0001,0x0007,0x00f5,0x00a8,0x0006,0x0001,0x0007,0x002d,0x00a8,
	0x0005,0x0001,0x0007,0x009b,0x00a8,0x0004,0x0001,0x0000,0x0016,0x003c,0x0000,0x004b,
	0x0007,0x0064,0x00a8,0x0003,0x0001,0x0015,0x0005,0x0102,0x008d,0x0000,0x0013,0x00c8,
	0x0000,0x0096,0x0007,0x0032,0x00a8,0x0007,0x0001,0x0007,0x005a,0x00a8,0x0001,0x0001,
	0x0007,0x0096,0x00a8,0x0003,0x0001,0x0000,0x0016,0x0046,0x0000,0x004b,0x0016,0x006e,
	0x0000,0x004b,0x0016,0x00a0,0x0000,0x004b,0x0016,0x00c8,0x0000,0x004b,0x0007,0x00fa,
	0x00a8,0x0000,0x0001,0x0007,0x00c0,0x00a8,0x0007,0x0001,0x0007,0x0096,0x00a8,0x0002,
	0x0001,0x0014,0x0122,0x00a8,0x0003,0x0001,0x0000,0x0016,0x0032,0x0000,0x004b,0x0007,
	0x0050,0x00a8,0x0004,0x0001,0x0013,0x0032,0x0000,0x0096,0x0015,0x0004,0x0065,0x0055,
	0x0000,0x0016,0x0064,0x0000,0x004b,0x0013,0x004b,0x0000,0x0096,0x0013,0x0083,0x0000,
	0x0096,0x0017,0x004b,0x0082,0x0000,0x0000,0x0000,0x0017,0x007d,0x007d,0x0000,0x0000,
	0x0000,0x0007,0x00aa,0x00a8,0x0001,0x0001,0x0007,0x00be,0x00a8,0x0002,0x0001,0x0007,
	0x0064,0x00a8,0x0003,0x0001,0x0007,0x001e,0x00a8,0x0004,0x0001,0x0000,0x0016,0x0028,
	0x0000,0x004b,0x0016,0x006e,0x0000,0x004b,0x0016,0x00b0,0x0000,0x004b,0x0016,0x00f0,
	0x0000,0x004b,0x0007,0x00fa,0x00a8,0x0000,0x0001,0x0007,0x00c0,0x00a8,0x0007,0x0001,
	0x0014,0x0122,0x00a8,0x0003,0x0001,0x0000,0x0015,0x0002,0x00e5,0x006e,0x0014,0x005e,
	0x00a8,0x0002,0x0001,0x0000,0x0013,0x0050,0x0000,0x0096,0x0013,0x0064,0x0000,0x0096,
	0x0007,0x0096,0x00a8,0x0001,0x0001,0x0007,0x00aa,0x00a8,0x0000,0x0001,0x0007,0x00c3,
	0x00a8,0x0007,0x0001,0x0000,0x0007,0x0046,0x00a8,0x0007,0x0001,0x0007,0x0028,0x00a8,
	0x0003,0x0001,0x0000,0x00ff,
};
const uint16_t p1_level1_elem_size_tbl[] = {
	0x0009,0x0012,0x000e,0x0011,0x0010,0x000b,0x0011,0x000e,0x0010,0x0014,0x000c,0x000c,
	0x0012,0x0016,0x0018,0x0014,0x0014,0x0015,0x0013,0x0014,
};
const uint16_t p1_level1_elem_data_tbl[] = {
	0x010e,0x0046,0x000d,0x00fa,0x005a,0x000d,0x0118,0x0064,0x000d,0x008c,0x007f,0x0004,
	0x005e,0x009b,0x0001,0x006e,0x009b,0x0002,0x0096,0x009b,0x0002,0x00c0,0x009b,0x0002,
	0x00ea,0x009b,0x0002,0x0114,0x009b,0x0002,0x001e,0x003c,0x000d,0x003c,0x004c,0x000d,
	0xfff0,0x009b,0x0002,0x0026,0x009b,0x0002,0x005e,0x009b,0x0002,0x0086,0x009b,0x0002,
	0x00b0,0x009b,0x0002,0x00da,0x009b,0x0002,0x0104,0x009b,0x0002,0x0130,0x009b,0x0002,
	0x0080,0x006f,0x0005,0x00a0,0x006f,0x0009,0x00f0,0x006f,0x0006,0x0090,0x006f,0x000a,
	0x0094,0x0043,0x0005,0x00b4,0x0043,0x0006,0x0104,0x0043,0x0009,0x00dc,0x0043,0x000a,
	0x0055,0x007f,0x0015,0x0001,0x009b,0x0002,0x006e,0x009b,0x0002,0x0096,0x009b,0x0002,
	0x00c0,0x009b,0x0002,0x00ea,0x009b,0x0002,0x0114,0x009b,0x0002,0xffca,0x006f,0x0006,
	0xfff0,0x0043,0x0006,0x0064,0x006f,0x0007,0x0096,0x006f,0x0005,0x0036,0x009b,0x0002,
	0x0046,0x0043,0x0007,0x00b4,0x006f,0x0009,0x0104,0x006f,0x0009,0x0011,0x006f,0x0006,
	0xffd0,0x009b,0x0002,0x0000,0x009b,0x0002,0x003e,0x009b,0x0003,0x007a,0x00b2,0x0001,
	0x0082,0x00b2,0x0002,0x00b8,0x00b2,0x0002,0x00ea,0x00b2,0x0002,0x0118,0x00b2,0x0002,
	0x0000,0x006f,0x0007,0x0090,0x0086,0x0009,0x00e0,0x0086,0x0006,0x007a,0x0086,0x0005,
	0x0130,0x0086,0x0006,0x0084,0x005a,0x0005,0x00a4,0x005a,0x0006,0x00f4,0x005a,0x0006,
	0x00cc,0x005a,0x000a,0x0014,0x0029,0x0010,0x00ca,0x0091,0x0001,0xfff0,0x00b2,0x0002,
	0x0026,0x00b2,0x0002,0x005e,0x00b2,0x0002,0x0086,0x00b2,0x0002,0x00b0,0x00b2,0x0002,
	0x00da,0x0091,0x0002,0x0104,0x0091,0x0002,0x0130,0x0091,0x0002,0x0000,0x0086,0x0006,
	0x00a0,0x0086,0x0007,0x0054,0x0086,0x0009,0x004c,0x0086,0x000a,0x00da,0x00b2,0x0003,
	0xffd0,0x005a,0x0006,0x0024,0x005a,0x0006,0x0070,0x005a,0x0007,0x000a,0x003c,0x000d,
	0x0028,0x0046,0x000d,0x010e,0x0032,0x000d,0x0122,0x0050,0x000d,0x0118,0x0041,0x000d,
	0xffe0,0x0091,0x0002,0x0010,0x0091,0x0002,0x0040,0x0091,0x000e,0x0080,0x0091,0x000e,
	0x0100,0x0091,0x0002,0x00ca,0x0091,0x000e,0x0130,0x0091,0x0002,0x0000,0x0091,0x0002,
	0x0020,0x0091,0x0002,0x0050,0x0091,0x0002,0x0080,0x0091,0x0002,0x00b0,0x0091,0x0002,
	0x00e0,0x0091,0x0002,0x0110,0x0091,0x0002,0x0000,0x0065,0x0005,0x0020,0x0065,0x0009,
	0x0070,0x0065,0x0006,0x00c0,0x0065,0x0009,0x0110,0x0065,0x0006,0x0010,0x0039,0x0005,
	0x0030,0x0039,0x0009,0x0080,0x0039,0x0006,0x00d0,0x0039,0x0009,0x0120,0x0039,0x0007,
	0x0090,0x0065,0x000a,0xfff0,0x0091,0x0002,0x0020,0x0091,0x0002,0x0050,0x0091,0x0002,
	0x0080,0x0091,0x0002,0x00b0,0x0091,0x0003,0x00c0,0x00a0,0x0003,0x00c0,0x00b1,0x0002,
	0x00b0,0x00a0,0x0001,0x00f0,0x00b1,0x0003,0x0120,0x00b1,0x0001,0x0000,0x0065,0x0006,
	0x0050,0x0065,0x0007,0x013f,0x00b1,0x0002,0x00b0,0x00b1,0x0001,0x00c5,0x003f,0x0010,
	0x0080,0x0066,0x0009,0x00d0,0x0066,0x0007,0x0060,0x0066,0x0005,0x00c0,0x0066,0x000a,
	0x00f0,0x0092,0x0003,0x00c0,0x0092,0x0002,0x0090,0x0092,0x0002,0x0060,0x0092,0x0002,
	0x0050,0x0092,0x0001,0x0060,0x00a1,0x0003,0x0030,0x00a1,0x0002,0x0020,0x00a1,0x0001,
	0x0000,0x00b1,0x0002,0x0030,0x00b1,0x0003,0x00f0,0x00a6,0x0001,0x0100,0x00a6,0x0002,
	0x0136,0x00a6,0x0002,0x00aa,0x0020,0x0010,0xfff0,0x00a6,0x0002,0x0020,0x008f,0x0001,
	0x0020,0x00a6,0x0003,0x0030,0x008f,0x0002,0x0060,0x008f,0x0003,0x00a0,0x0092,0x0002,
	0x0100,0x00aa,0x000f,0x00d0,0x0092,0x0003,0x00d0,0x00a6,0x0002,0x00e0,0x00a6,0x0002,
	0x0110,0x00a6,0x0003,0x00dc,0x0034,0x0010,0x0094,0x0092,0x0001,0x0050,0x00ac,0x0001,
	0x0060,0x00ac,0x0002,0x0136,0x00aa,0x000f,0x0090,0x00ac,0x0003,0x0130,0x00b8,0x0012,
	0x0120,0x00b9,0x0013,0x00c8,0x00a6,0x0001,0x0000,0x00aa,0x000f,0x0030,0x00a9,0x000f,
	0x0060,0x00aa,0x000f,0x0090,0x00a9,0x000f,0x00c0,0x00aa,0x000f,0x00f0,0x00a9,0x000f,
	0x0120,0x00aa,0x000f,0x0064,0x00b8,0x0011,0x0032,0x00b8,0x0013,0x00bc,0x00bb,0x0012,
	0x0000,0x00ba,0x0012,0x012c,0x00b8,0x0013,0x00dc,0x00ba,0x0013,0x0000,0x00a9,0x000f,
	0x0030,0x00aa,0x000f,0x0060,0x00a9,0x000f,0x0090,0x00aa,0x000f,0x00c0,0x00a9,0x000f,
	0x00f0,0x00aa,0x000f,0x0120,0x00a9,0x000f,0x0032,0x00b8,0x0011,0x004b,0x00b8,0x0013,
	0x0064,0x00bb,0x0012,0x0096,0x00ba,0x0012,0x00c8,0x00b8,0x0013,0x0118,0x00ba,0x0013,
	0x0070,0x0072,0x0001,0x0080,0x0072,0x0003,0x0050,0x008b,0x0002,0x0080,0x008b,0x0003,
	0x0040,0x008b,0x0001,0xfff0,0x00a9,0x000f,0x0020,0x00a9,0x000f,0x0050,0x00a9,0x000f,
	0x0080,0x00a9,0x000f,0x00b0,0x00a9,0x000f,0x00c0,0x009e,0x0001,0x00d0,0x009e,0x0002,
	0x0100,0x009e,0x0002,0x0130,0x009e,0x0002,0x00e0,0x002c,0x0010,0x00b0,0x00b7,0x0011,
	0x0030,0x00b7,0x0012,0x0080,0x00b8,0x0013,0x0050,0x00be,0x0012,0x0120,0x009e,0x0016,
	0x00d0,0x009e,0x0016,0x0080,0x009e,0x0016,0x00d0,0x0072,0x0006,0x0120,0x0072,0x0006,
	0x00f0,0x0046,0x0009,0x00a0,0x0046,0x0006,0x0080,0x0072,0x0016,0x0030,0x0072,0x0009,
	0x0010,0x0072,0x0005,0x0050,0x0046,0x0009,0x0030,0x0046,0x0005,0x0100,0x00a9,0x0008,
	0x00d0,0x00a9,0x0008,0x00a0,0x00aa,0x0008,0x00b0,0x009e,0x0003,0x0080,0x009e,0x0002,
	0x0050,0x009e,0x0002,0x0020,0x009e,0x0002,0x0000,0x009e,0x0002,0x00a0,0x0046,0x000a,
	0x00a0,0x0070,0x000a,0x00d0,0x0046,0x000a,0x0000,0x009e,0x0016,0x0050,0x009e,0x0016,
	0xfff0,0x00a9,0x0008,0x0020,0x00a9,0x0008,0x0050,0x00a9,0x0008,0x0080,0x00a8,0x0008,
	0x0000,0x0072,0x0006,0x0050,0x0072,0x0006,0x00a0,0x0072,0x0007,0x00a0,0x009e,0x0001,
	0x00b0,0x009e,0x0002,0x0120,0x0059,0x000d,0x0100,0x0041,0x000d,0x00f0,0x006a,0x000d,
	0x00e0,0x009e,0x0002,0x0110,0x009e,0x0002,0x0090,0x0046,0x0007,0x0040,0x0046,0x0009,
	0xfff0,0x0046,0x0006,0x0030,0x0072,0x000a,0x0070,0x009e,0x0003,0x0040,0x009e,0x0002,
	0x0030,0x009e,0x0001,0x0020,0x00a9,0x0008,0x0050,0x00a8,0x0008,0x0020,0x00ad,0x000f,
	0x0030,0x009e,0x0003,0x0050,0x00c8,0x0001,0x0060,0x00c8,0x0003,0x0040,0x00aa,0x0008,
	0x0080,0x00c8,0x0001,0x0090,0x00c8,0x0003,0x0070,0x00a9,0x0008,0x00b0,0x00c8,0x0001,
	0x00c0,0x00c8,0x0003,0x00b0,0x00ac,0x000f,0x00e0,0x0094,0x0001,0x0110,0x0068,0x0002,
	0x0100,0x0068,0x0001,0x00f0,0x0068,0x0001,0x00f0,0x0094,0x0002,0x0120,0x0094,0x0002,
	0x0100,0x0068,0x000a,0x0020,0x0056,0x000d,0x0000,0x003f,0x000d,0x0000,0x009e,0x0002,
	0xfff0,0x0068,0x0002,0x0020,0x0068,0x0003,0x0000,0x0094,0x0002,0x0040,0x0044,0x000d,
	0x0050,0x0061,0x000d,0x0020,0x0094,0x0002,0x0050,0x0094,0x0003,0x0040,0x00b7,0x0001,
	0x0050,0x00b7,0x0002,0x0080,0x00b7,0x0002,0x00b0,0x00b7,0x0002,0x00e0,0x00b7,0x0002,
	0x0110,0x00b7,0x0002,0x0090,0x008b,0x0005,0x00b0,0x008b,0x0009,0x0100,0x008b,0x0006,
	0x00b0,0x005f,0x0005,0x00d0,0x005f,0x0009,0x0120,0x005f,0x0007,0x00c0,0x005f,0x000a,
	0x0120,0x008b,0x000a,0x0000,0x00b7,0x0002,0x0030,0x00b7,0x0002,0x0060,0x00b7,0x0002,
	0x0090,0x00b7,0x0002,0x00c0,0x00b7,0x0002,0x00f0,0x00b7,0x0002,0x0120,0x00b7,0x0002,
	0xfff0,0x008b,0x0006,0x0040,0x008b,0x0009,0x0090,0x008b,0x0016,0x0090,0x005f,0x0006,
	0x0070,0x005f,0x0005,0x00e0,0x008b,0x0006,0x00e0,0x005f,0x0009,0x0090,0x0033,0x0005,
	0x00b0,0x0033,0x0009,0x0100,0x0033,0x0006,0x00a0,0x005f,0x000a,0x00a0,0x008a,0x000a,
	0x00e0,0x008b,0x000a,0x0130,0x008b,0x0006,0x0130,0x005f,0x0006,0x0000,0x00b7,0x0002,
	0x0020,0x00b7,0x0002,0x0050,0x00b7,0x0002,0x0080,0x00b7,0x0002,0x00a0,0x00b9,0x0008,
	0x00d0,0x00b8,0x0008,0x00b0,0x00b7,0x0003,0x00a0,0x008b,0x0007,0x0000,0x008b,0x0006,
	0x0050,0x008b,0x0009,0x0090,0x005f,0x0007,0x0040,0x005f,0x0009,0xfff0,0x005f,0x0016,
	0x0000,0x0033,0x0006,0x0040,0x0033,0x0007,0x00e0,0x0095,0x0001,0x00f0,0x0095,0x0003,
	0x00f0,0x00ae,0x0001,0x0100,0x00ae,0x0002,0x00f0,0x003c,0x0010,
};
const uint16_t p1_level1_screen_height_tbl[] = {
	0x00c7,0x00c7,0x00c7,0x00c7,0x00c7,0x00a0,0x00c7,0x00c7,0x00c7,0x00c7,0x00af,0x00af,
	0x00af,0x00af,0x00af,0x00af,0x00c7,0x00c7,0x00c7,0x00c7,
};
const uint16_t p1_level1_cave_size_tbl[] = {
	0x0060,0x00e0,0x00e0,0x00e0,0x00e0,0x0120,0x00e0,0x0120,0x0060,0x00e0,0x00e0,0x00e0,
	0x0120,0x0060,0x00e0,0x0120,0x0060,0x0060,0x00e0,0x0060,0x00e0,0x00e0,0x00e0,0x00e0,
	0x0060,0x0060,0x00e0,0x0060,0x00e0,0x00e0,0x0060,0x0120,0x0060,0x0060,0x00e0,0x0060,
	0x00e0,0x0120,0x00e0,0x0120,0x0060,0x00e0,0x0120,0x0060,0x00e0,0x0120,0x0060,0x00e0,
	0x0060,
};
const uint16_t p1_player_walk_spr_num_tbl[] = {
	0x0001,0x0002,0x0061,0x0001,0x0003,0x0062,
};
const uint16_t p1_player_walk_x_vel_tbl[] = {
	0x0004,0x0006,0x0006,0x0004,0x0006,0x0006,
};
const uint16_t p1_player_walk_dx_tbl[] = {
	0x0000,0xfffa,0xfffb,0x0000,0xfffa,0xfffb,
};
const uint16_t p1_player_hitting_spr_num_tbl[] = {
	0x0005,0xffff,0x0005,0xfff9,0x0004,0x0000,0x0004,0x0000,
};
const uint16_t p1_player_club_spr_num_tbl[] = {
	0x000e,0xfff1,0x000e,0x0014,0x0003,0x0007,0x000e,0xfff1,0x000e,0x0014,0x0009,0x0007,
};
const uint16_t p1_player_axe_spr_num_tbl[] = {
	0x000e,0xfff1,0x008b,0x0014,0x0003,0x0089,0x000e,0xfff1,0x008b,0x0014,0x0009,0x0089,
};
const uint8_t p1_object0x0a_data[] = {
	0x14,0x00,0x1e,0x00,0x04,0x00,0x1c,0x00,0x1d,0x00,0x1e,0x00,0x2d,0x00,0x64,0x00,
	0x18,0x00,0x12,0x00,0x1c,0x00,0x14,0x00,0x1f,0x00,0x17,0x00,0x02,0x00,0x01,0x00,
	0x00,0x00,0x01,0x00,0x08,0x00,0x02,0x00,0x00,0x00,0x01,0x00,0x08,0x00,0x02,0x00,
};
const uint8_t p1_object0x0b_data[] = {
	0x0d,0x00,0x1e,0x00,0x04,0x00,0x16,0x00,0x19,0x00,0x14,0x00,0x23,0x00,0xf4,0x01,
	0x73,0x00,0x20,0x00,0x6e,0x00,0x6a,0x00,0x72,0x00,0x72,0x00,0x01,0x00,0x01,0x00,
	0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,
};
const uint8_t p1_object0x0c_data[] = {
	0x15,0x00,0x1e,0x00,0x04,0x00,0x16,0x00,0x1e,0x00,0x14,0x00,0x23,0x00,0xc8,0x00,
	0x4c,0x00,0x46,0x00,0x4e,0x00,0x48,0x00,0x51,0x00,0x4b,0x00,0x03,0x00,0x01,0x00,
	0x00,0x00,0x01,0x00,0x06,0x00,0x02,0x00,0x00,0x00,0x01,0x00,0x06,0x00,0x02,0x00,
};
const uint8_t p1_object0x0d_data[] = {
	0x0f,0x00,0x23,0x00,0x04,0x00,0x28,0x00,0x20,0x00,0x3c,0x00,0x46,0x00,0xf4,0x01,
	0x35,0x00,0x46,0x00,0x37,0x00,0x30,0x00,0x34,0x00,0x34,0x00,0x05,0x00,0x00,0x00,
	0x00,0x00,0x01,0x00,0x02,0x00,0x03,0x00,0x00,0x00,0x01,0x00,0x02,0x00,0x03,0x00,
};
const uint16_t p1_score_tbl[] = {
	0x000a,0x0032,0x0064,0x00c8,0x01f4,
};
const uint16_t p1_player_death_spr_num_tbl[] = {
	0x0008,0x0008,0x0065,0x0066,0x0067,0x0068,0x0068,0x0068,
};
const uint16_t p1_bonus_spr_num_tbl[] = {
	0x005b,0x0052,0x005a,0x0083,0x0084,0x008c,
};
const uint16_t p1_secret_score_tbl[] = {
	0x0032,0x000a,0x0032,0x000a,0x0032,0x0032,0x0032,0x000a,0x0032,0x000a,
};
const uint16_t p1_bird_spr_num_tbl[] = {
	0x0001,0x0000,0x0001,0x0002,0x0001,0x0000,0x0001,0x0002,
};
const uint8_t p1_secret_palette_data[] = {
	0x00,0x00,0x00,0x03,0x06,0x06,0x03,0x05,0x06,0x02,0x04,0x06,0x02,0x05,0x07,0x03,
	0x04,0x07,0x00,0x06,0x06,0x00,0x00,0x00,0x00,0x03,0x04,0x00,0x04,0x05,0x00,0x00,
	0x00,0x01,0x03,0x03,0x02,0x04,0x04,0x03,0x05,0x05,0x04,0x06,0x06,0x03,0x07,0x07,
};
const uint8_t p1_level1_cave_palette_data[] = {
	0x00,0x00,0x00,0x05,0x03,0x02,0x04,0x02,0x01,0x03,0x01,0x00,0x00,0x00,0x00,0x05,
	0x00,0x01,0x07,0x06,0x01,0x00,0x00,0x00,0x00,0x04,0x02,0x01,0x05,0x03,0x00,0x00,
	0x00,0x01,0x01,0x01,0x02,0x02,0x02,0x03,0x03,0x03,0x04,0x04,0x04,0x06,0x06,0x06,
};
