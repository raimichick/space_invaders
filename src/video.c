#include "../include/video.h"
#include "../include/libattopng.h"
#include "../include/shell.h"
#include "../include/settings.h"

#include <stdio.h>

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Surface *game_surface;
static SDL_Texture *cab_texture;
static SDL_Texture *planet_texture;
static SDL_Texture *game_texture;

static int win_size_w;
static int win_size_h;
static int play_area_size_w;
static int play_area_size_h;

int initialize_video()
{
    /* sets up SDL window, renderer, surfaces, textures and updates window size variables. */

    win_size_h = SCREEN_HEIGHT*SETTINGS_WINDOW_MULTIPLIER,
    win_size_w = SCREEN_WIDTH*SETTINGS_WINDOW_MULTIPLIER,
    play_area_size_w = win_size_w;
    play_area_size_h = win_size_h;

    window = SDL_CreateWindow("Space Invaders 8080",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              win_size_w,
                              win_size_h,
                              0);
    if (!window) { SDL_Log( "Unable to create window. %s\n", SDL_GetError()); return 1; }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) { SDL_Log( "Unable to create renderer. %s\n", SDL_GetError()); return 1; }
    game_surface = SDL_CreateRGBSurface(0,
                                        win_size_w,
                                        win_size_h,
                                        32,
                                        0xFF000000,
                                        0x00FF0000,
                                        0x0000FF00,
                                        0x000000FF);
    if (!game_surface) { SDL_Log( "Unable to create game surface. %s\n", SDL_GetError()); return 1; }

    game_texture = SDL_CreateTextureFromSurface(renderer, game_surface);
    if (!game_texture) { SDL_Log( "Unable to create game texture. %s\n", SDL_GetError()); return 1; }


    if (SETTINGS_BACKGROUND)
    {
        // setup background textures
        SDL_Surface *cab_surface = IMG_Load("../assets/cabinet1.png");
        if (SETTINGS_BACKGROUND == 2)
             cab_surface = IMG_Load("../assets/cabinet2.png");

        if (!cab_surface) { SDL_Log( "Unable to create cabinet surface. %s\n", SDL_GetError()); return 1; }

        SDL_Surface *planet_surface = IMG_Load("../assets/planet_grad.png");
        if (!planet_surface) { SDL_Log( "Unable to create planet surface. %s\n", SDL_GetError()); return 1; }

        cab_texture = SDL_CreateTextureFromSurface(renderer, cab_surface);
        if (!cab_texture) { SDL_Log( "Unable to create cabinet texture. %s\n", SDL_GetError()); return 1; }

        planet_texture = SDL_CreateTextureFromSurface(renderer, planet_surface);
        if (!planet_texture) { SDL_Log( "Unable to create planet texture. %s\n", SDL_GetError()); return 1; }

        // resize window for background, center window
        win_size_w = ((cab_surface->w*SETTINGS_WINDOW_MULTIPLIER) / 2);
        win_size_h = ((cab_surface->h*SETTINGS_WINDOW_MULTIPLIER) / 2);
        SDL_SetWindowSize(window, win_size_w, win_size_h);
        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

        SDL_FreeSurface(cab_surface);
        SDL_FreeSurface(planet_surface);
    }

    return 0;
}

void free_video()
{
    SDL_FreeSurface(game_surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void draw_screen(State *state)
{
    SDL_RenderClear(renderer);

    spinvaders_vram_matrix_to_surface(state, game_surface);
    game_texture = SDL_CreateTextureFromSurface(renderer, game_surface);

    int x_pos = (win_size_w-(play_area_size_w))/2;
    int y_pos = (win_size_h-(play_area_size_h))/2;
    int y_offset = 0;
    if (SETTINGS_BACKGROUND)
    {
        y_offset = -6 * SETTINGS_WINDOW_MULTIPLIER;
        if (SETTINGS_BACKGROUND == 2)
            y_offset = -30 * SETTINGS_WINDOW_MULTIPLIER; // for cabinet2.png
        SDL_RenderCopy(renderer, planet_texture, NULL,NULL);
        SDL_Rect rect = {x_pos, y_pos - y_offset, play_area_size_w, play_area_size_h};
        SDL_RenderCopy(renderer, game_texture, NULL, &rect);
        SDL_RenderCopy(renderer, cab_texture, NULL,NULL);
        SDL_RenderPresent(renderer);
    }
    else
    {
        SDL_Rect rect = {x_pos, y_pos - y_offset, play_area_size_w, play_area_size_h};
        SDL_RenderCopy(renderer, game_texture, NULL, &rect);
        SDL_RenderPresent(renderer);
    }
}

void spinvaders_vram_matrix_to_png(State *state, int lbl_prefix)
{
    libattopng_t *png = libattopng_new(256, 224, PNG_GRAYSCALE);

    // the grid is sideways in memory, need to rotate CC for screen to be upright.
    const int ROW_COUNT = 224;     // screen width
    const int COL_COUNT = 256 / 8; // screen height

    // uint8_t vram = state->memory[0x2400];
    for (int r = 0; r < ROW_COUNT; r++)
    {
        for (int c = 0; c < COL_COUNT; c++)
        {
            uint16_t data_pos = (r * COL_COUNT) + c;
            uint8_t data = state->memory[VRAM_ADDRESS + data_pos];
            for (int bit_num = 0; bit_num < 8; bit_num++)
            {
                uint8_t data_bit = data & (0x01 << bit_num); // account for little endian
                data_bit = (data_bit == 0) ? 0 : 0xff;
                libattopng_set_pixel(png, c * 8 + bit_num, r, data_bit);
            }
            // printf("%02x", state->memory[0x2400 + data_pos]);
        }
    }
    char base_name[] = "test_space_inv.png";
    char file_name[50];
    sprintf(file_name, "../pngs/%d-%s", lbl_prefix, base_name);

    libattopng_save(png, file_name);
    libattopng_destroy(png);
}

void spinvaders_vram_matrix_to_surface(State *state, SDL_Surface *surface)
{
    // the grid is sideways in memory, need to rotate CC for screen to be upright.
    const int VRAM_ROW_COUNT = SCREEN_WIDTH;      // screen width
    const int VRAM_COL_COUNT = SCREEN_HEIGHT / 8; // screen height / 8 because each bit per byte is pxl
    const int VRAM_DATA_COUNT = VRAM_ROW_COUNT * VRAM_COL_COUNT;

    uint8_t col_pxl = 255; // will wrap around
    for (int data_pos = 0; data_pos < VRAM_DATA_COUNT; data_pos++)
    {
        uint8_t data = state->memory[VRAM_ADDRESS + data_pos];
        for (int bit_num = 0; bit_num < 8; bit_num++)
        {
            uint8_t pxl = data & (0x01 << bit_num); // account for little endian
            pxl = (pxl == 0) ? 0 : 0xff;

            // read by memory organization, placed in rect as rotated.
            int x = (SETTINGS_WINDOW_MULTIPLIER * data_pos / VRAM_COL_COUNT) - 1;
            int y = (SETTINGS_WINDOW_MULTIPLIER * col_pxl--) - 1;
            SDL_Rect rect = {x, y, SETTINGS_WINDOW_MULTIPLIER, SETTINGS_WINDOW_MULTIPLIER};
            if (pxl == 0)
            {
                SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, 0, 0, 0, 0));
            }
            else
            {
                uint8_t rgb[3] = {pxl, pxl, pxl};
                apply_color_filter(x, y, rgb);
                SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, rgb[0], rgb[1], rgb[2]));
            }
        }
    }
}

void apply_color_filter(int x, int y, uint8_t *rgb)
{
    const int m = SETTINGS_WINDOW_MULTIPLIER;
    const int red_y_limit = 33 * m;
    const int white_y_limit = 191 * m;
    const int line_below_shield = 238 * m;

    if (y < red_y_limit) // red
    {
        rgb[0] *= 1;
        rgb[1] *= 0;
        rgb[2] *= 0;
    }
    else if ( y < white_y_limit) // aliens
    {
        return;
    }
    else if ( (y < line_below_shield || y > line_below_shield + m) &&
             (y <= 239 * m || (x >= 15 * m && x <= 100 * m))) // shields, cannon, and lives
    {
        rgb[0] *= 0;
        rgb[1] *= 1;
        rgb[2] *= 0;
    }
}
