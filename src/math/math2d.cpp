#include <math/math2d.h>

Vector2i::Vector2i() {}
Vector2i::Vector2i(int a) : x(a), y(a) {}
Vector2i::Vector2i(int x, int y) : x(x), y(y) {}



Vector2i Vector2i::operator+(const Vector2i &other) const {
    return Vector2i(this->x + other.x, this->y + other.y);
}

Vector2i Vector2i::operator-(const Vector2i &other) const {
    return Vector2i(this->x - other.x, this->y - other.y);
}

Vector2i Vector2i::operator*(const Vector2i &other) const {
    return Vector2i(this->x * other.x, this->y * other.y);
}

Vector2i Vector2i::operator/(const Vector2i &other) const {
    return Vector2i(this->x / other.x, this->y / other.y);
}



Vector2i& Vector2i::operator+=(const Vector2i &other) {
    this->x += other.x;
    this->y += other.y;

    return *this;
}

Vector2i& Vector2i::operator-=(const Vector2i &other) {
    this->x -= other.x;
    this->y -= other.y;

    return *this;
}

Vector2i& Vector2i::operator*=(const Vector2i &other) {
    this->x *= other.x;
    this->y *= other.y;

    return *this;
}

Vector2i& Vector2i::operator/=(const Vector2i &other) {
    this->x /= other.x;
    this->y /= other.y;

    return *this;
}

Vector2f Vector2i::toVector2f() {
    return Vector2f((float) this->x, (float) this->y);
}

Vector2f::Vector2f() {}
Vector2f::Vector2f(float a) : x(a), y(a) {}
Vector2f::Vector2f(float x, float y) : x(x), y(y) {}



Vector2f Vector2f::operator+(const Vector2f &other) const {
    return Vector2f(this->x + other.x, this->y + other.y);
}

Vector2f Vector2f::operator-(const Vector2f &other) const {
    return Vector2f(this->x - other.x, this->y - other.y);
}

Vector2f Vector2f::operator*(const Vector2f &other) const {
    return Vector2f(this->x * other.x, this->y * other.y);
}

Vector2f Vector2f::operator/(const Vector2f &other) const {
    return Vector2f(this->x / other.x, this->y / other.y);
}



Vector2f& Vector2f::operator+=(const Vector2f &other) {
    this->x += other.x;
    this->y += other.y;

    return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f &other) {
    this->x -= other.x;
    this->y -= other.y;

    return *this;
}

Vector2f& Vector2f::operator*=(const Vector2f &other) {
    this->x *= other.x;
    this->y *= other.y;

    return *this;
}

Vector2f& Vector2f::operator/=(const Vector2f &other) {
    this->x /= other.x;
    this->y /= other.y;

    return *this;
}

Vector2i Vector2f::toVector2i() {
    return Vector2i((int) this->x, (int) this->y);
}