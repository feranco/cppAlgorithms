
const char* expr = "(5 * (((9+8) * (4+6)) + 7))"; //infix string
int idx = 0; //currently evaluated character

int baseEval (int l, char op, int r) {
  
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
  }
}

int infixEval () {
  int token;
  int x = 0;
  char op = 0;
  int lhs, res;

  while (expr[idx]!=0) {

    token = expr[idx++];

    if (token == ' ') continue; //skip spaces

    if (token >= '0' && token <= '9') {

      while (expr[i] >= '0' && expr[i] <= '9') { //convert string numbers to int 
	x = 10 * x + expr[i++] - '0';
      }

      if (op == 0) {
	lhs = x;
      }
      else {
	res = baseEval (lhs, op, x);
      }
    }
    
    if (token == '(') {
      infixEval();
    }

    if (token == '+' || token == '-' || token == '*' || token == '/') {
      op = expr[i++];
    }

     if (expr[i++] == ')') {
       return res;
    } 
    
  }
}
