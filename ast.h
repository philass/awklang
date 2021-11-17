#include <stdbool.h>

enum logicOp { 
  AND, 
  OR,
  GT,
  LT,
  EQ
};

struct ast {
  int nodetype;
  struct pattern *p;
  struct action *a;
  struct ast *next;
};

struct pattern {
  bool begin;
  bool end;
  struct exp *e;
};

struct action {
  // We will default to print until later
  struct exp *e;
};

struct exp {
  bool isTerm;
  enum logicOp op;
  struct term *t;
  struct exp *le;
  struct exp *re;
};

struct term {
  int type;
  int val;
};

int main() {
  return 0;
}
