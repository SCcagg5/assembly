#include "head.h"


int           trim(t_env *env) {
  int         i = 0;
  int         j = 0;
  int         k = 0;
  int         sw = 0;
  char       *allow = " .-abcdefghijklmnopqrstuvwxyz1234567890()\n";

  for(i = 0; env->inst[i] != '\0'; ++i){
    sw = 0;
    for (k = 0; k < 43; ++k){
      if (env->inst[i] == allow[k])
        sw = 1;
    }
    if (!sw){
      for (j = i; env->inst[j] != '\0'; ++j)
          env->inst[j] = env->inst[j+1];
      env->inst[j] = '\0';
      i--;
    }
  }
  return (0);
}

int           get_details(t_env *env, char *opt) {
  int         i = 0;
  char        type[10];
  char        val[50];

  type[i] = '\0';
  if(*env->inst++ != '\n') {
    while (*env->inst != '(' && *env->inst != '\0'
        && *env->inst != ')' && i < 10)
        type[i++] = *env->inst++;
    type[i] = '\0';
    env->inst++;
    i = 0;
    while (*env->inst != '(' && *env->inst != '\0'
        && *env->inst != ')' && i < 50)
        val[i++] = *env->inst++;
    env->inst += 2;
  }
  val[i] = '\0';
  return(compute(env, opt, type, val));
}


int           compute(t_env *env, char *opt, char *type, char *val){
  int i;
  int sw = 0;

  for (i = 0; env->rules.keyword[i] != NULL; ++i)
    if (my_cmp(opt, env->rules.keyword[i])){
      sw = 1;
      break;
    }
  if (!sw) {
    return (errordet(env, "Invalid instruction", opt));
  }
  if (!checkcall(opt, type, val)){
    return (errordet(env, "Invalid instruction", opt));
  }
  return env->rules.call[i](env, opt, type, val);
}

int checkcall(char *opt, char *type, char *val){
  if ((my_cmp(type, "") || my_cmp(val, ""))
   && (my_cmp(opt, "assert") || my_cmp(opt, "push"))){
      return (0);
    }
  if ((!my_cmp(type, "") || !my_cmp(val, ""))
    && (!my_cmp(opt, "assert") && !my_cmp(opt, "push"))){
      return (0);
  }
  return 1;
}
