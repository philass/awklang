#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: change this later to handle longer lines
int MAX_LINE_LENGTH = 1024;

bool isSpace(char letter) {
  return (letter == '\t' || letter == ' ');
}

// startIdxs and endIdxs need to be freed by the caller of this function
// they are heap allocated
void getWordIdxs(char *line, int **startIdxs, int **endIdxs, int *wordCount) {
  int numWords = 0;
  int letterIdx = 0;
  bool onSpace = true;
  while (line[letterIdx] != '\0') {
    if (isSpace(line[letterIdx])) {
      onSpace = true;
    } else {
      // We are on a letter
      if (onSpace) numWords++;
      onSpace = false;
    }
    letterIdx++;
  }
  int* wordStarts = malloc(numWords * sizeof(int));
  int* wordEnds = malloc(numWords * sizeof(int));
  int cw = 0;
  for (int i = 0; i < letterIdx; i++) {
    if (!isSpace(line[i]) && (i == 0 || isSpace(line[i-1]))) {
      wordStarts[cw] = i;
      cw++;
    }
    if (!isSpace(line[i]) && (i == letterIdx-1 || isSpace(line[i+1]))) {
      wordEnds[cw-1] = i;
    }
  }

  *startIdxs = wordStarts;
  *endIdxs = wordEnds;
  *wordCount = numWords;
}
  
int evalTerm(struct term *t, char* line, int *startIdxs, int *endIdxs, int wordCount) {
  if (t->type == Constant) {
    return t->val;
  }
  if (t->type == Positional) {
    int pos = t->val;
    if (pos > wordCount) {
      //don't do anything; variable doesn't exist
    }
    int wordLength = endIdxs[pos-1] - startIdxs[pos-1] + 1;
    int offset = startIdxs[pos-1];
    char str[wordLength];
    strcpy(str, line + offset, wordLength);
    int value = atoi(str);
    return value;
  }
}
    
    

}

void evalAction(struct action *a, char* line, int *startIdxs, int *endIdxs, int wordCount) {
  if (a->e != NULL) {
    if (e->isTerm) {
      int value = evalTerm(e->t, line, startIdxs, endIdxs, wordCount);
      printf("Value was \d\n", value);
    } else {
      printf("This branch has not been implemented\n");
    }
  } else {
    printf("This was an empty action\n");
  }
}


void eval(struct ast *a, FILE *f) {
  char line[MAX_LINE_LENGTH];

  while (fgets(line, MAX_LINE_LENGTH, f) != NULL) {
    // Break line up into words
    // Possible representation array for word starts, and word ends
    // In one pass we should be able to figure out the number of words
    
    // We need to extract the Positional Args that we care about...
    // That is the only part of the file parsing that depends on the AST
    int* startIdxs;
    int* endIdxs;
    int numWords;
    getWordIdxs(line, &startIdxs, &endIdxs, &numWords);

    // Now maybe test a dummy struct here"
    // Loop is for debug purposes

    for (int i = 0; i < numWords; i++) {
      printf("%d word is characaters %d - %d\n", i+1, startIdxs[i], endIdxs[i]);
    }
    


    // Free memory
    free(startIdxs);
    free(endIdxs);
  }
}


int main() {
  FILE *fp = fopen("test.txt", "r");
  eval(NULL, fp);
}
