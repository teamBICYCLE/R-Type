#ifndef		__VECTOR2D_HPP__
# define	__VECTOR2D_HPP__

# include <iostream>
# include <SFML/System/Vector2.hpp>

class Vector2D
{
    public:
        Vector2D(float x = 0, float y = 0);
        Vector2D(const float *v);
        Vector2D(const Vector2D &v);
        Vector2D& operator= (const Vector2D& v);
        void	set(float x, float y);

        float&	operator[](int i);
        float	operator[](int i) const;

        Vector2D&   operator+=(const Vector2D& v);
        Vector2D&   operator-=(const Vector2D& v);
        Vector2D&   operator*=(float s);
        Vector2D&   operator/=(float s);
        Vector2D    operator+(const Vector2D& v) const;
        Vector2D	operator-(const Vector2D& v) const;
        Vector2D	operator*(float s) const;
        Vector2D	operator/(float s) const;
        Vector2D	operator-() const;
        bool	    operator==(const Vector2D& v) const;
        bool	    operator!=(const Vector2D& v) const;
        friend std::ostream&  operator<<(std::ostream& stream, const Vector2D& vector);

    public:
        operator sf::Vector2f() const;

    public:
        float	length() const;
        float	lengthSquared() const;
        void    normalize();
        float	dot(const Vector2D& v) const;
        float	distance(const Vector2D& v) const;
        float	distanceSquared(const Vector2D& v) const;

        float	x;
        float	y;
};

#endif /* __VECTOR2D_HPP__ */
