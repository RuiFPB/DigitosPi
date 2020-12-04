#ifndef PI2_H
#define PI2_H

void arctan(long *resultado, long *w1, long *w2, long denom, long onestep);
void copy(long *resultado, long *inic);
void set(long *result, long rhs);
bool zero(long *resultado);
void sub(long *resultado, long *val);
void add(long *resultado, long *val);
void mult(long *resultado, long val);
void div(long *resultado, long denom);
void escreve(long *resultado);

#endif