#include "../include/video.h"
#include "../include/disassemble8080p.h"
#include "../include/libattopng.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdio.h>
#include <stdlib.h>

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
    const int ROW_COUNT = 224;     // screen width
    const int COL_COUNT = 256 / 8; // screen height

    // uint8_t vram = state->memory[0x2400];
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
                // uint8_t pxl = data_bit * 255;
                // uint8_t pxl = 255;
                int x = (2*r)-1;
                int y = (2*col_pxl--) - 1;
                SDL_Rect rect = {x, y, 1, 1};
                int red_limit = 35;
                int white_limit = 191;
                // TODO Add conditions for red / green / white filters.
                if (y < red_limit * 2) // red
                    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, pxl, 0, 0));
                if (y > red_limit*2 && y < white_limit*2)// white
                    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, pxl, pxl, pxl));
                if (y > white_limit * 2) // green
                {
                    if (y > 238*2 && (x < 15*2 || x > 100*2)) // white
                        SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, pxl, pxl, pxl));
                    else // green
                        SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0, pxl, 0));
                }
            }
            // printf("%02x", state->memory[0x2400 + data_pos]);
        }
    }
}
