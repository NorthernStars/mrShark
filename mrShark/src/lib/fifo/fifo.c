/*
 * fifo.c
 *
 *  Created on: 25.08.2013
 *      Author: Hannes Eilers
 */
#include "../../headers/sys.h"

void fifo_init (fifo_t *f, uint8_t *buffer, const uint8_t size)
{
	f->count = 0;
	f->pread = f->pwrite = buffer;
	f->read2end = f->write2end = f->size = size;
}

uint8_t fifo_put (fifo_t *f, const uint8_t data)
{
	return _inline_fifo_put (f, data);
}

uint8_t fifo_get_wait (fifo_t *f)
{
	while (!f->count);

	return _inline_fifo_get (f);
}

int fifo_get_nowait (fifo_t *f)
{
	if (!f->count)		return -1;

	return (int) _inline_fifo_get (f);
}

uint8_t fifo_getCount(fifo_t *f){
	return f->count;
}
