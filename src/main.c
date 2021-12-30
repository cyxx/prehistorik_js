
#include <SDL.h>
#include <SDL_mixer.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <sys/param.h>
#include "game.h"

static const char *WINDOW_CAPTION = "Prehistorik";

static const char *ICON_FILENAME = "icon.bmp";

static const int SCALE = 2;

static const int TICK_MS = 50;

#define MAX_SPRITESHEETS MAT_COUNT

struct spritesheet_t {
	int count;
	SDL_Rect *r;
	SDL_Surface *surface;
	SDL_Texture *texture;
};

static int _spritesheets_count;
static struct spritesheet_t _spritesheets[MAX_SPRITESHEETS];

struct sprite_t {
	int sheet;
	int num;
	int x, y;
	bool xflip;
};

#define MAX_SPRITES 512

struct spritelayer_t {
	int sprites_count;
	struct sprite_t sprites[MAX_SPRITES];
	SDL_Rect clipping_rect;
};

#define MAX_SPRITELAYERS 2

static struct spritelayer_t _spritelayers[MAX_SPRITELAYERS];

struct rect_t {
	SDL_Rect r;
	uint32_t color;
};

struct rect_t _background_rect;

#define MAX_RECTS 16

static int _rects_count;
static struct rect_t _rects[MAX_RECTS];

static SDL_Texture *_background;
static SDL_Renderer *_renderer;

static const int kJoystickDefaultIndex = 0;
static const int kJoystickCommitValue = 16384;

static SDL_Joystick *_joystick;
static const int kJoystickMapSize = 8;
static int _joystick_tbl[8];

static SDL_GameController *_controller;
static int _gamepad_tbl[SDL_CONTROLLER_BUTTON_MAX];

static int _scancode_tbl[512];

static void setup_keymap() {
	_scancode_tbl[SDL_SCANCODE_LEFT]   = GAME_KEYCODE_LEFT;
	_scancode_tbl[SDL_SCANCODE_RIGHT]  = GAME_KEYCODE_RIGHT;
	_scancode_tbl[SDL_SCANCODE_UP]     = GAME_KEYCODE_UP;
	_scancode_tbl[SDL_SCANCODE_DOWN]   = GAME_KEYCODE_DOWN;
	_gamepad_tbl[SDL_CONTROLLER_BUTTON_DPAD_UP]    = GAME_KEYCODE_UP;
	_gamepad_tbl[SDL_CONTROLLER_BUTTON_DPAD_DOWN]  = GAME_KEYCODE_DOWN;
	_gamepad_tbl[SDL_CONTROLLER_BUTTON_DPAD_LEFT]  = GAME_KEYCODE_LEFT;
	_gamepad_tbl[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] = GAME_KEYCODE_RIGHT;
	_scancode_tbl[SDL_SCANCODE_SPACE]  = GAME_KEYCODE_ACTION;
	_scancode_tbl[SDL_SCANCODE_RETURN] = GAME_KEYCODE_ACTION;
	_scancode_tbl[SDL_SCANCODE_LSHIFT] = GAME_KEYCODE_JUMP;
	_scancode_tbl[SDL_SCANCODE_RSHIFT] = GAME_KEYCODE_JUMP;
	_scancode_tbl[SDL_SCANCODE_J]      = GAME_KEYCODE_JUMP;
	_scancode_tbl[SDL_SCANCODE_ESCAPE] = GAME_KEYCODE_PAUSE;
	_scancode_tbl[SDL_SCANCODE_P]      = GAME_KEYCODE_PAUSE;
	_joystick_tbl[0] = GAME_KEYCODE_ACTION;
	_joystick_tbl[1] = GAME_KEYCODE_JUMP;
	_gamepad_tbl[SDL_CONTROLLER_BUTTON_A] = GAME_KEYCODE_ACTION;
	_gamepad_tbl[SDL_CONTROLLER_BUTTON_B] = GAME_KEYCODE_JUMP;
	_gamepad_tbl[SDL_CONTROLLER_BUTTON_BACK]  = GAME_KEYCODE_PAUSE;
	_gamepad_tbl[SDL_CONTROLLER_BUTTON_START] = GAME_KEYCODE_PAUSE;
	_gamepad_tbl[SDL_CONTROLLER_BUTTON_DPAD_UP]    = GAME_KEYCODE_UP;
	_gamepad_tbl[SDL_CONTROLLER_BUTTON_DPAD_DOWN]  = GAME_KEYCODE_DOWN;
	_gamepad_tbl[SDL_CONTROLLER_BUTTON_DPAD_LEFT]  = GAME_KEYCODE_LEFT;
	_gamepad_tbl[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] = GAME_KEYCODE_RIGHT;
}

static uint16_t fread_le16(FILE *fp) {
	const uint16_t x = fgetc(fp);
	return x | (fgetc(fp) << 8);
}

static void load_spritesheet(SDL_Renderer *renderer, const char *name_bin, const char *name_bmp) {
	assert(_spritesheets_count < MAX_SPRITESHEETS);
	struct spritesheet_t *sheet = &_spritesheets[_spritesheets_count];
	FILE *fp = fopen(name_bin, "rb");
	assert(fp);
	sheet->count = fread_le16(fp);
	sheet->r = (SDL_Rect *)malloc(sheet->count * sizeof(SDL_Rect));
	for (int i = 0; i < sheet->count; ++i) {
		SDL_Rect *rect = &sheet->r[i];
		rect->x = fread_le16(fp);
		rect->y = fread_le16(fp);
		rect->w = fread_le16(fp);
		rect->h = fread_le16(fp);
	}
	fclose(fp);
	sheet->surface = SDL_LoadBMP(name_bmp);
	SDL_SetColorKey(sheet->surface, 1, 0x00);
	fprintf(stdout, "Loaded surface '%s' %p with %d sprites\n", name_bin, sheet->surface, sheet->count);
	sheet->texture = SDL_CreateTextureFromSurface(renderer, sheet->surface);
	++_spritesheets_count;
}

static void render_clear_sprites(int dst_mask) {
	for (int j = 0; j < MAX_SPRITELAYERS; ++j) {
		if (dst_mask & (1 << j)) {
			_spritelayers[j].sprites_count = 0;
		}
	}
}

static void render_add_sprite(int spr_type, int frame, int x, int y, int dst_mask, int xflip) {
	for (int j = 0; j < MAX_SPRITELAYERS; ++j) {
		if (dst_mask & (1 << j)) {
			struct spritelayer_t *layer = &_spritelayers[j];
			assert(layer->sprites_count < MAX_SPRITES);
			struct sprite_t *spr = &layer->sprites[layer->sprites_count];
			spr->sheet = spr_type;
			spr->num = frame;
			spr->x = x;
			spr->y = y;
			spr->xflip = xflip;
			++layer->sprites_count;
		}
	}
}

static void render_get_sprite_dim(int file_num, int spr_num, int *w, int *h) {
	const SDL_Rect *rect = &_spritesheets[file_num].r[spr_num];
	if (w) {
		*w = rect->w;
	}
	if (h) {
		*h = rect->h;
	}
}

static void render_set_clipping_rect(int dst_mask, int x, int y, int w, int h) {
	for (int j = 0; j < MAX_SPRITELAYERS; ++j) {
		if (dst_mask & (1 << j)) {
			_spritelayers[j].clipping_rect.x = x;
			_spritelayers[j].clipping_rect.y = y;
			_spritelayers[j].clipping_rect.w = w;
			_spritelayers[j].clipping_rect.h = h;
		}
	}
}

static void render_fill_background_rect(int x, int y, int w, int h, uint32_t color) {
	_background_rect.r.x = x;
	_background_rect.r.y = y;
	_background_rect.r.w = w + 1;
	_background_rect.r.h = h + 1;
	_background_rect.color = color;
}

static void render_add_rect(int x, int y, int w, int h, uint32_t color) {
	assert(_rects_count < MAX_RECTS);
	struct rect_t *r = &_rects[_rects_count];
	r->r.x = x;
	r->r.y = y;
	r->r.w = w + 1;
	r->r.h = h + 1;
	r->color = color;
	++_rects_count;
}

static void fill_rect(SDL_Renderer *renderer, const SDL_Rect *rect, uint32_t color) {
	const uint8_t r = (color >> 16) & 255;
	const uint8_t g = (color >>  8) & 255;
	const uint8_t b =  color        & 255;
	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, rect);
}

static void redraw_screen(SDL_Renderer *renderer) {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, _background, 0, 0);
	if ((_background_rect.color >> 24) != 0) {
		fill_rect(renderer, &_background_rect.r, _background_rect.color);
	}
	for (int j = 0; j < _rects_count; ++j) {
		struct rect_t *rect = &_rects[j];
		if ((rect->color >> 24) != 0) {
			fill_rect(renderer, &rect->r, rect->color);
		}
	}
	for (int j = 0; j < MAX_SPRITELAYERS; ++j) {
		const struct spritelayer_t *layer = &_spritelayers[j];
		SDL_RenderSetClipRect(renderer, &layer->clipping_rect);
		for (int i = 0; i < layer->sprites_count; ++i) {
			const struct sprite_t *spr = &layer->sprites[i];
			assert(spr->sheet < _spritesheets_count);
			struct spritesheet_t *sheet = &_spritesheets[spr->sheet];
			if (spr->num >= sheet->count) {
				fprintf(stderr, "Invalid sprite %d (sheet %d)\n", spr->num, sheet->count);
				continue;
			}
			SDL_Rect r;
			r.x = spr->x;
			r.y = spr->y;
			r.w = sheet->r[spr->num].w;
			r.h = sheet->r[spr->num].h;
			if (spr->xflip) {
				SDL_RenderCopyEx(_renderer, sheet->texture, &sheet->r[spr->num], &r, 0., 0, SDL_FLIP_HORIZONTAL);
			} else {
				SDL_RenderCopy(renderer, sheet->texture, &sheet->r[spr->num], &r);
			}
		}
		SDL_RenderSetClipRect(renderer, 0);
	}
	SDL_RenderPresent(renderer);
	_spritelayers[1].sprites_count = 0;
	_rects_count = 0;
}

static int load_file(const char *name, uint8_t *dst) {
	const char *ext = strrchr(name, '.');
	if (strcasecmp(ext + 1, "pc1") == 0) {
		char path[MAXPATHLEN];
		snprintf(path, sizeof(path), "%s", name);
		strcpy(path + strlen(path) - 3, "bmp");
		SDL_Surface *surface = SDL_LoadBMP(path);
		fprintf(stdout, "Loaded background surface '%s' %p\n", path, surface);
		_background = SDL_CreateTextureFromSurface(_renderer, surface);
	} else if (strcasecmp(ext + 1, "mat") == 0) {
		char path_bmp[MAXPATHLEN];
		snprintf(path_bmp, sizeof(path_bmp), "sheet-%s", name);
		strcpy(path_bmp + strlen(path_bmp) - 3, "bmp");
		char path_bin[MAXPATHLEN];
		snprintf(path_bin, sizeof(path_bin), "sheet-%s", name);
		strcpy(path_bin + strlen(path_bin) - 3, "bin");
		load_spritesheet(_renderer, path_bin, path_bmp);
	} else if (strcasecmp(ext + 1, "dur") == 0) {
		FILE *fp = fopen("LEVEL1.DUR", "rb");
		fread(dst, 960, 1, fp);
		fclose(fp);
	} else {
		fprintf(stderr, "Unhandled file extension '%s'\n", ext + 1);
	}
	return 0;
}

static void clear_spritesheets() {
	for (int i = MAT_LSPR; i < _spritesheets_count; ++i) {
		struct spritesheet_t *sheet = &_spritesheets[i];
		free(sheet->r);
		SDL_FreeSurface(sheet->surface);
		SDL_DestroyTexture(sheet->texture);
	}
	_spritesheets_count = MAT_LSPR;
}

static void init_sound() {
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 2048);
}

static Mix_Chunk *_sounds[SND_COUNT];

static void load_sounds() {
	_sounds[SND_MASSUE2] = Mix_LoadWAV("MASSUE2.VOC");
	_sounds[SND_RESSORT] = Mix_LoadWAV("RESSORT.VOC");
	_sounds[SND_BONUS]   = Mix_LoadWAV("BONUS.VOC");
}

static void free_sounds() {
	for (int i = 0; i < SND_COUNT; ++i) {
		Mix_FreeChunk(_sounds[i]);
		_sounds[i] = 0;
	}
}

static void play_sound(int num) {
	if (_sounds[num]) {
		Mix_PlayChannel(-1, _sounds[num], 0);
	}
}

static void play_music(int num) {
}

static struct host_intf_t _host = {
	.load_file = load_file,
	.clear_spritesheets = clear_spritesheets,
	.clear_sprites = render_clear_sprites,
	.add_sprite = render_add_sprite,
	.get_sprite_dim = render_get_sprite_dim,
	.set_clipping_rect = render_set_clipping_rect,
	.fill_background_rect = render_fill_background_rect,
	.add_rect = render_add_rect,
	.init_sound = init_sound,
	.play_sound = play_sound,
	.play_music = play_music,
};

static void handle_event(SDL_Event *ev, bool *quit, bool *paused) {
	switch (ev->type) {
	case SDL_QUIT:
		*quit = true;
		break;
	case SDL_WINDOWEVENT:
		switch (ev->window.event) {
		case SDL_WINDOWEVENT_FOCUS_GAINED:
		case SDL_WINDOWEVENT_FOCUS_LOST:
			*paused = (ev->window.event == SDL_WINDOWEVENT_FOCUS_LOST);
			break;
		}
		break;
	case SDL_KEYUP:
		if (_scancode_tbl[ev->key.keysym.scancode] != 0) {
			Game_UpdateInput(_scancode_tbl[ev->key.keysym.scancode], 0);
		}
		break;
	case SDL_KEYDOWN:
		if (_scancode_tbl[ev->key.keysym.scancode] != 0) {
			Game_UpdateInput(_scancode_tbl[ev->key.keysym.scancode], 1);
		}
		break;
	case SDL_JOYHATMOTION:
		if (_joystick) {
			Game_UpdateInput(GAME_KEYCODE_UP,    (ev->jhat.value & SDL_HAT_UP)    != 0);
			Game_UpdateInput(GAME_KEYCODE_DOWN,  (ev->jhat.value & SDL_HAT_DOWN)  != 0);
			Game_UpdateInput(GAME_KEYCODE_LEFT,  (ev->jhat.value & SDL_HAT_LEFT)  != 0);
			Game_UpdateInput(GAME_KEYCODE_RIGHT, (ev->jhat.value & SDL_HAT_RIGHT) != 0);
		}
		break;
	case SDL_JOYAXISMOTION:
		if (_joystick) {
			switch (ev->jaxis.axis) {
			case 0:
				Game_UpdateInput(GAME_KEYCODE_LEFT,  (ev->jaxis.value < -kJoystickCommitValue));
				Game_UpdateInput(GAME_KEYCODE_RIGHT, (ev->jaxis.value >  kJoystickCommitValue));
				break;
			case 1:
				Game_UpdateInput(GAME_KEYCODE_UP,   (ev->jaxis.value < -kJoystickCommitValue));
				Game_UpdateInput(GAME_KEYCODE_DOWN, (ev->jaxis.value >  kJoystickCommitValue));
				break;
			}
		}
		break;
	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
		if (_joystick) {
			if (ev->jbutton.button >= 0 && ev->jbutton.button < kJoystickMapSize) {
				if (_joystick_tbl[ev->jbutton.button] != 0) {
					Game_UpdateInput(_joystick_tbl[ev->jbutton.button], ev->jbutton.state == SDL_PRESSED);
				}
			}
		}
		break;
	case SDL_CONTROLLERAXISMOTION:
		if (_controller) {
			switch (ev->caxis.axis) {
			case SDL_CONTROLLER_AXIS_LEFTX:
			case SDL_CONTROLLER_AXIS_RIGHTX:
				Game_UpdateInput(GAME_KEYCODE_LEFT,  (ev->caxis.value < -kJoystickCommitValue));
				Game_UpdateInput(GAME_KEYCODE_RIGHT, (ev->caxis.value >  kJoystickCommitValue));
				break;
			case SDL_CONTROLLER_AXIS_LEFTY:
			case SDL_CONTROLLER_AXIS_RIGHTY:
				Game_UpdateInput(GAME_KEYCODE_UP,   (ev->caxis.value < -kJoystickCommitValue));
				Game_UpdateInput(GAME_KEYCODE_DOWN, (ev->caxis.value >  kJoystickCommitValue));
				break;
			}
		}
		break;
	case SDL_CONTROLLERBUTTONDOWN:
	case SDL_CONTROLLERBUTTONUP:
		if (_controller) {
			if (_gamepad_tbl[ev->cbutton.button] != 0) {
				Game_UpdateInput(_gamepad_tbl[ev->cbutton.button], ev->cbutton.state == SDL_PRESSED);
			}
		}
		break;
	default:
		break;
	}
}

static void mainLoop() {
	bool quit, paused;
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		handle_event(&ev, &quit, &paused);
	}
	Game_DoFrame();
	redraw_screen(_renderer);
}

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);
	SDL_ShowCursor(SDL_DISABLE);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"); /* nearest pixel sampling */

	const int flags = SDL_WINDOW_RESIZABLE;
	const int w = GAME_W * SCALE;
	const int h = GAME_H * SCALE;
	SDL_Window *window = SDL_CreateWindow(WINDOW_CAPTION, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
	if (!window) {
		return -1;
	}
	SDL_Surface *icon = SDL_LoadBMP(ICON_FILENAME);
	if (icon) {
		SDL_SetWindowIcon(window, icon);
		SDL_FreeSurface(icon);
	}
	_renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderSetLogicalSize(_renderer, GAME_W, GAME_H);

	for (int j = 0; j < MAX_SPRITELAYERS; ++j) {
		_spritelayers[j].clipping_rect.x = 0;
		_spritelayers[j].clipping_rect.y = 0;
		_spritelayers[j].clipping_rect.w = GAME_W;
		_spritelayers[j].clipping_rect.h = GAME_H;
	}

	setup_keymap();
	if (SDL_NumJoysticks() > 0) {
		if (SDL_IsGameController(kJoystickDefaultIndex)) {
			_controller = SDL_GameControllerOpen(kJoystickDefaultIndex);
			if (_controller) {
				fprintf(stdout, "Using controller '%s'\n", SDL_GameControllerName(_controller));
			}
		}
		if (!_controller) {
			_joystick = SDL_JoystickOpen(kJoystickDefaultIndex);
			if (_joystick) {
				fprintf(stdout, "Using joystick '%s'\n", SDL_JoystickName(_joystick));
			}
		}
	}

	Mix_Init(0);
	load_sounds();

	Game_Init(&_host);
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(mainLoop, 1000 / TICK_MS, 1);
#else
	bool quit = false;
	bool paused = false;
	while (1) {
		SDL_Event ev;
		const uint32_t nextTick = SDL_GetTicks() + TICK_MS;
		while (SDL_PollEvent(&ev)) {
			handle_event(&ev, &quit, &paused);
		}
		if (quit) {
			break;
		}
		if (!paused) {
			Game_DoFrame();
			redraw_screen(_renderer);
			const int ms = nextTick - SDL_GetTicks();
			SDL_Delay(ms < 16 ? 16 : ms);
		} else {
			SDL_Delay(TICK_MS);
		}
	}
#endif
	Game_Fini();

	free_sounds();
	Mix_Quit();

	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(window);
	if (_controller) {
		SDL_GameControllerClose(_controller);
	}
	if (_joystick) {
		SDL_JoystickClose(_joystick);
	}
	SDL_Quit();
	return 0;
}
