#include <stdint.h>

typedef struct Conditions
{
    uint8_t zero : 1;      // aka Z
    uint8_t sign : 1;      // aka S
    uint8_t parity : 1;    // aka P
    uint8_t carry : 1;     // aka CY
    uint8_t aux_carry : 1; // aka AC
    uint8_t pad : 3;
} Conditions;

typedef struct State
{
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    uint8_t *memory;
    Conditions conditions;
    uint8_t int_enable;
} State;
