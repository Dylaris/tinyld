# tinyld

## Platform
- only support `linux`

## Feature
- only support `static link`

## Usage

```console
$ gcc -o build build.c
$ ./build -c
$ ./build -t
```
## TODO
- parse the symbol in a elf object file
- remove redudant object files from archive file 
- merge sections
- relocation
- output an executable file
