/*!
*@brief	ゲーム時間クラス。
* シングルトン。
*/
#pragma once

#include "Stopwatch.h"
#include <list>

/*!
*@brief	ゲーム時間。
*/
class GameTime{
public:
	/*!
		*@brief	1フレームの経過時間を取得(単位・秒)。
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
			//平均値をとる。
			m_frameDeltaTime = min(1.0f / 30.0f, totalTime / m_frameDeltaTimeQue.size());
			m_frameDeltaTimeQue.pop_front();
		}
	}
		
private:
	std::list<float> m_frameDeltaTimeQue;
	float		m_frameDeltaTime = 1.0f / 60.0f;		//1フレームの経過時間。
};

extern GameTime g_gameTime;	//

