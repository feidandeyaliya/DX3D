#include"game_enemy.h"
#include "collision.h"
#include "explosion.h"
#include "sound.h"
#include "scene.h"
#include "game_enemy.h"
#include "game_player.h"
#include"Game_Bullet.h"

void GameJudgment_Initialize(void)
{
}
void GameJudgment_Update(void)
{
	//弾と敵との当たり判定
	for (int ac = 0; ac < ENEMY_MAX; ac++)
	{
		for(int bc = 0; bc < BULLET_MAX; bc++)
		{
			//敵と弾の有効か調べる
			if (GameBullet_IsEnable(bc) && GameEnemy_IsEnable(ac))
			{
				if (Collision_CircleAndCircleHit(&Game_Bullet_GetCollision(bc), &Game_Enemy_GetCollision(ac)))
				{
					GameEnemy_Disable(ac);
					GameBullet_Disable(bc);
					Explosion_Set(Game_Enemy_GetCollision(ac).center.x, Game_Enemy_GetCollision(ac).center.y);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);

				}
			}
		}
		if (GameEnemy_IsEnable(ac))
		{
			if (Collision_CircleAndCircleHit(&GamePlayer_Position(), &Game_Enemy_GetCollision(ac)))
			{
				GameEnemy_Disable(ac);
				Explosion_Set(Game_Enemy_GetCollision(ac).center.x, Game_Enemy_GetCollision(ac).center.y);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
				if (GameBoss_getHP() > 0)
					GamePlayer_damage();
			}
		}
	}
	for (int bc = 0; bc < BULLET_MAX; bc++)
	{
		//敵と弾の有効か調べる
		if (GameBullet_IsEnable(bc) && GameBoss_IsEnable())
		{
			if (Collision_CircleAndCircleHit(&Game_Bullet_GetCollision(bc), &Game_Boss_GetCollision()))
			{
				GameEnemy_damage();
				GameBullet_Disable(bc);
				GameBullet_Disable(bc);
				Explosion_Set(Game_Boss_GetCollision().center.x, Game_Boss_GetCollision().center.y);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);

			}
		}
	}
		
	//両方が有効だったら当たり判定する

	//当たってら

	//敵と弾を無効する
	
	
}