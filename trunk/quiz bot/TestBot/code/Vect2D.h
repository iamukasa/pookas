#ifndef _VECT2D_H_
#define _VECT2D_H_

#include <math.h>

class Vect2D
{
public:
	Vect2D();
	Vect2D( float inX, float inY );
	~Vect2D(void);
	
	static float Distance( Vect2D a, Vect2D b ); 
	static float DotProduct( Vect2D a, Vect2D b );
	static void Subtract( Vect2D a, Vect2D b, Vect2D &c );

	void SetX( float inX );
	void SetY( float inY );
	void SetXY( float inX, float inY ); 

	float GetX();
	float GetY();
	void ToUnitVector();

private:
	float x, y; 

};

#endif