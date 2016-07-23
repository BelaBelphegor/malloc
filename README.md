# malloc
A simple C implementation of stdlib malloc.

#schema
---------------------------------------------------------
| PAGE TINY | FIRST BLOCK 			| SECOND BLOCK		|
| HEADER	| + Content				| + Content			|
---------------------------------------------------------
0 Pointer 	1 Pointer + header_size 2 Block + Block_size
