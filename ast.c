#include "ast.h"
#include <stddef.h>
#include <stdio.h>

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
