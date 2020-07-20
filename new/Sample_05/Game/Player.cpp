#include "stdafx.h"
#include "Player.h"
#include "GameTime.h"

Player::Player()
{
	//cmoファイルの読み込み。
	//Unityちゃんはアニメーションを流すとYアップになるので、
	//enFbxUpAxisYを指定している。
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
	//アニメーションクリップをロード。
	m_animationClips[enAnimationClip_idle].Load(L"Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_run].Load(L"Assets/animData/run.tka");

	//ループフラグを設定する。
	m_animationClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_run].SetLoopFlag(true);

	//アニメーションをロード。
	m_animation.Init(m_model, m_animationClips, enNumAnimationClip);
}


Player::~Player()
{
}

void Player::Update()
{
	//ゲームパッドから移動ベクトルを作成する。
	CVector3 move = CVector3::Zero();
	move.x = g_pad[0].GetLStickXF();
	move.z = g_pad[0].GetLStickYF();

	//Step - 4 プレイヤーの移動を時間ベースに変更する。
	move *= 5.0f;

	//移動ベクトルを足し算する。
	m_position += move;

	//回転クォータニオンを計算する。
	if (move.Length() > 0.01f) {
		//ゲームパッドの入力がある。
		m_rotation.SetRotation(CVector3::AxisY(), atan2(move.x, move.z));
		//走りアニメーションを流す。
		m_animation.Play(enAnimationClip_run);
	}
	else {
		//待機アニメーションを流す。
		m_animation.Play(enAnimationClip_idle);
	}
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	//アニメーションを進める。
	//Step-6 アニメーションの再生もフレームレートの変更に対応する。
	m_animation.Update(1.0f/60.0f);
}
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}