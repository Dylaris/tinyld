#include "tinyld.h"

static bool check_magic(u8 *magic)
{
    char buf[5];
    memcpy(buf, magic, sizeof(buf));
    buf[4] = '\0';

    if (strcmp(buf, ELF_MAGIC) != 0)
        return false;
    return true;
}

static bool check_class(u8 class)
{
    if (class != ELFCLASS64)
        return false;
    return true;
}

static bool check_endian(u8 endian)
{
    if (endian != ELFDATA2LSB)
        return false;
    return true;
}

void dump_elf_header(ehdr_t *ehdr)
{
    log(LOG_INFO, "ELF HEADER");

    printf("%-10s %u '%c' '%c' '%c'\n", "Magic", ehdr->e_ident[0],
        ehdr->e_ident[1], ehdr->e_ident[2], ehdr->e_ident[3]);
    printf("%-10s %u\n", "Class", ehdr->e_ident[EI_CLASS]);
    printf("%-10s %u\n", "Endian", ehdr->e_ident[EI_DATA]);
    printf("%-10s %u\n", "ELF -v", ehdr->e_ident[EI_VERSION]);
    printf("%-10s %u\n", "OS ABI", ehdr->e_ident[EI_OSABI]);
    printf("%-10s %u\n", "ABI -v", ehdr->e_ident[EI_ABIVERSION]);
}

void load_elf_file(ehdr_t *ehdr, const char *buf)
{
    *ehdr = *(ehdr_t *) buf;

    if (!check_magic(ehdr->e_ident))
        log(LOG_FATAL, "not a valid ELF file");

    if (!check_class(ehdr->e_ident[EI_CLASS]))
        log(LOG_FATAL, "only support 64 bit");

    if (!check_endian(ehdr->e_ident[EI_DATA]))
        log(LOG_FATAL, "only support little endian");
}

