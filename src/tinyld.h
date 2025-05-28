#ifndef TINYLD_H
#define TINYLD_H

#define ZD_FS
#define ZD_LOG
#define ZD_DS_DYNAMIC_ARRAY
#define ZD_COMMAND_LINE
#include "zd.h"

#include "ntype.h"
#include "file.h"

#define MAX_PATH_SIZE 255

// objfile.c
typedef struct object_file {
    char *name;
    char *parent;
    char *content;
    ehdr_t ehdr;
    phdr_t *phdrs;
    shdr_t *shdrs;
} objfile_t;

objfile_t *new_objfile(const char *, const char *, char *, size_t);
void destroy_objfile(void *);

// arfile.c
typedef struct archive_file {
    char *name;
    char *content;
    size_t size;
} arfile_t;

arfile_t *new_arfile(const char *, char *, size_t);
void destroy_arfile(void *);

// load.c
void load_elf_file(objfile_t *);
void load_ar_file(arfile_t *, dyna_t *);

#endif // TINYLD_H
