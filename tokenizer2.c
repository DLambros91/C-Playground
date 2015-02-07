/*
 * tokenizer.c
 * Name : Demetrios Lambropoulos
 * Date : Thursday, January 22, 2015
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>


typedef enum { false, true } bool;
typedef enum {ALPHANUM, ALPHA, OCTAL, HEXIDECIMAL, PLUS} state_t; // current state that the tokenizer is in - Jan 31 22:35

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
	char *str; // char pointer to point to pointer at argv[num] - Jan 31 22:35
	int curChar; // current string index - Jan 31 22:35
	bool isFinished; // is argv[num] fully traversed - Jan 31 22:35
	int manyTokens; // amount of tokens contained in argv[num] - Jan 31 22:35
	state_t state; // current state
	char **tokens;
	char **tokenDesc;
	int strSize;
};
typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char *ts ) {
 if (ts != NULL) {
	//struct TokenizerT_ *tk = malloc(sizeof(struct TokenizerT_));
	struct TokenizerT_ *tk = calloc(1,sizeof(TokenizerT));
	assert(tk != NULL);

	tk->manyTokens = 0;
	tk->curChar = 0;
	tk->strSize = 1;


	while ((char)ts[tk->curChar] != '\0')
	{
		tk->strSize++;
		tk->curChar++;
	}
	tk->str = calloc(tk->strSize, sizeof(char));
	int i;
	for(i = 0; i < tk->strSize; i++)
	{
		tk->str[i] = ts[i];
	}
	tk->curChar = 0;
	tk->tokens = calloc(tk->strSize, sizeof(char));
	tk->tokenDesc = calloc(tk->strSize, sizeof(char));
	return tk;
 }
 else {
	return NULL;
      }
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk )
{
	int i;
	assert(tk != NULL);
	printf("Made it past first assert\n");
//	if(tk->str!=NULL)
//	{
//		printf("tk->str isn't NULL\n");
//		printf("tk->str = %s", tk->str);
//		free(tk->str);
//		printf("Freed tk->str");
//	}
	printf("Made passed first free\n");
/*
	while(tokens[i]!=NULL)
	{
		free(tk->tokens[i]);
		i++;
	}
*/
	//free(tk->tokens);
	for(i = 0; tk->manyTokens-- > 0; i++)
	{
		printf("in for loop\n");

		if(tk->tokens[i]!=NULL && tk->tokenDesc[i]!=NULL)
		{
			free(tk->tokens[i]);
			free(tk->tokenDesc[i]);
		}
	}
	printf("Made it out of for loop\n");

	//free(tk->tokens);
	free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
  printf("made pass if statement\n");
  if(tk->str == '\0')
  {
	return '\0';
  }
  printf("true\n");
 // char *arr = malloc(sizeof(char) * tk->strSize);
  char *arr = calloc(tk->strSize, sizeof(char));
  int i = 0;
  while ((char)tk->str[tk->curChar] != '\0')
  {
	printf("%d\n", tk->curChar);
//	printf("in while loop\n");
        printf("%c\n", (char)tk->str[tk->curChar]);
	if((char)tk->str[tk->curChar] == ' ')
	{
		printf("breaking\n");
		tk->curChar++;
		break;
	}
	arr[i] = tk->str[tk->curChar];
	i++;
	tk->curChar++;
  }

	printf("left while loop\n%c\n", (char)tk->str[tk->curChar]);

	printf("arr = %s\n", arr);

  //tk->curChar++;
  return arr;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
  struct TokenizerT_ *tk = TKCreate(argv[1]);
  printf("made it to while loop\n");
  //printf("%s\n%d\n", tk->str, tk->manyTokens);
  while(tk->str[tk->curChar] != '\0')
  {	if (tk->curChar > tk->strSize-1)
	{
		printf("%c\n", (char)tk->str[tk->curChar]);
		break;
	}
        printf("made it in the first loop\n");
	// tk->tokens[tk->manyTokens] = malloc(sizeof(char)*tk->strSize+1);
	tk->tokens[tk->manyTokens] = calloc(tk->strSize+1 , sizeof(char));
	tk->tokens[tk->manyTokens] = TKGetNextToken(tk);
	printf("returned success %s\n", tk->tokens[tk->manyTokens]);
	tk->manyTokens++;
	printf("manytokens = %d\n", tk->manyTokens);
  }
  printf("made it to second while loop\n");
  printf("strSize = %d\n", tk->strSize);
  int num = tk->manyTokens;
  while(num > 0)
  {
	printf("manytokens = %d\n", num);
	//printf("%s\n", tk->tokens[--tk->manyTokens]);
	printf("%s\n", tk->tokens[--num]);
  }
  TKDestroy(tk);
  return 0;
}
