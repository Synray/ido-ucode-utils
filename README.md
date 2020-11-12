# IDO Ucode Disassembler

**Requires qemu-mips and mips-linux-gnu-gcc to compile and run.**

Converts the bytecode output from IDO (5.3 and 7.1) `cfe` and `uopt` into a human-readable format.

The majority of the source code for this project is copied from the IDO decompilation at [n64decomp/ido](https://github.com/n64decomp/ido).

If you are using this, you're probably dealing with a particularly hard function. Good luck.

## Usage

Compile with `make`.

You will need the ucode for the source file that you want to examine.
`cc` creates these files in /tmp and deletes them once compilation has finished, so in order to analyze the ucode, you need the commands that cc usually runs automatically.

The easiest way to get these commands is to run `cc` with `-show`. For an example using [n64decomp/sm64](https://github.com/n64decomp/sm64), in the Makefile, `-show` was added to `CFLAGS`.

Output from `make VERSION=eu -B build/eu/src/game/camera.o`:

```bash
# cfe
/usr/lib/cfe -D_MIPS_FPSET=16 -D_MIPS_ISA=2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 -D_MIPS_SZINT=32 -D_MIPS_SZLONG=32 -D_MIPS_SZPTR=32 -D__EXTENSIONS__ -DLANGUAGE_C -D_LANGUAGE_C -D__INLINE_INTRINSICS -Dsgi -D__sgi -Dunix -Dmips -Dhost_mips -D__unix -D__host_mips -D_SVR4_SOURCE -D_MODERN_C -D_SGI_SOURCE -D__DSO__ -DSYSTYPE_SVR4 -D_SYSTYPE_SVR4 -D_LONGLONG -D__mips=2 -I -Iinclude -Ibuild/eu -Ibuild/eu/include -Isrc -I. -Iinclude/libc -D_MIPSEB -DMIPSEB -D__STDC__=1 -DTARGET_N64 -D_LANGUAGE_C -DVERSION_EU=1 -DF3D_NEW=1 src/game/camera.c -Xv -D_CFE -Amachine(mips) -Asystem(unix) -non_shared -G 0 -std -XS/tmp/ctmsta0044P -mips2 -Xcpluscomm -Xsigned -EB -Xg0 -O2 > /tmp/ctmfa0044P
# The last tmp file is cfe_out

# Noisy output from each of the passes ...

# uopt
# The second tmp file in this command is uopt_out.
/usr/lib/uopt -v -G 0 -mips2 -EB -g0 -O2 /tmp/ctmfa0044P /tmp/ctmoa0044P -t /tmp/ctmsta0044P /tmp/ctmosa0044P

/usr/lib/ugen -v -G 0 -mips2 -EB -g0 -O2 /tmp/ctmoa0044P -o /tmp/ctmca0044P -t /tmp/ctmsta0044P -temp /tmp/ctmgta0044P

/usr/lib/as1 -elf -v -G 0 -p0 -mips2 -r4300_mul -r4300_mul -EB -g0 -O2 /tmp/ctmca0044P -o build/eu/src/game/camera.o -t /tmp/ctmsta0044P
```

After cleaning those up a bit:

```bash
# cfe
qemu-irix -L tools/ido5.3_compiler/ tools/ido5.3_compiler/usr/lib/cfe ${CFLAGS} source_file.c -Xv -D_CFE -Amachine(mips) -Asystem(unix) -non_shared -G 0 -std -XS./symfile -Xcpluscomm -Xsigned -mips2 -EB -Xg0 -O2 > cfe_out 

# uopt
qemu-irix -L tools/ido5.3_compiler/ tools/ido5.3_compiler/usr/lib/uopt -v -G 0 -mips2 -EB -g0 -O2 cfe_out uopt_out -t ./symfile strpfile 
```

Then to disassemble, run `udis`:

```bash
qemu-mips -L /usr/mips-linux-gnu/ build/udis uopt_out > uopt_ucode
qemu-mips -L /usr/mips-linux-gnu/ build/udis cfe_out > cfe_ucode
```
## Example Output

From sm64's camera.c:

```asm
/* ... */

ent  Pdt lexlev 2 block 299 pop 0 push 0 ext 1 
comm "update_camera"
pdef Adt Pmt block 299 off 0 len 4 lexlev 1 
regs lexlev 0 num 1 off 2 len 6 
regs lexlev 0 num 2 off 16 len 1 
regs lexlev 0 num 3 off 44 len 4 
lod  Adt Rmt block 0 off 4 len 4 
str  Adt Rmt block 0 off 16 len 4 
loc  page 2 line 3008 
loc  page 2 line 3011 
lod  Adt Rmt block 0 off 16 len 4 
str  Adt Smt block 14 off 0 len 4 
loc  page 2 line 3012 
mst  lexlev 2 
lod  Adt Rmt block 0 off 16 len 4 
str  Adt Rmt block 0 off 4 len 4 
rpar Adt Pmt block 0 off 0 len 4 lexlev 4 
cup  Jdt lexlev 2 block 300 pop 1 push 1 ext 0 
loc  page 2 line 3013 
ldc  Jdt len 4 cval 0
lod  Adt Rmt block 0 off 16 len 4 
ilod Ldt num 48 lexlev 8 len 1 off 0 
cvt  Jdt dt2 Ldt 
equ  Jdt 
fjp  lab1 382 lexlev 0 
loc  page 2 line 3013 
/* ... */
```
