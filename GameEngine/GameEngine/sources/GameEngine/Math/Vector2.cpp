#include "Vector2.h"


void Vector2::Normalize(Vector2& A)
{
	double len = A.Length();
	A.x /= len;
	A.y /= len;
}

double Vector2::Angle(const Vector2& A, const Vector2& B)
{
	return acos(Vector2::Dot(A, B) / (A.Length() * B.Length())) * 180.0 / M_PI;
}

double Vector2::Dot(const Vector2& A, const Vector2& B)
{
	return A.x * B.x + A.y * B.y;
}

Vector2 Vector2::Lerp(const Vector2& A, const Vector2& B, float t)
{
	return Vector2(A.x + (B.x - A.x) * t, A.y + (B.y - A.y) * t);
}

void Vector2::Rotate(Vector2& A, float deg)
{
	double len = A.Length();
	double angle = Vector2::Angle(Vector2(0, 1), A);
	A.x = cos(angle + deg) * len;
	A.y = sin(angle + deg) * len;
}

Vector2 Vector2::Reflect(const Vector2& direction, const Vector2& normal)
{
	double dot = Vector2::Dot(direction, normal);
	return Vector2(direction.x - 2.0 * dot * normal.x, direction.y - 2.0 * dot * normal.y);
}


Vector2::Vector2()
	: x(0), y(0)
{
}

Vector2::Vector2(double p_x, double p_y)
	: x(p_x), y(p_y)
{
}

Vector2::Vector2(const Vector2& other)
	: x(other.x), y(other.y)
{
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator=(const Vector2& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

double Vector2::Length() const
{
	return sqrt(pow(x, 2.0) + pow(y, 2.0));
}

Vector2 Vector2::Normalized() const
{
	double len = Length();
	return Vector2(x / len, y / len);
}

void Vector2::Set(double p_x, double p_y)
{
	x = p_x;
	y = p_y;
}

int Vector2::operator[](int index)
{
	return (index) ? y : x;
}

bool Vector2::operator==(const Vector2& other)
{
	return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other)
{
	return x != other.x || y != other.y;
}

Vector2 Vector2::operator+(const Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}
Vector2 Vector2::operator-(const Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(const Vector2& other)
{
	return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::operator/(const Vector2& other)
{
	return Vector2(x / other.x, y / other.y);
}


void Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
}

void Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
}

void Vector2::operator*=(const Vector2& other)
{
	x *= other.x;
	y *= other.y;
}

void Vector2::operator/=(const Vector2& other)
{
	x /= other.x;
	y /= other.y;
}

Vector2 Vector2::operator*(double k)
{
	return Vector2(x * k, y * k);
}

Vector2 Vector2::operator/(double k)
{
	return Vector2(x / k, y / k);
}

void Vector2::operator*=(double k)
{
	x *= k;
	y *= k;
}

void Vector2::operator/=(double k)
{
	x /= k;
	y /= k;
}
