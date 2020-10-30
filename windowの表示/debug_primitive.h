/*==================================================================================================

	デバッグ用図形表示モジュール[debug_Primitive.h]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#ifndef DEBUG_PRIMITIVE_H_
#define DEBUG_PRIMITIVE_H_


void DebugPrimitive_Initialize(void);
void DebugPrimitive_Finalize(void);
void DebugPrimitive_BatchBegin(void);
void DebugPrimitive_BatchDrawCircle(float x,float y,float radius);
void DebugPrimitive_BatchRun(void);

#endif // !DEBUG_PRIMITIVE_H_

