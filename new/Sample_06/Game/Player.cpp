
#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/sound/tkSoundSource.h"

namespace {
	const CVector3 START_POS = { -1088.16589f, 67.87, -867.0f };
}
class CSoundEmitter : public IGameObject {
private:
	float m_timer = 0.0f;
	float m_emitTime = 0.0f;
	std::string m_filePath;
public:
	void Init(float emitTime, const char* filePath)
	{
		m_emitTime = emitTime;
		m_filePath = filePath;
	}
	void Update()
	{
		m_timer += GameTime().GetFrameDeltaTime();
		if (m_timer > m_emitTime) {
			prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
			s->Init(m_filePath.c_str());
			s->Play(false);
			DeleteGO(this);
		}
	}
};
void Player::InitLight()
{
	m_charaLight = NewGO<prefab::CDirectionLight>(0);
	m_charaLight->SetDirection({ 1.0f, 0.0f, 0.0f });
	m_charaLight->SetLightingMaterialIDGroup(1 << enMaterialID_Chara);
	m_charaLight->SetColor({ 10.0f, 10.0f, 10.0f, 1.0f });
}
bool Player::Start()
{
	//モデルデータをロード。
	m_skinModelData.Load(L"modelData/unityChan.cmo");
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);
	m_normalMap.CreateFromDDSTextureFromFile(L"sprite/utc_nomal.dds");
	m_specMap.CreateFromDDSTextureFromFile(L"sprite/utc_spec.dds");
	m_skinModel.FindMaterial([&](CModelEffect* material) {
		//マテリアルＩＤを設定する。
		material->SetMaterialID(enMaterialID_Chara);
		//法線マップとスペキュラマップを設定。
		material->SetNormalMap(m_normalMap.GetBody());
		material->SetSpecularMap(m_specMap.GetBody());
	});

	m_animClip[enAnimationClip_idle].Load(L"animData/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"animData/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"animData/run.tka");
	m_animClip[enAnimationClip_jump].Load(L"animData/jump.tka");
	m_animClip[enAnimationClip_damage].Load(L"animData/damage.tka");
	m_animClip[enAnimationClip_KneelDown].Load(L"animData/KneelDown.tka");
	m_animClip[enAnimationClip_Clear].Load(L"animData/Clear.tka");
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	m_position = START_POS;
	m_prevPosition = m_position;
	m_animClip[enAnimationClip_jump].SetLoopFlag(false);
	m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
	m_animClip[enAnimationClip_Clear].SetLoopFlag(false);
	m_animation.Init(m_skinModel, m_animClip, enAnimationClip_num);
	m_animation.Play(enAnimationClip_idle);
	
	m_charaCon.Init(20.0f, 68.0f, m_position);
	m_game = FindGO<Game>("Game");
	return true;
}
void Player::Turn()
{
	CVector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	if (moveSpeedXZ.LengthSq() < 1.0f) {
		return;
	}
	m_rotation.SetRotation(CVector3::Up, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
}
void Player::UpdateFSM()
{
	
	static float JUMP_SPEED = 630.0f;
	switch (m_state) {
	case enState_Idle:

		Move();
		if (Pad(0).IsTrigger(enButtonA)) {
			m_charaCon.Jump();
			m_moveSpeed.y = JUMP_SPEED;
			m_state = enState_Jump;
		}else if (m_moveSpeed.LengthSq() > 0.001f) {
			//入力がある。
			m_state = enState_Run;
		}
		break;
	case enState_Run:
		Move();
		
		if (m_moveSpeed.LengthSq() < 1.0f * 1.0f) {
			//入力がなくなった。
			m_state = enState_Idle;
		}else if (Pad(0).IsTrigger(enButtonA)) {
			m_charaCon.Jump();
			//この時点でのXZ方向の速度を記憶しておく。
			m_moveSpeedWhenStartJump = m_moveSpeed.Length();
			m_moveSpeed.y = JUMP_SPEED;
			m_state = enState_Jump;
		}
		break;
	case enState_Jump:
		Move();
		if (!m_charaCon.IsJump()) {
			if (m_moveSpeed.LengthSq() < 1.0f * 1.0f) {
				//入力がなくなった。
				m_state = enState_Idle;
			}
			else {
				m_state = enState_Run;
			}
		}
		break;
	case enState_GameOver: {
		if (!m_animation.IsPlaying()) {
			m_game->NotifyRestart();
		}

	}break;
	case enState_WaitStartGameClear:
		m_timer += GameTime().GetFrameDeltaTime();
		if (m_timer > 0.5f) {
			
			CSoundEmitter* emitter = NewGO<CSoundEmitter>(0);
			emitter->Init(0.3f, "sound/uni1518.wav");
			m_state = enState_GameClear;
			m_timer = 0.0f;
		}
		
		break;
	case enState_GameClear: {
		
	}break;
	}
}
void Player::Move()
{
	//【ハンズオン】加速度を使ってキャラを動かす。
	//step-1 コントローラーの入力から加速度を作成する。
	

	//step-2 速度に加速度を加える。
	

	//step-3 座標に速度を加える。
	

}
void Player::AnimationController()
{
	if (m_state == enState_Jump) {
		m_animation.Play(enAnimationClip_jump, 0.2f);
	}
	else if( m_state == enState_Run
		|| m_state == enState_Idle
	){
		if (m_moveSpeed.LengthSq() > 6.0f * 6.0f) {
			//走りモーション。
			m_animation.Play(enAnimationClip_run, 0.2f);
		}
		else if (m_moveSpeed.LengthSq() > 1.0f * 1.0f) {
			//走りモーション。
			m_animation.Play(enAnimationClip_walk, 0.2f);
		}
		else {
			//待機モーション
			m_animation.Play(enAnimationClip_idle, 0.2f);
		}
	}
	else if (m_state == enState_GameClear) {
		m_animation.Play(enAnimationClip_Clear);
	}
	else if (m_state == enState_GameOver) {
		m_animation.Play(enAnimationClip_KneelDown);
	}
}

void Player::Update()
{
	AnimationController();

	Turn();
	
	if (m_position.y < -1000.0f && !m_game->IsGameOver()) {
		//初期位置に戻る。
		Game* game = FindGO<Game>("Game");
		game->NotifyGameOver();
	}

	UpdateFSM();
	
	//キャラクタを移動させる。
	if (m_charaCon.IsOnGround()) {
		m_moveSpeed.y = 0.0f;
	}
	//キャラライトはカメラの方向にする。
	if (m_charaLight) {
		m_charaLight->SetDirection(MainCamera().GetForward());
	}
	CQuaternion qRot = CQuaternion::Identity;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);	//寝てるので起こす。
													//ワールド行列を更新。
	CQuaternion q = m_rotation;
	q.Multiply(qRot);
	m_skinModel.Update(m_position, q, CVector3::One);

	CMatrix mRot;
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];

	m_prevPosition = m_position;
}

void Player::NotifyGameOver()
{
	CSoundEmitter* emitter = NewGO<CSoundEmitter>(0);
	emitter->Init(0.6f, "sound/uni1482.wav");
	m_state = enState_GameOver;
}

void Player::NotifyGameClear()
{
	m_state = enState_WaitStartGameClear;
}
void Player::NotifyRestart()
{
	m_animation.Play(enAnimationClip_idle);
	m_state = enState_Idle;
	m_position = START_POS;
	m_prevPosition = m_position;
	m_charaCon.SetPosition(m_position);
	m_moveSpeed = CVector3::Zero;
	
}
void Player::OnDestroy()
{
	DeleteGO(m_charaLight);
}

void Player::Render(CRenderContext& rc)
{
	//描画。
	m_skinModel.Draw(
		rc, 
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix()
	);

}