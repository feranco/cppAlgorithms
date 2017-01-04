
#ifndef RECURSION_H
#define RECURSION_H
int   infixEval ();  //evaluate infix expression
void  infixToPostfix (void); //convert infix expression to postfix
void  binaryMatrix (int** bm, int n);  
void  testBinaryMatrix (int n);
int getRulerMark (int i);
int Fibonacci (int i); //Compute Fibonacci in costant space
int recurrenceCF (int n);
int recurrenceCFTD (int n);
int knapBU (int n);
void testRecurrenceCF (void);
int maxK (int a[], int k, int l, int r);
#endif
