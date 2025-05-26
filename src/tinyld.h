#ifndef TINYLD_H
#define TINYLD_H

#define ZD_FS
#define ZD_LOG
#include "zd.h"

#include "ntype.h"
#include "elf.h"

typedef struct object_file {
    ehdr_t ehdr;
    phdr_t *phdrs;
    shdr_t *shdrs;
} objfile_t;

// load.c
void load_elf_file(objfile_t *, const char *);
void dump_elf_header(ehdr_t *);

#endif // TINYLD_H
