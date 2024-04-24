#include "patcher.h"
#include <string.h>

/*Sorted Controls:
	Menu :	Esc - 1b - 27 - 01
	Left:	<- -- 25 - 37 - 02
	Up:	    ^  -- 26 - 38 - 03
	Right:	-> -- 27 - 39 - 04
	Down:	v  -- 28 - 40 - 05
	WeaponL:A --- 41 - 65 - 06
	Items:	Q --- 51 - 81 - 08
	WeaponR:S --- 53 - 83 - 09
	Map:	W --- 57 - 87 - 0a
	Shoot:	X --- 58 - 88 - 0b
	Jump:	Z --- 5a - 90 - 0c
	Resume:	F1 -- 70 - 112  0d
	Reset:	F2 -- 71 - 113  0e
	*/

const unsigned char defaultLayout[13] = {0x1b, 0x25, 0x26, 0x27, 0x28, 0x41, 0x51, 0x53, 0x57, 0x58, 0x5a, 0x70, 0x71};
unsigned char newLayout[13] = {0};

const long int location1 = 0x000133a3;
const long int location2 = 0x000134a3;

const unsigned char defaultArr1[] = {
    0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x01, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x02, 0x03, 0x04, 0x05, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x06, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x07, 0x14, 0x14, 0x14,
    0x14, 0x08, 0x14, 0x09, 0x14, 0x14, 0x14, 0x0a, 0x0b, 0x14, 0x0c, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x0d, 0x0e, 0x14, 0x14, 0x0f, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x10, 0x11, 0x14, 0x12, 0x13};

const unsigned char defaultArr2[] = {
    0x00, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x01, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x13, 0x13, 0x13, 0x13, 0x02, 0x03, 0x04, 0x05, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x06, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x07, 0x13, 0x13, 0x13,
    0x13, 0x08, 0x13, 0x09, 0x13, 0x13, 0x13, 0x0a, 0x0b, 0x13, 0x0c, 0x13, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
    0x0d, 0x0e, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x0f, 0x10, 0x13, 0x11, 0x12};

unsigned char newArr1[176], newArr2[176];

void debug()
{
	for(int i = 0; i < 176; i++)
	{
		if(i%16 == 0) printf("\n");
		printf("0x%02x, ", defaultArr1[i]);
	}
	printf("\n");
	for(int i = 0; i < 176; i++)
	{
		if(i%16 == 0) printf("\n");
		printf("0x%02x, ", newArr1[i]);
	}
}

int resetConfig()
{
	FILE* out = fopen("Config.dat", "r+b");
	if(out == NULL) return -1;//printf("Trouble opening Config.dat");
	const unsigned char* ZERO = 0x0;

	fseek(out, 0x60, SEEK_SET);
	fwrite(&ZERO, 1, 1, out);
	fseek(out, 0x64, SEEK_SET);
	fwrite(&ZERO, 1, 1, out);
	fseek(out, 0x68, SEEK_SET);
	fwrite(&ZERO, 1, 1, out);

	fclose(out);
	return 0;
}	

int backUpDoukutsu()
{
	FILE* in = fopen("Doukutsu.exe", "rb");
	FILE* out = fopen("Doukutsu_backup.exe", "wb");
	if(out == NULL) return -1;//printf("game over\n");

	for(char ch; fread(&ch, 1, 1, in) > 0; fwrite(&ch, 1, 1, out));

	fseek(out, location1, SEEK_SET);
	fwrite(&defaultArr1, 176, 1, out);
	fseek(out, location2, SEEK_SET);
	fwrite(&defaultArr2, 176, 1, out);

	fclose(in);
	fclose(out);
	return 0;
}

int readInput()
{
	FILE* in = fopen("Doukutsu.exe", "rb");
	if(in == NULL) return -1;

	fseek(in, location1, SEEK_SET);
	fread(newArr1, 1, 176, in);

	fseek(in, location2, SEEK_SET);
	fread(newArr2, 1, 176, in);

	fclose(in);
	return 0;
}

int parseInput()
{ 
	const unsigned char OFFSET = 0x10; 
	enum LayoutPosition pos;
	char success;
	for(unsigned char i = 0; i < 176; i++)
	{
		success = 1;
		if(newArr1[i] == newArr2[i])
		{
			switch(newArr1[i])
			{
				case IGV_MENU:	pos = menu_p;		break;
				case IGV_LEFT:	pos = left_p; 		break;
				case IGV_UP:	pos = up_p; 		break;
				case IGV_RIGHT:	pos = right_p; 		break;
				case IGV_DOWN:	pos = down_p; 		break;
				case IGV_WEAPONL:pos = weaponl_p; 	break;
				case IGV_ITEMS: pos = items_p; 		break;
				case IGV_WEAPONR:pos = weaponr_p; 	break;
				case IGV_MAP: 	pos = map_p; 		break;
				case IGV_SHOOT: pos = shoot_p;		break;
				case IGV_JUMP: 	pos = jump_p; 		break;
				case IGV_RESUME:pos = resume_p; 	break;
				case IGV_RESET:	pos = reset_p; 		break;
				default: success = 0;				break;
			}
			if(success) newLayout[pos] = (unsigned char)(i + OFFSET);
		}
	}
	return 0;
}

// ListView population

char controlKeyAction[13][30] =
{"Menu/Quit",
"Move Left",
"Look Up",
"Move Right",
"Look Down/Interact",
"Scroll Weapons Left",
"Item Inventory",
"Scroll Weapons Right",
"Map System",
"Shoot",
"Jump/OK",
"Resume",
"Reset"};

enum LayoutPosition listViewLayout[13] = 
{
	menu_p, resume_p, reset_p, left_p, right_p, up_p, down_p, jump_p,shoot_p, weaponl_p, weaponr_p, items_p, map_p  
};
const char* retrieveKeyName1(enum LayoutPosition pos)
{
	return controlKeyAction[listViewLayout[pos]];
}
const char* retrieveKeyName2(enum LayoutPosition pos)
{
	return keyName(newLayout[listViewLayout[pos]]);
}
const char* retrieveKeyName2Default(enum LayoutPosition pos)
{
	return keyName(defaultLayout[listViewLayout[pos]]);
}
// =============================
int uploadKey(unsigned int wParam, enum LayoutPosition pos)
{
	if (!isSupported(wParam))
		return -1;

	// checks if you want to unbind a key
	if (strcmp(keyName(wParam),"<NONE>") == 0)
		wParam = 0;
	else // checks if such value already exists in a different place
	for(unsigned int i = 0; i < 13; i++)
		if(i != pos && newLayout[listViewLayout[i]] == (unsigned char)wParam) return -1; 

	newLayout[listViewLayout[pos]] = (unsigned char) wParam;
	return 0;
}

void resetLayout()
{
	memcpy(newLayout, defaultLayout, 13);
}

int applyFinalLayout()
{
	memcpy(newArr1, defaultArr1, 176);
	memcpy(newArr2, defaultArr2, 176);

	const unsigned char OFFSET = 0x10;

	// erase trace of default controls from the arrays 
	for(int i = 0; i < 13; i++)
	{
		newArr1[defaultLayout[i] - OFFSET] = 0x14;
		newArr2[defaultLayout[i] - OFFSET] = 0x13;
	}

	if(newLayout[0] != 0) newArr1[newLayout[0] - OFFSET] = IGV_MENU; 
	if(newLayout[1] != 0) newArr1[newLayout[1] - OFFSET] = IGV_LEFT; 
	if(newLayout[2] != 0) newArr1[newLayout[2] - OFFSET] = IGV_UP; 
	if(newLayout[3] != 0) newArr1[newLayout[3] - OFFSET] = IGV_RIGHT; 
	if(newLayout[4] != 0) newArr1[newLayout[4] - OFFSET] = IGV_DOWN; 
	if(newLayout[5] != 0) newArr1[newLayout[5] - OFFSET] = IGV_WEAPONL; 
	if(newLayout[6] != 0) newArr1[newLayout[6] - OFFSET] = IGV_ITEMS; 
	if(newLayout[7] != 0) newArr1[newLayout[7] - OFFSET] = IGV_WEAPONR; 
	if(newLayout[8] != 0) newArr1[newLayout[8] - OFFSET] = IGV_MAP; 
	if(newLayout[9] != 0) newArr1[newLayout[9] - OFFSET] = IGV_SHOOT; 
	if(newLayout[10] != 0) newArr1[newLayout[10] - OFFSET] = IGV_JUMP; 
	if(newLayout[11] != 0) newArr1[newLayout[11] - OFFSET] = IGV_RESUME; 
	if(newLayout[12] != 0) newArr1[newLayout[12] - OFFSET] = IGV_RESET; 

	if(newLayout[0] != 0) newArr2[newLayout[0] - OFFSET] = IGV_MENU; 
	if(newLayout[1] != 0) newArr2[newLayout[1] - OFFSET] = IGV_LEFT; 
	if(newLayout[2] != 0) newArr2[newLayout[2] - OFFSET] = IGV_UP; 
	if(newLayout[3] != 0) newArr2[newLayout[3] - OFFSET] = IGV_RIGHT; 
	if(newLayout[4] != 0) newArr2[newLayout[4] - OFFSET] = IGV_DOWN; 
	if(newLayout[5] != 0) newArr2[newLayout[5] - OFFSET] = IGV_WEAPONL; 
	if(newLayout[6] != 0) newArr2[newLayout[6] - OFFSET] = IGV_ITEMS; 
	if(newLayout[7] != 0) newArr2[newLayout[7] - OFFSET] = IGV_WEAPONR; 
	if(newLayout[8] != 0) newArr2[newLayout[8] - OFFSET] = IGV_MAP; 
	if(newLayout[9] != 0) newArr2[newLayout[9] - OFFSET] = IGV_SHOOT; 
	if(newLayout[10] != 0) newArr2[newLayout[10] - OFFSET] = IGV_JUMP; 
	if(newLayout[11] != 0) newArr2[newLayout[11] - OFFSET] = IGV_RESUME; 
	if(newLayout[12] != 0) newArr2[newLayout[12] - OFFSET] = IGV_RESET; 

	//debug();

	FILE* out = fopen("Doukutsu.exe", "r+b");
	if(out == NULL) return -1;//printf("bruh");
	fseek(out, location1, SEEK_SET);
	fwrite(&newArr1, 176, 1, out);
	fseek(out, location2, SEEK_SET);
	fwrite(&newArr2, 176, 1, out);
	fclose(out);
	return 0;
}

void arraygetter()
{
	for(int i = 0; i < 13; i++)
	{
		printf("0x%02x, ", newLayout[i]);
	}
}

int isSupported(unsigned int wParam)
{
	if(strcmp(keyName(wParam), "NOT SUPPORTED KEY") == 0) return 0;
	return -1;
}

const char* keyName(unsigned int wParam)
{
	switch(wParam)
	{
		// this is Backspace which we'll use to unbind keys
		case 0x00:
		case 0x08: return "<NONE>";

		case 0x10: return "SHIFT";
		case 0x11: return "CTRL";
		case 0x12: return "ALT";
		case 0x13: return "PAUSE";
		case 0x14: return "CAPLOCK";
		case 0x15: return "IME Kana/Hangul";
		case 0x16: return "IME On";
		case 0x17: return "IME Junja";
		case 0x18: return "IME final";
		case 0x19: return "IME Hanja/Kanji";
		case 0x1a: return "IME Off";
		case 0x1b: return "ESC";
		case 0x1c: return "IME convert";
		case 0x1d: return "IME nonconvert";
		case 0x1e: return "IME accept";
		case 0x1f: return "IME mchr";

		case 0x20: return "SPACEBAR";
		case 0x21: return "PAGE UP";
		case 0x22: return "PAGE DOWN";
		case 0x23: return "END";
		case 0x24: return "HOME";
		case 0x25: return "LEFT ARROW";
		case 0x26: return "UP ARROW";
		case 0x27: return "RIGHT ARROW";
		case 0x28: return "DOWN ARROW";
		case 0x29: return "SELECT";
		case 0x2a: return "PRINT";
		case 0x2b: return "EXECUTE";
		//case 0x2c: return "PRINT SCREEN";
		case 0x2d: return "INS";
		case 0x2e: return "DEL";
		case 0x2f: return "HELP";
				   
		case 0x30: return "0";
		case 0x31: return "1";
		case 0x32: return "2";
		case 0x33: return "3";
		case 0x34: return "4";
		case 0x35: return "5";
		case 0x36: return "6";
		case 0x37: return "7";
		case 0x38: return "8";
		case 0x39: return "9";
		//case 0x3a: return "Undefined key";
		//case 0x3b: return "Undefined key";
		//case 0x3c: return "Undefined key";
		//case 0x3d: return "Undefined key";
		//case 0x3e: return "Undefined key";
		//case 0x3f: return "Undefined key";

		//case 0x40: return "Undefined key";
		case 0x41: return "A";
		case 0x42: return "B";
		case 0x43: return "C";
		case 0x44: return "D";
		case 0x45: return "E";
		case 0x46: return "F";
		case 0x47: return "G";
		case 0x48: return "H";
		case 0x49: return "I";
		case 0x4a: return "J";
		case 0x4b: return "K";
		case 0x4c: return "L";
		case 0x4d: return "M";
		case 0x4e: return "N";
		case 0x4f: return "O";

		case 0x50: return "P";
		case 0x51: return "Q";
		case 0x52: return "R";
		case 0x53: return "S";
		case 0x54: return "T";
		case 0x55: return "U";
		case 0x56: return "V";
		case 0x57: return "W";
		case 0x58: return "X";
		case 0x59: return "Y";
		case 0x5a: return "Z";
		//case 0x5b: return "Left Windows";
		//case 0x5c: return "Right Windows";
		case 0x5d: return "Application";
		//case 0x5e: return "Reserved";
		//case 0x5f: return "Computer Sleep";

		case 0x60: return "Num 0";
		case 0x61: return "Num 1";
		case 0x62: return "Num 2";
		case 0x63: return "Num 3";
		case 0x64: return "Num 4";
		case 0x65: return "Num 5";
		case 0x66: return "Num 6";
		case 0x67: return "Num 7";
		case 0x68: return "Num 8";
		case 0x69: return "Num 9";
		case 0x6a: return "Multiply";
		case 0x6b: return "Add";
		case 0x6c: return "Separator";
		case 0x6d: return "Subtract";
		case 0x6e: return "Decimal";
		case 0x6f: return "Divide";

		case 0x70: return "F1";
		case 0x71: return "F2";
		case 0x72: return "F3";
		case 0x73: return "F4";
		case 0x74: return "F5";
		case 0x75: return "F6";
		case 0x76: return "F7";
		case 0x77: return "F8";
		case 0x78: return "F9";
		case 0x79: return "F10";
		case 0x7a: return "F11";
		case 0x7b: return "F12";
		case 0x7c: return "F13";
		case 0x7d: return "F14";
		case 0x7e: return "F15";
		case 0x7f: return "F16";
				   
		case 0x80: return "F17";
		case 0x81: return "F18";
		case 0x82: return "F19";
		case 0x83: return "F20";
		case 0x84: return "F21";
		case 0x85: return "F22";
		case 0x86: return "F23";
		case 0x87: return "F24";
		//case 0x88:
		//case 0x89:
		//case 0x8a:
		//case 0x8b:
		//case 0x8c:
		//case 0x8d:
		//case 0x8e:
		//case 0x8f: return "Reserved";
	
		//case 0x90: return "NUM LOCK"; // decided not to use it 'cause it messes up keys to switch the signal they send here;
		case 0x91: return "SCROLL LOCK";
		// 0x92 - 0xb9 these are some obscure signals you won't ever need, trust me

		case 0xba: return ";:";
		case 0xbb: return "+";
		case 0xbc: return ",";
		case 0xbd: return "-";
		case 0xbe: return ".";
		case 0xbf: return "/?";

		default: return "NOT SUPPORTED KEY"; 
	}	
}
