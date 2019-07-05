/** @file *//********************************************************************************************************

                                                       Water.h

						                    Copyright 2004, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Water/Water.h#4 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once

#include "HeightField/HeightField.h"

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

class Water
{
public:

	Water( int sizeX, int sizeY, float c, float damping );
	virtual ~Water();

	int		GetSizeX() const						{ return m_aSurface[0].GetSizeJ(); }
	int		GetSizeY() const						{ return m_aSurface[0].GetSizeI(); }
													
	void	SetC( float c )							{ m_C = c; }
	float	GetC() const							{ return m_C; }
													
	void	SetDamping( float damping )				{ m_Damping = damping; }
	float	GetDamping() const						{ return m_Damping; }

	// Return the current height field
	HeightField const &	GetHeightField() const;
	HeightField &		GetHeightField();

	// Return the vertex data from the current height field
	HeightField::Vertex const *	GetData( int x = 0, int y = 0 ) const;
	HeightField::Vertex *		GetData( int x = 0, int y = 0 );
	float						GetZ( int x, int y ) const;
//	Vector3f const &			GetNormal( int x, int y ) const;

	void	Update( float dt );

private:

	HeightField	m_aSurface[ 2 ];	// Surfaces
	int			m_CurrentSurface;	// Index of the current surface
	float		m_C;
	float		m_Damping;
};



/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline HeightField const & Water::GetHeightField() const
{
	return m_aSurface[ m_CurrentSurface ];
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline HeightField & Water::GetHeightField()
{
	// Just use the const version
	Water const * const	pCWater	= const_cast< Water const * >( this );

	return const_cast< HeightField & >( pCWater->GetHeightField() );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline HeightField::Vertex const * Water::GetData( int x/*= 0*/, int y/*= 0*/ ) const
{
	return GetHeightField().GetData( x, y );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline HeightField::Vertex * Water::GetData( int x/*= 0*/, int y/*= 0*/ )
{
	// Just use the const version
	Water const * const	pCWater	= const_cast< Water const * >( this );

	return const_cast< HeightField::Vertex * >( pCWater->GetData( x, y ) );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline float Water::GetZ( int x, int y ) const
{
	return GetData( x, y )->m_Z;
}
//
//
///********************************************************************************************************************/
///*																													*/
///********************************************************************************************************************/
//
//inline Vector3f const & Water::GetNormal( int x, int y ) const
//{
//	return GetData( x, y )->m_Normal;
//}
