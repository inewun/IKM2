#include "algorithms.h"
#include "input_validator.h"
#include <iostream>

// Флаг для включения/выключения подробного логирования
bool enableDetailedLogging = false;

/* Функция выводит информацию о перемещении элемента между стеками
 * @param индекс стека-источника
 * @param индекс стека-приемника
 * @param значение переносимого элемента
 */
void printAction(int from, int to, int value) {
    // Формат вывода: "<from> -> <to>"
    std::cout << from + 1 << " -> " << to + 1 << " (" << value << ")" << '\n';
}


/* Функция выводит текущее состояние всех стеков
 * @param вектор стеков для вывода
 * @param дополнительное сообщение для вывода перед состоянием стеков
 */
void printAll(const VectorStack& stacks, const std::string& message) {
    if (!enableDetailedLogging) return;

    std::cout << "\n" << message << "\n";
    for (int i = 0; i < stacks.size(); ++i) {
        std::cout << "Стопка " << (i + 1) << ": ";
        Stack temp = stacks[i];
        while (!temp.empty()) {
            std::cout << temp.top() << " ";
            temp.pop();
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Доблирование для вывода в результат
void printAllResult(const VectorStack& stacks) {
    cout << "\n";
    for (int i = 0; i < stacks.size(); ++i) {
        std::cout << "Стопка " << (i + 1) << ": ";
        Stack temp = stacks[i];
        while (!temp.empty()) {
            std::cout << temp.top() << " ";
            temp.pop();
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


/* Функция чтения начального состояния стеков из входного потока
 * @return вектор стеков с начальным состоянием
 */
VectorStack readStacks() {
    int n;
    if (!(std::cin >> n)) {
        std::cout << "Ошибка: введите число!\n";
        clearInputBuffer();
        return VectorStack();
    }

    if (n < 3 || n > 500) {
        std::cout << "Ошибка: требуется от 3 до 500 стопок.\n";
        return VectorStack();
    }

    VectorStack stacks(n);

    for (int i = 0; i < n; ++i) {
        int k;
        if (!(std::cin >> k)) {
            std::cout << "Ошибка: введите число контейнеров для стопки " << (i + 1) << "!\n";
            clearInputBuffer();
            return VectorStack();
        }

        if (k < 0 || k > 500) {
            std::cout << "Ошибка: количество контейнеров должно быть от 0 до 500.\n";
            return VectorStack();
        }

        Vector temp;
        for (int j = 0; j < k; ++j) {
            int x;
            if (!(std::cin >> x)) {
                std::cout << "Ошибка: введите тип товара для контейнера " << (j + 1) << " в стопке " << (i + 1) << "!\n";
                clearInputBuffer();
                return VectorStack();
            }

            if (x < 1 || x > n) {
                std::cout << "Ошибка: тип товара должен быть от 1 до " << n << ".\n";
                return VectorStack();
            }
            temp.push_back(x);
        }

        for (int j = temp.size() - 1; j >= 0; --j) {
            stacks[i].push(temp[j]);
        }
    }

    return stacks;
}


/* Функция для слияния и сортировки двух стеков
 * @param вектор стеков
 * @param индекс первого стека-источника (сортировочный стек)
 * @param индекс второго стека-источника (буферный стек)
 * @param индекс стека-приемника (для результата)
 */
void mergeAndSort(VectorStack& stacks, int fromOne, int fromTwo, int to) {
    Stack& sorted = stacks[fromOne];
    Stack& buffer = stacks[fromTwo];
    Stack& merged = stacks[to];

    printAll(stacks, "Начало mergeAndSort");

    while (!sorted.empty()) {
        int value = sorted.top();
        sorted.pop();
        merged.push(value);
        printAction(fromOne, to, value);
        printAll(stacks, "После перемещения из sorted в merged");
    }

    while (!buffer.empty()) {
        int value = buffer.top();
        buffer.pop();
        merged.push(value);
        printAction(fromTwo, to, value);
        printAll(stacks, "После перемещения из buffer в merged");
    }

    while (!merged.empty()) {
        int current = merged.top();

        if (sorted.empty() || sorted.top() <= current) {
            merged.pop();
            sorted.push(current);
            printAction(to, fromOne, current);
            printAll(stacks, "После перемещения из merged в sorted");
            continue;
        }

        merged.pop();
        buffer.push(current);
        printAction(to, fromTwo, current);
        printAll(stacks, "После перемещения из merged в buffer");

        while (!sorted.empty() && sorted.top() > buffer.top()) {
            int value = sorted.top();
            sorted.pop();
            merged.push(value);
            printAction(fromOne, to, value);
            printAll(stacks, "После перемещения из sorted в merged");
        }

        current = buffer.top();
        buffer.pop();
        sorted.push(current);
        printAction(fromTwo, fromOne, current);
        printAll(stacks, "После перемещения из buffer в sorted");
    }

    while (!sorted.empty()) {
        int value = sorted.top();
        sorted.pop();
        merged.push(value);
        printAction(fromOne, to, value);
        printAll(stacks, "После перемещения из sorted в merged");
    }
}


/* Функция распределяет цифры из стека с индексом i в соответствующие стеки
 * согласно их значениям (цифра n должна оказаться в стеке stacks[n-1])
 * @param индекс исходного стека, из которого распределяем цифры
 * @param вектор стеков
 */
void distribute(int i, VectorStack& stacks) {
    printAll(stacks, "Начало distribute");

    while (!stacks[i].empty()) {
        int num = stacks[i].top();
        stacks[i].pop();

        if (num == i + 1) {
            stacks[i].push(num);
            printAll(stacks, "Элемент уже в своем стеке");
            break;
        }

        stacks[num - 1].push(num);
        printAction(i, num - 1, num);
        printAll(stacks, "После перемещения элемента");
    }
}
