#define _CRT_SECURE_NO_WARNINGS

#include "texture.h"
#include "debugPrintf.h"

#include <d3dx9.h>
#include <string.h>
#include "mydirect3d.h"

#define TEXTURE_MAX (1024) //�e�N�X�`���Ǘ��ő吔

//�e�N�X�`���Ǘ��e�[�u���\����
typedef struct Texture_tag
{
	LPDIRECT3DTEXTURE9 pTexture;
	unsigned long width;
	unsigned long height;
	char filename[TEXTURE_FILENAME_MAX];
}Texture;

//�O���[�o���ϐ��錾
//�e�N�X�`���Ǘ��e�[�u��
static Texture g_Texture[TEXTURE_MAX];


//�e�N�X�`���Ǘ����W���[���̏�����
void texture_Initialize(void)
{
	//�e�N�X�`���Ǘ��e�[�u���̏�����
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i].pTexture = NULL;
		g_Texture[i].width = 0;
		g_Texture[i].height = 0;
		g_Texture[i].filename[0] = 0;
	}
}

//�e�N�X�`���Ǘ����W���[���̏I������
void texture_Finalize(void)
{

}

//�e�N�X�`���t�@�C���̓ǂݍ��ݗ\��
//
//�����FpFileName...�t�@�C����
//
//�߂�l�F�e�N�X�`���Ǘ��ԍ�
//�@�@�@�@�ő�Ǘ����𒴂��Ă����ꍇ��INVALID_TEXTURE_ID
//
int texture_SetTextureLoadFile(const char* pFileName)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		//�e�[�u�����󂢂Ă�����X�L�b�v
		if (g_Texture[i].filename[0] == 0)
		{
			continue;
		}
		if (strcmp(pFileName, g_Texture[i].filename) == 0)
		{
			//�\�񂳂�Ă���
			return i;
		}
	}

	//�V�K�\��
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		//�e�[�u�����g�p����������X�L�b�v
		if (g_Texture[i].filename[0] != 0)
		{
			continue;
		}
		strcpy(g_Texture[i].filename, pFileName);

		return i;
	}
	return TEXTURE_INVALID_ID;
}

//�e�N�X�`���̓ǂݍ���
//
//�\�񂪂���Ă���t�@�C����ǂݍ��݂܂�
//
//�߂�l�F�ǂݍ��߂Ȃ������t�@�C����
//        
int texture_Load(void)
{
	int err_count = 0;


	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		return -1;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i].filename[0] == 0)
		{
			//��̃e�[�u���Ȃ̂ŃX�L�b�v
			continue;
		}
		if (g_Texture[i].pTexture != NULL)
		{
			//���łɓǂݍ��܂�Ă���
			continue;
		}

		//�e�N�X�`���̓ǂݍ���
		HRESULT hr = D3DXCreateTextureFromFile(g_pDevice, g_Texture[i].filename, &g_Texture[i].pTexture);
		if (FAILED(hr))
		{
			DebugPrintf("�ǂݍ��߂Ȃ������e�N�X�`���t�@�C��:[%s}\n", g_Texture[i].pTexture);
			err_count++;
		}
		else
		{
			//�e�N�X�`���̉𑜓x�i���A�����j�̒���
			D3DXIMAGE_INFO info;
			D3DXGetImageInfoFromFile(g_Texture[i].filename, &info);
			g_Texture[i].height = info.Height;
			g_Texture[i].width = info.Width;
		}
	}
	return err_count;//�ǂݍ��߂Ȃ�������
}

//�e�N�X�`���̕������
//
//�����FtextureIds[]�c���������textureId��������int�^�z��̐擪�A�h���X
//�@�@�@count�@�@ �@�c�������e�N�X�`���̐�
//
void texture_Release(int textureIds[], int count)//int textureIds[]=>int* pTextureIds
{
	for (int i = 0; i < count; i++)
	{
		if (g_Texture[textureIds[i]].pTexture)
		{
			g_Texture[textureIds[i]].pTexture->Release();
			g_Texture[textureIds[i]].pTexture = NULL;
		}
		g_Texture[textureIds[i]].filename[0] = 0;
		g_Texture[textureIds[i]].height = 0;
		g_Texture[textureIds[i]].width = 0;
	}
}

//�e�N�X�`���̑S���
void texture_AllRelease(void)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i].pTexture)
		{
			g_Texture[i].pTexture->Release();
			g_Texture[i].pTexture = NULL;
		}
		g_Texture[i].filename[0] = 0;
		g_Texture[i].height = 0;
		g_Texture[i].width = 0;
	}

}

//�e�N�X�`���̕��̎擾
//
//�����F�e�N�X�`���̊Ǘ��ԍ�
//
//�߂�l�F�e�N�X�`���̕�
//
unsigned long texture_GetTextureWidth(int textureId)
{
	return g_Texture[textureId].width;
}

//�e�N�X�`���̍����̎擾
//
//�����F�e�N�X�`���̊Ǘ��ԍ�
//
//�߂�l�F�e�N�X�`���̍���
//
unsigned long texture_GetTextureHeight(int textureId)
{
	return g_Texture[textureId].height;
}

//�e�N�X�`���C���^�[�t�F�[�X�̃|�C���^�擾
//
//�����F�e�N�X�`���Ǘ��ԍ�
//
//�߂�l�F�e�N�X�`���C���^�[�t�F�[�X�|�C���^
//        �ǂݍ��߂Ă��Ȃ��܂��͕s���ȊǗ��ԍ��������ꍇNULL
//
LPDIRECT3DTEXTURE9 texture_GetTexture(int textureId)
{
	return g_Texture[textureId].pTexture;
}