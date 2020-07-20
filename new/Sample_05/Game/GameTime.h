/*!
*@brief	�Q�[�����ԃN���X�B
* �V���O���g���B
*/
#pragma once

#include "Stopwatch.h"
#include <list>

/*!
*@brief	�Q�[�����ԁB
*/
class GameTime{
public:
	/*!
		*@brief	1�t���[���̌o�ߎ��Ԃ��擾(�P�ʁE�b)�B
		*/
	const float GetFrameDeltaTime() const
	{
		return m_frameDeltaTime;
	}
	void PushFrameDeltaTime(float deltaTime)
	{
		m_frameDeltaTimeQue.push_back(deltaTime);
		if (m_frameDeltaTimeQue.size() > 5) {
			float totalTime = 0.0f;
			for (auto time : m_frameDeltaTimeQue) {
				totalTime += time;
			}
			//���ϒl���Ƃ�B
			m_frameDeltaTime = min(1.0f / 30.0f, totalTime / m_frameDeltaTimeQue.size());
			m_frameDeltaTimeQue.pop_front();
		}
	}
		
private:
	std::list<float> m_frameDeltaTimeQue;
	float		m_frameDeltaTime = 1.0f / 60.0f;		//1�t���[���̌o�ߎ��ԁB
};

extern GameTime g_gameTime;	//

