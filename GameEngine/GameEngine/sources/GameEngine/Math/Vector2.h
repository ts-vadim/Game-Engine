#pragma once

#include "Core.h"
#define _USE_MATH_DEFINES
#include <math.h>


class ENGINE_API Vector2
{
public:
	double x;
	double y;

public:
	/// <summary>
	/// Makes vector have a length of 1.
	/// </summary>
	static void Normalize(Vector2& A);
	/// <returns>
	/// Angle between two vectors in degrees.
	/// </returns>
	static double Angle(const Vector2& A, const Vector2& B);
	/// <returns>
	/// Dot product of two vectors. (ax * bx + ay * by)
	/// </returns>
	static double Dot(const Vector2& A, const Vector2& B);
	/// <summary>
	/// Linear interpolation between two vectors.
	/// </summary>
	static Vector2 Lerp(const Vector2& A, const Vector2& B, float t);
	/// <summary>
	/// Rotates vector 
	/// </summary>
	static void Rotate(Vector2& A, float deg);
	/// <returns>
	/// Returns direction, reflected from normal.
	/// </returns>
	static Vector2 Reflect(const Vector2& direction, const Vector2& normal);


public:
	Vector2();
	Vector2(double p_x, double p_y);
	Vector2(const Vector2& other);
	~Vector2();
	Vector2& operator=(const Vector2& other);

	double Length() const;
	Vector2 Normalized() const;

	void Set(double x, double y);

	double operator[](int index);

	bool operator==(const Vector2& other);
	bool operator!=(const Vector2& other);

	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2 operator*(const Vector2& other);
	Vector2 operator/(const Vector2& other);

	void operator+=(const Vector2& other);
	void operator-=(const Vector2& other);
	void operator*=(const Vector2& other);
	void operator/=(const Vector2& other);

	Vector2 operator*(double k);
	Vector2 operator/(double k);
	void operator*=(double k);
	void operator/=(double k);
};



