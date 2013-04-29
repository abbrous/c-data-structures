#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "../data-structures/queue.h"

void test_queue_initializes() 
{
	queue q;
	queue_new(&q, sizeof(int), NULL);

	assert(q.logicalLength == 0);
	assert(q.elementSize == sizeof(int));
	assert(q.freeFn == NULL);
	assert(q.head == NULL);
	assert(q.tail == NULL);

	queue_destroy(&q);
	PRINT_SUCCESS();
}

void test_queue_can_enqueue_item()
{
	queue s;
	queue_new(&s, sizeof(int), NULL);

	int value = 10;
	queue_enqueue(&s, &value);

	assert(s.logicalLength == 1);

	queue_destroy(&s);
	PRINT_SUCCESS();
} 

void test_queue_can_dequeue_item()
{
	queue s;
	queue_new(&s, sizeof(int), NULL);

	int value = 10;
	queue_enqueue(&s, &value);
	assert(s.logicalLength == 1);

	int other;
	queue_dequeue(&s, &other);
	assert(other == value);
	assert(s.logicalLength == 0);

	queue_destroy(&s);
	PRINT_SUCCESS();
}

void test_queue_can_peek_item()
{
	queue s;
	queue_new(&s, sizeof(int), NULL);

	int value = 10;
	queue_enqueue(&s, &value);
	assert(s.logicalLength == 1);

	int other;
	queue_peek(&s, &other);
	assert(other == value);
	assert(s.logicalLength == 1);

	queue_destroy(&s);
	PRINT_SUCCESS();
}

void test_queue_free_string(void *data)
{
	free(*(char **)data);
}

void test_queue_can_work_with_strings()
{
	queue q;
	queue_new(&q, sizeof(char *), test_queue_free_string);

	const char *names[] = { "David", "Muto", "Tester" };
	int i;
	char *name;
	for(i = 0; i < 3; i++) {
		name = strdup(names[i]);
		queue_enqueue(&q, &name);
	}

	assert(queue_size(&q) == 3);

	queue_dequeue(&q, &name);
	assert(strcmp(name, "David") == 0);
	free(name);

	assert(queue_size(&q) == 2);
	queue_destroy(&q);
	PRINT_SUCCESS();
}

void test_queue_operations()
{
	test_queue_initializes();
	test_queue_can_enqueue_item();
	test_queue_can_dequeue_item();
	test_queue_can_peek_item();
	test_queue_can_work_with_strings();
}