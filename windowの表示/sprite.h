#ifndef SPRITE_H
#define SPRITE_H

void Sprite_Initialize(void);

void Sprite_Finalaize(void);

//カラー設定
//
//引数：color　ポリゴンカラー
//
void Sprite_Setcolor(D3DCOLOR color);

//スプライトの描画
//テクスチャ切り取りサイズのポリゴンで指定座標に描画
//
//引数：textureId 　テクスチャ管理番号
//      dx　　　　　描画座標ｘ（左上座標
//      dy　　　　　描画座標ｙ（左上座標
//　　　tcx　　　　 テクスチャの切り取り座標ｘ
//　　　tcy　　　　 テクスチャの切り取り座標y
//　　　tcw　　　　 テクスチャの切り取り幅
//　　　tch　　　　 テクスチャの切り取り幅
//

void Sprite_Draw(int textureId, float dx, float dy);

void Sprite_Draw(int textureId, float dx, float dy,int tcx,int tcy,int tcw,int tch);

void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);

void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, float cx, float cy, float angle);


#endif
