#pragma once
struct ActionType
{
	int num;
	bool loop;
};
const static ActionType NORMAL = { 0,true };
const static ActionType SQUAT = { 1,false };
const static ActionType MOVE = { 2,false };
const static ActionType JUMP = { 3,false };
const static ActionType END = { 4,false };

const int GRAUND = 300;