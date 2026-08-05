/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
#include "class.h"

void sandbox() {
    // STUDENT TODO: Construct an instance of your class!
    stack<int> stk;

    for (int i = 1; i <= 20; ++i) {
        stk.push(i);
    }

    for (int i = 1; i <= 10; ++i) {
        stk.pop();
    }

    while (!stk.isEmpty()) {
        stk.pop();
    }

    assert(!stk.pop());
}