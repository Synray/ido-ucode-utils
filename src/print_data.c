#include <ctype.h>

#include "print_data.h"
#include "common.h"
#include "libu.h"

const char *reg_names[64] = {
    "$zero",
    "$at",
    "$v0", "$v1",
    "$a0", "$a1", "$a2", "$a3",
    "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
    "$t8", "$t9",
    "$k0", "$k1",
    "$gp",
    "$sp", "$fp",
    "$ra",
    "$f0", "$f1", "$f2", "$f3",
    "$f4", "$f5", "$f6", "$f7", "$f8", "$f9", "$f10", "$f11",
    "$f12", "$f13", "$f14", "$f15",
    "$f16", "$f17", "$f18", "$f19",
    "$f20", "$f21", "$f22", "$f23", "$f24", "$f25",
    "$f26", "$f27", "$f28", "$f29", "$f30", "$f31",
};

struct FieldNames {
    const char *lexlev;
    const char *ione;
    const char *offset;
    const char *length;
};

static struct FieldNames field_names[Uirsv + 1] = {
    [Uloc] = {.lexlev="page", .ione="line"},

    [Uixa] = {.ione="i"},
    [Uilod] = {/* .lexlev="bits", */ .ione="i"},
    [Uistr] = {/* .lexlev="bits", */ .ione="i"},
    [Umov] = {.lexlev="dst_align", .ione="src_align"},

    [Uregs] = {.ione="class"},
};

static struct FieldNames default_names = {.lexlev="lexlev", .ione="num", .offset="off", .length="len"};

static const char *lexlev_name() {
    if (field_names[OPC].lexlev != NULL) return field_names[OPC].lexlev;

    return default_names.lexlev;
}

static const char *num_name() {
    if (field_names[OPC].ione != NULL) return field_names[OPC].ione;

    return default_names.ione;
}

char mtype_name(enum Memtype type) {
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

char dtype_name(enum Datatype type) {
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
        default:  return 'U';
    }
}

void print_small_dtype(enum Datatype type, int length) {
    char dtypeSign;
    switch (DTYPE) {
        case Idt:
        case Jdt: dtypeSign = 's'; break;
        case Kdt:
        case Ldt: dtypeSign = 'u'; break;

        default: print_dtype(type); return;
    }

    printf("%c%d ", dtypeSign, length);
}

void print_dtype(enum Datatype type) {
    char dt = dtype_name(type);
    switch (dt)
    {
        case 'I': printf("s64 ");       break;
        case 'J': printf("s32 ");       break;
        case 'K': printf("u64 ");       break;
        case 'L': printf("u32 ");       break;
        case 'Q': printf("f64 ");       break;
        case 'R': printf("f32 ");       break;
        default:  printf("%cdt ", dt);  break;
    }
    if (dt == 'U') printf ("(%hhu) ", type);
}

void print_mtype(enum Memtype type) {
    char mt = mtype_name(type);
    printf("%cmt ", mt);
    if (mt == 'U') printf ("(%hhu) ", type);
}

void print_unsigned(union Valu v)
{
    switch (LENGTH) {
        case 1: printf("%hhu", (unsigned char)v.swpart.Ival); break;
        case 2: printf("%hu", (unsigned short)v.swpart.Ival); break;
        case 4: if (v.swpart.Ival > 0x1000u) printf("0x%x", v.swpart.Ival);
                else                         printf("%u", v.swpart.Ival);
                break;
        case 8: printf("%llu", v.dwval); break;
    }
}

// Print in hex if the number is bigger than 0x1000
void print_signed(union Valu v)
{
    switch (LENGTH) {
        case 1: printf("%hhd", (char)v.swpart.Ival); break;
        case 2: printf("%hd", (short)v.swpart.Ival); break;
        case 4: if (v.swpart.Ival >  0x1000 ||
                    v.swpart.Ival < -0x1000) printf("0x%x", v.swpart.Ival);
                else                         printf("%d", v.swpart.Ival);
                break;
        case 8: printf("%lld", v.dwval); break;
    }
}

bool print_register(int regNum) {
    if (regNum < sizeof(reg_names) / sizeof(reg_names[0])) {
        printf("%s ", reg_names[regNum]);
        return true;
    }

    return false;
}

void print_offset(int offset, bool hasMemType) {
    if (hasMemType && MTYPE == Rmt) {
        if (print_register(offset)) {
            return;
        }
    }

    printf("off %d ", offset);
}

void print_lexlev(unsigned short lexlev) {
    printf("%s %hu ", lexlev_name(), lexlev);
}

void print_ione(int ione) {
    printf("%s %d ", num_name(), ione);
}

void print_block(int block) {
    printf("block %d ", block);
}

void print_escaped_string(int length, char *str) {
    if (str == NULL) {
        return;
    }

    for (int i = 0; i < length; i++) {
        switch (str[i]) {
            case '\a': printf("\\a");  break;
            case '\b': printf("\\b");  break;
            case '\f': printf("\\f");  break;
            case '\n': printf("\\n");  break;
            case '\r': printf("\\r");  break;
            case '\t': printf("\\t");  break;
            case '\v': printf("\\v");  break;
            case '\\': printf("\\\\"); break;
            case '\?': printf("\\\?"); break;
            case '\'': printf("\\\'"); break;
            case '\"': printf("\\\""); break;
            case '\0': printf("\\0");  break;

            default: putchar(str[i]);  break;
        }
    }
}

void print_valu(union Valu v)
{
    if (((1 << DTYPE) & ((1 << Mdt) | (1 << Qdt) | (1 << Rdt) | (1 << Sdt) | (1 << Xdt))) || OPC == Ucomm) {
#if 1
        putchar('"');
        print_escaped_string(v.swpart.Ival, v.swpart.Chars);
        putchar('"');
#else
        printf("\"%.*s\"", v.swpart.Ival, v.swpart.Chars);
#endif
    } else {
        switch (DTYPE) {
/* address (pointer)             */ case Adt: printf("0x%x", v.swpart.Ival); break;
/* pointer to readonly data      */ case Cdt: printf("0x%x", v.swpart.Ival); break;
/* C pointer to function         */ case Fdt: printf("func %d", v.swpart.Ival); break;
/* address of label              */ case Gdt: printf("label %d", v.swpart.Ival); break;
/* address in the heap           */ case Hdt: printf("heapptr 0x%x", v.swpart.Ival); break;
/* integer, double word          */ case Idt:
/* integer, single word          */ case Jdt: print_signed(v); break;
/* unsigned integer, double word */ case Kdt:
/* unsigned integer, single word */ case Ldt: print_unsigned(v); break;
/* non-local labels              */ case Ndt: printf("label %d", v.swpart.Ival); break;
/* procedure, untyped            */ case Pdt: printf("proc %d", v.swpart.Ival); break;
/* 64 bit wide pointer           */ case Wdt: printf("wptr 0x%llx", v.dwval); break;
/* undefined                     */ case Zdt: printf("undefined %lld", v.dwval); break;
        }
    }
}

