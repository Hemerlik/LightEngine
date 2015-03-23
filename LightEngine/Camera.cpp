#include "Camera.h"

Camera::Camera()
{
	_projection.LoadIdentity();
	_lookAt.LoadIdentity();
}

Camera::~Camera()
{
}

const float Camera::GetAngle() const
{
	return (float)(_angle * 180 / M_PI);
}

const float Camera::GetFar() const
{
	return _far;
}

const float Camera::GetNear() const
{
	return _near;
}

const float Camera::GetRatio() const
{
	return _ratio;
}

const Matrix Camera::GetProjection() const
{
	return _projection;
}

void Camera::SetPosition(const Vector& position)
{
	_position.SetValues(position.GetX(), position.GetY(), position.GetZ());
	computeProjection();
}

void Camera::SetUp(const Vector& up)
{
	_up.SetValues(up);
	computeProjection();
}

void Camera::SetTarget(float targetX, float targetY, float targetZ)
{
	_target.SetValues(targetX, targetY, targetZ);
	computeProjection();
}

void Camera::SetTarget(const Vector& target)
{
	_target.SetValues(target);
	computeProjection();
}

void Camera::SetAngle(float angle)
{
	_angle = angle;
	computeProjection();
}

void Camera::SetNear(float newNear)
{
	_near = newNear;
	computeProjection();
}

void Camera::SetFar( float newFar)
{
	_far = newFar;
	computeProjection();
}

void Camera::WindowSize_Changed(float width, float height)
{
	_ratio = width / height;
	computeProjection();
}

void Camera::ResetProjection()
{
	computeProjection();
}

void Camera::computeProjection()
{
	_projection.LoadIdentity();

	float f = 1 / tan(_angle / 2);

	float* values = {0};

	values[0] = f / _ratio;
	values[5] = f;
	values[10] = (_near + _far) / (_near - _far);
	values[11] = (2 * _near * _far) / (_near - _far);
	values[14] = -1.0;

	_projection.SetValues(values);
}

void Camera::computeLookAt()
{
	float values[16] = {0};

	Vector look(_target.GetX() - _position.GetX(), _target.GetY() - _position.GetY(), _target.GetZ() - _position.GetZ());
	Vector norm;
	Vector newAxe;

	norm.CrossProduct(look, _up);
	newAxe.CrossProduct(norm, look);

	look.NormalizeVector();
	norm.NormalizeVector();
	newAxe.NormalizeVector();

	values[0] = norm.GetX();
	values[1] = norm.GetY();
	values[2] = norm.GetZ();
	
	values[4] = newAxe.GetX();
	values[5] = newAxe.GetY();
	values[6] = newAxe.GetZ();
	
	values[8] = -look.GetX();
	values[9] = -look.GetY();
	values[10] = -look.GetZ();
	
	values[15] = 1.0;

	_projection.SetValues(values);
}