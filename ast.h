#include <stdbool.h>

enum logicOp { 
  ANDOp, 
  OROp,
  GTOp,
  LTOp,
  EQOp
};

enum termType { 
  Positional, 
  Constant
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
  bool isTerm; // 0 for Number | 1 for postional
  enum logicOp op;
  struct term *t;
  struct exp *le;
  struct exp *re;
};

struct term {
  enum termType type;
  int val;
};


// This function walk throught the AST and prints the structure
// Very helpful for debugging purposes
void astWalk(struct ast *as);

struct term* newTerm(enum termType t, int v);

struct exp* newExprTerm(struct term* te);

struct exp* newExpr(struct exp* e1, enum logicOp op, struct exp* e2);

struct action* newAction(struct exp* ex);

struct pattern* newPattern(struct exp* ex);

struct pattern* newPatternBegin();

struct pattern* newPatternEnd();

struct ast* newStatement(struct pattern* pa, struct action* ac);
