#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N_ALPHA 26 // Размер алфавита

/// Получает знаковое целое число из стандартного потока ввода до разделителя.
/// Разделителем является любой символ, отличный от цифры и минуса в начале.
/// Параметры:
///   int *result - переменная, принимающая полученное число
///   int *next - переменная, принимающая символ разделителя
/// Возврат:
///   1 - успех
///   0 - ошибка

int get_next_int(int *result, int *next)
{
  int out_getchar = 0, is_negative = 0, temp = 0, is_ready = 0;
  char ch;

  while ((out_getchar = getchar())) {
    ch = (char)out_getchar;

    if (ch == '-') {
      if (is_negative)
        return 0;
      is_negative = 1;
    }
    else if ((ch >= '0') && (ch <= '9')) {
      temp = temp * 10 + (ch - '0');
      is_ready = 1;
    }
    else {
      if (is_ready)
        *result = temp * (1 - 2 * is_negative);
      *next = out_getchar;
      break;
    }
  }
  return 1;
} // get_next_int

/// Выполняет преобразование символа согласно алгоритму "Шифр Цезаря".
/// Параметры:
///   int num - величина сдвига
///   int *ch_int - обрабатываемый символ
/// Возврат:
///   Преобразованные латинские буквы, либо прочие символы в исходном виде.

char rotate_char(int num, int *ch_int)
{
  char ch = (char)*ch_int;

  if (ch >= 'a' && ch <= 'z') {
    ch = 'a' + (ch -'a' + num) % N_ALPHA;
  }
  else if (ch >= 'A' && ch <= 'Z') {
    ch = 'A' + (ch -'A' + num) % N_ALPHA;
  }

  return ch;
} // rotate_char


int main(void)
{
  int count = 0;
  int getchar_out;
  
  if (!get_next_int(&count, &getchar_out))
    return EXIT_FAILURE;

  if (count < 0)
    return EXIT_FAILURE;

  if (getchar_out == EOF)
    return EXIT_SUCCESS;

  do { // Избавляемся от пробелов, отделяющих текст от количества
    if ((char)getchar_out != ' ')
      break;
  }
  while ((getchar_out = getchar()) && (getchar_out != EOF));

  do {
    printf("%c", rotate_char(count, &getchar_out));
    if ((char)getchar_out == '.')
      break;
  } while ((getchar_out = getchar()) && (getchar_out != EOF));

  return EXIT_SUCCESS;
} // main
