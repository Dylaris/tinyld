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

    printf("%-15s %u '%c' '%c' '%c'\n", "Magic", ehdr->e_ident[0],
        ehdr->e_ident[1], ehdr->e_ident[2], ehdr->e_ident[3]);
    printf("%-15s %u\n", "Class", ehdr->e_ident[EI_CLASS]);
    printf("%-15s %u\n", "Endian", ehdr->e_ident[EI_DATA]);
    printf("%-15s %u\n", "ELF -v", ehdr->e_ident[EI_VERSION]);
    printf("%-15s %u\n", "OS ABI", ehdr->e_ident[EI_OSABI]);
    printf("%-15s %u\n", "ABI -v", ehdr->e_ident[EI_ABIVERSION]);
    printf("%-15s %u\n", "Type", ehdr->e_type);
    printf("%-15s %u\n", "Version", ehdr->e_version);
    printf("%-15s 0x%lx\n", "Entry point", ehdr->e_entry);
    printf("%-15s %lu\n", "PH offset", ehdr->e_phoff);
    printf("%-15s %lu\n", "SH offset", ehdr->e_shoff);
    printf("%-15s %u\n", "Flags", ehdr->e_flags);
    printf("%-15s %u\n", "EH size", ehdr->e_ehsize);
    printf("%-15s %u\n", "PHE size", ehdr->e_phentsize);
    printf("%-15s %u\n", "PHE num", ehdr->e_phnum);
    printf("%-15s %u\n", "SHE size", ehdr->e_shentsize);
    printf("%-15s %u\n", "SHE num", ehdr->e_shnum);
    printf("%-15s %u\n", "SHSTR idx", ehdr->e_shstrndx);
}

static void load_elf_header(objfile_t *obj, const char *start)
{
    obj->ehdr = *(ehdr_t *) start;

    if (!check_magic(obj->ehdr.e_ident))
        log(LOG_FATAL, "not a valid ELF file");

    if (!check_class(obj->ehdr.e_ident[EI_CLASS]))
        log(LOG_FATAL, "only support 64 bit");

    if (!check_endian(obj->ehdr.e_ident[EI_DATA]))
        log(LOG_FATAL, "only support little endian");
}

static void load_section_headers(objfile_t *obj, const char *start)
{
    u16 num_sh = obj->ehdr.e_shnum;

    for (u16 i = 0; i < num_sh; i++)
        obj->shdrs[i] = *(shdr_t *) (start + sizeof(shdr_t)*i);
}

static void load_program_headers(objfile_t *obj, const char *start)
{
    u16 num_ph = obj->ehdr.e_phnum;

    for (u16 i = 0; i < num_ph; i++)
        obj->phdrs[i] = *(phdr_t *) (start + sizeof(phdr_t)*i);
}

void load_elf_file(objfile_t *obj, const char *buf)
{
    load_elf_header(obj, buf);

    obj->phdrs = malloc(sizeof(phdr_t) * obj->ehdr.e_phnum);
    assert(obj->phdrs != NULL);
    obj->shdrs = malloc(sizeof(shdr_t) * obj->ehdr.e_shnum);
    assert(obj->shdrs != NULL);

    load_section_headers(obj, buf + obj->ehdr.e_shoff);
    load_program_headers(obj, buf + obj->ehdr.e_phoff);

#if 0
    for (u16 i = 0; i < obj->ehdr.e_shnum; i++)
        printf("name: %s\n", buf 
                             + obj->shdrs[obj->ehdr.e_shstrndx].sh_offset
                             + obj->shdrs[i].sh_name);

    for (u16 i = 0; i < obj->ehdr.e_phnum; i++)
        printf("vaddr: 0x%lx\n", obj->phdrs[i].p_vaddr); 
#endif
}

