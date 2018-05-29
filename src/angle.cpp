#include "angle.hpp"

const double Mapping::Angle::pi = 3.14159265358979323846;

Mapping::Angle::Angle() : angleInDeg(0) {
}

Mapping::Angle::Angle(Mapping::AngleType type, double value) {
    set(type, value);
}

void Mapping::Angle::set(Mapping::AngleType type, double value) {
    if (type == Mapping::AngleType::DEG) {
        angleInDeg = value - int(value / 360) * 360;
    } else if (type == Mapping::AngleType::RAD) {
        angleInDeg = (value - int(value / (2 * pi)) * 2 * pi) * (180 / pi);
    }
}

double Mapping::Angle::asDegree() {
    return angleInDeg;
}

double Mapping::Angle::asRadian() {
    return angleInDeg / (180 / pi);
}
