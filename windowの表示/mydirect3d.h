#pragma once
#include<d3d9.h>

#ifndef MY_DIRECT3D_H
#define MYDIRECT3D_H

//direct3D�֘A�̏�����

bool MyDirect3D_Initialize(HWND hWnd);

//���̏I������

void MyDirect3D_Finalize(void);

//
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);

#endif