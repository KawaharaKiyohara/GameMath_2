#pragma once

//���C�g�̃Z�b�g�A�b�v�B
void CreateSun()
{
	auto game = FindGO<Game>("Game");
	game->InitSceneLight();
	auto player = FindGO<Player>("Player");
	player->InitLight();
	//���ɑ΂��ăN�G����������B
	FindGOs<Star>("Star", [&](Star* star) {
		star->InitLight();
	});
	GraphicsEngine().GetTonemap().SetEnable(true);
}