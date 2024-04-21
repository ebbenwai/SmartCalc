#include "calc.h"

Stack* push(Stack* top, double number, char sign, int priority,
            char* function) {
  Stack* ptr = (Stack*)malloc(sizeof(Stack));
  ptr->number = number;
  ptr->sign = sign;
  ptr->priority = priority;
  strcpy(ptr->function, function);
  ptr->next = top;
  return ptr;
}

Stack* pop(Stack* top) {
  if (top == NULL) return top;

  Stack* ptr_next = top->next;
  free(top);

  return ptr_next;
}

int priority(char symbol) {
  int flag = 0;
  switch (symbol) {
    case '+':
    case '-':
      flag = 1;
      break;
    case '*':
    case '/':
      flag = 2;
      break;
    case '^':
      flag = 3;
      break;
    case 'c':
    case 's':
    case 't':
    case 'a':
    case 'l':
    case 'm':
      flag = 4;
      break;
    case ')':
      flag = 5;
      break;
    case '(':
      flag = 6;
      break;
  }
  return flag;
}

void parseNumber(Stack** top, const char* expression, int* index) {
  char numStr[MAX_SIZE];
  int i = 0;

  while (isdigit(expression[*index]) || expression[*index] == '.') {
    numStr[i++] = expression[*index];
    (*index)++;
  }
  numStr[i] = '\0';

  double number = atof(numStr);
  *top = push(*top, number, ' ', 0, "\0");
}

void parseVariableX(Stack** top, double x) {
  *top = push(*top, x, ' ', 0, "\0");
}

void parseTrigFunction(Stack** top, const char* expression, int* index) {
  char trigFunc[10] = {0};
  int i = 0;

  while (isalpha(expression[*index])) {
    trigFunc[i++] = expression[*index];
    (*index)++;
  }
  trigFunc[i] = '\0';

  if (strstr(trigFunc, "sin") || strstr(trigFunc, "cos") ||
      strstr(trigFunc, "tan") || strstr(trigFunc, "asin") ||
      strstr(trigFunc, "acos") || strstr(trigFunc, "atan") ||
      strstr(trigFunc, "log") || strstr(trigFunc, "ln") ||
      strstr(trigFunc, "sqrt") || strstr(trigFunc, "mod")) {
    *top = push(*top, 0.0, ' ', 4, trigFunc);
  }
}

void parseOperator(Stack** top, char op) {
  int priorityi = priority(op);
  *top = push(*top, 0.0, op, priorityi, "\0");
}

void parseExpression(Stack** top, const char* expression, double x) {
  int index = 0;
  int minus_flag = 0;

  while (expression[index] != '\0') {
    if (expression[index] == 'x') {
      parseVariableX(top, x);
      index++;
    } else if (expression[index] == '-' &&
               (index == 0 || (!isdigit(expression[index - 1]) &&
                               expression[index - 1] != ')'))) {
      minus_flag = 1;
      index++;
    } else if (isdigit(expression[index])) {
      parseNumber(top, expression, &index);
      if (minus_flag) {
        (*top)->number *= -1;
        minus_flag = 0;
      }
    } else if (isalpha(expression[index])) {
      parseTrigFunction(top, expression, &index);
    } else if (expression[index] == '+' || expression[index] == '-' ||
               expression[index] == '*' || expression[index] == '/' ||
               expression[index] == '^' || expression[index] == '(' ||
               expression[index] == ')') {
      parseOperator(top, expression[index]);
      index++;
    }
  }

  *top = reversed(*top);
}

void convertToReversePolishNotation(Stack** top) {
  Stack* result = NULL;
  Stack* operatorStack = NULL;
  Stack* current = *top;

  while (current != NULL) {
    if (current->priority == 0) {
      result = push(result, current->number, ' ', 0, "\0");
    } else if (current->function[0] != '\0') {
      operatorStack = push(operatorStack, 0, ' ', 4, current->function);
    } else if (current->sign == ')') {
      while (operatorStack != NULL && operatorStack->sign != '(') {
        result = push(result, 0.0, operatorStack->sign, operatorStack->priority,
                      operatorStack->function);
        operatorStack = pop(operatorStack);
      }

      if (operatorStack != NULL && operatorStack->sign == '(') {
        operatorStack = pop(operatorStack);
      }
    } else {
      while (operatorStack != NULL &&
             operatorStack->priority >= current->priority &&
             operatorStack->sign != '(') {
        result = push(result, 0.0, operatorStack->sign, operatorStack->priority,
                      operatorStack->function);
        operatorStack = pop(operatorStack);
      }

      operatorStack =
          push(operatorStack, 0.0, current->sign, current->priority, "\0");
    }

    current = current->next;
  }

  while (operatorStack != NULL) {
    result = push(result, 0.0, operatorStack->sign, operatorStack->priority,
                  operatorStack->function);
    operatorStack = pop(operatorStack);
  }

  while (*top != NULL) *top = pop(*top);
  *top = reversed(result);
}

double calculateTrigonometric(double operand, char* function) {
  double result_value = 0.0;

  if (strcmp(function, "sin") == 0) {
    result_value = sin(operand);
  } else if (strcmp(function, "cos") == 0) {
    result_value = cos(operand);
  } else if (strcmp(function, "tan") == 0) {
    result_value = tan(operand);
  } else if (strcmp(function, "asin") == 0) {
    result_value = asin(operand);
  } else if (strcmp(function, "acos") == 0) {
    result_value = acos(operand);
  } else if (strcmp(function, "atan") == 0) {
    result_value = atan(operand);
  } else if (strcmp(function, "log") == 0) {
    result_value = log10(operand);
  } else if (strcmp(function, "ln") == 0) {
    result_value = log(operand);
  } else if (strcmp(function, "sqrt") == 0) {
    result_value = sqrt(operand);
  }

  return result_value;
}

double evaluateExpression(Stack* top) {
  Stack* result = NULL;
  Stack* current = top;

  while (current != NULL) {
    if (current->priority == 0) {
      result = push(result, current->number, ' ', 0, current->function);
    } else if (strstr(current->function, "mod")) {
      double operand2 = result->number;
      result = pop(result);
      double operand1 = result->number;
      result = pop(result);
      double result_value = fmod(operand1, operand2);
      result = push(result, result_value, ' ', 0, "\0");
    } else if (current->priority == 4) {
      double operand = result->number;
      result = pop(result);
      double result_value = calculateTrigonometric(operand, current->function);
      result = push(result, result_value, ' ', 0, "\0");
    } else {
      double operand2 = result->number;
      result = pop(result);
      double operand1 = result->number;
      result = pop(result);
      double result_value = 0.0;
      switch (current->sign) {
        case '+':
          result_value = operand1 + operand2;
          break;
        case '-':
          result_value = operand1 - operand2;
          break;
        case '*':
          result_value = operand1 * operand2;
          break;
        case '/':
          if (operand2 != 0) {
            result_value = operand1 / operand2;
          } else {
            return 0;
          }
          break;
        case '^':
          result_value = pow(operand1, operand2);
          break;
        default:
          return 0;
      }
      result = push(result, result_value, ' ', 0, "\0");
    }
    current = current->next;
  }
  double final_result = result->number;
  while (result != NULL) {
    result = pop(result);
  }
  return final_result;
}

Stack* reversed(Stack* top) {
  Stack* result = NULL;

  while (top != NULL) {
    result = push(result, top->number, top->sign, top->priority, top->function);
    top = pop(top);
  }

  return result;
}

double calculate(const char* input_expression, double x) {
  Stack* expression = NULL;

  parseExpression(&expression, input_expression, x);

  convertToReversePolishNotation(&expression);

  long double result = evaluateExpression(expression);

  while (expression != NULL) {
    expression = pop(expression);
  }

  return result;
}
