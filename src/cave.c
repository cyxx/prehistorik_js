
#include "game.h"

int Cave_Init(int level, int num) {
	g_game.player_exit_from_cave_screen_x_pos = g_game.player_x_pos;
	g_game.player_exit_from_cave_screen_y_pos = g_game.player_y_pos;
	if (level == 1 || level == 5 || level == 7) {
		g_game.player_restart_x_pos = g_game.player_x_pos = 8;
		g_game.player_restart_y_pos = g_game.player_y_pos = 139;
	}
	if (level == 3) {
		g_game.player_restart_x_pos = g_game.player_x_pos = 86;
		g_game.player_restart_y_pos = g_game.player_y_pos = 159;
	}
	g_game.player_facing_left_flag = 0;
	g_game.object_cave_entrance_mask = 0;
	g_game.player_dead_counter = 0;
	g_game.game_over_flag = 0;
	g_game.player_gravity_flag = 0;
	g_game.next_screen_flag = 0;
	if (level == 1) {
		Game_SetPaletteCaveLevel1();
	}
	Game_SetScreenHeight(199);
	if (level == 1) {
		Game_DrawCaveScreenLevel1(num);
		g_game.cave_exit_x_pos = p1_level1_cave_size_tbl[num] - 8;
		g_game.cave_enter_x_pos = 40;
	} else if (level == 3) {
	} else if (level == 5) {
	} else if (level == 7) {
	}
	Objects_ChangeScreen(p1_level1_cave_tbl, num);
	Objects_DrawBackground();
	g_game.next_screen_flag = 0;
	for (int i = 0; i < MAX_SCORE_BONUSES; ++i) {
		g_game.score_bonuses_tbl[i].counter = 0;
	}
	g_game.fireball_flag = 0;
	g_game.bomb_flag = 0;
	g_game.player_platform_flag = 0;
	return 0;
}

int Cave_DoFrame(int level) {
	Game_UpdateTime();
	Game_DrawPanelScore();
	Game_DrawPanelLifes();
	Game_DrawPanelTime();
	Game_DrawPanelFood();
	Game_DrawPanelEnergy();
	Game_UpdateScoreBonuses();
	g_game.player_platform_flag = 0;
	Objects_Update();
	Game_UpdateFireball();
	player_update_action();
	Game_AddPlayerObject();
	if (g_game.next_screen_flag == 0) {
		player_update_club();
		if (g_game.player_lifes >= 0 && g_game.game_over_flag == 0) {
			player_update_halo();
		}
	}
	Game_DrawObjects();
	if (g_game.game_over_flag != 0 || g_game.player_climbing_flag != 0) return 0;
	if (g_game.player_x_pos < 6) {
		if (level == 1 || level == 5 || level == 7) {
			g_game.next_screen_flag = 1;
		}
	}
	if (level == 3) {
		if (g_game.player_x_pos < 86 && g_game.player_y_pos > 150) {
			g_game.next_screen_flag = 1;
		} else if (g_game.player_x_pos < 85) {
			g_game.player_x_pos = 85;
		}
	}
	if (g_game.player_x_pos > g_game.cave_exit_x_pos) {
		g_game.player_x_pos = g_game.cave_exit_x_pos;
	}
	if (g_game.next_screen_flag) {
		g_game.player_restart_x_pos = g_game.player_x_pos = g_game.player_exit_from_cave_screen_x_pos;
		g_game.player_restart_y_pos = g_game.player_y_pos = g_game.player_exit_from_cave_screen_y_pos;
		g_game.player_gravity_flag = 0;
		return 0;
	}
	return 1;
}
