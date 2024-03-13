#pragma once
#ifndef _PATCHER_H_
#include <stdio.h>

#define IGV_MENU (unsigned char) 0x01
#define IGV_LEFT (unsigned char) 0x02
#define IGV_UP (unsigned char) 0x03
#define IGV_RIGHT (unsigned char) 0x04
#define IGV_DOWN (unsigned char) 0x05
#define IGV_WEAPONL (unsigned char) 0x06
#define IGV_ITEMS (unsigned char) 0x08
#define IGV_WEAPONR (unsigned char) 0x09
#define IGV_MAP (unsigned char) 0x0a
#define IGV_SHOOT (unsigned char) 0x0b
#define IGV_JUMP (unsigned char) 0x0c
#define IGV_RESUME (unsigned char) 0x0d
#define IGV_RESET (unsigned char) 0x0e

#define _PATCHER_H_

enum LayoutPosition
{
	menu_p, left_p, up_p, right_p, down_p, weaponl_p, items_p, weaponr_p, map_p, shoot_p, jump_p, resume_p, reset_p
};

void arraygetter();
int readInput();
int parseInput();
void resetLayout();
int isSupported(unsigned int);
const char* keyName(unsigned int);
int uploadKey(unsigned int, enum LayoutPosition);
void applyFinalLayout();
void backUpDoukutsu();
const char* retrieveKeyName1(enum LayoutPosition);	// for the Action column
const char* retrieveKeyName2(enum LayoutPosition);	// for the Key column
const char* retrieveKeyName2Default(enum LayoutPosition pos);

#endif
