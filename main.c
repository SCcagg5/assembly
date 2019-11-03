#include "head.h"


int           main(int argc, char *argv[])
{
  t_env       env;
  t_call_list list = {{free_all, read_inst, trim, readfile}, 4};
  init_env(&env, argc, argv);
  while (list.size-- && !env.err)
    list.call[list.size](&env);
  return (env.err);
}

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

int           init_env(t_env *env, int argc, char *argv[]) {
  t_rules rules = {{"push", "assert", "add", "sub", "mul", "div", "mod",
                    "pop", "dump", "print", "exit", "hist", NULL, "typup"},
                  {push_f, assert_f, add_f, sub_f, mul_f, div_f,
                  mod_f, pop_f, dump_f, print_f, exit_f, hist_f}
  };
  if (argc == 1)
    return (error(env, "Invalid number of arg"));
  env->err = 0;
  env->file_name = argv[1];
  env->inst = malloc(sizeof(char));
  if (env->inst == NULL)
    return (error(env, "Invalid malloc"));
  env->inst[0] = '\0';
  env->rules = rules;
  env->hist = NULL;
  env->stack = NULL;
  env->line = 1;
  return (0);
}

int           readfile(t_env *env) {
  int         fd, i;
  int         sz = 1;
  char        buff[100];

  fd = open(env->file_name, O_RDONLY);
  if (fd < 0)
    return(error(env, "Can't open file"));
  while (sz != 0)
    {
      for (i = 0; i < 100; ++i)
        buff[i] = '\0';
      sz = read(fd, buff, 99);
      env->inst = concat(env->inst, buff);
    }
  return (0);
}

int           read_inst(t_env *env) {
  int         i = 0;
  char        opt[100];

  while (*env->inst && i < 7) {
    if (*env->inst == '\n' || *env->inst == ' ') {
      opt[i] = '\0';
      i = 0;
      if (get_details(env, opt))
        return (1);
      env->line++;
    }
    opt[i++] = *env->inst++;
  }
  if (i > 6){
    print("\n'");
    print(opt);
    print("' <- ");
    return (error(env, "Invalid instruction"));
  }
  return (0);
}

int           free_all(t_env *env) {
  t_stack *stack;
  t_hist *hist = env->hist;
  t_stack *tmps;
  t_hist *tmph;
  while ( hist != NULL) {
      stack = hist->stack;
     	while ( stack != NULL) {
          tmps = stack;
          stack = stack->next;
          free(tmps);
      }
      tmph = hist;
      hist = hist->next;
      free(tmph);
  }
  stack = env->stack;
  while (stack != NULL) {
      tmps = stack;
      stack = stack->next;
      free(tmps);
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
    print("\n'");
    print(opt);
    print("' <- ");
    return (error(env, "Invalid instruction"));
  }
  if (!checkcall(opt, type, val)){
    print("\n'");
    print(opt);
    print("' <- ");
    return (error(env, "Invalid instruction"));
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

int popstack(t_env *env, char *ret[], int *i){
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

int getstack(t_env *env, char *ret[], int *i){
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
