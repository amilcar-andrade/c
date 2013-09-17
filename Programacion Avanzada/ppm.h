#ifndef _PPM_H_
#define _PPM_H_
#include <stdint.h>

struct rgb{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

typedef struct rgb rgb_t;

struct ppm{
    uint32_t width;
    uint32_t height;
    uint32_t max_value;
	rgb_t * pixeles;
};

typedef struct ppm ppm_t;
enum error_code {Ok, FILE_UNABLE_TO_OPEN, INVALID_FORMAT};
typedef enum error_code error_code_t;

error_code_t ppm_open(const char*, ppm_t*);

#endif