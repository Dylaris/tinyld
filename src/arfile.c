/// archive file

#include "tinyld.h"

arfile_t *new_arfile(const char *filename, char *buf, size_t size)
{
    arfile_t *ar = malloc(sizeof(arfile_t));
    assert(ar != NULL);
    memset(ar, 0, sizeof(arfile_t));

    if (filename) {
        ar->name = malloc(MAX_PATH_SIZE + 1);
        assert(ar->name != NULL);
        strncpy(ar->name, filename, MAX_PATH_SIZE + 1);
        ar->name[MAX_PATH_SIZE] = '\0';
    }

    if (buf) {
        ar->content = malloc(size + 1);
        assert(ar->content != NULL);
        memcpy(ar->content, buf, size + 1);
        ar->content[size] = '\0';
    }

    ar->size = size;

    return ar;
}

void destroy_arfile(void *arg)
{
    // to be compatible with my 'dyna_destroy'
    arfile_t *ar = arg;

    if (ar->name)
        free(ar->name);
    if (ar->content)
        free(ar->content);

    *ar = (arfile_t) {0};
}
