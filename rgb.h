#ifndef RGB_H
#define RGB_H

struct rgb {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

#define RGBWhite	0xFF, 0xFF, 0xFF
#define RGBBlack	0x00, 0x00, 0x00
#define RGBRed		0xFF, 0x00, 0x00
#define RGBGreen	0x00, 0xFF, 0x00
#define RGBBlue		0x00, 0x00, 0xFF
#define RGBYellow	0xFF, 0xFF, 0x00
#define RGBMagenta	0xFF, 0x00, 0xFF
#define RGBCyan		0x00, 0xFF, 0xFF
#define RGBLightGray	0xCC, 0xCC, 0xCC
#define RGBDarkGray	0x33, 0x33, 0x33
#define RGBLightBlue	0x11, 0x11, 0xDD
#define RGBDarkBlue	0x11, 0x11, 0x55

#define White		{ RGBWhite	 }
#define Black		{ RGBBlack	 }
#define Red		{ RGBRed	 }
#define Green		{ RGBGreen	 }
#define Blue		{ RGBBlue	 }
#define Yellow		{ RGBYellow	 }
#define Magenta		{ RGBMagenta	 }
#define Cyan		{ RGBCyan	 }
#define LightGray	{ RGBLightGray	 }
#define DarkGray	{ RGBDarkGray	 }
#define LightBlue	{ RGBLightBlue	 }
#define DarkBlue	{ RGBDarkBlue	 }

#endif /* RGB_H*/
