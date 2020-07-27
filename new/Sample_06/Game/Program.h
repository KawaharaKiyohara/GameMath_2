#pragma once

//ライトのセットアップ。
void CreateSun()
{
	auto game = FindGO<Game>("Game");
	game->InitSceneLight();
	auto player = FindGO<Player>("Player");
	player->InitLight();
	//星に対してクエリをかける。
	FindGOs<Star>("Star", [&](Star* star) {
		star->InitLight();
	});
	GraphicsEngine().GetTonemap().SetEnable(true);
}