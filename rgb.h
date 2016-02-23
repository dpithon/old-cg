#ifndef RGB_H
#define RGB_H

struct rgb {
	float r;
	float g;
	float b;
};

#define RGBWhite	1.00F, 1.00F, 1.00F
#define RGBBlack	0.00F, 0.00F, 0.00F

#define RGBRed		1.00F, 0.00F, 0.00F
#define RGBGreen	0.00F, 1.00F, 0.00F
#define RGBBlue		0.00F, 0.00F, 1.00F

#define RGBYellow	1.00F, 1.00F, 0.00F
#define RGBMagenta	1.00F, 0.00F, 1.00F
#define RGBCyan		0.00F, 1.00F, 1.00F

#define RGBLightGray	0.80F, 0.80F, 0.80F
#define RGBDarkGray	0.20F, 0.20F, 0.20F
#define RGBLightBlue	0.06F, 0.06F, 0.86F
#define RGBDarkBlue	0.06F, 0.06F, 0.33F

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
