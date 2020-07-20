#pragma once
#include "character/CharacterController.h"

class Player
{
public:
	Player();
	~Player();
	void Update();
	void Draw();
private:
	enum EnAnimationClip {
		enAnimationClip_idle,	//�ҋ@�A�j���[�V�����B
		enAnimationClip_run,	//����A�j���[�V�����B
		enNumAnimationClip		//�A�j���[�V�����̐��B
	};
	SkinModel m_model;		//�X�L�����f���B
	Animation m_animation;	//�A�j���[�V�����B
	AnimationClip m_animationClips[enNumAnimationClip];
	CVector3 m_position = CVector3::Zero();				//���W�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�N�H�[�^�j�I���B
};

