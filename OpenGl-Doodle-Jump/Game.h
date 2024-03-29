
#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include <random>
#include <cstdlib>
#include <ctime>

#include "Common.h"
#include "Mesh.h"
#include "Shader.h"
#include "Shapes.h"
#include "Texture.h"
#include "MatrixTransformation.h"
#include "Font.h"
#include "Dependencies\FMOD\fmod.hpp"

using std::cout;
using std::uniform_real_distribution;
using std::uniform_int_distribution;

enum class State { PLAY, MAIN_MENU, GAME_OVER, EXIT, TOTAL_STATES };
enum class PlatformType { CONCRETE, SNOW, TOTAL_PLATFORM_TYPES };

struct PlatformPos
{
	float m_x;
	float m_y;
	int m_type;
};

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	SDL_Window* m_MainWindow;
	State GameState;

	int InitSDL();

	void GameLoop();
	void ProcessInput();
	void UpdateGameComponents();
	void Render();
	void RenderMainMenu();
	void RenderBackground();
	void RenderVictoryScreen();
	void RenderPlatforms();
	void RenderPlayer();
	void RenderEnemy();
	void RenderProjectile();
	void RenderGameOverScene();
	void RestartGame();
	void UpdateEnemySpawnRate();

	void CapFrameRate(Uint32);

	bool InitFmod();
	bool LoadAudio();

	Shapes shapes;
	Shader m_SimpleShader;
	Mesh m_Player, m_enemy, m_projectile, m_Background, m_Platform;
	Texture m_texPlayer, m_texMainMenu, m_texVictoryMenu, m_texEnemy[2], m_texSnow, m_texProjectile, m_texBackground[2], m_texPlatform, m_texGameoverScene;
	Camera m_Camera;
	MatrixTransform m_PlayerTransformation, m_enemyTransformation, m_projectileTransformation, m_BackgroundTransformation, m_PlatformTransformation, m_mainMenuTransformation;
	PlatformPos m_plat[16];
	Text* m_Text = nullptr;

	FMOD::System* m_AudioManager;
	FMOD::Sound* m_JumpSound, *m_mainThemeOne, *m_winterTheme, *m_quake, *m_growl, *m_fire;
	FMOD::Channel* m_FmodChannel;

	unsigned short int m_Score, m_NumOfPlatforms = 8;
	unsigned short int m_activateGrowlingSound = 0;
	float m_enemySpeed;
	double m_playerVelocity;
	float dx = 0.0f, dy = 0.0f;

	Uint32 m_StartingTick;

	bool m_isAudioActive = true;
	bool m_isMovingRight = false;
	bool m_isMovingLeft = false;
	bool m_isGameover = false;
	bool m_bEnemyChangeDir = false;
	bool m_bShooting = false;
	bool m_bShake = false;
	bool m_AlternateScreenMode = false;
	bool m_bDoOnce[3] = { false, false, false };
	bool m_bWin = false;
};

#endif // !__GAME_H__