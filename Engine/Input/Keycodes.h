#ifndef KEYCODES_H
#define KEYCODES_H


namespace QED
{
	namespace Engine
	{
		namespace Input
		{
			// Unindentified
			static constexpr unsigned short int key_UNKNOWN = -1;

			// Printable keys
			static constexpr unsigned short int key_SPACE			= 32;
			static constexpr unsigned short int key_APOSTROPHE		= 39;  /* ' */
			static constexpr unsigned short int key_COMMA			= 44;  /* , */
			static constexpr unsigned short int key_MINUS			= 45;  /* - */
			static constexpr unsigned short int key_PERIOD			= 46;  /* . */
			static constexpr unsigned short int key_SLASH			= 47;  /* / */
			static constexpr unsigned short int key_0				= 48;
			static constexpr unsigned short int key_1				= 49;
			static constexpr unsigned short int key_2				= 50;
			static constexpr unsigned short int key_3				= 51;
			static constexpr unsigned short int key_4				= 52;
			static constexpr unsigned short int key_5				= 53;
			static constexpr unsigned short int key_6				= 54;
			static constexpr unsigned short int key_7				= 55;
			static constexpr unsigned short int key_8				= 56;
			static constexpr unsigned short int key_9				= 57;
			static constexpr unsigned short int key_SEMICOLON		= 59;  /* ; */
			static constexpr unsigned short int key_EQUAL			= 61;  /* = */
			static constexpr unsigned short int key_A				= 65;
			static constexpr unsigned short int key_B				= 66;
			static constexpr unsigned short int key_C				= 67;
			static constexpr unsigned short int key_D				= 68;
			static constexpr unsigned short int key_E				= 69;
			static constexpr unsigned short int key_F				= 70;
			static constexpr unsigned short int key_G				= 71;
			static constexpr unsigned short int key_H				= 72;
			static constexpr unsigned short int key_I				= 73;
			static constexpr unsigned short int key_J				= 74;
			static constexpr unsigned short int key_K				= 75;
			static constexpr unsigned short int key_L				= 76;
			static constexpr unsigned short int key_M				= 77;
			static constexpr unsigned short int key_N				= 78;
			static constexpr unsigned short int key_O				= 79;
			static constexpr unsigned short int key_P				= 80;
			static constexpr unsigned short int key_Q				= 81;
			static constexpr unsigned short int key_R				= 82;
			static constexpr unsigned short int key_S				= 83;
			static constexpr unsigned short int key_T				= 84;
			static constexpr unsigned short int key_U				= 85;
			static constexpr unsigned short int key_V				= 86;
			static constexpr unsigned short int key_W				= 87;
			static constexpr unsigned short int key_X				= 88;
			static constexpr unsigned short int key_Y				= 89;
			static constexpr unsigned short int key_Z				= 90;
			static constexpr unsigned short int key_LEFT_BRACKET	= 91;  /* [ */
			static constexpr unsigned short int key_BACKSLASH		= 92;  /* \ */
			static constexpr unsigned short int key_RIGHT_BRACKET	= 93;  /* ] */
			static constexpr unsigned short int key_GRAVE_ACCENT	= 96;  /* ` */

			// Function keys
			static constexpr unsigned short int key_ESCAPE			= 256;
			static constexpr unsigned short int key_ENTER			= 257;
			static constexpr unsigned short int key_TAB				= 258;
			static constexpr unsigned short int key_BACKSPACE		= 259;
			static constexpr unsigned short int key_INSERT			= 260;
			static constexpr unsigned short int key_DELETE			= 261;
			static constexpr unsigned short int key_RIGHT			= 262;
			static constexpr unsigned short int key_LEFT			= 263;
			static constexpr unsigned short int key_DOWN			= 264;
			static constexpr unsigned short int key_UP				= 265;
			static constexpr unsigned short int key_PAGE_UP			= 266;
			static constexpr unsigned short int key_PAGE_DOWN		= 267;
			static constexpr unsigned short int key_HOME			= 268;
			static constexpr unsigned short int key_END				= 269;
			static constexpr unsigned short int key_CAPS_LOCK		= 280;
			static constexpr unsigned short int key_SCROLL_LOCK		= 281;
			static constexpr unsigned short int key_NUM_LOCK		= 282;
			static constexpr unsigned short int key_PRINT_SCREEN	= 283;
			static constexpr unsigned short int key_PAUSE			= 284;
			static constexpr unsigned short int key_F1				= 290;
			static constexpr unsigned short int key_F2				= 291;
			static constexpr unsigned short int key_F3				= 292;
			static constexpr unsigned short int key_F4				= 293;
			static constexpr unsigned short int key_F5				= 294;
			static constexpr unsigned short int key_F6				= 295;
			static constexpr unsigned short int key_F7				= 296;
			static constexpr unsigned short int key_F8				= 297;
			static constexpr unsigned short int key_F9				= 298;
			static constexpr unsigned short int key_F10				= 299;
			static constexpr unsigned short int key_F11				= 300;
			static constexpr unsigned short int key_F12				= 301;
			static constexpr unsigned short int key_F13				= 302;
			static constexpr unsigned short int key_F14				= 303;
			static constexpr unsigned short int key_F15				= 304;
			static constexpr unsigned short int key_F16				= 305;
			static constexpr unsigned short int key_F17				= 306;
			static constexpr unsigned short int key_F18				= 307;
			static constexpr unsigned short int key_F19				= 308;
			static constexpr unsigned short int key_F20				= 309;
			static constexpr unsigned short int key_F21				= 310;
			static constexpr unsigned short int key_F22				= 311;
			static constexpr unsigned short int key_F23				= 312;
			static constexpr unsigned short int key_F24				= 313;
			static constexpr unsigned short int key_F25				= 314;
			static constexpr unsigned short int key_KP_0			= 320;
			static constexpr unsigned short int key_KP_1			= 321;
			static constexpr unsigned short int key_KP_2			= 322;
			static constexpr unsigned short int key_KP_3			= 323;
			static constexpr unsigned short int key_KP_4			= 324;
			static constexpr unsigned short int key_KP_5			= 325;
			static constexpr unsigned short int key_KP_6			= 326;
			static constexpr unsigned short int key_KP_7			= 327;
			static constexpr unsigned short int key_KP_8			= 328;
			static constexpr unsigned short int key_KP_9			= 329;
			static constexpr unsigned short int key_KP_DECIMAL		= 330;
			static constexpr unsigned short int key_KP_DIVIDE		= 331;
			static constexpr unsigned short int key_KP_MULTIPLY		= 332;
			static constexpr unsigned short int key_KP_SUBTRACT		= 333;
			static constexpr unsigned short int key_KP_ADD			= 334;
			static constexpr unsigned short int key_KP_ENTER		= 335;
			static constexpr unsigned short int key_KP_EQUAL		= 336;
			static constexpr unsigned short int key_LEFT_SHIFT		= 340;
			static constexpr unsigned short int key_LEFT_CONTROL	= 341;
			static constexpr unsigned short int key_LEFT_ALT		= 342;
			static constexpr unsigned short int key_LEFT_SUPER		= 343;
			static constexpr unsigned short int key_RIGHT_SHIFT		= 344;
			static constexpr unsigned short int key_RIGHT_CONTROL	= 345;
			static constexpr unsigned short int key_RIGHT_ALT		= 346;
			static constexpr unsigned short int key_RIGHT_SUPER		= 347;
			static constexpr unsigned short int key_MENU			= 348;

			static constexpr unsigned short int key_LAST			= key_MENU;

			// Mouse buttons
			static constexpr unsigned short int mouseButton_1		= 0;
			static constexpr unsigned short int mouseButton_2		= 1;
			static constexpr unsigned short int mouseButton_3		= 2;
			static constexpr unsigned short int mouseButton_4		= 3;
			static constexpr unsigned short int mouseButton_5		= 4;
			static constexpr unsigned short int mouseButton_6		= 5;
			static constexpr unsigned short int mouseButton_7		= 6;
			static constexpr unsigned short int mouseButton_8		= 7;
			static constexpr unsigned short int mouseButton_LAST	= mouseButton_8;
			static constexpr unsigned short int mouseButton_LEFT	= mouseButton_1;
			static constexpr unsigned short int mouseButton_RIGHT	= mouseButton_2;
			static constexpr unsigned short int mouseButton_MIDDLE	= mouseButton_3;
		}
	}
}


#endif // !KEYCODES_H
