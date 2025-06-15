#include "algorithms.h"


/* Функция выводит информацию о перемещении элемента между стеками
 * @param индекс стека-источника
 * @param индекс стека-приемника
 * @param значение переносимого элемента
 */
void printAction(int from, int to, int value) {
    // Формат вывода: "<значение> s<индекс_источника> -> s<индекс_приемника>"
    std::cout << value << " s" << from << " -> s" << to << '\n';
}


/* Функция выводит текущее состояние всех стеков
 * @param вектор стеков для вывода
 * @param дополнительное сообщение для вывода перед состоянием стеков
 */
void printAll(const VectorStack& stacks, const std::string& message) {
    // Выводит дополнительное сообщение, если оно не пустое
    if (!message.empty()) std::cout << message << '\n'; 

    // Проходит по всем стекам в векторе
    for (int i = 0; i < stacks.size(); ++i) { 
        std::cout << "stack[" << i << "]: [ ";

        // Создает временную копию стека для вывода содержимого (чтобы не изменять оригинальный стек)
        Stack temp = stacks[i];

        // Выводит все элементы стека (начиная с верхнего)
        while (!temp.empty()) {
            std::cout << temp.top() << ' ';
            temp.pop();
        }

        std::cout << "]\n";  // Закрывает вывод стека
    }

    // Разделитель для удобства чтения
    std::cout << "-----------------------------\n";
}


/* Функция чтения начального состояния стеков из входного потока
 * @return вектор стеков с начальным состоянием
 */
VectorStack readStacks() {
    int n;
    std::cin >> n;          // Считывает количество стеков
    VectorStack stacks(n);  // Создает вектор из n стеков

    // Читает данные для каждого стека
    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;  // Читает количество элементов в текущем стеке

        Vector temp;  // Временный вектор для хранения элементов

        // Считывает элементы стека во временный вектор
        for (int j = 0; j < k; ++j) {
            int x;
            std::cin >> x;
            temp.push_back(x);
        }

        // Заполняет стек из вектора в обратном порядке (так как в стеке первый прочитанный элемент окажется внизу)
        for (int j = temp.size() - 1; j >= 0; --j)
            stacks[i].push(temp[j]);  // Помещает элементы "снизу-вверх"
    }

    // Выводит начальное состояние стеков
    printAll(stacks, "Initial state:");

    return stacks;  // Возвращает заполненный вектор стеков
}


/* Функция для слияния и сортировки двух стеков
 * @param вектор стеков
 * @param индекс первого стека-источника (сортировочный стек)
 * @param индекс второго стека-источника (буферный стек)
 * @param индекс стека-приемника (для результата)
 */
void mergeAndSort(VectorStack& stacks, int fromOne, int fromTwo, int to) {
    // Получаем ссылки на стеки по их индексам
    Stack& sorted = stacks[fromOne]; // Основной стек для сортировки
    Stack& buffer = stacks[fromTwo]; // Вспомогательный стек (буфер для одной цифры)
    Stack& merged = stacks[to];      // Стек для результата (также используется в процессе сортировки)

    // Перенос всех элементов из первого стека (sorted) в стек результата (merged)
    while (!sorted.empty()) {
        int value = sorted.top(); // Берет верхний элемент
        sorted.pop();             // Удаляет его из исходного стека
        merged.push(value);       // Добавляет в стек результата

        // Логирование операций
        printAction(fromOne, to, value);  // Печать действия (перенос из fromOne в to)
        printAll(stacks, "After move:");  // Печать состояния всех стеков
    }

    // Перенос всех элементов из второго стека (buffer) в стек результата (merged)
    while (!buffer.empty()) {
        int value = buffer.top();  // Берет верхний элемент
        buffer.pop();              // Удаляет его из буферного стека
        merged.push(value);        // Добавляет в стек результата

        // Логирование операций
        printAction(fromTwo, to, value);  // Печать действия (перенос из fromTwo в to)
        printAll(stacks, "After move:");  // Печать состояния всех стеков
    }

    // Сортировка элементов в стеке merged
    while (!merged.empty()) {
        int current = merged.top(); // Текущий верхний элемент merged

        // Если sorted пуст или верхний элемент sorted <= текущему элементу, переносит элемент в sorted
        if (sorted.empty() || sorted.top() <= current) {
            merged.pop();          // Удаляет из merged
            sorted.push(current);  // Добавляет в sorted

            // Логирование
            printAction(to, fromOne, current);  // Печать действия (перенос из to в fromOne)
            printAll(stacks, "Direct insert:"); // Печать состояния стеков
            continue; // Переходит к следующей итерации
        }

        // Если верхний элемент sorted > текущего элемента, временно сохраняет текущий элемент в буфер
        merged.pop();          // Удаляет из merged
        buffer.push(current);  // Добавляет в буфер

        // Логирование
        printAction(to, fromTwo, current); // Печать действия (перенос из to в fromTwo)
        printAll(stacks, "Buffered:");     // Печать состояния стеков

        // Переносит все элементы из sorted в merged, которые больше элемента в буфере
        while (!sorted.empty() && sorted.top() > buffer.top()) {
            int value = sorted.top();  // Берет верхний элемент sorted
            sorted.pop();              // Удаляет его
            merged.push(value);        // Добавляет в merged

            // Логирование
            printAction(fromOne, to, value); // Печать действия (перенос из fromOne в to)
            printAll(stacks, "Shift > x:");  // Печать состояния стеков
        }

        // Помещает элемент из буфера в sorted
        current = buffer.top(); // Берет элемент из буфера
        buffer.pop();           // Удаляет из буфера
        sorted.push(current);   // Добавляет в sorted

        // Логирование
        printAction(fromTwo, fromOne, current);  // Печать действия (перенос из fromTwo в fromOne)
        printAll(stacks, "Insert from buffer:"); // Печать состояния стеков
    }

    // Перенос всех отсортированных элементов из sorted обратно в merged (результирующий стек)
    while (!sorted.empty()) {
        int value = sorted.top(); // Берет верхний элемент
        sorted.pop();             // Удаляем из sorted
        merged.push(value);       // Добавляет в merged

        // Логирование
        printAction(fromOne, to, value); // Печать действия (перенос из fromOne в to)
        printAll(stacks, "Final move:"); // Печать состояния стеков
    }
}


/* Функция распределяет цифры из стека с индексом i в соответствующие стеки 
 * согласно их значениям (цифра n должна оказаться в стеке stacks[n-1])
 * @param индекс исходного стека, из которого распределяем цифры
 * @param вектор стеков
 */
void distribute(int i, VectorStack& stacks) {
    
    while (!stacks[i].empty()) {   // Пока исходный стек не пуст
        int num = stacks[i].top(); // Берет верхнюю цифру из стека
        stacks[i].pop();           // Удаляет ее из стека
        
        if (num == i + 1) {      // Если цифра уже находится в "своем" стеке (num == i+1)
            stacks[i].push(num); // Возвращаем цифру обратно в стек
            printAll(stacks, "-----------------------------"); // Выводим состояние стеков (разделитель для наглядности)
            break;
        }

        // Если цифра не в своем стеке, помещаем ее в соответствующий стек
        stacks[num - 1].push(num);

        // Выводим текущее состояние стеков
        printAll(stacks, "Current state:");
    }
}