#include "ast.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct term* newTerm(enum termType t, int v) {
  struct term *te = malloc(sizeof(struct term));
  te->type = t; 
  te->val = v; 
  return te;
}

struct exp* newExprTerm(struct term* te) {
  struct exp *e = malloc(sizeof(struct exp));
  e->isTerm = true;
  e->t = te;
  e->le = NULL;
  e->re = NULL;
  return e;
}


struct exp* newExpr(struct exp* e1, enum logicOp op, struct exp* e2) {
  struct exp *e = malloc(sizeof(struct exp));
  e->isTerm = false;
  e->t = NULL;
  e->le = e1;
  e->re = e2;
  return e;
}

struct action* newAction(struct exp* ex) {
  struct action *a = malloc(sizeof(struct action));
  a->e = ex;
  return a;
}

struct pattern* newPattern(struct exp* ex) {
  struct pattern *pa = malloc(sizeof(struct pattern));
  pa->e = ex;
  pa->begin = false;
  pa->end = false;
  return pa;
}

struct pattern* newPatternBegin() {
  struct pattern *pa = malloc(sizeof(struct pattern));
  pa->e = NULL;
  pa->begin = true;
  pa->end = false;
  return pa;
}

struct pattern* newPatternEnd() {
  struct pattern *pa = malloc(sizeof(struct pattern));
  pa->e = NULL;
  pa->begin = false;
  pa->end = true;
  return pa;
}

struct ast* newStatement(struct pattern* pa, struct action* ac) {
  struct ast *as = malloc(sizeof(struct ast));
  as->nodetype = 0; // TODO: See if this is needed at all
  as->p = pa;
  as->a = ac;
  as->next = NULL;
  return as;
}

void walkTerm(struct term *t) {
  if (t == NULL) {
    printf("( Empty Term )\n");
  } else {
    int val = t->val;
    if (t->type == Positional) {
      printf("(Term Postional $%d )\n", val);
    } else if (t->type == Constant) {
      printf("(Term Constant $%d )\n", val);
    } else {
      printf("(Term UNKOWN TYPE )\n");
    } 
  }
}

void printLogicOp(enum logicOp op) {
  if (op == ANDOp) printf(" AND \n");
  else if (op == OROp) printf(" OR \n");
  else if (op == GTOp) printf(" <= \n");
  else if (op == LTOp) printf(" >= \n");
  else if (op == EQOp) printf(" == \n");
  else printf(" UNKNOWN OP\n");
}

void walkExp(struct exp *e) {
  if (e == NULL) {
    printf("( EMPTY Expression )\n");
  } else {
    if (e->isTerm) {
      walkTerm(e->t);
    } else {
      walkExp(e->le);
      printLogicOp(e->op);
      walkExp(e->re);
    }
  }
}

void patternWalk(struct pattern *p) {
  if (p == NULL) {
    printf("( EMPTY PATTERN )\n");
  } else if (p->begin) {
    printf("( BEGIN )\n");
  } else if (p->end) {
    printf("( END )\n");
  } else {
    walkExp(p->e);
  }
}

void actionWalk(struct action *a) {
  if (a == NULL) {
    printf("( Empty ACTION )\n");
  } else {
    walkExp(a->e);
  }
}

void astWalk(struct ast *as) {
  if (as == NULL) {
    // We are done
  } else {
    patternWalk(as->p);
    // Possibly add some form of delimiter here
    actionWalk(as->a);
    // Walk next instruction
    astWalk(as->next);
  }
}

