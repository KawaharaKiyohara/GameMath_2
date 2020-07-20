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
		//���t���[��������ƂÂ񂷁B
		CQuaternion addRot;
		//Y�������0.01(���W�A���P��)��]����N�H�[�^�j�I�����쐬����B
		addRot.SetRotation(CVector3::AxisY(), 0.01f);
		//�G�l�~�[�̉�]��addRot�����Z����B
		m_rotation.Multiply(addRot);
		//�y�n���Y�I���|�P�z�G�l�~�[�Ɏ���p���������Ă݂�B
		//step-1 �G���̑O������(enemyForward)�����߂�B
		CVector3 enemyForward = CVector3::AxisZ();
		m_rotation.Multiply(enemyForward);

		//step-2 �G������v���C���[�ɐL�т�x�N�g��(toPlayerDir)�����߂�B
		CVector3 toPlayerDir = m_player->GetPosition() - m_position;
		//���K�����s���O�ɁA�v���C���[�܂ł̋��������߂Ă����B
		float toPlayerLen = toPlayerDir.Length();
		//���K���I
		toPlayerDir.Normalize();

		//step-3 enemyForward��toPlayerDir�̓��ς��v�Z����B
		float d = enemyForward.Dot(toPlayerDir);


		//step-4 ���ς̌��ʂ�acos�֐��ɓn���āAenemyForward��toPlayerDir�̂Ȃ��p�x�����߂�B
		float angle = acos(d);

		//step-5 ����p����
		//fabsf�͐�Βl�����߂�֐��I
		//�p�x�̓}�C�i�X�����݂��邩��A��Βl�ɂ���B
		if (fabsf(angle) < CMath::DegToRad(45.0f) //�p�x�̔���
			&& toPlayerLen < 200.0f               //�����̔���
			) {
			//��Ԃ�ǐՏ�Ԃɂ���B
			m_state = eState_Tracking;
		}


	}
	else if (m_state == eState_Tracking) {
		CVector3 toPlayer = m_player->GetPosition() - m_position;
		//toPlayer�𐳋K�����āA�傫��1�ɂ���B
		toPlayer.Normalize();
		m_moveSpeed.x = toPlayer.x * 200.0f;
		m_moveSpeed.z = toPlayer.z * 200.0f;
		m_moveSpeed.y -= 20.0f;
		m_position = m_charaCon.Execute(
			1.0f / 60.0f,
			m_moveSpeed
		);

		//�y�n���Y�I���z�G�l�~�[��i�s�����Ɍ�����B
		//step-1 atan2���g���āA�i�s�����Ɍ����邽�߂̊p�x�����߂�B
		float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);

		//step-2 ���߂��p�x���g���āA��]�N�H�[�^�j�I�������߂�B
		m_rotation.SetRotation(
			CVector3::AxisY(),
			angle
		);


	}
	//���[���h�s������߂�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 3.0f, 3.0f, 3.0f });

}
void Enemy::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}
