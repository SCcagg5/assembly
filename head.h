#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef   __ASSEMBL__
#define   __ASSEMBL__
/*----------------------- MACRO STA -----------------------------------*/
#define RED	"\x1B[31m"
#define GRN	"\x1B[32m"
#define YEL	"\x1B[33m"
#define BLU	"\x1B[34m"
#define MAG	"\x1B[35m"
#define CYN	"\x1B[36m"
#define WHT	"\x1B[37m"
#define NOR	"\x1B[00m"
#define CLEAR "\033c"
/*----------------------- MACRO END -----------------------------------*/

/*----------------------- ENUM  STA -----------------------------------*/
typedef enum   e_type
{
  NONE,
  INT8,
  INT16,
  INT32,
  FLOAT,
  DOUBLE
}              t_type;

typedef enum   e_opt
{
  PUSH,
  ASSERT,
  ADD,
  SUB,
  MUL,
  DIV,
  MOD,
  POP,
  DUMP,
  PRINT,
  EXIT,
  HIST
}              t_opt;

/*----------------------- ENUM  END -----------------------------------*/

/*----------------------- STRUC STA -----------------------------------*/
typedef struct s_val
{
  t_type type;
  char value[50];
}              t_val;

typedef struct s_stack
{
  t_val val;
  struct s_stack *next;
}              t_stack;

typedef struct s_hist
{
  int line;
  t_opt opt;
  t_val val;
  struct s_stack *stack;
  struct s_hist *next;
}              t_hist;

typedef struct s_rules
{
  char *keyword[13];
  int (*call[12])();
}              t_rules;

typedef struct s_env
{
  int err;
  char *file_name;
  char *inst;
  int line;
  t_rules rules;
  t_stack *stack;
  t_hist  *hist;
}              t_env;

typedef struct s_call_list {
    int (*call[10])();
    int size;
}              t_call_list;
/*----------------------- STRUC END -----------------------------------*/

/*----------------------- FUNCT STA -----------------------------------*/
int     readfile(t_env *env);
int     init_env(t_env *env, int argc, char *argv[]);
int	    my_strlen(char *str);
void    print(char* text);
int     error(t_env *env, char err[]);
char	 *my_realloc(char *ptr, int size);
char   *concat(char *s1, char*s2);
int read_inst(t_env *env);
int get_details(t_env *env, char *opt);
int trim(t_env *env);
int push_f(t_env *env, char *opt, char *type, char *val);
int assert_f(t_env *env, char *opt, char *type, char *val);
int add_f(t_env *env, char *opt, char *type, char *val);
int sub_f(t_env *env, char *opt, char *type, char *val);
int mul_f(t_env *env, char *opt, char *type, char *val);
int div_f(t_env *env, char *opt, char *type, char *val);
int mod_f(t_env *env, char *opt, char *type, char *val);
int pop_f(t_env *env, char *opt, char *type, char *val);
int dump_f(t_env *env, char *opt, char *type, char *val);
int print_f(t_env *env, char *opt, char *type, char *val);
int exit_f(t_env *env, char *opt, char *type, char *val);
int hist_f(t_env *env, char *opt, char *type, char *val);
int checkcall(char *opt, char *type, char *val);
int           compute(t_env *env, char *opt, char *type, char *val);
int		my_cmp(const char *str1, const char *str2);
int addhist(t_env *env, t_opt opt, t_val val);
void read_hist(t_env *env);

/*----------------------- FUNCT END -----------------------------------*/
#endif /* __ASSEMBL__ */
