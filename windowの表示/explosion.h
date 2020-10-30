#ifndef EXPLOSION_H
#define EXPLOSION_H

#define Explosion_MAX (1000)
//爆発の初期化
void Explosion_Initialize(void);

//爆発の終了処理
void Explosion_Finalize(void);

//爆発の更新
void Explosion_Update(void);

//爆発の描画
void Explosion_Draw(void);

//爆発の生成
void Explosion_Set(float x, float y);
#endif // !EXPLOSION_H
