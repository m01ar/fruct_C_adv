size_t totalMemoryUsage(list *head)
{
  size_t result = 0;
  for (list *node = head; node; node = node->next)
    result += node->size;

  return result;
}
