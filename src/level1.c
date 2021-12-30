
#include "game.h"


static bool _cave_flag;

static int16_t _display_get_ready_counter;

static void level1_reset() {
	_display_get_ready_counter = 17;
	g_game.next_screen_flag = 1;
	g_game.current_screen = k_start_screen_num;
	g_game.player_halo_spr_num = 0;
	g_game.player_halo_duration = 40;
	g_game.player_x_pos = 100;
	g_game.player_y_pos = 66;
	g_game.player_facing_left_flag = 0;
	g_game.player_climbing_flag = 0;
	g_game.player_moving_frame_num = 0;
	g_game.player_gravity_flag = 0;
	g_game.player_y_vel = 20;
	g_game.player_level5_flag = 0;
	g_game.player_halo_flag = 0;
	g_game.player_axe_flag = 0;
	g_game.player_club_flag = 0;
	g_game.player_dead_counter = 0;
	g_game.game_over_flag = 0;
	g_game.score = 0;
	g_game.time = 99;
	g_game.timer_counter = 0;
	g_game.food = 0;
	g_game.player_energy = 10;
}

static void display_get_ready() {
	if (_display_get_ready_counter <= 1 || _display_get_ready_counter >= 18) {
		return;
	}
	Game_AddObject(12, 128, 100, L1SPR_GET_READY_1, 0);
	Game_AddObject(14, 162,  97, L1SPR_GET_READY_2, 0);
	if (k_monsters_enabled != 0) {
		--_display_get_ready_counter;
	}
}

static void reset_objects() {
	g_game.objects_count = 0;
}

static uint8_t changing_screen_flag = 0; /* 1: right, 2: left */

int Level1_Init() {
	g_game.level_num = 1;
	g_game.host.load_file("fond1.pc1", 0);
	g_game.host.load_file("l1spr.mat", 0);
	reset_objects();
	g_game.host.load_file("eleml1.mat", 0);
	g_game.host.load_file("grot1.mat", 0);
	g_game.host.load_file("level1.dur", g_game.level_dur);
	level1_reset();
	Objects_Reset(p1_level1_screen_tbl);
	Objects_Reset(p1_level1_secret_tbl);
	Objects_Reset(p1_level1_cave_tbl);
	return 1;
}

int Level1_DoFrame() {
	if (_cave_flag) {
		if (Cave_DoFrame(1)) {
			return 1;
		}
		_cave_flag = 0;
	}
	if (g_game.next_screen_flag) { /* while (g_game.player_lifes >= 0 && g_game.current_screen != 19) { */
		Game_SetScreenHeight(199);
		if (g_game.current_screen < 100) {
			if (g_game.current_screen != 11) {
				Game_DrawLevelScreen(p1_level1_elem_size_tbl, p1_level1_elem_data_tbl, g_game.current_screen);
			} else {
				Game_DrawLevelScreen(p1_level1_elem_size_tbl, p1_level1_elem_data_tbl, 10);
			}
		} else {
			Game_DrawSecretScreen(g_game.current_screen - 100);
		}
		if (g_game.current_screen < 100) {
			Objects_ChangeScreen(p1_level1_screen_tbl, g_game.current_screen);
		} else {
			Objects_ChangeScreen(p1_level1_secret_tbl, g_game.current_screen - 100);
		}
		if (g_game.current_screen < 100) {
			Game_SetScreenHeight(p1_level1_screen_height_tbl[g_game.current_screen]);
		} else {
			Game_SetScreenHeight(168);
		}
		Objects_DrawBackground();
		g_game.next_screen_flag = 0;
		for (int i = 0; i < MAX_SCORE_BONUSES; ++i) {
			g_game.score_bonuses_tbl[i].counter = 0;
		}
		g_game.fireball_flag = 0;
		g_game.bomb_flag = 0;
		g_game.player_platform_flag = 0;
		g_game.object_cave_entrance_mask = 0;
	}
	Game_UpdateTime();
	Game_DrawPanelScore();
	Game_DrawPanelLifes();
	Game_DrawPanelTime();
	Game_DrawPanelFood();
	Game_DrawPanelEnergy();
	display_get_ready();
	Game_UpdateScoreBonuses();
	g_game.player_platform_flag = 0;
	Objects_Update();
	Game_UpdateFireball();
	if (g_game.current_screen == 100 || g_game.current_screen == 101) {
		if (g_game.player_x_pos < 20 && g_game.player_y_pos == 139) {
			g_game.player_y_pos -= 20;
			g_game.player_y_vel <<= 2;
			if (g_game.player_y_vel > 127) {
				g_game.player_y_vel = 127;
			}
			g_game.player_gravity_flag = 1;
			Game_AddObject(0, 6, 148, L1SPR_TRAMPOLINE, 0);
		} else {
			Game_AddObject(0, 6, 164, L1SPR_TRAMPOLINE, 0);
		}
	}
	if (g_game.current_screen == 9 && g_game.player_halo_flag != 0) {
		g_game.player_x_pos += 3;
		g_game.player_y_pos -= 3;
	}
	if (g_game.current_screen == 12 && g_game.player_halo_flag != 0) {
		if (g_game.player_x_pos < 60) {
			g_game.player_y_pos = 80;
			g_game.player_x_pos += 5;
		} else {
			g_game.player_restart_x_pos = g_game.player_x_pos;
			g_game.player_restart_y_pos = g_game.player_y_pos;
			g_game.player_halo_flag = 0;
			g_game.player_halo_duration = 39;
		}
	}
	player_update_action();
	if (g_game.current_screen == 10 || (g_game.current_screen == 11 && g_game.player_halo_flag != 0)) { /* screen flying over water with ballons */
		player_update_flying_position();
	}
	if (changing_screen_flag == 0) {
		add_player_object();
	}
	if (g_game.next_screen_flag == 0) {
		player_update_club();
		if (g_game.player_lifes >= 0 && g_game.game_over_flag == 0 && changing_screen_flag == 0) {
			player_update_halo();
		}
		if (g_game.current_screen == 18 && g_game.food < 45 && !k_no_food) {
			Game_AddObject(0, 110, 100, L1SPR_NOT_ENOUGH_FOOD_1, 0);
			Game_AddObject(0, 173, 100, L1SPR_NOT_ENOUGH_FOOD_2, 0);
		}
	}
	Game_DrawObjects();
	changing_screen_flag = 0;
	if (g_game.game_over_flag != 0) {
		return 1;
	}
	if (g_game.player_climbing_flag != 0) {
		return 1;
	}
	if (g_game.player_x_pos < 0) {
		g_game.player_x_pos = 0;
	} else if (g_game.player_x_pos > 300) {
		g_game.player_x_pos = 300;
	}
	if (g_game.player_y_pos > 180 && g_game.game_over_flag == 0) {
		g_game.game_over_flag = 1;
		g_game.player_dead_counter = 1;
	}
	if (g_game.current_screen == 5 && g_game.player_x_pos < 105 && g_game.player_y_pos > 155) {
		g_game.player_y_pos = 10;
		g_game.next_screen_flag = 1;
		g_game.current_screen = 100; /* secret area #1 */
		g_game.game_over_flag = 0;
	}
	if (g_game.current_screen == 14 && g_game.player_x_pos < 105 && g_game.player_y_pos > 155) {
		g_game.player_y_pos = 10;
		g_game.next_screen_flag = 1;
		g_game.current_screen = 101; /* secret area #2 */
		g_game.game_over_flag = 0;
	}
	if (g_game.current_screen < 100) {
		if (g_game.player_x_pos < 6 && g_game.player_halo_flag == 0 && g_game.current_screen != 0) {
			--g_game.current_screen;
			g_game.player_x_pos = 285;
			g_game.next_screen_flag = 1;
			changing_screen_flag = 2;
		}
		if (g_game.current_screen == 9 && g_game.player_x_pos > 260 && g_game.player_halo_flag == 0) {
			g_game.player_x_pos += 2;
			g_game.player_halo_flag = 1;
		}
		if (g_game.current_screen == 9 && g_game.player_x_pos >= 300 && g_game.player_halo_flag != 0) {
			++g_game.current_screen;
			g_game.player_x_pos = 6;
			g_game.next_screen_flag = 1;
			changing_screen_flag = 1;
		}
		if (g_game.player_x_pos > 295 && g_game.current_screen != 9 && g_game.current_screen != 18) {
			++g_game.current_screen;
			g_game.player_x_pos = 6;
			g_game.next_screen_flag = 1;
			changing_screen_flag = 1;
		}
		if (g_game.player_x_pos > 260 && g_game.current_screen == 18 && (k_no_food || g_game.food > 44)) {
			++g_game.current_screen;
			g_game.player_x_pos = 6;
			g_game.next_screen_flag = 1;
		}
	}
	if (g_game.current_screen == 100 && g_game.next_screen_flag == 0 && g_game.player_y_pos < 30 && g_game.player_gravity_flag != 0) {
		/* exit secret area #1 */
		g_game.current_screen = 5;
		g_game.next_screen_flag = 1;
		g_game.player_y_pos = 70;
		g_game.player_x_pos = 100;
		g_game.player_facing_left_flag = 0;
		g_game.player_gravity_flag = 0;
		if (g_game.player_y_vel < 127) {
			g_game.player_y_vel >>= 2;
		} else {
			g_game.player_y_vel = 34;
		}
	}
	if (g_game.current_screen == 101 && g_game.next_screen_flag == 0 && g_game.player_y_pos < 30 && g_game.player_gravity_flag != 0) {
		/* exit secret area #2 */
		g_game.current_screen = 14;
		g_game.next_screen_flag = 1;
		g_game.player_y_pos = 100;
		g_game.player_x_pos = 80;
		g_game.player_facing_left_flag = 0;
		g_game.player_gravity_flag = 0;
		g_game.player_y_vel >>= 2;
	}
	if ((g_game.object_cave_entrance_mask & 3) == 3) {
		g_game.next_screen_flag = 1;
		_cave_flag = 1;
		const int num = g_game.object_cave_entrance_mask >> 2;
		Cave_Init(1, num);
	}
	if (g_game.current_screen == 19) {
		return 0;
	}
	return 1;
}
