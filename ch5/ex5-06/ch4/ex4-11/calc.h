#define MAX_VARS 27

#define NUMBER '0'
#define COMMAND '!'
#define SPECIAL_OP '&'
#define VAR_ASSGN 'V'
#define VAR_OFFSET 64
#define VAR_REF 'v'
#define LAST_OUT '$'


void push(double f);
double pop();
int get_op(char *);
int get_ch();
void proc_cmd(char);

void peek();
void clear();
void duplicate();
void swap();
void dump();
