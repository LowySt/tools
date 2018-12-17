#define PLATFORM_IMPLEMENTATION
#include "Platform\lsWindows.h"

#define LS_CRT_IMPLEMENTATION
#include "lsCRT.h"

#define LS_MATH_IMPLEMENTATION
#define LS_SYM_IMPLEMENTATION
#include "lsSym.h"

#define TESTING_PNG 0
#define TESTING_SYMBOLIC_CALC 1

void main(void)
{
    
#if TESTING_PNG
    PNG image = {};
    char *out = (char *)ls_alloc(image.size);
    ls_loadCompressedPNG("F:\\ProgrammingProjects\\Lowy\\miniature-barnacle\\resources\\container.png", &image);
    ls_Deflate(image.compressedData, image.size, out);
#endif
    
#if TESTING_SYMBOLIC_CALC
    
    sym_expr expr = sym_load("C:\\sym.txt");
    
    sym_result R = sym_solve(expr);
    
#endif
    
    ls_printf("Variable: %c, Value: %f\n", R.variable, R.val);
    return;
}