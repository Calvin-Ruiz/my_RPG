Configuration files were made for mods implementations, except for "settings.conf".
There is no warranty if you done any change except those indicated in "settings.conf".
Note that commands works exactly like config files instructions, so there is no warranty about command use.

If you really want to build your config files, this is the minimal bases :

There is 3 kinds of files :
config.init -> configuration file to initialize everything needed by .func and .conf (like local variables)
.conf -> configuration file executed after defining all functions
.func -> function file, builded after config.init and before .conf files

Functions :
- call filename arg1 arg2 arg3 - call filename.func function with arguments
- @1 is replaced by arg1 inside filename.func

Arguments :
- @ : replace by the corresponding argument (only inside .func files)
- $ : replace by the corresponding object
- = : interprete as a number
- & : replace by the corresponding command
- { : replace by a pointer to psuedo-structure

Sub-arguments :
- Use '.' as separator (e.g. : $texture.player)
- Use '+' for raw moving (e.g. : $Player.[0].pos.+16)
- Use '[' for moving inside pointer and unreference it (like in C with void **) (e.g. : $entitylist.[3])
- Use '$' for a position inside linked list (e.g. : $entitylist.[3].$3)
- Use '@struct_type.key' for cast to structure and move to key position (not unreferenced)

