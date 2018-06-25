/**
 * @file      stack.hpp
 * @brief     Stack implementation
 * @author    Nick Swaerdens
 * @license   See LICENSE
 */

#ifndef STACK_HPP
#define STACK_HPP

namespace Mapping {

template <typename T, size_t MAX>
class Stack {
  private:
    T a[MAX];
    T *index;

  public:
    Stack() : index{a} {
    }

    bool isEmpty() {
        return index == a;
    }

    // Substract memory adress to get size.
    // Defined behaviour because the element is initialised right after the array.
    size_t size() {
        return index - a;
    }

    void clear() {
        index = a;
    }

    // Allows for setting the top element without incrementing the index.
    void set(T item) {
        if ((size() > 0) && (size() < MAX)) {
            *(index - 1) = item;
        }
    }

    void push(T item) {
        if (size() < MAX) {
            *(index++) = item;
        }
    }

    T peek() {
        if (size() > 0) {
            return *(index - 1);
        } else {
            return a[0];
        }
    }

    T &peekRef() {
        if (size() > 0) {
            return *(index - 1);
        } else {
            return a[0];
        }
    }

    T pop() {
        if (size() > 0) {
            return *(--index);
        } else {
            return a[0];
        }
    }

    // Caution, object can be overwritten when another element is pushed.
    T &popRef() {
        if (size() > 0) {
            return *(--index);
        } else {
            return a[0];
        }
    }
};
} // namespace Mapping

#endif // STACK_HPP