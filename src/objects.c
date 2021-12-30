
#include "game.h"

enum {
	OBJ_STAIRS = 0x01, /* obj_stairs_t */
	OBJ_PEAK = 0x02, /* obj2_t */
	OBJ_EGG = 0x03, /* obj3_t */
	OBJ_ROCK = 0x04, /* obj3_t */
	OBJ_BONUS = 0x05, /* obj5_t */
	OBJ_HIDDEN_FOOD = 0x06, /* obj_food_t */
	OBJ_SECRET_FOOD = 0x07, /* obj_food_t */
	OBJ_BALLOONS = 0x08, /* obj_balloons_t */
	OBJ_FISH = 0x09, /* obj_fish_t */
	OBJ_GUBBA_GLUB = 0x0a, /* obj_monster_t */
	OBJ_BEAR = 0x0b, /* obj_monster_t */
	OBJ_PYRO_TAX = 0x0c, /* obj_monster_t */
	OBJ_TURTOSAURUS = 0x0d, /* obj_monster_t */
	OBJ_CHIMP_AGOGO = 0x0e, /* obj_monkey_t */
	OBJ_PTERIYAKI = 0x0f, /* obj_bird_t */
	OBJ_PLATFORM = 0x10, /* obj_platform_t */
	OBJ_CAVE_ENTRANCE = 0x12, /* obj3_t */
	OBJ_FIRE = 0x13, /* obj_fire_t */
	OBJ_CAVE_SIGN = 0x15, /* obj_cave_sign_t */
	OBJ_CAVE_SPIDER = 0x16, /* obj_cave_spider_t */
	OBJ_CAVE_BAT = 0x17, /* obj_cave_bat_t */
};

enum {
	MONSTER_STATE_RESET = 0,
	MONSTER_STATE_IDLE = 1,
	MONSTER_STATE_HEADING_PLAYER = 3,
	MONSTER_STATE_RUNNING_AWAY = 4,
	MONSTER_STATE_KO = 5,
	MONSTER_STATE_DEAD = 6,
};

struct obj_stairs_t {
	int16_t x;
	int16_t y_top;
	int16_t y_bottom;
} __attribute__((packed));

struct obj2_t {
	int16_t x_pos;
	int16_t y_pos;
} __attribute__((packed));

struct obj3_t {
	int16_t x_pos;
	int16_t y_pos;
	int16_t counter;
} __attribute__((packed));

struct obj5_t {
	int16_t x_pos;
	int16_t y_pos;
	int16_t init_counter;
	int16_t counter;
	int16_t mask;
} __attribute__((packed));

struct obj_food_t {
	int16_t x_pos;
	int16_t y_pos;
	int16_t spr_num;
	int16_t state;
} __attribute__((packed));

struct obj_balloons_t {
	int16_t balloon1_x_pos;
	int16_t balloon1_y_pos;
	int16_t balloon1_spr_num;
	int16_t balloon2_x_pos;
	int16_t balloon2_y_pos;
	int16_t balloon2_spr_num;
} __attribute__((packed));

struct obj_fish_t {
	int16_t x_pos;
	int16_t y_pos;
	int16_t y_vel;
	int16_t state;
} __attribute__((packed));

struct obj_monster_t {
	int16_t init_state;
	int16_t unk2;
	int16_t init_x_pos;
	int16_t init_y_pos;
	int16_t state;
	int16_t lifes;
	int16_t x_pos;
	int16_t y_pos;
	int16_t direction;
	int16_t state_counter;
	int16_t ko_counter;
	int16_t unk22;
} __attribute__((packed));

struct obj_monkey_t {
	int16_t state;
	int16_t x_pos;
	int16_t y_pos;
	int16_t throw_flag;
	int16_t throw_x;
	int16_t throw_y;
} __attribute__((packed));

struct obj_bird_t {
	int16_t state;
	int16_t unk2;
	int16_t unk4;
	int16_t frame;
	int16_t unk8[4];
} __attribute__((packed));

struct obj_platform_t {
	int16_t x_pos;
	int16_t y_pos;
	int16_t current_y_pos;
	int16_t y_top;
	int16_t y_bottom;
	int16_t direction;
	int16_t dy;
} __attribute__((packed));

struct obj_fire_t {
	int16_t x_pos;
	int16_t state;
	int16_t y_pos;
} __attribute__((packed));

struct obj_cave_sign_t {
	int16_t screen_num;
	int16_t screen_x_pos;
	int16_t screen_y_pos;
} __attribute__((packed));

struct obj_cave_spider_t {
	int16_t x_pos;
	int16_t counter;
	int16_t y_pos;
} __attribute__((packed));

struct obj_cave_bat_t {
	int16_t unk0;
	int16_t unk2;
	int16_t state;
	int16_t unk6;
	int16_t unk8;
} __attribute__((packed));

static uint8_t object_size(int num) {
	switch (num) {
	case 0x00: /* screen separator */
		return 2;
	case 0x10:
		return 16;
	case 0x06:
	case 0x07:
	case 0x09:
	case 0x14:
	case 0x18:
		return 10;
	case 0x01:
	case 0x03:
	case 0x04:
	case 0x11:
	case 0x12:
	case 0x13:
	case 0x15:
	case 0x16:
	case 0x19:
	case 0x1c:
	case 0x1d:
		return 8;
	case 0x05:
	case 0x17:
	case 0x1e:
	case 0x1f:
		return 12;
	case 0x0f:
	case 0x23:
		return 18;
	case 0x08:
	case 0x0e:
	case 0x20:
	case 0x24:
		return 14;
	case 0x02:
	case 0x25:
		return 6;
	case 0x0a:
	case 0x0b:
	case 0x0c:
	case 0x0d:
	case 0x1a:
	case 0x1b:
	case 0x21:
	case 0x22:
	case 0x26:
	case 0x27:
		return 26;
	}
	return 0;
}

void Objects_Reset(uint16_t *p) {
	while (1) {
		const uint16_t num = p[0];
		if (num == 0xFF) {
			break;
		}
		switch (num) {
		case 0x00:
			break;
		case 0x01:
		case 0x11:
		case 0x12:
		case 0x15:
		case 0x19:
			break;
		case 0x02:
		case 0x25:
			break;
		case 0x03:
		case 0x1c: {
				struct obj3_t *obj = (struct obj3_t *)(p + 1);
				obj->counter = 2;
			}
			break;
		case 0x04: {
				struct obj3_t *obj = (struct obj3_t *)(p + 1);
				obj->counter = 3;
			}
			break;
		case 0x05: {
				struct obj5_t *obj = (struct obj5_t *)(p + 1);
				obj->counter = obj->init_counter;
				obj->mask = 0;
			}
			break;
		case 0x06: {
				struct obj_food_t *obj = (struct obj_food_t *)(p + 1);
				obj->state = 2;
			}
			break;
		case 0x07:
		case 0x14: {
				struct obj_food_t *obj = (struct obj_food_t *)(p + 1);
				obj->state = 1;
			}
			break;
		case 0x08:
			break;
		case 0x09: {
				struct obj_fish_t *obj = (struct obj_fish_t *)(p + 1);
				obj->y_pos = 220;
				obj->y_vel = 16 + (Random_GetNumber() % 5);
				obj->state = 0;
			}
			break;
		case 0x0a:
		case 0x0b:
		case 0x0c:
		case 0x0d:
		case 0x1a:
		case 0x1b:
		case 0x21:
		case 0x22:
		case 0x26:
		case 0x27: {
				struct obj_monster_t *obj = (struct obj_monster_t *)(p + 1);
				obj->state = obj->init_state;
				obj->lifes = obj->unk2;
				obj->x_pos = obj->init_x_pos;
				obj->y_pos = obj->init_y_pos;
				obj->state_counter = 0;
				obj->ko_counter = 0;
			}
			break;
		case 0x0e:
		case 0x20: {
				struct obj_monkey_t *obj = (struct obj_monkey_t *)(p + 1);
				obj->throw_flag = 0;
				obj->state = 0;
			}
			break;
		case 0x0f: {
				struct obj_bird_t *obj = (struct obj_bird_t *)(p + 1);
				obj->frame = 0;
				obj->unk4 = 0;
				obj->state = 0;
			}
			break;
		case 0x10: {
				struct obj_platform_t *obj = (struct obj_platform_t *)(p + 1);
				obj->current_y_pos = obj->y_pos;
				obj->direction = 0;
			}
			break;
		case 0x13: {
				struct obj_fire_t *obj = (struct obj_fire_t *)(p + 1);
				obj->state = 0;
			}
			break;
			break;
		case 0x16: {
				struct obj_cave_spider_t *obj = (struct obj_cave_spider_t *)(p + 1);
				obj->counter = Random_GetNumber() % 15;
			}
			break;
		case 0x17: {
				struct obj_cave_bat_t *obj = (struct obj_cave_bat_t *)(p + 1);
				obj->state = 0;
				obj->unk6 = obj->unk0;
				obj->unk8 = obj->unk2;
			}
			break;
		default:
			fprintf(stderr, "Unhandled object 0x%x reset\n", num);
			break;
		}
		p += object_size(num) / sizeof(uint16_t);
	}
}

static void update_bonus(int num) {
	switch (num) {
	case 0: /* BONUS_SPRING */
		g_game.player_y_vel = 34;
		break;
	case 1: /* BONUS_BOMB */
		g_game.bomb_flag = 1;
		Game_SetPaletteBomb();
		break;
	case 2: /* BONUS_ALARM */
		g_game.time += 30;
		if (g_game.time > 99) {
			g_game.time = 99;
		}
		g_game.timer_counter = 60;
		break;
	case 3: /* BONUS_CROSS_OF_LIFE */
		if (g_game.player_lifes < 99) {
			++g_game.player_lifes;
		}
		break;
	case 4: /* BONUS_SHIELD */
		g_game.player_halo_duration = 99;
		break;
	case 5: /* BONUS_AXE */
		g_game.player_axe_flag = 1;
		break;
	default:
		fprintf(stderr, "Unhandled bonus %d update\n", num);
		break;
	}
}

static void update_monster(const uint8_t *monster, struct obj_monster_t *objm, int num) {
	int16_t dat00 = READ_LE_UINT16(monster); monster += 2;
	int16_t dat02 = READ_LE_UINT16(monster); monster += 2;
	/*int16_t dat04 = READ_LE_UINT16(monster);*/ monster += 2;
	int16_t di    = READ_LE_UINT16(monster); monster += 2;
	int16_t si    = READ_LE_UINT16(monster); monster += 2;
	int16_t var18 = READ_LE_UINT16(monster); monster += 2;
	int16_t var16 = READ_LE_UINT16(monster); monster += 2;
	int16_t monster_score = READ_LE_UINT16(monster); monster += 2;
	int16_t monster_ko_spr_num = READ_LE_UINT16(monster); monster += 2;
	int16_t monster_init_spr_num = READ_LE_UINT16(monster); monster += 2;
	/*int16_t varE  = READ_LE_UINT16(monster);*/ monster += 2;
	int16_t monster_move_spr_num  = READ_LE_UINT16(monster); monster += 2;
	/*int16_t varA  = READ_LE_UINT16(monster);*/ monster += 2;
	int16_t monster_away_spr_num = READ_LE_UINT16(monster); monster += 2;
	int16_t monster_energy = READ_LE_UINT16(monster); monster += 2;
	int16_t monster_direction_flag = READ_LE_UINT16(monster); monster += 2;
	if (g_game.bomb_flag != 0) {
		objm->lifes = 0;
		if (objm->state != MONSTER_STATE_DEAD) {
			objm->state = MONSTER_STATE_KO;
			if (objm->ko_counter < 100) {
				objm->ko_counter = 8000;
			}
		}
	}
	if (objm->lifes != 0 || objm->state < MONSTER_STATE_DEAD) {
		const int16_t w = objm->init_x_pos;
		if (g_game.player_x_pos + 20 > w && g_game.player_x_pos - var18 < w) {
			const int16_t h = objm->init_y_pos;
			if (g_game.player_y_pos + 10 > h && g_game.player_y_pos - 15 < h) {
				if (g_game.object_cave_entrance_mask == 0) {
					g_game.object_cave_entrance_mask = 0;
				}
			}
		}
	}
	if (objm->state == MONSTER_STATE_DEAD && objm->lifes != 0) {

		objm->state = objm->init_state;
		--objm->lifes;
		objm->x_pos = objm->init_x_pos;
		objm->y_pos = objm->init_y_pos;

		objm->direction = 0;
		objm->state_counter = 0;
		objm->ko_counter = 0;
		objm->unk22 = 0;
		g_game.object_updated_flag = 0;
		return;
	}
	const int state = objm->state;
	if (state >= MONSTER_STATE_DEAD) {
		return;
	}
	g_game.object_updated_flag = 0;
	switch (state) {
	case MONSTER_STATE_RESET: {
			if (g_game.player_x_pos <= 2) {
				break;
			}
			if (g_game.player_y_pos + 30 <= objm->y_pos || g_game.player_y_pos - 15 >= objm->y_pos) {
				break;
			}
			objm->state = 1;
			objm->state_counter = 0;
			objm->ko_counter = 0;
			objm->unk22 = 0;
			if (objm->x_pos + 20 < g_game.player_x_pos) {
				objm->direction = 0;
			} else {
				objm->direction = 1;
			}
			Game_AddObject(0, objm->x_pos + 2, objm->y_pos, objm->state_counter + monster_init_spr_num, 0);
		}
		break;
	case 1: {
			Game_AddObject(0, objm->x_pos + 2, objm->y_pos, objm->state_counter + monster_init_spr_num, 0);
			if (k_monsters_enabled != 0) {
				++objm->state_counter;
			}
			if (objm->state_counter == 2) {
				objm->state = 3;
			}
		}
		break;
	case MONSTER_STATE_HEADING_PLAYER: {
			if (k_monsters_enabled != 0) {
				if (objm->direction != 0) {
					objm->x_pos -= 4;
				} else {
					objm->x_pos += 4;
				}
			}
			if (objm->x_pos >= 20 && objm->x_pos <= 275 && Game_GetScreenMask(objm->x_pos + di, objm->y_pos + si) == 0 && Game_GetScreenMask(objm->x_pos, objm->y_pos + si) == 0) {
				if (objm->state_counter == 0) {
					const int16_t rnd = Random_GetNumber() % 20;
					if (rnd == 2 || rnd == 12 || rnd == 16) {
						objm->direction ^= 1;
					}
					if (g_game.player_halo_duration == 0 && g_game.player_y_pos + 10 > objm->y_pos && g_game.player_y_pos - 15 < objm->y_pos) {
						objm->direction = (objm->x_pos + 20 >= g_game.player_x_pos) ? 1 : 0;
					}
				}
			} else {
				if (objm->x_pos < 20) {
					objm->x_pos = 20;
				} else if (objm->x_pos > 275) {
					objm->x_pos = 275;
				}
				/* toggle direction */
				if (objm->direction == 0) {
					objm->direction = 1;
					do {
						if (Game_GetScreenMask(objm->x_pos + di, objm->y_pos + si) == 0) {
							if (Game_GetScreenMask(objm->x_pos, objm->y_pos + si) == 0) {
								break;
							}
						}
						--objm->x_pos;
					} while(1);
				} else {
					objm->direction = 0;
					do {
						if (Game_GetScreenMask(objm->x_pos + di, objm->y_pos + si) == 0) {
							if (Game_GetScreenMask(objm->x_pos, objm->y_pos + si) == 0) {
								break;
							}
						}
						++objm->x_pos;
					} while(1);
				}
			}
			if (k_monsters_enabled != 0) {
				++objm->state_counter;
			}
			objm->state_counter &= 7;
			int var2 = 0;
			if (num != 0 && g_game.fireball_flag == 0 && g_game.player_y_pos + 5 > objm->y_pos && g_game.player_y_pos - 5 < objm->y_pos) {
				if ((objm->direction != 0 && objm->x_pos + 20 > g_game.player_x_pos) || (objm->direction == 0 && objm->x_pos < g_game.player_x_pos)) {
					g_game.fireball_flag = objm->direction + 1;
					g_game.fireball_x_pos = objm->x_pos;
					g_game.fireball_y_pos = objm->y_pos + 4;
					Game_AddObject(0, objm->x_pos, objm->y_pos, monster_move_spr_num + 2, objm->direction);
					var2 = 1;
				}
			}
			if (var2 == 0) {
				Game_AddObject(0, objm->x_pos, objm->y_pos, monster_move_spr_num + READ_LE_UINT16(monster + objm->state_counter * 2), objm->direction);
			}
			if (g_game.player_club_flag == 1) {
				if (g_game.player_facing_left_flag == 0) {
					if (g_game.player_x_pos + dat02 > objm->x_pos && g_game.player_x_pos + 3 < objm->x_pos) {
						if (g_game.player_y_pos + 30 > objm->y_pos && g_game.player_y_pos - 15 < objm->y_pos) {
							objm->state = 4;
							objm->state_counter = 0;
							objm->direction = 1;
							g_game.host.play_sound(SND_MASSUE2);
						}
					}
				} else {
					if (objm->x_pos < g_game.player_x_pos && objm->x_pos + var16 > g_game.player_x_pos) {
						if (g_game.player_y_pos + 30 > objm->y_pos && g_game.player_y_pos - 15 < objm->y_pos) {
							objm->state = 4;
							objm->state_counter = 0;
							objm->direction = 0;
							g_game.host.play_sound(SND_MASSUE2);
						}
					}
				}
			}
			if (objm->state != 3) {
				break;
			}
			if (g_game.player_x_pos + 20 > objm->x_pos && g_game.player_x_pos - var18 < objm->x_pos) {
				if (g_game.player_y_pos + 10 > objm->y_pos && g_game.player_y_pos - 15 < objm->y_pos) {
					if (g_game.object_cave_entrance_mask == 0) {
						Game_HitPlayer(2);
					}
				}
			}
		}
		break;
	case MONSTER_STATE_RUNNING_AWAY: {
			if (k_monsters_enabled != 0) {
				if (objm->direction != 0) {
					objm->x_pos += 8;
				} else {
					objm->x_pos -= 8;
				}
			}
			if (objm->x_pos >= 20 && objm->x_pos <= 275 && Game_GetScreenMask(di + objm->x_pos, si + objm->y_pos) == 0 && Game_GetScreenMask(objm->x_pos, si + objm->y_pos) == 0) {
			} else {
				if (objm->x_pos < 20) {
					objm->x_pos = 20;
				} else if (objm->x_pos > 275) {
					objm->x_pos = 275;
				}
				if (objm->direction == 0) {
					do {
						if (Game_GetScreenMask(objm->x_pos + di, objm->y_pos + si) == 0) {
							if (Game_GetScreenMask(objm->x_pos, objm->y_pos + si) == 0) {
								break;
							}
						}
						++objm->x_pos;
					} while(1);
				} else {
					do {
						if (Game_GetScreenMask(objm->x_pos + di, objm->y_pos + si) == 0) {
							if (Game_GetScreenMask(objm->x_pos, objm->y_pos + si) == 0) {
								break;
							}
						}
						--objm->x_pos;
					} while(1);
				}
			}
			Game_AddObject(0, objm->x_pos, objm->y_pos, monster_away_spr_num, objm->direction);
			if (k_monsters_enabled != 0) {
				++objm->state_counter;
			}
			if (objm->state_counter != 2) {
				break;
			}
			objm->state = 3;
			objm->direction ^= monster_direction_flag;
			if (k_monsters_enabled != 0) {
				++objm->ko_counter;
			}
			if (objm->ko_counter == monster_energy || g_game.player_axe_flag != 0) {
				objm->ko_counter = 40;
				objm->state = MONSTER_STATE_KO;
			}
		}
		break;
	case MONSTER_STATE_KO: {
			const int16_t num = (objm->ko_counter & 1) + monster_ko_spr_num;
			int w, h;
			Game_GetObjectDim(monster_ko_spr_num, &w, &h);
			const int16_t y = objm->y_pos + si - h;
			const int16_t x = objm->x_pos;
			Game_AddObject(0, x, y, num, 0);
			if (objm->ko_counter < 20 && (objm->ko_counter & 1) != 0) {
				const int16_t y = objm->y_pos + si - 8 - h;
				const int16_t x = objm->x_pos + dat00 - 3;
				Game_AddObject(0, x, y, 105, 0); /* DOWN ARROW */
			}
			if (k_monsters_enabled != 0) {
				--objm->ko_counter;
			}
			if (objm->ko_counter == 0) {
				objm->state = 3;
			} else {
				if (objm->x_pos + 20 <= g_game.player_x_pos || objm->x_pos - 10 >= g_game.player_x_pos) {
					break;
				}
				if (objm->y_pos - 30 >= g_game.player_y_pos || objm->y_pos + 23 <= g_game.player_y_pos) {
					break;
				}
				Game_AddScore(objm->x_pos, objm->y_pos, monster_score);
				objm->state = MONSTER_STATE_DEAD;
				++g_game.food;
			}
		}
		break;
	default:
		fprintf(stdout, "Unimplemented monster object state %d\n", state);
		break;
	}
}

void Objects_Update() {
	g_game.object_updated_flag = 1;
	uint16_t *p = g_game.current_objects_dat;
	while (1) {
		const uint16_t num = *p;
		if (num == 0) {
			break;
		}
		switch (num) {
		case OBJ_STAIRS: {
				struct obj_stairs_t *obj = (struct obj_stairs_t *)(p + 1);
				if (g_game.player_x_pos - 8 >= obj->x || g_game.player_x_pos + 8 <= obj->x) {
					break;
				}
				if (g_game.keymask & GAME_KEYCODE_UP) {
					if (g_game.player_y_pos - obj->y_bottom < 3 && g_game.player_climbing_flag != 0) {
						g_game.player_climbing_flag = 0;
						g_game.player_y_pos = obj->y_bottom - 1;
					}
					if (obj->y_top == g_game.player_y_pos) {
						g_game.player_moving_frame_num = 0;
						g_game.player_climbing_flag = 1;
						g_game.player_x_pos = obj->x + 4;
						g_game.player_y_pos -= 4;
					}
				}
				if (g_game.keymask & GAME_KEYCODE_DOWN) {
					if (obj->y_bottom == g_game.player_y_pos) {
						g_game.player_moving_frame_num = 0;
						g_game.player_climbing_flag = 1;
						g_game.player_x_pos = obj->x + 4;
						g_game.player_y_pos += 4;
					}
					if (obj->y_top - g_game.player_y_pos >= 3 && g_game.player_climbing_flag != 0) {
						g_game.player_climbing_flag = 0;
					}
				}
			}
			break;
		case OBJ_PEAK: {
				struct obj2_t *obj = (struct obj2_t *)(p + 1);
				if (obj->x_pos - 21 >= g_game.player_x_pos || obj->x_pos + 5 <= g_game.player_x_pos) {
					break;
				}
				if (g_game.player_y_pos + 27 <= obj->y_pos || obj->y_pos - 16 <= g_game.player_y_pos) {
					break;
				}
				Game_HitPlayer(1);
			}
			break;
		case OBJ_EGG: {
				struct obj3_t *obj = (struct obj3_t *)(p + 1);
				const int16_t counter = obj->counter;
				if (counter == 0) {
					break;
				}
				Game_AddObject(0, obj->x_pos, obj->y_pos, 128 - counter, 0);
				const int16_t h = (g_game.level_num == 5 || g_game.level_num == 7) ? 13 : 9;
				if (obj->y_pos - h != g_game.player_y_pos) {
					break;
				}
				if (g_game.player_club_flag != 1) {
					break;
				}
				if (g_game.player_facing_left_flag != 0) {
					if (!(obj->x_pos + 30 > g_game.player_x_pos && obj->x_pos < g_game.player_x_pos)) {
						break;
					}
				} else {
					if (!(obj->x_pos > g_game.player_x_pos && obj->x_pos - 35 < g_game.player_x_pos)) {
						break;
					}
				}
				--obj->counter;
				if (obj->counter != 0 && g_game.player_axe_flag != 0) {
					--obj->counter;
				}
				if (obj->counter == 0) {
					++g_game.food;
					Game_AddScore(obj->x_pos, obj->y_pos - 4, 50);
				}
			}
			break;
		case OBJ_ROCK: {
				struct obj3_t *obj = (struct obj3_t *)(p + 1);
				const int16_t counter = obj->counter;
				if (counter == 0) {
					break;
				}
				Game_AddObject(0, obj->x_pos, obj->y_pos, 147 - counter, 0);
				if (obj->y_pos - 2 == g_game.player_y_pos && g_game.player_club_flag == 1) {
					if ((g_game.player_facing_left_flag == 0 && g_game.player_x_pos + 40 > obj->x_pos && obj->x_pos > g_game.player_x_pos)
						|| (g_game.player_facing_left_flag != 0 && obj->x_pos + 35 > g_game.player_x_pos && obj->x_pos < g_game.player_x_pos)) {
						--obj->counter;
						if (obj->counter != 0 && g_game.player_axe_flag != 0) {
							--obj->counter;
						}
						g_game.host.play_sound(SND_MASSUE2);
					}
				}
				if (obj->counter != 0) {
					if (obj->y_pos <= g_game.player_y_pos) {
						break;
					}
					if (g_game.player_x_pos + 25 <= obj->x_pos || obj->x_pos + 25 <= g_game.player_x_pos) {
						break;
					}
					if (obj->y_pos - 35 < g_game.player_y_pos) {
						Game_HitPlayer(10);
					}
				}
			}
			break;
		case OBJ_BONUS: {
				struct obj5_t *obj = (struct obj5_t *)(p + 1);
				const uint16_t mask = obj->mask;
				if (mask & 0x80) {
					Game_AddObject(0, g_game.player_x_pos, g_game.bonus_current_y_pos, p1_bonus_spr_num_tbl[mask - 128], 0);
					g_game.bonus_current_dy += 4;
					g_game.bonus_current_y_pos += g_game.bonus_current_dy;
					if (g_game.bonus_current_dy == 20) {
						update_bonus(mask - 128);
						obj->mask = 0;
					}
				}
				const int16_t count = obj->counter;
				if (count >= 70) {
					break;
				}
				++obj->counter;
				const int16_t x = obj->x_pos;
				const int16_t y = obj->y_pos;
				if (count > 15  && count < 21) {
					Game_AddObject(0, x + 4, y + 11, 86 + (count - 16) / 2, 0);
				}
				if (count <= 20) {
					break;
				}
				if (count == 21) {
					obj->mask = Random_GetNumber() % 6;
				}
				if (count < 65) {
					int16_t si = x;
					int16_t di = y;
					switch (count & 3) {
					case 0:
						++si;
						break;
					case 1:
						++di;
						break;
					case 2:
						--si;
						break;
					case 3:
						--di;
						break;
					}
					Game_AddObject(0, si, di, 89, 0);
					if (si + 35 <= g_game.player_x_pos || si - 40 >= g_game.player_x_pos) {
						break;
					}
					if (di - 29 >= g_game.player_y_pos || di + 20 <= g_game.player_y_pos) {
						break;
					}
					if (g_game.player_club_flag == 1) {
						obj->mask = 0x80;
						g_game.bonus_current_dy = -20;
						g_game.bonus_current_y_pos = y + 10;
						obj->counter = 65;
						g_game.host.play_sound(SND_MASSUE2);
					}
				} else {
					Game_AddObject(0, x + 4, y + 11, 88 - (count - 65) / 2, 0);
				}
			}
			break;
		case OBJ_HIDDEN_FOOD: {
				struct obj_food_t *obj = (struct obj_food_t *)(p + 1);
				const uint16_t state = obj->state;
				if (state == 0) {
					break;
				} else if (state == 1) {
					Game_AddObject(0, obj->x_pos + 40, obj->y_pos, obj->spr_num + 61, 0);
					if (g_game.player_x_pos + 20 <= obj->x_pos + 40) {
						break;
					}
					if (g_game.player_x_pos - 20 >= obj->x_pos + 40) {
						break;
					}
					if (g_game.player_y_pos - 10 >= obj->y_pos) {
						break;
					}
					obj->state = 0;
					Game_AddScore(obj->x_pos + 40, obj->y_pos - 4, 100);
					++g_game.food;
				} else {
					if (g_game.player_x_pos + 10 <= obj->x_pos || g_game.player_x_pos - 10 >= obj->x_pos) {
						break;
					}
					if (g_game.player_club_flag != 1) {
						break;
					}
					if (g_game.player_y_pos + 15 <= obj->y_pos || g_game.player_y_pos - 10 >= obj->y_pos) {
						break;
					}
					--obj->state;
					Game_AddObject(0, obj->x_pos + 40, obj->y_pos - 6, obj->spr_num + 61, 0);
					g_game.host.play_sound(SND_MASSUE2);
				}
			}
			break;
		case OBJ_SECRET_FOOD: {
				struct obj_food_t *obj = (struct obj_food_t *)(p + 1);
				if (obj->state != 1) {
					break;
				}
				int16_t x = obj->x_pos;
				int16_t y = obj->y_pos;
				int16_t num = obj->spr_num;
				int w, h;
				Game_GetObjectDim(62 + num, &w, &h);
				y -= h;
				Game_AddObject(0, x, y, 62 + num, 0);
				if (g_game.player_x_pos + 20 <= x || g_game.player_x_pos - 20 >= x) {
					break;
				}
				if (g_game.player_y_pos + 25 <= y || g_game.player_y_pos - 10 >= y) {
					break;
				}
				obj->state = 0;
				Game_AddScore(x, y, p1_secret_score_tbl[num]);
				++g_game.food;
			}
			break;
		case OBJ_BALLOONS: {
				struct obj_balloons_t *obj = (struct obj_balloons_t *)(p + 1);
				if (g_game.player_halo_flag == 0 && g_game.player_level5_flag == 0) {
					Game_AddObject(0, obj->balloon1_x_pos, obj->balloon1_y_pos, obj->balloon1_spr_num, 0);
					Game_AddObject(0, obj->balloon2_x_pos, obj->balloon2_y_pos, obj->balloon2_spr_num, 0);
				}
			}
			break;
		case OBJ_FISH: {
				struct obj_fish_t *obj = (struct obj_fish_t *)(p + 1);
				int16_t x = obj->x_pos;
				int16_t y = obj->y_pos;
				const int16_t state = obj->state;
				if (state == 0) {
					Game_AddObject(0, x, y, 84, 0);
					obj->y_pos = y - obj->y_vel;
					--obj->y_vel;
					if (obj->y_vel == 0) {
						obj->state = 1;
					}
				} else {
					Game_AddObject(0, x, y, 85, 0);
					obj->y_pos = y + obj->y_vel;
					++obj->y_vel;
					if (obj->y_vel == 20) {
						obj->state = 0;
						obj->y_pos = 220;
					}
				}
				x = obj->x_pos;
				y = obj->y_pos;
				if (x - 23 >= g_game.player_x_pos || x + 15 <= g_game.player_x_pos) {
					break;
				}
				if (y - 25 >= g_game.player_y_pos || y + 25 <= g_game.player_y_pos) {
					break;
				}
				Game_HitPlayer(2);
			}
			break;
		case OBJ_GUBBA_GLUB: {
				update_monster(p1_object0x0a_data, (struct obj_monster_t *)(p + 1), 0);
			}
			break;
		case OBJ_BEAR: {
				update_monster(p1_object0x0b_data, (struct obj_monster_t *)(p + 1), 0);
			}
			break;
		case OBJ_PYRO_TAX: {
				update_monster(p1_object0x0c_data, (struct obj_monster_t *)(p + 1), 0);
			}
			break;
		case OBJ_TURTOSAURUS: {
				update_monster(p1_object0x0d_data, (struct obj_monster_t *)(p + 1), 0);
			}
			break;
		case OBJ_CHIMP_AGOGO: {
				struct obj_monkey_t *obj = (struct obj_monkey_t *)(p + 1);
				int16_t x = obj->x_pos;
				int16_t y = obj->y_pos;
				if (obj->state < 4) {
					if (obj->state == 0) {
						Game_AddObject(0, x, y, 94, 0);
						if (obj->throw_flag == 0 && g_game.game_over_flag == 0) {
							obj->state = 1;
						}
					} else if (obj->state < 3) {
						Game_AddObject(0, x, y, 92 + obj->state, 0);
						++obj->state;
						if (obj->state == 3) {
							obj->throw_flag = 1;
							obj->throw_x = x - 12;
							obj->throw_y = y + 16;
							obj->state = 0;
						}
					} else {
						Game_AddObject(0, x, y, 95, 0);
						obj->x_pos += 10;
						if (obj->x_pos > GAME_W) {
							obj->state = 4;
						}
					}
					if (obj->state < 3 && g_game.player_club_flag == 1 && x + 30 > g_game.player_x_pos && x - 36 < g_game.player_x_pos && y + 30 < g_game.player_y_pos && y + 30 > g_game.player_y_pos) {
						obj->state = 3;
						Game_AddScore(x, y, 100);
					}
				}
				if (obj->throw_flag == 0) {
					break;
				}
				x = obj->throw_x;
				y = obj->throw_y;
				Game_AddObject(0, x, y, 96, 0);
				if (x < g_game.player_x_pos + 20 && x > g_game.player_x_pos - 10 && y + 12 > g_game.player_y_pos && y < g_game.player_y_pos + 23) {
					obj->throw_flag = 0;
					Game_HitPlayer(1);
				}
				obj->throw_x -= 12;
				if (obj->throw_x < -70) {
					obj->throw_flag = 0;
				}
			}
			break;
		case OBJ_PTERIYAKI: {
				struct obj_bird_t *obj = (struct obj_bird_t *)(p + 1);
				if (obj->state == 0 && g_game.player_x_pos < 220) {
					obj->state = 1;
					obj->unk2 = 355;
					obj->frame = (obj->frame + 1) & 3;
				}
				int16_t di = obj->unk8[obj->frame];
				if (obj->state == 1 && k_monsters_enabled != 0) {
					obj->unk2 -= 8;
				}
				int16_t si = obj->unk2;
				int16_t spr_num = p1_bird_spr_num_tbl[obj->unk4] + 41;
				Game_AddObject(0, si, di, spr_num, 0);
				if (k_monsters_enabled != 0) {
					obj->unk4 += 1;
				}
				obj->unk4 = (obj->unk4 & 7);
				int16_t x = obj->unk2;
				if (x < -50) {
					obj->state = 0;
				} else {
					if (si - 30 < g_game.player_x_pos && si + 10 > g_game.player_x_pos) {
						if (di - 20 < g_game.player_y_pos && di + 18 > g_game.player_y_pos) {
							Game_HitPlayer(2);
						}
					}
					if (g_game.player_club_flag == 1) {
						if (g_game.player_x_pos + 52 > si && g_game.player_x_pos - 47 < si) {
							if (g_game.player_y_pos + 29 > di && g_game.player_y_pos - 29 < di) {
								if (g_game.player_facing_left_flag == 0) {
									obj->state = 2;
									obj->unk4 = 0;
									g_game.host.play_sound(SND_MASSUE2);
								}
							}
						}
					}
				}
				if (obj->state != 2) {
					break;
				}
				if (k_monsters_enabled != 0) {
					obj->unk2 += 30;
					++obj->unk4;
				}
				if (obj->unk4 == 6) {
					obj->state = 1;
				}
				Game_AddObject(0, obj->unk2, di, 44, 0);
			}
			break;
		case OBJ_PLATFORM: {
				struct obj_platform_t *obj = (struct obj_platform_t *)(p + 1);
				bool flag = 0;
				const int16_t x = obj->x_pos;
				const int16_t y = obj->current_y_pos;
				if (g_game.player_gravity_flag == 0 && x - 20 < g_game.player_x_pos && x + 20 > g_game.player_x_pos && g_game.player_y_pos + 31 > y && g_game.player_y_pos + 5 < y) {
					flag = 1;
					g_game.player_platform_flag = 1;
				}
				if (obj->direction == 0) {
					obj->current_y_pos -= obj->dy;
					if (obj->current_y_pos < obj->y_top) {
						obj->direction = 1;
					}
				} else {
					obj->current_y_pos += obj->dy;
					if (obj->current_y_pos > obj->y_bottom) {
						obj->direction = 0;
					}
				}
				Game_AddObject(0, x, obj->current_y_pos, 1000, 0);
				if (flag != 0) {
					g_game.player_y_pos = obj->current_y_pos - 29;
				}
			}
			break;
		case OBJ_CAVE_ENTRANCE: {
				struct obj3_t *obj = (struct obj3_t *)(p + 1);
				if (obj->x_pos - 8 >= g_game.player_x_pos || obj->x_pos + 8 <= g_game.player_x_pos) {
					break;
				}
				if (obj->y_pos != g_game.player_y_pos) {
					break;
				}
				if ((g_game.keymask & GAME_KEYCODE_DOWN) == 0) {
					break;
				}
				if (g_game.object_cave_entrance_mask != 0) {
					break;
				}
				g_game.player_x_pos = obj->x_pos;
				g_game.object_cave_entrance_mask = (obj->counter << 2) | 1;
			}
			break;
		case OBJ_FIRE: {
				struct obj_fire_t *obj = (struct obj_fire_t *)(p + 1);
				if (k_monsters_enabled != 0) {
					obj->state ^= 1;
				}
				const int16_t x = obj->x_pos;
				const int16_t y = obj->y_pos;
				Game_AddObject(0, x, y, 26 + obj->state, 0);
				if (x - 22 >= g_game.player_x_pos || x + 7 <= g_game.player_x_pos) {
					break;
				}
				if (y - 20 >= g_game.player_y_pos) {
					break;
				}
				Game_HitPlayer(1);
			}
			break;
		case 0x14: {
				struct obj_food_t *obj = (struct obj_food_t *)(p + 1);
				if (obj->state != 1) {
					break;
				}
				int16_t si = obj->x_pos;
				int16_t di = obj->y_pos;
				const int16_t num = obj->spr_num;
				int w, h;
				Game_GetObjectDim(p1_bonus_spr_num_tbl[num], &w, &h);
				di -= h;
				Game_AddObject(0, si, di, p1_bonus_spr_num_tbl[num], 0);
				if (g_game.player_x_pos + 20 <= si || g_game.player_x_pos - 20 >= si) {
					break;
				}
				if (g_game.player_y_pos + 20 <= di || g_game.player_y_pos - 10 >= di) {
					break;
				}
				obj->state = 0;
				update_bonus(num);
			}
			break;
		case OBJ_CAVE_SIGN: {
				if (g_game.cave_exit_x_pos - 8 >= g_game.player_x_pos) {
					break;
				}
				g_game.next_screen_flag = 1;
				g_game.current_screen = p[1];
				g_game.player_exit_from_cave_screen_x_pos = p[2];
				g_game.player_exit_from_cave_screen_y_pos = p[3];
				g_game.player_halo_duration = 39;
			}
			break;
		case OBJ_CAVE_SPIDER: {
				struct obj_cave_spider_t *obj = (struct obj_cave_spider_t *)(p + 1);
				if (obj->counter == 17) {
					obj->counter = 0;
				} else if (k_monsters_enabled != 0) {
					++obj->counter;
				}
				int16_t di = 0;
				if (obj->counter < 2 || obj->counter > 7) {
					Game_AddObject(0, obj->x_pos, obj->y_pos, 119, 0);
					di = (g_game.player_y_vel & 0x7F) <= 20 ? 0 : 30;
				}
				if (obj->counter == 2 || obj->counter == 6 || obj->counter == 7) {
					Game_AddObject(0, obj->x_pos, obj->y_pos + 10, 120, 0);
				}
				if (obj->counter > 2 && obj->counter < 6) {
					Game_AddObject(0, obj->x_pos, obj->y_pos + 16, 121, 0);
				}
				if (obj->x_pos - 23 >= g_game.player_x_pos || obj->x_pos + 16 <= g_game.player_x_pos) {
					break;
				}
				if (obj->y_pos + 25 >= g_game.player_y_pos || obj->y_pos + di + 16 <= g_game.player_y_pos) {
					break;
				}
				Game_HitPlayer(1);
			}
			break;
		case OBJ_CAVE_BAT: {
				struct obj_cave_bat_t *obj = (struct obj_cave_bat_t *)(p + 1);
				if (obj->state & 2) {
					break;
				}
				if (k_monsters_enabled != 0) {
					obj->unk8 += (Random_GetNumber() %  7) - 3;
					obj->unk6 += (Random_GetNumber() % 11) - 5;
				}
				if (obj->unk6 < g_game.cave_exit_y_pos) {
					obj->unk6 = g_game.cave_exit_y_pos;
				}
				if (obj->unk6 > g_game.cave_exit_x_pos - 30){
					obj->unk6 = g_game.cave_exit_x_pos - 30;
				}
				if (obj->unk8 > 140) {
					obj->unk8 = 130;
				}
				const int16_t si = obj->unk6;
				const int16_t di = obj->unk8;
				if (k_monsters_enabled != 0) {
					obj->state ^= 1;
				}
				Game_AddObject(0, si, di, 122 + (obj->state & 1), 0);
				if (g_game.player_x_pos < si && si - 30 < g_game.player_x_pos && g_game.player_y_pos - 4 < di) {
					Game_HitPlayer(1);
				}
				if (g_game.player_y_pos - 10 >= di) {
					break;
				}
				if (g_game.player_club_flag != 1) {
					break;
				}
				if (g_game.player_facing_left_flag == 0 && g_game.player_x_pos < si && si - 35 < g_game.player_x_pos) {
					obj->state |= 2;
					Game_AddScore(si, di, 10);
				}
				if (g_game.player_facing_left_flag != 0 && si + 50 < g_game.player_x_pos && g_game.player_x_pos > si) {
					obj->state |= 2;
					Game_AddScore(si, di, 10);
				}
			}
			break;
		default:
			fprintf(stderr, "Unhandled object 0x%x update\n", num);
			break;
		}
		p += object_size(num) / 2;
	}
}

uint16_t *Objects_ChangeScreen(uint16_t *p, int screen_num) {
	while (screen_num != 0) {
		const uint16_t num = *p;
		if (num == 0) {
			--screen_num;
		}
		p += object_size(num) / sizeof(uint16_t);
	}
	g_game.current_objects_dat = p;
	return p;
}

void Objects_DrawBackground() {
	uint16_t *p = g_game.current_objects_dat;
	while (1) {
		const uint16_t num = *p;
		if (num == 0) {
			break;
		}
		switch (num) {
		case OBJ_PEAK: {
				struct obj2_t *obj = (struct obj2_t *)(p + 1);
				Game_DrawBackgroundObject(obj->x_pos, obj->y_pos, 129);
			}
			break;
		case OBJ_CAVE_SIGN: {
				Game_DrawBackgroundObject(g_game.cave_exit_x_pos - 15, 115, 142);
			}
			break;
		}
		p += object_size(num) / sizeof(uint16_t);
	}
}
