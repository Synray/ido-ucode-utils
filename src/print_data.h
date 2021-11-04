#ifndef PRINT_DATA_H
#define PRINT_DATA_H
#include "ucode.h"
extern const char *reg_names[64];
extern union Bcode u;
extern char *ustrptr;
char mtype_name(enum Memtype type);
char dtype_name(enum Datatype type);
void print_small_dtype(enum Datatype type, int length);
void print_dtype(enum Datatype type);
void print_mtype(enum Memtype type);
void print_unsigned(union Valu v);
void print_signed(union Valu v);
bool print_register(int regNum);
void print_offset(int offset, bool hasMemType);
void print_unescaped(char *s, int len);
void print_valu(union Valu v);
void print_ione(int ione);
void print_block(int block);
void print_lexlev(unsigned short lexlev);
#endif /* PRINT_DATA_H */
