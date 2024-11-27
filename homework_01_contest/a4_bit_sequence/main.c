#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#ifndef UINT32_WIDTH
#define UINT32_WIDTH 32
#endif

/// Ищет максимальное число из подряд идущих бит числа
/// Параметры:
///   N: беззнаковое 32-битное целое число
///   K: натуральное число (1 ≤ K ≤ 31)
/// Возврат:
///   Максимальное число среди K подряд идущих битов числа N 

uint32_t max_of_bits(uint32_t N, uint32_t K)
{
  uint32_t max_num = 0, next_num = 0;
  uint32_t mask = 0;
  K %= UINT32_WIDTH;

  while (K--)
    mask = (mask << 1) +1;

  for (int i = 0; i < (UINT32_WIDTH - K); i++) {
    next_num = (N >> i) & mask;
    if (max_num < next_num)
      max_num = next_num;
  }

  return max_num;
} // max_of_bits

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
  uint32_t count;  // Натуральное число K (1 ≤ K ≤ 31) - количество бит
  int getchar_out;

  if (!get_next_unsigned_int(&number, &getchar_out))
    return EXIT_FAILURE;

  if (!get_next_unsigned_int(&count, &getchar_out))
    return EXIT_FAILURE;

  printf("%"PRIu32"\n", max_of_bits(number, count));
    
  return EXIT_SUCCESS;
} // main
