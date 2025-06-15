#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include "VectorStack.h"
#include <iostream>

/* ������� ��������� ������������ ������� ������
 * @param n - ���������� ������
 * @return true ���� ������ ���������, false � ��������� ������
 */
bool validateInput(int n);

/* ������� ��������� ������������ ������ ��� ����� ������
 * @param k - ���������� ����������� � ������
 * @param n - ����� ���������� ������
 * @return true ���� ������ ���������, false � ��������� ������
 */
bool validateStackInput(int k, int n);

/* ������� ������� ����� ����� ����� ������
 */
void clearInputBuffer();

/* ������� ���������, �������� �� ���� ������
 * @return true ���� ���� ���������, false � ��������� ������
 */
bool isNumberInput();

#endif // INPUT_VALIDATOR_H 