#include "VectorStack.h"

// Увеличивает вместимость массива
void Vector::reserve(int newCap) {
    if (newCap <= capacity) return;  // Новая вместимость должна быть не больше текущей
    int* newMass = new int[newCap];  // Создание нового массива с новой вместимостью
    for (int i = 0; i < length; ++i) newMass[i] = data[i];  // Копирует элементы из старого массива в новый
    delete[] data;      // Освобождает память старого массива
    data = newMass;     // Обновляет указатель на новый массив
    capacity = newCap;  // Обновляет значение вместимости
}

// Конструктор копирования
Vector::Vector(const Vector& old) : data(nullptr), length(old.length), capacity(old.capacity) {
    if (capacity) {
        data = new int[capacity];
        for (int i = 0; i < length; ++i) data[i] = old.data[i]; // Копирует элементы из заданого вектора
    }
}

// Оператор присваивания
Vector& Vector::operator=(const Vector& old) {
    if (this == &old) return *this;  // Проверяет на самоприсваивание
    delete[] data;                   // Освобождает текущие данные
    length = old.length;
    capacity = old.capacity;
    data = capacity ? new int[capacity] : nullptr;          // Выделяет новую память
    for (int i = 0; i < length; ++i) data[i] = old.data[i]; // Копирует элементы
    return *this;
}

// Деструктор
Vector::~Vector() { delete[] data; }

// Методы доступа:
int Vector::size() const { return length; }         // Возвращает текущий размер
bool Vector::empty() const { return length == 0; }  // Проверяет на пустоту

// Операторы доступа к элементам:
int& Vector::operator[](int i) { return data[i]; }              // Для изменения
const int& Vector::operator[](int i) const { return data[i]; }  // Для чтения

// Добавление элемента в конец
void Vector::push_back(int add) {
    if (length == capacity) reserve(capacity ? capacity * 2 : 1);  // Увеличивает вместимость при необходимости
    data[length++] = add;  // Добавляет элемент и увеличивает длину
}

// Удаление последнего элемента
void Vector::pop_back() { if (length) --length; }
