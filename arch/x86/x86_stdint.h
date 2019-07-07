#ifndef X86_STDINT_H
#define X86_STDINT_H

#define UINT_MAX 0xffffffff

#define INT_MAX  0x7fffffff
#define INT_MIN  0x80000000

typedef signed char    int8_t;
typedef unsigned char  uint8_t;

typedef signed short   int16_t;
typedef unsigned short uint16_t;

typedef int            int32_t;
typedef unsigned int   uint32_t;

typedef long           int64_t;
typedef unsigned long  uint64_t; 

typedef uint64_t       size_t;

#endif