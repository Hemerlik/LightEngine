#include <cmath>
#include <iostream>
#include <Windows.h>

#ifndef MATH_PI
#define MATH_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef MATRIX
#define MATRIX
#include "../MathTools/Matrix.h"
#endif

class Camera
{
public:
	Camera();
	~Camera();

	const Matrix GetProjection() const;
	const float GetRatio() const;
	const float GetAngle() const;
	const float GetNear() const;
	const float GetFar() const;

	void SetPosition(const Vector& position);
	void SetUp(const Vector& up);
	void SetTarget(float targetX, float targetY, float targetZ);
	void SetTarget(const Vector& target);

	void SetAngle(float angle);
	void SetNear(float near);
	void SetFar(float far);
	void WindowSize_Changed(float width, float height);
	void ResetProjection();

private:
	void initProjection();
	void computeProjection();
	void computeLookAt();
	Vector _position;
	Vector _up;
	Vector _target;
	float _angle;
	float _near;
	float _far;
	float _ratio;
	Matrix _projection;
	Matrix _lookAt;
};
