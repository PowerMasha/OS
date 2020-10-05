#include <stdio.h>
#include <dlfcn.h> // для работы с динамической библиотекой
#include "f_deque.h"

/*=================================compile-hints======================================================//
 *  gcc -fPIC -c f_deque.c  // -fPIC позволяет создавать независимый от размещения в оперативной памяти код
 *  gcc -shared f_deque.o -o f_deque.so
 *  gcc runtime_test.c -o runtime -ldl
 *
 *===================================================================================================*/

int main(){
    void *lib = dlopen("./f_deque.so", RTLD_LAZY); // открытие библиотеки,
    if (!lib) {
        printf("dlopen error\n");
        return -1;
    }

    f_deque*(*create)() = dlsym(lib, "create"); // получение адресов функций пои их имени из библиотеки
    _Bool(*empty)(f_deque* deque) = dlsym(lib, "empty");
    void(*push_back)(f_deque* deque, double flt) = dlsym(lib, "push_back");
    void(*pop_back)(f_deque* deque) = dlsym(lib, "pop_back");
    void(*push_front)(f_deque* deque, double flt) = dlsym(lib, "push_front");
    void(*pop_front)(f_deque* deque) = dlsym(lib, "pop_front");
    void(*print)(f_deque* deque) = dlsym(lib, "print");
    void(*destroy)(f_deque* deque) = dlsym(lib, "destroy");
    if(create == NULL || empty == NULL || push_back == NULL || pop_back == NULL ||
       push_front == NULL || pop_front == NULL || print == NULL || destroy == NULL) {
        printf("dlsym error\n");
        return -1;
    }

    f_deque* deque = (create)();
    (*pop_back)(deque);
    (*pop_front)(deque);
    (*print)(deque);
    (*push_back)(deque, 12.34);
    (*print)(deque);
    (*pop_front)(deque);
    (*push_front)(deque, 12.34);
    (*print)(deque);
    (*push_back)(deque, 56.78);
    (*push_front)(deque, 90.12);
    (*print)(deque);
    (*pop_front)(deque);
    (*pop_back)(deque);
    (*print)(deque);
    (*pop_back)(deque);
    (*print)(deque);
    (*destroy)(deque);

    dlclose(lib); // закрытие библиотеки
    return 0;
}