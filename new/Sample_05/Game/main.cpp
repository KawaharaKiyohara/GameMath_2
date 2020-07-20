#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"
#include "Background.h"
#include "GameTime.h"


GameTime g_gameTime;


///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 100.0f, -300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	
	//�v���C���[
	Player player;
	//�w�i�B
	Background bg;
	//�Q�[�����Ԍv���p�̃X�g�b�v�E�H�b�`��ǉ��B
	Stopwatch sw;
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�Q�[�����Ԃ̌v���J�n�B
		sw.Start();

		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		//�v���C���[�̍X�V�B
		player.Update();
		//�v���C���[�̕`��B
		player.Draw();
		//BG�̕`��B
		bg.Draw();
		//�J�����̍X�V�B
		g_camera3D.Update();

		//step-2 16�~���b�X���[�v�����āA�킴�Ə������������Ă݂�B
		Sleep( 0 );
		//�`��I���B
		g_graphicsEngine->EndRender();

		//�Q�[�����Ԃ̌v���I���B
		sw.Stop();
		//���̃t���[���ɂ����������Ԃ��L�����Ă����B
		g_gameTime.PushFrameDeltaTime(sw.GetElapsed());
	}
}