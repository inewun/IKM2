#ifndef VECTORSTACK_H
#define VECTORSTACK_H

// ����� Vector
class Vector {
    int* data;          // ��������� �� ������ ���������
    int  length;        // ������� ���������� ��������� � �������
    int  capacity;      // ����� ����������� �������

    // ����������� ����������� �������
    void reserve(int newCap);

public:
    // ����������� �� ��������� - ������� ������ ������
    Vector() : data(nullptr), length(0), capacity(0) {}

    // ����������� � ���������� - ������� ������ ��������� �������
    Vector(int value) : data(value ? new int[value] : nullptr), length(value), capacity(value) {}

    // ����������� �����������
    Vector(const Vector& old);

    // �������� ������������
    Vector& operator=(const Vector& old);

    // ���������� - ����������� ������
    ~Vector();

    // ������ �������:
    int  size()  const; // ���������� ������� ������
    bool empty() const; // ��������� �� �������

    // ��������� ������� � ���������:
    int& operator[](int i);             // ��� ���������
    const int& operator[](int i) const; // ��� ������

    // ���������� �������� � �����
    void push_back(int add);

    // �������� ���������� ��������
    void pop_back();
};


// ����� Stack �� ������ ������ Vector
class Stack {
    Vector inVector;        // ���������� ������ ��� �������� ������
public:
    bool empty() const;     // ��������� �� �������
    int  size()  const;     // ��������� ������ �����

    void push(int x);       // ������������ ������� � ����
    void pop();             // ������� ������� �� �����
    int& top();             // ��������� ������� ������� (��� ���������)
    const int& top() const; // ��������� ������� ������� (��� ������)
};


// ����� VectorStack - ������ ������
class VectorStack {
    Stack* data;      // ��������� �� ������ ������
    int    lenght;    // ������� ���������� ������
    int    capacity;  // ����������� �������

    // ����� ���������� �����������
    void reserve(int newCapacity);

public:
    // ������������ � ���������� ���������� ������ Vector
    VectorStack() : data(nullptr), lenght(0), capacity(0) {}

    VectorStack(int value) : data(value ? new Stack[value] : nullptr), lenght(value), capacity(value) {}

    VectorStack(const VectorStack& old);

    VectorStack& operator=(const VectorStack& old);

    ~VectorStack();

    // ������ �������:
    int  size()  const;
    bool empty() const;

    // ��������� ������� � ������:
    Stack& operator[](int i);
    const Stack& operator[](int i) const;

    // ���������� ����� � �����
    void push_back(const Stack& add);

    // �������� ���������� �����
    void pop_back();
};

#endif // VECTORSTACK_H