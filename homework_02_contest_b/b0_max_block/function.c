uint64_t findMaxBlock(list *head)
{
  list max_size_node = {0, 0, "", NULL};
  for (list *node = head; node; node = node->next) {
    if (node->size > max_size_node.size) {
      max_size_node.size = node->size;
      max_size_node.address = node->address;
    }
  }
  return max_size_node.address;
}

// Размышления к оптимизации:
//
// В функции вместо переменной типа (list)
// можно использовать
// 1. переменную типа (uint64_t) для
// хранения максимального значения size
// 2. переменную типа (list *) для
// хранения указателя на элемент списка,
// содержащего максимальный size
// 3. возвращать из (п.2) по стрелке
// значение поля address
//
// Таким образом на стеке будет вместо
// sizeof(list) байт выделяться
// sizeof(uint64_t) + sizeof(list *)
// байт.
