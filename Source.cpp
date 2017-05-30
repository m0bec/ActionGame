#include "DxLib.h"
//�����͋C�ɂ��Ȃ���-----------------
#include "ActionVar.h"
//------------------------------------

const int GRAPH_NUM = 1759;

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(640, 480, 16);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1) return -1;
	//Loadfile-----------------------------------------
	SetTransColor(0, 120, 141);

	const char dir[] = "Rmai_graph/";
	const char type[] = ".bmp";
	char str[4];
	int num = 0;
	int error_flag = 0;
	char str_num[3];
	char str_[100] = "\0";
	char filename[100] = "\0";
	struct Graph
	{
		int graph;
		int width, height;
		bool loop_flag = false;
	};
	Graph gr[100];

	//action
	struct Action
	{
		int begin;
		int end;
	};
	Action action[100];

	for (int i = 0; i < 100; i++) {
		action[i].begin = num;
		for (int j = 1; j < 100; j++) {
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
			str[3] = '\0';

			filename[0] = '\0';
			sprintf(str_num, "%d", j);

			strcat(filename, dir);
			strcat(filename, str);
			strcat(filename, " (");
			strcat(filename, str_num);
			strcat(filename, ").bmp");
			strcpy(str_, filename);
			gr[num].graph = LoadGraph(filename);
			if (gr[num].graph == -1) {
				error_flag++;
				break;
			}
			else {
				GetGraphSize(gr[num].graph, &gr[num].width, &gr[num].height);
				num++;
				error_flag = 0;
			}
		}
		if (error_flag == 2) {
			break;
		}
		action[i].end = num-1;
	}
	//----------------------------------------------

	//FPS-------------------------------------------
	const int FPS = 30;
	int count_fps = 0;
	int start_fps;
	int wait_fps;
	//----------------------------------------------

	//�`��------------------------------------------
	ActionType state = NORMAL;
	bool key_push_flag = false;
	bool no_action_flag = false;
	bool action_flag = false;
	bool jump_flag = false;
	int gr_num = 0;
	int x = 100, y = 300;
	//----------------------------------------------

	//�ړ��֘A--------------------------------------
	const int JUMP_VELO = 15;
	const int WALK_VELO = 5;
	const int AIR_MOVE = 3;
	bool turn = false;
	struct velo
	{
		int x;
		int y;
	};
	velo v = { 0, 0 };
	int gravity = 1;
	//---------------------------------------------

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	

	while (1)
	{
		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();
		
		//�`��----------------------------------------------------
		switch (state.num) {
		case NORMAL_:
			if (CheckHitKey(KEY_INPUT_DOWN)) {
				state = SQUAT;
				gr_num = action[SQUAT.num].begin;
			}
			else if (CheckHitKey(KEY_INPUT_UP)) {
				state = JUMP;
				gr_num = action[JUMP.num].begin;
				v.y = JUMP_VELO;
			}
			else if (CheckHitKey(KEY_INPUT_RIGHT)) {
				state = MOVE;
				gr_num = action[MOVE.num].begin;
				v.x = WALK_VELO;
				turn = false;
			}
			else if (CheckHitKey(KEY_INPUT_LEFT)) {
				state = MOVE;
				gr_num = action[MOVE.num].begin;
				v.x = -WALK_VELO;
				turn = true;
			}

			break;

		case SQUAT_:
			if (gr_num == action[SQUAT_].end) {
				if (!CheckHitKey(KEY_INPUT_DOWN)) {
					if (CheckHitKey(KEY_INPUT_UP))
					{
						state = JUMP;
						gr_num = action[JUMP.num].begin;
					}
					else {
						state = NORMAL;
						gr_num = action[NORMAL.num].begin;
					}
				}
			}
			break;

		case MOVE_:
			if (CheckHitKey(KEY_INPUT_RIGHT)) {
				v.x = WALK_VELO;
				turn = false;
			}
			else if (CheckHitKey(KEY_INPUT_LEFT)) {
				v.x = -WALK_VELO;
				turn = true;
			}
			else {
				state = NORMAL;
				gr_num = action[NORMAL.num].begin;
				v.x = 0;
			}
			break;

		case JUMP_:
			if (y >= GRAUND) {
				state = NORMAL;
				gr_num = action[NORMAL.num].begin;
			}

			v.x = 0;

			if (CheckHitKey(KEY_INPUT_RIGHT)) {
				turn = false;
				v.x = AIR_MOVE;
			}
			else if (CheckHitKey(KEY_INPUT_LEFT)) {
				turn = true;
				v.x = -AIR_MOVE;
			}

			break;

		case END_:

			break;
		}

		//�`��-------------------------------------------------------------------
		if (!turn) {
			DrawGraph(x - gr[gr_num].width / 2, y - gr[gr_num].height, gr[gr_num].graph, true);
		}
		else {
			DrawTurnGraph(x - gr[gr_num].width / 2, y - gr[gr_num].height, gr[gr_num].graph, true);
		}
		//------------------------------------------------------------------------

		++gr_num;
		if (state.loop == LOOP) {
			if (gr_num > action[state.num].end) {
				gr_num = action[state.num].begin;
			}
		}
		else if(state.loop == FINISH){
			if (gr_num > action[state.num].end) {
				gr_num = action[state.num].end;
				action_flag = false;
			}
		}
		else if (state.loop == KEEP) {
			if (gr_num > action[state.num].end) {
				gr_num = action[state.num].end;
			}
		}
		//------------------------------------------------------------
		
		//�ړ�--------------------------------------------------------
		x += v.x;
		y -= v.y;
		if (y < GRAUND) {
			v.y -= gravity;
		}
		else {
			y = GRAUND;
			v.y = 0;
		}

		//------------------------------------------------------------

		//FPS---------------------------------------------------------
		Sleep(1000 / 30);
		//------------------------------------------------------------

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