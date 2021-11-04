#ifndef COMMON_H
#define COMMON_H

#ifdef __sgi
#define TRAP_IF(cond)
#else
#include <assert.h>
#define TRAP_IF(cond) assert(!(cond))
#endif

#ifdef __sgi
typedef unsigned char bool;
#define true 1
#define false 0
#else
#include <stdbool.h>
#endif

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Set bits [start..end) in a 64-bit word to ones (bit with index 0 is the msb)
#define GENMASK(start, end) ((((MAX((long long int)(start), 0LL) - MIN((long long int)(end), 64LL)) >> 63) << ((MAX((start), 0) - MIN((end), 64)) & 63)) >> MAX((start), 0))

//#define GETBIT32(value, index) ((int)(((unsigned int)(value) & -((unsigned int)(index) < 32)) << ((index) & 31)) < 0)
#define GETBIT32(value, index) ((unsigned int)(index) < 32 && ((value) & (1U << (31 - (index)))))

/*
 * Byte swaps for word and half words.
 */
#define swap_word(a) ( ((a) << 24) | \
		      (((a) << 8) & 0x00ff0000) | \
		      (((a) >> 8) & 0x0000ff00) | \
	((unsigned int)(a) >>24) )

#define swap_half(a) ( ((a & 0xff) << 8) | ((unsigned short)(a) >> 8) )

#endif
