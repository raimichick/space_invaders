//
// Created by Ayu on 4/13/2024.
//
#include "../src/test_functions.c"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (test_func() == atoi(argv[1])) return 0;
    return 1;
}