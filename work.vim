function! Git_informa()
	split
	nnoremap <Leader>gi :call Git_exit()<CR>
	exe 'AsyncRun echo > informa__.txt ;' . 'git branch >> informa__.txt ;'. 'echo ==================================== >> informa__.txt ;' . 'git status >> informa__.txt'
	open informa__.txt
endfunction

function! Git_exit()
	nnoremap <Leader>gi :call Git_informa()<CR>
	q!
endfunction

nnoremap <Leader>gi :call Git_informa()<CR>
