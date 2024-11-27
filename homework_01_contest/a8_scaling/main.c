#include <stdio.h>
#include <stdlib.h>

#define WEIGHT_LIMIT 1000000

/// Чаша весов (объект)

typedef struct {
  int count;      // Количество гирек на чаше
  signed long weight; // Общая масса на чаше
} ScalePan;

/// Нагрузить чашу весов (вспомогательная функция)

void load_pan(ScalePan *pan, signed long unit)
{
  pan->count++;
  pan->weight += unit;
} // load_pan

/// Подсчитать суммарное количество гирек, необходимых для взвешивания груза
/// n - масса взвешиваемого груза, г

int weights(signed long n)
{
  ScalePan
    left_pan  = (ScalePan) {.count = 0, .weight = n},
    right_pan = (ScalePan) {.count = 0, .weight = 0};

  int carry = 0; // Флаг переноса
  signed long unit = 1; // Размер гирьки (степени тройки)

  if (left_pan.weight > WEIGHT_LIMIT) // Первичная проверка измеряемого
    return -1;

  while (n) {
    switch (n % 3) {
    case 2:
      if (!carry)  // c ? (0) : (-)
        load_pan(&left_pan, unit);
      carry = 1;
      break;
    case 1:
      if (carry)   // c ? (-) : (+)
        load_pan(&left_pan, unit);
      else
        load_pan(&right_pan, unit);
      break;
    case 0:
      if (carry)   // c ? (+) : (0)
        load_pan(&right_pan, unit);
      carry = 0;
      break;
    }
    
    if ((left_pan.weight > WEIGHT_LIMIT) ||
      (right_pan.weight > WEIGHT_LIMIT))
      return -1;
      
    n /= 3;
    unit *= 3;
  }
  
  if (carry)
    load_pan(&right_pan, unit);

  // printf("(%d) %ld > < %ld (%d)\n",
  //   left_pan.count, left_pan.weight,
  //   right_pan.weight, right_pan.count);
    
  return right_pan.count + left_pan.count;
} // weights

int main(void)
{
  signed long input;
  int result;

  if (scanf("%ld", &input) < 1)
    return EXIT_FAILURE;

  if (input < 0)
    return EXIT_FAILURE;

  result = weights(input);

  printf("%d\n", result);

  return EXIT_SUCCESS;
}
