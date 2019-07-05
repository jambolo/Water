/** @file *//********************************************************************************************************

                                                      Water.cpp

						                    Copyright 2004, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Water/Water.cpp#5 $

	$NoKeywords: $

 ********************************************************************************************************************/

#include "Water.h"

#include "Misc/max.h"


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

Water::Water( int sizeX, int sizeY, float c, float damping )
	: m_C( c ), m_Damping( damping ),
	m_CurrentSurface( 0 )
{
	// Create and initialize the first surface

	std::vector<HeightField::Vertex> v( sizeX * sizeY );
	m_aSurface[ 0 ] = HeightField( sizeX, sizeY, v );

	// Copy the surface to the other one

	m_aSurface[ 1 ] = m_aSurface[ 0 ];
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

Water::~Water()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void Water::Update( float dt )
{
	// Flip the current surface

	m_CurrentSurface ^= 1;

	int const	oldSurface		= m_CurrentSurface ^ 1;

	// Compute the new heights

	double const	a = .5;//limit( 0., ( m_C * m_C ) * ( dt * dt ) / ( m_aSurface[ m_CurrentSurface ].GetXYScale() * m_aSurface[ m_CurrentSurface ].GetXYScale() ), .5 );
	double const	b = 2. - 4. * a;

	int const		sx	= m_aSurface[ m_CurrentSurface ].GetSizeJ();
	int const		sy	= m_aSurface[ m_CurrentSurface ].GetSizeI();

	for ( int y = 1; y < sy - 1; y++ )
	{
		for ( int x = 1; x < sx - 1; x++ )
		{
			HeightField::Vertex * const	paV0	= m_aSurface[ m_CurrentSurface ].GetData( x, y );
			HeightField::Vertex * const	paV1	= m_aSurface[ oldSurface ].GetData( x, y );

			paV0->m_Z	=   float(   a * (   paV1[ -1  ].m_Z + paV1[  1  ].m_Z + paV1[ -sx ].m_Z + paV1[  sx ].m_Z )
								   + b * paV1[ 0 ].m_Z
								   - paV0[ 0 ].m_Z )
						  * m_Damping;
		}
	}
//
//	m_aSurface[ m_CurrentSurface ].ComputeNormals();
}
