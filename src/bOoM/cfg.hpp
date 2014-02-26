#ifndef HEADERBOOM_cfg
#define HEADERBOOM_cfg

#include <iostream>
#define PRINT_EXPR(...) (std::cout << (#__VA_ARGS__) << " : " << (__VA_ARGS__) << std::endl)
#define PRINT_STATEMENT(...) {std::cout << (#__VA_ARGS__) << " : statement" << std::endl; {__VA_ARGS__}; }
#define PRINT(...) (std::cout << (__VA_ARGS__) << std::endl)
#define STREAM_EXPR(...) (#__VA_ARGS__) << " : " << (__VA_ARGS__)
#define STREAM(...) (__VA_ARGS__)

#endif


