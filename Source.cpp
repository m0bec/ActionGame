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

	struct BOX
	{
		int lx, rx;
		int hy, ly;
		int type = NONE;
		bool flag = true;
	};

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
		BOX box;
		BOX attack;
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
				gr[num].box.type = BODY;
				gr[num].box.lx = 0;
				gr[num].box.rx = gr[num].width;
				gr[num].box.hy = 0;
				gr[num].box.ly = gr[num].height;
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

	//enemyのロード----------------------------------
	struct Enemy
	{
		int x, y;
		int gr;
		int life;
		int width, height;
	};
	const int ENEMY_VELO = 2;
	int etx, ety;
	Enemy enemy;
	enemy = { 600, GRAUND, LoadGraph("Enemy/Enemy1.png"), 10 };
	GetGraphSize(enemy.gr, &enemy.width, &enemy.height);
	//----------------------------------------------


	//FPS-------------------------------------------
	const int FPS = 2;
	int count_fps = 0;
	//----------------------------------------------

	//描画------------------------------------------
	ActionType state = NORMAL;
	bool key_push_flag = false;
	bool no_action_flag = false;
	int action_flag = 0;
	bool jump_flag = false;
	int gr_num = 0;
	int x = 100, y = 300;
	int tx, ty;
	//----------------------------------------------

	//移動関連--------------------------------------
	char input_buf[256];

	const int JUMP_VELO = 15;
	const int WALK_VELO = 4;
	const int DASH_VELO = 8;
	const int AIR_MOVE = 3;
	const int WAIT_TIME = 5;
	const int FALL_VELO = 1;
	int time = 0;
	int key_out_flag = NORMAL_;
	bool dash_jump_flag = false;
	bool memo_turn = false;
	bool turn = false;
	struct velo
	{
		int x;
		int y;
	};
	velo v = { 0, 0 };
	int gravity = 1;
	
	//---------------------------------------------

	//あたり判定-------------------------------------
	
	BOX Benemy = {0, enemy.width, 0, enemy.height, BODY};
	//----------------------------------------------

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	

	while (1)
	{
		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();
		
		//state管理----------------------------------------------------
		GetHitKeyStateAll(input_buf);

		if (key_out_flag != NORMAL_) {
			if (time > WAIT_TIME) {
				key_out_flag = NORMAL_;
				time = 0;
				printfDx("%D\n", time);
			}
			else {
				time++;
			}
		}

		switch (state.num) {
		case NORMAL_:
			if (input_buf[KEY_INPUT_DOWN] == 1) {
				if (input_buf[KEY_INPUT_Z] == 1) {
					state = DW_JAB;
					gr_num = action[DW_JAB.num].begin;
					action_flag = ACTION_DWJAB;
				}
				else if (input_buf[KEY_INPUT_X] == 1) {
					state = DS_ATTACK;
					gr_num = action[DS_ATTACK.num].begin;
					action_flag = ACTION_DSATTACK;
				}
				else {
					state = SQUAT;
					gr_num = action[SQUAT.num].begin;
				}
			}
			else if (input_buf[KEY_INPUT_UP] == 1) {
				state = JUMP;
				gr_num = action[JUMP.num].begin;
				v.y = JUMP_VELO;
			}
			else if (input_buf[KEY_INPUT_RIGHT] == 1) {
				turn = false;

				if (input_buf[KEY_INPUT_Z] == 1) {
					state = W_JAB;
					gr_num = action[W_JAB.num].begin;
					action_flag = ACTION_WJAB;
				}
				else if (input_buf[KEY_INPUT_X] == 1) {
					state = WS_ATTACK;
					gr_num = action[WS_ATTACK.num].begin;
					action_flag = ACTION_WSATTACK;
				}
				else if (key_out_flag == MOVE_ && memo_turn == turn) {
					state = F_DASH;
					gr_num = action[F_DASH.num].begin;
					v.x = DASH_VELO;
					time = 0;
					key_out_flag = NORMAL_;
				}
				else {
					state = MOVE;
					gr_num = action[MOVE.num].begin;
					v.x = WALK_VELO;
				}
			}
			else if (input_buf[KEY_INPUT_LEFT] == 1) {
				turn = true;

				if (input_buf[KEY_INPUT_Z] == 1) {
					state = W_JAB;
					gr_num = action[W_JAB.num].begin;
					action_flag = ACTION_WJAB;
				}
				else if (input_buf[KEY_INPUT_X] == 1) {
					state = WS_ATTACK;
					gr_num = action[WS_ATTACK.num].begin;
					action_flag = ACTION_WSATTACK;
				}
				else if (key_out_flag == MOVE_ && memo_turn == turn) {
					state = F_DASH;
					gr_num = action[F_DASH.num].begin;
					v.x = DASH_VELO;
					time = 0;
					key_out_flag = NORMAL_;
				}
				else {
					state = MOVE;
					gr_num = action[MOVE.num].begin;
					v.x = -WALK_VELO;
				}
			}
			else if (input_buf[KEY_INPUT_A] == 1) {
				state = STAND_GARD;
				gr_num = action[STAND_GARD.num].begin;
			}
			else if (input_buf[KEY_INPUT_Z] == 1) {
				state = JAB;
				gr_num = action[JAB.num].begin;
				action_flag = ACTION_JAB;
			}
			else if (input_buf[KEY_INPUT_X] == 1) {
				state = S_ATTACK;
				gr_num = action[S_ATTACK.num].begin;
				action_flag = ACTION_SATTACK;
			}
			

			break;

		case SQUAT_:
			
			if (!input_buf[KEY_INPUT_DOWN] == 1) {
					if (input_buf[KEY_INPUT_UP] == 1)
					{
						state = JUMP;
						gr_num = action[JUMP.num].begin;
					}
					else {
						state = NORMAL;
						gr_num = action[NORMAL.num].begin;
					}
				}
			else {
				if (input_buf[KEY_INPUT_A] == 1) {
					state = SQUAT_GARD;
					gr_num = action[SQUAT_GARD.num].end;
				}
				else if (input_buf[KEY_INPUT_Z] == 1) {
					state = DW_JAB;
					gr_num = action[DW_JAB.num].begin;
					action_flag = ACTION_DWJAB;
				}
				else if (input_buf[KEY_INPUT_X] == 1) {
					state = DS_ATTACK;
					gr_num = action[DS_ATTACK.num].begin;
					action_flag = ACTION_DSATTACK;
				}
			}
			
			break;

		case MOVE_:
			if (input_buf[KEY_INPUT_Z] == 1) {
				state = W_JAB;
				gr_num = action[W_JAB.num].begin;
				v.x = 0;
				action_flag = ACTION_WJAB;
			}
			else if (input_buf[KEY_INPUT_X] == 1) {
				state = WS_ATTACK;
				gr_num = action[WS_ATTACK.num].begin;
				v.x = 0;
				action_flag = ACTION_WSATTACK;
			}
			else if (input_buf[KEY_INPUT_UP] == 1) {
				state = JUMP;
				gr_num = action[JUMP.num].begin;
				v.y = JUMP_VELO;
			}
			else if (input_buf[KEY_INPUT_LEFT] == 1) {
				v.x = -WALK_VELO;
				turn = true;
			}
			else if (input_buf[KEY_INPUT_RIGHT] == 1) {
				v.x = WALK_VELO;
				turn = false;
				
			}
			else {
				state = NORMAL;
				gr_num = action[NORMAL.num].begin;
				v.x = 0;
				dash_jump_flag = false;
			}


			//ダッシュ受付
			if (CheckHitKeyAll() == 0) {
				key_out_flag = MOVE_;
				memo_turn = turn;
			}

			break;

		case JUMP_:
			if (y >= GRAUND) {
				state = NORMAL;
				gr_num = action[NORMAL.num].begin;
				v.x = 0;
			}

			if (v.y >= 0 && action[NORMAL.num].begin + 4 == gr_num) {
				gr_num = action[NORMAL.num].begin + 4;
			}
			if (!dash_jump_flag) {
				v.x = 0;
				if (input_buf[KEY_INPUT_RIGHT] == 1) {
					turn = false;
					v.x = AIR_MOVE;
				}
				else if (input_buf[KEY_INPUT_LEFT] == 1) {
					turn = true;
					v.x = -AIR_MOVE;
				}
				else if (input_buf[KEY_INPUT_DOWN] == 1) {
					v.y -= FALL_VELO;
				}
			}
			if (input_buf[KEY_INPUT_A] == 1) {
				state = AIR_GARD;
				gr_num = action[AIR_GARD.num].begin;
				v.x = 0;
			}
			else if (input_buf[KEY_INPUT_Z] == 1) {
				state = JW_JAB;
				gr_num = action[JW_JAB.num].begin;
				action_flag = ACTION_JWJAB;
			}
			else if (input_buf[KEY_INPUT_X] == 1) {
				state = JS_ATTACK;
				gr_num = action[JS_ATTACK.num].begin;
				action_flag = ACTION_JSATTACK;
			}

			break;

		case F_DASH_:
			if (input_buf[KEY_INPUT_X] == 1) {
				state = WS_ATTACK;
				gr_num = action[WS_ATTACK.num].begin;
				v.x = 0;
				action_flag = ACTION_WSATTACK;
			}else if (input_buf[KEY_INPUT_UP] == 1) {
				state = JUMP;
				gr_num = action[JUMP.num].begin;
				v.y = JUMP_VELO;
				dash_jump_flag = true;
			}
			else if (input_buf[KEY_INPUT_RIGHT] == 1 && !turn) {
				turn = false;
				v.x = DASH_VELO;
			}
			else if (input_buf[KEY_INPUT_LEFT] == 1 && turn) {
				turn = true;
				v.x = -DASH_VELO;
			}
			else {
				state = NORMAL;
				gr_num = action[NORMAL.num].begin;
				v.x = 0;
			}
			break;

		case B_DASH_:

			break;
			
		case STAND_GARD_:
			if (gr_num == action[STAND_GARD.num].end) {
				if (input_buf[KEY_INPUT_DOWN] == 1) {
					state = SQUAT_GARD;
					gr_num = action[SQUAT_GARD.num].begin;
				}
				else {
					if (!input_buf[KEY_INPUT_A] == 1) {
						state = NORMAL;
						gr_num = action[NORMAL.num].begin;
					}
				}
			}
			break;

		case SQUAT_GARD_:
			if (gr_num == action[SQUAT_GARD.num].end) {
				if (input_buf[KEY_INPUT_A] == 1) {
					if (input_buf[KEY_INPUT_DOWN] == 1) {
						state = SQUAT_GARD;
					}
					else {
						state = STAND_GARD;
						gr_num = action[STAND_GARD.num].begin;
					}
				}
				else {
					state = NORMAL;
					gr_num = action[NORMAL.num].begin;
				}
				
			}
			break;

		case AIR_GARD_:
			if (y >= GRAUND) {
				state = NORMAL;
				gr_num = action[NORMAL.num].begin;
			}
			break;

		case JAB_:
			if (action_flag == ACTION_NORMAL) {
				state = NORMAL;
				gr_num = action[NORMAL.num].begin;
			}
			break;

		case W_JAB_:
			if (action_flag == ACTION_NORMAL) {
				state = NORMAL;
				gr_num = action[NORMAL.num].begin;
			}

			break;

		case S_ATTACK_:
			if (action_flag == ACTION_NORMAL) {
				state = NORMAL;
				gr_num = action[NORMAL.num].begin;
			}

			break;

		case WS_ATTACK_:
			if (action_flag == ACTION_NORMAL) {
				state = NORMAL;
				gr_num = action[NORMAL.num].begin;
			}

			break;

		case DW_JAB_:
			if (action_flag == ACTION_NORMAL) {
				state = SQUAT;
				gr_num = action[SQUAT.num].end;
			}

			break;

		case DS_ATTACK_:
			if (action_flag == ACTION_NORMAL) {
				state = SQUAT;
				gr_num = action[SQUAT.num].end;
			}

			break;

		case JW_JAB_:
			if (y < GRAUND) {
				if (action_flag == ACTION_NORMAL) {
					state = JUMP;
					gr_num = action[JUMP.num].end;
				}
				else if (input_buf[KEY_INPUT_RIGHT] == 1) {
					turn = false;
					v.x = AIR_MOVE;
				}
				else if (input_buf[KEY_INPUT_LEFT] == 1) {
					turn = true;
					v.x = -AIR_MOVE;
				}
				else if (input_buf[KEY_INPUT_DOWN] == 1) {
					v.y -= FALL_VELO;
				}
			}
			else {
				state = NORMAL;
				gr_num = action[NORMAL.num].end;
				action_flag = ACTION_NORMAL;
				v.x = 0;
				dash_jump_flag = false;
			}

			break;

		case JS_ATTACK_:
			if (y < GRAUND) {
				if (action_flag == ACTION_NORMAL) {
					state = JUMP;
					gr_num = action[JUMP.num].end;
				}
				else if (input_buf[KEY_INPUT_RIGHT] == 1) {
					turn = false;
					v.x = AIR_MOVE;
				}
				else if (input_buf[KEY_INPUT_LEFT] == 1) {
					turn = true;
					v.x = -AIR_MOVE;
				}
				else if (input_buf[KEY_INPUT_DOWN] == 1) {
					v.y -= FALL_VELO;
				}
			}
			else {
				state = NORMAL;
				gr_num = action[NORMAL.num].end;
				action_flag = ACTION_NORMAL;
				v.x = 0;
				dash_jump_flag = false;
			}

			break;
		}

		

		//描画-------------------------------------------------------------------
		if (state.gr_type == LEG) {
			tx = x - gr[gr_num].width / 2;
			ty = y - gr[gr_num].height;
			
		}
		else if (state.gr_type == HEAD) {
			tx = x - gr[gr_num].width / 2;
			ty = y - gr[JUMP.num].height;
		}

		if (!turn) {
			DrawGraph(tx, ty, gr[gr_num].graph, true);
			DrawBox(tx + gr[gr_num].box.lx, ty + gr[gr_num].box.hy, tx + gr[gr_num].box.rx, ty + gr[gr_num].box.ly,
				GetColor(255, 255, 255), false);
		}
		else {
			DrawTurnGraph(tx, ty, gr[gr_num].graph, true);
		}
		DrawBox(tx + gr[gr_num].box.lx, ty + gr[gr_num].box.hy, tx + gr[gr_num].box.rx, ty + gr[gr_num].box.ly,
			GetColor(255, 255, 255), false);
		
		//敵
		if (enemy.life > 0) {
			etx = enemy.x - enemy.width / 2;
			ety = enemy.y - enemy.height;
			DrawGraph(etx, ety, enemy.gr, true);
			DrawBox(etx + Benemy.lx, ety + Benemy.hy, etx + Benemy.rx, ety + Benemy.ly,
				GetColor(255, 255, 255), false);
		}
		//------------------------------------------------------------------------

		//あたり判定----------------------------------------------------
		if (enemy.life > 0) {
			if (etx + Benemy.rx > tx + gr[gr_num].box.lx && etx + Benemy.lx < tx + gr[gr_num].box.rx
				&&  ety + Benemy.hy < ty + gr[gr_num].box.ly && ety + Benemy.ly > ty + gr[gr_num].box.hy) {
				enemy.life -= 1;
				printfDx("OK\n");
			}
		}
		//------------------------------------------------------------

		if (count_fps >= FPS) {
			++gr_num;
			if (state.loop == LOOP) {
				if (gr_num > action[state.num].end) {
					gr_num = action[state.num].begin;
				}
			}
			else if (state.loop == FINISH) {
				if (gr_num > action[state.num].end) {
					gr_num = action[state.num].end;
					action_flag = ACTION_NORMAL;
				}
			}
			else if (state.loop == KEEP) {
				if (gr_num > action[state.num].end) {
					gr_num = action[state.num].end;
				}
			}

			//移動--------------------------------------------------------
			x += v.x;
			y -= v.y;
			if (y < GRAUND) {
				v.y -= gravity;
			}
			else {
				y = GRAUND;
				v.y = 0;
			}

			//敵の動き------------------------------------------------------------------
			if (enemy.life > 0) {
				if (enemy.x <= x) {
					enemy.x += ENEMY_VELO;
				}
				else {
					enemy.x -= ENEMY_VELO;
				}
			}
			//-----------------------------------------------------------------------

			

			count_fps = 0;
		}
		else {
			count_fps++;
		}


		// 裏画面の内容を表画面にコピーする
		ScreenFlip();

		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// -1 が返ってきたらループを抜ける
		if (ProcessMessage() < 0) break;

		// もしＥＳＣキーが押されていたらループから抜ける
		if (input_buf[KEY_INPUT_ESCAPE]) break;

		
	}
	
	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}