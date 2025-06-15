#ifndef VECTORSTACK_H
#define VECTORSTACK_H

// Класс Vector
class Vector {
    int* data;          // Указатель на массив элементов
    int  length;        // Текущее количество элементов в массиве
    int  capacity;      // Общая вместимость массива

    // Увеличивает вместимость массива
    void reserve(int newCap);

public:
    // Конструктор по умолчанию - создает пустой вектор
    Vector() : data(nullptr), length(0), capacity(0) {}

    // Конструктор с параметром - создает вектор заданного размера
    Vector(int value) : data(value ? new int[value] : nullptr), length(value), capacity(value) {}

    // Конструктор копирования
    Vector(const Vector& old);

    // Оператор присваивания
    Vector& operator=(const Vector& old);

    // Деструктор - освобождает память
    ~Vector();

    // Методы доступа:
    int  size()  const; // Возвращает текущий размер
    bool empty() const; // Проверяет на пустоту

    // Операторы доступа к элементам:
    int& operator[](int i);             // Для изменения
    const int& operator[](int i) const; // Для чтения

    // Добавление элемента в конец
    void push_back(int add);

    // Удаление последнего элемента
    void pop_back();
};


// Класс Stack на основе класса Vector
class Stack {
    Vector inVector;        // Внутренний вектор для хранения данных
public:
    bool empty() const;     // Проверяет на пустоту
    int  size()  const;     // Возращает размер стека

    void push(int x);       // Добавленияет элемент в стек
    void pop();             // Удаляет элемент из стека
    int& top();             // Возращает верхний элемент (для изменения)
    const int& top() const; // Возращает верхний элемент (для чтения)
};


// Класс VectorStack - вектор стеков
class VectorStack {
    Stack* data;      // Указатель на массив стеков
    int    lenght;    // Текущее количество стеков
    int    capacity;  // Вместимость массива

    // Метод увеличения вместимости
    void reserve(int newCapacity);

public:
    // Конструкторы и деструктор аналогичны классу Vector
    VectorStack() : data(nullptr), lenght(0), capacity(0) {}

    VectorStack(int value) : data(value ? new Stack[value] : nullptr), lenght(value), capacity(value) {}

    VectorStack(const VectorStack& old);

    VectorStack& operator=(const VectorStack& old);

    ~VectorStack();

    // Методы доступа:
    int  size()  const;
    bool empty() const;

    // Операторы доступа к стекам:
    Stack& operator[](int i);
    const Stack& operator[](int i) const;

    // Добавление стека в конец
    void push_back(const Stack& add);

    // Удаление последнего стека
    void pop_back();
};

#endif // VECTORSTACK_H
