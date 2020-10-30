#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d9.h>

#define TEXTURE_FILENAME_MAX (64)//�e�N�X�`���t�@�C�����ő啶����
#define TEXTURE_INVALID_ID   (-1)//�����ȃe�N�X�`���Ǘ��ԍ�


//�e�N�X�`���Ǘ����W���[���̏�����
void texture_Initialize(void);

//�e�N�X�`���Ǘ����W���[���̏I������
void texture_Finalize(void);

//�e�N�X�`���t�@�C���̓ǂݍ��ݗ\��
//
//�����FpFileName...�t�@�C����
//
//�߂�l�F�e�N�X�`���Ǘ��ԍ�
//�@�@�@�@�ő�Ǘ����𒴂��Ă����ꍇ��INVALID_TEXTURE_ID
//
int texture_SetTextureLoadFile(const char* pFileName);

//�e�N�X�`���̓ǂݍ���
//
//�\�񂪂���Ă���t�@�C����ǂݍ��݂܂�
//
//�߂�l�F�ǂݍ��߂Ȃ������t�@�C����
//
int texture_Load(void);

//�e�N�X�`���̕������
//
//�����FtextureIds[]�c���������textureId��������int�^�z��̐擪�A�h���X
//�@�@�@count�@�@ �@�c�������e�N�X�`���̐�
//
void texture_Release(int textureIds[], int count);//int textureIds[]=>int* pTextureIds

//�e�N�X�`���̑S���
void texture_AllRelease(void);

//�e�N�X�`���̕��̎擾
//
//�����F�e�N�X�`���̊Ǘ��ԍ�
//
//�߂�l�F�e�N�X�`���̕�
//
unsigned long texture_GetTextureWidth(int textureId);

//�e�N�X�`���̍����̎擾
//
//�����F�e�N�X�`���̊Ǘ��ԍ�
//
//�߂�l�F�e�N�X�`���̍���
//
unsigned long texture_GetTextureHeight(int textureId);

//�e�N�X�`���C���^�[�t�F�[�X�̃|�C���^�擾
//
//�����F�e�N�X�`���Ǘ��ԍ�
//
//�߂�l�F�e�N�X�`���C���^�[�t�F�[�X�|�C���^
//        �ǂݍ��߂Ă��Ȃ��܂��͕s���ȊǗ��ԍ��������ꍇNULL
//
LPDIRECT3DTEXTURE9 texture_GetTexture(int textureId);

#endif