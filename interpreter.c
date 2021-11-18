#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

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
