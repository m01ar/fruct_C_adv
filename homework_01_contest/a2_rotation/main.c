#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#ifndef UINT32_WIDTH
#define UINT32_WIDTH 32
#endif

/// Выполняет циклический сдвиг вправо 32-битного беззнакового целого числа.
/// Параметры:
///   uint32_t number - обрабатываемое число
///    uint32_t shift - величина сдвига
/// Возврат:
///   Результат циклического сдвига

uint32_t ror_uint32(uint32_t number, uint32_t shift)
{
  shift = shift % UINT32_WIDTH;
  return (number << (UINT32_WIDTH - shift)) | (number >> shift);
} // ror_uint32

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
  uint32_t shift;  // Натуральное число K (1 ≤ K ≤ 31) - величина сдвига
  int getchar_out;

  if (!get_next_unsigned_int(&number, &getchar_out))
    return EXIT_FAILURE;

  if (!get_next_unsigned_int(&shift, &getchar_out))
    return EXIT_FAILURE;

  printf("%"PRIu32"\n", ror_uint32(number, shift));

  return EXIT_SUCCESS;
} // main
