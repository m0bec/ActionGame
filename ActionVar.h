#pragma once
const int LEG = 0;
const int HEAD = 1;

struct ActionType
{
	int num;
	int loop;
	int gr_type;
};
const int LOOP = 0;
const int FINISH = 1;
const int KEEP = 2;

const ActionType NORMAL = { 0,LOOP,LEG };
const ActionType SQUAT = { 1,KEEP,LEG };
const ActionType MOVE = { 2,LOOP,LEG };
const ActionType JUMP = { 3,KEEP,LEG };
const ActionType F_DASH = { 4,KEEP,LEG };
const ActionType B_DASH = { 5,KEEP,LEG };
const ActionType STAND_GARD = { 6, KEEP,LEG };
const ActionType SQUAT_GARD = { 7,KEEP,LEG };
const ActionType AIR_GARD = { 8,KEEP,LEG };
const ActionType JAB = { 9, FINISH,LEG };
const ActionType DOWN = { 10,LOOP,LEG };
const ActionType W_JAB = { 11,FINISH,LEG };
const ActionType S_ATTACK = { 12,FINISH,LEG };
const ActionType WS_ATTACK = { 13, FINISH,LEG };
const ActionType DW_JAB = { 14,FINISH,LEG };
const ActionType DS_ATTACK = { 15,FINISH,LEG };
const ActionType JW_JAB = { 16, FINISH,HEAD };
const ActionType JS_ATTACK = { 17, FINISH,HEAD };

const int NORMAL_ = 0;
const int SQUAT_ = 1;
const int MOVE_ = 2;
const int JUMP_ = 3;
const int F_DASH_ = 4;
const int B_DASH_ = 5;
const int STAND_GARD_ = 6;
const int SQUAT_GARD_ = 7;
const int AIR_GARD_ = 8;
const int JAB_ = 9;
const int DOWN_ = 10;
const int W_JAB_ = 11;
const int S_ATTACK_ = 12;
const int WS_ATTACK_ = 13;
const int DW_JAB_ = 14;
const int DS_ATTACK_ = 15;
const int JW_JAB_ = 16;
const int JS_ATTACK_ = 17;

const int ACTION_NORMAL = 0;
const int ACTION_JAB = 1;
const int ACTION_WJAB = 2;
const int ACTION_SATTACK = 3;
const int ACTION_WSATTACK = 4;
const int ACTION_DWJAB = 5;
const int ACTION_DSATTACK = 6;
const int ACTION_JWJAB = 7;
const int ACTION_JSATTACK = 8;

const int GRAUND = 300;