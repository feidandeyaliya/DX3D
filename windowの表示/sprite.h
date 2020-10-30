#ifndef SPRITE_H
#define SPRITE_H

void Sprite_Initialize(void);

void Sprite_Finalaize(void);

//�J���[�ݒ�
//
//�����Fcolor�@�|���S���J���[
//
void Sprite_Setcolor(D3DCOLOR color);

//�X�v���C�g�̕`��
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

void Sprite_Draw(int textureId, float dx, float dy);

void Sprite_Draw(int textureId, float dx, float dy,int tcx,int tcy,int tcw,int tch);

void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);

void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, float cx, float cy, float angle);


#endif
