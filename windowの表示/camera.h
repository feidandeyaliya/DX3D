/*==================================================================================================

	カメラ制御[camera.h]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#ifndef CAMERA_H_
#define CAMERA_H_

#include<d3d9.h>
void Camera_Initialize(void);
void Camera_Update(void);
void Camera_SetMatrixToDevice(void);

const D3DXVECTOR3* Camera_GetFrontVector(void);
const D3DXVECTOR3* Camera_GetAt(void);
#endif // !CAMERA_H_

