if filereadable(expand("~/.vimrc.bundles"))
  source ~/.vimrc.bundles
endif

"=================================================================
" 安裝相關軟體，Vundle和airline字型
"=================================================================
"sudo apt-get install exuberant-ctags cscope vim-gtk git
"git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
"git clone https://github.com/powerline/fonts
"cd fonts && ./install.sh
" 剪貼下面的文字並放到 ~/.vimrc

"=================================================================
" Start vundle
"=================================================================
set nocompatible              " be iMproved, required
filetype off                  " required


"====================================================================
"编码设置
"====================================================================
"Vim 在与屏幕/键盘交互时使用的编码(取决于实际的终端的设定)
set encoding=utf-8
set langmenu=zh_CN.UTF-8
" 设置打开文件的编码格式
set fileencodings=ucs-bom,utf-8,cp936,gb18030,big5,euc-jp,euc-kr,latin1,gbk,gb2312
set fileencoding=utf-8
"解决菜单乱码
source $VIMRUNTIME/delmenu.vim
source $VIMRUNTIME/menu.vim
"解决consle输出乱码
"set termencoding = cp936
set termencoding=utf-8
"设置中文提示
"language messages zh_CN.utf-8
"设置中文帮助
set helplang=cn
"设置为双字宽显示，否则无法完整显示如:☆
set ambiwidth=double


"====================================================================
" airline Settings
"===================================================================
" 指定安裝的字型 (airline會需要一些特殊符號字型)
set guifont=Inconsolata\ for\ Powerline\ 20

" 显示颜色
set t_Co=256
set laststatus=2
"这个是安装字体后 必须设置此项  使用powerline打过补丁的字体"
let g:airline_powerline_fonts = 1
" 开启tabline
let g:airline#extensions#tabline#enabled = 1
" tabline中当前buffer两端的分隔字符
let g:airline#extensions#tabline#left_sep = ' '
" tabline中未激活buffer两端的分隔字符
let g:airline#extensions#tabline#left_alt_sep = ' '
" tabline中buffer显示编号 打开tabline功能 方便查看Buffer和切换 省去了minibufexpl插件
let g:airline#extensions#tabline#buffer_nr_show = 1

let g:airline_theme="molokai"

"设置切换Buffer快捷键"
"" nnoremap <C-tab> :bn<CR>
"" nnoremap <C-s-tab> :bp<CR>

nnoremap [b :bp<CR>
nnoremap ]b :bn<CR>

" 映射<leader>num到num buffer
map <leader>1 :b 1<CR>
map <leader>2 :b 2<CR>
map <leader>3 :b 3<CR>
map <leader>4 :b 4<CR>
map <leader>5 :b 5<CR>
map <leader>6 :b 6<CR>
map <leader>7 :b 7<CR>
map <leader>8 :b 8<CR>
map <leader>9 :b 9<CR>

" 关闭状态显示空白符号计数
let g:airline#extensions#whitespace#enabled = 0
let g:airline#extensions#whitespace#symbol = '!'
" 设置consolas字体"前面已经设置过
"set guifont=Consolas\ for\ Powerline\ FixedD:h11
if !exists('g:airline_symbols')
    let g:airline_symbols = {}
endif
" old vim-powerline symbols
let g:airline_left_sep = '⮀'
let g:airline_left_alt_sep = '⮁'
let g:airline_right_sep = '⮂'
let g:airline_right_alt_sep = '⮃'
let g:airline_symbols.branch = '⭠'
let g:airline_symbols.readonly = '⭤'


"====================================================================
" Trinity Settings
"====================================================================
"Open/close the Tagbar separately
nmap <F6> :TagbarToggle<CR>
"Open/close the Source Explorer separately
nmap <F7>  :TrinityToggleSourceExplorer<CR>
"Open/close the Taglist separately
nmap <F8> :TrinityToggleTagList<CR>
"Open/close the NERDTree separately
nmap <F9> :TrinityToggleNERDTree<CR>
"Open/close SrcExpl, Taglist, Nerdtree
nmap <F10>  :TrinityToggleAll<CR>

"====================================================================
" NERDTree setting
"====================================================================
" let mapleader = ","
" nmap <leader>ne :NERDTree<cr>
nmap <C-H> <C-W>h
nmap <C-J> <C-W>j
nmap <C-K> <C-W>k
nmap <C-L> <C-W>l
" Below key mappings can replace the Vim feature for jumping to previously visited locations via jump list.

nmap <C-I> <C-W>j:call g:SrcExpl_Jump()<CR>
nmap <C-O> :call g:SrcExpl_GoBack()<CR>

"====================================================================
" Editor Settings
"====================================================================
" 配色
" using Molokai Color Scheme for Vim
" from https://github.com/tomasr/molokai
" set t_Co=256
" colorscheme molokai

" set solarized colorscheme
" from https://https://github.com/altercation/vim-colors-solarized
" syntax enable
" set background=dark
" set background=light
" set t_Co=256
" let g:solarized_termcolors=256
" colorscheme solarized

" set background=light
" colorscheme wombat256mod

set t_Co=256
set background=dark
colorscheme gruvbox
" colorscheme jellybeans

" 設定gvim 的字型和大小
set guifont=inconsolata\ 20

" highlight找到的字串
set hlsearch

" search時即時顯示結果
set incsearch

" highlight游標所在row
set cursorline

" 第80字元地方顯示高亮度區塊（這是連續兩個描述)
set colorcolumn=80
highlight ColorColumn guibg=#202020

" mouse control
" set mouse=a

" 顯示行號
set nu
" 為方便複製，用<F2>開啟/關閉行號顯示
nnoremap <F2> :set nonumber!<CR>

" 顯示tab （這是連續兩個描述)
set listchars=tab:\|.
set list

" 強制tab space為4個字元
set tabstop=4

" 使用space代替tab
set expandtab
"set noexpandtab

" 當編寫Makefile時，取消expandtab設定 (Makefile需區分tab與space)
autocmd FileType make setlocal noexpandtab

" auto indent的移動字元量
set shiftwidth=4

" 設置自動縮進
set autoindent

" 使用C/C++ 語言的自動縮排方式：
set cindent

" 智能縮排
set smartindent

" 在狀態欄顯示正在輸入的命令
set showcmd

" 設置匹配模式，顯示匹配的括號
set showmatch

" 智能補全
set completeopt=longest,menu

" 通过使用: commands命令，告诉我们文件的哪一行被改变过
set report=0

"====================================================================
" set vim-cpp-enhanced-highlight
"====================================================================
"Highlighting of class scope is disabled by default. To enable set
let g:cpp_class_scope_highlight = 1

" Highlighting of member variables is disabled by default. To enable set
let g:cpp_member_variable_highlight = 1

" Highlighting of class names in declarations is disabled by default. To enable set
let g:cpp_class_decl_highlight = 1

" Highlighting of POSIX functions is disabled by default. To enable set

let g:cpp_posix_standard = 1

"There are two ways to highlight template functions. Either
let g:cpp_experimental_simple_template_highlight = 1

"which works in most cases, but can be a little slow on large files. Alternatively set
let g:cpp_experimental_template_highlight = 1

"which is a faster implementation but has some corner cases where it doesn't work.
"Note: C++ template syntax is notoriously difficult to parse, so don't expect this feature to be perfect.
"Highlighting of library concepts is enabled by

let g:cpp_concepts_highlight = 1
" This will highlight the keywords concept and requires as well as all named requirements (like DefaultConstructible) in the standard library.

" Highlighting of user defined functions can be disabled by
let g:cpp_no_function_highlight = 1


"====================================================================
" Highlight Class and Function names
"====================================================================
"syn match    cCustomParen    "(" contains=cParen,cCppParen
"syn match    cCustomFunc     "\w\+\s*(" contains=cCustomParen
"syn match    cCustomScope    "::"
"syn match    cCustomClass    "\w\+\s*::" contains=cCustomScope

"hi def link cCustomFunc  Function
"hi def link cCustomClass Function

" Highlight all function names
"syntax match cCustomFunc /\w\+\s*(/me=e-1,he=e-1
"highlight def link cCustomFunc Function

"syn match    cCustomParen    "?=(" contains=cParen,cCppParen
"syn match    cCustomFunc     "\w\+\s*(\@=" contains=cCustomParen
"syn match    cCustomScope    "::"
"syn match    cCustomClass    "\w\+\s*::" contains=cCustomScope
"hi def cCustomFunc  gui=bold guifg=yellowgreen
"hi def link cCustomClass Function


"====================================================================
" YouCompleteMe setting
"====================================================================
let g:ycm_server_python_interpreter='/usr/bin/python3'
let g:ycm_global_ycm_extra_conf='~/.vim/.ycm_extra_conf.py'"
