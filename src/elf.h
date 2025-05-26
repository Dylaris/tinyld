/// ELF structure

#ifndef TINYLD_ELF_H
#define TINYLD_ELF_H

#include "ntype.h"

#define EI_CLASS        4
#define EI_DATA         5
#define EI_VERSION      6
#define EI_OSABI        7
#define EI_ABIVERSION   8
#define EI_PAD          9

#define ELF_MAGIC       "\177ELF"
#define ELFCLASS64      2
#define ELFDATA2LSB     1
#define EV_CURRENT      1

#define ET_NONE         0
#define ET_REL          1
#define ET_EXEC         2
#define ET_DYN          3

#define EM_X86_64       62

typedef struct elf64_header {
    u8  e_ident[16];
    u16 e_type;
    u16 e_machine;
    u32 e_version;
    u64 e_entry;
    u64 e_phoff;
    u64 e_shoff;
    u32 e_flags;
    u16 e_ehsize;
    u16 e_phentsize;
    u16 e_phnum;
    u16 e_shentsize;
    u16 e_shnum;
    u16 e_shstrndx;
} ehdr_t;

typedef struct section_header {
} shdr_t;

typedef struct program_header {
} phdr_t;

#endif // TINYLD_ELF_H
