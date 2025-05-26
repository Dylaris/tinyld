#include "tinyld.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        log(LOG_FATAL, "give me an input file");

    const char *filename = argv[1];
    mf_t mf = {0};
    fs_loadf(filename, &mf, true);

    objfile_t obj = {0};
    load_elf_file(&obj, mf.content);
    dump_elf_header(&obj.ehdr);

    if (obj.phdrs)
        free(obj.phdrs);
    if (obj.shdrs)
        free(obj.shdrs);
    fs_destroy_mf(&mf);

    return 0;
}
