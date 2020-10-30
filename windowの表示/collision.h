/*==================================================================================================

	ƒRƒŠƒWƒ‡ƒ“”»’è[collision.h]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#ifndef COLLISION_H
#define COLLISION_H

#include <d3dx9.h>

typedef struct CollisionCircle_tag
{
	D3DXVECTOR2 center;
	float radius;
}CollisionCircle;

bool Collision_CircleAndCircleHit(const CollisionCircle*pA, const CollisionCircle*pB);

#endif // !COLLISION_H

