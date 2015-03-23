#include <cmath>

class Vector
{
public:
	Vector();
	Vector(float x, float y, float z);
	Vector(const Vector& source);
	~Vector();

	void SetValues(float x, float y, float z);
	void SetValues(const Vector& vector);
	void CrossProduct(const Vector& vector1, const Vector& vector2);
	void NormalizeVector();

	const float GetX() const;
	const float GetY() const;
	const float GetZ() const;
private:
	float* _values;
};