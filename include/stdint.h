#ifndef STDINT_H
#define STDINT_H

#define X86


#define DEFAULT

#ifdef X86
#include "../arch/x86/x86_stdint.h"
#else
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

#endif