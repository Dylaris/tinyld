#include "tinyld.h"

static void define_rule(cmdl_t *cmdl)
{
    cmdl_define(cmdl, OPTT_SINGLE_ARG, NULL, "o", NULL);
    cmdl_define(cmdl, OPTT_SINGLE_ARG, NULL, "l", NULL);
    cmdl_define(cmdl, OPTT_SINGLE_ARG, NULL, "L", NULL);
}

static void get_all_objfiles(cmdl_t *cmdl, dyna_t *objfiles)
{
    // single object file
    cmdlopt_t *opt_o = cmdl_getopt(cmdl, "o");

    for (size_t i = 0; i < opt_o->pargs.count; i++) {
        string_t *objname = dyna_get(&opt_o->pargs, i);
        mf_t mf = {0};
        fs_loadf(objname->base, &mf, true);

        objfile_t *obj = new_objfile(mf.name, NULL, mf.content, mf.size);
        dyna_append(objfiles, obj);

        fs_destroy_mf(&mf);
    }

    // archive file (library)
    cmdlopt_t *opt_l = cmdl_getopt(cmdl, "l");
    cmdlopt_t *opt_L = cmdl_getopt(cmdl, "L");

    char path[MAX_PATH_SIZE];

    for (size_t i = 0; i < opt_l->vals.count; i++) {
        string_t *file = dyna_get(&opt_l->vals, i);
        for (size_t j = 0; j < opt_L->vals.count; j++) {
            string_t *dir = dyna_get(&opt_L->vals, j);
            snprintf(path, sizeof(path), "%s/lib%s.a", dir->base, file->base);
            if (fs_typeof(path) == FT_NOET)
                continue;
            mf_t mf = {0};
            fs_loadf(path, &mf, true);

            printf("%s\n", path);
    
            arfile_t *ar = new_arfile(mf.name, mf.content, mf.size);
            load_ar_file(ar, objfiles);
            destroy_arfile(ar);

            fs_destroy_mf(&mf);

            break;
        }
    }

    // fill the elf struct for each object file
    printf("object file count: %zu\n", objfiles->count);
    for (size_t i = 0; i < objfiles->count; i++) {
        objfile_t *obj = dyna_get(objfiles, i);
        load_elf_file(obj);
    }
}

int main(int argc, char **argv)
{
    cmdl_t cmdl = {0};
    cmdl_init(&cmdl, true);

    define_rule(&cmdl);
    cmdl_build(&cmdl, argc, argv);

    dyna_t objfiles = {0};
    dyna_init(&objfiles, sizeof(objfile_t), destroy_objfile);

    get_all_objfiles(&cmdl, &objfiles);

    dyna_destroy(&objfiles);
    cmdl_destroy(&cmdl);

    return 0;
}
