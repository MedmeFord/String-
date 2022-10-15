#include "s21_string.h"

#include <math.h>

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *buff = (unsigned char *)str;
  unsigned char *result = s21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (buff[i] == c) {
      result = &buff[i];
      i = n + 1;
    }
  }
  return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *buff1 = (unsigned char *)str1;
  unsigned char *buff2 = (unsigned char *)str2;
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (buff1[i] != buff2[i]) {
      if (buff1[i] > buff2[i]) {
        result = 1;
      } else {
        result = -1;
      }
      i = n + 1;
    }
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *s;
  unsigned char *d;
  d = (unsigned char *)dest;
  s = (unsigned char *)src;
  unsigned long i = 0;
  while (i < n) {
    if (s != s21_NULL && d != s21_NULL && n != 0) {
      d[i] = s[i];
      i++;
    }
  }
  return d;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *dest1 = (char *)dest;
  char *src1 = (char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    if (src != s21_NULL) {
      dest1[i] = src1[i];
    }
  }
  return src != s21_NULL ? dest1 : s21_NULL;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  char *ch_str;
  ch_str = (char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    ch_str[i] = c;
  }
  return ch_str;
}

char *s21_strcat(char *dest, const char *src) {
  int len1 = s21_strlen(dest);
  int len2 = s21_strlen(src);
  int len = len1 + len2 + 1;
  for (int i = len1; i < len; i++) {
    dest[i] = src[i - len1];
  }
  dest[len] = '\0';
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int len1 = s21_strlen(dest);
  int len2 = n;
  int len = len1 + len2;
  for (int i = len1; i < len; i++) {
    dest[i] = src[i - len1];
  }
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *res = s21_NULL;
  while ((*str != '\0') && (*str != c)) {
    str++;
  }
  if (*str == c) {
    res = ((char *)str);
  }
  return res;
}

int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  return (*str1 - *str2);
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  s21_size_t i = 1;
  if (n != 0) {
    while ((*str1 && (*str1 == *str2)) && (i < n)) {
      str1++;
      str2++;
      i++;
    }
    res = *str1 - *str2;
  }
  return res;
}

char *s21_strcpy(char *dest, const char *src) {
  int i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  if (n > 0) {
    while (src[i] != '\0' && i < n) {
      dest[i] = src[i];
      i++;
    }
  }

  return n > 0 ? dest : 0;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  int flag = 0;
  for (int i = 0; str1[i] != '\0'; i++) {
    for (int j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        flag = 1;
      }
    }
    if (flag == 0) {
      count++;
    }
  }
  return count;
}

char *s21_strerror(int errnum) {
  static char *arr[] = errlist;
  char *err;
  err = arr[errnum];
  static char unknown[1024] = {'\0'};
  if (err == s21_NULL || errnum >= MAX || errnum < 0) {
    char str[200] = {'\0'};
    s21_sprintf(str, "%d", errnum);
    s21_strcpy(unknown, "Unknown error: ");
    s21_strcat(unknown, str);
    err = unknown;
  }
  return err;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t i;
  i = 0;
  while (str[i]) {
    i++;
  }
  return i;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;
  while (*str1 != '\0') {
    for (int i = 0; str2[i] != '\0'; i++) {
      if (*str1 == str2[i]) {
        res = (char *)str1;
      }
      break;
    }
    str1++;
  }
  return res;
}

char *s21_strrchr(const char *str, int c) {
  char *res = s21_NULL;
  const char *start = str;
  int len = s21_strlen(str);
  str += len;
  while (*str != *start && *str != c) {
    str--;
  }
  if (*str == c) {
    res = (char *)str;
  }
  return res;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  if (*str1 != '\0' && *str2 != '\0') {
    while (*str1 == *str2) {
      count++;
      str1++;
      str2++;
    }
  }
  return count;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = s21_NULL;
  int i = 0, j;
  if (needle[i] == '\0') {
    res = (char *)&haystack[i];
  } else {
    while (haystack[i] != '\0') {
      j = 0;
      while (haystack[i + j] == needle[j] && haystack[i + j] != '\0') {
        if (needle[j + 1] == '\0') {
          res = (char *)&haystack[i];
        }
        j++;
      }
      i++;
      if (needle[j + 1] == '\0') {
        break;
      }
    }
  }
  return res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  int i = 0, j = 0, k = 0, flag = -1;
  char *str;
  if (src == s21_NULL || trim_chars == s21_NULL) {
    str = s21_NULL;
  } else if (s21_strlen(src) == 0) {
    str = s21_NULL;
  } else {
    str = malloc(sizeof(char) * s21_strlen(src) + 1);
    if (str == s21_NULL) {
      str = s21_NULL;
      free(str);
    } else {
      while (src[j]) {
        if (s21_strlen(trim_chars) != 0) {
          while (trim_chars[i]) {
            if (src[j] == trim_chars[i]) {
              flag = j;
            }
            i++;
          }
        }
        if (flag >= 0) {
          j++;
          flag = -1;
        } else {
          str[k] = src[j];
          k++;
          j++;
        }
        i = 0;
      }
      str[k] = '\0';
    }
  }
  return str;
}

// char *s21_strtok(char *str, const char *delim) {
//   static char *p;
//   char *k;
//   int flag = 0, len = 0;
//   if (!str) {
//     str = p;
//   }
//   k = str;
//   for (int i = 0; *str != '\0' && !flag; i++) {
//     for (int j = 0; delim[j] != '\0' && *str != '\0'; j++) {
//       if (*str == delim[j]) {
//         *str = '\0';
//         flag = 1;
//       }
//     }
//     str++;
//   }
//   len = strlen(str);
//   p = str + len + 1;
//   return (k[0] == '\0') ? s21_NULL : k;
// }

char *s21_strtok(char *str, const char *delim) {
  static char *tarr;
  char *res = s21_NULL;
  if (str) {
    tarr = str;
    while (*tarr && s21_strchr(delim, *tarr)) {
      *tarr++ = '\0';
    }
  }
  if (tarr && *tarr) {
    str = tarr;
    while (*tarr && !s21_strchr(delim, *tarr)) {
      ++tarr;
    }
    while (*tarr && s21_strchr(delim, *tarr)) {
      *tarr++ = '\0';
    }
    res = str;
  }
  return res;
}

void *s21_to_upper(const char *str) {
  char *res = s21_NULL;
  if (str != s21_NULL) {
    int size = s21_strlen(str) + 1;
    res = malloc(size * sizeof(char));
    int i;
    for (i = 0; str[i]; i++) {
      if (str[i] >= 97 && str[i] <= 122) {
        res[i] = str[i] - 32;
      } else {
        res[i] = str[i];
      }
    }
    res[i] = '\0';
  }
  return res;
}

void *s21_to_lower(const char *str) {
  char *res = s21_NULL;
  if (str != s21_NULL) {
    int size = s21_strlen(str) + 1;
    int i;
    res = malloc(size * sizeof(char));
    for (i = 0; str[i]; i++) {
      if (str[i] <= 90 && str[i] >= 65) {
        res[i] = str[i] + 32;
      } else {
        res[i] = str[i];
      }
    }
    res[i] = '\0';
  }
  return res;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *str1 = "";
  int i = 0, j = 0;
  if (src == s21_NULL || str == s21_NULL) {
    str1 = s21_NULL;
  }
  int size_src = s21_strlen(src);
  int size_str = s21_strlen(str);

  if (size_src == 0 || str1 == s21_NULL) {
    str1 = s21_NULL;
  } else if (size_src < (int)start_index) {
    str1 = s21_NULL;
  } else {
    str1 = (char *)malloc(sizeof(char) * (size_str + size_src + 1));
    if (str1 == s21_NULL) {
      str1 = s21_NULL;
      free(str1);
    } else {
      while (i < (size_src + size_str + 1)) {
        if (i == (int)start_index) {
          while (*str) {
            str1[i] = *str;
            str++;
            i++;
          }
        }
        str1[i] = src[j];
        i++;
        j++;
      }
    }
  }
  return str1;
}
