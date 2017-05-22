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
// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	// 画面モードの設定
	SetGraphMode(640, 480, 16);

	// ＤＸライブラリ初期化処理
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

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	
	
	while (1)
	{
		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();


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