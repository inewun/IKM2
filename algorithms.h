﻿#include "VectorStack.h"
#include <iostream>
#include <fstream>

using namespace std;

// Объявление внешней переменной для логирования
extern std::ofstream logFile;

// Флаг для включения/выключения подробного логирования
extern bool enableDetailedLogging;

/* Функция выводит информацию о перемещении элемента между стеками
 * @param индекс стека-источника
 * @param индекс стека-приемника
 * @param значение переносимого элемента
 */
void printAction(int from, int to, int value);

/* Функция выводит текущее состояние всех стеков
 * @param вектор стеков для вывода
 * @param дополнительное сообщение для вывода перед состоянием стеков
 */
void printAll(const VectorStack& stacks, const string& prefix = "");

// Как и прошлое, просто пришлось дублировать из-за логирования, чтобы можно было выводить результат
void printAllResult(const VectorStack& stacks);

/* Функция чтения начального состояния стеков из входного потока
 * @return вектор стеков с начальным состоянием
 */
VectorStack readStacks();

/* Функция для слияния и сортировки двух стеков
 * @param вектор стеков
 * @param индекс первого стека-источника (сортировочный стек)
 * @param индекс второго стека-источника (буферный стек)
 * @param индекс стека-приемника (для результата)
 */
void mergeAndSort(VectorStack& stacks, int fromOne, int fromTwo, int to);

/* Функция распределяет цифры из стека с индексом i в соответствующие стеки
 * согласно их значениям (цифра n должна оказаться в стеке stacks[n-1])
 * @param индекс исходного стека, из которого распределяем цифры
 * @param вектор стеков
 */
void distribute(int i, VectorStack& stacks);