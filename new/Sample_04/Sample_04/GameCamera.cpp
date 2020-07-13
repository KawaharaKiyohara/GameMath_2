#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 300.0f, 800.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
}


GameCamera::~GameCamera()
{
}
void GameCamera::Update()
{
	//���݂̒����_���王�_�ւ̃x�N�g�������߂��B
	auto toCameraPos = g_camera3D.GetPosition() - g_camera3D.GetTarget();
	//�V���������_�����߂�B
	auto newTarget = m_player->GetPosition();
	//Y�����ɂ�����Əグ��B
	newTarget.y += 20.0f;
	//�V�������_���v�Z����B
	auto newPositin = newTarget + toCameraPos;

	g_camera3D.SetTarget(newTarget);
	g_camera3D.SetPosition(newPositin);
	g_camera3D.Update();
}
