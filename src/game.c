
#include "game.h"

struct game_t g_game;

static void restart_level() {
	g_game.current_score = 0;
	g_game.player_lifes = 3;
	g_game.host.clear_spritesheets();
	Level1_Init();
}

int Game_Init(struct host_intf_t *host_intf) {
	g_game.host = *host_intf;

	g_game.host.load_file("charset1.mat", 0);
	Random_Reset();

	restart_level();
	return 0;
}

int Game_Fini() {
	g_game.host.clear_spritesheets();
	return 0;
}

int Game_UpdateInput(int key, int down) {
	if (down) {
		g_game.keymask |= key;
	} else {
		g_game.keymask &= ~key;
	}
	return 0;
}

int Game_DoFrame() {
	if (!Level1_DoFrame() || g_game.player_lifes < 0 || g_game.time == 0) {
		restart_level();
	}
	return 0;
}

void Game_AddObject(int unk, int x_pos, int y_pos, int spr_num, int flag) {
	assert(g_game.objects_count < MAX_OBJECTS);
	struct object_t *obj = &g_game.objects_tbl[g_game.objects_count];
	obj->state = 1;
	obj->x_pos = x_pos;
	obj->y_pos = y_pos;
	obj->spr_num = spr_num;
	obj->xflip = flag;
	++g_game.objects_count;
}

void Game_GetObjectDim(int spr_num, int *w, int *h) {
	assert(spr_num != 0);
	g_game.host.get_sprite_dim(MAT_LSPR, spr_num - 1, w, h);
}

void Game_AddScore(int x_pos, int y_pos, int score) {
	g_game.current_score += score;
	int num = 0;
	for (int i = 0; i < 5; ++i) {
		if (p1_score_tbl[i] == score) {
			num = i + 1;
			break;
		}
	}
	if (num == 0) {
		return;
	}
	g_game.host.play_sound(SND_BONUS);
	for (int i = 0; i < MAX_SCORE_BONUSES; ++i) {
		struct score_bonus_t *bonus = &g_game.score_bonuses_tbl[i];
		if (bonus->counter == 0) {
			bonus->counter = 10;
			bonus->x_pos = x_pos;
			bonus->y_pos = y_pos;
			bonus->spr_num = 33 + num;
			break;
		}
	}
}

void Game_UpdateScoreBonuses() {
	for (int i = 0; i < MAX_SCORE_BONUSES; ++i) {
		struct score_bonus_t *bonus = &g_game.score_bonuses_tbl[i];
		if (bonus->counter != 0) {
			--bonus->counter;
			Game_AddObject(0, bonus->x_pos, bonus->y_pos, bonus->spr_num, 0);
			bonus->y_pos -= 4;
		}
	}
}

void Game_DrawObjects() {
	for (int i = 0; i < g_game.objects_count; ++i) {
		struct object_t *obj = &g_game.objects_tbl[i];
		assert(obj->spr_num != 0);
		if (obj->spr_num == 1000) {
			g_game.host.add_sprite(MAT_ELEM, 0, obj->x_pos,      obj->y_pos, SPR_DST_FOREGROUND, 0);
			g_game.host.add_sprite(MAT_ELEM, 2, obj->x_pos + 16, obj->y_pos, SPR_DST_FOREGROUND, 0);
			continue;
		}
		g_game.host.add_sprite(MAT_LSPR, obj->spr_num - 1, obj->x_pos, obj->y_pos, SPR_DST_FOREGROUND, obj->xflip);
	}
	g_game.objects_count = 0;
}

void Game_DrawString(int x_pos, int y_pos, const char *s, uint8_t color_fg, uint8_t color_bg, int flag) {
	for (; *s; ++s) {
		const uint8_t num = ((uint8_t)*s) - 0x20;
		assert(num < 96);
		g_game.host.add_sprite(MAT_CHAR, num, x_pos, y_pos - 8, SPR_DST_FOREGROUND, flag);
		x_pos += 8;
	}
}

void Game_DrawBackgroundObject(int x, int y, int num) {
	g_game.host.add_sprite(MAT_LSPR, num, x, y, SPR_DST_BACKGROUND, 0);
}

void Game_DrawPanelScore() {
	if (g_game.current_score > 999999) {
		g_game.current_score -= 1000000;
	}
	const uint8_t color_fg = 15;
	const uint8_t color_bg = (g_game.level_num == 1) ? 4 : 0;
	char buf[16];
	snprintf(buf, sizeof(buf), "%05d", g_game.current_score);
	Game_DrawString(48, 8, buf, color_fg, color_bg, 0);
	if (g_game.score * 10000 <= g_game.current_score) {
		++g_game.score;
		++g_game.player_lifes;
		if (g_game.player_lifes > 99) {
			g_game.player_lifes = 99;
		}
	}
}

void Game_DrawPanelLifes() {
	const uint8_t color_fg = 15;
	const uint8_t color_bg = (g_game.level_num == 1) ? 4 : 0;
	char buf[16];
	snprintf(buf, sizeof(buf), "%02d", g_game.player_lifes);
	Game_DrawString(232, 8, buf, color_fg, color_bg, 0);
}

void Game_DrawPanelTime() {
	const uint8_t color_fg = (g_game.time < 11) ? 5 : 15;
	const uint8_t color_bg = (g_game.level_num == 1) ? 4 : 0;
	char buf[16];
	snprintf(buf, sizeof(buf), "%02d", g_game.time);
	Game_DrawString(296, 8, buf, color_fg, color_bg, 0);
}

void Game_DrawPanelFood() {
	if (g_game.food > 46) {
		g_game.food = 46;
	}
	g_game.host.add_rect(128, 0, g_game.food, 5, p1_level1_palette_colors[5]);
	g_game.host.add_rect(128, 0,  0, 6, p1_level1_palette_colors[15]);
	g_game.host.add_rect(174, 0,  0, 5, p1_level1_palette_colors[15]);
}

void Game_DrawPanelEnergy() {
	char buf[16];
	snprintf(buf, sizeof(buf), "ENERGY %2d", g_game.player_energy);
	Game_DrawString(4, 18, buf, 15, 0, 0);
}

void Game_UpdateTime() {
	const int16_t count = g_game.timer_counter;
	++g_game.timer_counter;
	if (count > 60) {
		if (k_no_timeout) {
		} else if (g_game.time != 0) {
			--g_game.time;
		} else if (g_game.game_over_flag == 0) {
			g_game.player_halo_duration = 0;
			g_game.game_over_flag = 1;
			g_game.player_dead_counter = 1;
		}
		g_game.timer_counter = 0;
	}
}

int Game_GetScreenMask(int x_pos, int y_pos) {
	if (x_pos > GAME_W - 1) {
		x_pos = GAME_W - 1;
	}
	if (y_pos > GAME_H - 1) {
		y_pos = GAME_H - 1;
	}
	const int offset = (y_pos << 3) + (y_pos << 5) + (x_pos >> 3);
	const int mask = 0x80 >> (x_pos & 7);
	return (g_game.tiles_mask_buffer[offset] & mask) == 0 ? 1 : 0;
}

static void set_screen_mask(int x_pos, int y_pos) {
	if (y_pos < 0 || y_pos >= GAME_H) {
		return;
	}
	const int offset = (x_pos >> 3) + (y_pos * 40);
	const int mask = 0x80 >> (x_pos & 7);
	g_game.tiles_mask_buffer[offset] |= mask;
}

struct tile_mask_t {
	struct {
		int16_t start_x;
		int16_t start_y;
		int16_t len;
	} a[4];
} __attribute__((packed));

void Game_UpdateScreenMask(int tile_num, int x_pos, int y_pos) {
	struct tile_mask_t *tile = ((struct tile_mask_t *)g_game.level_dur) + tile_num;
	for (int num = 0; tile->a[num].start_x != -1; ++num) {
		int16_t si = tile->a[num].start_x + x_pos;
		int16_t di = tile->a[num].start_y + y_pos;
		const int16_t len = tile->a[num].len;
		for (int i = 0; i < len; ++i) {
			if (si >= 0 && si < GAME_W) {
				set_screen_mask(si, di);
			}
			++si;
		}
	}
}

void Game_SetScreenHeight(int height) {
	g_game.screen_height = height;
	g_game.host.set_clipping_rect(SPR_DST_FOREGROUND, 0, 0, GAME_W, height);
}

void Game_DrawLevelScreen(const uint16_t *size, const uint16_t *tiles, int screen_num) {
	memset(g_game.tiles_mask_buffer, 0, sizeof(g_game.tiles_mask_buffer));
	g_game.host.clear_sprites(SPR_DST_BACKGROUND);
	g_game.host.fill_background_rect(0, 0, GAME_W - 1, GAME_H - 1, 0x00000000);
	while (1) {
		for (int i = 0; i < *size + 1; ++i) {
			int16_t x = *tiles++;
			int16_t y = *tiles++;
			uint16_t num = *tiles++;
			assert(num != 0);
			if (screen_num == 0) {
				--num;
				x = (x >> 4) * 16;
				g_game.host.add_sprite(MAT_ELEM, num, x, y, SPR_DST_BACKGROUND, 0);
				Game_UpdateScreenMask(num, x, y);
			}
		}
		if (screen_num == 0) {
			if (0) {
				for (int y = 0; y < GAME_H; ++y) {
					fprintf(stdout, "Y %3d: ", y);
					for (int x = 0; x < GAME_W / 8; ++x) {
						fprintf(stdout, "%02x ", g_game.tiles_mask_buffer[y * (GAME_W / 8) + x]);
					}
					fprintf(stdout, "\n");
				}
			}
			break;
		}
		--screen_num;
		++size;
	}
}

void Game_DrawSecretScreen(int num) {
		Game_SetPaletteScreenArea();
	memset(g_game.tiles_mask_buffer, 0, sizeof(g_game.tiles_mask_buffer));
	g_game.host.clear_sprites(SPR_DST_BACKGROUND);
	for (int x = 0; x < 10000; x += 48) {
		g_game.host.add_sprite(MAT_ELEM, 1, x, 168, SPR_DST_BACKGROUND, 0);
		Game_UpdateScreenMask(1, x, 168);
		const int16_t bx =  Random_GetNumber() % 320;
		const int16_t by = (Random_GetNumber() % 134) + 10;
		const int16_t num = (Random_GetNumber() % 2) + 17;
		g_game.host.add_sprite(MAT_ELEM, num, bx, by, SPR_DST_BACKGROUND, 0);
	}
}

void Game_DrawCaveScreenLevel1(int num) {
	g_game.host.fill_background_rect(0, 9, GAME_W - 1, 190, 0xFF000000);
	memset(g_game.tiles_mask_buffer, 0, sizeof(g_game.tiles_mask_buffer));
	g_game.host.clear_sprites(SPR_DST_BACKGROUND);
	int x = -32;
	while (x < p1_level1_cave_size_tbl[num]) {
		g_game.host.add_sprite(MAT_GROT, 1, x, 50, SPR_DST_BACKGROUND, 0);
		x += 64;
	}
	g_game.host.add_sprite(MAT_GROT, 0, x, 50, SPR_DST_BACKGROUND, 0);
	for (int x = 0; x < GAME_W; ++x) {
		set_screen_mask(x, 168);
	}
}

void Game_HitPlayer(int energy) {
	if (!k_player_no_hit && g_game.player_halo_duration == 0 && g_game.game_over_flag == 0) {
		if (energy < g_game.player_energy) {
			g_game.player_energy -= energy;
			g_game.player_halo_duration = 19;
		} else if (g_game.object_cave_entrance_mask == 0) {
			g_game.player_energy = 0;
			g_game.player_dead_counter = 1;
			g_game.game_over_flag = 1;
		}
	}
}

void player_update_action() {
	g_game.player_action_key_flag = (g_game.keymask & GAME_KEYCODE_ACTION) != 0;
	if (g_game.player_action_key_flag != 0) {
		if (g_game.player_action_state_flag != 0) {
			g_game.player_action_key_flag = 0;
		} else if (g_game.player_club_flag == 0 && g_game.game_over_flag == 0 && g_game.player_climbing_flag == 0 && g_game.player_halo_flag == 0 && g_game.player_level5_flag == 0) {
			g_game.player_action_state_flag = 1;
			g_game.player_club_flag = 2;
		}
	} else {
		g_game.player_action_state_flag = 0;
	}
}

void player_update_club() {
	player_update_action();
	if (g_game.player_lifes < 0) {
		return;
	}
	if (g_game.game_over_flag != 0 || g_game.object_cave_entrance_mask != 0) {
		g_game.player_club_flag = 0;
		return;
	}
	if (g_game.player_club_flag != 0) {
		const int16_t num = (2 - g_game.player_club_flag) * 3;
		const uint16_t *tbl = ((g_game.player_axe_flag != 0) ? p1_player_axe_spr_num_tbl : p1_player_club_spr_num_tbl) + num;
		int16_t dx_pos = tbl[0];
		int16_t dy_pos = tbl[1];
		const int16_t spr_num = tbl[2];
		if (g_game.player_facing_left_flag) {
			dx_pos = -dx_pos;
		}
		Game_AddObject(0, g_game.player_x_pos + dx_pos, g_game.player_y_pos + dy_pos, spr_num, g_game.player_facing_left_flag);
		--g_game.player_club_flag;
	}

}

void player_update_halo() {
	const int dx_pos = (g_game.player_climbing_flag != 0) ? 4 : 0;
	if (g_game.player_halo_duration != 0 && g_game.player_halo_duration < 100) {
		if (k_monsters_enabled != 0) {
			--g_game.player_halo_duration;
			g_game.player_halo_spr_num = 1 - g_game.player_halo_spr_num;
		}
		if (g_game.player_halo_duration > 15 || g_game.player_halo_spr_num != 0) {
			if (g_game.player_level5_flag == 0) {
				Game_AddObject(13, g_game.player_x_pos - 5 - dx_pos, g_game.player_y_pos - 11, L1SPR_PLAYER_HALO + g_game.player_halo_spr_num, 0);
			} else {
				Game_AddObject(0, g_game.player_x_pos + 6, g_game.player_y_pos + 10, 141, 0);
			}
		}
	}
}

void player_update_flying_position() {
	if (g_game.game_over_flag != 0) {
		return;
	}
	g_game.player_y_pos += 2;
	if ((g_game.keymask & GAME_KEYCODE_LEFT) != 0 && g_game.player_x_pos > 4) {
		g_game.player_x_pos -= 5;
	}
	if (g_game.keymask & GAME_KEYCODE_RIGHT) {
		g_game.player_x_pos += 5;
	}
	if ((g_game.keymask & GAME_KEYCODE_UP) != 0 && g_game.player_y_pos > 30) {
		g_game.player_y_pos -= 8;
	}
	if (g_game.keymask & GAME_KEYCODE_DOWN) {
		g_game.player_y_pos += 5;
	}
	g_game.player_restart_x_pos = g_game.player_x_pos;
	g_game.player_restart_y_pos = 100;
	g_game.player_restart_screen = g_game.current_screen;
}

static void add_player_death_animation() {
	if (g_game.game_over_flag == 1) {
		g_game.player_dead_x_pos = g_game.player_x_pos;
		g_game.player_dead_y_pos = g_game.player_y_pos;
		if (g_game.player_halo_flag != 0 || g_game.player_level5_flag != 0) {
			g_game.balloon_x_pos = g_game.player_x_pos;
			g_game.balloon_y_pos = g_game.player_y_pos - 30;
		}
	}
	if (g_game.player_halo_flag != 0 || g_game.player_level5_flag != 0) {
		g_game.balloon_y_pos -= 8;
		if (g_game.player_level5_flag == 0) {
			Game_AddObject(0, g_game.balloon_x_pos, g_game.balloon_y_pos, L1SPR_BALLOONS, 0);
		} else {
			Game_AddObject(0, g_game.balloon_x_pos, g_game.balloon_y_pos, L1SPR_BALLOONS, 0);
			Game_AddObject(0, g_game.balloon_x_pos + 21, g_game.balloon_y_pos, 125, 0);
		}
	}
	if (g_game.game_over_flag < 9) {
		Game_AddObject(1, g_game.player_x_pos - 5, g_game.player_y_pos, p1_player_death_spr_num_tbl[g_game.game_over_flag - 1], 0);
		++g_game.game_over_flag;
		return;
	}
	if (g_game.player_dead_counter != 0) {
		const int16_t spr_num = (g_game.player_dead_counter & 1) + L1SPR_PLAYER_DEAD_1;
		++g_game.player_dead_counter;
		g_game.player_dead_y_pos -= 4;
		Game_AddObject(1, g_game.player_dead_x_pos, g_game.player_dead_y_pos, spr_num, 0);
		if (g_game.player_action_key_flag != 0) {
			g_game.player_dead_y_pos = -1;
		}
		if (g_game.player_dead_y_pos > 0) {
			return;
		}
	}
	g_game.player_dead_counter = 0;
	g_game.player_x_pos = g_game.player_restart_x_pos;
	g_game.player_y_pos = g_game.player_restart_y_pos;
	if (g_game.player_x_pos < 6) {
		g_game.player_x_pos = 6;
	} else if (g_game.player_x_pos > 285) {
		g_game.player_x_pos = 285;
	}
	g_game.player_halo_duration = 39;
	g_game.player_energy = 10;
	g_game.player_facing_left_flag = 0;
	g_game.player_moving_frame_num = 0;
	g_game.player_gravity_flag = 0;
	g_game.player_y_vel = 20;
	g_game.player_climbing_flag = 0;
	g_game.player_axe_flag = 0;
	g_game.player_club_flag = 0;
	g_game.player_dead_counter = 0;
	g_game.game_over_flag = 0;
	--g_game.player_lifes;
	if (g_game.player_lifes >= 0) {
	}
	if (g_game.time == 0) {
		g_game.time = 50;
	}
	if (g_game.time < 11) {
		g_game.time += 10;
	}
	g_game.timer_counter = 0;
	if (g_game.player_restart_screen != g_game.current_screen) {
		g_game.current_screen = g_game.player_restart_screen;
		g_game.next_screen_flag = 1;
	}
}

void Game_AddPlayerObject() {
	int16_t di = 0;
	if (g_game.player_lifes < 0) {
		return;
	}
	if (g_game.object_cave_entrance_mask & 3) { /* entering cave */
		Game_AddObject(0, g_game.player_x_pos + 4, g_game.player_y_pos, 44 + (g_game.object_cave_entrance_mask & 3), 0);
		if ((g_game.object_cave_entrance_mask & 3) != 3) {
			++g_game.object_cave_entrance_mask;
		}
		return;
	}
	if (g_game.game_over_flag != 0) {
		add_player_death_animation();
		return;
	}
	if (g_game.player_climbing_flag != 0) {
		g_game.player_gravity_flag = 0;
		if (g_game.keymask & GAME_KEYCODE_UP) {
			g_game.player_y_pos -= 4;
			g_game.player_moving_frame_num ^= 1;
		}
		if (g_game.keymask & GAME_KEYCODE_DOWN) {
			g_game.player_y_pos += 4;
			g_game.player_moving_frame_num ^= 1;
		}
		const int spr_num = 16 + (g_game.player_moving_frame_num & 1); /* climbing stairs */
		Game_AddObject(0, g_game.player_x_pos, g_game.player_y_pos, spr_num, 0);
		return;
	}
	if (g_game.player_halo_flag != 0) {
		Game_AddObject(0, g_game.player_x_pos, g_game.player_y_pos - 30, L1SPR_PLAYER_WITH_BALLOONS, 0);
		return;
	}
	if (g_game.player_level5_flag != 0) {
		Game_AddObject(0, g_game.player_x_pos, g_game.player_y_pos, L1SPR_PLAYER_WITH_BALLOONS, 0);
		Game_AddObject(0, g_game.player_x_pos + 21, g_game.player_y_pos, 125, 0);
		return;
	}
	int16_t spr_num = 1;
	g_game.player_dy = 0;
	g_game.player_dx = 0;
	int16_t si = 0;
	if (g_game.player_gravity_flag == 0) {
		if (Game_GetScreenMask(g_game.player_x_pos + 8, g_game.player_y_pos + 29) != 0) {
			if (Game_GetScreenMask(g_game.player_x_pos + 23, g_game.player_y_pos + 29) != 0) {
				if (g_game.player_platform_flag == 0) {
					di = 1;
					spr_num = 4;
					while (1) {
						++g_game.player_y_pos;
						++si;
						if (si >= 10) {
							break;
						}
						if (Game_GetScreenMask(g_game.player_x_pos + 8, g_game.player_y_pos + 29) == 0) {
							break;
						}
						if (Game_GetScreenMask(g_game.player_x_pos + 23, g_game.player_y_pos + 29) == 0) {
							break;
						}
					}
				}
			}
		}
	}
	if (g_game.player_gravity_flag == 0 && di == 0 && g_game.game_over_flag == 0 && g_game.player_platform_flag == 0) {
		g_game.player_restart_x_pos = g_game.player_x_pos;
		g_game.player_restart_y_pos = g_game.player_y_pos;
		g_game.player_restart_screen = g_game.current_screen;
	}
	if ((g_game.keymask & GAME_KEYCODE_LEFT) != 0 && g_game.player_club_flag == 0) {
		si = 5;
		if (di == 0 && g_game.player_gravity_flag == 0) {
			++g_game.player_moving_frame_num;
			if (g_game.player_moving_frame_num > si) {
				g_game.player_moving_frame_num = 0;
			}
			spr_num = p1_player_walk_spr_num_tbl[g_game.player_moving_frame_num];
			si = p1_player_walk_x_vel_tbl[g_game.player_moving_frame_num];
			if (g_game.player_facing_left_flag == 1) {
				g_game.player_dx = -(int16_t)p1_player_walk_dx_tbl[g_game.player_moving_frame_num];
			}
		}
		if (g_game.player_facing_left_flag != 1 && di == 0 && g_game.player_gravity_flag == 0) {
			spr_num = L1SPR_PLAYER_FRONT;
		}
		g_game.player_facing_left_flag = 1;
		g_game.player_x_pos -= si;
		if (g_game.player_gravity_flag != 0) {
			g_game.player_x_pos -= 2;
		}
	}
	if ((g_game.keymask & GAME_KEYCODE_RIGHT) != 0 && g_game.player_club_flag == 0) {
		si = 5;
		if (di == 0 && g_game.player_gravity_flag == 0) {
			++g_game.player_moving_frame_num;
			if (g_game.player_moving_frame_num > si) {
				g_game.player_moving_frame_num = 0;
			}
			spr_num = p1_player_walk_spr_num_tbl[g_game.player_moving_frame_num];
			si = p1_player_walk_x_vel_tbl[g_game.player_moving_frame_num];
			if (g_game.player_facing_left_flag == 0) {
				g_game.player_dx = (int16_t)p1_player_walk_dx_tbl[g_game.player_moving_frame_num];
			}
		}
		if (g_game.player_facing_left_flag != 0 && di == 0 && g_game.player_gravity_flag == 0) {
			spr_num = L1SPR_PLAYER_FRONT;
		}
		g_game.player_facing_left_flag = 0;
		g_game.player_x_pos += si;
		if (g_game.player_gravity_flag != 0) {
			g_game.player_x_pos += 2;
		}
	}
	if (g_game.player_gravity_flag != 0) {
		si = 0;
		do {
			++g_game.player_gravity_flag;
			++si;
			if (g_game.player_gravity_flag == 2 && (g_game.player_y_vel & 0x7F) > 20) {
				g_game.host.play_sound(SND_RESSORT);
			}
			if ((g_game.player_y_vel & 0x7F) - 8 < g_game.player_gravity_flag && (g_game.player_y_vel & 0x7F) > g_game.player_gravity_flag) {
				--g_game.player_y_pos;
			}
			if ((g_game.player_y_vel & 0x7F) - 6 > g_game.player_gravity_flag) {
				g_game.player_y_pos -= 2;
			}
			if ((g_game.player_y_vel & 0x7F) < g_game.player_gravity_flag) {
				g_game.player_gravity_flag = 0;
				di = 1;
				if (g_game.player_y_vel & 0x80) {
					g_game.player_y_vel = g_game.object_player_y_vel;
				}
			}
		} while (g_game.player_gravity_flag != 0 && si < 4);
		spr_num = 4;
	}
	if (di == 0 && g_game.player_gravity_flag == 0 && (g_game.keymask & GAME_KEYCODE_JUMP) != 0) {
		g_game.player_gravity_flag = 1;
	}
	if (g_game.player_club_flag != 0) {
		si = 2 - g_game.player_club_flag;
		if (g_game.player_gravity_flag != 0 || di != 0) {
			si += 2;
		}
		spr_num = p1_player_hitting_spr_num_tbl[si * 2];
		g_game.player_dy = p1_player_hitting_spr_num_tbl[si * 2 + 1];
		if (g_game.keymask & GAME_KEYCODE_LEFT) {
			g_game.player_facing_left_flag = 1;
			g_game.player_x_pos -= 5;
		}
		if (g_game.keymask & GAME_KEYCODE_RIGHT) {
			g_game.player_facing_left_flag = 0;
			g_game.player_x_pos += 5;
		}
	}
	Game_AddObject(1, g_game.player_x_pos + g_game.player_dx, g_game.player_y_pos + g_game.player_dy, spr_num, g_game.player_facing_left_flag);
}

void Game_UpdateFireball() {
	if (g_game.fireball_flag == 0) {
		return;
	}
	if (g_game.fireball_flag == 1) {
		g_game.fireball_x_pos += 8;
		if (g_game.fireball_x_pos > GAME_W) {
			g_game.fireball_flag = 0;
			return;
		}
	} else {
		g_game.fireball_x_pos -= 8;
		if (g_game.fireball_x_pos < 0)  {
			g_game.fireball_flag = 0;
			return;
		}
	}
	Game_AddObject(0, g_game.fireball_x_pos, g_game.fireball_y_pos, L1SPR_FIREBALL, g_game.fireball_flag - 1);
	if (g_game.player_x_pos + 25 <= g_game.fireball_x_pos || g_game.player_x_pos - 10 >= g_game.fireball_x_pos) {
		return;
	}
	if (g_game.player_y_pos - 13 >= g_game.fireball_y_pos || g_game.player_y_pos + 16 <= g_game.fireball_y_pos) {
		return;
	}
	if (g_game.object_cave_entrance_mask != 0) {
		return;
	}
	Game_HitPlayer(1);
}

static void color_difference(int num, const uint32_t src, const uint8_t *dst) {
	const uint8_t src_r = src >> 16;
	const uint8_t src_g = src >> 8;
	const uint8_t src_b = src;
	const int diff_r = abs(src_r - dst[0] * 8);
	const int diff_g = abs(src_g - dst[1] * 8);
	const int diff_b = abs(src_b - dst[2] * 8);
	fprintf(stdout, "palette %2d: diff r:%d g:%d b:%d\n", num, diff_r, diff_g, diff_b);
}

void Game_SetPaletteCaveLevel1() {
	if (0) {
		const uint8_t *p = p1_level1_cave_palette_data;
		for (int i = 0; i < 16; ++i, p += 3) {
			color_difference(i, p1_level1_palette_colors[i], p);
		}
	}
}

void Game_SetPaletteScreenArea() {
	if (0) {
		const uint8_t *p = p1_secret_palette_data;
		for (int i = 0; i < 16; ++i, p += 3) {
			color_difference(i, p1_level1_palette_colors[i], p);
		}
	}
}

void Game_SetPaletteBomb() {
}
