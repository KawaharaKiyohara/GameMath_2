#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"
#include <algorithm>
#include <GameCamera.h>
#include "Enemy.h"

///////////////////////////////////////////////////////////////////
//クラスのインスタンスをグローバルな領域に置く場合は
//動的確保をしたほうが良い。
//なぜか？
//  ->アプリケーションが起動したときにコンストラクタが呼ばれるから。
//    ->なんの問題がある？
//      ->エンジンの初期化の前にコンストラクタが呼ばれると困る！
//        ->なぜ困るかわからない人は、Player hogehoge;をコメントアウトして、プログラムを実行してみよう！
//          ->クラッシュするよ！
///////////////////////////////////////////////////////////////////

//クラッシュさせたい人は、Player hogehogeのコメントアウトを外してみよう。
//Player hogehoge;
//プレイヤー
Player* player = nullptr;
//ゲームカメラ。
GameCamera* gameCamera = nullptr;
//レベルを初期化。
Level* level = nullptr;;

std::vector< Enemy* > enemyList;		//エネミーのリスト。
///////////////////////////////////////////////////////////////////
//ゲームの初期化処理
///////////////////////////////////////////////////////////////////
void InitGame()
{
	//プレイヤーの初期化。
	player = new Player;
	player->SetPosition({ 30.0f, 0.0f, 0.0f });

	//レベルを構築する。
	level = new Level;
	level->Init(L"Assets/level/stage_00.tkl", [&](LevelObjectData& objData)->bool {
		if (wcscmp(objData.name, L"enemy") == 0) {
			//エネミー！！！
			auto enemy = new Enemy( objData.position, objData.rotation, player);
			enemyList.push_back(enemy);
			return true;
		}
		return false;
	});

	gameCamera = new GameCamera();
	gameCamera->SetPlayer(player);
}
///////////////////////////////////////////////////////////////////
//ゲームの更新処理。
//座標の更新とかの処理はここで呼び出すとよいかも？
///////////////////////////////////////////////////////////////////
void UpdateGame()
{
	//ゲームパッドの更新。	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	//物理エンジンの更新。
	g_physics.Update();
	//プレイヤーの更新。
	player->Update();
	gameCamera->Update();
	//Enemyを更新。
	for (auto& enemy : enemyList) {
		enemy->Update();
	}
}
///////////////////////////////////////////////////////////////////
// ゲームの描画処理。
// 描画と更新は分けてやるほうが良いかも？
///////////////////////////////////////////////////////////////////
void RenderGame()
{
	//描画開始。
	g_graphicsEngine->BegineRender();

	//プレイヤーの描画。
	player->Draw();
	//レベルを描画。
	level->Draw();
	//Coinを描画。
	for (auto& enemy : enemyList) {
		enemy->Draw();
	}

	//描画終了。
	g_graphicsEngine->EndRender();
}

///////////////////////////////////////////////////////////////////
// ゲームの終了処理。
///////////////////////////////////////////////////////////////////
void TermnateGame()
{
	//動的に確保したインスタンスを破棄。
	delete player;
	delete level;
	delete gameCamera;
	for (auto& enemy : enemyList) {
		delete enemy;
	}
}
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームエンジンの初期化。
	InitGameEngine(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	//ゲームの初期化。
	InitGame();
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//ゲームの更新。
		UpdateGame();
		//ゲームの描画処理。
		RenderGame();
	}
	//ゲームの終了処理
	TermnateGame();
}