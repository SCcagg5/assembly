#include "head.h"

int push_f(t_env *env, char *opt, char *type, char *val){
  t_val value;
  value.type = 0;
  my_strcpy(value.value, val);
  addstack(env, value);
  addhist(env, 0, value);
 return (0);
}
int assert_f(t_env *env, char *opt, char *type, char *val){
   t_val value = {0, ""};
   addhist(env, 1, value);
 return (0);
 }

int add_f(t_env *env, char *opt, char *type, char *val){
   t_val value = {0, ""};
   char ret1[50];
   char ret2[50];
   popstack(env, ret1);
   popstack(env, ret2);
   ftoa(ret1, atof(ret2) + atof(ret1));
   value.type = 0;
   my_strcpy(value.value, ret1);
   addstack(env, value);
   addhist(env, 2, value);
 return (0);
 }

int sub_f(t_env *env, char *opt, char *type, char *val){
  t_val value = {0, ""};
  char ret1[50];
  char ret2[50];
  popstack(env, ret1);
  popstack(env, ret2);
  ftoa(ret1, atof(ret2) - atof(ret1));
  value.type = 0;
  my_strcpy(value.value, ret1);
  addstack(env, value);
  addhist(env, 2, value);
 return (0);
 }

int mul_f(t_env *env, char *opt, char *type, char *val){
  t_val value = {0, ""};
  char ret1[50];
  char ret2[50];
  popstack(env, ret1);
  popstack(env, ret2);
  ftoa(ret1, (atof(ret2) * atof(ret1)));
  value.type = 0;
  my_strcpy(value.value, ret1);
  addstack(env, value);
  addhist(env, 4, value);
 return (0);
 }

int div_f(t_env *env, char *opt, char *type, char *val){
   t_val value = {0, ""};
   char ret1[50];
   char ret2[50];
   popstack(env, ret1);
   popstack(env, ret2);
   ftoa(ret1, atof(ret2) / atof(ret1));
   value.type = 0;
   my_strcpy(value.value, ret1);
   addstack(env, value);
   addhist(env, 5, value);
 return (0);
 }

int mod_f(t_env *env, char *opt, char *type, char *val){
   t_val value = {0, ""};
   char ret1[50];
   char ret2[50];
   popstack(env, ret1);
   popstack(env, ret2);
   ftoa(ret1, my_mod(atof(ret2), atof(ret1)));
   value.type = 0;
   my_strcpy(value.value, ret1);
   addstack(env, value);
   addhist(env, 6, value);
 return (0);
 }

int pop_f(t_env *env, char *opt, char *type, char *val){
   t_val value = {0, ""};
   char ret[50];
   popstack(env, ret);
   addhist(env, 7, value);
 return (0);
 }

int dump_f(t_env *env, char *opt, char *type, char *val){
   t_val value = {0, ""};
   t_stack *stack = env->stack;
    	while (stack != NULL) {
         print(stack->val.value);
         print("\n");
         stack = stack->next;
     }
   addhist(env, 8, value);
 return (0);
 }

int print_f(t_env *env, char *opt, char *type, char *val){
   t_val value = {0, ""};
   addhist(env, 9, value);
 return (0);
 }

int exit_f(t_env *env, char *opt, char *type, char *val){
   t_val value = {0, ""};
   addhist(env, 10, value);
 return (1);
 }

 int hist_f(t_env *env, char *opt, char *type, char *val){
    t_val value = {0, ""};
    addhist(env, 11, value);
    read_hist(env);
  return (0);
  }
