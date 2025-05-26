#include "tinyld.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        log(LOG_FATAL, "give me an input file");

    const char *filename = argv[1];
    mf_t mf = {0};
    fs_loadf(filename, &mf, true);

    ehdr_t ehdr = {0};
    load_elf_file(&ehdr, mf.content);
    dump_elf_header(&ehdr);

    fs_destroy_mf(&mf);

    return 0;
}
