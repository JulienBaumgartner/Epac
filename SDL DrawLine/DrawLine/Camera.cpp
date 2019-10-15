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
		r.x_, r.y_, r.z_, 0,
		u.x_, u.y_, u.z_, 0,
		f.x_, f.y_, f.z_, 0,
		position.x_, position.y_, position.z_, 1);

}

algebra::Matrix4<float> Camera::ViewInv() const
{
	algebra::Vec3<float> f = (target - position).normalize();
	algebra::Vec3<float> u = (up - (f*up)).normalize();
	algebra::Vec3<float> r = (f^u).normalize();

	return algebra::Matrix4<float>(
		r.x_, u.x_, f.x_, 0,
		r.y_, u.y_, f.y_, 0,
		r.z_, u.z_, f.z_, 0,
		-(position*r), -(position*u), -(position*f), 1);

}
