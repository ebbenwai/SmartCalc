#include <check.h>

#include "calc.h"

START_TEST(valid_1) {
  char *test_str = "3+2*(4-1)";
  ck_assert_int_eq(check_error(test_str), 0);
}
END_TEST

START_TEST(valid_2) {
  char *test_str = "3+*2";
  ck_assert_int_eq(check_error(test_str), 1);
}
END_TEST

START_TEST(valid_3) {
  char *test_str = "3+(2*4-1";
  ck_assert_int_eq(check_error(test_str), 1);
}
END_TEST

START_TEST(valid_4) {
  char *test_str = "3s(2+4)";
  ck_assert_int_eq(check_error(test_str), 1);
}
END_TEST

START_TEST(valid_5) {
  char *test_str = "asdbnf";
  ck_assert_int_eq(check_error(test_str), 1);
}
END_TEST

START_TEST(valid_6) {
  char *test_str = "sin(.2.2.2)";
  ck_assert_int_eq(check_error(test_str), 1);
}
END_TEST

START_TEST(valid_7) {
  char *test_str = "acos((4343)))";
  ck_assert_int_eq(check_error(test_str), 1);
}
END_TEST

START_TEST(valid_8) {
  char *test_str = "3.1415-21/42+12*tan(5)";
  ck_assert_int_eq(check_error(test_str), 0);
}
END_TEST

START_TEST(valid_9) {
  char *test_str = "cso(3)+93*-)";
  ck_assert_int_eq(check_error(test_str), 1);
}
END_TEST

START_TEST(valid_10) {
  char *test_str = "3..2+4";
  ck_assert_int_eq(check_error(test_str), 1);
}
END_TEST

START_TEST(valid_11) {
  char *test_str = "sin(12^3+cos(3))^12/tan(43*sin(4))";
  ck_assert_int_eq(check_error(test_str), 0);
}
END_TEST

START_TEST(valid_12) {
  char *test_str = "cos(33)+sin()";
  ck_assert_int_eq(check_error(test_str), 1);
}
END_TEST

START_TEST(calc_1) {
  double result = calculate("10+20", 0);
  ck_assert_double_eq(result, 30);
}
END_TEST

START_TEST(calc_2) {
  double result = calculate("sin(cos(sqrt(12345.54321)))", 0);
  ck_assert_double_eq_tol(result, -0.393229, 0.000001);
}
END_TEST

START_TEST(calc_3) {
  double result = calculate("74/4*43+(32^43/4)+cos(12)+(43*43^0.12)", 0);
  ck_assert_ldouble_eq(
      result,
      13164036458569648337239753460458804039861886925068638906788872192.000000);
}
END_TEST

START_TEST(calc_4) {
  long double result = calculate("sqrt(2^2^7)*cos(12)", 0);
  ck_assert_double_eq(result, sqrt(pow(pow(2, 2), 7)) * cos(12));
}
END_TEST

START_TEST(calc_5) {
  double result = calculate("cos(sin(tan(0.5)))", 0);
  ck_assert_double_eq(result, cos(sin(tan(0.5))));
}
END_TEST

START_TEST(calc_6) {
  double result = calculate("-8/(2+3)*(7-2)+6", 0);
  ck_assert_double_eq(result, -2);
}
END_TEST

START_TEST(calc_7) {
  double result = calculate("tan((5.23+1.25)*(0.25+0.001))", 0);
  ck_assert_double_eq(result, tan((5.23 + 1.25) * (0.25 + 0.001)));
}
END_TEST

START_TEST(calc_8) {
  double result = calculate("ln(1357-245)", 0);
  ck_assert_double_eq(result, log(1357 - 245));
}
END_TEST

START_TEST(calc_9) {
  double result = calculate("log(143*524)", 0);
  ck_assert_double_eq(result, log10(143 * 524));
}
END_TEST

START_TEST(calc_10) {
  double result = calculate("sin(cos(sin(tan(-0.005))))", 0);
  ck_assert_float_eq(sin(cos(sin(tan(-0.005)))), result);
}
END_TEST

START_TEST(calc_11) {
  double result = calculate("asin(0.1*cos(2*atan(0.9)))^2", 0);
  ck_assert_float_eq(pow(asin(0.1 * cos(2 * atan(0.9))), 2), result);
}
END_TEST

START_TEST(calc_12) {
  double result = calculate("acos(0.1)+(asin(sin(1)))*3/23", 0);
  ck_assert_float_eq(acos(0.1) + (asin(sin(1))) * 3 / 23, result);
}
END_TEST

START_TEST(calc_13) {
  double result = calculate("1.25mod3.45", 0);
  ck_assert_float_eq(fmod(1.25, 3.45), result);
}
END_TEST

START_TEST(calc_14) {
  double result = calculate("((10.5-2.2)*(4.8+2.3)-1.7/3)^9", 0);
  ck_assert_float_eq(pow(((10.5 - 2.2) * (4.8 + 2.3) - 1.7 / 3), 9), result);
}
END_TEST

START_TEST(calc_15) {
  double result =
      calculate("sin((log(32+1)*7/11*432*(sin(2)*12-45+4)/2)^2)", 0);
  ck_assert_float_eq(
      sin(pow(log10(32 + 1) * 7 / 11 * 432 * (sin(2) * 12 - 45 + 4) / 2, 2)),
      result);
}
END_TEST

START_TEST(calc_16) {
  double result = calculate("12mod3*3-sin(2)", 0);
  ck_assert_float_eq(fmod(12, 3) * 3 - sin(2), result);
}
END_TEST

int main(void) {
  Suite *s;
  TCase *tc_core;
  SRunner *sr;

  s = suite_create("Core");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, valid_1);
  tcase_add_test(tc_core, valid_2);
  tcase_add_test(tc_core, valid_3);
  tcase_add_test(tc_core, valid_4);
  tcase_add_test(tc_core, valid_5);
  tcase_add_test(tc_core, valid_6);
  tcase_add_test(tc_core, valid_7);
  tcase_add_test(tc_core, valid_8);
  tcase_add_test(tc_core, valid_9);
  tcase_add_test(tc_core, valid_10);
  tcase_add_test(tc_core, valid_11);
  tcase_add_test(tc_core, valid_12);

  tcase_add_test(tc_core, calc_1);
  tcase_add_test(tc_core, calc_2);
  tcase_add_test(tc_core, calc_3);
  tcase_add_test(tc_core, calc_4);
  tcase_add_test(tc_core, calc_5);
  tcase_add_test(tc_core, calc_6);
  tcase_add_test(tc_core, calc_7);
  tcase_add_test(tc_core, calc_8);
  tcase_add_test(tc_core, calc_9);
  tcase_add_test(tc_core, calc_10);
  tcase_add_test(tc_core, calc_11);
  tcase_add_test(tc_core, calc_12);
  tcase_add_test(tc_core, calc_13);
  tcase_add_test(tc_core, calc_14);
  tcase_add_test(tc_core, calc_15);
  tcase_add_test(tc_core, calc_16);

  suite_add_tcase(s, tc_core);

  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
