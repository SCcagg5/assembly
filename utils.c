#include "head.h"

void read_hist(t_env *env) {
  t_stack *stack;
  t_hist *hist = env->hist;
  char line[50];
   	while ( hist != NULL) {
        ftoa(line, (double)hist->line);
        print(env->rules.keyword[hist->opt]);
        print(" (line: ");
        print(line);
        print(")\n  ");
        print("NULL");
        stack = hist->stack;
         	while ( stack != NULL) {
              print(" <- ");
              print(stack->val.value);
              stack = stack->next;
          }
        print("\n\n");
        hist = hist->next;

    }

}
