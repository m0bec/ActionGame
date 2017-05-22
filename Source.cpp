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
// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	// 画面モードの設定
	SetGraphMode(640, 480, 16);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) return -1;
	
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