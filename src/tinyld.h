#ifndef TINYLD_H
#define TINYLD_H

#define ZD_FS
#define ZD_LOG
#define ZD_DS_DYNAMIC_ARRAY
#define ZD_COMMAND_LINE
#include "zd.h"

#include "ntype.h"
#include "elf.h"

#define MAX_PATH_SIZE 255

// objfile.c
typedef struct object_file {
    char *name;
    mf_t mf;
    ehdr_t ehdr;
    phdr_t *phdrs;
    shdr_t *shdrs;
} objfile_t;

objfile_t *new_objfile(const char *);
void destroy_objfile(void *);

// arfile.c
typedef struct archive_file {
    char *name;
    mf_t mf;
} arfile_t;

arfile_t *new_arfile(const char *filename);
void destroy_arfile(void *);

// load.c
void load_elf_file(objfile_t *);
void load_ar_file(arfile_t *);

#endif // TINYLD_H
