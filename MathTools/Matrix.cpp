#include "Matrix.h"

Matrix::Matrix()
{
	for(int i = 0; i < 16; i++)
		m_values[i] = 0.0;
}

Matrix::Matrix(float* values)
{
	for(int i = 0; i < 16; i++)
		m_values[i] = values[i];
}

Matrix::Matrix(Matrix const& matrix)
{
	for(int i = 0; i < 16; i++)
		m_values[i] = matrix.m_values[i];
}

Matrix::~Matrix()
{
}

void Matrix::LoadIdentity()
{
	for(int i = 0; i < 16; i++)
		m_values[i] = 0.0;

	m_values[0] = 1.0;
	m_values[5] = 1.0;
	m_values[10] = 1.0;
	m_values[15] = 1.0;
}

float const* Matrix::GetValues() const
{
	return (float* const)m_values;
}

void Matrix::SetValues(const float* values)
{
	for(int i = 0; i < 16; i++)
		m_values[i] = values[i];
}

Matrix Matrix::operator*(Matrix const& matrix)
{
	Matrix result;

	for(int k = 0; k < 4; k++)
	{
		for(int j = 0; j < 4; j++)
		{
			for(int i = 0; i < 4; i++)
				result.m_values[4*j+k] += m_values[4*j+i]*matrix.m_values[4*i+k];
		}
	}

	return result;
}

Matrix& Matrix::operator=(Matrix const& matrix)
{
	for(int i = 0; i < 16; i++)
		m_values[i] = matrix.m_values[i];

	return *this;
}

void Matrix::Translate(float x, float y, float z)
{
	Matrix translation;
	translation.LoadIdentity();

	translation.m_values[3] = x;
	translation.m_values[7] = y;
	translation.m_values[11] = z;

	*this = *this*translation;
}

void Matrix::Translate(const Vector& translation)
{
	Matrix translate;
	translate.LoadIdentity();

	translate.m_values[3] = translation.GetX();
	translate.m_values[7] = translation.GetY();
	translate.m_values[11] = translation.GetZ();

	*this = *this * translate;
}

void Matrix::Scale(float x, float y, float z)
{
	Matrix scale;

	scale.m_values[0] = x;
	scale.m_values[5] = y;
	scale.m_values[10] = z;
	scale.m_values[15] = 1.0;

	*this = *this * scale;
}

void Matrix::Scale(const Vector& vector)
{
	Matrix scale;

	scale.m_values[0] = vector.GetX();
	scale.m_values[5] = vector.GetY();
	scale.m_values[10] = vector.GetZ();
	scale.m_values[15] = 1.0;

	*this = *this * scale;
}

void Matrix::Rotate(float angle, float x, float y, float z)
{
	Matrix rotation;

	angle = (float)(angle * M_PI / 180);

	Vector axis(x, y, z);
	axis.NormalizeVector();

	float vx = axis.GetX();
	float vy = axis.GetY();
	float vz = axis.GetZ();

	rotation.m_values[0] = vx * vx * (1 - cos(angle)) + cos(angle);
	rotation.m_values[1] = vx * vy * (1 - cos(angle)) - vz * sin(angle);
	rotation.m_values[2] = vx * vz * (1 - cos(angle)) + vy * sin(angle);

	rotation.m_values[4] = vy * vx * (1 - cos(angle)) + vz * sin(angle);
	rotation.m_values[5] = vy * vy * (1 - cos(angle)) + cos(angle);
	rotation.m_values[6] = vy * vz * (1 - cos(angle)) - vx * sin(angle);

	rotation.m_values[8] = vz * vx * (1 - cos(angle)) - vy * sin(angle);
	rotation.m_values[9] = vz * vy * (1 - cos(angle)) + vx * sin(angle);
	rotation.m_values[10] = vz * vz * (1 - cos(angle)) + cos(angle);

	rotation.m_values[15] = 1.0;

	*this = *this * rotation;
}

void Matrix::Rotate(float angle, const Vector& vector)
{
	Vector direction(vector);

	Matrix rotation;

	angle = (float)(angle * M_PI / 180);

	direction.NormalizeVector();
	
	float x = direction.GetX();
	float y = direction.GetY();
	float z = direction.GetZ();

	rotation.m_values[0] = x * x * (1 - cos(angle)) + cos(angle);
	rotation.m_values[1] = x * y * (1 - cos(angle)) - z * sin(angle);
	rotation.m_values[2] = x * z * (1 - cos(angle)) + y * sin(angle);

	rotation.m_values[4] = y * x * (1 - cos(angle)) + z * sin(angle);
	rotation.m_values[5] = y * y * (1 - cos(angle)) + cos(angle);
	rotation.m_values[6] = y * z * (1 - cos(angle)) - x * sin(angle);

	rotation.m_values[8] = z * x * (1 - cos(angle)) - y * sin(angle);
	rotation.m_values[9] = z * y * (1 - cos(angle)) + x * sin(angle);
	rotation.m_values[10] = z * z * (1 - cos(angle)) + cos(angle);

	rotation.m_values[15] = 1.0;

	*this = *this * rotation;
}