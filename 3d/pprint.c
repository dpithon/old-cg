static void printv(coord_st  *u)
{
	printf("%6.2f %6.2f %6.2f %6.2f", u->x, u->y, u->z, u->w);
}

static void pretty_printv(const char *s, coord_st  *u)
{
	fprintf(stderr,"%s%6.2f %6.2f %6.2f %6.2f\n", s, u->x, u->y, u->z, u->w);
}

static void pretty_printm(matrix_st *m)
{
	pretty_printv("", &(m->rows.r1));
	pretty_printv("", &(m->rows.r2));
	pretty_printv("", &(m->rows.r3));
	pretty_printv("", &(m->rows.r4));
	printf("\n");
}


