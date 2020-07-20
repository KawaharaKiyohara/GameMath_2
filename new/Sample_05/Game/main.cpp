#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"
#include "Background.h"
#include "GameTime.h"


GameTime g_gameTime;


///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 100.0f, -300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	
	//プレイヤー
	Player player;
	//背景。
	Background bg;
	//ゲーム時間計測用のストップウォッチを追加。
	Stopwatch sw;
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//ゲーム時間の計測開始。
		sw.Start();

		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		//プレイヤーの更新。
		player.Update();
		//プレイヤーの描画。
		player.Draw();
		//BGの描画。
		bg.Draw();
		//カメラの更新。
		g_camera3D.Update();

		//step-2 16ミリ秒スリープさせて、わざと処理落ちさせてみる。
		Sleep( 0 );
		//描画終了。
		g_graphicsEngine->EndRender();

		//ゲーム時間の計測終了。
		sw.Stop();
		//このフレームにかかった時間を記憶しておく。
		g_gameTime.PushFrameDeltaTime(sw.GetElapsed());
	}
}