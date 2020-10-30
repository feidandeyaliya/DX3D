#pragma once
#include<d3d9.h>

#ifndef MY_DIRECT3D_H
#define MYDIRECT3D_H

//direct3DŠÖ˜A‚Ì‰Šú‰»

bool MyDirect3D_Initialize(HWND hWnd);

//ª‚ÌI—¹ˆ—

void MyDirect3D_Finalize(void);

//
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);

#endif