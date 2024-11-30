#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>

typedef struct node {
	uint64_t address;
	size_t size;
	char comment[64];
	struct node *next;
} node_t;

/// Составляет список по вводу с клавиатуры

node_t *compose_list()
{
	int node_cnt = 0;
	node_t *head_node = NULL, *last_node = NULL, *this_node = NULL;

	if (scanf("%d", &node_cnt) < 1)
		return NULL;

	for (int i = 0; i < node_cnt; i++) {
		this_node = malloc(sizeof(node_t));
		if (scanf("%"SCNu64" %zu",
		          &(this_node->address), &(this_node->size)) < 2) {
			free(this_node);
			return NULL;
		}

		if (!head_node)
			head_node = this_node;

		if (!last_node)
			last_node = this_node;
		else {
			last_node->next = this_node;
			last_node = this_node;
		}
	}
	return head_node;
}

/// Вывод элементов списка в консоль (рекурсивный)

void print_list(node_t *node)
{
	if (!node)
		return;
	printf("%"PRIu64" %zu\n", node->address, node->size);
	print_list(node->next);
}

/// Удаление списка (рекурсивное)

void free_list(node_t *node)
{
	if (!node)
		return;
	free_list(node->next);
//	puts("freeing node...");
	free(node);
}

/// Заданная к реализации функция

uint64_t findMaxBlock(node_t *head)
{
	node_t max_size_node = {0, 0, "", NULL};
	for (node_t *node = head; node; node = node->next)
	{
		if (node->size > max_size_node.size) {
			max_size_node.size = node->size;
			max_size_node.address = node->address;
		}
	}
	return max_size_node.address;
}

int main()
{
	node_t *head_node = NULL;

	head_node = compose_list();
	puts("");
	// for (this_node = head_node; this_node; this_node = this_node->next)
	//     printf("%"PRIu64" %zu\n", this_node->address, this_node->size);
// 	print_list(head_node);
	printf("%"PRIu64"\n", findMaxBlock(head_node));
	free_list(head_node);
	return EXIT_SUCCESS;
}
