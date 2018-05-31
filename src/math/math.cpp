#include "math.hpp"

namespace math {
int pow(int base, int exp) {
    int result = 1;
    while (exp) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

float pow(float base, int exp) {
    float p = 1.0;
    for (int i = 1; i <= exp; i++)
        p = p * base;
    return p;
}

int abs(int v) {
    return v * ((v > 0) - (v < 0));
}

float abs(float v) {
    return v * ((v > 0) - (v < 0));
}

float sqrt(const float x) {
    union {
        int i;
        float x;
    } u;
    u.x = x;
    u.i = (1 << 29) + (u.i >> 1) - (1 << 22);

    u.x = u.x + x / u.x;
    u.x = 0.25f * u.x + x / u.x;

    return u.x;
}

int ceil(float num) {
    int inum = (int)num;
    if (num == (float)inum) {
        return inum;
    }
    return inum + 1;
}

int getPt(int n1, int n2, float perc) {
    int diff = n2 - n1;
    return (n1 + (diff * perc));
}

float fact(int x) {
    float f = 1.0;
    for (int i = 1; i <= x; i++) {
        f = f * i;
    }
    return f;
}

float cos(float x) {
    float sum_positive = 0.0;
    float sum_negative = 0.0;
    float output = 0.0;
    for (int i = 4; i <= 20; i += 4) {
        sum_positive = sum_positive + (pow(x, i) / fact(i));
    }

    for (int i = 2; i <= 20; i += 4) {
        sum_negative = sum_negative + (pow(x, i) / fact(i));
    }

    output = (1 - (sum_negative) + (sum_positive));
    return output;
}

float sin(float x) {
    float sum = 0.0;
    for (int i = 0; i < 9; i++) {
        float top = pow(-1, i) * pow(x, 2 * i + 1);
        float bottom = fact(2 * i + 1);
        sum = sum + top / bottom;
    }
    return sum;
}

void int_to_string(int n, char ch1[]) {
    char buffer[5];
    int i = 0;

    bool isNeg = n < 0;

    unsigned int n1 = isNeg ? -n : n;

    while (n1 != 0) {
        buffer[i++] = n1 % 10 + '0';
        n1 = n1 / 10;
    }

    if (isNeg)
        buffer[i++] = '-';

    buffer[i] = '\0';

    for (int t = 0; t < i / 2; t++) {
        buffer[t] ^= buffer[i - t - 1];
        buffer[i - t - 1] ^= buffer[t];
        buffer[t] ^= buffer[i - t - 1];
    }

    if (n == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
    }

    int k = 0;
    int l = 0;
    while (k < 5) {
        ch1[k] = buffer[l];
        l++;
        k++;
    }
}

float atan(float inX) {
    float x = inX;
    return x * (-0.1784f * abs(x) - 0.0663f * x * x + 1.0301f);
}

float acos(float inX) {
    float x1 = abs(inX);
    float x2 = x1 * x1;
    float x3 = x2 * x1;
    float s;

    s = -0.2121144f * x1 + 1.5707288f;
    s = 0.0742610f * x2 + s;
    s = -0.0187293f * x3 + s;
    s = sqrt(1.0f - x1) * s;

    float pi = 3.14159265359;
    return inX >= 0.0f ? s : pi - s;
}
} // namespace math