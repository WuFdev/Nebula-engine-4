#include "math.h"
#include "simd.h"
#include <float.h>
#include <random>


namespace Lumix
{


const Vec2 Vec2::MAX = Vec2(FLT_MAX);
const Vec2 Vec2::MIN = Vec2(-FLT_MAX);
const Vec2 Vec2::ZERO = Vec2(0);

const Vec3 Vec3::MAX = Vec3(FLT_MAX);
const Vec3 Vec3::MIN = Vec3(-FLT_MAX);
const Vec3 Vec3::ZERO = Vec3(0);

const Vec4 Vec4::MAX = Vec4(FLT_MAX);
const Vec4 Vec4::MIN = Vec4(-FLT_MAX);
const Vec4 Vec4::ZERO = Vec4(0);

const Transform Transform::IDENTITY = Transform({0, 0, 0}, {0, 0, 0, 1}, 1.f);

	
Vec2::Vec2(const IVec2& rhs)
	: x(float(rhs.x))
	, y(float(rhs.y)) {}

Vec2::Vec2(const DVec2& rhs)
	: x(float(rhs.x))
	, y(float(rhs.y)) {}

Vec2::Vec2(float a)
	: x(a)
	, y(a) {}

Vec2::Vec2(float a, float b)
	: x(a)
	, y(b) {}

float& Vec2::operator[](u32 i) {
	ASSERT(i >= 0 && i < 2);
	return (&x)[i];
}

float Vec2::operator[](u32 i) const {
	ASSERT(i >= 0 && i < 2);
	return (&x)[i];
}

bool Vec2::operator==(const Vec2& rhs) const {
	return x == rhs.x && y == rhs.y;
}

bool Vec2::operator!=(const Vec2& rhs) const {
	return x != rhs.x || y != rhs.y;
}

void Vec2::operator/=(float rhs) {
	*this *= 1.0f / rhs;
}

void Vec2::operator*=(float f) {
	x *= f;
	y *= f;
}

Vec4 operator*(float f, const Vec4& v) {
	return Vec4(f * v.x, f * v.y, f * v.z, f * v.w);
}

Vec4 operator*(const Vec4& v, float s) {
	return Vec4(v.x * s, v.y * s, v.z * s, v.w * s);
}

Vec3 operator*(float f, const Vec3& v) {
	return Vec3(f * v.x, f * v.y, f * v.z);
}

Vec2 Vec2::operator*(const Vec2& v) const {
	return Vec2(x * v.x, y * v.y);
}
Vec2 Vec2::operator/(const Vec2& v) const {
	return Vec2(x / v.x, y / v.y);
}
Vec2 Vec2::operator*(float f) const {
	return Vec2(x * f, y * f);
}
Vec2 Vec2::operator/(float f) const {
	return Vec2(x / f, y / f);
}
Vec2 Vec2::operator+(const Vec2& v) const {
	return Vec2(x + v.x, y + v.y);
}
void Vec2::operator+=(const Vec2& v) {
	x += v.x;
	y += v.y;
}
Vec2 Vec2::operator-(const Vec2& v) const {
	return Vec2(x - v.x, y - v.y);
}
Vec2 Vec2::operator-(float f) const {
	return Vec2(x - f, y - f);
}
Vec2 Vec2::operator-() const {
	return Vec2(-x, -y);
}

IVec2::IVec2(const Vec2& rhs)
	: x(int(rhs.x))
	, y(int(rhs.y))
{
}


Vec2 IVec2::operator/(const Vec2& rhs) { return {x / rhs.x, y / rhs.y}; }


IVec3::IVec3(const DVec3& rhs)
	: x(int(rhs.x))
	, y(int(rhs.y))
	, z(int(rhs.z))
{
}


IVec3::IVec3(const Vec3& rhs)
	: x(int(rhs.x))
	, y(int(rhs.y))
	, z(int(rhs.z))
{
}


DVec3 IVec3::operator *(double i) const
{
    return {i * x, i * y, i * z};
}

void lerp(const Vec4& op1, const Vec4& op2, Vec4* out, float t) {
	const float invt = 1.0f - t;
	out->x = op1.x * invt + op2.x * t;
	out->y = op1.y * invt + op2.y * t;
	out->z = op1.z * invt + op2.z * t;
	out->w = op1.w * invt + op2.w * t;
}

Vec3 Quat::rotate(const Vec3& v) const
{
	// nVidia SDK implementation

	Vec3 qvec(x, y, z);
	Vec3 uv = cross(qvec, v);
	Vec3 uuv = cross(qvec, uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;

	return v + uv + uuv;
}
	
DVec3 Quat::rotate(const DVec3& v) const
{
	// nVidia SDK implementation

	const DVec3 qvec(x, y, z);
	DVec3 uv = cross(qvec, v);
	DVec3 uuv = cross(qvec, uv);
	uv *= (2.0 * w);
	uuv *= 2.0;

	return v + uv + uuv;
}

float lerp(float a, float b, float t) {
	return a * (1 - t) + b * t;
}

Vec3 lerp(const Vec3& op1, const Vec3& op2, float t) {
	Vec3 res;
	const float invt = 1.0f - t;
	res.x = op1.x * invt + op2.x * t;
	res.y = op1.y * invt + op2.y * t;
	res.z = op1.z * invt + op2.z * t;
	return res;
}


DVec3 lerp(const DVec3& op1, const DVec3& op2, float t) {
	DVec3 res;
	const float invt = 1.0f - t;
	res.x = op1.x * invt + op2.x * t;
	res.y = op1.y * invt + op2.y * t;
	res.z = op1.z * invt + op2.z * t;
	return res;
}


Vec2 lerp(const Vec2& op1, const Vec2& op2, float t) {
	Vec2 res;
	const float invt = 1.0f - t;
	res.x = op1.x * invt + op2.x * t;
	res.y = op1.y * invt + op2.y * t;
	return res;
}


Vec4::Vec4(float a)
	: x(a)
	, y(a)
	, z(a)
	, w(a)
{
}

Vec4::Vec4(float a, float b, float c, float d)
	: x(a)
	, y(b)
	, z(c)
	, w(d)
{
}

Vec4::Vec4(const Vec2& v1, const Vec2& v2)
	: x(v1.x)
	, y(v1.y)
	, z(v2.x)
	, w(v2.y)
{
}

Vec4::Vec4(const Vec3& v, float d)
	: x(v.x)
	, y(v.y)
	, z(v.z)
	, w(d)
{
}

Vec2 Vec4::xz() const { return Vec2(x, z); }
Vec2 Vec4::xy() const { return Vec2(x, y); }
Vec3 Vec4::xyz() const { return Vec3(x, y, z); }
Vec2 Vec4::yz() const { return Vec2(y, z); }
Vec3 Vec4::rgb() const { return Vec3(x, y, z); }

float& Vec4::operator[](u32 i) {
	ASSERT(i >= 0 && i < 4);
	return (&x)[i];
}

float Vec4::operator[](u32 i) const {
	ASSERT(i >= 0 && i < 4);
	return (&x)[i];
}

bool Vec4::operator==(const Vec4& rhs) const {
	return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}

bool Vec4::operator!=(const Vec4& rhs) const {
	return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
}

Vec4 Vec4::operator+(const Vec4& rhs) const {
	return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Vec4 Vec4::operator-() const {
	return Vec4(-x, -y, -z, -w);
}

Vec4 Vec4::operator-(const Vec4& rhs) const {
	return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

void Vec4::operator+=(const Vec4& rhs)
{
	float x = this->x;
	float y = this->y;
	float z = this->z;
	float w = this->w;
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Vec4::operator-=(const Vec4& rhs)
{
	float x = this->x;
	float y = this->y;
	float z = this->z;
	float w = this->w;
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Vec4::operator/=(float rhs)
{
	*this *= 1.0f / rhs;
}

Vec4 Vec4::operator*(float s) { return Vec4(x * s, y * s, z * s, w * s); }

void Vec4::operator*=(float rhs)
{
	float x = this->x;
	float y = this->y;
	float z = this->z;
	float w = this->w;
	x *= rhs;
	y *= rhs;
	z *= rhs;
	w *= rhs;
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vec2 normalize(const Vec2& value) {
	float x = value.x;
	float y = value.y;
	const float inv_len = 1 / sqrt(x * x + y * y);
	x *= inv_len;
	y *= inv_len;
	return Vec2(x, y);
}


Vec3 normalize(const Vec3& value) {
	float x = value.x;
	float y = value.y;
	float z = value.z;
	const float inv_len = 1 / sqrt(x * x + y * y + z * z);
	x *= inv_len;
	y *= inv_len;
	z *= inv_len;
	return Vec3(x, y, z);
}

Quat normalize(const Quat& value) {
	float x = value.x;
	float y = value.y;
	float z = value.z;
	float w = value.w;
	const float inv_len = 1 / sqrt(x * x + y * y + z * z + w * w);
	x *= inv_len;
	y *= inv_len;
	z *= inv_len;
	w *= inv_len;
	return Quat(x, y, z, w);
}

float length(const Vec2& value) { return sqrt(value.x * value.x + value.y * value.y); }
float length(const Vec3& value) { return sqrt(value.x * value.x + value.y * value.y + value.z * value.z); }
double length(const DVec3& value) { return sqrt(value.x * value.x + value.y * value.y + value.z * value.z); }
float squaredLength(const Vec2& value) { return value.x * value.x + value.y * value.y; }
float squaredLength(const Vec3& value) { return value.x * value.x + value.y * value.y + value.z * value.z; }
double squaredLength(const DVec2& value) { return value.x * value.x + value.y * value.y; }
double squaredLength(const DVec3& value) { return value.x * value.x + value.y * value.y + value.z * value.z; }


Vec3::Vec3(const Vec2& v, float c)
	: x(v.x)
	, y(v.y)
	, z(c) {}

Vec3::Vec3(float a)
	: x(a)
	, y(a)
	, z(a) {}

Vec3::Vec3(float a, float b, float c)
	: x(a)
	, y(b)
	, z(c) {}

float& Vec3::operator[](u32 i) {
	ASSERT(i >= 0 && i < 3);
	return (&x)[i];
}

float Vec3::operator[](u32 i) const {
	ASSERT(i >= 0 && i < 3);
	return (&x)[i];
}

bool Vec3::operator==(const Vec3& rhs) const {
	return x == rhs.x && y == rhs.y && z == rhs.z;
}

bool Vec3::operator!=(const Vec3& rhs) const {
	return x != rhs.x || y != rhs.y || z != rhs.z;
}

Vec3 Vec3::operator+(const Vec3& rhs) const {
	return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vec3 Vec3::operator-() const {
	return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator-(const Vec3& rhs) const {
	return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vec3 Vec3::operator*(float s) const {
	return Vec3(x * s, y * s, z * s);
}
Vec3 Vec3::operator*(const Vec3& rhs) const {
	return Vec3(x * rhs.x, y * rhs.y, z * rhs.z);
}
Vec3 Vec3::operator*(const IVec3& rhs) const {
	return Vec3(x * rhs.x, y * rhs.y, z * rhs.z);
}
Vec3 Vec3::operator/(const IVec3& rhs) const {
	return Vec3(x / rhs.x, y / rhs.y, z / rhs.z);
}

Vec3 Vec3::operator/(float s) const {
	float tmp = 1 / s;
	return Vec3(x * tmp, y * tmp, z * tmp);
}

void Vec3::operator/=(float rhs) {
	*this *= 1.0f / rhs;
}

Vec2 Vec3::xz() const {
	return {x, z};
}

DVec3::DVec3(float a) : x(a), y(a), z(a) {}

DVec3::DVec3(double x, double y, double z) : x(x), y(y), z(z) {}

DVec3::DVec3(const Vec3& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}

DVec3 DVec3::operator-() const { return {-x, -y, -z}; }

DVec3 DVec3::operator*(float rhs) const { return {x * rhs, y * rhs, z * rhs}; }

DVec3 DVec3::operator/(float rhs) const { return {x / rhs, y / rhs, z / rhs}; }

DVec3 DVec3::operator/(const DVec3& rhs) const { return {x / rhs.x, y / rhs.y, z / rhs.z}; }

DVec3 DVec3::operator-(const DVec3& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z }; }

DVec3 DVec3::operator+(const DVec3& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z }; }

DVec3 DVec3::operator-(const Vec3& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z }; }

DVec3 DVec3::operator+(const Vec3& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z }; }

void DVec3::operator*=(const double& rhs) { x *= rhs; y *= rhs; z *= rhs; }

void DVec3::operator/=(const double& rhs) { x /= rhs; y /= rhs; z /= rhs; }

void DVec3::operator+=(const DVec3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; }

void DVec3::operator+=(const Vec3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; }

void DVec3::operator-=(const Vec3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; }

DVec2 DVec3::xz() const { return DVec2(x, z); }

Vec3::Vec3(const DVec3& rhs)
	: x((float)rhs.x)
	, y((float)rhs.y)
	, z((float)rhs.z)
{}

void Vec3::operator*=(float rhs) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
}

void Vec3::operator+=(const Vec3& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
}

void Vec3::operator-=(const Vec3& rhs) {
	float x = this->x;
	float y = this->y;
	float z = this->z;
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	this->x = x;
	this->y = y;
	this->z = z;
}

const Quat Quat::IDENTITY = { 0, 0, 0, 1 };


Quat::Quat(const Vec3& axis, float angle)
{
	float half_angle = angle * 0.5f;
	float s = sinf(half_angle);
	w = cosf(half_angle);
	x = axis.x * s;
	y = axis.y * s;
	z = axis.z * s;
}


Quat Quat::vec3ToVec3(const Vec3& v0, const Vec3& v1)
{
	const Vec3 from = normalize(v0);
	const Vec3 to = normalize(v1);
	
	float cos_angle = dot(from, to);
    Vec3 half;
	
    if(cos_angle > -1.0005f && cos_angle < -0.9995f) {
		Vec3 n = Vec3(0, from.z, -from.y);
		if (squaredLength(n) < 0.01) {
			n = Vec3(from.y, -from.x, 0);
		}
		n = normalize(n);
		return Quat(n, PI);
    }
    else
        half = normalize(from + to);

    // http://physicsforgames.blogspot.sk/2010/03/quaternion-tricks.html
    return Quat(
        from.y * half.z - from.z * half.y,
        from.z * half.x - from.x * half.z,
        from.x * half.y - from.y * half.x,
		dot(from, half));
}


void Quat::fromEuler(const Vec3& euler)
{
	ASSERT(euler.x >= -HALF_PI && euler.x <= HALF_PI);
	float ex = euler.x * 0.5f;
	float ey = euler.y * 0.5f;
	float ez = euler.z * 0.5f;
	float sinX = sinf(ex);
	float cosX = cosf(ex);
	float sinY = sinf(ey);
	float cosY = cosf(ey);
	float sinZ = sinf(ez);
	float cosZ = cosf(ez);

	w = cosY * cosX * cosZ + sinY * sinX * sinZ;
	x = cosY * sinX * cosZ + sinY * cosX * sinZ;
	y = sinY * cosX * cosZ - cosY * sinX * sinZ;
	z = cosY * cosX * sinZ - sinY * sinX * cosZ;
}


Vec3 Quat::toEuler() const
{
	// from urho3d
	float check = 2.0f * (w * x - y * z);

	if (check < -0.999999f) {
		return Vec3(-PI * 0.5f, 0.0f, -atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)));
	}

	if (check > 0.999999f) {
		return Vec3(PI * 0.5f, 0.0f, atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)));
	}

	return Vec3(asinf(check),
		atan2f(2.0f * (x * z + w * y), 1.0f - 2.0f * (x * x + y * y)),
		atan2f(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z)));
}


void Quat::conjugate()
{
	w = -w;
}


Quat Quat::conjugated() const
{
	return Quat(x, y, z, -w);
}

Vec3 slerp(const Vec3& a, const Vec3& b, float t) {
     float d = dot(a, b);
     d = clamp(d, -1.f, 1.f);
     const float s = acosf(d) * t;
     const Vec3 r = normalize(b - a * d);
     return a * cosf(s) + r * sinf(s);
}

Quat nlerp(const Quat& q1, const Quat& q2, float t)
{
	Quat res;
	float inv = 1.0f - t;
	if (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w < 0) t = -t;
	float ox = q1.x * inv + q2.x * t;
	float oy = q1.y * inv + q2.y * t;
	float oz = q1.z * inv + q2.z * t;
	float ow = q1.w * inv + q2.w * t;
	float l = 1 / sqrt(ox * ox + oy * oy + oz * oz + ow * ow);
	ox *= l;
	oy *= l;
	oz *= l;
	ow *= l;
	res.x = ox;
	res.y = oy;
	res.z = oz;
	res.w = ow;
	return res;
}


Quat Quat::operator*(const Quat& rhs) const
{
	return Quat(w * rhs.x + rhs.w * x + y * rhs.z - rhs.y * z,
		w * rhs.y + rhs.w * y + z * rhs.x - rhs.z * x,
		w * rhs.z + rhs.w * z + x * rhs.y - rhs.x * y,
		w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z);
}


Quat Quat::operator-() const
{
	return Quat(x, y, z, -w);
}


Quat Quat::operator+(const Quat& q) const
{
	return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
}


Quat Quat::operator*(float m) const
{
	return Quat(x * m, y * m, z * m, w * m);
}


Vec3 Quat::operator*(const Vec3& q) const
{
	return rotate(q);
}


Matrix Quat::toMatrix() const
{
	float fx = x + x;
	float fy = y + y;
	float fz = z + z;
	float fwx = fx*w;
	float fwy = fy*w;
	float fwz = fz*w;
	float fxx = fx*x;
	float fxy = fy*x;
	float fxz = fz*x;
	float fyy = fy*y;
	float fyz = fz*y;
	float fzz = fz*z;

	Matrix mtx;
	mtx.columns[0].x = 1.0f - (fyy + fzz);
	mtx.columns[1].x = fxy - fwz;
	mtx.columns[2].x = fxz + fwy;
	mtx.columns[0].y = fxy + fwz;
	mtx.columns[1].y = 1.0f - (fxx + fzz);
	mtx.columns[2].y = fyz - fwx;
	mtx.columns[0].z = fxz - fwy;
	mtx.columns[1].z = fyz + fwx;
	mtx.columns[2].z = 1.0f - (fxx + fyy);

	mtx.columns[3].x = mtx.columns[3].y = mtx.columns[3].z = mtx.columns[0].w = mtx.columns[1].w = mtx.columns[2].w = 0;
	mtx.columns[3].w = 1;
	return mtx;
}

Transform::Transform(const DVec3& _pos, const Quat& _rot, float _scale)
	: pos(_pos)
	, rot(_rot)
	, scale(_scale) {}

Transform Transform::operator*(const Transform& rhs) const { return {rot.rotate(rhs.pos * scale) + pos, rot * rhs.rot, scale * rhs.scale}; }

Transform Transform::operator*(const LocalRigidTransform& rhs) const { return {pos + rot.rotate(rhs.pos * scale), rot * rhs.rot, scale}; }

DVec3 Transform::transform(const Vec3& value) const { return pos + rot.rotate(value) * scale; }

DVec3 Transform::transform(const DVec3& value) const { return pos + rot.rotate(value) * scale; }

RigidTransform Transform::getRigidPart() const { return {pos, rot}; }

Transform Transform::inverted() const {
	Transform result;
	result.rot = rot.conjugated();
	result.pos = result.rot.rotate(-pos / scale);
	result.scale = 1.0f / scale;
	return result;
}

LocalRigidTransform LocalRigidTransform::inverted() const {
	LocalRigidTransform result;
	result.rot = rot.conjugated();
	result.pos = result.rot.rotate(-pos);
	return result;
}

Matrix LocalRigidTransform::toMatrix() const {
	return Matrix(pos, rot);
}

LocalRigidTransform LocalRigidTransform::operator*(const LocalRigidTransform& rhs) const {
	return {rot.rotate(rhs.pos) + pos, rot * rhs.rot};
}

LocalRigidTransform LocalRigidTransform::interpolate(const LocalRigidTransform& rhs, float t) const {
	LocalRigidTransform ret;
	ret.pos = lerp(pos, rhs.pos, t);
	ret.rot = nlerp(rot, rhs.rot, t);
	return ret;
}

RigidTransform RigidTransform::inverted() const {
	RigidTransform result;
	result.rot = rot.conjugated();
	result.pos = result.rot.rotate(-pos);
	return result;
}

RigidTransform::RigidTransform(const DVec3& pos, const Quat& rot)
	: pos(pos)
	, rot(rot) {}

RigidTransform RigidTransform::operator*(const RigidTransform& rhs) const { return {rot.rotate(rhs.pos) + pos, rot * rhs.rot}; }

RigidTransform RigidTransform::operator*(const LocalRigidTransform& rhs) const { return {DVec3(rot.rotate(rhs.pos)) + pos, rot * rhs.rot}; }

const Matrix Matrix::IDENTITY(Vec4(1, 0, 0, 0), Vec4(0, 1, 0, 0), Vec4(0, 0, 1, 0), Vec4(0, 0, 0, 1));

Matrix::Matrix(const Vec3& pos, const Quat& rot) {
	*this = rot.toMatrix();
	setTranslation(pos);
}

void Matrix::lookAt(const Vec3& eye, const Vec3& at, const Vec3& up) {
	*this = Matrix::IDENTITY;
	Vec3 f = normalize((eye - at));
	Vec3 r = normalize(cross(up, f));
	Vec3 u = cross(f, r);
	setXVector(r);
	setYVector(u);
	setZVector(f);
	transpose();
	setTranslation(Vec3(-dot(r, eye), -dot(u, eye), -dot(f, eye)));
}

void Matrix::fromEuler(float yaw, float pitch, float roll) {
	float sroll = sinf(roll);
	float croll = cosf(roll);
	float spitch = sinf(pitch);
	float cpitch = cosf(pitch);
	float syaw = sinf(yaw);
	float cyaw = cosf(yaw);

	columns[0].x = sroll * spitch * syaw + croll * cyaw;
	columns[0].y = sroll * cpitch;
	columns[0].z = sroll * spitch * cyaw - croll * syaw;
	columns[0].w = 0.0f;
	columns[1].x = croll * spitch * syaw - sroll * cyaw;
	columns[1].y = croll * cpitch;
	columns[1].z = croll * spitch * cyaw + sroll * syaw;
	columns[1].w = 0.0f;
	columns[2].x = cpitch * syaw;
	columns[2].y = -spitch;
	columns[2].z = cpitch * cyaw;
	columns[2].w = 0.0f;
	columns[3].x = 0.0f;
	columns[3].y = 0.0f;
	columns[3].z = 0.0f;
	columns[3].w = 1.0f;
}

Matrix Matrix::rotationX(float angle) {
	Matrix m = IDENTITY;
	float c = cosf(angle);
	float s = sinf(angle);

	m.columns[1].y = m.columns[2].z = c;
	m.columns[2].y = -s;
	m.columns[1].z = s;

	return m;
}

Matrix Matrix::rotationY(float angle) {
	Matrix m = IDENTITY;
	float c = cosf(angle);
	float s = sinf(angle);

	m.columns[0].x = m.columns[2].z = c;
	m.columns[2].x = s;
	m.columns[0].z = -s;

	return m;
}

Matrix Matrix::rotationZ(float angle) {
	Matrix m = IDENTITY;
	float c = cosf(angle);
	float s = sinf(angle);

	m.columns[0].x = m.columns[1].y = c;
	m.columns[1].x = -s;
	m.columns[0].y = s;

	return m;
}

void Matrix::setOrtho(float left, float right, float bottom, float top, float z_near, float z_far, bool reversed_z) {
	*this = IDENTITY;
	columns[0].x = 2 / (right - left);
	columns[1].y = 2 / (top - bottom);
	columns[3].x = (right + left) / (left - right);
	columns[3].y = (top + bottom) / (bottom - top);
	if (reversed_z) {
		columns[2].z = 1 / (z_far - z_near);
		columns[3].z = z_far / (z_far - z_near);
	} else {
		columns[2].z = -1 / (z_far - z_near);
		columns[3].z = z_near / (z_near - z_far);
	}
}

void Matrix::setPerspective(float fov, float ratio, float near_plane, float far_plane, bool reversed_z) {
	*this = Matrix::IDENTITY;
	float f = 1 / tanf(fov * 0.5f);
	float z_diff = near_plane - far_plane;
	columns[0].x = f / ratio;
	columns[1].y = f;
	columns[3].w = 0;
	columns[2].w = -1.0f;

	if (reversed_z) {
		columns[2].z = 0;
		columns[3].z = near_plane;
	} else {
		columns[2].z = -1;
		columns[3].z = -near_plane;
	}
}

void Matrix::decompose(Vec3& position, Quat& rotation, float& scale) const {
	position = getTranslation();
	scale = length(getXVector());
	Matrix tmp = *this;
	tmp.multiply3x3(1 / scale);
	rotation = tmp.getRotation();
}

Matrix Matrix::operator*(float rhs) const {
	Matrix out;
	out.columns[0].x = columns[0].x * rhs;
	out.columns[0].y = columns[0].y * rhs;
	out.columns[0].z = columns[0].z * rhs;
	out.columns[0].w = columns[0].w * rhs;

	out.columns[1].x = columns[1].x * rhs;
	out.columns[1].y = columns[1].y * rhs;
	out.columns[1].z = columns[1].z * rhs;
	out.columns[1].w = columns[1].w * rhs;

	out.columns[2].x = columns[2].x * rhs;
	out.columns[2].y = columns[2].y * rhs;
	out.columns[2].z = columns[2].z * rhs;
	out.columns[2].w = columns[2].w * rhs;

	out.columns[3].x = columns[3].x * rhs;
	out.columns[3].y = columns[3].y * rhs;
	out.columns[3].z = columns[3].z * rhs;
	out.columns[3].w = columns[3].w * rhs;

	return out;
}

Matrix Matrix::operator+(const Matrix& rhs) const {
	Matrix out;

	out.columns[0].x = columns[0].x + rhs.columns[0].x;
	out.columns[0].y = columns[0].y + rhs.columns[0].y;
	out.columns[0].z = columns[0].z + rhs.columns[0].z;
	out.columns[0].w = columns[0].w + rhs.columns[0].w;

	out.columns[1].x = columns[1].x + rhs.columns[1].x;
	out.columns[1].y = columns[1].y + rhs.columns[1].y;
	out.columns[1].z = columns[1].z + rhs.columns[1].z;
	out.columns[1].w = columns[1].w + rhs.columns[1].w;

	out.columns[2].x = columns[2].x + rhs.columns[2].x;
	out.columns[2].y = columns[2].y + rhs.columns[2].y;
	out.columns[2].z = columns[2].z + rhs.columns[2].z;
	out.columns[2].w = columns[2].w + rhs.columns[2].w;

	out.columns[3].x = columns[3].x + rhs.columns[3].x;
	out.columns[3].y = columns[3].y + rhs.columns[3].y;
	out.columns[3].z = columns[3].z + rhs.columns[3].z;
	out.columns[3].w = columns[3].w + rhs.columns[3].w;

	return out;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
	Matrix out;

	const float4 a = f4Load(&columns[0].x);
	const float4 b = f4Load(&columns[1].x);
	const float4 c = f4Load(&columns[2].x);
	const float4 d = f4Load(&columns[3].x);

	float4 t1 = f4Splat(rhs.columns[0].x);
	float4 t2 = f4Mul(a, t1);
	t1 = f4Splat(rhs.columns[0].y);
	t2 = f4Add(f4Mul(b, t1), t2);
	t1 = f4Splat(rhs.columns[0].z);
	t2 = f4Add(f4Mul(c, t1), t2);
	t1 = f4Splat(rhs.columns[0].w);
	t2 = f4Add(f4Mul(d, t1), t2);

	f4Store(&out.columns[0].x, t2);

	t1 = f4Splat(rhs.columns[1].x);
	t2 = f4Mul(a, t1);
	t1 = f4Splat(rhs.columns[1].y);
	t2 = f4Add(f4Mul(b, t1), t2);
	t1 = f4Splat(rhs.columns[1].z);
	t2 = f4Add(f4Mul(c, t1), t2);
	t1 = f4Splat(rhs.columns[1].w);
	t2 = f4Add(f4Mul(d, t1), t2);

	f4Store(&out.columns[1].x, t2);

	t1 = f4Splat(rhs.columns[2].x);
	t2 = f4Mul(a, t1);
	t1 = f4Splat(rhs.columns[2].y);
	t2 = f4Add(f4Mul(b, t1), t2);
	t1 = f4Splat(rhs.columns[2].z);
	t2 = f4Add(f4Mul(c, t1), t2);
	t1 = f4Splat(rhs.columns[2].w);
	t2 = f4Add(f4Mul(d, t1), t2);

	f4Store(&out.columns[2].x, t2);

	t1 = f4Splat(rhs.columns[3].x);
	t2 = f4Mul(a, t1);
	t1 = f4Splat(rhs.columns[3].y);
	t2 = f4Add(f4Mul(b, t1), t2);
	t1 = f4Splat(rhs.columns[3].z);
	t2 = f4Add(f4Mul(c, t1), t2);
	t1 = f4Splat(rhs.columns[3].w);
	t2 = f4Add(f4Mul(d, t1), t2);

	f4Store(&out.columns[3].x, t2);

	return out;
}

void Matrix::normalizeScale() {
	Vec3 scale = {1 / length(Vec3(columns[0].x, columns[1].x, columns[2].x)), 1 / length(Vec3(columns[0].y, columns[1].y, columns[2].y)), 1 / length(Vec3(columns[0].z, columns[1].z, columns[2].z))};

	columns[0].x *= scale.x;
	columns[1].x *= scale.x;
	columns[2].x *= scale.x;

	columns[0].y *= scale.y;
	columns[1].y *= scale.y;
	columns[2].y *= scale.y;

	columns[0].z *= scale.z;
	columns[1].z *= scale.z;
	columns[2].z *= scale.z;
}

Quat Matrix::getRotation() const {
	Quat rot;
	float tr = columns[0].x + columns[1].y + columns[2].z;

	if (tr > 0) {
		float t = tr + 1.0f;
		float s = 1 / sqrt(t) * 0.5f;

		rot.w = s * t;
		rot.z = (columns[0].y - columns[1].x) * s;
		rot.y = (columns[2].x - columns[0].z) * s;
		rot.x = (columns[1].z - columns[2].y) * s;
	} else if ((columns[0].x > columns[1].y) && (columns[0].x > columns[2].z)) {
		float t = 1.0f + columns[0].x - columns[1].y - columns[2].z;
		float s = 1 / sqrt(t) * 0.5f;
		rot.x = s * t;
		rot.y = (columns[0].y + columns[1].x) * s;
		rot.z = (columns[0].z + columns[2].x) * s;
		rot.w = (columns[1].z - columns[2].y) * s;
	} else if (columns[1].y > columns[2].z) {
		float t = 1.0f + columns[1].y - columns[0].x - columns[2].z;
		float s = 1 / sqrt(t) * 0.5f;
		rot.w = (columns[2].x - columns[0].z) * s;
		rot.x = (columns[0].y + columns[1].x) * s;
		rot.y = s * t;
		rot.z = (columns[1].z + columns[2].y) * s;
	} else {
		float t = 1.0f + columns[2].z - columns[0].x - columns[1].y;
		float s = 1 / sqrt(t) * 0.5f;
		rot.w = (columns[0].y - columns[1].x) * s;
		rot.x = (columns[2].x + columns[0].z) * s;
		rot.y = (columns[2].y + columns[1].z) * s;
		rot.z = s * t;
	}
	return rot;
}

void Matrix::transpose() {
	float tmp = columns[1].x;
	columns[1].x = columns[0].y;
	columns[0].y = tmp;

	tmp = columns[2].y;
	columns[2].y = columns[1].z;
	columns[1].z = tmp;

	tmp = columns[2].x;
	columns[2].x = columns[0].z;
	columns[0].z = tmp;

	tmp = columns[3].x;
	columns[3].x = columns[0].w;
	columns[0].w = tmp;

	tmp = columns[3].y;
	columns[3].y = columns[1].w;
	columns[1].w = tmp;

	tmp = columns[3].z;
	columns[3].z = columns[2].w;
	columns[2].w = tmp;
}

void Matrix::multiply3x3(float scale) {
	columns[0].x *= scale;
	columns[0].y *= scale;
	columns[0].z *= scale;
	columns[1].x *= scale;
	columns[1].y *= scale;
	columns[1].z *= scale;
	columns[2].x *= scale;
	columns[2].y *= scale;
	columns[2].z *= scale;
}

Vec3 Matrix::transformPoint(const Vec3& rhs) const {
	return Vec3(columns[0].x * rhs.x + columns[1].x * rhs.y + columns[2].x * rhs.z + columns[3].x,
		columns[0].y * rhs.x + columns[1].y * rhs.y + columns[2].y * rhs.z + columns[3].y,
		columns[0].z * rhs.x + columns[1].z * rhs.y + columns[2].z * rhs.z + columns[3].z);
}

Vec3 Matrix::transformVector(const Vec3& rhs) const {
	return Vec3(columns[0].x * rhs.x + columns[1].x * rhs.y + columns[2].x * rhs.z,
		columns[0].y * rhs.x + columns[1].y * rhs.y + columns[2].y * rhs.z,
		columns[0].z * rhs.x + columns[1].z * rhs.y + columns[2].z * rhs.z);
}

void Matrix::setIdentity() {
	columns[0].x = 1;
	columns[0].y = 0;
	columns[0].z = 0;
	columns[0].w = 0;
	columns[1].x = 0;
	columns[1].y = 1;
	columns[1].z = 0;
	columns[1].w = 0;
	columns[2].x = 0;
	columns[2].y = 0;
	columns[2].z = 1;
	columns[2].w = 0;
	columns[3].x = 0;
	columns[3].y = 0;
	columns[3].z = 0;
	columns[3].w = 1;
}

float dot(const Vec4& op1, const Vec4& op2) {
	return op1.x * op2.x + op1.y * op2.y + op1.z * op2.z + op1.w * op2.w;
}

float dot(const Vec3& op1, const Vec3& op2) {
	return op1.x * op2.x + op1.y * op2.y + op1.z * op2.z;
}

float dot(const Vec2& op1, const Vec2& op2) {
	return op1.x * op2.x + op1.y * op2.y;
}

Vec3 cross(const Vec3& op1, const Vec3& op2) {
	return Vec3(op1.y * op2.z - op1.z * op2.y, op1.z * op2.x - op1.x * op2.z, op1.x * op2.y - op1.y * op2.x);
}

DVec3 cross(const DVec3& op1, const DVec3& op2) {
	return DVec3(op1.y * op2.z - op1.z * op2.y, op1.z * op2.x - op1.x * op2.z, op1.x * op2.y - op1.y * op2.x);
}

float easeInOut(float t) {
	float scaled_t = t * 2;
	if (scaled_t < 1) {
		return 0.5f * scaled_t * scaled_t;
	}
	--scaled_t;
	return -0.5f * (scaled_t * (scaled_t - 2) - 1);
}

float degreesToRadians(float angle) {
	return angle * PI / 180.0f;
}

double degreesToRadians(double angle) {
	return angle * PI / 180.0;
}

float degreesToRadians(int angle) {
	return angle * PI / 180.0f;
}

float radiansToDegrees(float angle) {
	return angle / PI * 180.0f;
}

Vec2 degreesToRadians(const Vec2& v) {
	return Vec2(degreesToRadians(v.x), degreesToRadians(v.y));
}

Vec2 radiansToDegrees(const Vec2& v) {
	return Vec2(radiansToDegrees(v.x), radiansToDegrees(v.y));
}

Vec3 degreesToRadians(const Vec3& v) {
	return Vec3(degreesToRadians(v.x), degreesToRadians(v.y), degreesToRadians(v.z));
}

Vec3 radiansToDegrees(const Vec3& v) {
	return Vec3(radiansToDegrees(v.x), radiansToDegrees(v.y), radiansToDegrees(v.z));
}

float angleDiff(float a, float b) {
	float delta = a - b;
	delta = fmodf(delta, PI * 2);
	if (delta > PI) return -PI * 2 + delta;
	if (delta < -PI) return PI * 2 + delta;
	return delta;
}

bool getRayPlaneIntersecion(const Vec3& origin,
	const Vec3& dir,
	const Vec3& plane_point,
	const Vec3& normal,
	float& out)
{
	float d = dot(dir, normal);
	if (d == 0)
	{
		return false;
	}
	d = dot(plane_point - origin, normal) / d;
	out = d;
	return true;
}

bool getRaySphereIntersection(const Vec3& origin,
	const Vec3& dir,
	const Vec3& center,
	float radius,
	Ref<float> out)
{
	ASSERT(length(dir) < 1.01f && length(dir) > 0.99f);
	Vec3 L = center - origin;
	float tca = dot(L, dir);
	float d2 = dot(L, L) - tca * tca;
	if (d2 > radius * radius) return false;
	float thc = sqrt(radius * radius - d2);
	float t = tca - thc;
	out = t >= 0 ? t : tca + thc;
	return true;
}

bool getRayAABBIntersection(const Vec3& origin,
	const Vec3& dir,
	const Vec3& min,
	const Vec3& size,
	Vec3& out)
{
	Vec3 dirfrac;

	dirfrac.x = 1.0f / (dir.x == 0 ? 0.00000001f : dir.x);
	dirfrac.y = 1.0f / (dir.y == 0 ? 0.00000001f : dir.y);
	dirfrac.z = 1.0f / (dir.z == 0 ? 0.00000001f : dir.z);

	Vec3 max = min + size;
	float t1 = (min.x - origin.x) * dirfrac.x;
	float t2 = (max.x - origin.x) * dirfrac.x;
	float t3 = (min.y - origin.y) * dirfrac.y;
	float t4 = (max.y - origin.y) * dirfrac.y;
	float t5 = (min.z - origin.z) * dirfrac.z;
	float t6 = (max.z - origin.z) * dirfrac.z;

	float tmin = maximum(
		maximum(minimum(t1, t2), minimum(t3, t4)), minimum(t5, t6));
	float tmax = minimum(
		minimum(maximum(t1, t2), maximum(t3, t4)), maximum(t5, t6));

	if (tmax < 0)
	{
		return false;
	}

	if (tmin > tmax)
	{
		return false;
	}

	out = tmin < 0 ? origin : origin + dir * tmin;
	return true;
}


float getLineSegmentDistance(const Vec3& origin, const Vec3& dir, const Vec3& a, const Vec3& b)
{
	Vec3 a_origin = origin - a;
	Vec3 ab = b - a;

	float dot1 = dot(ab, a_origin);
	float dot2 = dot(ab, dir);
	float dot3 = dot(dir, a_origin);
	float dot4 = dot(ab, ab);
	float dot5 = dot(dir, dir);

	float denom = dot4 * dot5 - dot2 * dot2;
	if (abs(denom) < 1e-5f)
	{
		Vec3 X = origin + dir * dot(b - origin, dir);
		return length(b - X);
	}

	float numer = dot1 * dot2 - dot3 * dot4;
	float param_a = numer / denom;
	float param_b = (dot1 + dot2 * param_a) / dot4;

	if (param_b < 0 || param_b > 1)
	{
		param_b = clamp(param_b, 0.0f, 1.0f);
		Vec3 B = a + ab * param_b;
		Vec3 X = origin + dir * dot(b - origin, dir);
		return length(B - X);
	}

	Vec3 vec = (origin + dir * param_a) - (a + ab * param_b);
	return length(vec);
}


bool getRayTriangleIntersection(const Vec3& origin,
	const Vec3& dir,
	const Vec3& p0,
	const Vec3& p1,
	const Vec3& p2,
	float* out_t)
{
	Vec3 normal = cross(p1 - p0, p2 - p0);
	float q = dot(normal, dir);
	if (q == 0) return false;

	float d = -dot(normal, p0);
	float t = -(dot(normal, origin) + d) / q;
	if (t < 0) return false;

	Vec3 hit_point = origin + dir * t;

	Vec3 edge0 = p1 - p0;
	Vec3 VP0 = hit_point - p0;
	if (dot(normal, cross(edge0, VP0)) < 0)
	{
		return false;
	}

	Vec3 edge1 = p2 - p1;
	Vec3 VP1 = hit_point - p1;
	if (dot(normal, cross(edge1, VP1)) < 0)
	{
		return false;
	}

	Vec3 edge2 = p0 - p2;
	Vec3 VP2 = hit_point - p2;
	if (dot(normal, cross(edge2, VP2)) < 0)
	{
		return false;
	}

	if (out_t) *out_t = t;
	return true;
}


LUMIX_ENGINE_API bool getSphereTriangleIntersection(const Vec3& center,
	float radius,
	const Vec3& v0,
	const Vec3& v1,
	const Vec3& v2)
{
	Vec3 normal = normalize(cross(v0 - v1, v2 - v1));
	float D = -dot(v0, normal);

	float dist = dot(center, normal) + D;

	if (fabs(dist) > radius) return false;

	float squared_radius = radius * radius;
	if (squaredLength(v0 - center) < squared_radius) return true;
	if (squaredLength(v1 - center) < squared_radius) return true;
	if (squaredLength(v2 - center) < squared_radius) return true;

	return false;
}


static std::mt19937_64& getGUIDRandomGenerator()
{
	static std::random_device seed;
	static std::mt19937_64 gen(seed());

	return gen;
}

static std::mt19937& getRandomGenerator()
{
	static std::random_device seed;
	static std::mt19937 gen(seed());

	return gen;
}


u64 randGUID()
{
	return getGUIDRandomGenerator()();
}


u32 rand()
{
	return getRandomGenerator()();
}


u32 rand(u32 from_incl, u32 to_incl)
{
	std::uniform_int_distribution<> dist(from_incl, to_incl);
	return dist(getRandomGenerator());
}


float randFloat()
{
	std::uniform_real_distribution<float> dist;
	return dist(getRandomGenerator());
}


void seedRandom(u32 seed)
{
	getRandomGenerator().seed(seed);
}


float randFloat(float from, float to)
{
	std::uniform_real_distribution<float> dist(from, to);
	return dist(getRandomGenerator());
}


u32 nextPow2(u32 v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}


u32 log2(u32 v)
{
	u32 r = (v > 0xffff) << 4; v >>= r;
	u32 shift = (v > 0xff) << 3; v >>= shift; r |= shift;
	shift = (v > 0xf) << 2; v >>= shift; r |= shift;
	shift = (v > 0x3) << 1; v >>= shift; r |= shift;
	r |= (v >> 1);
	return r;
}


Matrix4x3::Matrix4x3(const Matrix& rhs) {
	columns[0] = rhs.columns[0].xyz();
	columns[1] = rhs.columns[1].xyz();
	columns[2] = rhs.columns[2].xyz();
	columns[3] = rhs.columns[3].xyz();
}

Matrix3x4 Matrix4x3::transposed() const {
	Matrix3x4 res;
	res.columns[0] = Vec4(columns[0].x, columns[1].x, columns[2].x, columns[3].x);
	res.columns[1] = Vec4(columns[0].y, columns[1].y, columns[2].y, columns[3].y);
	res.columns[2] = Vec4(columns[0].z, columns[1].z, columns[2].z, columns[3].z);
	return res;
}

Matrix3x4::Matrix3x4(const Matrix& rhs) {
	columns[0] = rhs.columns[0];
	columns[1] = rhs.columns[1];
	columns[2] = rhs.columns[2];
}

Matrix::Matrix(const Vec4& col0, const Vec4& col1, const Vec4& col2, const Vec4& col3) {
	columns[0] = col0;
	columns[1] = col1;
	columns[2] = col2;
	columns[3] = col3;
}

void Matrix::setXVector(const Vec3& v) {
	columns[0].x = v.x;
	columns[0].y = v.y;
	columns[0].z = v.z;
}

void Matrix::setYVector(const Vec3& v) {
	columns[1].x = v.x;
	columns[1].y = v.y;
	columns[1].z = v.z;
}

void Matrix::setZVector(const Vec3& v) {
	columns[2].x = v.x;
	columns[2].y = v.y;
	columns[2].z = v.z;
}


float Matrix::determinant() const {
	return columns[0].w * columns[1].z * columns[2].y * columns[3].x - columns[0].z * columns[1].w * columns[2].y * columns[3].x - columns[0].w * columns[1].y * columns[2].z * columns[3].x +
			columns[0].y * columns[1].w * columns[2].z * columns[3].x + columns[0].z * columns[1].y * columns[2].w * columns[3].x - columns[0].y * columns[1].z * columns[2].w * columns[3].x -
			columns[0].w * columns[1].z * columns[2].x * columns[3].y + columns[0].z * columns[1].w * columns[2].x * columns[3].y + columns[0].w * columns[1].x * columns[2].z * columns[3].y -
			columns[0].x * columns[1].w * columns[2].z * columns[3].y - columns[0].z * columns[1].x * columns[2].w * columns[3].y + columns[0].x * columns[1].z * columns[2].w * columns[3].y +
			columns[0].w * columns[1].y * columns[2].x * columns[3].z - columns[0].y * columns[1].w * columns[2].x * columns[3].z - columns[0].w * columns[1].x * columns[2].y * columns[3].z +
			columns[0].x * columns[1].w * columns[2].y * columns[3].z + columns[0].y * columns[1].x * columns[2].w * columns[3].z - columns[0].x * columns[1].y * columns[2].w * columns[3].z -
			columns[0].z * columns[1].y * columns[2].x * columns[3].w + columns[0].y * columns[1].z * columns[2].x * columns[3].w + columns[0].z * columns[1].x * columns[2].y * columns[3].w -
			columns[0].x * columns[1].z * columns[2].y * columns[3].w - columns[0].y * columns[1].x * columns[2].z * columns[3].w + columns[0].x * columns[1].y * columns[2].z * columns[3].w;
}


Matrix Matrix::inverted() const {
	Matrix mtx;
	float d = determinant();
	if (d == 0) return *this;
	d = 1.0f / d;

	mtx.columns[0] = Vec4(d * (columns[1].z * columns[2].w * columns[3].y - columns[1].w * columns[2].z * columns[3].y + columns[1].w * columns[2].y * columns[3].z -
									columns[1].y * columns[2].w * columns[3].z - columns[1].z * columns[2].y * columns[3].w + columns[1].y * columns[2].z * columns[3].w),
		d * (columns[0].w * columns[2].z * columns[3].y - columns[0].z * columns[2].w * columns[3].y - columns[0].w * columns[2].y * columns[3].z + columns[0].y * columns[2].w * columns[3].z +
				columns[0].z * columns[2].y * columns[3].w - columns[0].y * columns[2].z * columns[3].w),
		d * (columns[0].z * columns[1].w * columns[3].y - columns[0].w * columns[1].z * columns[3].y + columns[0].w * columns[1].y * columns[3].z - columns[0].y * columns[1].w * columns[3].z -
				columns[0].z * columns[1].y * columns[3].w + columns[0].y * columns[1].z * columns[3].w),
		d * (columns[0].w * columns[1].z * columns[2].y - columns[0].z * columns[1].w * columns[2].y - columns[0].w * columns[1].y * columns[2].z + columns[0].y * columns[1].w * columns[2].z +
				columns[0].z * columns[1].y * columns[2].w - columns[0].y * columns[1].z * columns[2].w));
	mtx.columns[1] = Vec4(d * (columns[1].w * columns[2].z * columns[3].x - columns[1].z * columns[2].w * columns[3].x - columns[1].w * columns[2].x * columns[3].z +
									columns[1].x * columns[2].w * columns[3].z + columns[1].z * columns[2].x * columns[3].w - columns[1].x * columns[2].z * columns[3].w),
		d * (columns[0].z * columns[2].w * columns[3].x - columns[0].w * columns[2].z * columns[3].x + columns[0].w * columns[2].x * columns[3].z - columns[0].x * columns[2].w * columns[3].z -
				columns[0].z * columns[2].x * columns[3].w + columns[0].x * columns[2].z * columns[3].w),
		d * (columns[0].w * columns[1].z * columns[3].x - columns[0].z * columns[1].w * columns[3].x - columns[0].w * columns[1].x * columns[3].z + columns[0].x * columns[1].w * columns[3].z +
				columns[0].z * columns[1].x * columns[3].w - columns[0].x * columns[1].z * columns[3].w),
		d * (columns[0].z * columns[1].w * columns[2].x - columns[0].w * columns[1].z * columns[2].x + columns[0].w * columns[1].x * columns[2].z - columns[0].x * columns[1].w * columns[2].z -
				columns[0].z * columns[1].x * columns[2].w + columns[0].x * columns[1].z * columns[2].w));
	mtx.columns[2] = Vec4(d * (columns[1].y * columns[2].w * columns[3].x - columns[1].w * columns[2].y * columns[3].x + columns[1].w * columns[2].x * columns[3].y -
									columns[1].x * columns[2].w * columns[3].y - columns[1].y * columns[2].x * columns[3].w + columns[1].x * columns[2].y * columns[3].w),
		d * (columns[0].w * columns[2].y * columns[3].x - columns[0].y * columns[2].w * columns[3].x - columns[0].w * columns[2].x * columns[3].y + columns[0].x * columns[2].w * columns[3].y +
				columns[0].y * columns[2].x * columns[3].w - columns[0].x * columns[2].y * columns[3].w),
		d * (columns[0].y * columns[1].w * columns[3].x - columns[0].w * columns[1].y * columns[3].x + columns[0].w * columns[1].x * columns[3].y - columns[0].x * columns[1].w * columns[3].y -
				columns[0].y * columns[1].x * columns[3].w + columns[0].x * columns[1].y * columns[3].w),
		d * (columns[0].w * columns[1].y * columns[2].x - columns[0].y * columns[1].w * columns[2].x - columns[0].w * columns[1].x * columns[2].y + columns[0].x * columns[1].w * columns[2].y +
				columns[0].y * columns[1].x * columns[2].w - columns[0].x * columns[1].y * columns[2].w));
	mtx.columns[3] = Vec4(d * (columns[1].z * columns[2].y * columns[3].x - columns[1].y * columns[2].z * columns[3].x - columns[1].z * columns[2].x * columns[3].y +
									columns[1].x * columns[2].z * columns[3].y + columns[1].y * columns[2].x * columns[3].z - columns[1].x * columns[2].y * columns[3].z),
		d * (columns[0].y * columns[2].z * columns[3].x - columns[0].z * columns[2].y * columns[3].x + columns[0].z * columns[2].x * columns[3].y - columns[0].x * columns[2].z * columns[3].y -
				columns[0].y * columns[2].x * columns[3].z + columns[0].x * columns[2].y * columns[3].z),
		d * (columns[0].z * columns[1].y * columns[3].x - columns[0].y * columns[1].z * columns[3].x - columns[0].z * columns[1].x * columns[3].y + columns[0].x * columns[1].z * columns[3].y +
				columns[0].y * columns[1].x * columns[3].z - columns[0].x * columns[1].y * columns[3].z),
		d * (columns[0].y * columns[1].z * columns[2].x - columns[0].z * columns[1].y * columns[2].x + columns[0].z * columns[1].x * columns[2].y - columns[0].x * columns[1].z * columns[2].y -
				columns[0].y * columns[1].x * columns[2].z + columns[0].x * columns[1].y * columns[2].z));
	return mtx;
}

Matrix Matrix::fastInverted() const {
	Matrix ret;
	ret.columns[0].x = columns[0].x;
	ret.columns[1].y = columns[1].y;
	ret.columns[2].z = columns[2].z;

	ret.columns[1].x = columns[0].y;
	ret.columns[0].y = columns[1].x;

	ret.columns[1].z = columns[2].y;
	ret.columns[2].y = columns[1].z;

	ret.columns[0].z = columns[2].x;
	ret.columns[2].x = columns[0].z;

	float x = -columns[3].x;
	float y = -columns[3].y;
	float z = -columns[3].z;
	ret.columns[3].x = x * ret.columns[0].x + y * ret.columns[1].x + z * ret.columns[2].x;
	ret.columns[3].y = x * ret.columns[0].y + y * ret.columns[1].y + z * ret.columns[2].y;
	ret.columns[3].z = x * ret.columns[0].z + y * ret.columns[1].z + z * ret.columns[2].z;

	ret.columns[0].w = 0;
	ret.columns[1].w = 0;
	ret.columns[2].w = 0;
	ret.columns[3].w = 1;

	return ret;
}

void Matrix::copy3x3(const Matrix& mtx) {
	columns[0].x = mtx.columns[0].x;
	columns[0].y = mtx.columns[0].y;
	columns[0].z = mtx.columns[0].z;

	columns[1].x = mtx.columns[1].x;
	columns[1].y = mtx.columns[1].y;
	columns[1].z = mtx.columns[1].z;

	columns[2].x = mtx.columns[2].x;
	columns[2].y = mtx.columns[2].y;
	columns[2].z = mtx.columns[2].z;
}

void Matrix::translate(const Vec3& t) {
	columns[3].x += t.x;
	columns[3].y += t.y;
	columns[3].z += t.z;
}

void Matrix::translate(float x, float y, float z) {
	columns[3].x += x;
	columns[3].y += y;
	columns[3].z += z;
}

void Matrix::setTranslation(const Vec3& t) {
	columns[3].x = t.x;
	columns[3].y = t.y;
	columns[3].z = t.z;
}

} // namespace Lumix