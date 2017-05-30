#pragma once
struct ActionType
{
	int num;
	int loop;
};
const int LOOP = 0;
const int FINISH = 1;
const int KEEP = 2;

const ActionType NORMAL = { 0,LOOP };
const ActionType SQUAT = { 1,KEEP };
const ActionType MOVE = { 2,LOOP };
const ActionType JUMP = { 3,KEEP };
const ActionType DOWN = { 10,LOOP };
const ActionType F_DASH = { 4,KEEP };
const ActionType B_DASH = { 5,KEEP };
const ActionType STAND_GARD = { 6, KEEP };
const ActionType SQUAT_GARD = { 7,KEEP };
const ActionType AIR_GARD = { 8,KEEP };
const ActionType SYOU_GARD = { 9, FINISH };

const int NORMAL_ = 0;
const int SQUAT_ = 1;
const int MOVE_ = 2;
const int JUMP_ = 3;
const int F_DASH_ = 4;
const int B_DASH_ = 5;
const int STAND_GARD_ = 6;
const int SQUAT_GARD_ = 7;
const int AIR_GARD_ = 8;
const int SYOU_GARD_ = 9;
const int DOWN_ = 10;

const int GRAUND = 300;