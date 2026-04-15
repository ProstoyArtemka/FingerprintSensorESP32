#ifndef MATH_H
#define MATH_H

class Vector2f;

class Vector2i {

    public:
        int x;
        int y;
        
        Vector2i(int x, int y);
        Vector2i(int a);
        Vector2i();

        Vector2i operator+(const Vector2i &other) const;
        Vector2i operator-(const Vector2i &other) const;
        Vector2i operator*(const Vector2i &other) const;
        Vector2i operator/(const Vector2i &other) const;

        Vector2i& operator+=(const Vector2i &other);
        Vector2i& operator-=(const Vector2i &other);
        Vector2i& operator*=(const Vector2i &other);
        Vector2i& operator/=(const Vector2i &other);

        Vector2f toVector2f();
};

class Vector2f {

    public:
        float x;
        float y;
        
        Vector2f(float x, float y);
        Vector2f(float a);
        Vector2f();

        Vector2f operator+(const Vector2f &other) const;
        Vector2f operator-(const Vector2f &other) const;
        Vector2f operator*(const Vector2f &other) const;
        Vector2f operator/(const Vector2f &other) const;

        Vector2f& operator+=(const Vector2f &other);
        Vector2f& operator-=(const Vector2f &other);
        Vector2f& operator*=(const Vector2f &other);
        Vector2f& operator/=(const Vector2f &other);

        Vector2i toVector2i();
};

#endif