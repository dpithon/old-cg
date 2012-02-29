#ifndef _RGP_H
#define _RGP_H

void rgp_init(int, int, int, char *argv[]);
void rgp_gui_main(void);

void rgp_set_color(unsigned char, unsigned char, unsigned char);

void rgp_point(int, int);
void rgp_line(int, int, int, int);

#endif /* _RGP_H */
