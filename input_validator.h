#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include "VectorStack.h"
#include <iostream>

/* Функция проверяет корректность входных данных
 * @param n - количество стопок
 * @return true если данные корректны, false в противном случае
 */
bool validateInput(int n);

/* Функция проверяет корректность данных для одной стопки
 * @param k - количество контейнеров в стопке
 * @param n - общее количество стопок
 * @return true если данные корректны, false в противном случае
 */
bool validateStackInput(int k, int n);

/* Функция очищает поток ввода после ошибки
 */
void clearInputBuffer();

/* Функция проверяет, является ли ввод числом
 * @return true если ввод корректен, false в противном случае
 */
bool isNumberInput();

#endif // INPUT_VALIDATOR_H 