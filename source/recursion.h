#ifndef RECURSION_H
#define RECURSION_H
int   infixEval ();  //evaluate infix expression
void  infixToPostfix (void); //convert infix expression to postfix
void  binaryMatrix (int** bm, int n);  //build a matrix 2^n * n with all binary numbers with n digits
void  testBinaryMatrix (int n);
int   getRulerMark (int i);
#endif
