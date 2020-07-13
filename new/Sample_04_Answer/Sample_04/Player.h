#pragma once
#include "character/CharacterController.h"

class Player
{
public:
	Player();
	~Player();
	void Update();
	void Draw();
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition() 
	{
		return m_position;
	}
private:
	SkinModel m_model;									//�X�L�����f���B
	Animation m_animation;								//�A�j���[�V�����B
	AnimationClip m_animationClips[2];					//�A�j���[�V�����N���b�v�B
	CVector3 m_position = CVector3::Zero();				//���W�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	//Hands-On 3 �L�����N�^�[�R���g���[���[��ǉ��B
	CharacterController m_charaCon;
};

