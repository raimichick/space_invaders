#include "../include/video.h"
#include "../include/disassemble8080p.h"
#include "../include/libattopng.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdio.h>
#include <stdlib.h>

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Surface *game_surface;
static SDL_Texture *cab_texture;
static SDL_Texture *planet_texture;
static SDL_Texture *game_texture;

int initialize_video()
{
    window = SDL_CreateWindow("SDL2 Window",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              1192, 1179, 0);
    if (!window) { SDL_Log( "Unable to create window. %s\n", SDL_GetError()); return 1; }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) { SDL_Log( "Unable to create renderer. %s\n", SDL_GetError()); return 1; }

    SDL_Surface *cab_surface = IMG_Load("../assets/cabinet.png");
    if (!cab_surface) { SDL_Log( "Unable to create cabinet surface. %s\n", SDL_GetError()); return 1; }

    SDL_Surface *planet_surface = IMG_Load("../assets/planet.png");
    if (!planet_surface) { SDL_Log( "Unable to create planet surface. %s\n", SDL_GetError()); return 1; }

    game_surface = SDL_CreateRGBSurface(0,
                                        SCREEN_WIDTH*SETTINGS_WINDOW_MULTIPLIER,
                                        SCREEN_HEIGHT*SETTINGS_WINDOW_MULTIPLIER,
                                        32,
                                        0xFF000000,
                                        0x00FF0000,
                                        0x0000FF00,
                                        0x000000FF);
    if (!game_surface) { SDL_Log( "Unable to create game surface. %s\n", SDL_GetError()); return 1; }

    cab_texture = SDL_CreateTextureFromSurface(renderer, cab_surface);
    if (!cab_texture) { SDL_Log( "Unable to create cabinet texture. %s\n", SDL_GetError()); return 1; }

    planet_texture = SDL_CreateTextureFromSurface(renderer, planet_surface);
    if (!planet_texture) { SDL_Log( "Unable to create planet texture. %s\n", SDL_GetError()); return 1; }

    game_texture = SDL_CreateTextureFromSurface(renderer, game_surface);
    if (!game_texture) { SDL_Log( "Unable to create game texture. %s\n", SDL_GetError()); return 1; }

    SDL_FreeSurface(cab_surface);
    SDL_FreeSurface(planet_surface);

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
    spinvaders_vram_matrix_to_surface(state, game_surface);
    game_texture = SDL_CreateTextureFromSurface(renderer, game_surface);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, planet_texture, NULL,NULL);
    SDL_RenderCopy(renderer, cab_texture, NULL,NULL);
    int m = SETTINGS_WINDOW_MULTIPLIER;
    SDL_Rect rect = {(1192-(SCREEN_WIDTH*m))/2, (1179-(SCREEN_HEIGHT*m))/2, SCREEN_WIDTH*m, SCREEN_HEIGHT*m};
    SDL_RenderCopy(renderer, game_texture, NULL, &rect);
    SDL_RenderPresent(renderer);
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
            uint8_t data = state->memory[0x2400 + data_pos];
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
    const int ROW_COUNT = SCREEN_WIDTH;      // screen width
    const int COL_COUNT = SCREEN_HEIGHT / 8; // screen height / 8 because each bit per byte is pxl

    for (int r = 0; r < ROW_COUNT; r++)
    {
        int col_pxl = 255;
        for (int c = 0; c < COL_COUNT; c++)
        {
            uint16_t data_pos = (r * COL_COUNT) + c;
            uint8_t data = state->memory[0x2400 + data_pos];
            for (int bit_num = 0; bit_num < 8; bit_num++)
            {
                uint8_t pxl = data & (0x01 << bit_num); // account for little endian
                pxl = (pxl == 0) ? 0 : 0xff;

                // read by memory organization, placed in rect as rotated.
                int x = (SCREEN_SIZE_MULT * r) - 1;
                int y = (SCREEN_SIZE_MULT * col_pxl--) - 1;
                SDL_Rect rect = {x, y, SCREEN_SIZE_MULT, SCREEN_SIZE_MULT};

                if (pxl == 0)
                {
                    SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, 0, 0, 0, 0));
                    continue;
                }



                // set colors
                int red_limit = 33 * SCREEN_SIZE_MULT;
                int white_limit = 191 * SCREEN_SIZE_MULT;
                int white_line_border = 238 * SCREEN_SIZE_MULT;
                if (y < red_limit) // red
                    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, pxl, 0, 0));
                else if (y < white_limit || (y >= white_line_border &&
                                             y <= white_line_border + SCREEN_SIZE_MULT)) // white
                    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, pxl, pxl, pxl));
                else
                {
                    // only inner portion green
                    if (y > 239 * SCREEN_SIZE_MULT &&
                        (x < 15 * SCREEN_SIZE_MULT || x > 100 * SCREEN_SIZE_MULT)) // white
                        SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, pxl, pxl, pxl));
                    else // green
                        SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0, pxl, 0));
                }
            }
            // printf("%02x", state->memory[0x2400 + data_pos]);
        }
    }
}

void spinvaders_vram_matrix_to_texture(State *state, SDL_Texture *texture)
{
    // the grid is sideways in memory, need to rotate CC for screen to be upright.
    const int ROW_COUNT = SCREEN_WIDTH;      // screen width
    const int COL_COUNT = SCREEN_HEIGHT / 8; // screen height / 8 because each bit per byte is pxl

    void* pixels;
    int pitch;
    if (SDL_LockTexture(texture, NULL, &pixels, &pitch) < 0) {
        printf("Unable to lock texture! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // Access and modify the texture's pixel data
    Uint32* pixels32 = (Uint32*)pixels;
    // Draw a blue diagonal line on the texture
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        int x = y;
        if (x < SCREEN_WIDTH) {
            pixels32[y * (pitch / 4) + x] = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), 0, 0, 255, 255); // Solid blue
        }
    }
    // Unlock the texture
    SDL_UnlockTexture(texture);
    return;
    for (int r = 0; r < ROW_COUNT; r++)
    {
        int col_pxl = 255;
        for (int c = 0; c < COL_COUNT; c++)
        {
            uint16_t data_pos = (r * COL_COUNT) + c;
            uint8_t data = state->memory[0x2400 + data_pos];
            for (int bit_num = 0; bit_num < 8; bit_num++)
            {
                uint8_t pxl = data & (0x01 << bit_num); // account for little endian
                pxl = (pxl == 0) ? 0 : 0xff;

                // read by memory organization, placed in rect as rotated.
                int x = (1 * r) - 1;
                int y = (1 * col_pxl--) - 1;
                // if (pxl == 0)
                // {
                //     pixels32[y * (pitch / 4) + x] = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), 0, 0, 0, 0); // transparent.
                //     continue;
                // }

                // set colors
                int red_limit = 33 * 1;
                int white_limit = 191 * 1;
                int white_line_border = 238 * 1;
                if (y < red_limit) // red
                    // SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, pxl, 0, 0));
                    pixels32[y * (pitch / 4) + x] = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), 255, 0, 0, 255); // transparent.
                else if (y < white_limit || (y >= white_line_border &&
                                             y <= white_line_border + 1)) // white
                    // SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, pxl, pxl, pxl));
                    pixels32[y * (pitch / 4) + x] = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), 255, 255, 255, 255); // transparent.
                else
                {
                    // only inner portion green
                    if (y > 239 * 1 &&
                        (x < 15 * 1 || x > 100 * 1)) // white
                        // SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, pxl, pxl, pxl));
                        pixels32[y * (pitch / 4) + x] = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), 255, 255, 255, 255); // transparent.
                    else // green
                        // SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0, pxl, 0));
                        pixels32[y * (pitch / 4) + x] = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), 0, 255, 0, 255); // transparent.
                }
            }
            // printf("%02x", state->memory[0x2400 + data_pos]);
        }
    }

    // Unlock the texture
    SDL_UnlockTexture(texture);
}
