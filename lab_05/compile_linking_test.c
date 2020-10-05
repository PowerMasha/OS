#include "f_deque.h"

extern f_deque* create(); // объявление переменных и функций
extern void push_back(f_deque* deque, double flt);
extern void pop_back(f_deque* deque);
extern void push_front(f_deque* deque, double flt);
extern void pop_front(f_deque* deque);
extern void print(f_deque* deque);
extern void destroy(f_deque* deque);

int main() {
    f_deque* deque = create(); // создание дека
    pop_back(deque);  //удаление справа
    pop_front(deque); // удаление слева
    print(deque); // вывод дека
    push_back(deque, 12.34); // добавление элемента справа
    print(deque);
    pop_front(deque); //удаление слева
    push_front(deque, 12.34); // добавление элемента слева
    print(deque);
    push_back(deque, 56.78); //справа
    push_front(deque, 90.12); // слева
    print(deque);
    pop_front(deque);
    pop_back(deque);
    print(deque);
    pop_back(deque);
    print(deque);
    destroy(deque);
    return 0;
}