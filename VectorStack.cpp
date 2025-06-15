#include "VectorStack.h"

// Метод увеличения вместимости
void VectorStack::reserve(int newCapacity) {
    if (newCapacity <= capacity) return;      // Новая вместимость должна быть не больше текущей
    Stack* newMass = new Stack[newCapacity];  // Создание нового массива с новой вместимостью
    for (int i = 0; i < lenght; ++i) newMass[i] = data[i]; // Копирует элементы из старого массива в новый
    delete[] data;           // Освобождает память старого массива
    data = newMass;          // Обновляет указатель на новый массив
    capacity = newCapacity;  // Обновляет значение вместимости
}

// Конструктор копирования
VectorStack::VectorStack(const VectorStack& old) : data(nullptr), lenght(old.lenght), capacity(old.capacity) {
    if (capacity) {
        data = new Stack[capacity];
        for (int i = 0; i < lenght; ++i) data[i] = old.data[i]; // Копирует элементы
    }
}

// Оператор присваивания
VectorStack& VectorStack::operator=(const VectorStack& old) {
    if (this == &old) return *this; // Проверяет на самоприсваивание
    delete[] data;                  // Освобождает текущие данные
    lenght = old.lenght;
    capacity = old.capacity;
    data = capacity ? new Stack[capacity] : nullptr;         // Выделяет новую память
    for (int i = 0; i < lenght; ++i) data[i] = old.data[i];  // Копирует элементы
    return *this;
}

// Деструктор
VectorStack::~VectorStack() { delete[] data; }

// Методы доступа:
int VectorStack::size() const { return lenght; }         // Возвращает текущий размер
bool VectorStack::empty() const { return lenght == 0; }  // Проверяет на пустоту


// Операторы доступа к стекам:
Stack& VectorStack::operator[](int i) { return data[i]; }              // Для изменения
const Stack& VectorStack::operator[](int i) const { return data[i]; }  // Для чтения

// Добавление стека в конец
void VectorStack::push_back(const Stack& add) {
    if (lenght == capacity) reserve(capacity ? capacity * 2 : 1);  // Увеличивает вместимость при необходимости
    data[lenght++] = add;  // Добавляет элемент и увеличивает длину
}

// Удаление последнего стека
void VectorStack::pop_back() { if (lenght) --lenght; }
