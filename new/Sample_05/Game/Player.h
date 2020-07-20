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
		enAnimationClip_idle,	//待機アニメーション。
		enAnimationClip_run,	//走りアニメーション。
		enNumAnimationClip		//アニメーションの数。
	};
	SkinModel m_model;		//スキンモデル。
	Animation m_animation;	//アニメーション。
	AnimationClip m_animationClips[enNumAnimationClip];
	CVector3 m_position = CVector3::Zero();				//座標。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転クォータニオン。
};

