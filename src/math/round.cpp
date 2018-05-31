#include "round.hpp"

namespace math {
int round(double number) {
    if (number - (int)number < 0.5) {
        return (int)number;
    } else {
        return (int)number + 1;
    }
}
} // namespace math
