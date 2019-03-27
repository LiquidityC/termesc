project('termesc', 'c')

incdir = include_directories('include')

shared_library('termesc', 'src/termesc.c', include_directories : incdir)
executable('demo', 'src/main.c', 'src/termesc.c', include_directories : incdir)
