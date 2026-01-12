" Set the path option for when NO files are loaded.
" This is also supposed to always exist no matter what
" filetype is currently in effect.
"
" NOTE: We don't need to use setlocal here since this
"       is supposed to be 'global'.
set path=.,,MathLib/lib/include/**,MathLib/Tests/**

" Add a local .vim directory for adding project-level filetype
" behavior.
set rtp+=.vim

set number
