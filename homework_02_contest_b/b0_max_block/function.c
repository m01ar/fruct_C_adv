uint64_t findMaxBlock(list *head)
{
	list max_size_node = {0, 0, "", NULL};
	for (list *node = head; node; node = node->next)
	{
		if (node->size > max_size_node.size) {
			max_size_node.size = node->size;
			max_size_node.address = node->address;
		}
	}
	return max_size_node.address;
}
