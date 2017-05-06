#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl/gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <vector>
#include "baseTypes.h"
#include "SixteenSegmentManager.h"
#include "StateManager.h"
#include "ScoreBoardManager.h"
#include "ShapeDraw.h"


/**
 * A manager for rendering text and numeric values in a sixteen segment display format
 * Each segment render call is relegated to its own function
 * These functions are enumerated in an array of function pointers
 * Rendering occurs via passing a 16-bit value, each bit (starting from the least significant)
 * if the bit is flagged, the corresponding function renders an "active" segment, otherwise an "inactive" segment is rendered
 * 16-bit value constants are defined in the header file
 *
 * Display Data:
 * 16-segment display data
 * width  = 47
 * height = 85
 * horizontal segment length: 19 
 * vertical segment length: 38
 * number of horizontal chunks in diagonal segment: 12
 */

SixteenSegmentManager* SixteenSegmentManager::instance = NULL;

SixteenSegmentManager::SixteenSegmentManager()
{
	initializeFunctionPointers();
}

SixteenSegmentManager::~SixteenSegmentManager()
{
}

/**
 * Singleton accessor method
 */
SixteenSegmentManager* SixteenSegmentManager::GetInstance()
{
	instance = !instance ? new SixteenSegmentManager() : instance;
	return instance;
}

/**
 * Initializes the array of function pointers
 */
void SixteenSegmentManager::initializeFunctionPointers()
{
	displaySegment[0]  = &SixteenSegmentManager::seg_0;
	displaySegment[1]  = &SixteenSegmentManager::seg_1;
	displaySegment[2]  = &SixteenSegmentManager::seg_2;
	displaySegment[3]  = &SixteenSegmentManager::seg_3;
	displaySegment[4]  = &SixteenSegmentManager::seg_4;
	displaySegment[5]  = &SixteenSegmentManager::seg_5;
	displaySegment[6]  = &SixteenSegmentManager::seg_6;
	displaySegment[7]  = &SixteenSegmentManager::seg_7;
	displaySegment[8]  = &SixteenSegmentManager::seg_8;
	displaySegment[9]  = &SixteenSegmentManager::seg_9;
	displaySegment[10] = &SixteenSegmentManager::seg_A;
	displaySegment[11] = &SixteenSegmentManager::seg_B;
	displaySegment[12] = &SixteenSegmentManager::seg_C;
	displaySegment[13] = &SixteenSegmentManager::seg_D;
	displaySegment[14] = &SixteenSegmentManager::seg_E;
	displaySegment[15] = &SixteenSegmentManager::seg_F;
}

/**
 * Renders a single display with all segments set to the same state
 * 
 * @Param on: segment state
 * @Param x: x location of the display
 * @Param y: y location of the display
 */
void SixteenSegmentManager::renderAllSegments(bool8_t on, uint32_t x, uint32_t y)
{
	for (int i = 0; i < 16; i++)
	{
		(this->*(this->displaySegment[i]))(on, x, y);
	}
}

/**
 * Displays a string of alphanumeric characters as a series of 16-segment displays
 * 
 * @Param word: The string being rendered
 * @Param x: x location of the display
 * @Param y: y location of the display
 */
void SixteenSegmentManager::displayString(char8_t* word, uint32_t x, uint32_t y)
{
	for (int i = 0; i < strlen(word); i++)
	{

		render(word[i], x + (50 * i), y);
	}
}

/**
 * Renders a character to the screen as a 16-segment display
 * 
 * @Param value: 16-bit character value being rendered to the screen
 * @Param x: x location of the display
 * @Param y: y location of the display
 */
void SixteenSegmentManager::render(uint16_t value, uint32_t x, uint32_t y)
{
	for (auto i = 0; i < 16; i++)
	{
		auto segBit = value & 0x0001;
		(this->*(this->displaySegment[i]))(segBit, x, y);
		value >>= 1;
	}
}

/**
 * Renders a character to the screen
 * 
 * @Param c: Character being rendered
 * @Param x: x location of the display
 * @Param y: y location of the display
 */
void SixteenSegmentManager::render(char8_t c, uint32_t x, uint32_t y)
{
	switch(c)
	{
		case 'a':
			render(A, x, y);
			break;
		case 'b':
			render(B, x, y);
			break;
		case 'c':
			render(C, x, y);
			break;
		case 'd':
			render(D, x, y);
			break;
		case 'e':
			render(E, x, y);
			break;
		case 'f':
			render(F, x, y);
			break;
		case 'g':
			render(G, x, y);
			break;
		case 'h':
			render(H, x, y);
			break;
		case 'i':
			render(I, x, y);
			break;
		case 'j':
			render(J, x, y);
			break;
		case 'k':
			render(K, x, y);
			break;
		case 'l':
			render(L, x, y);
			break;
		case 'm':
			render(M, x, y);
			break;
		case 'n':
			render(N, x, y);
			break;
		case 'o':
			render(O, x, y);
			break;
		case 'p':
			render(P, x, y);
			break;
		case 'q':
			render(Q, x, y);
			break;
		case 'r':
			render(R, x, y);
			break;
		case 's':
			render(S, x, y);
			break;
		case 't':
			render(T, x, y);
			break;
		case 'u':	
			render(U, x, y);
			break;
		case 'v':
			render(V, x, y);
			break;
		case 'w':
			render(W, x, y);
			break;
		case 'x':
			render(X, x, y);
			break;
		case 'y':
			render(Y, x, y);
			break;
		case 'z':
			render(Z, x, y);
			break;
		case '0':
			render(ZERO, x, y);
			break;
		case '1':
			render(ONE, x, y);
			break;
		case '2':
			render(TWO, x, y);
			break;
		case '3':
			render(THREE, x, y);
			break;
		case '4':
			render(FOUR, x, y);
			break;
		case '5':
			render(FIVE, x, y);
			break;
		case '6':
			render(SIX, x, y);
			break;
		case '7':
			render(SEVEN, x, y);
			break;
		case '8':
			render(EIGHT, x, y);
			break;
		case '9':
			render(NINE, x, y);
			break;
		default:
			break;
	}
}

void SixteenSegmentManager::seg_0(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	for (auto i = 0; i < 4; i++)
	{
		DrawLine(x + 4 + i, y + 81 + i, x + 22 - i, y + 81 + i, color, color, color, color);
		DrawLine(x + 4 + i, y + 81 - i, x + 22 - i, y + 81 - i, color, color, color, color);
	}
}

void SixteenSegmentManager::seg_1(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	for (auto i = 0; i < 4; i++)
	{
		DrawLine(x + 24 + i, y + 81 + i, x + 42 - i, y + 81 + i, color, color, color, color);
		DrawLine(x + 24 + i, y + 81 - i, x + 42 - i, y + 81 - i, color, color, color, color);
	}
}

void SixteenSegmentManager::seg_2(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	for (auto i = 0; i < 4; i++)
	{
		DrawLine(x + 43 - i, y + 80 - i, x + 43 - i, y + 43 + i, color, color, color, color);
		DrawLine(x + 43 + i, y + 80 - i, x + 43 + i, y + 43 + i, color, color, color, color);
	}
}

void SixteenSegmentManager::seg_3(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	for (auto i = 0; i < 4; i++)
	{
		DrawLine(x + 43 - i, y + 41 - i, x + 43 - i, y + 4 + i, color, color, color, color);
		DrawLine(x + 43 + i, y + 41 - i, x + 43 + i, y + 4 + i, color, color, color, color);
	}
}

void SixteenSegmentManager::seg_4(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	for (auto i = 0; i < 4; i++)
	{
		DrawLine(x + 24 + i, y + 3 + i, x + 42 - i, y + 3 + i, color, color, color, color);
		DrawLine(x + 24 + i, y + 3 - i, x + 42 - i, y + 3 - i, color, color, color, color);
	}
}

void SixteenSegmentManager::seg_5(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	for (auto i = 0; i < 4; i++)
	{
		DrawLine(x + 4 + i, y + 3 + i, x + 22 - i, y + 3 + i, color, color, color, color);
		DrawLine(x + 4 + i, y + 3 - i, x + 22 - i, y + 3 - i, color, color, color, color);
	}
}

void SixteenSegmentManager::seg_6(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	for (auto i = 0; i < 4; i++)
	{
		DrawLine(x + 3 - i, y + 4 + i, x + 3 - i, y + 41 - i, color, color, color, color);
		DrawLine(x + 3 + i, y + 4 + i, x + 3 + i, y + 41 - i, color, color, color, color);
	}
}

void SixteenSegmentManager::seg_7(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	for (auto i = 0; i < 4; i++)
	{
		DrawLine(x + 3 - i, y + 43 + i, x + 3 - i, y + 81 - i, color, color, color, color);
		DrawLine(x + 3 + i, y + 43 + i, x + 3 + i, y + 81 - i, color, color, color, color);
	}
}

void SixteenSegmentManager::seg_8(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	auto tl_x = x + 8;
	auto tl_y = y + 76;

	for (auto i = 0; i < 3; i++)
	{
		DrawLine(tl_x + i, tl_y, 
			tl_x + i, tl_y - (9 + 3 * i), 
			color, color, color, color);
		DrawLine(tl_x + 8 + i, tl_y - (15 + 3 * i), 
			tl_x + 8 + i, tl_y - 30, 
			color, color, color, color);
	}

	for (auto i = 0; i < 5; i++)
	{
		DrawLine(tl_x + 3 + i, 
			tl_y - (3 * i), tl_x + 3 + i, 
			tl_y - (18 + 3 * i), 
			color, color, color, color);
	}
}

void SixteenSegmentManager::seg_9(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	for (auto i = 0; i < 4; i++)
	{
		DrawLine(x + 23 - i, y + 43 + i, x + 23 - i, y + 81 - i, color, color, color, color);
		DrawLine(x + 23 + i, y + 43 + i, x + 23 + i, y + 81 - i, color, color, color, color);
	}
}

void SixteenSegmentManager::seg_A(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	auto bl_x = x + 28;
	auto bl_y = y + 47;

	for (auto i = 0; i < 3; i++)
	{
		DrawLine(bl_x + i, bl_y,
			bl_x + i, bl_y + (9 + 3 * i),
			color, color, color, color);
		DrawLine(bl_x + 8 + i, bl_y + (15 + 3 * i),
			bl_x + 8 + i, bl_y + 30,
			color, color, color, color);
	}

	for (auto i = 0; i < 5; i++)
	{
		DrawLine(bl_x + 3 + i, bl_y + (3 * i), 
			bl_x + 3 + i, bl_y + (18 + 3 * i),
			color, color, color, color);
	}
}

void SixteenSegmentManager::seg_B(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	for (auto i = 0; i < 4; i++)
	{
		DrawLine(x + 24 + i, y + 42 + i, x + 42 - i, y + 42 + i, color, color, color, color);
		DrawLine(x + 24 + i, y + 42 - i, x + 42 - i, y + 42 - i, color, color, color, color);
	}
}

void SixteenSegmentManager::seg_C(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	auto tl_x = x + 28;
	auto tl_y = y + 37;

	for (auto i = 0; i < 3; i++)
	{
		DrawLine(tl_x + i, tl_y,
			tl_x + i, tl_y - (9 + 3 * i),
			color, color, color, color);
		DrawLine(tl_x + 8 + i, tl_y - (15 + 3 * i),
			tl_x + 8 + i, tl_y - 30,
			color, color, color, color);
	}

	for (auto i = 0; i < 5; i++)
	{
		DrawLine(tl_x + 3 + i,
			tl_y - (3 * i), tl_x + 3 + i,
			tl_y - (18 + 3 * i),
			color, color, color, color);
	}
}

void SixteenSegmentManager::seg_D(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	for (auto i = 0; i < 4; i++)
	{
		DrawLine(x + 23 - i, y + 4 + i, x + 23 - i, y + 42 - i, color, color, color, color);
		DrawLine(x + 23 + i, y + 4 + i, x + 23 + i, y + 42 - i, color, color, color, color);
	}
}

void SixteenSegmentManager::seg_E(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	auto bl_x = x + 8;
	auto bl_y = y + 8;

	for (auto i = 0; i < 3; i++)
	{
		DrawLine(bl_x + i, bl_y,
			bl_x + i, bl_y + (9 + 3 * i),
			color, color, color, color);
		DrawLine(bl_x + 8 + i, bl_y + (15 + 3 * i),
			bl_x + 8 + i, bl_y + 30,
			color, color, color, color);
	}

	for (auto i = 0; i < 5; i++)
	{
		DrawLine(bl_x + 3 + i, bl_y + (3 * i),
			bl_x + 3 + i, bl_y + (18 + 3 * i),
			color, color, color, color);
	}
}

void SixteenSegmentManager::seg_F(bool8_t on, uint32_t x, uint32_t y)
{
	auto color = on ? SEG_ON : SEG_OFF;
	for (auto i = 0; i < 4; i++)
	{
		DrawLine(x + 4 + i, y + 42 + i, x + 22 - i, y + 42 + i, color, color, color, color);
		DrawLine(x + 4 + i, y + 42 - i, x + 22 - i, y + 42 - i, color, color, color, color);
	}
}
