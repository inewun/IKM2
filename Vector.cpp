#include "VectorStack.h"

// ����������� ����������� �������
void Vector::reserve(int newCap) {
    if (newCap <= capacity) return;  // ����� ����������� ������ ���� �� ������ �������
    int* newMass = new int[newCap];  // �������� ������ ������� � ����� ������������
    for (int i = 0; i < length; ++i) newMass[i] = data[i];  // �������� �������� �� ������� ������� � �����
    delete[] data;      // ����������� ������ ������� �������
    data = newMass;     // ��������� ��������� �� ����� ������
    capacity = newCap;  // ��������� �������� �����������
}

// ����������� �����������
Vector::Vector(const Vector& old) : data(nullptr), length(old.length), capacity(old.capacity) {
    if (capacity) {
        data = new int[capacity];
        for (int i = 0; i < length; ++i) data[i] = old.data[i]; // �������� �������� �� �������� �������
    }
}

// �������� ������������
Vector& Vector::operator=(const Vector& old) {
    if (this == &old) return *this;  // ��������� �� ����������������
    delete[] data;                   // ����������� ������� ������
    length = old.length;
    capacity = old.capacity;
    data = capacity ? new int[capacity] : nullptr;          // �������� ����� ������
    for (int i = 0; i < length; ++i) data[i] = old.data[i]; // �������� ��������
    return *this;
}

// ����������
Vector::~Vector() { delete[] data; }

// ������ �������:
int Vector::size() const { return length; }         // ���������� ������� ������
bool Vector::empty() const { return length == 0; }  // ��������� �� �������

// ��������� ������� � ���������:
int& Vector::operator[](int i) { return data[i]; }              // ��� ���������
const int& Vector::operator[](int i) const { return data[i]; }  // ��� ������

// ���������� �������� � �����
void Vector::push_back(int add) {
    if (length == capacity) reserve(capacity ? capacity * 2 : 1);  // ����������� ����������� ��� �������������
    data[length++] = add;  // ��������� ������� � ����������� �����
}

// �������� ���������� ��������
void Vector::pop_back() { if (length) --length; }
