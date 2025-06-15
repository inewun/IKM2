#include "input_validator.h"

bool validateInput(int n) {
    // �������� �� ���������� ����� ������
    if (n <= 0 || n > 500) {
        std::cout << "0\n"; // ������� 0 ��� ������������ �����
        return false;
    }
    return true;
}

bool validateStackInput(int k, int n) {
    // �������� �� ���������� ���������� �����������
    if (k < 0 || k > 500) {
        std::cout << "0\n";
        return false;
    }

    // ���������� ���������� ������� �� ����� ������
    while (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
        std::cin.get();
    }
    std::cin.get(); // ���������� ������ ����� ������

    // �������� ����������� ����������� � ������
    for (int i = 0; i < k; ++i) {
        int container = 0;
        char c;

        // ���������� �������
        while (std::cin.peek() == ' ') {
            std::cin.get();
        }

        // ������ ����� �����������
        while (std::cin.peek() >= '0' && std::cin.peek() <= '9') {
            c = std::cin.get();
            container = container * 10 + (c - '0');
        }

        // ���������, ��� ��������� ���� �� ���� �����
        if (container == 0) {
            std::cout << "������: ������� �����!\n";
            return false;
        }

        // �������� �� ���������� ��� ���������� (�� 1 �� n)
        if (container < 1 || container > n) {
            std::cout << "������: ��� ������ ������ ���� �� 1 �� " << n << ".\n";
            return false;
        }
    }
    return true;
}

void clearInputBuffer() {
    std::cin.clear();
    while (std::cin.get() != '\n'); // ������ �� ����� ������
}

bool isNumberInput() {
    if (std::cin.fail()) {
        std::cout << "0\n";
        clearInputBuffer();
        return false;
    }
    return true;
}