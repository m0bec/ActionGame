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
const ActionType END = { 4,LOOP };

const int NORMAL_ = 0;
const int SQUAT_ = 1;
const int MOVE_ = 2;
const int JUMP_ = 3;
const int END_ = 4;
const int FALL_ = 5;

const int GRAUND = 300;