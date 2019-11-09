#include "head.h"

int addhist(t_env *env, t_opt opt, t_val val){
  t_hist * hist;
  t_stack *stack;
  t_stack * tmp;

  hist = malloc(sizeof(t_hist));
  hist->line = env->line;
  hist->opt = opt;
  hist->val = val;
  hist->stack = NULL;
  stack = env->stack;
  while (stack != NULL) {
    tmp = malloc(sizeof(t_stack));
    my_strcpy(tmp->val.value, stack->val.value);
    tmp->val.type = stack->val.type;
    tmp->next = hist->stack;
    hist->stack = tmp;
    stack = stack->next;
  }
  hist->next =  env->hist;
  env->hist = hist;
  return 0;
}

int addstack(t_env *env, t_val val){
  t_stack * stack;
  stack = malloc(sizeof(t_stack));
  my_strcpy(stack->val.value, val.value);
  stack->val.type = val.type;
  stack->next =  env->stack;
  env->stack = stack;
  return 0;
}

int stacksize(t_env *env){
  t_stack *stack;
  int i = 0;
  stack = env->stack;
  while (stack != NULL) {
      i += 1;
      stack = stack->next;
  }
  return (i);
}

int popstack(t_env *env, char ret[], int *i){
  t_stack * stack;
  stack = env->stack;
  if (stack == NULL){
    return (1);
  }
  my_strcpy(ret, env->stack->val.value);
  if (*i < (int)env->stack->val.type){
    *i = env->stack->val.type;
  }
  env->stack = env->stack->next;
  free(stack);
  return (0);
}

int getstack(t_env *env, char ret[], int *i){
  t_stack * stack;
  stack = env->stack;
  if (stack == NULL){
    return (1);
  }
  my_strcpy(ret, env->stack->val.value);
  if (*i < (int)env->stack->val.type){
    *i = env->stack->val.type;
  }
  return (0);
}
