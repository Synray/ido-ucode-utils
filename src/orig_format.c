#include "common.h"
#include "ucode.h"
#include "libu.h"
extern char *ustrptr;
extern union Bcode u;
char mtype_name(enum Memtype type);
char dtype_name(enum Datatype type);
void print_dtype(enum Datatype type);
void print_valu(union Valu v);
static const char *opcode_format[] = {
    " ABS  %D",
    " ADD  %D",
    " ADJ  %D %d %d",
    " AENT  %D %d %d %d %d %d",
    " AND  %D",
    " AOS  ",
    " ASYM %d %d",
    " BGN  %d %d %d",
    " BGNB %d",
    " BSUB  %D",
    " CG1 ",
    " CG2 ",
    " CHKH %D %d",
    " CHKL %D %d",
    " CHKN",
    " CHKT",
    " CIA %d %d %d %d ",
    "L%d CLAB  %d",
    " CLBD %D %d",
    " COMM ",
    " CSYM %d 0x%x %d",
    " CTRL %D %M %d %d %d %d",
    " CUBD %D %d",
    " CUP  %D %d %d %d %d %d",
    " CVT  %D %D",
    " CVTL %D %d",
    " DEC  %D %d",
    " DEF  %M %d",
    " DIF  %D %d",
    " DIV  %D",
    " DUP  %D",
    " END  %d",
    " ENDB %d",
    " ENT  %D %d %d %d %d %d",
    " EOF ",
    " EQU  %D",
    " ESYM %d 0x%x %d ",
    " FILL %D %d %d %d",
    " FJP  L%d",
    " FSYM %d 0x%x %d",
    " GEQ  %D",
    " GRT  %D",
    " GSYM %d 0x%x %d",
    " HSYM %d %d",
    " ICUF %D %d %d %d",
    " IDX %D ",
    " IEQU %D %d %d",
    " IGEQ %D %d %d",
    " IGRT %D %d %d",
    " IJP ",
    " ILDA  %M %d %d %d %d",
    " ILDV %D %d %d",
    " ILEQ %D %d %d",
    " ILES %D %d %d",
    " ILOD %D %d %d %d %d %d",
    " INC  %D %d",
    " INEQ %D %d %d",
    " INIT %D %M %d %d %d %d %d %d ",
    " INN  %D %d %d",
    " INT  %D %d",
    " IOR  %D",
    " ISLD %D %M %d %d %d",
    " ISST %D %M %d %d %d",
    " ISTR %D %d %d %d %d %d",
    " ISTV %D %d %d",
    " IXA  %D %d",
    "L%d LAB %d %d",
    " LBD ",
    " LBDY %d",
    " LBGN %d",
    " LCA  %D %d %d ",
    " LDA  %M %d %d %d %d",
    " LDAP ",
    " LDC  %D %d ",
    "L%d LDEF %d %d",
    " LDSP ",
    " LEND ",
    " LEQ  %D",
    " LES  %D",
    " LEX  %d %d",
    " LNOT %D",
    " LOC  %d %d",
    " LOD  %D %M %d %d %d %d",
    " LSYM %d 0x%x %d",
    " LTRM ",
    " MAX  %D",
    " MIN  %D",
    " MOD  %D",
    " MOV  %D %d %d %d",
    " MOVV  %D %d %d %d",
    " MPMV  %D %M %d %d %d %d",
    " MPY  %D",
    " MST  %d",
    " MUS  %D %d",
    " NEG  %D",
    " NEQ  %D",
    " NOP ",
    " NOT  %D",
    " ODD  %D",
    " OPTN %d %d",
    " PAR  %D %M %d %d %d",
    " PDEF %D %M %d %d %d %d",
    " PMOV %D %M %d %d %d %d",
    " POP  %D",
    " REGS %d %d %d %d",
    " REM  %D",
    " RET ",
    " RLDA %M %d %d %d",
    " RLDC  %D %d %d ",
    " RLOD %D %M %d %d %d %d",
    " RND  %D %D",
    " RPAR  %D %M %d %d %d %d",
    " RSTR %D %M %d %d %d %d",
    " SDEF %d %d",
    " SGS  %D %d",
    " SHL  %D",
    " SHR  %D",
    " SIGN %D",
    " SQR  %D",
    " SQRT %D",
    " SSYM %D %d %d",
    " STEP %D %d",
    " STP  %d",
    " STR  %D %M %d %d %d %d",
    " STSP ",
    " SUB  %D",
    " SWP  %D %D",
    " TJP  L%d",
    " TPEQ %D %d ",
    " TPGE %D %d ",
    " TPGT %D %d ",
    " TPLE %D %d ",
    " TPLT %D %d ",
    " TPNE %D %d ",
    " TYP  %D %D",
    " UBD ",
    " UJP  L%d",
    " UNAL %d %d %d",
    " UNI  %D %d",
    " VREG %D %M %d %d %d %d",
    " XJP  %D L%d L%d %d %d",
    " XOR  %D",
    " XPAR  %D",
    " MTAG	%d %d",
    " ALIA	%d %d",
    " ILDI	%D %d %d %d %d",
    " ISTI	%D %d %d %d %d",
    " IRLD	%D %d %d %d %d",
    " IRST	%D %d %d %d %d",
    " LDRC	%D %d %d",
    " MSYM	%d %d %d %d",
    " RCUF	%D %d %d %d %d",
    " KSYM	%d %d %d %d",
    " OSYM	%d %d",
};

void print_operand(enum uoperand op) {
    switch (op) {
        case Smtype:
            printf("%c", mtype_name(MTYPE));
            break;

        case Sdtype:
        case Sdtype2:
            printf("%c", dtype_name(DTYPE));
            break;
        case Sdtypenum:
            printf("%d", DTYPE);
            break;

        case Slexlev:
            printf("%hu", LEXLEV);
            break;

        case Slabel0:
        case Slabel1:
        case Sblockno:
        case Ssomenumber:
            printf("%d", IONE);
            break;

        case Spop:
            printf("%u", POP);
            break;
        case Spush:
            printf("%u", PUSH);
            break;
        case Sexternal:
            printf("%u", EXTRNAL);
            break;
        case Slength:
            printf("%d", LENGTH);
            break;

        case Sconstval:
        case Scomment:
            print_valu(CONSTVAL);
            break;

        case Sinitval:
            print_valu(INITVAL);
            break;

        case Soffset:
            printf("%d", OFFSET);
            break;
        case Soffset2:
            printf("%d", OFFSET2);
            break;
        case Slabel2:
            printf("%d", LENGTH);
            break;
        case SarrayOffset:
            printf("%d", ARYOFF);
            break;

        case Slbound:
            printf("%lld", LBOUND);
            break;
        case Shbound:
            printf("%lld", HBOUND);
            break;

        case Send:
        default:
            break;
    }
}


void disassemble_orig_format(const char *ustr)
{
    struct utabrec urec = utab[OPC];
    const char *fmt = opcode_format[OPC];
    int curop = 0;

    while (*fmt) {
        if (*fmt != '%') {
            putchar(*fmt);
        } else {
            fmt++; // skip the conversion char
            print_operand(urec.format[curop++]);
        }
        fmt++;
    }

    if (urec.hasconst) {
        print_operand(urec.format[curop]);
    }

    puts("");
}
