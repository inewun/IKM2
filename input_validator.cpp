#include "input_validator.h"

bool validateInput(int n) {
    // Проверка на положительное число стопок
    if (n <= 0 || n > 500) {
        std::cout << "0\n"; // Выводим 0 как признак невозможности решения
        return false;
    }
    return true;
}

bool validateStackInput(int k, int n) {
    // Проверка на корректное количество контейнеров
    if (k < 0 || k > 500) {
        std::cout << "0\n";
        return false;
    }

    // Проверка каждого контейнера в стопке
    for (int i = 0; i < k; ++i) {
        int container;
        // Проверка на корректный ввод числа
        if (!(std::cin >> container)) {
            // Если ввод не удался, проверяем причину
            if (std::cin.eof()) {
                std::cout << "0\n"; // Достигнут конец файла
            }
            else {
                std::cout << "0\n"; // Введены некорректные символы
                clearInputBuffer(); // Очищаем буфер ввода
            }
            return false;
        }
        // Проверка на корректный тип товара (от 1 до n)
        if (container < 1 || container > n) {
            std::cout << "0\n";
            return false;
        }
    }
    return true;
}

void clearInputBuffer() {
    std::cin.clear();
    while (std::cin.get() != '\n'); // Читаем все символы до конца строки
}

bool isNumberInput() {
    if (std::cin.fail()) {
        std::cout << "0\n";
        clearInputBuffer();
        return false;
    }
    return true;
}