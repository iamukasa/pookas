#ifndef _VECT3D_H_
#define _VECT3D_H_

#include <math.h>

class Vect3D
{
public:
	Vect3D();
	Vect3D( float inX, float inY, float inZ );
	~Vect3D(void);
	
	static float Distance( Vect3D a, Vect3D b ); 
	static float DotProduct( Vect3D a, Vect3D b );
	static void Subtract( Vect3D a, Vect3D b, Vect3D &c );

	void SetX( float inX );
	void SetY( float inY );
	void SetZ( float inZ );
	void SetXYZ( float inX, float inY, float inZ ); 

	float GetX();
	float GetY();
	float GetZ(); 
	void ToUnitVector();

private:
	float x, y, z; 

};

#endif