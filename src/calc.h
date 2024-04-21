#ifndef CALC_H
#define CALC_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255

typedef struct stack {
  double number;
  char sign;
  int priority;
  char function[10];
  struct stack* next;
} Stack;

int check_error(char* str);
int is_operator(char c);
int is_operand(char c);
int has_error(char current_char, char next_char, char prev_char);
int has_bracket_error(int open_bracket_counter, int close_bracket_counter,
                      char current_char, char next_char, char prev_char);
int has_function_error(char current_char, char next_char);
int check_error(char* str);

Stack* push(Stack* top, double number, char sign, int priority, char* function);
Stack* pop(Stack* top);
int priority(char symbol);
void parseNumber(Stack** top, const char* expression, int* index);
void parseVariableX(Stack** top, double x);
void parseTrigFunction(Stack** top, const char* expression, int* index);
void parseOperator(Stack** top, char op);
void parseExpression(Stack** top, const char* expression, double x);
void convertToReversePolishNotation(Stack** top);
double calculateTrigonometric(double operand, char* function);
double evaluateExpression(Stack* top);
double calculate(const char* input_expression, double x);
Stack* reversed(Stack* top);

#endif