#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#ifndef UINT32_WIDTH
#define UINT32_WIDTH 32
#endif

/// Получает новое число из исходного путем изменения значения всех битов
/// старшего байта исходного числа на противоположные.
/// Параметры:
///   N: беззнаковое 32-битное целое число
/// Возврат:
///   Число, полученное из исходного

uint32_t msbyte_invert(uint32_t N)
{
  return (~N & 0xFF000000) | (N & 0x00FFFFFF);
} // msbyte_invert

/// Получает беззнаковое целое число из стандартного потока ввода до разделителя.
/// Разделителем является любой символ, отличный от цифры и минуса в начале.
/// Параметры:
///   uint32_t *result - переменная, принимающая полученное число
///   int *next - переменная, принимающая символ разделителя
/// Возврат:
///   1 - успех
///   0 - ошибка

int get_next_unsigned_int(uint32_t *result, int *next)
{
  int out_getchar = 0, temp = 0, is_ready = 0;
  char ch;

  while ((out_getchar = getchar())) {
    ch = (char)out_getchar;

    if ((ch >= '0') && (ch <= '9')) {
      temp = temp * 10 + (ch - '0');
      is_ready = 1;
    }
    else {
      if (!is_ready) {
        if (out_getchar == EOF)
          return 0;
        continue;
      }
      else {
        *result = temp;
        *next = out_getchar;
        break;
      }
    }
  }
  return 1;
} // get_next_unsigned_int

int main()
{
  uint32_t number; // Беззнаковое 32-битное целое число
  int getchar_out;

  if (!get_next_unsigned_int(&number, &getchar_out))
    return EXIT_FAILURE;

  printf("%"PRIu32"\n", msbyte_invert(number));

  return EXIT_SUCCESS;
} // main