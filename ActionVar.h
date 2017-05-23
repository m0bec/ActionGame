#pragma once
struct ActionType
{
	int num;
	bool loop;
};
const ActionType NORMAL = { 0,true };
const ActionType SQUAT = { 1,false };
const ActionType MOVE = { 2,false };
const ActionType JUMP = { 3,false };
const ActionType END = { 4,false };