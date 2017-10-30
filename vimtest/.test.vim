let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <C-Space> 
imap <Nul> <C-Space>
inoremap <expr> <Up> pumvisible() ? "\" : "\<Up>"
inoremap <expr> <Down> pumvisible() ? "\" : "\<Down>"
inoremap <silent> <C-Tab> =UltiSnips#ListSnippets()
snoremap <silent>  c
xnoremap <silent> 	 :call UltiSnips#SaveLastVisualSelection()gvs
snoremap <silent> 	 :call UltiSnips#ExpandSnippet()
nnoremap  :CtrlPCurWD
nnoremap <silent>  :CtrlP
snoremap  "_c
nnoremap \d :YcmShowDetailedDiagnostic
noremap \rd :call rtags#Diagnostics()
noremap \rc :call rtags#FindSubClasses()
noremap \rC :call rtags#FindSuperClasses()
noremap \rb :call rtags#JumpBack()
noremap \rv :call rtags#FindVirtuals()
noremap \rw :call rtags#RenameSymbolUnderCursor()
noremap \rl :call rtags#ProjectList()
noremap \rr :call rtags#ReindexFile()
noremap \rs :call rtags#FindSymbols(input("Pattern? ", "", "customlist,rtags#CompleteSymbols"))
noremap \rn :call rtags#FindRefsByName(input("Pattern? ", "", "customlist,rtags#CompleteSymbols"))
noremap \rf :call rtags#FindRefs()
noremap \rp :call rtags#JumpToParent()
noremap \rT :call rtags#JumpTo(g:NEW_TAB)
noremap \rV :call rtags#JumpTo(g:V_SPLIT)
noremap \rS :call rtags#JumpTo(g:H_SPLIT)
noremap \rJ :call rtags#JumpTo(g:SAME_WINDOW, { '--declaration-only' : '' })
noremap \rj :call rtags#JumpTo(g:SAME_WINDOW)
noremap \ri :call rtags#SymbolInfo()
nnoremap \fU :excute 'CtrlPFunky ' . expand('<cword>')
nnoremap \fu :CtrlPFunky
nnoremap \ff :YcmCompleter FixIt
nnoremap \gg :YcmCompleter GoToDeclaration
nnoremap \gf :YcmCompleter GoToDefinition
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
map gd :YcmCompleter GoToDefinitionElseDeclaration
nmap tf :BufExplorer
map zm :WMToggle
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
snoremap <silent> <Del> c
snoremap <silent> <BS> c
snoremap <silent> <C-Tab> :call UltiSnips#ListSnippets()
map <ScrollWheelDown> 
map <ScrollWheelUp> 
nmap <Nul>m :w:silent !rm -f cscope.* tags
nmap <Nul>a <Nul>w <Nul>u
nmap <Nul>u :silent !ctags -R:exec "redraw!"
nmap <Nul>w :silent !cscope -bqR:cs reset:exec "redraw!"
nmap <Nul>o :cs add cscope.out 
nmap <Nul>k :cs kill cscope.out 
nmap <Nul>s :scs find s =expand("<cword>")
inoremap <silent> 	 =UltiSnips#ExpandSnippet()
inoremap <expr> [c-p] pumvisible() ? "\" : "\[c-p]"
inoremap <expr> [c-n] pumvisible() ? "\" : "\[c-n]"
let &cpo=s:cpo_save
unlet s:cpo_save
set background=dark
set backspace=indent,eol,start
set cindent
set completefunc=youcompleteme#Complete
set completeopt=preview,menuone
set cpoptions=aAceFsB
set cscopeprg=/usr/bin/cscope
set cscopetag
set cscopeverbose
set fileencodings=ucs-bom,utf-8,cp936,gb18030,big5,euc-jp,euc-kr,latin1
set guicursor=n-v-c:block-Cursor/lCursor,ve:ver35-Cursor,o:hor50-Cursor,i-ci:ver25-Cursor/lCursor,r-cr:hor20-Cursor/lCursor,sm:block-Cursor-blinkwait175-blinkoff150-blinkon175,a:blinkon0
set helplang=en
set hlsearch
set laststatus=2
set nomodeline
set mouse=nv
set ruler
set runtimepath=~/.vim,~/.vim/bundle/Vundle.vim,~/.vim/bundle/YouCompleteMe,~/.vim/bundle/ctrlp.vim,~/.vim/bundle/ctrlp-funky,~/.vim/bundle/YCM-Generator,~/.vim/bundle/vim-rtags,~/.vim/bundle/ultisnips,~/.vim/bundle/vim-snippets,~/.vim/bundle/tabular,~/.vim/bundle/vim-markdown,~/.vim/bundle/python-vim-instant-markdown,/usr/local/share/vim/vimfiles,/usr/local/share/vim/vim80,/usr/local/share/vim/vimfiles/after,~/.vim/after,~/.vim/bundle/Vundle.vim/after,~/.vim/bundle/YouCompleteMe/after,~/.vim/bundle/ctrlp.vim/after,~/.vim/bundle/ctrlp-funky/after,~/.vim/bundle/YCM-Generator/after,~/.vim/bundle/vim-rtags/after,~/.vim/bundle/ultisnips/after,~/.vim/bundle/vim-snippets/after,~/.vim/bundle/tabular/after,~/.vim/bundle/vim-markdown/after,~/.vim/bundle/python-vim-instant-markdown/after
set shiftwidth=2
set shortmess=filnxtToOc
set tabstop=2
set updatetime=100
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/common_test/vimtest
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +1 t1.c
badd +1 t1.h
badd +1 t2.c
badd +1 t2.h
argglobal
silent! argdel *
edit t2.h
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winminheight=1 winheight=1 winminwidth=1 winwidth=1
argglobal
setlocal keymap=
setlocal noarabic
setlocal noautoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal concealcursor=
setlocal conceallevel=0
setlocal completefunc=youcompleteme#Complete
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
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal fixendofline
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
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=2
setlocal imsearch=2
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=bin,octal,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=2
setlocal noshortname
setlocal signcolumn=auto
setlocal nosmartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=2
setlocal tagcase=
setlocal tags=
setlocal textwidth=0
setlocal thesaurus=
setlocal noundofile
setlocal undolevels=-123456
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 22) / 45)
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
set winheight=1 winwidth=20 shortmess=filnxtToOc
set winminheight=1 winminwidth=1
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
