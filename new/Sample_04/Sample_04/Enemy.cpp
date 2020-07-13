#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(CVector3 pos, CQuaternion rot, Player* player) :
	m_position(pos),
	m_rotation(rot),
	m_player(player)
{
	m_model.Init(L"Assets/modelData/enemy.cmo");
	m_charaCon.Init(10.0f, 30.0f, m_position);
}
Enemy::~Enemy()
{
}
void Enemy::Update()
{
	if (m_state == eState_Search) {
		//毎フレームちょっとづつ回す。
		CQuaternion addRot;
		//Y軸周りに0.01(ラジアン単位)回転するクォータニオンを作成する。
		addRot.SetRotation(CVector3::AxisY(), 0.01f);
		//エネミーの回転にaddRotを加算する。
		m_rotation.Multiply(addRot);
		//【ハンズオン－１】エネミーに視野角を実装してみる。
		//step-1 敵兵の前方方向(enemyForward)を求める。
		

		//step-2 敵兵からプレイヤーに伸びるベクトル(toPlayerDir)を求める。
		

		//step-3 enemyForwardとtoPlayerDirの内積を計算する。
		

		//step-4 内積の結果をacos関数に渡して、enemyForwardとtoPlayerDirのなす角度を求める。
		

		//step-5 視野角判定
		

	}
	else if (m_state == eState_Tracking) {
		CVector3 toPlayer = m_player->GetPosition() - m_position;
		//toPlayerを正規化して、大きさ1にする。
		toPlayer.Normalize();
		m_moveSpeed.x = toPlayer.x * 200.0f;
		m_moveSpeed.z = toPlayer.z * 200.0f;
		m_moveSpeed.y -= 20.0f;
		m_position = m_charaCon.Execute(
			1.0f / 60.0f,
			m_moveSpeed
		);

		//【ハンズオン】エネミーを進行方向に向ける。
		//step-1 atan2を使って、進行方向に向けるための角度を求める。
		

		//step-2 求めた角度を使って、回転クォータニオンを求める。
		

	}
	//ワールド行列を求める。
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 3.0f, 3.0f, 3.0f });

}
void Enemy::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}
