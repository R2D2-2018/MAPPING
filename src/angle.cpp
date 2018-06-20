#include "angle.hpp"

const double Mapping::Angle::pi = 3.14159265358979323846;

Mapping::Angle::Angle() : angleInDeg(0) {
}

Mapping::Angle::Angle(Mapping::AngleType type, double value) {
    set(type, value);
}

void Mapping::Angle::set(Mapping::AngleType type, double value) {
    if (type == Mapping::AngleType::DEG) {
        if (value < 0) {
            value -= (int(value / 360) * 360);
            angleInDeg = 360 + value;
        } else {
            angleInDeg = value - int(value / 360) * 360;
        }
    } else if (type == Mapping::AngleType::RAD) {
        if (value < 0) {
            value -= (int(value / ((2 * pi))) * (2 * pi));
            value = 2 * pi + value;
            angleInDeg = value * (180 / pi);
        } else {
            angleInDeg = (value - int(value / (2 * pi)) * 2 * pi) * (180 / pi);
        }
    }
}

double Mapping::Angle::asDegree() const {
    return angleInDeg;
}

double Mapping::Angle::asRadian() const {
    return angleInDeg / (180 / pi);
}

Mapping::Angle &Mapping::Angle::operator+=(const Angle &other) {
    angleInDeg += other.angleInDeg;
    angleInDeg = angleInDeg - int(angleInDeg / 360) * 360;
    return *this;
}

Mapping::Angle Mapping::Angle::operator+(const Mapping::Angle &other) {
    return Mapping::Angle(AngleType::DEG, angleInDeg + other.angleInDeg);
}

Mapping::Angle &Mapping::Angle::operator-=(const Angle &other) {
    angleInDeg -= other.angleInDeg;
    angleInDeg = angleInDeg - int(angleInDeg / 360) * 360;
    return *this;
}

Mapping::Angle Mapping::Angle::operator-(const Mapping::Angle &other) {
    return Mapping::Angle(AngleType::DEG, angleInDeg - other.angleInDeg);
}
