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
badd +152 src/mlp.cpp
badd +19 include/nn/mlp.hpp
badd +27 README.md
badd +21 src/logic_gate_xor.cpp
badd +53 CMakeLists.txt
badd +0 fugitive:///home/chanjl/reference/cpp-project.git/worktrees/neural-network//
argglobal
%argdel
$argadd ~/reference/cpp-project.git/neural-network/
edit include/nn/mlp.hpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
split
1wincmd k
wincmd _ | wincmd |
vsplit
1wincmd h
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
exe '1resize ' . ((&lines * 26 + 28) / 57)
exe 'vert 1resize ' . ((&columns * 85 + 102) / 205)
exe '2resize ' . ((&lines * 26 + 28) / 57)
exe 'vert 2resize ' . ((&columns * 119 + 102) / 205)
exe '3resize ' . ((&lines * 27 + 28) / 57)
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
let s:l = 52 - ((24 * winheight(0) + 13) / 26)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 52
normal! 0
lcd ~/reference/cpp-project.git/neural-network
wincmd w
argglobal
if bufexists(fnamemodify("~/reference/cpp-project.git/neural-network/CMakeLists.txt", ":p")) | buffer ~/reference/cpp-project.git/neural-network/CMakeLists.txt | else | edit ~/reference/cpp-project.git/neural-network/CMakeLists.txt | endif
if &buftype ==# 'terminal'
  silent file ~/reference/cpp-project.git/neural-network/CMakeLists.txt
endif
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
let s:l = 2 - ((0 * winheight(0) + 13) / 26)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 2
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
let s:l = 9 - ((8 * winheight(0) + 13) / 27)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 9
normal! 0
lcd ~/reference/cpp-project.git/neural-network
wincmd w
3wincmd w
exe '1resize ' . ((&lines * 26 + 28) / 57)
exe 'vert 1resize ' . ((&columns * 85 + 102) / 205)
exe '2resize ' . ((&lines * 26 + 28) / 57)
exe 'vert 2resize ' . ((&columns * 119 + 102) / 205)
exe '3resize ' . ((&lines * 27 + 28) / 57)
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
nohlsearch
let g:this_session = v:this_session
let g:this_obsession = v:this_session
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
