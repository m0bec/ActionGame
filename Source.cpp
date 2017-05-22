#include "DxLib.h"
#include <iostream>
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

	const char dir[] = "Rmai_graph/";
	const char type[] = ".bmp";
	char str[3];
	int num = 0;
	char str_num1[1];
	char str_num2[2];
	char filename[100];
	struct Graph
	{
		int graph;
		bool flag = false;
	};
	Graph gr[100];
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			sprintf(str, "%d", i);
			if (i < 10) {
				str[2] = str[0];
				str[0] = '0';
				str[1] = '0';
			}
			else if (i < 100) {
				str[2] = str[1];
				str[1] = str[0];
				str[0] = '0';
			}


			filename[0] = '\0';
			if (j < 10) {
				sprintf(str_num1, "%d", j);
			}
			else {
				sprintf(str_num2, "%d", j);
			}
			strcat(filename, str);
			strcat(filename, " (");
			strcat(filename, str_num1);
			strcat(filename, ").bmp");
			gr[i].graph = LoadGraph(filename);

			gr[i].graph = LoadGraph(filename);
		}
		
	}

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