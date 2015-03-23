#include"Vector.h"

Vector::Vector()
{
}

Vector::Vector(float x, float y, float z)
{
	_values[0] = x;
	_values[1] = y;
	_values[2] = z;
}

Vector::Vector(const Vector& source)
{
	_values[0] = source._values[0];
	_values[1] = source._values[1];
	_values[2] = source._values[2];
}

Vector::~Vector()
{
}

void Vector::SetValues(float x, float y, float z)
{
	_values[0] = x;
	_values[1] = y;
	_values[2] = z;
}

void Vector::SetValues(const Vector& vector)
{
	for(int i = 0; i < 3; i++)
		_values[i] = vector._values[i];
}

void Vector::CrossProduct(const Vector& vector1, const Vector& vector2)
{
	float x1 = vector1.GetX();
	float y1 = vector1.GetY();
	float z1 = vector1.GetZ();

	float x2 = vector2.GetX();
	float y2 = vector2.GetY();
	float z2 = vector2.GetZ();

	float x = y1 * z2 - y2 * z1;
	float y = z1 * x2 - x1 * z2;
	float z = x1 * y2 - y1 * x2;

	this->SetValues(x,y,z);
}

void Vector::NormalizeVector()
{
	float height = sqrt(_values[0] * _values[0] + _values[1] * _values[1] + _values[2] * _values[2]);

	if(height != 0.0)
	{
		_values[0] /= height;
		_values[1] /= height;
		_values[2] /= height;
	}
}

const float Vector::GetX() const
{
	return _values[0];
}

const float Vector::GetY() const
{
	return _values[1];
}

const float Vector::GetZ() const
{
	return _values[2];
}