#include "VectorStack.h"

// ��������� �� �������
bool Stack::empty() const { return inVector.empty(); }

// ��������� ������ �����
int Stack::size() const { return inVector.size(); }

// ������������ ������� � ����
void Stack::push(int x) { inVector.push_back(x); }

// ������� ������� �� �����
void Stack::pop() { inVector.pop_back(); }

// ��������� ������� ������� (��� ���������)
int& Stack::top() { return inVector[inVector.size() - 1]; }

// ��������� ������� ������� (��� ������)
const int& Stack::top() const { return inVector[inVector.size() - 1]; }
