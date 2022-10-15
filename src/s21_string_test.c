#include "s21_string.h"

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(test_memchr) {
  char str[] = "Hello, how are you?";
  char *empty = "";
  char *s1 = "This is a s21_memchr test";
  ck_assert_ptr_eq(s21_memchr(str, 'h', 3), memchr(str, 'h', 3));
  ck_assert_ptr_eq(s21_memchr(str, 'l', 1), memchr(str, 'l', 1));
  ck_assert_ptr_eq(s21_memchr(str, 'h', 0), memchr(str, 'h', 0));
  ck_assert_ptr_eq(s21_memchr("h", 'h', 3), memchr("h", 'h', 3));
  ck_assert_ptr_eq(s21_memchr(str, 500, 2), memchr(str, 500, 2));
  ck_assert_ptr_eq(s21_memchr(empty, 500, 1), memchr(empty, 500, 1));
  ck_assert_ptr_eq(s21_memchr(empty, 'l', 10), memchr(empty, 'l', 10));
  ck_assert_ptr_eq(s21_memchr(s1, 's', 0), memchr(s1, 's', 0));
  ck_assert_ptr_eq(s21_memchr(s1, 's', 2), memchr(s1, 's', 2));
  ck_assert_ptr_eq(s21_memchr(s1, 's', 50), memchr(s1, 's', 50));
  ck_assert_ptr_eq(s21_memchr(s1, 'u', 50), memchr(s1, 'u', 50));
  ck_assert_ptr_eq(s21_memchr(s1, 'u', 32), memchr(s1, 'u', 32));
}
END_TEST

START_TEST(test_memcmp) {
  unsigned char str1[] = "1, 2, 3, 4, 5, 6, 7, 8, 9";
  unsigned char str2[] = "1, 2, 3, 4, 5, 6, 7, 8, 9";
  ck_assert_int_eq(s21_memcmp(str1, str2, 10), memcmp(str1, str2, 10));
  ck_assert_int_eq(s21_memcmp(str1, str2, 0), memcmp(str1, str2, 0));
  unsigned char str3[] = "1, 2, 3, 4, 6, 6, 7, 8, 9";
  unsigned char str4[] = "1, 2, 3, 4, 5, 6, 7, 8, 9";
  ck_assert_int_eq(s21_memcmp(str3, str4, 10), memcmp(str3, str4, 10));
  unsigned char str5[] = "1, 2, 3, 4, 6, 6, 7, 8, 9";
  unsigned char str6[] = "1, 2, 3, 4, 7, 6, 7, 8, 9";
  ck_assert_int_eq(s21_memcmp(str5, str6, 10), memcmp(str5, str6, 10));
  unsigned char str7[] = "1, 2, 3, 4, 6, 6, 7, 8, 9";
  unsigned char str8[] = "1, 2, 3, 4, 7, 6, 7";
  ck_assert_int_eq(s21_memcmp(str7, str8, 10), memcmp(str7, str8, 10));
  ck_assert_int_eq(s21_memcmp(str8, str7, 10), memcmp(str8, str7, 10));
  unsigned char str9[20] = "1, 3, 4";
  unsigned char str10[20] = "1, 2, 3";
  ck_assert_int_eq(s21_memcmp(str9, str10, 10), memcmp(str9, str10, 10));
  char *s1 = "This is a 1st string s21_memcmp test";
  char *s2 = "This is a 2nd string s21_memcmp test";
  ck_assert_msg(s21_memcmp(s1, s2, 256) == memcmp(s1, s2, 256),
                "1st memcmp test failed.");
  ck_assert_msg(s21_memcmp(s1, s2, 2) == memcmp(s1, s2, 2),
                "2nd memcmp test failed.");
  ck_assert_msg(s21_memcmp(s1, s2, 123) == memcmp(s1, s2, 123),
                "3rd memcmp test failed.");
  ck_assert_msg(s21_memcmp(s1, s2, 36) == memcmp(s1, s2, 36),
                "4rth memcmp test failed.");
}
END_TEST

START_TEST(test_memcpy) {
  char dst1[] = "32123";
  char str1[] = "12367";
  ck_assert_str_eq(s21_memcpy(dst1, str1, 5), memcpy(dst1, str1, 5));
  ck_assert_str_eq(s21_memcpy(dst1, str1, 0), memcpy(dst1, str1, 0));
  char dst2[] = "32123dfgdf";
  char str2[] = "12367";
  ck_assert_str_eq(s21_memcpy(dst2, str2, 5), memcpy(dst2, str2, 5));
  char dst3[] = "32123";
  char str3[] = "12367asdfg";
  ck_assert_str_eq(s21_memcpy(dst3, str3, 5), memcpy(dst3, str3, 5));
}
END_TEST

START_TEST(test_memmove) {
  char dst1[10] = "OldText";
  char str1[10] = "NewText";
  ck_assert_str_eq(s21_memmove(dst1, str1, 8), memmove(dst1, str1, 8));
  ck_assert_str_eq(s21_memmove(dst1, str1, 0), memmove(dst1, str1, 0));
  ck_assert_str_eq(s21_memmove(dst1, "", 0), memmove(dst1, "", 0));
  ck_assert_str_eq(s21_memmove("", str1, 0), memmove("", str1, 0));
  ck_assert_str_eq(s21_memmove("", "", 0), memmove("", "", 0));
  char *src1 = "schesrdsfdsfdsfesr";
  int len = s21_strlen(src1);
  char dest1[100] = {0};
  char dest2[100] = {0};
  char dest3[100] = {0};
  char dest4[100] = {0};
  char dest5[100] = {0};
  char dest6[100] = {0};
  char dest7[100] = {0};
  char dest8[100] = {0};
  char dest9[100] = {0};
  char dest10[100] = {0};
  s21_memcpy(dest1, src1, len + 1);
  memcpy(dest2, src1, len + 1);
  s21_memcpy(dest3, src1, 5);
  memcpy(dest4, src1, 5);
  s21_memcpy(dest5, src1, 0);
  memcpy(dest6, src1, 0);
  s21_memcpy(dest7, src1, 18);
  memcpy(dest8, src1, 18);
  s21_memcpy(dest9, src1, 1);
  memcpy(dest10, src1, 1);
  ck_assert_str_eq(dest1, dest2);
  ck_assert_str_eq(dest3, dest4);
  ck_assert_str_eq(dest5, dest6);
  ck_assert_str_eq(dest7, dest8);
  ck_assert_str_eq(dest9, dest10);
}
END_TEST

START_TEST(test_memset) {
  char str[] = "This is string.h library function";
  ck_assert_str_eq(s21_memset(str, '$', 7), memset(str, '$', 7));
  ck_assert_str_eq(s21_memset(str, 7, 7), memset(str, 7, 7));
  ck_assert_str_eq(s21_memset(str, '\0', 7), memset(str, '\0', 7));
  char str1[] = "School is cool";
  char str2[] = "School-21";
  char str3[] = "amogus";
  char str4[] = "This is a string!";
  char str5[] = "Shrek";
  char res1[] = "School is cool";
  char res2[] = "School-21";
  char res3[] = "amogus";
  char res4[] = "This is a string!";
  char res5[] = "Shrek";
  s21_memset(str1, '_', 5);
  s21_memset(str2, '_', 4);
  s21_memset(str3, 'M', 2);
  s21_memset(str4, '-', 1);
  s21_memset(str5, 'S', 1);
  memset(res1, '_', 5);
  memset(res2, '_', 4);
  memset(res3, 'M', 2);
  memset(res4, '-', 1);
  memset(res5, 'S', 1);
  ck_assert_msg(memcmp(str1, res1, sizeof(str1)) == 0,
                "1st memset test failed");
  ck_assert_msg(memcmp(str2, res2, sizeof(str2)) == 0,
                "2nd memset test failed");
  ck_assert_msg(memcmp(str3, res3, sizeof(str3)) == 0,
                "3rd memset test failed");
  ck_assert_msg(memcmp(str4, res4, sizeof(str4)) == 0,
                "4rth memset test failed");
  ck_assert_msg(memcmp(str5, res5, sizeof(str5)) == 0,
                "5rth memset test failed");
}
END_TEST

START_TEST(test_strcat) {
  char src1[150] = "This is source";
  char dest1[150] = "This is destination";
  char *empty = "";
  ck_assert_str_eq(strcat(src1, dest1), strcat(src1, dest1));
  ck_assert_str_eq(s21_strcat(src1, "\0"), strcat(src1, "\0"));
  ck_assert_str_eq(s21_strcat(src1, "\n"), strcat(src1, "\n"));
  ck_assert_str_eq(s21_strcat(src1, empty), strcat(src1, empty));
  char str1[21] = "TEST";
  char str2[8] = "strcat";
  char str3[9] = "function";
  char str4[1] = "";
  char str5[2] = " ";
  s21_strcat(str1, str5);
  ck_assert_msg(!memcmp(str1, "TEST ", 6), "1st strcat test failed");
  s21_strcat(str1, str2);
  ck_assert_msg(!memcmp(str1, "TEST strcat", 12), "2nd strcat test failed");
  s21_strcat(str1, str5);
  ck_assert_msg(!memcmp(str1, "TEST strcat ", 13), "3rd strcat test failed");
  s21_strcat(str1, str3);
  ck_assert_msg(!memcmp(str1, "TEST strcat function", 21),
                "4rth strcat test failed");
  s21_strcat(str1, str4);
  ck_assert_msg(!memcmp(str1, "TEST strcat function", 21),
                "5th strcat test failed");
}
END_TEST

START_TEST(test_strncat) {
  char src1[50] = "This is source";
  char dest1[50] = "This is destination";
  ck_assert_str_eq(s21_strncat(src1, dest1, 5), strncat(src1, dest1, 5));
  ck_assert_str_eq(s21_strncat(src1, "", 5), strncat(src1, "", 5));
  ck_assert_str_eq(s21_strncat(src1, "\n", 5), strncat(src1, "\n", 5));
  ck_assert_str_eq(s21_strncat(src1, "", 0), strncat(src1, "", 0));
  ck_assert_str_eq(s21_strncat(src1, "\n", 0), strncat(src1, "\n", 0));
  ck_assert_str_eq(s21_strncat(src1, dest1, 0), strncat(src1, dest1, 0));
  char str1[25] = "TEST";
  char str2[8] = "strncat";
  char str3[35] = "function";
  char str4[1] = "";
  char str5[30] = "amogus";
  s21_strncat(str1, str2, 3);
  ck_assert_msg(!memcmp(str1, "TESTstr", 8), "1st strncat test failed");
  s21_strncat(str1, str4, 3);
  ck_assert_msg(!memcmp(str1, "TESTstr", 8), "2nd strncat test failed");
  s21_strncat(str2, str4, 1);
  ck_assert_msg(!memcmp(str2, "strncat", 8), "3rd strncat test failed");
  s21_strncat(str5, str3, 3);
  ck_assert_msg(!memcmp(str5, "amogusfun", 10), "4rth strncat test failed");
}
END_TEST

START_TEST(test_strchr) {
  const char str[] = "Doing some.tests here";
  char *empty = "";
  const char ch1 = '.';
  ck_assert_str_eq(s21_strchr(str, ch1), strchr(str, ch1));
  ck_assert_ptr_eq(s21_strchr(empty, ch1), strchr(empty, ch1));
  ck_assert_ptr_eq(s21_strchr(empty, 0), strchr(empty, 0));
  ck_assert_str_eq(s21_strchr(str, ch1), ".tests here");
  char *str1 = "TEST";
  char *str2 = "strchr";
  char *str3 = "function";
  char *str4 = "";
  char *str5 = "amogus";
  ck_assert_str_eq(s21_strchr(str1, 'E'), strchr(str1, 'E'));
  ck_assert_str_eq(s21_strchr(str3, 'i'), strchr(str3, 'i'));
  ck_assert_str_eq(s21_strchr(str5, 'a'), strchr(str5, 'a'));
  ck_assert_str_eq(s21_strchr(str1, 'E'), strchr(str1, 'E'));
  ck_assert_ptr_eq(s21_strchr(str2, 'E'), strchr(str2, 'E'));
  ck_assert_str_eq(s21_strchr(str3, 'i'), strchr(str3, 'i'));
  ck_assert_ptr_eq(s21_strchr(str4, ' '), strchr(str4, ' '));
  ck_assert_str_eq(s21_strchr(str5, 'a'), strchr(str5, 'a'));
}
END_TEST

START_TEST(test_strcmp) {
  char str1[15] = "abcdef";
  char str2[15] = "ABCDEF";
  ck_assert_int_eq(s21_strcmp(str1, ""), strcmp(str1, ""));
  ck_assert_int_eq(s21_strcmp("", ""), strcmp("", ""));
  ck_assert_int_eq(s21_strcmp("", str2), strcmp("", str2));
  ck_assert_int_eq(s21_strcmp("4321", "1234"), 3);
  char t1[] = "Sample Text";
  char t2[] = "Sample Text Plus Some Text";
  ck_assert_msg(s21_strcmp(t1, t2) == -32, "1st strcmp test failed");
  char t3[] = "AAA";
  char t4[] = "B";
  ck_assert_msg(s21_strcmp(t3, t4) == -1, "2nd strcmp test failed");
  char t5[] = "A\0BCD";
  char t6[] = "A";
  ck_assert_msg(s21_strcmp(t5, t6) == 0, "3rd strcmp test failed");
  char t7[] = "amogus";
  char t8[] = "m";
  ck_assert_msg(s21_strcmp(t7, t8) == -12, "4rth strcmp test failed");
  char t9[] = "shrek";
  char t10[] = "as";
  ck_assert_msg(s21_strcmp(t9, t10) == 18, "5th strcmp test failed");
  char t11[] = "бг";
  char t12[] = "бг";
  ck_assert_msg(s21_strcmp(t11, t12) == 0, "5th strcmp test failed");
}
END_TEST

START_TEST(test_strncmp) {
  char str1[15] = "abcdef";
  char str2[15] = "ABCDEF";
  ck_assert_int_eq(s21_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
  ck_assert_int_eq(s21_strncmp(str1, "", 3), strncmp(str1, "", 3));
  ck_assert_int_eq(s21_strncmp("", "", 3), strncmp("", "", 3));
  ck_assert_int_eq(s21_strncmp("", str2, 3), strncmp("", str2, 3));
  ck_assert_int_eq(s21_strncmp("4321", "1234", 3), 3);
  ck_assert_int_eq(s21_strncmp(str1, "ab", 2), strncmp(str1, "ab", 2));
  ck_assert_int_eq(s21_strncmp("ab", "ABCDEF", 4), strncmp("ab", "ABCDEF", 4));
  char *t1 = "Sample Text";
  char *t2 = "Sample Text Plus Some Text";
  ck_assert_msg(!s21_strncmp(t1, t2, 10) && !strncmp(t1, t2, 10),
                "1st strncmp test failed");
  ck_assert_msg(s21_strncmp(t1, t2, 14) < 0 && strncmp(t1, t2, 14) < 0,
                "2nd strncmp test failed");
  char *t3 = "";
  char *t4 = "A";
  ck_assert_msg(s21_strncmp(t3, t4, 0) == 0 && strncmp(t3, t4, 0) == 0,
                "3rd strncmp test failed");
  ck_assert_msg(s21_strncmp(t3, t4, 1) < 0 && strncmp(t3, t4, 1) < 0,
                "3rd strncmp test failed");
  char *t5 = "ShrekAmogus";
  char *t6 = "Shr";
  ck_assert_msg(s21_strncmp(t5, t6, 5) > 0 && strncmp(t5, t6, 5) > 0,
                "4rth strncmp test failed");
  ck_assert_msg(s21_strncmp(t5, t6, 0) == 0 && strncmp(t5, t6, 0) == 0,
                "5th strncmp test failed");
}
END_TEST

START_TEST(test_strcpy) {
  char src1[104] = "This is for strcpy";
  char dest1[104];
  ck_assert_str_eq(s21_strcpy(dest1, ""), strcpy(dest1, ""));
  ck_assert_str_eq(s21_strcpy(dest1, src1), strcpy(dest1, src1));
  char s1[50] = "Sample Text";
  char d1[50] = "";
  s21_strcpy(d1, s1);
  ck_assert_msg(!strcmp(d1, s1), "1st  strcpy test failed");
  char s2[50] = "AAAAA";
  char d2[50] = "NO";
  s21_strcpy(d2, s2);
  ck_assert_msg(!strcmp(d2, s2), "2nd strcpy test failed");
  char s3[50] = "";
  char d3[50] = "HELLO";
  s21_strcpy(d3, s3);
  ck_assert_msg(!strcmp(d3, s3), "3rd strcpy test failed");
  char s4[50] = "amogus";
  char d4[50] = "HELLO";
  s21_strcpy(d4, s4);
  ck_assert_msg(!strcmp(d4, s4), "4rth strcpy test failed");
  char s5[50] = "Shrek";
  char d5[50] = "what";
  s21_strcpy(d5, s5);
  ck_assert_msg(!strcmp(d5, s5), "5th strcpy test failed");
}
END_TEST

START_TEST(test_strncpy) {
  char src1[104] = "This is for strncpy";
  char dest1[104];
  ck_assert_str_eq(s21_strncpy(dest1, "", 7), strncpy(dest1, "", 7));
  ck_assert_str_eq(s21_strncpy(dest1, src1, 7), strncpy(dest1, src1, 7));
  char s1[50] = "Sample Text";
  char d1[50] = "";
  s21_strncpy(d1, s1, 2);
  ck_assert_msg(!strcmp(d1, "Sa"), "1st strncpy test failed");
  char s2[50] = "AAAAA";
  char d2[50] = "NO";
  s21_strncpy(d2, s2, 0);
  ck_assert_msg(!strcmp(d2, "NO"), "2nd strncpy test failed");
  char s3[50] = "H";
  char d3[50] = "fELLO";
  s21_strncpy(d3, s3, 1);
  ck_assert_msg(!strcmp(d3, "HELLO"), "3rd strncpy test failed");
  char s4[50] = "amo";
  char d4[50] = "qwegus";
  s21_strncpy(d4, s4, 3);
  ck_assert_msg(!strcmp(d4, "amogus"), "4rth strncpy test failed");
  char s5[50] = "shrek";
  char d5[50] = "s";
  s21_strncpy(d5, s5, 5);
  ck_assert_msg(!strcmp(d5, "shrek"), "5th strncpy test failed");
}
END_TEST

START_TEST(test_strcspn) {
  const char str1[] = "ABCDEF4960910";
  const char str2[] = "013";
  const char str3[] = "J";
  const char str4[] = "609";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
  ck_assert_int_eq(s21_strcspn(str1, ""), strcspn(str1, ""));
  ck_assert_int_eq(s21_strcspn("", str2), strcspn("", str2));
  ck_assert_int_eq(s21_strcspn("", ""), strcspn("", ""));
  ck_assert_int_eq(s21_strcspn(str1, str3), strcspn(str1, str3));
  ck_assert_int_eq(s21_strcspn(str1, str4), strcspn(str1, str4));
}
END_TEST

START_TEST(test_strerror) {
  for (int i = 1; i <= 144; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
  char *str1 = s21_strerror(20);
  char *str2 = strerror(20);
  ck_assert_str_eq(str1, str2);

  char *str3 = s21_strerror(12);
  char *str4 = strerror(12);
  ck_assert_str_eq(str3, str4);

  char *str5 = s21_strerror(1337);
  char *str6 = strerror(1337);
  ck_assert_str_eq(str5, str6);

  char *str7 = s21_strerror(1);
  char *str8 = strerror(1);
  ck_assert_str_eq(str7, str8);

  char *str9 = s21_strerror(25);
  char *str10 = strerror(25);
  ck_assert_str_eq(str9, str10);
}
END_TEST

START_TEST(test_strlen) {
  char str[6] = "Hello";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
  ck_assert_int_eq(s21_strlen(str), 5);
  ck_assert_int_eq(s21_strlen(""), strlen(""));
  ck_assert_int_eq(s21_strlen(""), 0);
  ck_assert_int_eq(s21_strlen("Hola \n"), strlen("Hola \n"));
  ck_assert_int_eq(s21_strlen("Hola \0"), strlen("Hola \0"));
  char *s1 = "0123456789";
  ck_assert_msg(s21_strlen(s1) == strlen(s1), "1st strlen test failed");
  char *s2 = "";
  ck_assert_msg(s21_strlen(s2) == strlen(s2), "2nd strlen test failed");
  char *s3 = "amogus";
  ck_assert_msg(s21_strlen(s3) == strlen(s3), "3rd strlen test failed");
  char *s4 = "shrek";
  ck_assert_msg(s21_strlen(s4) == strlen(s4), "4rth strlen test failed");
  char *s5 = "is love";
  ck_assert_msg(s21_strlen(s5) == strlen(s5), "5th strlen test failed");
}
END_TEST

START_TEST(test_strpbrk) {
  const char str[] = "abcde2fghi3jk4l";
  const char *empty = "";
  ck_assert_ptr_eq(s21_strpbrk(str, "34"), strpbrk(str, "34"));
  ck_assert_ptr_eq(s21_strpbrk(str, "abcd"), strpbrk(str, "abcd"));
  ck_assert_ptr_eq(s21_strpbrk(str, "ABCD"), strpbrk(str, "ABCD"));
  ck_assert_ptr_eq(s21_strpbrk(str, "a"), strpbrk(str, "a"));
  ck_assert_ptr_eq(s21_strpbrk(str, "3"), strpbrk(str, "3"));
  ck_assert_ptr_eq(s21_strpbrk(str, "000"), strpbrk(str, "000"));
  ck_assert_ptr_eq(s21_strpbrk(str, empty), strpbrk(str, empty));
  ck_assert_ptr_eq(s21_strpbrk(empty, "34"), strpbrk(empty, "34"));
  ck_assert_ptr_eq(s21_strpbrk(empty, empty), strpbrk(empty, empty));
  char *str1 = "hello";
  char *str2 = "hel";
  char *res1, *res2;
  res1 = s21_strpbrk(str1, str2);
  res2 = strpbrk(str1, str2);
  ck_assert_str_eq(res1, res2);
  char *str4 = "ab";
  res1 = s21_strpbrk(str1, str4);
  res2 = strpbrk(str1, str4);
  ck_assert_ptr_eq(res1, res2);
  char *str5 = "o";
  res1 = s21_strpbrk(str1, str5);
  res2 = strpbrk(str1, str5);
  ck_assert_str_eq(res1, res2);
  char *str6 = "abcdefghjkl";
  char *str7 = "abcd";
  res1 = s21_strpbrk(str6, str7);
  res2 = strpbrk(str6, str7);
  ck_assert_str_eq(res1, res2);
  char *str8 = "amogus is shrek?";
  char *str9 = "is";
  res1 = s21_strpbrk(str8, str9);
  res2 = s21_strpbrk(str8, str9);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_strrchr) {
  const char str1[] = "Some.words.for.the.test";
  const char ch1 = '.';
  ck_assert_str_eq(s21_strrchr(str1, ch1), strrchr(str1, ch1));
  ck_assert_str_eq(s21_strrchr(str1, ch1), ".test");
  ck_assert_ptr_eq(s21_strrchr(str1, '-'), strrchr(str1, '-'));
  ck_assert_ptr_eq(s21_strrchr(str1, 0), strrchr(str1, 0));
  ck_assert_ptr_eq(s21_strrchr("", '-'), strrchr("", '-'));
  char *s1 = "School-21";
  char *s2 = "";
  char *s3 = "amogus";
  ck_assert_msg(s21_strrchr(s1, 'm') == strrchr(s1, 'm'),
                "1st strrchr test failed");
  ck_assert_msg(s21_strrchr(s1, 'o') == strrchr(s1, 'o'),
                "2nd strrchr test failed");
  ck_assert_msg(s21_strrchr(s2, 'o') == strrchr(s2, 'o'),
                "3rd strrchr test failed");
  ck_assert_msg(s21_strrchr(s3, ' ') == strrchr(s3, ' '),
                "4rth strrchr test failed");
  ck_assert_msg(s21_strrchr(s3, 's') == strrchr(s3, 's'),
                "5th strrchr test failed");
}
END_TEST

START_TEST(test_strspn) {
  const char str1[] = "ABCDEFG019874";
  ck_assert_int_eq(s21_strspn(str1, "ABCD"), strspn(str1, "ABCD"));
  ck_assert_int_eq(s21_strspn(str1, "19"), strspn(str1, "19"));
  ck_assert_int_eq(s21_strspn(str1, "Hola!"), strspn(str1, "Hola!"));
  ck_assert_int_eq(s21_strspn(str1, "F!"), strspn(str1, "F!"));
  ck_assert_int_eq(s21_strspn(str1, "\0"), strspn(str1, "\0"));
  ck_assert_int_eq(s21_strspn(str1, ""), strspn(str1, ""));
  ck_assert_int_eq(s21_strspn("", str1), strspn("", str1));
  ck_assert_int_eq(s21_strspn("", ""), strspn("", ""));
  char *s1 = "School-21";
  char *s2 = "ho";
  char *s3 = "";
  ck_assert_msg(s21_strspn(s1, s2) == strspn(s1, s2), "1st strspn test failed");
  ck_assert_msg(s21_strspn(s3, s2) == strspn(s3, s2), "2nd strspn test failed");
  ck_assert_msg(s21_strspn(s2, s3) == strspn(s2, s3), "3rd strspn test failed");
  ck_assert_msg(s21_strspn(s1, s3) == strspn(s1, s3),
                "4rth strspn test failed");
  ck_assert_msg(s21_strspn(s3, s1) == strspn(s3, s1), "5th strspn test failed");
}
END_TEST

START_TEST(test_strstr) {
  const char haystack1[30] = "TutorialsPointYouGotThePoint";
  const char needle1[10] = "Point";
  const char *empty = "";
  ck_assert_str_eq(s21_strstr(haystack1, needle1), strstr(haystack1, needle1));
  ck_assert_str_eq(s21_strstr(haystack1, empty), strstr(haystack1, empty));
  ck_assert_ptr_eq(s21_strstr(haystack1, needle1), strstr(haystack1, needle1));
  ck_assert_ptr_eq(s21_strstr(haystack1, empty), strstr(haystack1, empty));
  ck_assert_ptr_eq(s21_strstr(empty, haystack1), strstr(empty, haystack1));
  ck_assert_ptr_eq(s21_strstr(empty, empty), strstr(empty, empty));
  ck_assert_ptr_eq(s21_strstr(haystack1, "Something"),
                   strstr(haystack1, "Something"));
  ck_assert_ptr_eq(s21_strstr(haystack1, "\0"), strstr(haystack1, "\0"));
  char *s1 = "School-21";
  char *s2 = "ho";
  char *s3 = "";
  ck_assert_msg(s21_strstr(s1, s2) == strstr(s1, s2), "1st strstr test failed");
  ck_assert_msg(s21_strstr(s1, s3) == strstr(s1, s3), "2nd strstr test failed");
  ck_assert_msg(s21_strstr(s3, s2) == strstr(s3, s2), "3rd strstr test failed");
  ck_assert_msg(s21_strstr(s2, s3) == strstr(s2, s3),
                "4rth strstr test failed");
  ck_assert_msg(s21_strstr(s3, s1) == strstr(s3, s1), "5th strstr test failed");
}
END_TEST

START_TEST(test_strtok) {
  char str[20] = "Hello.World";
  char delim[20] = ".";
  char *empty = "";
  ck_assert_str_eq(s21_strtok(str, delim), strtok(str, delim));
  ck_assert_str_eq(s21_strtok(str, delim), "Hello");
  ck_assert_str_eq(s21_strtok(str, "\0"), strtok(str, "\0"));
  ck_assert_str_eq(s21_strtok(str, "asdf"), strtok(str, "asdf"));
  ck_assert_str_eq(s21_strtok(str, "1234"), strtok(str, "1234"));
  ck_assert_str_eq(s21_strtok(str, empty), strtok(str, empty));
  ck_assert_ptr_eq(s21_strtok(empty, delim), strtok(empty, delim));
  char dest[] = "Hell0 world\0";
  char orig[] = "Hell0 world\0";
  ck_assert_str_eq(s21_strtok(dest, " "), strtok(orig, " "));
  char dest2[] = "Hell0 world\n\0";
  char orig2[] = "Hell0 world\n\0";
  ck_assert_str_eq(s21_strtok(dest2, " "), strtok(orig2, " "));
  char dest3[] = "a\n\0";
  char orig3[] = "a\n\0";
  ck_assert_str_eq(s21_strtok(dest3, " "), strtok(orig3, " "));
  char dest4[] = " s\0";
  char orig4[] = " s\0";
  ck_assert_str_eq(s21_strtok(dest4, " "), strtok(orig4, " "));
  char dest5[] = " \0";
  char orig5[] = " \0";
  ck_assert_ptr_eq(s21_strtok(dest5, " "), strtok(orig5, " "));
  char dest6[] = "\n\0";
  char orig6[] = "\n\0";
  ck_assert_str_eq(s21_strtok(dest6, " "), strtok(orig6, " "));
  char dest7[] = "\0";
  char orig7[] = "\0";
  ck_assert_ptr_eq(s21_strtok(dest7, " "), strtok(orig7, " "));
}
END_TEST

START_TEST(s21_sprintf_test1) {
  char str1[500] = {0};
  char str2[500] = {0};
  void *p = (void *)0x3456;
  int n1 = 0, n2 = 0;
  int r1 =
      sprintf(str1,
              "[%d] [%o] [%s] [%c] [%i] [%e] [%f] [%E] [%g] [%u] [%x] "
              "[%G] [%X] [%n] [%p] [%%] [%s]",
              25, 342, "aboba", 'a', 123, 25.34, 4325.23434, 0.0000000123,
              2.12345, 12345u, 8342, 3.12345, 1235, &n1, p, "hello my friend");
  int r2 = s21_sprintf(str2,
                       "[%d] [%o] [%s] [%c] [%i] [%e] [%f] [%E] [%g] [%u] "
                       "[%x] [%G] [%X] [%n] [%p] [%%] [%s]",
                       25, 342, "aboba", 'a', 123, 25.34, 4325.23434,
                       0.0000000123, 2.12345, 12345u, 8342, 3.12345, 1235, &n2,
                       p, "hello my friend");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test2) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(str1, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
  int r2 =
      s21_sprintf(str2, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test3) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(str1, "% d%#+34.10g%#.10x%#15.1o%25.10s", 5, 25.3456, 1234,
                   4567, "HELLOMYDEARFRIEND");
  int r2 = s21_sprintf(str2, "% d%#+34.10g%#.10x%#15.1o%25.10s", 5, 25.3456,
                       1234, 4567, "HELLOMYDEARFRIEND");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test4) {
  char str1[510] = {0};
  char str2[510] = {0};
  void *p = (void *)43252342;
  int r1 = sprintf(str1, "%*.006d%#24.e%-15.20i%20p%020u", 7, 894,
                   43253242.4342, 4567899, p, 43252342u);
  int r2 = s21_sprintf(str2, "%*.006d%#24.e%-15.20i%20p%020u", 7, 894,
                       43253242.4342, 4567899, p, 43252342u);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
  char str3[510] = {0};
  char str4[510] = {0};
  int r3 = sprintf(str3, "%*.0f", 25, 25432.34345);
  int r4 = s21_sprintf(str4, "%*.0f", 25, 25432.34345);
  ck_assert_str_eq(str3, str4);
  ck_assert_int_eq(r3, r4);
}
END_TEST

START_TEST(s21_sprintf_test_d) {
  char str1[510] = {0};
  char str2[510] = {0};
  short h = 34;
  int r1 = sprintf(
      str1,
      "%03d%.*d%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 5,
      8, 7, 253, 335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  int r2 = s21_sprintf(
      str2,
      "%03d%.*d%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 5,
      8, 7, 253, 335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_i) {
  char str1[510] = {0};
  char str2[510] = {0};
  short h = 34;
  int r1 = sprintf(
      str1,
      "%03i%.*i%-25.10i%-30.2i%10.12i%11i%*i%*.*i%+-25.*i%+10.2li%-11.*hi", 5,
      8, 7, 253, 335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  int r2 = s21_sprintf(
      str2,
      "%03i%.*i%-25.10i%-30.2i%10.12i%11i%*i%*.*i%+-25.*i%+10.2li%-11.*hi", 5,
      8, 7, 253, 335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_c) {
  char str1[510] = {0};
  char str2[510] = {0};
  wchar_t c1 = 'T', c2 = 'Z';
  int r1 = sprintf(str1, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a', 'e',
                   'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
  int r2 = s21_sprintf(str2, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a',
                       'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_e) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 =
      sprintf(str1, "%+-20e%010.*e%-*.16e%#025.10e%*.*e%*.15e%#010.*e%25.16e",
              2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15,
              11111.22, 16, -3245.3425342, 16, -0.00123, 235423424.43252);
  int r2 = s21_sprintf(
      str2, "%+-20e%010.*e%-*.16e%#025.10e%*.*e%*.15e%#010.*e%25.16e",
      2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15, 11111.22,
      16, -3245.3425342, 16, -0.00123, 235423424.43252);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_E) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(str1, "%+-25.4E%25.*E%-*.10E%#02.E%*.*E%*.15E%*E%12.16E",
                   3456.4325, 10, 23452.43242, 5, -0.05234, 25.432523432, 10, 2,
                   53242.4242, 10, 456789.43242, 25, 1111122222.34567899,
                   2345678.23453242);
  int r2 = s21_sprintf(str2, "%+-25.4E%25.*E%-*.10E%#02.E%*.*E%*.15E%*E%12.16E",
                       3456.4325, 10, 23452.43242, 5, -0.05234, 25.432523432,
                       10, 2, 53242.4242, 10, 456789.43242, 25,
                       1111122222.34567899, 2345678.23453242);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_f) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(
      str1, "%+-10.5f%+10.2f%15.16f%+*.10f%*.16f%-10.*f%25.*f%25.f%#+10.f%*.*f",
      2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245,
      2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
      34567.43244);
  int r2 = s21_sprintf(
      str2, "%+-10.5f%+10.2f%15.16f%+*.10f%*.16f%-10.*f%25.*f%25.f%#+10.f%*.*f",
      2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245,
      2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
      34567.43244);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_o) {
  char str1[510] = {0};
  char str2[510] = {0};
  unsigned short h = 253;
  unsigned long l = 4325234324242l;
  int r1 = sprintf(str1, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                   12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
  int r2 =
      s21_sprintf(str2, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                  12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_x) {
  char str1[510] = {0};
  char str2[510] = {0};
  unsigned short h = 345;
  unsigned long l = 52342353242l;
  int r1 = sprintf(str1,
                   "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%20."
                   "*x%#10.*x%*.5hx%10.25lx",
                   235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                   8, 23452, 10, 34254, 3, 33334, 10, h, l);
  int r2 = s21_sprintf(str2,
                       "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*."
                       "10x%20.*x%#10.*x%*.5hx%10.25lx",
                       235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
                       3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_X) {
  char str1[510] = {0};
  char str2[510] = {0};
  unsigned short h = 234;
  unsigned long l = 4325243132l;
  int r1 = sprintf(str1,
                   "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%21.*"
                   "X%#12.*X%*.8hx%14.12lX",
                   235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                   8, 23452, 10, 34254, 3, 33334, 10, h, l);
  int r2 = s21_sprintf(str2,
                       "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%"
                       "21.*X%#12.*X%*.8hx%14.12lX",
                       235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
                       3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_u) {
  char str1[510] = {0};
  char str2[510] = {0};
  unsigned short h = 115;
  unsigned long l = 123325242342l;
  int r1 =
      sprintf(str1, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu%u",
              4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u,
              20, 2432u, l, h, 4294967295u);
  int r2 = s21_sprintf(
      str2, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu%u", 4321u,
      34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u, 20, 2432u, l,
      h, 4294967295u);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_s) {
  char str1[510] = {0};
  char str2[510] = {0};
  wchar_t s[10] = {'h', 'e', 'l', 'l', 'o'};
  int r1 = sprintf(str1, "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15ls%15.3ls",
                   "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10,
                   "QWERTY", 15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
  int r2 =
      s21_sprintf(str2, "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15ls%15.3ls",
                  "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10,
                  "QWERTY", 15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_p) {
  char str1[510] = {0};
  char str2[510] = {0};
  void *p1 = (void *)0x123456789;
  void *p2 = (void *)4325234;
  void *p3 = (void *)0x123f324b;
  void *p4 = (void *)432520;
  int r1 = sprintf(str1, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4, p2,
                   10, p3, p1, 10, p4);
  int r2 = s21_sprintf(str2, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4,
                       p2, 10, p3, p1, 10, p4);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_percent) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(str1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  int r2 = s21_sprintf(str2, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_g) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(
      str1,
      "[%g] [%25g] [%-10g] [%#-15g] [%017g] [%#05.5g] [%#010.16g] "
      "[%+#8.6g] [%*.8g] [%#-10.*g] [%+#12.16g] [%*.*g] [%015g] [%0#15.10g]",
      43242.43242, 123432.43242, 1234.234242, 0001.1234, -34252.43242, 1234.5,
      111.432534243243242, 4324.43242, 25, -3213.43242, 16, -43.43242353242342,
      111.24324242, 25, 5, 7.342, 3456.3424, -324234.234);
  int r2 = s21_sprintf(
      str2,
      "[%g] [%25g] [%-10g] [%#-15g] [%017g] [%#05.5g] [%#010.16g] "
      "[%+#8.6g] [%*.8g] [%#-10.*g] [%+#12.16g] [%*.*g] [%015g] [%0#15.10g]",
      43242.43242, 123432.43242, 1234.234242, 0001.1234, -34252.43242, 1234.5,
      111.432534243243242, 4324.43242, 25, -3213.43242, 16, -43.43242353242342,
      111.24324242, 25, 5, 7.342, 3456.3424, -324234.234);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_G) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(str1,
                   "[%G] [%25G] [%#-15G] [%017G] [%#05.5G] [%#010.16G] "
                   "[%+#8.6G] [%*.8G] [%#-10.*G] [%+#12.16G] [%*.*G]",
                   43242.43242, 123432.43242, 0001.1234, -34252.43242, 1234.5,
                   111.432534243243242, 4324.43242, 25, -3213.43242, 16,
                   -43.43242353242342, 111.24324242, 25, 5, 7.342);
  int r2 = s21_sprintf(str2,
                       "[%G] [%25G] [%#-15G] [%017G] [%#05.5G] [%#010.16G] "
                       "[%+#8.6G] [%*.8G] [%#-10.*G] [%+#12.16G] [%*.*G]",
                       43242.43242, 123432.43242, 0001.1234, -34252.43242,
                       1234.5, 111.432534243243242, 4324.43242, 25, -3213.43242,
                       16, -43.43242353242342, 111.24324242, 25, 5, 7.342);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(to_upper_test) {
  char destination[] = "Here w0 are123\0";
  char *test01 = s21_to_upper(destination);
  ck_assert_str_eq(test01, "HERE W0 ARE123");
  free(test01);

  char destination2[] = "Here w0 are\n\0";
  char *test02 = s21_to_upper(destination2);
  ck_assert_str_eq(test02, "HERE W0 ARE\n");
  free(test02);

  char destination3[] = "a\n\0";
  char *test03 = s21_to_upper(destination3);
  ck_assert_str_eq(test03, "A\n");
  free(test03);

  char destination4[] = " \n\0";
  char *test04 = s21_to_upper(destination4);
  ck_assert_str_eq(test04, " \n");
  free(test04);

  char destination5[] = " \0";
  char *test05 = s21_to_upper(destination5);
  ck_assert_str_eq(test05, " ");
  free(test05);

  char destination6[] = "\n\0";
  char *test06 = s21_to_upper(destination6);
  ck_assert_str_eq(test06, "\n");
  free(test06);

  char destination7[] = "\0";
  char *test07 = s21_to_upper(destination7);
  ck_assert_str_eq(test07, "");
  free(test07);
}
END_TEST

START_TEST(to_lower_test) {
  char destination[] = "HERE W0 ARE123\0";
  char *test01 = s21_to_lower(destination);
  ck_assert_str_eq(test01, "here w0 are123");
  free(test01);

  char destination2[] = "HERE W0 ARE\n\0";
  char *test02 = s21_to_lower(destination2);
  ck_assert_str_eq(test02, "here w0 are\n");
  free(test02);

  char destination3[] = "A\n\0";
  char *test03 = s21_to_lower(destination3);
  ck_assert_str_eq(test03, "a\n");
  free(test03);

  char destination4[] = " \n\0";
  char *test04 = s21_to_lower(destination4);
  ck_assert_str_eq(test04, " \n");
  free(test04);

  char destination5[] = " \0";
  char *test05 = s21_to_lower(destination5);
  ck_assert_str_eq(test05, " ");
  free(test05);

  char destination6[] = "\n\0";
  char *test06 = s21_to_lower(destination6);
  ck_assert_str_eq(test06, "\n");
  free(test06);

  char destination7[] = "\0";
  char *test07 = s21_to_lower(destination7);
  ck_assert_str_eq(test07, "");
  free(test07);
}
END_TEST

START_TEST(insert_test) {
  char *s1 = "School-21 test";
  char *s2 = "insert ";
  char *s3 = "amogus";
  char *s4 = "is";
  char *s5 = "shrek";
  char *res1 = s21_insert(s1, " ", 3);
  char *res2 = s21_insert(s5, s3, 5);
  char *res3 = s21_insert(s3, s5, 0);
  char *res4 = s21_insert(s5, s4, 5);
  char *res5 = s21_insert(s2, s1, 4);

  ck_assert_str_eq(res1, "Sch ool-21 test");
  ck_assert_str_eq(res2, "shrekamogus");
  ck_assert_str_eq(res3, "shrekamogus");
  ck_assert_str_eq(res4, "shrekis");
  ck_assert_str_eq(res5, "inseSchool-21 testrt ");

  free(res1);
  free(res2);
  free(res3);
  free(res4);
  free(res5);
}
END_TEST

START_TEST(trim_test) {
  char dest[] = "-=Hello=-\0";
  char *test01 = s21_trim(dest, "-");
  ck_assert_str_eq(test01, "=Hello=\0");
  free(test01);

  char dest2[] = "-Hello\n\0";
  char *test02 = s21_trim(dest2, "-");
  ck_assert_str_eq(test02, "Hello\n\0");
  free(test02);

  char dest3[] = "a\0";
  char *test03 = s21_trim(dest3, "a");
  ck_assert_str_eq(test03, "");
  free(test03);

  char dest4[] = " \n\0";
  char *test04 = s21_trim(dest4, "\n");
  ck_assert_str_eq(test04, " ");
  free(test04);

  char dest5[] = "\n\0";
  char *test05 = s21_trim(dest5, "\0");
  ck_assert_str_eq(test05, "\n");
  free(test05);

  char dest6[] = " \0";
  char *test06 = s21_trim(dest6, " ");
  ck_assert_str_eq(test06, "");
  free(test06);
}
END_TEST

Suite *lib_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("Suite tests");
  tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);
  tcase_add_test(tc_core, test_memchr);
  tcase_add_test(tc_core, test_memcmp);
  tcase_add_test(tc_core, test_memcpy);
  tcase_add_test(tc_core, test_memmove);
  tcase_add_test(tc_core, test_memset);
  tcase_add_test(tc_core, test_strcat);
  tcase_add_test(tc_core, test_strncat);
  tcase_add_test(tc_core, test_strchr);
  tcase_add_test(tc_core, test_strcmp);
  tcase_add_test(tc_core, test_strncmp);
  tcase_add_test(tc_core, test_strcpy);
  tcase_add_test(tc_core, test_strncpy);
  tcase_add_test(tc_core, test_strcspn);
  tcase_add_test(tc_core, test_strerror);
  tcase_add_test(tc_core, test_strlen);
  tcase_add_test(tc_core, test_strpbrk);
  tcase_add_test(tc_core, test_strrchr);
  tcase_add_test(tc_core, test_strspn);
  tcase_add_test(tc_core, test_strstr);
  tcase_add_test(tc_core, test_strtok);
  tcase_add_test(tc_core, s21_sprintf_test1);
  tcase_add_test(tc_core, s21_sprintf_test2);
  tcase_add_test(tc_core, s21_sprintf_test3);
  tcase_add_test(tc_core, s21_sprintf_test4);
  tcase_add_test(tc_core, s21_sprintf_test_d);
  tcase_add_test(tc_core, s21_sprintf_test_i);
  tcase_add_test(tc_core, s21_sprintf_test_c);
  tcase_add_test(tc_core, s21_sprintf_test_e);
  tcase_add_test(tc_core, s21_sprintf_test_E);
  tcase_add_test(tc_core, s21_sprintf_test_f);
  tcase_add_test(tc_core, s21_sprintf_test_o);
  tcase_add_test(tc_core, s21_sprintf_test_x);
  tcase_add_test(tc_core, s21_sprintf_test_X);
  tcase_add_test(tc_core, s21_sprintf_test_u);
  tcase_add_test(tc_core, s21_sprintf_test_s);
  tcase_add_test(tc_core, s21_sprintf_test_p);
  tcase_add_test(tc_core, s21_sprintf_test_percent);
  tcase_add_test(tc_core, s21_sprintf_test_g);
  tcase_add_test(tc_core, s21_sprintf_test_G);
  tcase_add_test(tc_core, to_upper_test);
  tcase_add_test(tc_core, to_lower_test);
  tcase_add_test(tc_core, insert_test);
  tcase_add_test(tc_core, trim_test);
  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;
  s = lib_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
