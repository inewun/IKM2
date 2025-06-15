#include "VectorStack.h"

// Проверяет на пустоту
bool Stack::empty() const { return inVector.empty(); }

// Возращает размер стека
int Stack::size() const { return inVector.size(); }

// Добавленияет элемент в стек
void Stack::push(int x) { inVector.push_back(x); }

// Удаляет элемент из стека
void Stack::pop() { inVector.pop_back(); }

// Возращает верхний элемент (для изменения)
int& Stack::top() { return inVector[inVector.size() - 1]; }

// Возращает верхний элемент (для чтения)
const int& Stack::top() const { return inVector[inVector.size() - 1]; }
