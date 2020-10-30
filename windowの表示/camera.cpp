#include<d3dx9.h>
#include"mydirect3d.h"
#include"config.h"
#include"KeyLogger.h"

float cam = -8.f;

static D3DXVECTOR3 g_vFront(0.0f, -0.5f, 1.0f);
static D3DXVECTOR3 g_vRight(1.0f, 0.0f, 0.0f);
static D3DXVECTOR3 g_vUp(0.0f, 1.0f, 0.0f);
static D3DXVECTOR3 g_Position(0.0f, 1.0f, -5.0f);
static D3DXVECTOR3 g_Direct(0.0f, 0.0f, 0.0f);
static D3DXVECTOR3 g_At(1.0f, 0.0f, 0.0f);
static D3DXVECTOR3 g_MovingSpeed(0.0f, 0.0f, 0.0f);
static float g_RotationalSpeed = 0.1f;
#define MOVINGSPEED_MAX (0.2f)
#define MOVING_ACCEL (0.03f)
#define MOVING_ATTENUATION_RATE (0.90f)

void Camera_Initialize(void)
{
	g_vFront= D3DXVECTOR3(0.0f, -0.5f, 1.0f);
	g_vRight= D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 g_At = g_Position + g_vFront;
	//外積で上方向ベクトルを算出
	D3DXVec3Cross(&g_vUp, &g_vFront, &g_vRight);

	//各ベクトルを正規化
	D3DXVec3Normalize(&g_vFront, &g_vFront);
	D3DXVec3Normalize(&g_vRight, &g_vRight);
	D3DXVec3Normalize(&g_vUp, &g_vUp);

	g_Position= D3DXVECTOR3(0.0f, 1.0f, -5.0f);
	g_Direct = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MovingSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_RotationalSpeed = 0.05f;
	

}

void Camera_Update(void)
{
	if (keylogger_Press(KL_FRONT))
	{
		D3DXVECTOR3 v = g_vFront;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		g_Direct = g_Direct + v;
	}
	if (keylogger_Press(KL_BACK))
	{
		D3DXVECTOR3 v = g_vFront;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		g_Direct = g_Direct - v;
	}
	if (keylogger_Press(KL_LEFT))
	{
		D3DXVECTOR3 v = g_vRight;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		g_Direct = g_Direct - v;
	}
	if (keylogger_Press(KL_RIGHT))
	{
		D3DXVECTOR3 v = g_vRight;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		g_Direct = g_Direct + v;
	}
	if (keylogger_Press(KL_UP))
	{
		D3DXVECTOR3 v = g_vUp;
		v.x = v.z = 0.0f;
		D3DXVec3Normalize(&v, &v);
		g_Direct = g_Direct + v;
	}
	if (keylogger_Press(KL_DOWN))
	{
		D3DXVECTOR3 v = g_vUp;
		v.x = v.z = 0.0f;
		D3DXVec3Normalize(&v, &v);
		g_Direct = g_Direct - v;
	}
	//速度の一定化
	D3DXVec3Normalize(&g_Direct, &g_Direct);
	g_MovingSpeed += g_Direct*MOVING_ACCEL;
	if (D3DXVec3Length(&g_MovingSpeed) > MOVINGSPEED_MAX)
	{
		D3DXVec3Normalize(&g_MovingSpeed, &g_MovingSpeed);
		g_MovingSpeed *= MOVINGSPEED_MAX;
	}
	g_Position += g_MovingSpeed;
	g_MovingSpeed *= MOVING_ATTENUATION_RATE;
	g_Direct = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (keylogger_Press(KL_TURN_UP))
	{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationAxis(&mtxR, &g_vRight, -g_RotationalSpeed);
		//D3DXVec3Transform;//座標変換すると、四次元ベクトルで出力（w=1が追加演算）
		//D3DXVec3TransformCoord;//座標変換すると、三次元ベクトルで出力（w=1が追加演算後、削除）
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);//座標変換すると、三次元ベクトルで出力（w=0が追加演算後、削除）		
		D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
		//D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);

	}
	if (keylogger_Press(KL_TURN_DOWN))
	{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationAxis(&mtxR, &g_vRight, g_RotationalSpeed);
		//D3DXVec3Transform;//座標変換すると、四次元ベクトルで出力（w=1が追加演算）
		//D3DXVec3TransformCoord;//座標変換すると、三次元ベクトルで出力（w=1が追加演算後、削除）
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);//座標変換すると、三次元ベクトルで出力（w=0が追加演算後、削除）		
		D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
		//D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);

	}
	
	if (keylogger_Press(KL_SPACE))
	{
		g_At = g_Position + g_vFront * 5.5f;
		if (keylogger_Press(KL_TURN_LEFT))
		{

			D3DXMATRIX mtxR;
			D3DXMatrixRotationY(&mtxR, g_RotationalSpeed);
			D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);//座標変換すると、三次元ベクトルで出力（w=0が追加演算後、削除）		
			D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
			//D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);

			g_Position = g_At - g_vFront * 5.5f;
		}
		if (keylogger_Press(KL_TURN_RIGHT))
		{

			D3DXMATRIX mtxR;
			D3DXMatrixRotationY(&mtxR, -g_RotationalSpeed);
			D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);//座標変換すると、三次元ベクトルで出力（w=0が追加演算後、削除）		
			D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
			//D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);

			g_Position = g_At - g_vFront * 5.5f;
		}
	}
	else
	{
		if (keylogger_Press(KL_TURN_LEFT))
		{
			D3DXMATRIX mtxR;
			D3DXMatrixRotationY(&mtxR, -g_RotationalSpeed);
			//D3DXVec3Transform;//座標変換すると、四次元ベクトルで出力（w=1が追加演算）
			//D3DXVec3TransformCoord;//座標変換すると、三次元ベクトルで出力（w=1が追加演算後、削除）
			D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);//座標変換すると、三次元ベクトルで出力（w=0が追加演算後、削除）		
			D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
			//D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);

		}
		if (keylogger_Press(KL_TURN_RIGHT))
		{
			D3DXMATRIX mtxR;
			D3DXMatrixRotationY(&mtxR, g_RotationalSpeed);
			D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);//座標変換すると、三次元ベクトルで出力（w=0が追加演算後、削除）		
			D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
			//D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);
		}
	}

	

	D3DXVec3Cross(&g_vUp, &g_vFront, &g_vRight);
	//各ベクトルを正規化
	D3DXVec3Normalize(&g_vFront, &g_vFront);
	D3DXVec3Normalize(&g_vRight, &g_vRight);
	D3DXVec3Normalize(&g_vUp, &g_vUp);
}


void Camera_SetMatrixToDevice(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	//ビュー座標変換行列の作成
	D3DXMATRIX mtxView;
	//注視点を算出
	g_At =g_Position+g_vFront*5.5f;//注視点
	D3DXMatrixLookAtLH(&mtxView, &g_Position, &g_At, &g_vUp);
	//デバイスにビュー変換行列を設定
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	//プロジェクション（パースペクティブ）変換行列の作成
	D3DXMATRIX mtxProjection;
	float fov_y = D3DXToRadian(60);
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	float z_near = 0.1f;
	float z_far = 100.f;
	D3DXMatrixPerspectiveFovLH(&mtxProjection, fov_y, aspect, z_near, z_far);
	//デバイスにプロジェクション変換行列を設定
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	cam += 0.1f;
}


const D3DXVECTOR3* Camera_GetPosition(void)
{
	return &g_Position;
}


const D3DXVECTOR3* Camera_GetFrontVector(void)
{
	return &g_vFront;
}

const D3DXVECTOR3* Camera_GetAt(void)
{
	return &g_At;
}