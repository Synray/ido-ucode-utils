#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ucode.h"
#include "common.h"
#include "libu.h"
#include "print_data.h"

char *ustrptr;
union Bcode u;

/*******************************************************
 * print functions for opcodes with unique output
 *******************************************************/

bool print_uregs() {
    print_ione(IONE);
    int next = 1;
    if (IONE == 3 || IONE == 4) {
        next = 2; // skip odd registers for floating point classes
    }
    for (int i = OFFSET; i < OFFSET + LENGTH; i += next) {
        printf("%s ", reg_names[i]);
    }
    return true;
}

// some kind of link between two registers
// unaliased?
bool print_unal() {
    print_register(LEXLEV);
    print_register(IONE);
    printf("%d", DTYPE);
    return true;
}

bool print_lodstr() {
    if (MTYPE == Rmt) {
        print_dtype(DTYPE);
        print_mtype(MTYPE);
        print_register(OFFSET);
        return true;
    }
    return false;
}

bool print_rlodrstr() {
    print_dtype(DTYPE);
    print_mtype(MTYPE);
    print_block(IONE);
    print_offset(OFFSET, false);
    print_register(LEXLEV);
    return true;
}

bool print_ldc() {
    print_dtype(DTYPE);
    print_valu(CONSTVAL);
    return true;
}

bool print_rldc() {
    print_dtype(DTYPE);
    print_register(IONE);
    print_valu(CONSTVAL);
    return true;
}

bool print_rlda() {
    print_mtype(MTYPE);
    print_block(IONE);
    print_offset(OFFSET, false);
    print_register(LENGTH);
    return true;
}

bool print_rpar() {
    print_dtype(DTYPE);
    print_mtype(MTYPE);
    print_offset(OFFSET, false);
    print_register(LEXLEV);
    return true;
}

bool print_lab() {
    printf("%d ", IONE);
    if (LEXLEV != 0) {
        print_lexlev(LEXLEV);
    }
    if (LENGTH != 0) {
        printf("len %d ", LENGTH);
    }
    return true;
}

bool print_ilodistr() {
    print_small_dtype(DTYPE, LEXLEV);
    print_ione(IONE);

    // this field isn't actually an offset. it seems to be unused
    print_offset(OFFSET, false);
    return true;
}

bool print_cvtl() {
    print_small_dtype(DTYPE, IONE);
    return true;
}

// Most opcodes sometimes treat one field as a register...
// but the field is different for almost every opcode -_-
static bool (*print_function[UopcodeMax])() = {
    [Uregs] = print_uregs,
    [Uunal] = print_unal,
    [Ulod]  = print_lodstr,
    [Ustr]  = print_lodstr,
    [Uilod] = print_ilodistr,
    [Uistr] = print_ilodistr,
    [Urlod] = print_rlodrstr,
    [Urstr] = print_rlodrstr,
    [Urpar] = print_rpar,
    [Uldc]  = print_ldc,
    [Urldc] = print_rldc,
    [Urlda] = print_rlda,

    [Ulab] = print_lab,

    [Ucvtl] = print_cvtl,
};

void disassemble(char *ustr) {
    if (OPC == Ueof) return;

    struct utabrec urec = utab[OPC];

    if (OPC == Uent) puts("");
    printf("%.4s ", urec.opcname);

    // handle unique opcodes, usually just to print the right field as a register
    if (print_function[OPC] != NULL) {
        if (print_function[OPC]()) {
            puts("");
            return;
        }
    }

    // default output, print field by field
    bool hasMemType = false;
    for (int i = 0; urec.format[i] != Send; i++) {
        switch (urec.format[i]) {
            case Sdtype: print_dtype(DTYPE);                        break;
            case Smtype: hasMemType = true; print_mtype(MTYPE);     break;
            case Sdtype2: print_dtype(DTYPE2);      break;
            case Sdtypenum: printf("dtnum %d ", DTYPE);             break;

            case Slexlev: print_lexlev(LEXLEV); break;

            case Slabel0: printf("lab0 %d ", IONE);                 break;
            case Slabel1: printf("lab1 %d ", IONE);                 break;
            case Sblockno: print_block(IONE);                       break;
            case Ssomenumber: print_ione(IONE);   break;

            case Spop: printf("pop %u ", POP);                      break;
            case Spush: printf("push %u ", PUSH);                   break;
            case Sexternal: printf("ext %u ", EXTRNAL);             break;
            case Slength: printf("len %d ", LENGTH);                break;

            case Sconstval: printf("cval ");
            case Scomment:  print_valu(CONSTVAL);                   break;

            case Sinitval:  printf("init "); print_valu(INITVAL);   break;

            case Soffset: print_offset(OFFSET, hasMemType);         break;
            case Soffset2: printf("off2 %d ", OFFSET2);             break;
            case Slabel2: printf("lab2 %d ", LENGTH);               break;
            case SarrayOffset: printf("aryoff %d ", ARYOFF);        break;

            case Slbound: printf("%lld-", LBOUND);                  break;
            case Shbound: printf("%lld",  HBOUND);                  break;

            case Send:
            default:                                                break;
        }
    }
    puts("");
}

void read_ucode() {
    do {
        readuinstr(&u, ustrptr);
        disassemble(ustrptr);
    } while (OPC != Ueof);
}

void usage() {
    fprintf(stderr, "Usage: udis INPUT > OUT.u\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    uini();
    initur(argv[1]);

    ustrptr = calloc(1, 0x400);

    read_ucode();

    free(ustrptr);
}
