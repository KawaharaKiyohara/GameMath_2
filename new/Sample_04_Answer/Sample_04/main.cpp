#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"
#include <algorithm>
#include <GameCamera.h>
#include "Enemy.h"

///////////////////////////////////////////////////////////////////
//�N���X�̃C���X�^���X���O���[�o���ȗ̈�ɒu���ꍇ��
//���I�m�ۂ������ق����ǂ��B
//�Ȃ����H
//  ->�A�v���P�[�V�������N�������Ƃ��ɃR���X�g���N�^���Ă΂�邩��B
//    ->�Ȃ�̖�肪����H
//      ->�G���W���̏������̑O�ɃR���X�g���N�^���Ă΂��ƍ���I
//        ->�Ȃ����邩�킩��Ȃ��l�́APlayer hogehoge;���R�����g�A�E�g���āA�v���O���������s���Ă݂悤�I
//          ->�N���b�V�������I
///////////////////////////////////////////////////////////////////

//�N���b�V�����������l�́APlayer hogehoge�̃R�����g�A�E�g���O���Ă݂悤�B
//Player hogehoge;
//�v���C���[
Player* player = nullptr;
//�Q�[���J�����B
GameCamera* gameCamera = nullptr;
//���x�����������B
Level* level = nullptr;;

std::vector< Enemy* > enemyList;		//�G�l�~�[�̃��X�g�B
///////////////////////////////////////////////////////////////////
//�Q�[���̏���������
///////////////////////////////////////////////////////////////////
void InitGame()
{
	//�v���C���[�̏������B
	player = new Player;
	player->SetPosition({ 30.0f, 0.0f, 0.0f });

	//���x�����\�z����B
	level = new Level;
	level->Init(L"Assets/level/stage_00.tkl", [&](LevelObjectData& objData)->bool {
		if (wcscmp(objData.name, L"enemy") == 0) {
			//�G�l�~�[�I�I�I
			auto enemy = new Enemy( objData.position, objData.rotation, player);
			enemyList.push_back(enemy);
			return true;
		}
		return false;
	});

	gameCamera = new GameCamera();
	gameCamera->SetPlayer(player);
}
///////////////////////////////////////////////////////////////////
//�Q�[���̍X�V�����B
//���W�̍X�V�Ƃ��̏����͂����ŌĂяo���Ƃ悢�����H
///////////////////////////////////////////////////////////////////
void UpdateGame()
{
	//�Q�[���p�b�h�̍X�V�B	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	//�����G���W���̍X�V�B
	g_physics.Update();
	//�v���C���[�̍X�V�B
	player->Update();
	gameCamera->Update();
	//Enemy���X�V�B
	for (auto& enemy : enemyList) {
		enemy->Update();
	}
}
///////////////////////////////////////////////////////////////////
// �Q�[���̕`�揈���B
// �`��ƍX�V�͕����Ă��ق����ǂ������H
///////////////////////////////////////////////////////////////////
void RenderGame()
{
	//�`��J�n�B
	g_graphicsEngine->BegineRender();

	//�v���C���[�̕`��B
	player->Draw();
	//���x����`��B
	level->Draw();
	//Coin��`��B
	for (auto& enemy : enemyList) {
		enemy->Draw();
	}

	//�`��I���B
	g_graphicsEngine->EndRender();
}

///////////////////////////////////////////////////////////////////
// �Q�[���̏I�������B
///////////////////////////////////////////////////////////////////
void TermnateGame()
{
	//���I�Ɋm�ۂ����C���X�^���X��j���B
	delete player;
	delete level;
	delete gameCamera;
	for (auto& enemy : enemyList) {
		delete enemy;
	}
}
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���G���W���̏������B
	InitGameEngine(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	//�Q�[���̏������B
	InitGame();
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�Q�[���̍X�V�B
		UpdateGame();
		//�Q�[���̕`�揈���B
		RenderGame();
	}
	//�Q�[���̏I������
	TermnateGame();
}