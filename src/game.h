
#ifndef GAME_H__
#define GAME_H__

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define GAME_W 320
#define GAME_H 200

static inline uint16_t READ_LE_UINT16(const uint8_t *p) {
	return p[0] | (p[1] << 8);
}

static inline void WRITE_LE_UINT16(uint8_t *p, uint16_t value) {
	p[0] = value & 255;
	p[1] = value >> 8;
}

enum {
	MAT_CHAR,
	MAT_LSPR,
	MAT_ELEM,
	MAT_GROT,
};

enum {
	SPR_DST_BACKGROUND = 1 << 0,
	SPR_DST_FOREGROUND = 1 << 1,
};

struct host_intf_t {
	int (*load_file)(const char *name, uint8_t *dst);
	void (*clear_spritesheets)();
	void (*clear_sprites)(int dst_mask);
	void (*add_sprite)(int file_num, int spr_num, int x, int y, int dst_mask, int xflip);
	void (*get_sprite_dim)(int file_num, int spr_num, int *w, int *h);
	void (*set_clipping_rect)(int dst_mask, int x, int y, int w, int h);
	void (*fill_background_rect)(int x, int y, int w, int h, uint32_t color);
	void (*add_rect)(int x, int y, int w, int h, uint32_t color);
};

enum {
	GAME_KEYCODE_LEFT   = 1 << 0,
	GAME_KEYCODE_RIGHT  = 1 << 1,
	GAME_KEYCODE_DOWN   = 1 << 2,
	GAME_KEYCODE_UP     = 1 << 3,
	GAME_KEYCODE_ACTION = 1 << 4,
	GAME_KEYCODE_PAUSE  = 1 << 5,
};

int Game_Init(struct host_intf_t *host_intf);
int Game_Fini();
int Game_UpdateInput(int key, int down);
int Game_DoFrame();

#define MAX_OBJECTS       20
#define MAX_SCORE_BONUSES 10

enum {
	SND_MASSUE2,
	SND_RESSORT,
	SND_BONUS,
};

enum {
	L1SPR_PLAYER_DEAD_1 = 39,
	L1SPR_NOT_ENOUGH_FOOD_1 = 83,
	L1SPR_NOT_ENOUGH_FOOD_2 = 92,
	L1SPR_DOWN_ARROW = 105,
	L1SPR_FIREBALL = 109,
	L1SPR_PLAYER_WITH_BALLOONS = 117,
	L1SPR_BALLOONS = 118,
	L1SPR_PLAYER_HALO = 128,
	L1SPR_GET_READY_1 = 133,
	L1SPR_GET_READY_2 = 134,
	L1SPR_PLAYER_FRONT = 135,
	L1SPR_PAUSE = 142,
	L1SPR_TRAMPOLINE = 147,
};

struct object_t {
	int16_t state;
	int16_t x_pos;
	int16_t y_pos;
	int16_t spr_num;
	int16_t xflip;
};

struct score_bonus_t {
	int16_t counter;
	int16_t x_pos;
	int16_t y_pos;
	int16_t spr_num;
};

struct game_t {
	struct host_intf_t host;

	uint32_t keymask;

	uint32_t rand;

	uint32_t score;
	uint32_t extra_life_score;

	int16_t level_num;

	int16_t food;
	int16_t time;
	int16_t timer_counter;

	int16_t game_over_flag;

	int16_t player_x_pos, player_y_pos;
	int16_t player_dx, player_dy;
	int16_t player_y_vel;
	int16_t player_energy;
	int16_t player_lifes;
	int16_t player_climbing_flag;
	int16_t player_club_flag;
	int16_t player_halo_duration;
	int16_t player_halo_spr_num;
	int16_t player_gravity_flag;
	int16_t player_moving_frame_num;
	int16_t player_dead_x_pos, player_dead_y_pos;
	int16_t player_dead_counter;
	int16_t player_action_key_flag;
	int16_t word_3717C;
	bool player_halo_flag;
	bool player_facing_left_flag;
	bool player_axe_flag;
	bool player_level5_flag;
	int16_t player_restart_x_pos, player_restart_y_pos;
	int16_t player_restart_screen;

	int16_t fireball_flag; /* 1: to the right, -1: to the left */
	int16_t fireball_x_pos, fireball_y_pos;

	int16_t balloon_x_pos, balloon_y_pos;

	uint8_t level_dur[40 * 4 * 6];
	uint8_t tiles_mask_buffer[GAME_H * (GAME_W / 8)];

	bool next_screen_flag; /* 1 if screen should change (left, right, cave, secret) */
	int16_t current_screen;
	uint8_t *current_objects_dat;
	int16_t screen_height;

	int16_t bonus_current_dy;
	int16_t bonus_current_y_pos;
	struct score_bonus_t score_bonuses_tbl[MAX_SCORE_BONUSES];

	int objects_count;
	struct object_t objects_tbl[MAX_OBJECTS];
	bool object_updated_flag;
	bool bomb_flag;
	bool player_platform_flag;
	uint16_t object_cave_entrance_mask;
	int16_t object_player_y_vel;

	int16_t cave_exit_x_pos, cave_exit_y_pos;
	int16_t player_exit_from_cave_screen_x_pos, player_exit_from_cave_screen_y_pos;
};

static const bool k_player_no_hit = 0;
static const bool k_no_timeout = 0;
static const bool k_no_food = 0;
static const bool k_monsters_enabled = 1;
static const int16_t k_start_screen_num = 0;

/* game.c */
extern struct game_t g_game;

void Game_AddObject(int unk, int x_pos, int y_pos, int spr_num, int flag);
void Game_GetObjectDim(int spr_num, int *w, int *h);
void Game_AddScore(int x_pos, int y_pos, int score);
void Game_UpdateScoreBonuses();
void Game_DrawObjects();
void Game_DrawString(int x_pos, int y_pos, const char *s, uint8_t color_fg, uint8_t color_bg, int flag);
void Game_DrawBackgroundObject(int x, int y, int num);
void Game_DrawPanelScore();
void Game_DrawPanelLifes();
void Game_DrawPanelTime();
void Game_DrawPanelFood();
void Game_DrawPanelEnergy();
void Game_UpdateTime();
int Game_GetScreenMask(int x_pos, int y_pos);
void Game_UpdateScreenMask(int tile_num, int x_pos, int y_pos);
void Game_SetScreenHeight(int height);
void Game_DrawLevelScreen(const uint16_t *size, const uint16_t *tiles, int screen_num);
void Game_DrawSecretScreen(int num);
void Game_DrawCaveScreenLevel1(int num);
void Game_HitPlayer(int energy);
void player_update_action();
void player_update_club();
void player_update_halo();
void player_update_flying_position();
void add_player_object();
void Game_UpdateFireball();

/* cave.c */
int Cave_Init(int level, int num);
int Cave_DoFrame(int level);

/* level1.c */
int Level1_Init();
int Level1_DoFrame();

/* objects.c */
void Objects_Reset(uint8_t *p);
void Objects_Update();
uint8_t *Objects_ChangeScreen(uint8_t *p, int screen_num);
void Objects_DrawBackground();

/* random.c */
void Random_Reset();
uint16_t Random_GetNumber();

/* staticres.c */
extern const uint32_t p1_level1_palette_colors[];
extern uint8_t p1_level1_screen_tbl[];
extern uint8_t p1_level1_secret_tbl[];
extern uint8_t p1_level1_cave_tbl[];
extern const uint16_t p1_level1_elem_size_tbl[];
extern const uint16_t p1_level1_elem_data_tbl[];
extern const uint16_t p1_level1_screen_height_tbl[];
extern const uint16_t p1_level1_cave_size_tbl[];
extern const uint16_t p1_player_walk_spr_num_tbl[];
extern const uint16_t p1_player_walk_x_vel_tbl[];
extern const uint16_t p1_player_walk_dx_tbl[];
extern const uint16_t p1_player_hitting_spr_num_tbl[];
extern const uint16_t p1_player_club_spr_num_tbl[];
extern const uint16_t p1_player_axe_spr_num_tbl[];
extern const uint8_t p1_object0x0a_data[];
extern const uint8_t p1_object0x0b_data[];
extern const uint8_t p1_object0x0c_data[];
extern const uint8_t p1_object0x0d_data[];
extern const uint16_t p1_score_tbl[];
extern const uint16_t p1_player_death_spr_num_tbl[];
extern const uint16_t p1_bonus_spr_num_tbl[];
extern const uint16_t p1_secret_score_tbl[];
extern const uint16_t p1_bird_spr_num_tbl[];

#endif /* GAME_H__ */
