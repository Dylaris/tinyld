/// object file

#include "tinyld.h"

objfile_t *new_objfile(const char *filename, 
        const char *parent, char *buf, size_t size)
{
    objfile_t *obj = malloc(sizeof(objfile_t));
    assert(obj != NULL);
    memset(obj, 0, sizeof(objfile_t));

    if (filename) {
        obj->name = malloc(MAX_PATH_SIZE + 1);
        assert(obj->name != NULL);
        strncpy(obj->name, filename, MAX_PATH_SIZE + 1);
        obj->name[MAX_PATH_SIZE] = '\0';
    }

    if (parent) {
        obj->parent = malloc(MAX_PATH_SIZE + 1);
        assert(obj->parent != NULL);
        strncpy(obj->parent, parent, MAX_PATH_SIZE + 1);
        obj->parent[MAX_PATH_SIZE] = '\0';
    }

    if (buf) {
        obj->content = malloc(size + 1);
        assert(obj->content != NULL);
        memcpy(obj->content, buf, size);
        obj->content[size] = '\0';
    }

    return obj;
}

void destroy_objfile(void *arg)
{
    // to be compatible with my 'dyna_destroy'
    objfile_t *obj = arg;

    if (obj->name)
        free(obj->name);
    if (obj->parent)
        free(obj->parent);
    if (obj->content)
        free(obj->content);
    if (obj->phdrs)
        free(obj->phdrs);
    if (obj->shdrs)
        free(obj->shdrs);

    *obj = (objfile_t) {0};
}
