/*==================================================================================================

	�f�o�b�O�t�H���g���W���[��[debug_font.h]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#pragma once
#ifndef DEBUG_FONT_H
#define DEBUG_FONT_H

//�f�o�b�O�t�H���g���W���[���̏�����
void DebugFont_Initialize(void);

//�f�o�b�O�t�H���g���W���[���̏I������
void DebugFont_Finalize(void);

//�f�o�b�O�t�H���g�̕\��
//
//�����Fdx,dy    �f�o�b�O������ւ̕`����W
//      pSting   �f�o�b�O������ւ̃|�C���^
//
void DebugFont_Draw(float dx, float dy, const char* pString);

#endif // !DEBUG_FONT_H
