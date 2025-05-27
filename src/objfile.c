/// object file

#include "tinyld.h"

objfile_t *new_objfile(const char *filename)
{
    objfile_t *obj = malloc(sizeof(objfile_t));
    assert(obj != NULL);
    memset(obj, 0, sizeof(objfile_t));

    obj->name = malloc(MAX_PATH_SIZE + 1);
    assert(obj->name != NULL);
    strncpy(obj->name, filename, MAX_PATH_SIZE + 1);
    obj->name[MAX_PATH_SIZE] = '\0';

    fs_loadf(filename, &obj->mf, true);

    return obj;
}

void destroy_objfile(void *arg)
{
    // to be compatible with my 'dyna_destroy'
    objfile_t *obj = arg;

    if (obj->name)
        free(obj->name);
    if (obj->phdrs)
        free(obj->phdrs);
    if (obj->shdrs)
        free(obj->shdrs);
    fs_destroy_mf(&obj->mf);

    *obj = (objfile_t) {0};
}
