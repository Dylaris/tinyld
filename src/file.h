/// Some well-defined structure for specific file

#ifndef TINYLD_FILE_H
#define TINYLD_FILE_H

#include "ntype.h"

// ELF file

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

#define SHT_PROGBITS    1
#define SHT_SYMTAB      2
#define SHT_STRTAB      3
#define SHT_RELA        4
#define SHT_DYNAMIC     6
#define SHT_REL         9
#define SHT_DYNSYM      11

#define SHF_WRITE       (1 << 0)
#define SHF_ALLOC       (1 << 1)
#define SHF_EXECINSTR   (1 << 2)

typedef struct section_header {
    u32 sh_name;
    u32 sh_type;
    u64 sh_flags;
    u64 sh_addr;
    u64 sh_offset;
    u64 sh_size;
    u32 sh_link;
    u32 sh_info;
    u64 sh_addralign;
    u64 sh_entsize;
} shdr_t;

#define PT_LOAD     1
#define PT_DYNAMIC  2
#define PT_INTERP   3
#define PT_PHDR     6

#define PF_X (1 << 0)
#define PF_W (1 << 1)
#define PF_R (1 << 2)

typedef struct program_header {
    u32 p_type;
    u32 p_flags;
    u64 p_offset;
    u64 p_vaddr;
    u64 p_paddr;
    u64 p_filesz;
    u64 p_memsz;
    u64 p_align;
} phdr_t;

// symbol binding
#define STB_LOCAL   0
#define STB_GLOBAL  1
#define STB_WEAK    2

// symbol type
#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_COMMON  5
#define STT_TLS     6

typedef struct symbol {
    u32 st_name;
    u8  st_info;
    u8  st_other;
    u16 st_shndx;
    u64 st_value;
    u64 st_size;
} sym_t;

// Archive file

#define AR_MAGIC    "!<arch>\n"
#define AR_STRTAB   "// "
#define AR_SYMTAB1  "/ "
#define AR_SYMTAB2  "/SYM64/ "

//          <<< 2 bytes aligned >>>
//
// !<arch>\n[ section ][ section ]...[ section ]
// section => [ahdr_t] [ ... ]
//                        ^
//                  obj file content

typedef struct archive_header {
    u8 a_name[16];
    u8 a_date[12];
    u8 a_uid[6];
    u8 a_gid[6];
    u8 a_mode[8];
    u8 a_size[10];
    u8 a_fmag[2];
} ahdr_t;

#endif // TINYLD_FILE_H
