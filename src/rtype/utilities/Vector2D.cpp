#include <math.h>
#include "Vector2D.hh"

Vector2D::Vector2D(float x, float y)
    : x(x), y(y)
{
}


Vector2D::Vector2D(const float *v)
    : x(v[0]), y(v[1])
{
}


Vector2D::Vector2D(const Vector2D &v)
    : x(v.x), y(v.y)
{
}

Vector2D&	Vector2D::operator=(const Vector2D& v)
{
  set(v.x, v.y);
  return *this;
}

void		Vector2D::set(float x, float y)
{
  this->x = x;
  this->y = y;
}

float&		Vector2D::operator[](int i)
{
  if (i == 0)
    return x;
  if (i == 1)
    return y;
  return x;
}

float		Vector2D::operator[](int i) const
{
  if (i == 0)
    return x;
  if (i == 1)
    return y;
  return x;
}

Vector2D&	Vector2D::operator+=(const Vector2D& v)
{
  x += v.x;
  y += v.y;
  return *this;
}

Vector2D&	Vector2D::operator-=(const Vector2D& v)
{
  x -= v.x;
  y -= v.y;
  return *this;
}

Vector2D&	 Vector2D::operator*=(float s)
{
  x *= s;
  y *= s;
  return *this;
}

Vector2D&	 Vector2D::operator/=(float s)
{
  x /= s;
  y /= s;
  return *this;
}

Vector2D	 Vector2D::operator+(const Vector2D& v) const
{
  return Vector2D(x + v.x,  y + v.y);
}

Vector2D	 Vector2D::operator-(const Vector2D& v) const
{
  return Vector2D(x - v.x, y - v.y);
}

Vector2D	 Vector2D::operator-(void) const
{
  return Vector2D(-x, -y);
}

Vector2D	 Vector2D::operator*(float s) const
{
  return Vector2D(x * s, y * s);
}

Vector2D	 Vector2D::operator/(float s) const
{
  return Vector2D(x / s, y / s);
}

bool		 Vector2D::operator==(const Vector2D& v) const
{
  return ((x == v.x) &&
	  (y == v.y));
}

bool		Vector2D::operator!=(const Vector2D& v) const
{
  return ((x != v.x) ||
	  (y != v.y));
}

Vector2D::operator sf::Vector2f() const
{
    return sf::Vector2f(x, y);
}

float		Vector2D::length() const
{
  return sqrt(lengthSquared());
}

float		 Vector2D::lengthSquared() const
{
  return x * x + y * y;
}

void		 Vector2D::normalize()
{
  float len = length();
  if (len > 0)
    {
      x /= len;
      y /= len;
    }
}

float		 Vector2D::dot(const Vector2D& v) const
{
  return x * v.x + y * v.y;
}

float		 Vector2D::distance(const Vector2D& v) const
{
  return sqrt(distanceSquared(v));
}

float		 Vector2D::distanceSquared(const Vector2D& v) const
{
  float dx, dy;
  dx = x - v.x;
  dy = y - v.y;
  return dx * dx + dy * dy;
}

Vector2D	operator*(float s, const Vector2D& v)
{
  return v * s;
}

std::ostream&  operator<<(std::ostream& stream, const Vector2D& vector)
{
  stream << "x=" << vector.x << "-y=" << vector.y;
  return stream;
}
