#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/// Получает знаковое целое число из стандартного потока ввода
/// Параметры:
///   int *result - переменная, принимающая полученное число
/// Возврат:
///   1 - успех
///   0 - ошибка

int get_next_int(int *result)
{
  int out_getchar = 0, is_negative = 0, temp = 0, is_ready = 0;
  char ch;

  while ((out_getchar = getchar())) {
    ch = (char)out_getchar;
    if ((out_getchar == EOF) || (ch == ' ') || (ch == '\n')) {
      if (is_ready)
        *result = temp * (1 - 2 * is_negative);
      break;
    }
    else if (ch == '-') {
      if (is_negative)
        return 0;
      is_negative = 1;
    }
    else if ((ch >= '0') && (ch <= '9')) {
      temp = temp * 10 + (ch - '0');
      is_ready = 1;
    }
    else {
      return 0;
    }
  }
  return 1;
} // get_next_int

int main(void)
{
  int count = 0, temp = 0, max = INT_MIN, freq = 0;
  
  if (!get_next_int(&count)) // Считываем количество
    return EXIT_FAILURE;

  if (count < 1)       // Проверяем количество
    return EXIT_FAILURE;
  
  while (count-- && get_next_int(&temp)) {
    if (temp > max) {   // Новый максимум 
      max = temp;
      freq = 1;
    }
    else if (temp == max) // Повтор максимума
      freq++;
  }

  printf("%d\n", freq);

  return EXIT_SUCCESS;
} // main
