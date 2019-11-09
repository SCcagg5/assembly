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
    return (errordet(env, "Invalid instruction", opt));
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
