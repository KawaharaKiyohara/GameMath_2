#include "stdafx.h"
#include "Player.h"
#include "GameTime.h"

Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	//Unity�����̓A�j���[�V�����𗬂���Y�A�b�v�ɂȂ�̂ŁA
	//enFbxUpAxisY���w�肵�Ă���B
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
	//�A�j���[�V�����N���b�v�����[�h�B
	m_animationClips[enAnimationClip_idle].Load(L"Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_run].Load(L"Assets/animData/run.tka");

	//���[�v�t���O��ݒ肷��B
	m_animationClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_run].SetLoopFlag(true);

	//�A�j���[�V���������[�h�B
	m_animation.Init(m_model, m_animationClips, enNumAnimationClip);
}


Player::~Player()
{
}

void Player::Update()
{
	//�Q�[���p�b�h����ړ��x�N�g�����쐬����B
	CVector3 move = CVector3::Zero();
	move.x = g_pad[0].GetLStickXF();
	move.z = g_pad[0].GetLStickYF();

	//Step - 4 �v���C���[�̈ړ������ԃx�[�X�ɕύX����B
	move *= 5.0f;

	//�ړ��x�N�g���𑫂��Z����B
	m_position += move;

	//��]�N�H�[�^�j�I�����v�Z����B
	if (move.Length() > 0.01f) {
		//�Q�[���p�b�h�̓��͂�����B
		m_rotation.SetRotation(CVector3::AxisY(), atan2(move.x, move.z));
		//����A�j���[�V�����𗬂��B
		m_animation.Play(enAnimationClip_run);
	}
	else {
		//�ҋ@�A�j���[�V�����𗬂��B
		m_animation.Play(enAnimationClip_idle);
	}
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	//�A�j���[�V������i�߂�B
	//Step-6 �A�j���[�V�����̍Đ����t���[�����[�g�̕ύX�ɑΉ�����B
	m_animation.Update(1.0f/60.0f);
}
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}