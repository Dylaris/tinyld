#define ZD_IMPLEMENTATION
#define ZD_BUILD
#include "zd.h"

#define TARGET  "tinyld"
#define SRC_DIR "src"
#define CC      "gcc"

void compile(void)
{
    builder_t builder;
    build_init(&builder);

    cmd_t cmd = {0};
    cmd_init(&cmd);
    cmd_append_arg(&cmd, CC);
    cmd_append_arg(&cmd, "-Wall", "-Wextra", "-Wno-unused-function");
    cmd_append_arg(&cmd, "-I", SRC_DIR, "-I", ".");
    cmd_append_arg(&cmd, "-o", TARGET);

    md_t md = {0};
    fs_loadd(SRC_DIR, &md);

    for (size_t i = 0; i < md.f_cnt; i++) {
        if (!wildcard_match(md.files[i], "*.c"))
            continue;

        string_t cfile = {0};        
        string_append(&cfile, "%s/%s", SRC_DIR, md.files[i]);
        cmd_append_arg(&cmd, cfile.base);
        string_destroy(&cfile);
    }
    cmd_append_arg(&cmd, "-lm");

    build_append_cmd(&builder, &cmd);

    build_run_sync(&builder);

    fs_destroy_md(&md);
    build_destroy(&builder);
}

void clean(void)
{
    fs_remove(TARGET);
}

void test(void)
{
    cmd_t cmd = {0};
    cmd_init(&cmd);

    cmd_append_arg(&cmd, CC);
    cmd_append_arg(&cmd, "-static");
    cmd_append_arg(&cmd, "-B", ".");
    cmd_append_arg(&cmd, "-o", "test/hello", "test/hello.c");

    cmd_run(&cmd);

    cmd_destroy(&cmd);
}

void define_rule(cmdl_t *cmdl)
{
    cmdl_define(cmdl, OPTT_NO_ARG, "help", "h", "Display help information");
    cmdl_define(cmdl, OPTT_NO_ARG, "compile", "c", "Compile all files");
    cmdl_define(cmdl, OPTT_NO_ARG, "clean", "cl", "Clean all generated files");
    cmdl_define(cmdl, OPTT_NO_ARG, "test", "t", "Test 'tinyld'");
}

int main(int argc, char **argv)
{
    cmdl_t cmdl;
    cmdl_init(&cmdl, false);

    define_rule(&cmdl);

    cmdl_build(&cmdl, argc, argv);

    bool is_help    = cmdl_isuse(&cmdl, "help");
    bool is_compile = cmdl_isuse(&cmdl, "compile");
    bool is_clean   = cmdl_isuse(&cmdl, "clean");
    bool is_test   = cmdl_isuse(&cmdl, "test");

    if (is_compile)
        compile();
    else if (is_clean)
        clean();
    else if (is_help)
        cmdl_usage(&cmdl);
    else if (is_test)
        test();

    cmdl_destroy(&cmdl);

    return 0;
}
