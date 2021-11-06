
if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif

syntax case ignore
" structural / meta
syntax keyword ucodeMisc comm
syntax match ucodeLoc "^\s*\<loc\> .*"

syntax keyword ucodeMisc lex 
syntax keyword ucodeMisc mtag

syntax match ucodeMisc /^\s*\<init\>/
syntax keyword ucodeMisc optn
syntax keyword ucodeMisc bgn 
syntax keyword ucodeMisc stp 
syntax keyword ucodeMisc bgnb
syntax keyword ucodeMisc bsub
syntax keyword ucodeMisc endb

syntax keyword ucodeMisc def 
syntax keyword ucodeMisc ldef
syntax keyword ucodeMisc pdef
syntax keyword ucodeMisc sdef

syntax keyword ucodeFunction ent 
syntax keyword ucodeFunction end 

syntax keyword ucodeFunction aent

syntax keyword ucodeMisc lbgn
syntax keyword ucodeMisc lbdy
syntax keyword ucodeMisc ltrm
syntax keyword ucodeMisc lend

syntax keyword ucodeMemory vreg
syntax keyword ucodeMemory regs

syntax keyword ucodeMisc nop 


" arithmetic
syntax keyword ucodeOp add 
syntax keyword ucodeOp sub 
syntax keyword ucodeOp div 
syntax keyword ucodeOp rem 
syntax keyword ucodeOp mpy
syntax keyword ucodeOp min 
syntax keyword ucodeOp max 
syntax keyword ucodeOp inc 
syntax keyword ucodeOp dec 
syntax keyword ucodeOp neg 
syntax keyword ucodeOp odd 

" maybe float intrinsics
syntax keyword ucodeOp abs 
syntax keyword ucodeOp mod 
syntax keyword ucodeOp sign
syntax keyword ucodeOp sqr 
syntax keyword ucodeOp sqrt

" set 
syntax keyword ucodeOp uni 
syntax keyword ucodeOp int 
syntax keyword ucodeOp dif 
syntax keyword ucodeOp inn 
syntax keyword ucodeOp mus 
syntax keyword ucodeOp adj 
syntax keyword ucodeOp sgs 

" bitwise operators
syntax keyword ucodeOp and 
syntax keyword ucodeOp ior 
syntax keyword ucodeOp xor 
syntax keyword ucodeOp not 
syntax keyword ucodeOp lnot
syntax keyword ucodeOp shl 
syntax keyword ucodeOp shr 

syntax keyword ucodeOp cvt 
syntax keyword ucodeOp cvtl
syntax keyword ucodeOp typ 
syntax keyword ucodeOp swp 
" 'pop' appears in other opcodes
syntax match ucodeOp /\s*^\<pop\>/

" alloca
syntax keyword ucodeAlloca aos 
" store/load stack pointer, used with alloca
syntax keyword ucodeAlloca ldsp
syntax keyword ucodeAlloca stsp
" something similar?
syntax keyword ucodeAlloca ldap

" control flow
syntax keyword ucodeBranch fjp 
syntax keyword ucodeBranch tjp 
syntax keyword ucodeBranch ujp 
syntax keyword ucodeBranch xjp 
syntax keyword ucodeBranch ijp 

syntax keyword ucodeBranch chkt
syntax keyword ucodeBranch chkh
syntax keyword ucodeBranch chkl
syntax keyword ucodeBranch chkn

syntax keyword ucodeBranch clab
syntax keyword ucodeBranch lab 

" Traps
syntax keyword ucodeTrap tpeq
syntax keyword ucodeTrap tpne
syntax keyword ucodeTrap tplt
syntax keyword ucodeTrap tpgt
syntax keyword ucodeTrap tpge
syntax keyword ucodeTrap tple


" functions
" Mark stack: Save current stack's state in preparation for calling a procedure
syntax keyword ucodeFunction mst 
syntax keyword ucodeFunction cia 
syntax keyword ucodeFunction cup 
syntax keyword ucodeFunction rcuf
" function pointer
syntax keyword ucodeFunction icuf

syntax keyword ucodeFunction par 
syntax keyword ucodeFunction rpar
syntax keyword ucodeFunction xpar
syntax keyword ucodeFunction pmov
syntax keyword ucodeFunction mpmv
syntax keyword ucodeFunction ret 

" lower and upper bound
syntax keyword ucodeMisc clbd
syntax keyword ucodeMisc cubd
syntax keyword ucodeMisc ubd 
syntax keyword ucodeMisc lbd 

" conditional
syntax keyword ucodeConditional equ 
syntax keyword ucodeConditional neq 
syntax keyword ucodeConditional geq 
syntax keyword ucodeConditional grt 
syntax keyword ucodeConditional leq 
syntax keyword ucodeConditional les 

" struct comparisons
syntax keyword ucodeConditional iequ
syntax keyword ucodeConditional ineq
" some kind of element-wise comparison, or a string comparison?
syntax keyword ucodeConditional igeq
syntax keyword ucodeConditional igrt
syntax keyword ucodeConditional ileq
syntax keyword ucodeConditional iles

"load/store
syntax keyword ucodeMemory ixa 

syntax keyword ucodeMemory lod 
syntax keyword ucodeMemory str 
syntax keyword ucodeMemory lca 
syntax keyword ucodeMemory lda 
syntax keyword ucodeMemory ldc 

" register constant, readonly constant?
syntax keyword ucodeMemory ldrc

" indirect or indexed loads/stores
syntax keyword ucodeMemory ilod
syntax keyword ucodeMemory ilda
syntax keyword ucodeMemory ildi
syntax keyword ucodeMemory istr
syntax keyword ucodeMemory isld
syntax keyword ucodeMemory isst
syntax keyword ucodeMemory isti
syntax keyword ucodeMemory istv

" register load/store
syntax keyword ucodeMemory rlda
syntax keyword ucodeMemory rldc
syntax keyword ucodeMemory rlod
syntax keyword ucodeMemory rstr

" indirect? register load/store?
syntax keyword ucodeMemory irld
syntax keyword ucodeMemory irst
syntax keyword ucodeMemory irlv
syntax keyword ucodeMemory irsv

syntax keyword ucodeMemory mov 
syntax keyword ucodeMemory movv

syntax keyword ucodeMemory idx 

" wtfs
syntax keyword ucodeMisc ctrl
syntax keyword ucodeMisc dup 
syntax keyword ucodeMisc fill

syntax keyword ucodeMisc rnd 
syntax keyword ucodeMisc step
syntax keyword ucodeMisc alia
" what
syntax keyword ucodeMisc unal
" used internally by uopt and ugen
syntax keyword ucodeMisc cg1 
syntax keyword ucodeMisc cg2 

" data types
syntax keyword ucodeDType Adt Cdt Fdt Gdt Hdt Idt Jdt Kdt Ldt Mdt Ndt Pdt Qdt Rdt Sdt Wdt Xdt Zdt
" synonyms
syntax keyword ucodeDType                     s64 s32 u64 u32             f64 f32
" cvtl types
syntax keyword ucodeDType s16 s8 u16 u8

" memory types
syntax keyword ucodeMType Zmt Pmt Tmt Smt Mmt Rmt Amt

syntax keyword ucodeSymbol asym hsym csym esym fsym gsym lsym ssym msym ksym osym


" mips registers
syntax match ucodeMipsConstantRegister "\$zero"
syntax match ucodeMipsRegister "\$at"
syntax match ucodeMipsReturnRegister "\$v0"
syntax match ucodeMipsRegister "\$v1"
syntax match ucodeMipsArgRegister "\$a0"
syntax match ucodeMipsArgRegister "\$a1"
syntax match ucodeMipsArgRegister "\$a2"
syntax match ucodeMipsArgRegister "\$a3"
syntax match ucodeMipsRegister "\$t0"
syntax match ucodeMipsRegister "\$t1"
syntax match ucodeMipsRegister "\$t2"
syntax match ucodeMipsRegister "\$t3"
syntax match ucodeMipsRegister "\$t4"
syntax match ucodeMipsRegister "\$t5"
syntax match ucodeMipsRegister "\$t6"
syntax match ucodeMipsRegister "\$t7"
syntax match ucodeMipsSavedRegister "\$s0"
syntax match ucodeMipsSavedRegister "\$s1"
syntax match ucodeMipsSavedRegister "\$s2"
syntax match ucodeMipsSavedRegister "\$s3"
syntax match ucodeMipsSavedRegister "\$s4"
syntax match ucodeMipsSavedRegister "\$s5"
syntax match ucodeMipsSavedRegister "\$s6"
syntax match ucodeMipsSavedRegister "\$s7"
syntax match ucodeMipsSavedRegister "\$s8"
syntax match ucodeMipsRegister "\$t8"
syntax match ucodeMipsRegister "\$t9"
syntax match ucodeMipsRegister "\$k0"
syntax match ucodeMipsRegister "\$k1"
syntax match ucodeMipsSpecialRegister "\$gp"
syntax match ucodeMipsStackRegister "\$sp"
syntax match ucodeMipsStackRegister "\$fp"
syntax match ucodeMipsReturnRegister "\$ra"

syntax match ucodeMipsFloatReturnRegister "\$f0"
syntax match ucodeMipsFloatReturnRegister "\$f2"

syntax match ucodeMipsFloatArgRegister "\$f12"
syntax match ucodeMipsFloatArgRegister "\$f14"

syntax match ucodeMipsFloatRegister "\$f4"
syntax match ucodeMipsFloatRegister "\$f6"
syntax match ucodeMipsFloatRegister "\$f8"
syntax match ucodeMipsFloatRegister "\$f10"
syntax match ucodeMipsFloatRegister "\$f16"
syntax match ucodeMipsFloatRegister "\$f18"

syntax match ucodeMipsFloatSavedRegister "\$f20"
syntax match ucodeMipsFloatSavedRegister "\$f22"
syntax match ucodeMipsFloatSavedRegister "\$f24"
syntax match ucodeMipsFloatSavedRegister "\$f26"
syntax match ucodeMipsFloatSavedRegister "\$f28"
syntax match ucodeMipsFloatSavedRegister "\$f30"

hi def link ucodeMipsFloatSavedRegister PreProc
hi def link ucodeMipsFloatArgRegister Type
hi def link ucodeMipsFloatRegister Identifier
hi def link ucodeMipsFloatReturnRegister Label

hi def link ucodeMipsSavedRegister Boolean
hi def link ucodeMipsSpecialRegister Special
hi def link ucodeMipsArgRegister Type
hi def link ucodeMipsStackRegister StorageClass
hi def link ucodeMipsReturnRegister Label
hi def link ucodeMipsConstantRegister Constant
hi link ucodeMipsRegister Identifier


syntax match ucodeHashComment /#.*/
syntax region ucodeString start=/"/ skip=/\\"/ end=/"/
syntax match ucodeNumber /\<[-]\?\d\+\>/ " Decimal numbers
syntax match ucodeNumber /\<-\?0\(x\|X\)[0-9a-fA-F]\+\>/ " Hex numbers

hi def link ucodeString String
hi def link ucodeHashComment         ModeMsg
hi def link ucodeNumber              Number

hi def link ucodeMisc Identifier
hi def link ucodeMemory StorageClass
hi def link ucodeAlloca StorageClass
hi def link ucodeBranch Statement
hi def link ucodeTrap PreProc
hi def link ucodeConditional Boolean
hi def link ucodeSymbol StorageClass
hi def link ucodeFunction Statement
hi def link ucodeOp Special
hi def link ucodeMisc Identifier

hi def link ucodeLoc Comment

hi def link ucodeDType Type
hi def link ucodeMType StorageClass

let b:current_syntax = "ucode"
