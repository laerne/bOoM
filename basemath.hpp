#ifndef H_basemath
#define H_basemath

#include <cmath>
typedef float real;

#ifndef MAX
#define MAX(a,b) ((a)>=(b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b) ((a)<=(b) ? (a) : (b))
#endif

#ifndef ABS
#define ABS(x) ((x)>0 ? (x) : -(x))
#endif

#ifndef SQ
#define SQ(x) ((x)*(x))
#endif

#endif

