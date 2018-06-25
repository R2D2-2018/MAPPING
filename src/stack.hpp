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

    /**
     * @brief Checks if the stack is empty.
     *
     * @return Returns whether the stack is empty or not.
     */
    bool isEmpty() {
        return index == a;
    }

    /**
     * @brief Checks the size of the stack.
     *
     * Checks the size of the stack by substracting the first element of the array from the pointer.
     * This is defined behaviour because the index is initializes right after the array.
     *
     * @return Returns the size of the stack.
     */
    size_t size() {
        return index - a;
    }

    /**
     * @brief Clears the stack.
     */
    void clear() {
        index = a;
    }

    /**
     * @brief Sets the values of the last item on the stack.
     */
    void set(T item) {
        if ((size() > 0) && (size() < MAX)) {
            *(index - 1) = item;
        }
    }

    /**
     * @brief Pushes an item to the stack.
     *
     * Pushed items are copied onto the stack.
     */
    void push(T item) {
        if (size() < MAX) {
            *(index++) = item;
        }
    }

    /**
     * @brief Returns a copy of the last item on the stack.
     *
     * This function does not remove the item.
     *
     * @returns a copy of the item or the first element.
     */
    T peek() {
        if (size() > 0) {
            return *(index - 1);
        } else {
            return a[0];
        }
    }

    /**
     * @brief Returns a reference to the last item on the stack.
     *
     * This allows for editing the item on the stack.
     *
     * @returns Reference of the item or the first element.
     */
    T &peekRef() {
        if (size() > 0) {
            return *(index - 1);
        } else {
            return a[0];
        }
    }

    /**
     * @brief Returns a copy of the last item on the stack.
     *
     * This function also removes the item from the stack.
     *
     * @returns Copy of the item or the first element.
     */
    T pop() {
        if (size() > 0) {
            return *(--index);
        } else {
            return a[0];
        }
    }
};
} // namespace Mapping

#endif // STACK_HPP