#include "head.h"

int error(t_env *env, char err[]){
  print("[ERROR] ");
  print(err);
  print("\n");
  env->err = 1;
  return(1);
}

int errordet(t_env *env, char err[], char opt[]){
  char *line = malloc(10 * sizeof(char));

  ftoa(line, (double)env->line);
  print("[ ERROR   | l:");
  print(line);
  print(" ] ");
  print(err);
  print(" -> ");
  print(opt);
  print("\n");
  env->err = 1;
  free(line);
  return(1);
}

int warningdet (t_env *env, char err[], char opt[]){
  char *line = malloc(10 * sizeof(char));

  ftoa(line, (double)env->line);
  print("[ Warning | l:");
  print(line);
  print(" ] ");
  print(err);
  print(" -> ");
  print(opt);
  print("\n");
  env->err = 0;
  free(line);
  return(0);
}

int warning(t_env *env, char err[]){
  print("[WARNING] ");
  print(err);
  print("\n");
  env->err += 0;
  return(0);
}

void print(char* text)
{
  while (*text && write(1, text++, 1));
}

int	my_strlen(char *str)
{
  int	i = 0;
  while (str && str[i++] != '\0');
  return (i);
}

char *concat(char *s1, char*s2)
{
  int i;
  int size1 = my_strlen(s1) - 1;
  int size2 = my_strlen(s2);
  s1 = my_realloc(s1, size1 + size2);
  for (i = size1; i < size1 + size2; ++i){
    s1[i] = s2[i - size1];
  }
  s1[i] = '\0';
  return s1;
}

char	*my_realloc(char *ptr, int size)
{
  char	*ptr_realloc;
  int	c = 0;

  if (ptr == NULL || size < 1)
    return (NULL);
  ptr_realloc = malloc(sizeof(char) * (size + 1));
  if (ptr_realloc == NULL)
    return (NULL);
  while (c != size && ptr[c] != '\0'){
      ptr_realloc[c] = ptr[c];
      c += 1;
  }
  if (ptr[c] == '\0')
    while (c < size)
      ptr_realloc[c++] = '\0';
  ptr_realloc[c] = '\0';
  free(ptr);
  return (ptr_realloc);
}

int		my_cmp(const char *str1, const char *str2)
{
  int i = 0;
  for (i = 0; str1[i] != '\0' && str2[i] != '\0'
      && str2[i] == str1[i]; ++i);
  return (str1[i] == str2[i]);
}

char *my_strcpy(char *destination, char *source)
{
    char *start = destination;
    while(*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
    return start;
}

int char2int(char c){
    return c - '0';
}

double my_mod(double i, double j){
  double res = j;
  while (res > 0){
    res -= i;
  }
  res += i;
  return res;
}


double atof(const char str[]){
    double value, power;
    int i, sign;

    i = 0;
    sign = (str[i] == '-') ? -1 : 1;
    if (str[i] == '+' || str[i] == '-')
        i++;
    for (value = 0.000000; str[i] != '.' && str[i] != '\0'; ++i)
        value = 10.000000 * value + char2int(str[i]);
    if (str[i] == '.'){
        i++;
    }
    for (power = 1.000000; str[i] != '\0'; ++i)
    {
        value = 10.000000 * value + char2int(str[i]);
        power *= 10;
    }
    return sign * value /power;
}

void ftoa(char *dist, double num) {
  int i, j;
  int numI = (int)num;
  int tmp[50];

  for (i = 0; numI / 10 != 0; i++) {
    tmp[i] = numI % 10;
    numI /= 10;
  }
  tmp[i] = numI;
  for (j = 0; i >= 0; i--) {
    dist[j++] = tmp[i] + '0';
  }
  dist[j++] = '.';
  num -= (int)num;
  for (i = 0; i < 10; i++) {
    num *= 10;
    dist[j++] = (int)num + '0';
    num -= (int)num;
  }
  dist[j] = '\0';
  format(dist);
}

void addtolast(char *dist){
  int i, j;

  i = 0;
  j = 0;
  for (i = 0; dist[i] != '.'; ++i);
  for (j = i; dist[j] != '\0'; ++j);
  j -= 1;
  dist[j] = dist[j] + 1;
}

void format(char *dist){
  int i, j, k, ard;
  for (i = 0; dist[i] != '.'; ++i);
  for (j = i; dist[i] != '\0'; ++i){
    if (dist[i] != '0'){
      j = i + 1;
      if (dist[i] == '9'){
        ard = 0;
        for (k = j; dist[k] != '\0'; ++k){
          ard += dist[k] == '9' || dist[k] == '8' ? 0 : 1;
        }
        if (ard == 0){
          dist[--j] = '\0';
          addtolast(dist);
          break;
        }
      }
    }
  }
  if (dist[j - 1] == '.')
    --j;
  dist[j] = '\0';
}
