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

	char graph_directory[] = "Rmai_graph/";
	Graph mai[GRAPH_NUM];
	for (int i = 0; i < GRAPH_NUM; i++) {
		while (true) {
			mai[i].graph = LoadGraph("");
			if (mai[i].graph == -1) {
				mai[i - 1].fin_flag = false;
			}
		}
	}
	
	const int graph_start = 1401;
	const int graph_end = 1687;
	int num = 0;
	std::string numname;
	const std::string filename_num(" 9502-");
	const std::string filetype(".bmp");
	const std::string graph_directory("Rmai_graph/");
	std::string filename;
	std::vector<int> graph;

	int soundBGM, soundVoice;
	soundBGM = LoadSoundMem("077 44444-44444.wav");
	soundVoice = LoadSoundMem("078 006-00005.wav");
	for (int i = graph_start; i <= graph_end; i++) {
		if (num < 10) {
			numname = "00" + std::to_string(num);
		}
		else if (num < 100) {
			numname = "0" + std::to_string(num);
		}
		else {
			numname = std::to_string(num);
		}
		filename = graph_directory + std::to_string(i) + filename_num + numname + filetype;
		char* file = new char[filename.size() + 1];
		std::char_traits<char>::copy(file, filename.c_str(), filename.size() + 1);
		graph.push_back(LoadGraph(file));
		++num;
	}
	
	int gr = LoadGraph("Rmai_graph/1401 9502-000.bmp");
	std::vector<int>::iterator itr = graph.begin();
	int  count = 0;
	
	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	
	PlaySoundMem(soundBGM, DX_PLAYTYPE_LOOP, true);
	PlaySoundMem(soundVoice, DX_PLAYTYPE_BACK, true);
	
	while (1)
	{
		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		if (itr == graph.end())	itr = graph.begin();

		DrawGraph(0, 0, *itr, false);

		++count;
		if (count > 1) {
			++itr;
			count = 0;
		}


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