/// archive file

#include "tinyld.h"

arfile_t *new_arfile(const char *filename)
{
    arfile_t *ar = malloc(sizeof(arfile_t));
    assert(ar != NULL);
    memset(ar, 0, sizeof(arfile_t));

    ar->name = malloc(MAX_PATH_SIZE + 1);
    assert(ar->name != NULL);
    strncpy(ar->name, filename, MAX_PATH_SIZE + 1);
    ar->name[MAX_PATH_SIZE] = '\0';

    fs_loadf(filename, &ar->mf, true);

    return ar;
}

void destroy_arfile(void *arg)
{
    // to be compatible with my 'dyna_destroy'
    arfile_t *ar = arg;
#if 0
    if (ar->name)
        free(ar->name);
    if (ar->phdrs)
        free(ar->phdrs);
    if (ar->shdrs)
        free(ar->shdrs);
#endif
    fs_destroy_mf(&ar->mf);

    *ar = (arfile_t) {0};
}
