#pragma once

extern HWND			g_hWnd ;				//�E�B���h�E�n���h���B
extern GraphicsEngine* g_graphicsEngine ;	//�O���t�B�b�N�X�G���W���B

//�Q�[���G���W���̏������B
void InitGameEngine(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName);
//�E�B���h�E���b�Z�[�W���f�B�X�p�b�`�Bfalse���Ԃ��Ă�����A�Q�[���I���B
bool DispatchWindowMessage();
