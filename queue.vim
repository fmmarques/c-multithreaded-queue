let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
map! <S-Insert> <MiddleMouse>
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
map <S-Insert> <MiddleMouse>
map º :tabn
map ç :tabp
let &cpo=s:cpo_save
unlet s:cpo_save
set background=dark
set backspace=indent,eol,start
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=pt
set history=50
set iminsert=0
set imsearch=0
set nomodeline
set mouse=a
set printoptions=paper:a4
set ruler
set runtimepath=~/.vim,/var/lib/vim/addons,/usr/share/vim/vimfiles,/usr/share/vim/vim74,/usr/share/vim/vimfiles/after,/var/lib/vim/addons/after,~/.vim/after
set softtabstop=2
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set tags=tags
set termencoding=utf-8
set window=57
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/src/queue
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/hive2_GPU_queue.vim
badd +23 ~/src/alien-armada/main.cpp
badd +18 ~/src/alien-armada/include/logic/game.h
badd +10 ~/src/alien-armada/include/logic/state.h
badd +11 ~/src/alien-armada/include/logic/game/state.h
badd +3 ~/.vimrc
badd +224 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/hive.h
badd +231 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/hive.cc
badd +61 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/frame_calc.h
badd +518 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/frame_calc.cpp
badd +192 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/part4.cl
badd +11 ~/src/image-processing-on-gpu-clusters/.gitignore
badd +103 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/part3.cl
badd +67 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/frame.h
badd +118 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/frame.cc
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/histogram.h
badd +13 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/workqueue.h
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/sbdxml_encoder.h
badd +88 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/sbdxml_encoder.cc
badd +19 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/sbd_vidprocess.h
badd +171 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/sbd_vidprocess.cc
badd +328 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/videoprocessing.cpp
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/.gitignore
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/part4.mod.cl
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/vidprocess.h
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/vidprocess.cc
badd +34 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/VidProcessNode.cpp
badd +6 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/options.h
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/results.txt
badd +316 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/mpeg_decoder.cc
badd +169 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/CMakeLists.txt
badd +1 /tmp/data
badd +85 /tmp/148.modified.csv
badd +1 /tmp/148.original-modified.diff
badd +81 /tmp/148.original.csv
badd +278 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/part6.cl
badd +1 /tmp/1555.original-modified.diff
badd +46 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/scripts/test_integrity.sh
badd +1 /tmp/150.original-modified.diff
badd +1 /tmp/151.original-modified.diff
badd +242 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/part9.cl
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/decoder.cc
badd +16 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/ProcessingNode.h
badd +18 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/decoder.h
badd +1 /tmp/1.original-modified.diff
badd +28 /tmp/1.original.csv
badd +6 /tmp/1.modified.csv
badd +79 /tmp/199.original.csv
badd +1 /tmp/199.modified.csv
badd +17 /tmp/1.original-modified.join
badd +1 /tmp/0.original.csv
badd +2 /tmp/0.modified.csv
badd +1 /tmp/0.original-modified.join
badd +184 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/part5.cl
badd +235 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/part8.cl
badd +107 ~/src/testing_ground/pixel_processing.cpp
badd +1 /tmp/2.original.csv
badd +75 aux/pixel_processing.cpp
badd +1 /tmp/2.modified.csv
badd +1 /tmp/au
badd +1 /tmp/0.original-modified.diff
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/bug_tracker.txt
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/scripts/process_library.sh
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/tests/integration/integrity.cpp
badd +223 /opt/cmake-3.7.2/share/cmake-3.7/Modules/FindMPI.cmake
badd +24 /opt/cmake-3.7.2/share/cmake-3.7/Modules/FindZLIB.cmake
badd +45 /opt/cmake-3.7.2/share/cmake-3.7/Modules/FindBoost.cmake
badd +12 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/cmake/FindFFMPEG.cmake
badd +29 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/cmake/FindAVUtil.cmake
badd +30 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/cmake/FindAVCodec.cmake
badd +38 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/cmake/FindAVFormat.cmake
badd +9 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/cmake/Findx265.cmake
badd +21 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/cmake/Findmp3lame.cmake
badd +20 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/cmake/Findopus.cmake
badd +22 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/cmake/Findvorbis.cmake
badd +9 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/cmake/Findvorbisenc.cmake
badd +88 ~/src/lainnovatis/lainnovatis_backend/lainnovatis/model.py
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/tests/unit/src/frame.cpp
badd +8 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/tests/unit/include/frame.h
badd +5 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/tests/integration/include/integrity.h
badd +16 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/tests/unit/src/test_frame.cpp
badd +12 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/tests/unit/include/test_frame.h
badd +108 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/tests/integration/src/integrity.cpp
badd +6 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/tests/unit/unit.cpp
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/tests/integration/src/main.cpp
badd +6 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/tests/unit/src/main.cpp
badd +0 CMakeLists.txt
silent! argdel *
edit CMakeLists.txt
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal keymap=
setlocal noarabic
setlocal noautoindent
setlocal balloonexpr=
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal nocindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=s1:/*,mb:*,ex:*/,://,b:#,:%,:XCOMM,n:>,fb:-
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal concealcursor=
setlocal conceallevel=0
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'cmake'
setlocal filetype=cmake
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=tcq
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=0
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=octal,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=8
setlocal noshortname
setlocal nosmartindent
setlocal softtabstop=2
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'cmake'
setlocal syntax=cmake
endif
setlocal tabstop=8
setlocal tags=
setlocal textwidth=0
setlocal thesaurus=
setlocal noundofile
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 28) / 57)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
tabnext 1
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
