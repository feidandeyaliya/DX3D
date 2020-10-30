#include"texture.h"
#include"sprite.h"
#include"scene.h"
#include"game.h"
#include"Title.h"
#include"result.h"

static Scene g_NowScene = SCENE_GAME;
static Scene g_NextScene = SCENE_GAME;

typedef void(*SceneFunction)(void);

static const SceneFunction g_pSceneInitialize[] = 
{ 
	Title_Initialize,
	Game_Initialize,
	Result_Initialize,
};

static const SceneFunction g_pSceneUpdate[] =
{
	Title_Update,
	Game_Update,
	Result_Update,
};

static const SceneFunction g_pSceneDraw[] =
{
	Title_Draw,
	Game_Draw,
	Result_Draw,
};

static const SceneFunction g_pSceneFinalize[] =
{
	Title_Finalize,
	Game_Finalize,
	Result_Finalize,
};

void Scene_Initialize(void)
{
	g_pSceneInitialize[g_NowScene]();
}
void Scene_Update(void)
{
	g_pSceneUpdate[g_NowScene]();
}
void Scene_Draw(void)
{
	g_pSceneDraw[g_NowScene]();
}
void Scene_Finalize(void)
{
	g_pSceneFinalize[g_NowScene]();
}

void Scene_Change(Scene nextScene)
{
	g_NextScene = nextScene;
}
void Scene_ExecuteChange(void)
{
	if (g_NowScene == g_NextScene)
		return;

	Scene_Finalize();
	g_NowScene = g_NextScene;
	Scene_Initialize();
}