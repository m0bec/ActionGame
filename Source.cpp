#include "DxLib.h"
//こいつは気にしないで-----------------
#include "ActionVar.h"
//------------------------------------

const int GRAPH_NUM = 1759;

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	// 画面モードの設定
	SetGraphMode(640, 480, 16);

	// ＤＸライブラリ初期化処理
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

	//描画------------------------------------------
	ActionType state = NORMAL;
	bool key_push_flag = false;
	bool no_action_flag = false;
	bool action_flag = false;
	bool jump_flag = false;
	int gr_num = 0;
	int x = 100, y = 100;
	//----------------------------------------------

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	

	while (1)
	{
		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();
		
		//描画----------------------------------------------------
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			no_action_flag = false;
			if (!key_push_flag) {
				state = SQUAT;
				gr_num = action[state.num].begin;
				action_flag = true;
				key_push_flag = true;
			}
		}
		else if(CheckHitKey(KEY_INPUT_UP)){
			no_action_flag = false;
			if (!key_push_flag) {
				state = JUMP;
				gr_num = action[state.num].begin;
				action_flag = true;
				key_push_flag = true;
			}
		}
		else if(!action_flag && !jump_flag){
			if (!no_action_flag) {
				state = NORMAL;
				gr_num = action[state.num].begin;
				no_action_flag = true;
				key_push_flag = false;
			}
		}

		DrawGraph(x-gr[gr_num].width/2, y-gr[gr_num].height, gr[gr_num].graph, true);

		++gr_num;
		if (state.loop) {
			if (gr_num > action[state.num].end) {
				gr_num = action[state.num].begin;
			}
		}
		else {
			if (gr_num > action[state.num].end) {
				gr_num = action[state.num].end;
				action_flag = false;
			}
		}
		//------------------------------------------------------------
		
		//FPS---------------------------------------------------------
		Sleep(1000 / 30);
		//------------------------------------------------------------

		// 裏画面の内容を表画面にコピーする
		ScreenFlip();

		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// -1 が返ってきたらループを抜ける
		if (ProcessMessage() < 0) break;

		// もしＥＳＣキーが押されていたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		
	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}