#pragma once

extern HWND			g_hWnd ;				//ウィンドウハンドル。
extern GraphicsEngine* g_graphicsEngine ;	//グラフィックスエンジン。

//ゲームエンジンの初期化。
void InitGameEngine(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName);
//ウィンドウメッセージをディスパッチ。falseが返ってきたら、ゲーム終了。
bool DispatchWindowMessage();
