#include "Vect2D.h"

Vect2D::Vect2D()
{
}

Vect2D::Vect2D( float inX, float inY )
{
	x = inX;
	y = inY; 
}

Vect2D::~Vect2D(void)
{
}
	
float Vect2D::GetX()
{
	return x;
}

float Vect2D::GetY()
{
	return y;
}

void Vect2D::SetX( float inX )
{
	x = inX;
}

void Vect2D::SetY( float inY )
{
	y = inY;
}

void Vect2D::SetXY( float inX, float inY )
{
	x = inX;
	y = inY; 
}

void Vect2D::ToUnitVector()
{
	//calculate length 
	float length = sqrt((x*x) + (y*y));
	if ( length > 0 )
	{
		x = x/length; 
		y = y/length;
	}
}

void Vect2D::Subtract( Vect2D a, Vect2D b, Vect2D &c )
{	
	c.SetXY( a.GetX()-b.GetX(), a.GetY()-b.GetY() );
}

float Vect2D::DotProduct( Vect2D a, Vect2D b )
{
	return (a.GetX() * b.GetX()) + (a.GetY() * b.GetY());

}

float Vect2D::Distance( Vect2D a, Vect2D b )
{
	Vect2D between;
	Subtract( b, a, between );

	return sqrt( (between.GetX()*between.GetX()) + (between.GetY()*between.GetY()) );
}
