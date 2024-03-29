#include "head.h"

void read_hist(t_env *env) {
  t_hist *hist = env->hist;
  t_stack *stack;
  char line[50];
  char *type[] = {"none", "int8", "int16", "int32", "float", "double"};

  while ( hist != NULL) {
        ftoa(line, (double)hist->line);
        print(env->rules.keyword[hist->opt]);
        print(" (line: ");
        print(line);
        print(")\n  NULL");
        stack = hist->stack;
         	while ( stack != NULL) {
              print(" <- ");
              print(stack->val.value);
              print("(");
              print(type[stack->val.type]);
              print(")");
              stack = stack->next;
          }
        print("\n\n");
        hist = hist->next;
    }
}

int gettype(t_env *env, char *type, double val){
  int i, valid = -1;
  char *allow[] = {"int8", "int16", "int32", "float", "double"};

  (void) val;
  for ( i = -1; ++i < 5;)
      if (my_cmp(type, allow[i])){
        valid = i;
    }
  if (valid == -1){
    errordet(env, "Invalid type", type);
    return (0);
  }
  return ++valid;
}

int typed(int type, char *val, t_env *env){
  int i = 0;
  int change = 0;
  t_val value = {0, ""};
  char *allow[] = {"int8", "int16", "int32", "float", "double"};
  double limit[3][2] = {{-128.0, 127.0}, {-32768.0, 32767.0},
                        {-2147483648.0, -2147483647.0}};

  if (type < 4 && (double)(int)atof(val) != atof(val)){
    warningdet(env, "Invalid type", allow[type - 1]);
    return (addhist(env, 13, value) + 5);
  }
  for (i = 0; type < 4 && i < 3; ++i)
    if (type == i + 1 && (atof(val) < limit[i][0] || atof(val) > limit[i][1])) {
      type += 1;
      change += 1;
    }
  if (change == 1) {
    warningdet(env, "Invalid type", allow[type - 1 - change]);
    addhist(env, 13, value);
  }
  return (type);
}
