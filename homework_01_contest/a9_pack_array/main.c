#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define SIZE 32

/// В программе реализована структура данных:

struct pack_array {
  uint32_t array; // поле для хранения упакованного массива из 0 и 1
  uint32_t count0 : 8; // счетчик нулей в array
  uint32_t count1 : 8; // счетчик единиц в array
};

/// Упаковывает переданный ей массив из 32-ух элементов 0 и 1 в указанную
/// структуру данных. Функция должна строго соответствовать прототипу:

void array2struct(int array[], struct pack_array *pack_array)
{
  for (int i = 0; i < SIZE; i++) {
    pack_array->array |= array[i] << i;
    if (array[i])
      pack_array->count1++;
    else
      pack_array->count0++;
  }
} // array2struct

int main()
{
  int getchar_out;
  int counter = SIZE;
  char ch;

  int array[SIZE] = {0};
  struct pack_array pa;

  while (counter && (getchar_out = getchar()) && (getchar_out != EOF)) {
    ch = (char)getchar_out;
    switch (ch) {
      case '0':
      case '1':
        array[--counter] = (int)(ch - '0');
        break;
      case ' ':
        continue;
      default:
        counter = 0;
    }
  }

  array2struct(array, &pa);

//  printf("array = %"PRIx32"\ncount0 = %d\ncount1 = %d\n",
  printf("%"PRIu32" %d %d\n",
    pa.array, pa.count0, pa.count1);

  return 0;
} // main
