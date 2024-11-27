#include <stdio.h>
#include <stdlib.h>

/// Функция извлечения порядка числа согласно прототипу из условия задачи

int extractExp(float f)
{
  union {
    float asFloat;
    struct {
      unsigned int mantissa : 23;
      unsigned int exponent : 8;
      unsigned int   sign : 1;
    } asStruct;
  } value;

  value.asFloat = f;
  return (int)value.asStruct.exponent;
} // extractExp

int main(void)
{
  float input;
//  unsigned long output;

  if (scanf("%f", &input) != 1)
    return EXIT_FAILURE;

//  memcpy(&output, &input, 4);
//  printf("%d\n", (int)(0xFF & (output>>23)));
  printf("%d\n", extractExp(input));

  return EXIT_SUCCESS;
}  // main
