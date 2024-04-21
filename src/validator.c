#include "calc.h"

int is_operator(char c) {
  int error_detected = 0;
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'd') {
    error_detected = 1;
  }
  return error_detected;
}

int is_operand(char c) {
  int error_detected = 0;
  if (c >= '0' && c <= '9') {
    error_detected = 1;
  }
  return error_detected;
}

int has_error(char current_char, char next_char, char prev_char) {
  int error_detected = 0;
  if (is_operator(current_char) &&
      (is_operator(next_char) || next_char == '\0')) {
    error_detected = 1;
  } else if ((current_char == '*' || current_char == '/' ||
              current_char == '^' || current_char == 'm') &&
             !prev_char) {
    error_detected = 1;
  } else if ((current_char == '.') && ((next_char < '0' || next_char > '9') ||
                                       (prev_char < '0' || prev_char > '9'))) {
    error_detected = 1;
  }
  return error_detected;
}

int has_bracket_error(int open_bracket_counter, int close_bracket_counter,
                      char current_char, char next_char, char prev_char) {
  int error_detected = 0;
  if ((current_char == '(' && (prev_char >= '0' && prev_char <= '9')) ||
      (current_char == '(' && next_char == ')') ||
      (current_char == '(' && (next_char == 'm' || next_char == '/' ||
                               next_char == '*' || next_char == '^'))) {
    error_detected = 1;
  } else if ((current_char == ')' && (next_char >= '0' && next_char <= '9')) ||
             (current_char == ')' && next_char == '(') ||
             (current_char == ')' &&
              (prev_char == 'd' || prev_char == '+' || prev_char == '-' ||
               prev_char == '*' || prev_char == '/' || prev_char == '^'))) {
    error_detected = 1;
  }
  if (current_char == '(') {
    open_bracket_counter++;
  } else if (current_char == ')') {
    if (open_bracket_counter > close_bracket_counter) {
      close_bracket_counter++;
    } else {
      error_detected = 1;
    }
  }
  return error_detected;
}

int has_function_error(char current_char, char next_char) {
  int error_detected = 0;
  if (is_operand(current_char) &&
      (next_char == 's' || next_char == 'c' || next_char == 't' ||
       next_char == 'a' || next_char == 'l')) {
    error_detected = 1;
  } else if (isalpha(current_char) && isdigit(next_char)) {
    error_detected = 1;
  }
  return error_detected;
}

int check_error(char *str) {
  int open_bracket_counter = 0, close_bracket_counter = 0;
  int error_detected = 0;

  for (int i = 0; i < (int)strlen(str); i++) {
    if (has_error(str[i], str[i + 1], str[i - 1]) ||
        has_bracket_error(open_bracket_counter, close_bracket_counter, str[i],
                          str[i + 1], str[i - 1]) ||
        has_function_error(str[i], str[i + 1]) ||
        (!is_operand(str[i]) && str[i] != ')' && str[i] != 'x' &&
         str[i + 1] == '\0')) {
      error_detected = 1;
      break;
    }

    if (str[i] == '(') {
      open_bracket_counter++;
    } else if (str[i] == ')') {
      if (open_bracket_counter > close_bracket_counter) {
        close_bracket_counter++;
      } else {
        error_detected = 1;
        break;
      }
    }
  }

  if (open_bracket_counter != close_bracket_counter) {
    error_detected = 1;
  }

  return error_detected;
}
