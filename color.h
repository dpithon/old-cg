#ifndef _COLOR_H
#define _COLOR_H

typedef struct rgb {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} rgb_t;

#define RGBWhite	{ 0xFF, 0xFF, 0xFF }
#define RGBBlack	{ 0x00, 0x00, 0x00 }
#define RGBRed		{ 0xFF, 0x00, 0x00 }
#define RGBGreen	{ 0x00, 0xFF, 0x00 }
#define RGBBlue		{ 0x00, 0x00, 0xFF }
#define RGBYellow	{ 0xFF, 0xFF, 0x00 }
#define RGBMagenta	{ 0xFF, 0x00, 0xFF }
#define RGBCyan		{ 0x00, 0xFF, 0xFF }
#define RGBLightGray	{ 0xCC, 0xCC, 0xCC }
#define RGBDarkGray	{ 0x33, 0x33, 0x33 }

#endif /* _COLOR_H*/
