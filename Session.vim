let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/reference/cpp-project.git/neural-network
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +112 src/mlp.cpp
badd +34 include/nn/mlp.hpp
badd +25 CMakeLists.txt
badd +27 README.md
badd +1 fugitive:///home/chanjl/reference/cpp-project.git/worktrees/neural-network//
badd +1 src/logic_gate_or.cpp
badd +1 ~/reference/cpp-project.git/worktrees/neural-network/COMMIT_EDITMSG
argglobal
%argdel
$argadd ./
edit src/logic_gate_or.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
2wincmd k
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd w
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
wincmd =
argglobal
balt README.md
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 3 - ((2 * winheight(0) + 12) / 25)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 3
normal! 0
lcd ~/reference/cpp-project.git/neural-network
wincmd w
argglobal
if bufexists(fnamemodify("~/reference/cpp-project.git/neural-network/include/nn/mlp.hpp", ":p")) | buffer ~/reference/cpp-project.git/neural-network/include/nn/mlp.hpp | else | edit ~/reference/cpp-project.git/neural-network/include/nn/mlp.hpp | endif
if &buftype ==# 'terminal'
  silent file ~/reference/cpp-project.git/neural-network/include/nn/mlp.hpp
endif
balt ~/reference/cpp-project.git/neural-network/src/mlp.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 11 - ((5 * winheight(0) + 12) / 25)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 11
normal! 0
lcd ~/reference/cpp-project.git/neural-network
wincmd w
argglobal
if bufexists(fnamemodify("fugitive:///home/chanjl/reference/cpp-project.git/worktrees/neural-network//", ":p")) | buffer fugitive:///home/chanjl/reference/cpp-project.git/worktrees/neural-network// | else | edit fugitive:///home/chanjl/reference/cpp-project.git/worktrees/neural-network// | endif
if &buftype ==# 'terminal'
  silent file fugitive:///home/chanjl/reference/cpp-project.git/worktrees/neural-network//
endif
balt ~/reference/cpp-project.git/neural-network/README.md
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker=<<<<<<<<,>>>>>>>>
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 9 - ((8 * winheight(0) + 6) / 12)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 9
normal! 0
lcd ~/reference/cpp-project.git/neural-network
wincmd w
argglobal
if bufexists(fnamemodify("~/reference/cpp-project.git/worktrees/neural-network/COMMIT_EDITMSG", ":p")) | buffer ~/reference/cpp-project.git/worktrees/neural-network/COMMIT_EDITMSG | else | edit ~/reference/cpp-project.git/worktrees/neural-network/COMMIT_EDITMSG | endif
if &buftype ==# 'terminal'
  silent file ~/reference/cpp-project.git/worktrees/neural-network/COMMIT_EDITMSG
endif
balt ~/reference/cpp-project.git/neural-network/README.md
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 1 - ((0 * winheight(0) + 6) / 13)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
lcd ~/reference/cpp-project.git/neural-network
wincmd w
4wincmd w
wincmd =
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
let g:this_session = v:this_session
let g:this_obsession = v:this_session
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
