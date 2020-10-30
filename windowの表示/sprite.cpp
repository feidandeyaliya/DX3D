#include<d3dx9.h>

#include"mydirect3d.h"
#include"texture.h"

typedef struct Vertex2D_tag
{
	D3DXVECTOR4 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 TexCoord;
}Vertex2D;
#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//FVF �t���L�V�u���o�[�e�b�N�X�t�H�[�}�b�g
//RHW = 1...���W�ϊ��ςݒ��_

//�O���[�o���ϐ��錾
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;	//���_�o�b�t�@
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;	//�C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X
static D3DCOLOR g_Color = 0xffffffff;					//�|���S���J���[

void Sprite_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return;
	}
	pDevice->CreateVertexBuffer(
		sizeof(Vertex2D) * 4,	//���_�o�b�t�@�̗�(�o�C�g)
		D3DUSAGE_WRITEONLY,		//�g����
		FVF_VERTEX2D,			//FVF
		D3DPOOL_MANAGED,		//�������̊Ǘ����@
		&g_pVertexBuffer,		//�擾�����C���^�[�t�F�[�X�̃A�h���X���L�^���邽�߂̃|�C���^
		NULL
		);

	pDevice->CreateIndexBuffer(
		sizeof(WORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBuffer,
		NULL
	);
}

void Sprite_Finalaize(void)
{
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}

//�J���[�ݒ�
//
//�����Fcolor�@�|���S���J���[
//
void Sprite_Setcolor(D3DCOLOR color)
{
	g_Color = color;
}



//�X�v���C�g�̕`��(�V���v��)
//�e�N�X�`���؂���T�C�Y�̃|���S���Ŏw����W�ɕ`��
//
//�����FtextureId �@�e�N�X�`���Ǘ��ԍ�
//      dx�@�@�@�@�@�`����W���i������W
//      dy�@�@�@�@�@�`����W���i������W
//
void Sprite_Draw(int textureId, float dx, float dy)
{
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		MessageBox(NULL, "Device�̎擾�Ɏ��s���܂���", "�G���[", MB_OK);
		return;
	}
	//�f�o�C�X��FVF�̐ݒ������
	g_pDevice->SetFVF(FVF_VERTEX2D);

	//�f�o�C�X�Ƀe�N�X�`���̐ݒ������
	g_pDevice->SetTexture(0, texture_GetTexture(textureId));

	//
	unsigned long w = texture_GetTextureWidth(textureId);

	unsigned long h = texture_GetTextureHeight(textureId);



	//���_�f�[�^
	Vertex2D v[] =
	{
		{D3DXVECTOR4(dx    - 0.5f,dy   - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(0.0f,0.0f)},
		{D3DXVECTOR4(dx +w - 0.5f,dy   - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(1.0f,0.0f)},
		{D3DXVECTOR4(dx    - 0.5f,dy+h - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(0.0f,1.0f)},
		{D3DXVECTOR4(dx+w  - 0.5f,dy+h - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(1.0f,1.0f)},
	};

	//���_�o�b�t�@�����b�N���ăf�[�^����������
	Vertex2D* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);

	//�f�[�^����������
	memcpy(pV, v, sizeof(v));

	g_pVertexBuffer->Unlock();
	//�C���f�b�N�X�o�b�t�@�����b�N���ăf�[�^����������
	WORD* pI;
	g_pIndexBuffer->Lock(0, 0, (void**)&pI, 0);
	pI[0] = 0;
	pI[1] = 1;
	pI[2] = 2;
	pI[3] = 1;
	pI[4] = 3;
	pI[5] = 2;
	
	g_pIndexBuffer->Unlock();

	//�f�o�C�X�ɒ��_�o�b�t�@�̗��p��ݒ�
	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));

	//�f�o�C�X�ɃC���f�b�N�X�o�b�t�@�̗��p��ݒ�
	g_pDevice->SetIndices(g_pIndexBuffer);

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);


	//�|���S���`��(���S��)
	//g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2,pI,D3DFMT_INDEX16, v, sizeof(Vertex2D));

	//�|���S���`��(�ȈՔ�)
	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
}




//�X�v���C�g�̕`��(���{�T�C�Y)
//�e�N�X�`���؂���T�C�Y�̃|���S���Ŏw����W�ɕ`��
//
//�����FtextureId �@�e�N�X�`���Ǘ��ԍ�
//      dx�@�@�@�@�@�`����W���i������W
//      dy�@�@�@�@�@�`����W���i������W
//�@�@�@tcx�@�@�@�@ �e�N�X�`���̐؂�����W��
//�@�@�@tcy�@�@�@�@ �e�N�X�`���̐؂�����Wy
//�@�@�@tcw�@�@�@�@ �e�N�X�`���̐؂��蕝
//�@�@�@tch�@�@�@�@ �e�N�X�`���̐؂��蕝
//
void Sprite_Draw(int textureId, float dx, float dy, int tcx, int tcy, int tcw, int tch)
{
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		MessageBox(NULL, "Device�̎擾�Ɏ��s���܂���", "�G���[", MB_OK);
		return;
	}
	//�f�o�C�X��FVF�̐ݒ������
	g_pDevice->SetFVF(FVF_VERTEX2D);

	//�f�o�C�X�Ƀe�N�X�`���̐ݒ������
	g_pDevice->SetTexture(0, texture_GetTexture(textureId));

	//�|���R���̃T�C�Y�̓e�N�X�`���T�C�Y
	unsigned long w = texture_GetTextureWidth(textureId);

	unsigned long h = texture_GetTextureHeight(textureId);

	//�e�N�X�`���؂���UV���W
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;


	//���_�f�[�^
	Vertex2D v[] =
	{
		{D3DXVECTOR4(dx - 0.5f,       dy - 0.5f,1.0f,1.0f      ), g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dx + tcw - 0.5f, dy - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(dx - 0.5f,       dy + tch - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dx + tcw - 0.5f, dy + tch - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(u1,v1)},
	};

	Vertex2D* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);

	//�f�[�^����������
	memcpy(pV, v, sizeof(v));

	g_pVertexBuffer->Unlock();

	//�f�o�C�X�ɗ��p���钸�_�o�b�t�@���w�肷��
	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));

	g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}



//�X�v���C�g�̕`��(�T�C�Y����)
//�e�N�X�`���؂���T�C�Y�̃|���S���Ŏw����W�ɕ`��
//
//�����FtextureId �@�e�N�X�`���Ǘ��ԍ�
//      dx�@�@�@�@�@�`����W���i������W
//      dy�@�@�@�@�@�`����W���i������W
//      dw          �|���R���T�C�Y�̕�
//      dh�@�@�@�@�@�|���R���T�C�Y�̍���
//�@�@�@tcx�@�@�@�@ �e�N�X�`���̐؂�����W��
//�@�@�@tcy�@�@�@�@ �e�N�X�`���̐؂�����Wy
//�@�@�@tcw�@�@�@�@ �e�N�X�`���̐؂��蕝
//�@�@�@tch�@�@�@�@ �e�N�X�`���̐؂��蕝
//
void Sprite_Draw(int textureId, float dx, float dy,float dw,float dh, int tcx, int tcy, int tcw, int tch)
{
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		MessageBox(NULL, "Device�̎擾�Ɏ��s���܂���", "�G���[", MB_OK);
		return;
	}
	//�f�o�C�X��FVF�̐ݒ������
	g_pDevice->SetFVF(FVF_VERTEX2D);

	//�f�o�C�X�Ƀe�N�X�`���̐ݒ������
	g_pDevice->SetTexture(0, texture_GetTexture(textureId));

	//�|���R���̃T�C�Y�̓e�N�X�`���T�C�Y
	unsigned long w = texture_GetTextureWidth(textureId);

	unsigned long h = texture_GetTextureHeight(textureId);

	//�e�N�X�`���؂���UV���W
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;


	//���_�f�[�^
	Vertex2D v[] =
	{
		{D3DXVECTOR4(dx - 0.5f,  dy - 0.5f,1.0f,1.0f),        g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dx + dw - 0.5f, dy - 0.5f,1.0f,1.0f),    g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(dx - 0.5f,dy + dh - 0.5f,1.0f,1.0f),     g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dx + dw - 0.5f,dy + dh - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(u1,v1)},
	};




	//�|���S���`��(�ȈՔ�)
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
}


//�X�v���C�g�̕`��(+��])
//�e�N�X�`���؂���T�C�Y�̃|���S���Ŏw����W�ɕ`��
//
//�����FtextureId �@�e�N�X�`���Ǘ��ԍ�
//      dx�@�@�@�@�@�`����W���i������W
//      dy�@�@�@�@�@�`����W���i������W
//      dw          �|���R���T�C�Y�̕�
//      dh�@�@�@�@�@�|���R���T�C�Y�̍���
//�@�@�@tcx�@�@�@�@ �e�N�X�`���̐؂�����W��
//�@�@�@tcy�@�@�@�@ �e�N�X�`���̐؂�����Wy
//�@�@�@tcw�@�@�@�@ �e�N�X�`���̐؂��蕝
//�@�@�@tch�@�@�@�@ �e�N�X�`���̐؂��蕝
//      cx          ��]�̒��S���W��
//      cy          ��]�̒��S���W��
//      angle       ��]�p�x(���W�A��)
//
void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch,float cx,float cy,float angle)
{
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		MessageBox(NULL, "Device�̎擾�Ɏ��s���܂���", "�G���[", MB_OK);
		return;
	}
	//�f�o�C�X��FVF�̐ݒ������
	g_pDevice->SetFVF(FVF_VERTEX2D);

	//�f�o�C�X�Ƀe�N�X�`���̐ݒ������
	g_pDevice->SetTexture(0, texture_GetTexture(textureId));

	//�|���R���̃T�C�Y�̓e�N�X�`���T�C�Y
	unsigned long w = texture_GetTextureWidth(textureId);

	unsigned long h = texture_GetTextureHeight(textureId);

	//�e�N�X�`���؂���UV���W
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;

	

	//���_�f�[�^
	Vertex2D v[] =
	{
		{D3DXVECTOR4(   - 0.5f,   - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dw - 0.5f,   -0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(-0.5f,dh - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dw - 0.5f,dh - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(u1,v1)},
	};

	//���s�ړ��s��
	D3DXMATRIX mtxTranslationC;
	D3DXMatrixTranslation(&mtxTranslationC, -cx, -cy, 0.0f);

	//�߂�ړ��s��
	D3DXMATRIX mtxTranslationI;
	D3DXMatrixTranslation(&mtxTranslationI, cx+dx, cy+dy, 0.0f);

	//��]�s��
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation, angle);

	//�g��s��
	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, 2.0f, 2.0f, 1.0f);

	//�s��̍���
	D3DXMATRIX mtxWorld;
	mtxWorld = mtxTranslationC * mtxRotation * mtxTranslationI;

	//���W�ϊ�
	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&v[i].Position, &v[i].Position, &mtxWorld);
	}

	

	//�|���S���`��(�ȈՔ�)
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
}