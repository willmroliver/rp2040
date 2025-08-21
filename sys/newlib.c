extern void _exit(int status);

int _close(int file)
{
	return -1;
}

int _lseek(int file, int ptr, int dir)
{
	return 0;
}

int _read(int file, char *ptr, int len)
{
	return 0;
}

int _write(int file, char *ptr, int len)
{
	return 0;
}

void *_sbrk(int incr)
{
	_write(1, "Memory management not yet implemented by runtime\n", 49);
	_exit(1);

	/* extern char _end; */
	/* static char *heap_end; */
	/* char *prev_heap_end; */
	/**/
	/* if (heap_end == 0) { */
	/* 	heap_end = &_end; */
	/* } */
	/* prev_heap_end = heap_end; */
	/* if (heap_end + incr > stack_ptr) { */
	/* 	_write(1, "Heap and stack collision\n", 25); */
	/* 	_exit(1); */
	/* } */
	/**/
	/* heap_end += incr; */
	/* return (void *)prev_heap_end; */
}

