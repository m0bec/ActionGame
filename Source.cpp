#include "DxLib.h"
#include <fstream>
#include <string>
#include <vector>

const int NORMAL = 0;
const int GRAPH_NUM = 1759;
struct Graph
{
	int graph;
	bool fin_flag = true;;
};
// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(640, 480, 16);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1) return -1;
	
	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	
	while (1)
	{
		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		


		// ����ʂ̓��e��\��ʂɃR�s�[����
		ScreenFlip();
		
		// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
		// -1 ���Ԃ��Ă����烋�[�v�𔲂���
		if (ProcessMessage() < 0) break;

		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}