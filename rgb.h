#ifndef RGB_H
#define RGB_H

struct rgb {
	double r;
	double g;
	double b;
};

#define RGBWhite	1.00, 1.00, 1.00
#define RGBBlack	0.00, 0.00, 0.00

#define RGBRed		1.00, 0.00, 0.00
#define RGBGreen	0.00, 1.00, 0.00
#define RGBBlue		0.00, 0.00, 1.00

#define RGBYellow	1.00, 1.00, 0.00
#define RGBMagenta	1.00, 0.00, 1.00
#define RGBCyan		0.00, 1.00, 1.00

#define RGBLightGray	0.80, 0.80, 0.80
#define RGBDarkGray	0.20, 0.20, 0.20
#define RGBLightBlue	0.06, 0.06, 0.86
#define RGBDarkBlue	0.06, 0.06, 0.33

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
