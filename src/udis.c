#include <stdio.h>
#include <stdlib.h>
#include "ucode.h"
#include "common.h"
#include "libu.h"

char *ustrptr;
union Bcode u;

struct FieldNames
{
    char *lexlev;
    char *ione;
    char *offset;
    char *length;
};

static struct FieldNames field_names[Uirsv + 1] = {
    [Uloc] = {.lexlev="page", .ione="line"},
};

static struct FieldNames default_names = {.lexlev="lexlev", .ione="num", .offset="off", .length="len"};


void disassemble(char *ustr);

char mtype_name(enum Memtype type)
{
    switch (type) {
        default:  return 'U';
        case Zmt: return 'Z';
        case Pmt: return 'P';
        case Tmt: return 'T';
        case Smt: return 'S';
        case Mmt: return 'M';
        case Rmt: return 'R';
        case Amt: return 'A';
    }
}

char dtype_name(enum Datatype type)
{
    switch (type) {
        case Adt: return 'A';
        case Cdt: return 'C';
        case Fdt: return 'F';
        case Gdt: return 'G';
        case Hdt: return 'H';
        case Idt: return 'I';
        case Jdt: return 'J';
        case Kdt: return 'K';
        case Ldt: return 'L';
        case Mdt: return 'M';
        case Ndt: return 'N';
        case Pdt: return 'P';
        case Qdt: return 'Q';
        case Rdt: return 'R';
        case Sdt: return 'S';
        case Wdt: return 'W';
        case Xdt: return 'X';
        case Zdt: return 'Z';
        default: return 'U';
    }
}

void print_dtype(enum Datatype type)
{
    char dt = dtype_name(type);
    printf("%cdt ", dt);
    if (dt == 'U') printf ("(%hhu) ", type);
}

void print_mtype(enum Memtype type)
{
    char mt = mtype_name(type);
    printf("%cmt ", mt);
    if (mt == 'U') printf ("(%hhu) ", type);
}

void print_unsigned(union Valu v)
{
    switch (LENGTH) {
        case 1: printf("%hhu", (unsigned char)v.swpart.Ival); break;
        case 2: printf("%hu", (unsigned short)v.swpart.Ival); break;
        case 4: printf("%u", v.swpart.Ival); break;
        case 8: printf("%llu", v.dwval); break;
    }
}

// Print in hex if the number is bigger than 1000
void print_signed(union Valu v)
{
    switch (LENGTH) {
        case 1: printf("%hhd", (char)v.swpart.Ival); break;
        case 2: printf("%hd", (short)v.swpart.Ival); break;
        case 4: if (v.swpart.Ival > 1000) printf("0x%x", v.swpart.Ival);
                else                      printf("%d", v.swpart.Ival);
                break;
        case 8: printf("%lld", v.dwval); break;
    }
}

void print_valu(union Valu v)
{
    if (((1 << DTYPE) & ((1 << Mdt) | (1 << Qdt) | (1 << Rdt) | (1 << Sdt) | (1 << Xdt))) || OPC == Ucomm) {
        printf("\"%.*s\"", v.swpart.Ival, v.swpart.Chars);
    } else {
        switch (DTYPE) {
/* address (pointer)             */ case Adt: printf("ptr 0x%8x", v.swpart.Ival); break;
/* pointer to readonly data      */ case Cdt: printf("cptr 0x%8x", v.swpart.Ival); break;
/* C pointer to function         */ case Fdt: printf("funcptr 0x%8x", v.swpart.Ival); break;
/* address of label              */ case Gdt: printf("labelptr 0x%8x", v.swpart.Ival); break;
/* address in the heap           */ case Hdt: printf("heapptr 0x%8x", v.swpart.Ival); break;
/* integer, double word          */ case Idt: 
/* integer, single word          */ case Jdt: print_unsigned(v); break;
/* unsigned integer, double word */ case Kdt: 
/* unsigned integer, single word */ case Ldt: print_signed(v); break;
/* non-local labels              */ case Ndt: printf("label %d", v.swpart.Ival); break;
/* procedure, untyped            */ case Pdt: printf("proc 0x%8x", v.swpart.Ival); break;
/* 64 bit wide pointer           */ case Wdt: printf("wptr 0x%16llx", v.dwval); break;
/* undefined                     */ case Zdt: printf("undefined %lld", v.dwval); break;
        }
    }
}

static char *lexlev_name()
{
    if (field_names[OPC].lexlev != NULL) return field_names[OPC].lexlev;

    return default_names.lexlev;
}

static char *num_name()
{
    if (field_names[OPC].ione != NULL) return field_names[OPC].ione;

    return default_names.ione;
}

void disassemble(char *ustr)
{
    if (OPC == Ueof) return;

    struct utabrec urec = utab[OPC];
    enum uoperand part;

    if (OPC == Uent) puts("");
    printf("%.4s ", urec.opcname);

    int i = 0;
    part = urec.format[i];
    while (part != Send) {
        switch (part) {
            case Sdtype: print_dtype(DTYPE);                        break;
            case Smtype: print_mtype(MTYPE);                        break;
            case Sdtype2: printf("dt2 "); print_dtype(DTYPE2);      break;
            case Sdtypenum: printf("dtnum %d ", DTYPE);             break;

            case Slexlev: printf("%s %hu ", lexlev_name(), LEXLEV); break;

            case Slabel0: printf("lab0 %d ", IONE);                 break;
            case Slabel1: printf("lab1 %d ", IONE);                 break;
            case Sblockno: printf("block %d ", IONE);               break;
            case Ssomenumber: printf("%s %d ", num_name(), IONE);   break;

            case Spop: printf("pop %u ", POP);                      break;
            case Spush: printf("push %u ", PUSH);                   break;
            case Sexternal: printf("ext %u ", EXTRNAL);             break;
            case Slength: printf("len %d ", LENGTH);                break;

            case Sconstval: printf("cval ");
            case Scomment:  print_valu(CONSTVAL);                   break;

            case Sinitval:  printf("init "); print_valu(INITVAL);   break;

            case Soffset: printf("off %d ", OFFSET);                break;
            case Soffset2: printf("off2 %d ", OFFSET2);             break;
            case Slabel2: printf("lab2 %d ", LENGTH);               break;
            case SarrayOffset: printf("aryoff %d ", ARYOFF);        break;

            case Slbound: printf("lbnd %lld ", LBOUND);             break;
            case Shbound: printf("hbnd %lld ", HBOUND);             break;

            case Send:
            default:                                                break;
        }

        i++;
        part = urec.format[i];
    }
    puts("");
}

void read_ucode()
{
    do {
        readuinstr(&u, ustrptr);
        disassemble(ustrptr);
    } while (OPC != Ueof);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        abort();

    uini();
    initur(argv[1]);

    ustrptr = calloc(1, 0x400);

    read_ucode();

    free(ustrptr);
}
