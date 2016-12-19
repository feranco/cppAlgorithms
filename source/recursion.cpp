#include "recursion.h"
#include <iostream>
#include <string>

const char* expr = "(5 * (((9+8) * (4*6)) + 7))"; //infix string
int idx = 0; //currently evaluated character

int calc (int l, char op, int r) {
  
  switch (op) {
  case '+':
    return l + r;
    break;

  case '-':
    return l - r;
    break;

 case '*':
    return l * r;
    break;

 case '/':
    return l / r;
    break;

  default:
    return 0;
  }
}

int infixEval () {
  int token;
  char op = 0;
  int lhs, res;

  while (1) {

    token = expr[idx++];

    if (token == ' ') continue; //skip spaces

    if (token >= '0' && token <= '9') {
      int x = 0;
      --idx; //necessary to manage multiple digit numbers
      //convert string numbers to int 
      while (expr[idx] >= '0' && expr[idx] <= '9') {
	x = 10 * x + expr[idx++] - '0';
      }

      if (op == 0) {
	lhs = x;
      }
      else {
	res = calc (lhs, op, x);
      }
    }
    
    if (token == '(') {
      int x = infixEval();
      if (expr[idx] == 0) return x; //return the final value
      if (op == 0) {
	lhs = x;
      }
      else {
	res = calc(lhs, op, x);
      }
    }

    if (token == '+' || token == '-' || token == '*' || token == '/') {
      op = token;
    }

    if (token == ')') {
      return res;
    } 
  }
  return res;
}

void infixToPostfix (void) {
  char op; //hold the current level operator
  char token;

  while (expr[idx] != 0) {
    
    token = expr[idx++];

    if (token  == ' ') continue; //skip spaces

    if (token >= '0' && token <= '9') {
      std::cout << token << " ";
    }
    else if (token == '+' || token == '*') {
      op = token;
    }
    else if (token == '(') {
      infixToPostfix();
    }
    else if (token == ')') {
      std::cout << op << " ";
      return;
    } 
  }
}

std::string postfix = "";

void postfixToInfix (void) {
    /*
  static int count = 0;
  int level = count;
  char token;
  int x;
  
  while (pn[idx] != 0) {

    token = pn[idx++];
    
    
  }
     */
}
