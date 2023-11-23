ru defaults.vim
no U :up<cr>
au filetype vim no <buffer> U :up<bar>so %<cr>

se ts=4 sw=4 nohls noet acd udf cino=j1 rnu fdm=syntax mouse=a
au filetype cpp no <silent> <buffer> \r :up<bar>term ++close ++shell ./c % && gdb -q a.out -ex 'r <i' <bar><bar> read<cr>

tmap <c-[><c-[> <c-w>N

no! jp  <c-]>.push_back(
no! vc vector<

au filetype cpp ab <buffer> in int
au filetype cpp ab <buffer> un unsigned
au filetype cpp ab <buffer> au auto
au filetype cpp ab <buffer> con const
au filetype cpp ab <buffer> fa for(auto
au filetype cpp ab <buffer> ret return
au filetype cpp ab <buffer> fi for(int
au filetype cpp ab <buffer> rt assert

" -- extra --
no gb yiw: <c-r>"<home>ab <buffer> 
map! gb <esc>gb
au filetype python no <buffer> \r :up<bar>!python %<cr>

" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
 \| md5sum \| cut -c-6
