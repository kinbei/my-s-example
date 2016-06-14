#include "queue.h"

void queue_init(struct queue *q, int sz) {
	q->head = 0;
	q->tail = 0;
	q->buffer = NULL;
	q->sz = sz;
}

int queue_empty(struct queue *q) {
	return q->head == q->tail;
}

int queue_pop(struct queue *q, void *result) {
	if (q->head == q->tail) {
		return 1;
	}
	memcpy(result, q->buffer + q->head * q->sz, q->sz);
	q->head++;
	if (q->head >= q->cap)
		q->head = 0;
	return 0;
}

void queue_push(struct queue *q, const void *value) {
	void * slot = q->buffer + q->tail * q->sz;
	++q->tail;
	if (q->tail >= q->cap)
		q->tail = 0;
	if (q->head == q->tail) {
		// full
		assert(q->sz > 0);
		int cap = q->cap * 2;
		if (cap == 0)
			cap = 4;
		char * tmp = skynet_malloc(cap * q->sz);
		int i;
		int head = q->head;
		for (i=0;i<q->cap;i++) {
			memcpy(tmp + i * q->sz, q->buffer + head * q->sz, q->sz);
			++head;
			if (head >= q->cap) {
				head = 0;
			}
		}
		skynet_free(q->buffer);
		q->head = 0;
		q->tail = q->cap ? q->cap : 1;
		q->cap = cap;
		q->buffer = tmp;
		slot = tmp;
	}
	memcpy(slot, value, q->sz);
}

int queue_size(struct queue *q) {
	if (q->head > q->tail) {
		return q->tail + q->cap - q->head;
	}
	return q->tail - q->head;
}