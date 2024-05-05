#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int main()
{
    int32_t a = INT32_MAX;
    double b = 214748365.0;
    
    int32_t c = (int32_t)(2362232012.8000002); // saturation
    int32_t d = (int32_t)(2362232012);         // overflow
    
    int32_t e = (int32_t)((double)INT32_MAX + 214748365); // saturation [INT32_MAX]
    int32_t f = (int32_t)(INT32_MAX + 214748365);         // overflow
    int32_t g = (int32_t)(INT32_MAX + 214748365.0);       // saturation [INT32_MAX]
    
    int32_t h = (int32_t)((double)a + 214748365); // saturation [INT32_MIN]
    int32_t i = (int32_t)(a + 214748365);         // overflow
    int32_t k = (int32_t)(a + 214748365.0);       // saturation [INT32_MIN]
    int32_t l = (int32_t)(a + b);                 // saturation [INT32_MIN]
    
    return 0;
}