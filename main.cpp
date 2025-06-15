#include "algorithms.h"
#include "input_validator.h"
#include <iostream>

// Определяем макрос, чтобы избежать конфликта с byte из Windows.h
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace std;

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
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printInstructions();

    while (true) {
        cout << "Введите количество стопок (0 для выхода, 'log' для переключения логирования): ";
        string input;
        cin >> input;

        // Выход из программы
        if (input == "0") {
            cout << "\nПрограмма завершена.\n";
            break;
        }

        // Переключение режима логирования
        if (input == "log") {
            enableDetailedLogging = !enableDetailedLogging;
            cout << "Подробное логирование " << (enableDetailedLogging ? "включено" : "выключено") << "\n";
            continue;
        }

        // Возвращаем ввод обратно в поток
        cin.putback(input[0]);
        for (int i = 1; i < input.length(); ++i) {
            cin.putback(input[i]);
        }

        // Читаем количество стопок
        int n;
        if (!(cin >> n)) {
            cout << "Ошибка: введите число!\n\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        // Проверяем корректность количества стопок
        if (n < 1 || n > 500) {
            cout << "Ошибка: требуется от 1 до 500 стопок.\n\n";
            continue;
        }

        cout << "\nВведите данные для каждой стопки:\n";
        VectorStack stacks(n);
        bool inputError = false;

        // Читаем данные для каждой стопки
        for (int i = 0; i < n && !inputError; ++i) {
            cout << "Стопка " << (i + 1) << ":\n";
            cout << "Количество контейнеров: ";

            int k;
            if (!(cin >> k)) {
                cout << "Ошибка: введите число!\n\n";
                cin.clear();
                cin.ignore(10000, '\n');
                inputError = true;
                continue;
            }

            if (k < 0 || k > 500) {
                cout << "Ошибка: количество контейнеров должно быть от 0 до 500.\n\n";
                inputError = true;
                continue;
            }

            // Читаем типы контейнеров
            if (k > 0) {
                cout << "Типы товаров (через пробел): ";
                Vector temp;
                for (int j = 0; j < k && !inputError; ++j) {
                    int x;
                    if (!(cin >> x)) {
                        cout << "Ошибка: введите число!\n\n";
                        cin.clear();
                        cin.ignore(10000, '\n');
                        inputError = true;
                        continue;
                    }

                    if (x < 1 || x > n) {
                        cout << "Ошибка: тип товара должен быть от 1 до " << n << ".\n\n";
                        cin.clear();
                        cin.ignore(10000, '\n');
                        inputError = true;
                        continue;
                    }
                    temp.push_back(x);
                }

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
        printAll(stacks, "");

        cout << "\nВыполняем сортировку...\n\n";

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
            }
            else {
                cout << "0\n";
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
                // Сортируем первую стопку
                for (int j = temp1.size() - 1; j >= 0; --j) {
                    if (temp1[j] == 1) {
                        stacks[0].push(1);
                    }
                    else {
                        cout << "1 -> 2\n";
                        stacks[1].push(2);
                    }
                }

                // Сортируем вторую стопку
                for (int j = temp2.size() - 1; j >= 0; --j) {
                    if (temp2[j] == 2) {
                        stacks[1].push(2);
                    }
                    else {
                        cout << "2 -> 1\n";
                        stacks[0].push(1);
                    }
                }
            }
            else {
                cout << "0\n";
            }
        }
        else {
            // Сортируем три и более стопок
            for (int i = 0; i + 2 < stacks.size(); ++i) {
                mergeAndSort(stacks, i, i + 1, i + 2);
                distribute(i + 2, stacks);
            }
        }

        // Вывод результата
        cout << "\nРезультат сортировки:";
        printAllResult(stacks);

        cout << "\nСортировка завершена. Введите новые данные или 0 для выхода.\n\n";
    }

    return 0;
}
