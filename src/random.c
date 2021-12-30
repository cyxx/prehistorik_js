
#include "game.h"

void Random_Reset() {
	g_game.rand = 1;
}

static uint32_t mul(uint16_t lo, uint16_t hi) {
	const uint16_t a = hi * 0x4E35 + lo * 0x15A;
	const uint32_t b = lo * 0x4E35;
	return b + (a << 16);
}

uint16_t Random_GetNumber() {
	g_game.rand = mul(g_game.rand, g_game.rand >> 16);
	++g_game.rand;
	return (g_game.rand >> 16) & 0x7FFF;
}
