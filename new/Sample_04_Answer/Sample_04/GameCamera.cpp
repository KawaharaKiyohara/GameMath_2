#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 300.0f, 800.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
}


GameCamera::~GameCamera()
{
}
void GameCamera::Update()
{
	//現在の注視点から視点へのベクトルを求めるよ。
	auto toCameraPos = g_camera3D.GetPosition() - g_camera3D.GetTarget();
	//新しい注視点を求める。
	auto newTarget = m_player->GetPosition();
	//Y方向にちょっと上げる。
	newTarget.y += 20.0f;
	//新しい視点を計算する。
	auto newPositin = newTarget + toCameraPos;

	g_camera3D.SetTarget(newTarget);
	g_camera3D.SetPosition(newPositin);
	g_camera3D.Update();
}
