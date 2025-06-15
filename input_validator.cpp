#include "input_validator.h"

bool validateInput(int n) {
    // Проверка на допустимое число стопок
    if (n <= 0 || n > 500) {
        std::cout << "0\n"; // Выводим 0 при недопустимом вводе
        return false;
    }
    return true;
}

bool validateStackInput(int k, int n) {
    // Проверка на допустимое количество контейнеров
    if (k < 0 || k > 500) {
        std::cout << "0\n";
        return false;
    }

    // Пропускаем оставшиеся символы до конца строки
    while (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
        std::cin.get();
    }
    std::cin.get(); // Пропускаем символ новой строки

    // Проверка содержимого контейнеров в стопке
    for (int i = 0; i < k; ++i) {
        int container = 0;
        char c;

        // Пропускаем пробелы
        while (std::cin.peek() == ' ') {
            std::cin.get();
        }

        // Читаем число посимвольно
        while (std::cin.peek() >= '0' && std::cin.peek() <= '9') {
            c = std::cin.get();
            container = container * 10 + (c - '0');
        }

        // Проверяем, что прочитали хотя бы одну цифру
        if (container == 0) {
            std::cout << "Ошибка: введите число!\n";
            return false;
        }

        // Проверка на допустимый тип контейнера (от 1 до n)
        if (container < 1 || container > n) {
            std::cout << "Ошибка: тип товара должен быть от 1 до " << n << ".\n";
            return false;
        }
    }
    return true;
}

void clearInputBuffer() {
    std::cin.clear();
    while (std::cin.get() != '\n'); // Читаем до конца строки
}

bool isNumberInput() {
    if (std::cin.fail()) {
        std::cout << "0\n";
        clearInputBuffer();
        return false;
    }
    return true;
}