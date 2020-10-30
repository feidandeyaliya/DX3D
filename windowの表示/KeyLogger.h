/*==================================================================================================

	キー入力の記録制御[keylogger.h]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#ifndef KEYLOGGER_H
#define KEYLOGGER_H

//有効キーの列挙型
typedef enum KeyloggerKey_tag
{
	KL_FRONT,
	KL_BACK,
	KL_LEFT,
	KL_RIGHT,
	KL_UP,
	KL_DOWN,
	KL_TURN_LEFT,
	KL_TURN_RIGHT,
	KL_TURN_UP,
	KL_TURN_DOWN,
	KL_CENTERTURN_LEFT,
	KL_CENTERTURN_RIGHT,
	KL_SPACE,
	KL_MAX
}KeyloggerKey;

void keylogger_Initialize(void);

void keylogger_Finalize(void);

void keylogger_Update(void);

//キー入力状態の取得
//
//引数：
//
//戻り値：押されたらtrue
//
bool keylogger_Press(KeyloggerKey kl);

//キー入力状態の取得(押した瞬間)
//
//引数：
//
//戻り値：押した瞬間true
//
bool keylogger_Trigger(KeyloggerKey kl);

//キー入力状態の取得(離した瞬間)
//
//引数：
//
//戻り値：離した瞬間true
//
bool keylogger_Release(KeyloggerKey kl);


void keylogger_RecordStart(int frame_max);
void keylogger_RecordEnd(void);
void keylogger_RecordLoad(void);
void keylogger_RecordPlay(void);
bool keylogger_IsRecordPlay(void);


#endif // !KEYLOGGER_H
