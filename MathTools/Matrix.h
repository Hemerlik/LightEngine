#include <stdio.h>
#include <iostream>
#include <cmath>
#include "Vector.h"

#ifndef MATH_PI

#define MATH_PI
#define M_PI	3.14159265358979323846

#endif

class Matrix
{
public:
	Matrix();
	Matrix(Matrix const& matrix);
	Matrix(float* values);

	~Matrix();

	void LoadIdentity();

	float const* GetValues() const;
	void SetValues(const float* values);

	Matrix operator*(Matrix const& matrix);
	Matrix& operator=(Matrix const& matrix);

	void Translate(float x, float y, float z);
	void Translate(const Vector& translation);
	void Scale(float x, float y, float z);
	void Scale(const Vector& scale);
	void Rotate(float angle, float x, float y, float z);
	void Rotate(float angle, const Vector& direction);

private:
	float m_values[16];
};