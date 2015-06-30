//-----------------------------------------------------------------------------
#include "actualkeycodes.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
// 實際鍵盤掃描碼轉換自訂鍵盤掃描碼
ENUM_AKCodes convakcode(IN int ik1, IN int ik2)
{
	if(ik1 == 0x00 || ik1 == 0xe0)
	{
		switch(ik2)
		{
		case 0x3b: return ENUM_AKCodes_F1;
		case 0x3c: return ENUM_AKCodes_F2;
		case 0x3d: return ENUM_AKCodes_F3;
		case 0x3e: return ENUM_AKCodes_F4;
		case 0x3f: return ENUM_AKCodes_F5;
		case 0x40: return ENUM_AKCodes_F6;
		case 0x41: return ENUM_AKCodes_F7;
		case 0x42: return ENUM_AKCodes_F8;
		case 0x43: return ENUM_AKCodes_F9;
		case 0x44: return ENUM_AKCodes_F10;
		case 0x85: return ENUM_AKCodes_F11;
		case 0x86: return ENUM_AKCodes_F12;
		case 0x47: return ENUM_AKCodes_HOME;
		case 0x4f: return ENUM_AKCodes_END;
		case 0x52: return ENUM_AKCodes_INSERT;
		case 0x53: return ENUM_AKCodes_DELETE;
		case 0x49: return ENUM_AKCodes_PAGEUP;
		case 0x51: return ENUM_AKCodes_PAGEDOWN;
		case 0x48: return ENUM_AKCodes_UP;
		case 0x50: return ENUM_AKCodes_DOWN;
		case 0x4b: return ENUM_AKCodes_LEFT;
		case 0x4d: return ENUM_AKCodes_RIGHT;
		default: return ENUM_AKCodes_NULL;
		}//switch
	}
	else
	{
		switch(ik1)
		{
		case 0x08: return ENUM_AKCodes_BACKSPACE;
		case 0x09: return ENUM_AKCodes_TAB;
		case 0x0d: return ENUM_AKCodes_ENTER;
		case 0x1b: return ENUM_AKCodes_ESC;
		case 0x20: return ENUM_AKCodes_SPACE;
		case 0x30: return ENUM_AKCodes_0;
		case 0x31: return ENUM_AKCodes_1;
		case 0x32: return ENUM_AKCodes_2;
		case 0x33: return ENUM_AKCodes_3;
		case 0x34: return ENUM_AKCodes_4;
		case 0x35: return ENUM_AKCodes_5;
		case 0x36: return ENUM_AKCodes_6;
		case 0x37: return ENUM_AKCodes_7;
		case 0x38: return ENUM_AKCodes_8;
		case 0x39: return ENUM_AKCodes_9;
		case 0x41: return ENUM_AKCodes_A;
		case 0x42: return ENUM_AKCodes_B;
		case 0x43: return ENUM_AKCodes_C;
		case 0x44: return ENUM_AKCodes_D;
		case 0x45: return ENUM_AKCodes_E;
		case 0x46: return ENUM_AKCodes_F;
		case 0x47: return ENUM_AKCodes_G;
		case 0x48: return ENUM_AKCodes_H;
		case 0x49: return ENUM_AKCodes_I;
		case 0x4a: return ENUM_AKCodes_J;
		case 0x4b: return ENUM_AKCodes_K;
		case 0x4c: return ENUM_AKCodes_L;
		case 0x4d: return ENUM_AKCodes_M;
		case 0x4e: return ENUM_AKCodes_N;
		case 0x4f: return ENUM_AKCodes_O;
		case 0x50: return ENUM_AKCodes_P;
		case 0x51: return ENUM_AKCodes_Q;
		case 0x52: return ENUM_AKCodes_R;
		case 0x53: return ENUM_AKCodes_S;
		case 0x54: return ENUM_AKCodes_T;
		case 0x55: return ENUM_AKCodes_U;
		case 0x56: return ENUM_AKCodes_V;
		case 0x57: return ENUM_AKCodes_W;
		case 0x58: return ENUM_AKCodes_X;
		case 0x59: return ENUM_AKCodes_Y;
		case 0x5a: return ENUM_AKCodes_Z;
		case 0x61: return ENUM_AKCodes_a;
		case 0x62: return ENUM_AKCodes_b;
		case 0x63: return ENUM_AKCodes_c;
		case 0x64: return ENUM_AKCodes_d;
		case 0x65: return ENUM_AKCodes_e;
		case 0x66: return ENUM_AKCodes_f;
		case 0x67: return ENUM_AKCodes_g;
		case 0x68: return ENUM_AKCodes_h;
		case 0x69: return ENUM_AKCodes_i;
		case 0x6a: return ENUM_AKCodes_j;
		case 0x6b: return ENUM_AKCodes_k;
		case 0x6c: return ENUM_AKCodes_l;
		case 0x6d: return ENUM_AKCodes_m;
		case 0x6e: return ENUM_AKCodes_n;
		case 0x6f: return ENUM_AKCodes_o;
		case 0x70: return ENUM_AKCodes_p;
		case 0x71: return ENUM_AKCodes_q;
		case 0x72: return ENUM_AKCodes_r;
		case 0x73: return ENUM_AKCodes_s;
		case 0x74: return ENUM_AKCodes_t;
		case 0x75: return ENUM_AKCodes_u;
		case 0x76: return ENUM_AKCodes_v;
		case 0x77: return ENUM_AKCodes_w;
		case 0x78: return ENUM_AKCodes_x;
		case 0x79: return ENUM_AKCodes_y;
		case 0x7a: return ENUM_AKCodes_z;
		case 0x21: return ENUM_AKCodes_SYM21;
		case 0x22: return ENUM_AKCodes_SYM22;
		case 0x23: return ENUM_AKCodes_SYM23;
		case 0x24: return ENUM_AKCodes_SYM24;
		case 0x25: return ENUM_AKCodes_SYM25;
		case 0x26: return ENUM_AKCodes_SYM26;
		case 0x27: return ENUM_AKCodes_SYM27;
		case 0x28: return ENUM_AKCodes_SYM28;
		case 0x29: return ENUM_AKCodes_SYM29;
		case 0x2a: return ENUM_AKCodes_SYM2A;
		case 0x2b: return ENUM_AKCodes_SYM2B;
		case 0x2c: return ENUM_AKCodes_SYM2C;
		case 0x2d: return ENUM_AKCodes_SYM2D;
		case 0x2e: return ENUM_AKCodes_SYM2E;
		case 0x2f: return ENUM_AKCodes_SYM2F;
		case 0x3a: return ENUM_AKCodes_SYM3A;
		case 0x3b: return ENUM_AKCodes_SYM3B;
		case 0x3c: return ENUM_AKCodes_SYM3C;
		case 0x3d: return ENUM_AKCodes_SYM3D;
		case 0x3e: return ENUM_AKCodes_SYM3E;
		case 0x3f: return ENUM_AKCodes_SYM3F;
		case 0x40: return ENUM_AKCodes_SYM40;
		case 0x5b: return ENUM_AKCodes_SYM5B;
		case 0x5c: return ENUM_AKCodes_SYM5C;
		case 0x5d: return ENUM_AKCodes_SYM5D;
		case 0x5e: return ENUM_AKCodes_SYM5E;
		case 0x5f: return ENUM_AKCodes_SYM5F;
		case 0x60: return ENUM_AKCodes_SYM60;
		case 0x7b: return ENUM_AKCodes_SYM7B;
		case 0x7c: return ENUM_AKCodes_SYM7C;
		case 0x7d: return ENUM_AKCodes_SYM7D;
		case 0x7e: return ENUM_AKCodes_SYM7E;
		default: return ENUM_AKCodes_NULL;
		}//switch
	}//if
}
//-----------------------------------------------------------------------------
// 取得鍵盤掃描結果, 鍵入的字元不會出現在console視窗上
ENUM_AKCodes getakcode()
{
	int ik1 = _getch();
	int ik2 = (ik1 == 0x00 || ik1 == 0xe0) ? _getch() : ik1;

	return convakcode(ik1, ik2);
}
//-----------------------------------------------------------------------------
// 取得鍵盤掃描結果, 鍵入的字元會出現在console視窗上
ENUM_AKCodes getakcodee()
{
	int ik1 = _getche();
	int ik2 = (ik1 == 0x00 || ik1 == 0xe0) ? _getche() : ik1;

	return convakcode(ik1, ik2);
}
//-----------------------------------------------------------------------------
// 取得自訂鍵盤掃描碼的描述字串
nstring akcodestr(IN ENUM_AKCodes emAkCode)
{
	switch(emAkCode)
	{
	case ENUM_AKCodes_0: return __T("0");
	case ENUM_AKCodes_1: return __T("1");
	case ENUM_AKCodes_2: return __T("2");
	case ENUM_AKCodes_3: return __T("3");
	case ENUM_AKCodes_4: return __T("4");
	case ENUM_AKCodes_5: return __T("5");
	case ENUM_AKCodes_6: return __T("6");
	case ENUM_AKCodes_7: return __T("7");
	case ENUM_AKCodes_8: return __T("8");
	case ENUM_AKCodes_9: return __T("9");
	case ENUM_AKCodes_A: return __T("A");
	case ENUM_AKCodes_B: return __T("B");
	case ENUM_AKCodes_C: return __T("C");
	case ENUM_AKCodes_D: return __T("D");
	case ENUM_AKCodes_E: return __T("E");
	case ENUM_AKCodes_F: return __T("F");
	case ENUM_AKCodes_G: return __T("G");
	case ENUM_AKCodes_H: return __T("H");
	case ENUM_AKCodes_I: return __T("I");
	case ENUM_AKCodes_J: return __T("J");
	case ENUM_AKCodes_K: return __T("K");
	case ENUM_AKCodes_L: return __T("L");
	case ENUM_AKCodes_M: return __T("M");
	case ENUM_AKCodes_N: return __T("N");
	case ENUM_AKCodes_O: return __T("O");
	case ENUM_AKCodes_P: return __T("P");
	case ENUM_AKCodes_Q: return __T("Q");
	case ENUM_AKCodes_R: return __T("R");
	case ENUM_AKCodes_S: return __T("S");
	case ENUM_AKCodes_T: return __T("T");
	case ENUM_AKCodes_U: return __T("U");
	case ENUM_AKCodes_V: return __T("V");
	case ENUM_AKCodes_W: return __T("W");
	case ENUM_AKCodes_X: return __T("X");
	case ENUM_AKCodes_Y: return __T("Y");
	case ENUM_AKCodes_Z: return __T("Z");
	case ENUM_AKCodes_a: return __T("a");
	case ENUM_AKCodes_b: return __T("b");
	case ENUM_AKCodes_c: return __T("c");
	case ENUM_AKCodes_d: return __T("d");
	case ENUM_AKCodes_e: return __T("e");
	case ENUM_AKCodes_f: return __T("f");
	case ENUM_AKCodes_g: return __T("g");
	case ENUM_AKCodes_h: return __T("h");
	case ENUM_AKCodes_i: return __T("i");
	case ENUM_AKCodes_j: return __T("j");
	case ENUM_AKCodes_k: return __T("k");
	case ENUM_AKCodes_l: return __T("l");
	case ENUM_AKCodes_m: return __T("m");
	case ENUM_AKCodes_n: return __T("n");
	case ENUM_AKCodes_o: return __T("o");
	case ENUM_AKCodes_p: return __T("p");
	case ENUM_AKCodes_q: return __T("q");
	case ENUM_AKCodes_r: return __T("r");
	case ENUM_AKCodes_s: return __T("s");
	case ENUM_AKCodes_t: return __T("t");
	case ENUM_AKCodes_u: return __T("u");
	case ENUM_AKCodes_v: return __T("v");
	case ENUM_AKCodes_w: return __T("w");
	case ENUM_AKCodes_x: return __T("x");
	case ENUM_AKCodes_y: return __T("y");
	case ENUM_AKCodes_z: return __T("z");
	case ENUM_AKCodes_SYM21: return __T("!");
	case ENUM_AKCodes_SYM22: return __T("\"");
	case ENUM_AKCodes_SYM23: return __T("#");
	case ENUM_AKCodes_SYM24: return __T("$");
	case ENUM_AKCodes_SYM25: return __T("%");
	case ENUM_AKCodes_SYM26: return __T("&");
	case ENUM_AKCodes_SYM27: return __T("'");
	case ENUM_AKCodes_SYM28: return __T("(");
	case ENUM_AKCodes_SYM29: return __T(")");
	case ENUM_AKCodes_SYM2A: return __T("*");
	case ENUM_AKCodes_SYM2B: return __T("+");
	case ENUM_AKCodes_SYM2C: return __T(",");
	case ENUM_AKCodes_SYM2D: return __T("-");
	case ENUM_AKCodes_SYM2E: return __T(".");
	case ENUM_AKCodes_SYM2F: return __T("/");
	case ENUM_AKCodes_SYM3A: return __T(":");
	case ENUM_AKCodes_SYM3B: return __T(";");
	case ENUM_AKCodes_SYM3C: return __T("<");
	case ENUM_AKCodes_SYM3D: return __T("=");
	case ENUM_AKCodes_SYM3E: return __T(">");
	case ENUM_AKCodes_SYM3F: return __T("?");
	case ENUM_AKCodes_SYM40: return __T("@");
	case ENUM_AKCodes_SYM5B: return __T("[");
	case ENUM_AKCodes_SYM5C: return __T("\\");
	case ENUM_AKCodes_SYM5D: return __T("]");
	case ENUM_AKCodes_SYM5E: return __T("^");
	case ENUM_AKCodes_SYM5F: return __T("_");
	case ENUM_AKCodes_SYM60: return __T("`");
	case ENUM_AKCodes_SYM7B: return __T("{");
	case ENUM_AKCodes_SYM7C: return __T("|");
	case ENUM_AKCodes_SYM7D: return __T("}");
	case ENUM_AKCodes_SYM7E: return __T("~");
	case ENUM_AKCodes_SPACE: return __T("SPACE");
	case ENUM_AKCodes_BACKSPACE: return __T("BACKSPACE");
	case ENUM_AKCodes_TAB: return __T("TAB");
	case ENUM_AKCodes_ENTER: return __T("ENTER");
	case ENUM_AKCodes_ESC: return __T("ESC");
	case ENUM_AKCodes_F1: return __T("F1");
	case ENUM_AKCodes_F2: return __T("F2");
	case ENUM_AKCodes_F3: return __T("F3");
	case ENUM_AKCodes_F4: return __T("F4");
	case ENUM_AKCodes_F5: return __T("F5");
	case ENUM_AKCodes_F6: return __T("F6");
	case ENUM_AKCodes_F7: return __T("F7");
	case ENUM_AKCodes_F8: return __T("F8");
	case ENUM_AKCodes_F9: return __T("F9");
	case ENUM_AKCodes_F10: return __T("F10");
	case ENUM_AKCodes_F11: return __T("F11");
	case ENUM_AKCodes_F12: return __T("F12");
	case ENUM_AKCodes_HOME: return __T("HOME");
	case ENUM_AKCodes_END: return __T("END");
	case ENUM_AKCodes_INSERT: return __T("INSERT");
	case ENUM_AKCodes_DELETE: return __T("DELETE");
	case ENUM_AKCodes_PAGEUP: return __T("PAGEUP");
	case ENUM_AKCodes_PAGEDOWN: return __T("PAGEDOWN");
	case ENUM_AKCodes_UP: return __T("UP");
	case ENUM_AKCodes_DOWN: return __T("DOWN");
	case ENUM_AKCodes_LEFT: return __T("LEFT");
	case ENUM_AKCodes_RIGHT: return __T("RIGHT");
	default: return __T("unknow");
	}//switch
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------