#include "input_validator.h"

bool validateInput(int n) {
    // �������� �� ������������� ����� ������
    if (n <= 0 || n > 500) {
        std::cout << "0\n"; // ������� 0 ��� ������� ������������� �������
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

    // �������� ������� ���������� � ������
    for (int i = 0; i < k; ++i) {
        int container;
        // �������� �� ���������� ���� �����
        if (!(std::cin >> container)) {
            // ���� ���� �� ������, ��������� �������
            if (std::cin.eof()) {
                std::cout << "0\n"; // ��������� ����� �����
            }
            else {
                std::cout << "0\n"; // ������� ������������ �������
                clearInputBuffer(); // ������� ����� �����
            }
            return false;
        }
        // �������� �� ���������� ��� ������ (�� 1 �� n)
        if (container < 1 || container > n) {
            std::cout << "0\n";
            return false;
        }
    }
    return true;
}

void clearInputBuffer() {
    std::cin.clear();
    while (std::cin.get() != '\n'); // ������ ��� ������� �� ����� ������
}

bool isNumberInput() {
    if (std::cin.fail()) {
        std::cout << "0\n";
        clearInputBuffer();
        return false;
    }
    return true;
}