#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *s);

//int atoi(const char *s);

void uint16toa(uint16_t i, char *s, int len);

void int16toa(int16_t i, char *s, int len);

void uint32toa(uint32_t i, char *s, int len);

void memset(void *s, int c, size_t n);

#endif
