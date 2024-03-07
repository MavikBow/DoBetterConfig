#pragma once
#ifndef _PATCHER_H_
#include <stdio.h>
#define _PATCHER_H_

enum LayoutPosition
{
	menu_p, left_p, up_p, right_p, down_p, weaponl_p, items_p, weaponr_p, map_p, shoot_p, jump_p, resume_p, reset_p
};

const char* keyName(unsigned int);
int readInput();
int parseInput();
void resetLayout();
void arraygetter();
int isSupported(unsigned int);
int uploadKey(unsigned int, enum LayoutPosition);

#endif
