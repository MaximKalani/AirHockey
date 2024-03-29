#include <Vector2D.hpp>

Vector2D::Vector2D()
{
    x = 0.0f;
    x = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
    

}


void Vector2D::Normalize()
{
    float sum = abs(this->x) + abs(this->y);
    this->x = this->x/sum;
    this->y = this->y/sum;
}

Vector2D& Vector2D::Add(const Vector2D& vec)
{
    this->x += vec.x;
    this->y += vec.y;
    
    return *this;
    
}

Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
    
    return *this;
    
}

Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
    this->x *= vec.x;
    this->y *= vec.y;
    
    return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec)
{
    this->x /= vec.x;
    this->y /= vec.y;
    
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D& vec)
{
    Vector2D result;
    result.x = this->x + vec.x;
    result.y = this->y + vec.y;
    return result;
}

Vector2D Vector2D::operator-(const Vector2D& vec)
{
    Vector2D result;
    result.x = this->x - vec.x;
    result.y = this->y - vec.y;
    return result;
}

Vector2D Vector2D::operator*(const Vector2D& vec)
{
    Vector2D result;
    result.x = this->x * vec.x;
    result.y = this->y * vec.y;
    return result;
}

Vector2D Vector2D::operator/(const Vector2D& vec)
{
    Vector2D result;
    result.x = this->x / vec.x;
    result.y = this->y / vec.y;
    return result;
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
    return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
    return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
    return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
    return this->Divide(vec);
}

Vector2D& Vector2D::operator*(const int& i)
{
    this->x *= i;
    this->y *= i;

    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
    stream << "(" << vec.x << "," << vec.y << ")";
    return stream;
}