#include "Vect3D.h"

Vect3D::Vect3D()
{
}

Vect3D::Vect3D( float inX, float inY, float inZ )
{
	x = inX;
	y = inY; 
	z = inZ;
}

Vect3D::~Vect3D(void)
{
}
	
float Vect3D::GetX()
{
	return x;
}

float Vect3D::GetY()
{
	return y;
}

float Vect3D::GetZ()
{
	return z;
}

void Vect3D::SetX( float inX )
{
	x = inX;
}

void Vect3D::SetY( float inY )
{
	y = inY;
}

void Vect3D::SetZ( float inZ )
{
	z = inZ;
}

void Vect3D::SetXYZ( float inX, float inY, float inZ )
{
	x = inX;
	y = inY; 
	z = inZ;
}

void Vect3D::ToUnitVector()
{
	//calculate length 
	float length = sqrt((x*x) + (y*y) + (z*z));
	if ( length > 0 )
	{
		x = x/length; 
		y = y/length;
		z = z/length;
	}
}

void Vect3D::Subtract( Vect3D a, Vect3D b, Vect3D &c )
{	
	c.SetXYZ( a.GetX()-b.GetX(), a.GetY()-b.GetY(), a.GetZ()-b.GetZ() );
}

float Vect3D::DotProduct( Vect3D a, Vect3D b )
{
	return (a.GetX() * b.GetX()) + (a.GetY() * b.GetY()) + (a.GetZ() * b.GetZ());

}

float Vect3D::Distance( Vect3D a, Vect3D b )
{
	Vect3D between;
	Subtract( b, a, between );

	return sqrt( (between.GetX()*between.GetX()) + (between.GetY()*between.GetY()) 
		+ (between.GetZ()*between.GetZ()) );
}
