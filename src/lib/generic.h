#pragma once

/* Copyright © 2010 Lukas Martini, Christoph Sünderhauf
 * Copyright © 2011 Lukas Martini
 *
 * This file is part of Xelix.
 *
 * Xelix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Xelix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Xelix.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdconf.h"

#define GCC_VERSION (__GNUC__ * 10000 \
                               + __GNUC_MINOR__ * 100 \
                               + __GNUC_PATCHLEVEL__)

#define isdigit(C) ((C) >= '0' && (C) <= '9')
#define DUMPVAR(C,D) printf("%%dumpvar: %s="C" at %s:%d%%\n", 0x02, #D, D, __FILE__, __LINE__);
#define DUMPVARS(D) DUMPVAR("%s", #D);
#define DUMPVARC(D) DUMPVAR("%c", #D);
#define DUMPVARD(D) DUMPVAR("%d", #D);
#define DUMPVARX(D) DUMPVAR("0x%x", #D);

// Typedefs
typedef unsigned long uint64;
typedef signed long sint64;
typedef unsigned int uint32;
typedef signed int sint32;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned char uint8;
typedef signed char sint8;

typedef long int time_t;
typedef long int size_t;
typedef uint8 byte;

typedef enum { false = 0 , true = 1 } bool;

#define NULL  0
#define EOF  -1

//typedef int bool;
//#define true  1
//#define false 0

bool schedulingEnabled;
#define SPAWN_FUNCTION process_create
#define SPAWN_FUNCTION_N "process_create" //fixme

// Port I/O so that we don't always have to use assembler
void outb(uint16 port, uint8 value);
void outw(uint16 port, uint16 value);
uint8 inb(uint16 port);
uint8 readCMOS (uint16 port);
void writeCMOS (uint16 port, uint8 value);
bool init_haveGrub;

// fills size bytes of memory starting at ptr with the byte fill.
void memset(void* ptr, uint8 fill, uint32 size);
// copies size bytes of memory from src to dest
void memcpy(void* dest, void* src, uint32 size); 
//Itoa
char *itoa (int num, int base);

// Printing
void print(char* s);
void vprintf(const char *fmt, void **arg);
void printf(const char *fmt, ...);

extern void display_clear();
#define display_clear() clear()

// Freeze
void freeze(void);

// Don't use this one, use the macros below.
void panic_raw(char *file, uint32 line, int assertionf, const char *reason, ...);

// to automatically have file names and line numbers
#define panic(...) panic_raw( __FILE__, __LINE__, 0, __VA_ARGS__);
#define assert(b) ((b) ? (void)0 : panic_raw(__FILE__, __LINE__, 1, #b))

// Misc
int (memcmp)(const void *s1, const void *s2, size_t n);
void reboot(); // to be moved later when the halting process becomes more complicated ;)