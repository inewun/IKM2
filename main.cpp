#include "algorithms.h"
#include "input_validator.h"
#include <iostream>
#include <fstream>
#include <filesystem>

// Определяем макрос, чтобы избежать конфликта с byte из Windows.h
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace std;
std::ofstream logFile;
bool enableDetailedLogging = false; 

// Функция преобразования строки в число
int stringToNumber(const char* str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Пропускаем пробелы в начале
    while (str[i] == ' ') i++;

    // Проверяем знак
    if (str[i] == '-') {
        sign = -1;
        i++;
    }
    else if (str[i] == '+') {
        i++;
    }

    // Преобразуем цифры в число
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}

void printInstructions() {
    cout << "*** Программа сортировки контейнеров ***\n\n";
    cout << "Правила ввода данных:\n";
    cout << "1. В первой строке введите количество стопок (от 1 до 500)\n";
    cout << "2. В следующих строках для каждой стопки введите:\n";
    cout << "   - количество контейнеров в стопке (от 0 до 500)\n";
    cout << "   - типы товаров в контейнерах (числа от 1 до количества стопок)\n";
    cout << "3. Для выхода из программы введите 0\n";
    cout << "4. Для включения/выключения подробного логирования введите 'log'\n\n";

    // Пример для тестирования
    cout << "Пример ввода:\n";
    cout << "3\n";
    cout << "4 1 2 3 2\n";
    cout << "0\n";
    cout << "0\n\n";
}

int main() {
    // Устанавливаем кодировку консоли
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Открываем файл для логирования
    string logPath = "log.txt";
    logFile.open(logPath, ios::out | ios::trunc);
    if (!logFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл log.txt по пути: " << logPath << "\n";
        return 1;
    }
    cout << "Файл логов открыт: " << logPath << "\n";
    logFile << "=== Начало работы программы ===\n";

    printInstructions();

    while (true) {
        cout << "Введите количество стопок (0 для выхода, 'log' для переключения логирования): ";
        logFile << "\n=== Новый запуск ===\n";
        logFile << "Введите количество стопок (0 для выхода, 'log' для переключения логирования): ";
        string input;
        cin >> input;
        logFile << input << "\n";

        // Выход из программы
        if (input == "0") {
            cout << "\nПрограмма завершена.\n";
            logFile << "\nПрограмма завершена.\n";
            break;
        }

        // Переключение режима логирования
        if (input == "log") {
            enableDetailedLogging = !enableDetailedLogging;
            cout << "Подробное логирование " << (enableDetailedLogging ? "включено" : "выключено") << "\n";
            logFile << "Подробное логирование " << (enableDetailedLogging ? "включено" : "выключено") << "\n";
            continue;
        }

        // Преобразуем строку в число
        int n = stringToNumber(input.c_str());
        if (n == 0 && input[0] != '0') {
            cout << "Ошибка: введите число!\n\n";
            logFile << "Ошибка: введите число!\n\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        // Проверяем корректность количества стопок
        if (n < 1 || n > 500) {
            cout << "Ошибка: требуется от 1 до 500 стопок.\n\n";
            logFile << "Ошибка: требуется от 1 до 500 стопок.\n\n";
            continue;
        }

        cout << "\nВведите данные для каждой стопки:\n";
        logFile << "\nВведите данные для каждой стопки:\n";
        VectorStack stacks(n);
        bool inputError = false;

        // Читаем данные для каждой стопки
        for (int i = 0; i < n && !inputError; ++i) {
            cout << "Стопка " << (i + 1) << ":\n";
            logFile << "Стопка " << (i + 1) << ":\n";
            cout << "Количество контейнеров: ";
            logFile << "Количество контейнеров: ";
            string kInput;
            cin >> kInput;
            logFile << kInput << "\n";
            int k = stringToNumber(kInput.c_str());
            if (k == 0 && kInput[0] != '0') {
                cout << "Ошибка: введите число!\n\n";
                logFile << "Ошибка: введите число!\n\n";
                cin.clear();
                cin.ignore(10000, '\n');
                inputError = true;
                continue;
            }

            if (k < 0 || k > 500) {
                cout << "Ошибка: количество контейнеров должно быть от 0 до 500.\n\n";
                logFile << "Ошибка: количество контейнеров должно быть от 0 до 500.\n\n";
                inputError = true;
                continue;
            }

            // Читаем типы контейнеров
            if (k > 0) {
                cout << "Типы товаров (через пробел): ";
                logFile << "Типы товаров (через пробел): ";
                Vector temp;
                for (int j = 0; j < k && !inputError; ++j) {
                    string xInput;
                    cin >> xInput;
                    logFile << xInput << " ";
                    int x = stringToNumber(xInput.c_str());
                    if (x == 0 && xInput[0] != '0') {
                        cout << "Ошибка: введите число!\n\n";
                        logFile << "Ошибка: введите число!\n\n";
                        cin.clear();
                        cin.ignore(10000, '\n');
                        inputError = true;
                        continue;
                    }

                    if (x < 1 || x > n) {
                        cout << "Ошибка: тип товара должен быть от 1 до " << n << ".\n\n";
                        logFile << "Ошибка: тип товара должен быть от 1 до " << n << ".\n\n";
                        cin.clear();
                        cin.ignore(10000, '\n');
                        inputError = true;
                        continue;
                    }
                    temp.push_back(x);
                }
                cin.ignore(10000, '\n'); // Очищаем буфер после чтения всех чисел
                logFile << "\n";

                // Заполняем стопку контейнерами
                if (!inputError) {
                    for (int j = temp.size() - 1; j >= 0; --j) {
                        stacks[i].push(temp[j]);
                    }
                }
            }
        }

        if (inputError) {
            continue;
        }

        // Показываем начальное состояние
        cout << "\nНачальное состояние стопок:\n";
        logFile << "\n=== Начальное состояние стопок ===\n";
        printAll(stacks, "Начальное состояние");

        cout << "\nВыполняем сортировку...\n\n";
        logFile << "\n=== Начало сортировки ===\n";

        // Специальная обработка для 1 и 2 стопок
        if (n == 1) {
            // Для одной стопки проверяем, все ли контейнеры типа 1
            bool isSorted = true;
            Vector temp;
            while (!stacks[0].empty()) {
                temp.push_back(stacks[0].top());
                stacks[0].pop();
            }
            for (int j = temp.size() - 1; j >= 0; --j) {
                if (temp[j] != 1) {
                    isSorted = false;
                }
                stacks[0].push(temp[j]);
            }

            if (isSorted) {
                cout << "Стопка уже отсортирована.\n";
                logFile << "Стопка уже отсортирована.\n";
            }
            else {
                cout << "0\n";
                logFile << "0\n";
            }
        }
        else if (n == 2) {
            // Для двух стопок проверяем возможность сортировки
            bool canSort = true;
            Vector temp1, temp2;

            // Сохраняем содержимое стопок
            while (!stacks[0].empty()) {
                temp1.push_back(stacks[0].top());
                stacks[0].pop();
            }

            while (!stacks[1].empty()) {
                temp2.push_back(stacks[1].top());
                stacks[1].pop();
            }

            // Проверяем типы контейнеров
            for (int j = 0; j < temp1.size(); ++j) {
                if (temp1[j] != 1 && temp1[j] != 2) {
                    canSort = false;
                    break;
                }
            }

            for (int j = 0; j < temp2.size(); ++j) {
                if (temp2[j] != 1 && temp2[j] != 2) {
                    canSort = false;
                    break;
                }
            }

            // Выполняем сортировку
            if (canSort) {
                printAll(stacks, "Начало сортировки двух стопок");
                // Сортируем первую стопку
                for (int j = temp1.size() - 1; j >= 0; --j) {
                    if (temp1[j] == 1) {
                        stacks[0].push(1);
                    }
                    else {
                        cout << "1 -> 2\n";
                        logFile << "Перемещение: стопка 1 -> стопка 2 (контейнер типа 2)\n";
                        stacks[1].push(2);
                    }
                    printAll(stacks, "После перемещения из первой стопки");
                }

                // Сортируем вторую стопку
                for (int j = temp2.size() - 1; j >= 0; --j) {
                    if (temp2[j] == 2) {
                        stacks[1].push(2);
                    }
                    else {
                        cout << "2 -> 1\n";
                        logFile << "Перемещение: стопка 2 -> стопка 1 (контейнер типа 1)\n";
                        stacks[0].push(1);
                    }
                    printAll(stacks, "После перемещения из второй стопки");
                }

                cout << "Сортировка завершена.\n";
                logFile << "Сортировка завершена.\n";
            }
            else {
                cout << "0\n";
                logFile << "0\n";
            }
        }
        else {
            // Сортируем три и более стопок
            for (int i = 0; i + 2 < stacks.size(); ++i) {
                mergeAndSort(stacks, i, i + 1, i + 2);
                distribute(i + 2, stacks);
            }
        }

        // Показываем результат
        cout << "\nРезультат сортировки:\n";
        logFile << "\n=== Результат сортировки ===\n";
        printAllResult(stacks);

        cout << "\nСортировка завершена. Введите новые данные или 0 для выхода.\n\n";
        logFile << "\n=== Сортировка завершена ===\n\n";
    }

    logFile.close();
    return 0;
}