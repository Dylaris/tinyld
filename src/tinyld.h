#ifndef TINYLD_H
#define TINYLD_H

#define ZD_FS
#define ZD_LOG
#include "zd.h"

#include "ntype.h"
#include "elf.h"

// load.c
void load_elf_file(ehdr_t *, const char *);
void dump_elf_header(ehdr_t *);

#endif // TINYLD_H
