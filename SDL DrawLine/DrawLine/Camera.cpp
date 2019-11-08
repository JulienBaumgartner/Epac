#include "Camera.h"



Camera::Camera() : position(0,0,0), up(0,1,0), target(1,0,0)
{
}


Camera::~Camera()
{
}

algebra::Matrix4<float> Camera::View() const
{
	algebra::Vec3<float> f = (target - position).normalize();
	algebra::Vec3<float> u = (up - (f*up)).normalize();
	algebra::Vec3<float> r = (f^u).normalize();

	return algebra::Matrix4<float>(
		r.x, r.y, r.z, 0,
		u.x, u.y, u.z, 0,
		f.x, f.y, f.z, 0,
		position.x, position.y, position.z, 1);

}

algebra::Matrix4<float> Camera::ViewInv() const
{
	algebra::Vec3<float> f = (target - position).normalize();
	algebra::Vec3<float> u = (up - (f*up)).normalize();
	algebra::Vec3<float> r = (f^u).normalize();

	return algebra::Matrix4<float>(
		r.x, u.x, f.x, 0,
		r.y, u.y, f.y, 0,
		r.z, u.z, f.z, 0,
		-(position*r), -(position*u), -(position*f), 1);

}
