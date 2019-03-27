au FileType c setl makeprg=ninja\ -C\ build
au FileType h setl makeprg=ninja\ -C\ build

nnoremap <F1> :Make<cr>

packadd termdebug
let g:termdebug_wide = 1
let g:syntastic_c_include_dirs = [ 'include' ]
