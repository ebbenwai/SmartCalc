# SmartCalc Documentation

## Copyright Information
This calculator is protected by copyright. All rights reserved.
© 2024 by ebbenwai.

## Installation
Для использования этого калькулятора пользователю необходимо установить следующие утилиты:
- gcc
- make
- qmake

## Development Details

### Backend
"Backend" часть была реализована на языке программирования C, стандарта C11, с использованием компилятора gcc. Основные функции включает:
- Вычисление математических выражений с использованием обратной польской нотации, реализованный через алгоритм Дейкстры. Данный способ позволяет обрабатывать сложные выражения, включая тригонометрические функции, математические операции и унарные знаки.
- Сборка проекта с использованием Makefile, расположенного в папке src. Для установки приложения необходимо выполнить команду make install, для удаления - make uninstall.

### Frontend
"Frontend" часть была реализована на языке программирования C++ и с использованием библиотеки QT. Основные функции включают:
- Калькулятор с возможностью выполнения различных операций, включая арифметические действия и тригонометрические функции.
- Графический модуль для построения графиков функций с использованием библиотеки QCustomPlot. Это позволяет визуализировать математические зависимости и настраивать параметры графиков.


## Installation Command
Чтобы установить калькулятор, выполните следующую команду:
make install
## Arithmetic Operations
Калькулятор поддерживает следующие арифметические операции:

| Operator name | Infix notation <br /> (Classic) | Prefix notation <br /> (Polish notation) | Postfix notation <br /> (Reverse Polish notation) |
| --------- | ------ | ------ | ------ |
| Brackets | (a + b) | (+ a b) | a b + |
| Addition | a + b | + a b | a b + |
| Subtraction | a - b | - a b | a b - |
| Multiplication | a * b | * a b | a b * |
| Division | a / b | / a b | a b \ |
| Power | a ^ b | ^ a b | a b ^ |
| Modulus | a mod b | mod a b | a b mod |
| Unary plus | +a | +a | a+ |
| Unary minus | -a | -a | a- |


## Mathematical Functions
Калькулятор включает в себя различные математические функции, в том числе:
  
| Function description | Function |
| -------------------- | -------- |
| Computes cosine    | cos(x)  |
| Computes sine      | sin(x)  |
| Computes tangent   | tan(x)  |
| Computes arc cosine | acos(x) |
| Computes arc sine  | asin(x) |
| Computes arc tangent| atan(x) |
| Computes square root| sqrt(x) |
| Computes natural logarithm| ln(x)|
| Computes common logarithm| log(x)|


## Function Plotting
Калькулятор предоставляет возможность построения графиков функций. Вы можете легко визуализировать математические уравнения.
