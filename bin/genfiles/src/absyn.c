 struct Cyc_timespec{ int tv_sec; int tv_nsec; } ; struct Cyc_itimerspec{ struct
Cyc_timespec it_interval; struct Cyc_timespec it_value; } ; struct Cyc__types_fd_set{
int fds_bits[ 8u]; } ; extern void exit( int); extern void* abort(); struct Cyc_Core_Opt{
void* v; } ; extern unsigned char Cyc_Core_InvalidArg[ 15u]; struct Cyc_Core_InvalidArg_struct{
unsigned char* tag; struct _tagged_string f1; } ; extern unsigned char Cyc_Core_Failure[
12u]; struct Cyc_Core_Failure_struct{ unsigned char* tag; struct _tagged_string
f1; } ; extern unsigned char Cyc_Core_Impossible[ 15u]; struct Cyc_Core_Impossible_struct{
unsigned char* tag; struct _tagged_string f1; } ; extern unsigned char Cyc_Core_Not_found[
14u]; extern unsigned char Cyc_Core_Unreachable[ 16u]; struct Cyc_Core_Unreachable_struct{
unsigned char* tag; struct _tagged_string f1; } ; extern unsigned char*
string_to_Cstring( struct _tagged_string); extern unsigned char*
underlying_Cstring( struct _tagged_string); extern struct _tagged_string
Cstring_to_string( unsigned char*); extern int system( unsigned char*); struct
Cyc_List_List{ void* hd; struct Cyc_List_List* tl; } ; struct _tagged_ptr0{ void**
curr; void** base; void** last_plus_one; } ; extern struct Cyc_List_List* Cyc_List_list(
struct _tagged_ptr0); extern unsigned char Cyc_List_List_empty[ 15u]; extern
struct Cyc_List_List* Cyc_List_map( void*(* f)( void*), struct Cyc_List_List* x);
extern unsigned char Cyc_List_List_mismatch[ 18u]; extern struct Cyc_List_List*
Cyc_List_imp_rev( struct Cyc_List_List* x); extern unsigned char Cyc_List_Nth[ 8u];
extern int Cyc_List_list_cmp( int(* cmp)( void*, void*), struct Cyc_List_List*
l1, struct Cyc_List_List* l2); struct Cyc_Lineno_Pos{ struct _tagged_string
logical_file; struct _tagged_string line; int line_no; int col; } ; extern
unsigned char Cyc_Position_Exit[ 9u]; struct Cyc_Position_Segment; static const
int Cyc_Position_Lex= 0; static const int Cyc_Position_Parse= 1; static const
int Cyc_Position_Elab= 2; struct Cyc_Position_Error{ struct _tagged_string
source; struct Cyc_Position_Segment* seg; void* kind; struct _tagged_string desc;
} ; extern unsigned char Cyc_Position_Nocontext[ 14u]; struct _tuple0{ void* f1;
struct _tagged_string* f2; } ; struct Cyc_Absyn_Tvar; struct Cyc_Absyn_Tqual;
struct Cyc_Absyn_Conref; struct Cyc_Absyn_PtrInfo; struct Cyc_Absyn_VarargInfo;
struct Cyc_Absyn_FnInfo; struct Cyc_Absyn_TunionInfo; struct Cyc_Absyn_TunionFieldInfo;
struct Cyc_Absyn_VarargCallInfo; struct Cyc_Absyn_Exp; struct Cyc_Absyn_Stmt;
struct Cyc_Absyn_Pat; struct Cyc_Absyn_Switch_clause; struct Cyc_Absyn_SwitchC_clause;
struct Cyc_Absyn_Fndecl; struct Cyc_Absyn_Structdecl; struct Cyc_Absyn_Uniondecl;
struct Cyc_Absyn_Tuniondecl; struct Cyc_Absyn_Tunionfield; struct Cyc_Absyn_Enumfield;
struct Cyc_Absyn_Enumdecl; struct Cyc_Absyn_Typedefdecl; struct Cyc_Absyn_Vardecl;
struct Cyc_Absyn_Decl; struct Cyc_Absyn_Structfield; static const int Cyc_Absyn_Loc_n=
0; static const int Cyc_Absyn_Rel_n= 0; struct Cyc_Absyn_Rel_n_struct{ int tag;
struct Cyc_List_List* f1; } ; static const int Cyc_Absyn_Abs_n= 1; struct Cyc_Absyn_Abs_n_struct{
int tag; struct Cyc_List_List* f1; } ; static const int Cyc_Absyn_Static= 0;
static const int Cyc_Absyn_Abstract= 1; static const int Cyc_Absyn_Public= 2;
static const int Cyc_Absyn_Extern= 3; static const int Cyc_Absyn_ExternC= 4;
struct Cyc_Absyn_Tqual{ int q_const: 1; int q_volatile: 1; int q_restrict: 1; }
; static const int Cyc_Absyn_B1= 0; static const int Cyc_Absyn_B2= 1; static
const int Cyc_Absyn_B4= 2; static const int Cyc_Absyn_B8= 3; static const int
Cyc_Absyn_AnyKind= 0; static const int Cyc_Absyn_MemKind= 1; static const int
Cyc_Absyn_BoxKind= 2; static const int Cyc_Absyn_RgnKind= 3; static const int
Cyc_Absyn_EffKind= 4; static const int Cyc_Absyn_Signed= 0; static const int Cyc_Absyn_Unsigned=
1; struct Cyc_Absyn_Conref{ void* v; } ; static const int Cyc_Absyn_Eq_constr= 0;
struct Cyc_Absyn_Eq_constr_struct{ int tag; void* f1; } ; static const int Cyc_Absyn_Forward_constr=
1; struct Cyc_Absyn_Forward_constr_struct{ int tag; struct Cyc_Absyn_Conref* f1;
} ; static const int Cyc_Absyn_No_constr= 0; struct Cyc_Absyn_Tvar{ struct
_tagged_string* name; int* identity; struct Cyc_Absyn_Conref* kind; } ; static
const int Cyc_Absyn_Unknown_b= 0; static const int Cyc_Absyn_Upper_b= 0; struct
Cyc_Absyn_Upper_b_struct{ int tag; struct Cyc_Absyn_Exp* f1; } ; struct Cyc_Absyn_PtrInfo{
void* elt_typ; void* rgn_typ; struct Cyc_Absyn_Conref* nullable; struct Cyc_Absyn_Tqual
tq; struct Cyc_Absyn_Conref* bounds; } ; struct Cyc_Absyn_VarargInfo{ struct Cyc_Core_Opt*
name; struct Cyc_Absyn_Tqual tq; void* type; void* rgn; int inject; } ; struct
Cyc_Absyn_FnInfo{ struct Cyc_List_List* tvars; struct Cyc_Core_Opt* effect; void*
ret_typ; struct Cyc_List_List* args; int c_varargs; struct Cyc_Absyn_VarargInfo*
cyc_varargs; struct Cyc_List_List* attributes; } ; struct Cyc_Absyn_UnknownTunionInfo{
struct _tuple0* name; int is_xtunion; } ; static const int Cyc_Absyn_UnknownTunion=
0; struct Cyc_Absyn_UnknownTunion_struct{ int tag; struct Cyc_Absyn_UnknownTunionInfo
f1; } ; static const int Cyc_Absyn_KnownTunion= 1; struct Cyc_Absyn_KnownTunion_struct{
int tag; struct Cyc_Absyn_Tuniondecl* f1; } ; struct Cyc_Absyn_TunionInfo{ void*
tunion_info; struct Cyc_List_List* targs; void* rgn; } ; struct Cyc_Absyn_UnknownTunionFieldInfo{
struct _tuple0* tunion_name; struct _tuple0* field_name; int is_xtunion; } ;
static const int Cyc_Absyn_UnknownTunionfield= 0; struct Cyc_Absyn_UnknownTunionfield_struct{
int tag; struct Cyc_Absyn_UnknownTunionFieldInfo f1; } ; static const int Cyc_Absyn_KnownTunionfield=
1; struct Cyc_Absyn_KnownTunionfield_struct{ int tag; struct Cyc_Absyn_Tuniondecl*
f1; struct Cyc_Absyn_Tunionfield* f2; } ; struct Cyc_Absyn_TunionFieldInfo{ void*
field_info; struct Cyc_List_List* targs; } ; static const int Cyc_Absyn_VoidType=
0; static const int Cyc_Absyn_Evar= 0; struct Cyc_Absyn_Evar_struct{ int tag;
struct Cyc_Core_Opt* f1; struct Cyc_Core_Opt* f2; int f3; struct Cyc_Core_Opt*
f4; } ; static const int Cyc_Absyn_VarType= 1; struct Cyc_Absyn_VarType_struct{
int tag; struct Cyc_Absyn_Tvar* f1; } ; static const int Cyc_Absyn_TunionType= 2;
struct Cyc_Absyn_TunionType_struct{ int tag; struct Cyc_Absyn_TunionInfo f1; } ;
static const int Cyc_Absyn_TunionFieldType= 3; struct Cyc_Absyn_TunionFieldType_struct{
int tag; struct Cyc_Absyn_TunionFieldInfo f1; } ; static const int Cyc_Absyn_PointerType=
4; struct Cyc_Absyn_PointerType_struct{ int tag; struct Cyc_Absyn_PtrInfo f1; }
; static const int Cyc_Absyn_IntType= 5; struct Cyc_Absyn_IntType_struct{ int
tag; void* f1; void* f2; } ; static const int Cyc_Absyn_FloatType= 1; static
const int Cyc_Absyn_DoubleType= 2; static const int Cyc_Absyn_ArrayType= 6;
struct Cyc_Absyn_ArrayType_struct{ int tag; void* f1; struct Cyc_Absyn_Tqual f2;
struct Cyc_Absyn_Exp* f3; } ; static const int Cyc_Absyn_FnType= 7; struct Cyc_Absyn_FnType_struct{
int tag; struct Cyc_Absyn_FnInfo f1; } ; static const int Cyc_Absyn_TupleType= 8;
struct Cyc_Absyn_TupleType_struct{ int tag; struct Cyc_List_List* f1; } ; static
const int Cyc_Absyn_StructType= 9; struct Cyc_Absyn_StructType_struct{ int tag;
struct _tuple0* f1; struct Cyc_List_List* f2; struct Cyc_Absyn_Structdecl** f3;
} ; static const int Cyc_Absyn_UnionType= 10; struct Cyc_Absyn_UnionType_struct{
int tag; struct _tuple0* f1; struct Cyc_List_List* f2; struct Cyc_Absyn_Uniondecl**
f3; } ; static const int Cyc_Absyn_AnonStructType= 11; struct Cyc_Absyn_AnonStructType_struct{
int tag; struct Cyc_List_List* f1; } ; static const int Cyc_Absyn_AnonUnionType=
12; struct Cyc_Absyn_AnonUnionType_struct{ int tag; struct Cyc_List_List* f1; }
; static const int Cyc_Absyn_EnumType= 13; struct Cyc_Absyn_EnumType_struct{ int
tag; struct _tuple0* f1; struct Cyc_Absyn_Enumdecl* f2; } ; static const int Cyc_Absyn_RgnHandleType=
14; struct Cyc_Absyn_RgnHandleType_struct{ int tag; void* f1; } ; static const
int Cyc_Absyn_TypedefType= 15; struct Cyc_Absyn_TypedefType_struct{ int tag;
struct _tuple0* f1; struct Cyc_List_List* f2; struct Cyc_Core_Opt* f3; } ;
static const int Cyc_Absyn_HeapRgn= 3; static const int Cyc_Absyn_AccessEff= 16;
struct Cyc_Absyn_AccessEff_struct{ int tag; void* f1; } ; static const int Cyc_Absyn_JoinEff=
17; struct Cyc_Absyn_JoinEff_struct{ int tag; struct Cyc_List_List* f1; } ;
static const int Cyc_Absyn_NoTypes= 0; struct Cyc_Absyn_NoTypes_struct{ int tag;
struct Cyc_List_List* f1; struct Cyc_Position_Segment* f2; } ; static const int
Cyc_Absyn_WithTypes= 1; struct Cyc_Absyn_WithTypes_struct{ int tag; struct Cyc_List_List*
f1; int f2; struct Cyc_Absyn_VarargInfo* f3; struct Cyc_Core_Opt* f4; } ; static
const int Cyc_Absyn_NonNullable_ps= 0; struct Cyc_Absyn_NonNullable_ps_struct{
int tag; struct Cyc_Absyn_Exp* f1; } ; static const int Cyc_Absyn_Nullable_ps= 1;
struct Cyc_Absyn_Nullable_ps_struct{ int tag; struct Cyc_Absyn_Exp* f1; } ;
static const int Cyc_Absyn_TaggedArray_ps= 0; static const int Cyc_Absyn_Regparm_att=
0; struct Cyc_Absyn_Regparm_att_struct{ int tag; int f1; } ; static const int
Cyc_Absyn_Stdcall_att= 0; static const int Cyc_Absyn_Cdecl_att= 1; static const
int Cyc_Absyn_Fastcall_att= 2; static const int Cyc_Absyn_Noreturn_att= 3;
static const int Cyc_Absyn_Const_att= 4; static const int Cyc_Absyn_Aligned_att=
1; struct Cyc_Absyn_Aligned_att_struct{ int tag; int f1; } ; static const int
Cyc_Absyn_Packed_att= 5; static const int Cyc_Absyn_Section_att= 2; struct Cyc_Absyn_Section_att_struct{
int tag; struct _tagged_string f1; } ; static const int Cyc_Absyn_Nocommon_att=
6; static const int Cyc_Absyn_Shared_att= 7; static const int Cyc_Absyn_Unused_att=
8; static const int Cyc_Absyn_Weak_att= 9; static const int Cyc_Absyn_Dllimport_att=
10; static const int Cyc_Absyn_Dllexport_att= 11; static const int Cyc_Absyn_No_instrument_function_att=
12; static const int Cyc_Absyn_Constructor_att= 13; static const int Cyc_Absyn_Destructor_att=
14; static const int Cyc_Absyn_No_check_memory_usage_att= 15; static const int
Cyc_Absyn_Carray_mod= 0; static const int Cyc_Absyn_ConstArray_mod= 0; struct
Cyc_Absyn_ConstArray_mod_struct{ int tag; struct Cyc_Absyn_Exp* f1; } ; static
const int Cyc_Absyn_Pointer_mod= 1; struct Cyc_Absyn_Pointer_mod_struct{ int tag;
void* f1; void* f2; struct Cyc_Absyn_Tqual f3; } ; static const int Cyc_Absyn_Function_mod=
2; struct Cyc_Absyn_Function_mod_struct{ int tag; void* f1; } ; static const int
Cyc_Absyn_TypeParams_mod= 3; struct Cyc_Absyn_TypeParams_mod_struct{ int tag;
struct Cyc_List_List* f1; struct Cyc_Position_Segment* f2; int f3; } ; static
const int Cyc_Absyn_Attributes_mod= 4; struct Cyc_Absyn_Attributes_mod_struct{
int tag; struct Cyc_Position_Segment* f1; struct Cyc_List_List* f2; } ; static
const int Cyc_Absyn_Char_c= 0; struct Cyc_Absyn_Char_c_struct{ int tag; void* f1;
unsigned char f2; } ; static const int Cyc_Absyn_Short_c= 1; struct Cyc_Absyn_Short_c_struct{
int tag; void* f1; short f2; } ; static const int Cyc_Absyn_Int_c= 2; struct Cyc_Absyn_Int_c_struct{
int tag; void* f1; int f2; } ; static const int Cyc_Absyn_LongLong_c= 3; struct
Cyc_Absyn_LongLong_c_struct{ int tag; void* f1; long long f2; } ; static const
int Cyc_Absyn_Float_c= 4; struct Cyc_Absyn_Float_c_struct{ int tag; struct
_tagged_string f1; } ; static const int Cyc_Absyn_String_c= 5; struct Cyc_Absyn_String_c_struct{
int tag; struct _tagged_string f1; } ; static const int Cyc_Absyn_Null_c= 0;
static const int Cyc_Absyn_Plus= 0; static const int Cyc_Absyn_Times= 1; static
const int Cyc_Absyn_Minus= 2; static const int Cyc_Absyn_Div= 3; static const
int Cyc_Absyn_Mod= 4; static const int Cyc_Absyn_Eq= 5; static const int Cyc_Absyn_Neq=
6; static const int Cyc_Absyn_Gt= 7; static const int Cyc_Absyn_Lt= 8; static
const int Cyc_Absyn_Gte= 9; static const int Cyc_Absyn_Lte= 10; static const int
Cyc_Absyn_Not= 11; static const int Cyc_Absyn_Bitnot= 12; static const int Cyc_Absyn_Bitand=
13; static const int Cyc_Absyn_Bitor= 14; static const int Cyc_Absyn_Bitxor= 15;
static const int Cyc_Absyn_Bitlshift= 16; static const int Cyc_Absyn_Bitlrshift=
17; static const int Cyc_Absyn_Bitarshift= 18; static const int Cyc_Absyn_Size=
19; static const int Cyc_Absyn_Printf= 20; static const int Cyc_Absyn_Fprintf=
21; static const int Cyc_Absyn_Xprintf= 22; static const int Cyc_Absyn_Scanf= 23;
static const int Cyc_Absyn_Fscanf= 24; static const int Cyc_Absyn_Sscanf= 25;
static const int Cyc_Absyn_PreInc= 0; static const int Cyc_Absyn_PostInc= 1;
static const int Cyc_Absyn_PreDec= 2; static const int Cyc_Absyn_PostDec= 3;
struct Cyc_Absyn_VarargCallInfo{ int num_varargs; struct Cyc_List_List*
injectors; struct Cyc_Absyn_VarargInfo* vai; } ; static const int Cyc_Absyn_Const_e=
0; struct Cyc_Absyn_Const_e_struct{ int tag; void* f1; } ; static const int Cyc_Absyn_Var_e=
1; struct Cyc_Absyn_Var_e_struct{ int tag; struct _tuple0* f1; void* f2; } ;
static const int Cyc_Absyn_UnknownId_e= 2; struct Cyc_Absyn_UnknownId_e_struct{
int tag; struct _tuple0* f1; } ; static const int Cyc_Absyn_Primop_e= 3; struct
Cyc_Absyn_Primop_e_struct{ int tag; void* f1; struct Cyc_List_List* f2; } ;
static const int Cyc_Absyn_AssignOp_e= 4; struct Cyc_Absyn_AssignOp_e_struct{
int tag; struct Cyc_Absyn_Exp* f1; struct Cyc_Core_Opt* f2; struct Cyc_Absyn_Exp*
f3; } ; static const int Cyc_Absyn_Increment_e= 5; struct Cyc_Absyn_Increment_e_struct{
int tag; struct Cyc_Absyn_Exp* f1; void* f2; } ; static const int Cyc_Absyn_Conditional_e=
6; struct Cyc_Absyn_Conditional_e_struct{ int tag; struct Cyc_Absyn_Exp* f1;
struct Cyc_Absyn_Exp* f2; struct Cyc_Absyn_Exp* f3; } ; static const int Cyc_Absyn_SeqExp_e=
7; struct Cyc_Absyn_SeqExp_e_struct{ int tag; struct Cyc_Absyn_Exp* f1; struct
Cyc_Absyn_Exp* f2; } ; static const int Cyc_Absyn_UnknownCall_e= 8; struct Cyc_Absyn_UnknownCall_e_struct{
int tag; struct Cyc_Absyn_Exp* f1; struct Cyc_List_List* f2; } ; static const
int Cyc_Absyn_FnCall_e= 9; struct Cyc_Absyn_FnCall_e_struct{ int tag; struct Cyc_Absyn_Exp*
f1; struct Cyc_List_List* f2; struct Cyc_Absyn_VarargCallInfo* f3; } ; static
const int Cyc_Absyn_Throw_e= 10; struct Cyc_Absyn_Throw_e_struct{ int tag;
struct Cyc_Absyn_Exp* f1; } ; static const int Cyc_Absyn_NoInstantiate_e= 11;
struct Cyc_Absyn_NoInstantiate_e_struct{ int tag; struct Cyc_Absyn_Exp* f1; } ;
static const int Cyc_Absyn_Instantiate_e= 12; struct Cyc_Absyn_Instantiate_e_struct{
int tag; struct Cyc_Absyn_Exp* f1; struct Cyc_List_List* f2; } ; static const
int Cyc_Absyn_Cast_e= 13; struct Cyc_Absyn_Cast_e_struct{ int tag; void* f1;
struct Cyc_Absyn_Exp* f2; } ; static const int Cyc_Absyn_Address_e= 14; struct
Cyc_Absyn_Address_e_struct{ int tag; struct Cyc_Absyn_Exp* f1; } ; static const
int Cyc_Absyn_New_e= 15; struct Cyc_Absyn_New_e_struct{ int tag; struct Cyc_Absyn_Exp*
f1; struct Cyc_Absyn_Exp* f2; } ; static const int Cyc_Absyn_Sizeoftyp_e= 16;
struct Cyc_Absyn_Sizeoftyp_e_struct{ int tag; void* f1; } ; static const int Cyc_Absyn_Sizeofexp_e=
17; struct Cyc_Absyn_Sizeofexp_e_struct{ int tag; struct Cyc_Absyn_Exp* f1; } ;
static const int Cyc_Absyn_Deref_e= 18; struct Cyc_Absyn_Deref_e_struct{ int tag;
struct Cyc_Absyn_Exp* f1; } ; static const int Cyc_Absyn_StructMember_e= 19;
struct Cyc_Absyn_StructMember_e_struct{ int tag; struct Cyc_Absyn_Exp* f1;
struct _tagged_string* f2; } ; static const int Cyc_Absyn_StructArrow_e= 20;
struct Cyc_Absyn_StructArrow_e_struct{ int tag; struct Cyc_Absyn_Exp* f1; struct
_tagged_string* f2; } ; static const int Cyc_Absyn_Subscript_e= 21; struct Cyc_Absyn_Subscript_e_struct{
int tag; struct Cyc_Absyn_Exp* f1; struct Cyc_Absyn_Exp* f2; } ; static const
int Cyc_Absyn_Tuple_e= 22; struct Cyc_Absyn_Tuple_e_struct{ int tag; struct Cyc_List_List*
f1; } ; static const int Cyc_Absyn_CompoundLit_e= 23; struct _tuple1{ struct Cyc_Core_Opt*
f1; struct Cyc_Absyn_Tqual f2; void* f3; } ; struct Cyc_Absyn_CompoundLit_e_struct{
int tag; struct _tuple1* f1; struct Cyc_List_List* f2; } ; static const int Cyc_Absyn_Array_e=
24; struct Cyc_Absyn_Array_e_struct{ int tag; struct Cyc_List_List* f1; } ;
static const int Cyc_Absyn_Comprehension_e= 25; struct Cyc_Absyn_Comprehension_e_struct{
int tag; struct Cyc_Absyn_Vardecl* f1; struct Cyc_Absyn_Exp* f2; struct Cyc_Absyn_Exp*
f3; } ; static const int Cyc_Absyn_Struct_e= 26; struct Cyc_Absyn_Struct_e_struct{
int tag; struct _tuple0* f1; struct Cyc_Core_Opt* f2; struct Cyc_List_List* f3;
struct Cyc_Absyn_Structdecl* f4; } ; static const int Cyc_Absyn_AnonStruct_e= 27;
struct Cyc_Absyn_AnonStruct_e_struct{ int tag; void* f1; struct Cyc_List_List*
f2; } ; static const int Cyc_Absyn_Tunion_e= 28; struct Cyc_Absyn_Tunion_e_struct{
int tag; struct Cyc_Core_Opt* f1; struct Cyc_Core_Opt* f2; struct Cyc_List_List*
f3; struct Cyc_Absyn_Tuniondecl* f4; struct Cyc_Absyn_Tunionfield* f5; } ;
static const int Cyc_Absyn_Enum_e= 29; struct Cyc_Absyn_Enum_e_struct{ int tag;
struct _tuple0* f1; struct Cyc_Absyn_Enumdecl* f2; struct Cyc_Absyn_Enumfield*
f3; } ; static const int Cyc_Absyn_Malloc_e= 30; struct Cyc_Absyn_Malloc_e_struct{
int tag; struct Cyc_Absyn_Exp* f1; void* f2; } ; static const int Cyc_Absyn_UnresolvedMem_e=
31; struct Cyc_Absyn_UnresolvedMem_e_struct{ int tag; struct Cyc_Core_Opt* f1;
struct Cyc_List_List* f2; } ; static const int Cyc_Absyn_StmtExp_e= 32; struct
Cyc_Absyn_StmtExp_e_struct{ int tag; struct Cyc_Absyn_Stmt* f1; } ; static const
int Cyc_Absyn_Codegen_e= 33; struct Cyc_Absyn_Codegen_e_struct{ int tag; struct
Cyc_Absyn_Fndecl* f1; } ; static const int Cyc_Absyn_Fill_e= 34; struct Cyc_Absyn_Fill_e_struct{
int tag; struct Cyc_Absyn_Exp* f1; } ; struct Cyc_Absyn_Exp{ struct Cyc_Core_Opt*
topt; void* r; struct Cyc_Position_Segment* loc; } ; static const int Cyc_Absyn_Skip_s=
0; static const int Cyc_Absyn_Exp_s= 0; struct Cyc_Absyn_Exp_s_struct{ int tag;
struct Cyc_Absyn_Exp* f1; } ; static const int Cyc_Absyn_Seq_s= 1; struct Cyc_Absyn_Seq_s_struct{
int tag; struct Cyc_Absyn_Stmt* f1; struct Cyc_Absyn_Stmt* f2; } ; static const
int Cyc_Absyn_Return_s= 2; struct Cyc_Absyn_Return_s_struct{ int tag; struct Cyc_Absyn_Exp*
f1; } ; static const int Cyc_Absyn_IfThenElse_s= 3; struct Cyc_Absyn_IfThenElse_s_struct{
int tag; struct Cyc_Absyn_Exp* f1; struct Cyc_Absyn_Stmt* f2; struct Cyc_Absyn_Stmt*
f3; } ; static const int Cyc_Absyn_While_s= 4; struct _tuple2{ struct Cyc_Absyn_Exp*
f1; struct Cyc_Absyn_Stmt* f2; } ; struct Cyc_Absyn_While_s_struct{ int tag;
struct _tuple2 f1; struct Cyc_Absyn_Stmt* f2; } ; static const int Cyc_Absyn_Break_s=
5; struct Cyc_Absyn_Break_s_struct{ int tag; struct Cyc_Absyn_Stmt* f1; } ;
static const int Cyc_Absyn_Continue_s= 6; struct Cyc_Absyn_Continue_s_struct{
int tag; struct Cyc_Absyn_Stmt* f1; } ; static const int Cyc_Absyn_Goto_s= 7;
struct Cyc_Absyn_Goto_s_struct{ int tag; struct _tagged_string* f1; struct Cyc_Absyn_Stmt*
f2; } ; static const int Cyc_Absyn_For_s= 8; struct Cyc_Absyn_For_s_struct{ int
tag; struct Cyc_Absyn_Exp* f1; struct _tuple2 f2; struct _tuple2 f3; struct Cyc_Absyn_Stmt*
f4; } ; static const int Cyc_Absyn_Switch_s= 9; struct Cyc_Absyn_Switch_s_struct{
int tag; struct Cyc_Absyn_Exp* f1; struct Cyc_List_List* f2; } ; static const
int Cyc_Absyn_SwitchC_s= 10; struct Cyc_Absyn_SwitchC_s_struct{ int tag; struct
Cyc_Absyn_Exp* f1; struct Cyc_List_List* f2; } ; static const int Cyc_Absyn_Fallthru_s=
11; struct Cyc_Absyn_Fallthru_s_struct{ int tag; struct Cyc_List_List* f1;
struct Cyc_Absyn_Switch_clause** f2; } ; static const int Cyc_Absyn_Decl_s= 12;
struct Cyc_Absyn_Decl_s_struct{ int tag; struct Cyc_Absyn_Decl* f1; struct Cyc_Absyn_Stmt*
f2; } ; static const int Cyc_Absyn_Cut_s= 13; struct Cyc_Absyn_Cut_s_struct{ int
tag; struct Cyc_Absyn_Stmt* f1; } ; static const int Cyc_Absyn_Splice_s= 14;
struct Cyc_Absyn_Splice_s_struct{ int tag; struct Cyc_Absyn_Stmt* f1; } ; static
const int Cyc_Absyn_Label_s= 15; struct Cyc_Absyn_Label_s_struct{ int tag;
struct _tagged_string* f1; struct Cyc_Absyn_Stmt* f2; } ; static const int Cyc_Absyn_Do_s=
16; struct Cyc_Absyn_Do_s_struct{ int tag; struct Cyc_Absyn_Stmt* f1; struct
_tuple2 f2; } ; static const int Cyc_Absyn_TryCatch_s= 17; struct Cyc_Absyn_TryCatch_s_struct{
int tag; struct Cyc_Absyn_Stmt* f1; struct Cyc_List_List* f2; } ; static const
int Cyc_Absyn_Region_s= 18; struct Cyc_Absyn_Region_s_struct{ int tag; struct
Cyc_Absyn_Tvar* f1; struct Cyc_Absyn_Vardecl* f2; struct Cyc_Absyn_Stmt* f3; } ;
struct Cyc_Absyn_Stmt{ void* r; struct Cyc_Position_Segment* loc; struct Cyc_List_List*
non_local_preds; int try_depth; void* annot; } ; static const int Cyc_Absyn_Wild_p=
0; static const int Cyc_Absyn_Var_p= 0; struct Cyc_Absyn_Var_p_struct{ int tag;
struct Cyc_Absyn_Vardecl* f1; } ; static const int Cyc_Absyn_Null_p= 1; static
const int Cyc_Absyn_Int_p= 1; struct Cyc_Absyn_Int_p_struct{ int tag; void* f1;
int f2; } ; static const int Cyc_Absyn_Char_p= 2; struct Cyc_Absyn_Char_p_struct{
int tag; unsigned char f1; } ; static const int Cyc_Absyn_Float_p= 3; struct Cyc_Absyn_Float_p_struct{
int tag; struct _tagged_string f1; } ; static const int Cyc_Absyn_Tuple_p= 4;
struct Cyc_Absyn_Tuple_p_struct{ int tag; struct Cyc_List_List* f1; } ; static
const int Cyc_Absyn_Pointer_p= 5; struct Cyc_Absyn_Pointer_p_struct{ int tag;
struct Cyc_Absyn_Pat* f1; } ; static const int Cyc_Absyn_Reference_p= 6; struct
Cyc_Absyn_Reference_p_struct{ int tag; struct Cyc_Absyn_Vardecl* f1; } ; static
const int Cyc_Absyn_Struct_p= 7; struct Cyc_Absyn_Struct_p_struct{ int tag;
struct Cyc_Absyn_Structdecl* f1; struct Cyc_Core_Opt* f2; struct Cyc_List_List*
f3; struct Cyc_List_List* f4; } ; static const int Cyc_Absyn_Tunion_p= 8; struct
Cyc_Absyn_Tunion_p_struct{ int tag; struct Cyc_Absyn_Tuniondecl* f1; struct Cyc_Absyn_Tunionfield*
f2; struct Cyc_List_List* f3; struct Cyc_List_List* f4; } ; static const int Cyc_Absyn_Enum_p=
9; struct Cyc_Absyn_Enum_p_struct{ int tag; struct Cyc_Absyn_Enumdecl* f1;
struct Cyc_Absyn_Enumfield* f2; } ; static const int Cyc_Absyn_UnknownId_p= 10;
struct Cyc_Absyn_UnknownId_p_struct{ int tag; struct _tuple0* f1; } ; static
const int Cyc_Absyn_UnknownCall_p= 11; struct Cyc_Absyn_UnknownCall_p_struct{
int tag; struct _tuple0* f1; struct Cyc_List_List* f2; struct Cyc_List_List* f3;
} ; static const int Cyc_Absyn_UnknownFields_p= 12; struct Cyc_Absyn_UnknownFields_p_struct{
int tag; struct _tuple0* f1; struct Cyc_List_List* f2; struct Cyc_List_List* f3;
} ; struct Cyc_Absyn_Pat{ void* r; struct Cyc_Core_Opt* topt; struct Cyc_Position_Segment*
loc; } ; struct Cyc_Absyn_Switch_clause{ struct Cyc_Absyn_Pat* pattern; struct
Cyc_Core_Opt* pat_vars; struct Cyc_Absyn_Exp* where_clause; struct Cyc_Absyn_Stmt*
body; struct Cyc_Position_Segment* loc; } ; struct Cyc_Absyn_SwitchC_clause{
struct Cyc_Absyn_Exp* cnst_exp; struct Cyc_Absyn_Stmt* body; struct Cyc_Position_Segment*
loc; } ; static const int Cyc_Absyn_Unresolved_b= 0; static const int Cyc_Absyn_Global_b=
0; struct Cyc_Absyn_Global_b_struct{ int tag; struct Cyc_Absyn_Vardecl* f1; } ;
static const int Cyc_Absyn_Funname_b= 1; struct Cyc_Absyn_Funname_b_struct{ int
tag; struct Cyc_Absyn_Fndecl* f1; } ; static const int Cyc_Absyn_Param_b= 2;
struct Cyc_Absyn_Param_b_struct{ int tag; struct Cyc_Absyn_Vardecl* f1; } ;
static const int Cyc_Absyn_Local_b= 3; struct Cyc_Absyn_Local_b_struct{ int tag;
struct Cyc_Absyn_Vardecl* f1; } ; static const int Cyc_Absyn_Pat_b= 4; struct
Cyc_Absyn_Pat_b_struct{ int tag; struct Cyc_Absyn_Vardecl* f1; } ; struct Cyc_Absyn_Vardecl{
void* sc; struct _tuple0* name; struct Cyc_Absyn_Tqual tq; void* type; struct
Cyc_Absyn_Exp* initializer; struct Cyc_Core_Opt* rgn; struct Cyc_List_List*
attributes; } ; struct Cyc_Absyn_Fndecl{ void* sc; int is_inline; struct _tuple0*
name; struct Cyc_List_List* tvs; struct Cyc_Core_Opt* effect; void* ret_type;
struct Cyc_List_List* args; int c_varargs; struct Cyc_Absyn_VarargInfo*
cyc_varargs; struct Cyc_Absyn_Stmt* body; struct Cyc_Core_Opt* cached_typ;
struct Cyc_Core_Opt* param_vardecls; struct Cyc_List_List* attributes; } ;
struct Cyc_Absyn_Structfield{ struct _tagged_string* name; struct Cyc_Absyn_Tqual
tq; void* type; struct Cyc_Core_Opt* width; struct Cyc_List_List* attributes; }
; struct Cyc_Absyn_Structdecl{ void* sc; struct Cyc_Core_Opt* name; struct Cyc_List_List*
tvs; struct Cyc_Core_Opt* fields; struct Cyc_List_List* attributes; } ; struct
Cyc_Absyn_Uniondecl{ void* sc; struct Cyc_Core_Opt* name; struct Cyc_List_List*
tvs; struct Cyc_Core_Opt* fields; struct Cyc_List_List* attributes; } ; struct
Cyc_Absyn_Tunionfield{ struct _tuple0* name; struct Cyc_List_List* tvs; struct
Cyc_List_List* typs; struct Cyc_Position_Segment* loc; void* sc; } ; struct Cyc_Absyn_Tuniondecl{
void* sc; struct _tuple0* name; struct Cyc_List_List* tvs; struct Cyc_Core_Opt*
fields; int is_xtunion; } ; struct Cyc_Absyn_Enumfield{ struct _tuple0* name;
struct Cyc_Absyn_Exp* tag; struct Cyc_Position_Segment* loc; } ; struct Cyc_Absyn_Enumdecl{
void* sc; struct _tuple0* name; struct Cyc_Core_Opt* fields; } ; struct Cyc_Absyn_Typedefdecl{
struct _tuple0* name; struct Cyc_List_List* tvs; void* defn; } ; static const
int Cyc_Absyn_Var_d= 0; struct Cyc_Absyn_Var_d_struct{ int tag; struct Cyc_Absyn_Vardecl*
f1; } ; static const int Cyc_Absyn_Fn_d= 1; struct Cyc_Absyn_Fn_d_struct{ int
tag; struct Cyc_Absyn_Fndecl* f1; } ; static const int Cyc_Absyn_Let_d= 2;
struct Cyc_Absyn_Let_d_struct{ int tag; struct Cyc_Absyn_Pat* f1; struct Cyc_Core_Opt*
f2; struct Cyc_Core_Opt* f3; struct Cyc_Absyn_Exp* f4; int f5; } ; static const
int Cyc_Absyn_Letv_d= 3; struct Cyc_Absyn_Letv_d_struct{ int tag; struct Cyc_List_List*
f1; } ; static const int Cyc_Absyn_Struct_d= 4; struct Cyc_Absyn_Struct_d_struct{
int tag; struct Cyc_Absyn_Structdecl* f1; } ; static const int Cyc_Absyn_Union_d=
5; struct Cyc_Absyn_Union_d_struct{ int tag; struct Cyc_Absyn_Uniondecl* f1; } ;
static const int Cyc_Absyn_Tunion_d= 6; struct Cyc_Absyn_Tunion_d_struct{ int
tag; struct Cyc_Absyn_Tuniondecl* f1; } ; static const int Cyc_Absyn_Enum_d= 7;
struct Cyc_Absyn_Enum_d_struct{ int tag; struct Cyc_Absyn_Enumdecl* f1; } ;
static const int Cyc_Absyn_Typedef_d= 8; struct Cyc_Absyn_Typedef_d_struct{ int
tag; struct Cyc_Absyn_Typedefdecl* f1; } ; static const int Cyc_Absyn_Namespace_d=
9; struct Cyc_Absyn_Namespace_d_struct{ int tag; struct _tagged_string* f1;
struct Cyc_List_List* f2; } ; static const int Cyc_Absyn_Using_d= 10; struct Cyc_Absyn_Using_d_struct{
int tag; struct _tuple0* f1; struct Cyc_List_List* f2; } ; static const int Cyc_Absyn_ExternC_d=
11; struct Cyc_Absyn_ExternC_d_struct{ int tag; struct Cyc_List_List* f1; } ;
struct Cyc_Absyn_Decl{ void* r; struct Cyc_Position_Segment* loc; } ; static
const int Cyc_Absyn_ArrayElement= 0; struct Cyc_Absyn_ArrayElement_struct{ int
tag; struct Cyc_Absyn_Exp* f1; } ; static const int Cyc_Absyn_FieldName= 1;
struct Cyc_Absyn_FieldName_struct{ int tag; struct _tagged_string* f1; } ;
unsigned char Cyc_Absyn_EmptyAnnot[ 15u]="\000\000\000\000EmptyAnnot"; extern
int Cyc_Absyn_qvar_cmp( struct _tuple0*, struct _tuple0*); extern int Cyc_Absyn_varlist_cmp(
struct Cyc_List_List*, struct Cyc_List_List*); extern int Cyc_Absyn_tvar_cmp(
struct Cyc_Absyn_Tvar*, struct Cyc_Absyn_Tvar*); extern struct Cyc_Absyn_Tqual
Cyc_Absyn_const_tqual(); extern struct Cyc_Absyn_Tqual Cyc_Absyn_combine_tqual(
struct Cyc_Absyn_Tqual x, struct Cyc_Absyn_Tqual y); extern struct Cyc_Absyn_Tqual
Cyc_Absyn_empty_tqual(); extern struct Cyc_Absyn_Conref* Cyc_Absyn_new_conref(
void* x); extern struct Cyc_Absyn_Conref* Cyc_Absyn_empty_conref(); extern
struct Cyc_Absyn_Conref* Cyc_Absyn_compress_conref( struct Cyc_Absyn_Conref* x);
extern void* Cyc_Absyn_conref_val( struct Cyc_Absyn_Conref* x); extern void* Cyc_Absyn_new_evar(
struct Cyc_Core_Opt* k, struct Cyc_Core_Opt* tenv); extern void* Cyc_Absyn_wildtyp(
struct Cyc_Core_Opt*); extern void* Cyc_Absyn_uchar_t; extern void* Cyc_Absyn_ushort_t;
extern void* Cyc_Absyn_uint_t; extern void* Cyc_Absyn_ulong_t; extern void* Cyc_Absyn_schar_t;
extern void* Cyc_Absyn_sshort_t; extern void* Cyc_Absyn_sint_t; extern void* Cyc_Absyn_slong_t;
extern void* Cyc_Absyn_float_t; extern void* Cyc_Absyn_double_t; extern struct
_tuple0* Cyc_Absyn_exn_name; extern struct Cyc_Absyn_Tuniondecl* Cyc_Absyn_exn_xed;
extern void* Cyc_Absyn_exn_typ; extern void* Cyc_Absyn_string_typ( void* rgn);
extern void* Cyc_Absyn_const_string_typ( void* rgn); extern void* Cyc_Absyn_file_typ_nocyc();
extern void* Cyc_Absyn_file_typ(); extern void* Cyc_Absyn_bounds_one; extern
void* Cyc_Absyn_starb_typ( void* t, void* rgn, struct Cyc_Absyn_Tqual tq, void*
b); extern void* Cyc_Absyn_atb_typ( void* t, void* rgn, struct Cyc_Absyn_Tqual
tq, void* b); extern void* Cyc_Absyn_star_typ( void* t, void* rgn, struct Cyc_Absyn_Tqual
tq); extern void* Cyc_Absyn_at_typ( void* t, void* rgn, struct Cyc_Absyn_Tqual
tq); extern void* Cyc_Absyn_cstar_typ( void* t, struct Cyc_Absyn_Tqual tq);
extern void* Cyc_Absyn_tagged_typ( void* t, void* rgn, struct Cyc_Absyn_Tqual tq);
extern void* Cyc_Absyn_void_star_typ(); extern struct Cyc_Core_Opt* Cyc_Absyn_void_star_typ_opt();
extern void* Cyc_Absyn_strct( struct _tagged_string* name); extern void* Cyc_Absyn_strctq(
struct _tuple0* name); extern void* Cyc_Absyn_unionq_typ( struct _tuple0* name);
extern void* Cyc_Absyn_union_typ( struct _tagged_string* name); extern struct
Cyc_Absyn_Exp* Cyc_Absyn_new_exp( void*, struct Cyc_Position_Segment*); extern
struct Cyc_Absyn_Exp* Cyc_Absyn_New_exp( struct Cyc_Absyn_Exp* rgn_handle,
struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp*
Cyc_Absyn_copy_exp( struct Cyc_Absyn_Exp*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_const_exp(
void*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_null_exp(
struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_bool_exp(
int, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_true_exp(
struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_false_exp(
struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_int_exp(
void*, int, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_signed_int_exp(
int, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_uint_exp(
unsigned int, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_char_exp(
unsigned char c, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_float_exp(
struct _tagged_string f, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp*
Cyc_Absyn_string_exp( struct _tagged_string s, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_var_exp( struct _tuple0*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_varb_exp( struct _tuple0*, void*, struct
Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_unknownid_exp(
struct _tuple0*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_primop_exp(
void*, struct Cyc_List_List* es, struct Cyc_Position_Segment*); extern struct
Cyc_Absyn_Exp* Cyc_Absyn_prim1_exp( void*, struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_prim2_exp( void*, struct Cyc_Absyn_Exp*,
struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp*
Cyc_Absyn_add_exp( struct Cyc_Absyn_Exp*, struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_subtract_exp( struct Cyc_Absyn_Exp*,
struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp*
Cyc_Absyn_times_exp( struct Cyc_Absyn_Exp*, struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_divide_exp( struct Cyc_Absyn_Exp*, struct
Cyc_Absyn_Exp*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_eq_exp(
struct Cyc_Absyn_Exp*, struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_neq_exp( struct Cyc_Absyn_Exp*, struct
Cyc_Absyn_Exp*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_gt_exp(
struct Cyc_Absyn_Exp*, struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_lt_exp( struct Cyc_Absyn_Exp*, struct Cyc_Absyn_Exp*,
struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_gte_exp(
struct Cyc_Absyn_Exp*, struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_lte_exp( struct Cyc_Absyn_Exp*, struct
Cyc_Absyn_Exp*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_assignop_exp(
struct Cyc_Absyn_Exp*, struct Cyc_Core_Opt*, struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_assign_exp( struct Cyc_Absyn_Exp*, struct
Cyc_Absyn_Exp*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_increment_exp(
struct Cyc_Absyn_Exp*, void*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp*
Cyc_Absyn_post_inc_exp( struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_post_dec_exp( struct Cyc_Absyn_Exp*,
struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_pre_inc_exp(
struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp*
Cyc_Absyn_pre_dec_exp( struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_conditional_exp( struct Cyc_Absyn_Exp*,
struct Cyc_Absyn_Exp*, struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_and_exp( struct Cyc_Absyn_Exp*, struct
Cyc_Absyn_Exp*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_or_exp(
struct Cyc_Absyn_Exp*, struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_seq_exp( struct Cyc_Absyn_Exp*, struct
Cyc_Absyn_Exp*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_unknowncall_exp(
struct Cyc_Absyn_Exp*, struct Cyc_List_List*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_fncall_exp( struct Cyc_Absyn_Exp*, struct
Cyc_List_List*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_throw_exp(
struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp*
Cyc_Absyn_noinstantiate_exp( struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_instantiate_exp( struct Cyc_Absyn_Exp*,
struct Cyc_List_List*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp*
Cyc_Absyn_cast_exp( void*, struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_address_exp( struct Cyc_Absyn_Exp*,
struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_sizeoftyp_exp(
void* t, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_sizeofexp_exp(
struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp*
Cyc_Absyn_deref_exp( struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_structmember_exp( struct Cyc_Absyn_Exp*,
struct _tagged_string*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp*
Cyc_Absyn_structarrow_exp( struct Cyc_Absyn_Exp*, struct _tagged_string*, struct
Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_subscript_exp(
struct Cyc_Absyn_Exp*, struct Cyc_Absyn_Exp*, struct Cyc_Position_Segment*);
extern struct Cyc_Absyn_Exp* Cyc_Absyn_tuple_exp( struct Cyc_List_List*, struct
Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_stmt_exp( struct
Cyc_Absyn_Stmt*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_null_pointer_exn_exp(
struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp* Cyc_Absyn_array_exp(
struct Cyc_List_List*, struct Cyc_Position_Segment*); extern struct Cyc_Absyn_Exp*
Cyc_Absyn_unresolvedmem_exp( struct Cyc_Core_Opt*, struct Cyc_List_List*, struct
Cyc_Position_Segment*); extern struct Cyc_Absyn_Stmt* Cyc_Absyn_new_stmt( void*
s, struct Cyc_Position_Segment* loc); extern struct Cyc_Absyn_Stmt* Cyc_Absyn_skip_stmt(
struct Cyc_Position_Segment* loc); extern struct Cyc_Absyn_Stmt* Cyc_Absyn_exp_stmt(
struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment* loc); extern struct Cyc_Absyn_Stmt*
Cyc_Absyn_seq_stmt( struct Cyc_Absyn_Stmt* s1, struct Cyc_Absyn_Stmt* s2, struct
Cyc_Position_Segment* loc); extern struct Cyc_Absyn_Stmt* Cyc_Absyn_seq_stmts(
struct Cyc_List_List*, struct Cyc_Position_Segment* loc); extern struct Cyc_Absyn_Stmt*
Cyc_Absyn_return_stmt( struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment* loc);
extern struct Cyc_Absyn_Stmt* Cyc_Absyn_ifthenelse_stmt( struct Cyc_Absyn_Exp* e,
struct Cyc_Absyn_Stmt* s1, struct Cyc_Absyn_Stmt* s2, struct Cyc_Position_Segment*
loc); extern struct Cyc_Absyn_Stmt* Cyc_Absyn_while_stmt( struct Cyc_Absyn_Exp*
e, struct Cyc_Absyn_Stmt* s, struct Cyc_Position_Segment* loc); extern struct
Cyc_Absyn_Stmt* Cyc_Absyn_break_stmt( struct Cyc_Position_Segment* loc); extern
struct Cyc_Absyn_Stmt* Cyc_Absyn_continue_stmt( struct Cyc_Position_Segment* loc);
extern struct Cyc_Absyn_Stmt* Cyc_Absyn_for_stmt( struct Cyc_Absyn_Exp* e1,
struct Cyc_Absyn_Exp* e2, struct Cyc_Absyn_Exp* e3, struct Cyc_Absyn_Stmt* s,
struct Cyc_Position_Segment* loc); extern struct Cyc_Absyn_Stmt* Cyc_Absyn_switch_stmt(
struct Cyc_Absyn_Exp* e, struct Cyc_List_List*, struct Cyc_Position_Segment* loc);
extern struct Cyc_Absyn_Stmt* Cyc_Absyn_fallthru_stmt( struct Cyc_List_List* el,
struct Cyc_Position_Segment* loc); extern struct Cyc_Absyn_Stmt* Cyc_Absyn_decl_stmt(
struct Cyc_Absyn_Decl* d, struct Cyc_Absyn_Stmt* s, struct Cyc_Position_Segment*
loc); extern struct Cyc_Absyn_Stmt* Cyc_Absyn_declare_stmt( struct _tuple0*,
void*, struct Cyc_Absyn_Exp* init, struct Cyc_Absyn_Stmt*, struct Cyc_Position_Segment*
loc); extern struct Cyc_Absyn_Stmt* Cyc_Absyn_cut_stmt( struct Cyc_Absyn_Stmt* s,
struct Cyc_Position_Segment* loc); extern struct Cyc_Absyn_Stmt* Cyc_Absyn_splice_stmt(
struct Cyc_Absyn_Stmt* s, struct Cyc_Position_Segment* loc); extern struct Cyc_Absyn_Stmt*
Cyc_Absyn_label_stmt( struct _tagged_string* v, struct Cyc_Absyn_Stmt* s, struct
Cyc_Position_Segment* loc); extern struct Cyc_Absyn_Stmt* Cyc_Absyn_do_stmt(
struct Cyc_Absyn_Stmt* s, struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*
loc); extern struct Cyc_Absyn_Stmt* Cyc_Absyn_trycatch_stmt( struct Cyc_Absyn_Stmt*
s, struct Cyc_List_List* scs, struct Cyc_Position_Segment* loc); extern struct
Cyc_Absyn_Stmt* Cyc_Absyn_goto_stmt( struct _tagged_string* lab, struct Cyc_Position_Segment*
loc); extern struct Cyc_Absyn_Stmt* Cyc_Absyn_assign_stmt( struct Cyc_Absyn_Exp*
e1, struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment* loc); extern struct
Cyc_Absyn_Pat* Cyc_Absyn_new_pat( void* p, struct Cyc_Position_Segment* s);
extern struct Cyc_Absyn_Decl* Cyc_Absyn_new_decl( void* r, struct Cyc_Position_Segment*
loc); extern struct Cyc_Absyn_Decl* Cyc_Absyn_let_decl( struct Cyc_Absyn_Pat* p,
struct Cyc_Core_Opt* t_opt, struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*
loc); extern struct Cyc_Absyn_Decl* Cyc_Absyn_letv_decl( struct Cyc_List_List*,
struct Cyc_Position_Segment* loc); extern struct Cyc_Absyn_Vardecl* Cyc_Absyn_new_vardecl(
struct _tuple0* x, void* t, struct Cyc_Absyn_Exp* init); extern struct Cyc_Absyn_Vardecl*
Cyc_Absyn_static_vardecl( struct _tuple0* x, void* t, struct Cyc_Absyn_Exp* init);
extern struct Cyc_Absyn_Decl* Cyc_Absyn_struct_decl( void* s, struct Cyc_Core_Opt*
n, struct Cyc_List_List* ts, struct Cyc_Core_Opt* fs, struct Cyc_List_List* atts,
struct Cyc_Position_Segment* loc); extern struct Cyc_Absyn_Decl* Cyc_Absyn_union_decl(
void* s, struct Cyc_Core_Opt* n, struct Cyc_List_List* ts, struct Cyc_Core_Opt*
fs, struct Cyc_List_List* atts, struct Cyc_Position_Segment* loc); extern struct
Cyc_Absyn_Decl* Cyc_Absyn_tunion_decl( void* s, struct _tuple0* n, struct Cyc_List_List*
ts, struct Cyc_Core_Opt* fs, int is_xtunion, struct Cyc_Position_Segment* loc);
extern int Cyc_Absyn_is_format_prim( void* p); extern void* Cyc_Absyn_function_typ(
struct Cyc_List_List* tvs, struct Cyc_Core_Opt* eff_typ, void* ret_typ, struct
Cyc_List_List* args, int c_varargs, struct Cyc_Absyn_VarargInfo* cyc_varargs,
struct Cyc_List_List*); extern void* Cyc_Absyn_pointer_expand( void*); extern
int Cyc_Absyn_is_lvalue( struct Cyc_Absyn_Exp*); extern struct Cyc_Absyn_Structfield*
Cyc_Absyn_lookup_field( struct Cyc_List_List*, struct _tagged_string*); extern
struct Cyc_Absyn_Structfield* Cyc_Absyn_lookup_struct_field( struct Cyc_Absyn_Structdecl*,
struct _tagged_string*); extern struct Cyc_Absyn_Structfield* Cyc_Absyn_lookup_union_field(
struct Cyc_Absyn_Uniondecl*, struct _tagged_string*); struct _tuple3{ struct Cyc_Absyn_Tqual
f1; void* f2; } ; extern struct _tuple3* Cyc_Absyn_lookup_tuple_field( struct
Cyc_List_List*, int); extern struct _tagged_string Cyc_Absyn_attribute2string(
void*); extern int Cyc_Absyn_fntype_att( void* a); struct Cyc_Stdio___sFILE;
extern unsigned char Cyc_Stdio_FileCloseError[ 19u]; extern unsigned char Cyc_Stdio_FileOpenError[
18u]; struct Cyc_Stdio_FileOpenError_struct{ unsigned char* tag; struct
_tagged_string f1; } ; extern int Cyc_String_zstrptrcmp( struct _tagged_string*,
struct _tagged_string*); struct Cyc_Set_Set; extern unsigned char Cyc_Set_Absent[
11u]; struct Cyc_Dict_Dict; extern unsigned char Cyc_Dict_Present[ 12u]; extern
unsigned char Cyc_Dict_Absent[ 11u]; static const int Cyc_Tcenv_VarRes= 0;
struct Cyc_Tcenv_VarRes_struct{ int tag; void* f1; } ; static const int Cyc_Tcenv_StructRes=
1; struct Cyc_Tcenv_StructRes_struct{ int tag; struct Cyc_Absyn_Structdecl* f1;
} ; static const int Cyc_Tcenv_TunionRes= 2; struct Cyc_Tcenv_TunionRes_struct{
int tag; struct Cyc_Absyn_Tuniondecl* f1; struct Cyc_Absyn_Tunionfield* f2; } ;
static const int Cyc_Tcenv_EnumRes= 3; struct Cyc_Tcenv_EnumRes_struct{ int tag;
struct Cyc_Absyn_Enumdecl* f1; struct Cyc_Absyn_Enumfield* f2; } ; struct Cyc_Tcenv_Genv{
struct Cyc_Set_Set* namespaces; struct Cyc_Dict_Dict* structdecls; struct Cyc_Dict_Dict*
uniondecls; struct Cyc_Dict_Dict* tuniondecls; struct Cyc_Dict_Dict* enumdecls;
struct Cyc_Dict_Dict* typedefs; struct Cyc_Dict_Dict* ordinaries; struct Cyc_List_List*
availables; } ; struct Cyc_Tcenv_Fenv; static const int Cyc_Tcenv_NotLoop_j= 0;
static const int Cyc_Tcenv_CaseEnd_j= 1; static const int Cyc_Tcenv_FnEnd_j= 2;
static const int Cyc_Tcenv_Stmt_j= 0; struct Cyc_Tcenv_Stmt_j_struct{ int tag;
struct Cyc_Absyn_Stmt* f1; } ; static const int Cyc_Tcenv_Outermost= 0; struct
Cyc_Tcenv_Outermost_struct{ int tag; void* f1; } ; static const int Cyc_Tcenv_Frame=
1; struct Cyc_Tcenv_Frame_struct{ int tag; void* f1; void* f2; } ; static const
int Cyc_Tcenv_Hidden= 2; struct Cyc_Tcenv_Hidden_struct{ int tag; void* f1; void*
f2; } ; struct Cyc_Tcenv_Tenv{ struct Cyc_List_List* ns; struct Cyc_Dict_Dict*
ae; struct Cyc_Core_Opt* le; } ; extern unsigned char Cyc_Tcutil_TypeErr[ 12u];
extern void* Cyc_Tcutil_impos( struct _tagged_string); extern void* Cyc_Tcutil_compress(
void* t); static int Cyc_Absyn_zstrlist_cmp( struct Cyc_List_List* ss1, struct
Cyc_List_List* ss2){ return(( int(*)( int(* cmp)( struct _tagged_string*, struct
_tagged_string*), struct Cyc_List_List* l1, struct Cyc_List_List* l2)) Cyc_List_list_cmp)(
Cyc_String_zstrptrcmp, ss1, ss2);} int Cyc_Absyn_varlist_cmp( struct Cyc_List_List*
vs1, struct Cyc_List_List* vs2){ return Cyc_Absyn_zstrlist_cmp( vs1, vs2);}
struct _tuple4{ void* f1; void* f2; } ; int Cyc_Absyn_qvar_cmp( struct _tuple0*
q1, struct _tuple0* q2){ void* _temp0=(* q1).f1; goto _LL1; _LL1: { void* _temp2=(*
q2).f1; goto _LL3; _LL3:{ struct _tuple4 _temp5=({ struct _tuple4 _temp4; _temp4.f1=
_temp0; _temp4.f2= _temp2; _temp4;}); void* _temp21; void* _temp23; void*
_temp25; struct Cyc_List_List* _temp27; void* _temp29; struct Cyc_List_List*
_temp31; void* _temp33; struct Cyc_List_List* _temp35; void* _temp37; struct Cyc_List_List*
_temp39; void* _temp41; void* _temp43; void* _temp45; void* _temp47; void*
_temp49; void* _temp51; struct Cyc_List_List* _temp53; void* _temp55; struct Cyc_List_List*
_temp57; void* _temp59; _LL7: _LL24: _temp23= _temp5.f1; if( _temp23 ==( void*)
Cyc_Absyn_Loc_n){ goto _LL22;} else{ goto _LL9;} _LL22: _temp21= _temp5.f2; if(
_temp21 ==( void*) Cyc_Absyn_Loc_n){ goto _LL8;} else{ goto _LL9;} _LL9: _LL30:
_temp29= _temp5.f1; if(( unsigned int) _temp29 > 1u?*(( int*) _temp29) == Cyc_Absyn_Rel_n:
0){ _LL32: _temp31=(( struct Cyc_Absyn_Rel_n_struct*) _temp29)->f1; goto _LL26;}
else{ goto _LL11;} _LL26: _temp25= _temp5.f2; if(( unsigned int) _temp25 > 1u?*((
int*) _temp25) == Cyc_Absyn_Rel_n: 0){ _LL28: _temp27=(( struct Cyc_Absyn_Rel_n_struct*)
_temp25)->f1; goto _LL10;} else{ goto _LL11;} _LL11: _LL38: _temp37= _temp5.f1;
if(( unsigned int) _temp37 > 1u?*(( int*) _temp37) == Cyc_Absyn_Abs_n: 0){ _LL40:
_temp39=(( struct Cyc_Absyn_Abs_n_struct*) _temp37)->f1; goto _LL34;} else{ goto
_LL13;} _LL34: _temp33= _temp5.f2; if(( unsigned int) _temp33 > 1u?*(( int*)
_temp33) == Cyc_Absyn_Abs_n: 0){ _LL36: _temp35=(( struct Cyc_Absyn_Abs_n_struct*)
_temp33)->f1; goto _LL12;} else{ goto _LL13;} _LL13: _LL44: _temp43= _temp5.f1;
if( _temp43 ==( void*) Cyc_Absyn_Loc_n){ goto _LL42;} else{ goto _LL15;} _LL42:
_temp41= _temp5.f2; goto _LL14; _LL15: _LL48: _temp47= _temp5.f1; goto _LL46;
_LL46: _temp45= _temp5.f2; if( _temp45 ==( void*) Cyc_Absyn_Loc_n){ goto _LL16;}
else{ goto _LL17;} _LL17: _LL52: _temp51= _temp5.f1; if(( unsigned int) _temp51
> 1u?*(( int*) _temp51) == Cyc_Absyn_Rel_n: 0){ _LL54: _temp53=(( struct Cyc_Absyn_Rel_n_struct*)
_temp51)->f1; goto _LL50;} else{ goto _LL19;} _LL50: _temp49= _temp5.f2; goto
_LL18; _LL19: _LL60: _temp59= _temp5.f1; goto _LL56; _LL56: _temp55= _temp5.f2;
if(( unsigned int) _temp55 > 1u?*(( int*) _temp55) == Cyc_Absyn_Rel_n: 0){ _LL58:
_temp57=(( struct Cyc_Absyn_Rel_n_struct*) _temp55)->f1; goto _LL20;} else{ goto
_LL6;} _LL8: goto _LL6; _LL10: _temp39= _temp31; _temp35= _temp27; goto _LL12;
_LL12: { int i= Cyc_Absyn_zstrlist_cmp( _temp39, _temp35); if( i != 0){ return i;}
goto _LL6;} _LL14: return - 1; _LL16: return 1; _LL18: return - 1; _LL20: return
1; _LL6:;} return Cyc_String_zstrptrcmp((* q1).f2,(* q2).f2);}} int Cyc_Absyn_tvar_cmp(
struct Cyc_Absyn_Tvar* tv1, struct Cyc_Absyn_Tvar* tv2){ int i= Cyc_String_zstrptrcmp(
tv1->name, tv2->name); if( i != 0){ return i;} if( tv1->identity == tv2->identity){
return 0;} if( tv1->identity != 0? tv2->identity != 0: 0){ return*(( int*)
_check_null( tv1->identity)) -*(( int*) _check_null( tv2->identity));} else{ if(
tv1->identity == 0){ return - 1;} else{ return 1;}}} static int Cyc_Absyn_new_type_counter=
0; void* Cyc_Absyn_new_evar( struct Cyc_Core_Opt* k, struct Cyc_Core_Opt* env){
return( void*)({ struct Cyc_Absyn_Evar_struct* _temp61=( struct Cyc_Absyn_Evar_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Evar_struct)); _temp61[ 0]=({ struct Cyc_Absyn_Evar_struct
_temp62; _temp62.tag= Cyc_Absyn_Evar; _temp62.f1= k; _temp62.f2= 0; _temp62.f3=
Cyc_Absyn_new_type_counter ++; _temp62.f4= env; _temp62;}); _temp61;});} static
struct Cyc_Core_Opt Cyc_Absyn_mk={( void*)(( void*) 1u)}; void* Cyc_Absyn_wildtyp(
struct Cyc_Core_Opt* tenv){ return Cyc_Absyn_new_evar(( struct Cyc_Core_Opt*)&
Cyc_Absyn_mk, tenv);} struct Cyc_Absyn_Tqual Cyc_Absyn_combine_tqual( struct Cyc_Absyn_Tqual
x, struct Cyc_Absyn_Tqual y){ return({ struct Cyc_Absyn_Tqual _temp63; _temp63.q_const=
x.q_const? 1: y.q_const; _temp63.q_volatile= x.q_volatile? 1: y.q_volatile;
_temp63.q_restrict= x.q_restrict? 1: y.q_restrict; _temp63;});} struct Cyc_Absyn_Tqual
Cyc_Absyn_empty_tqual(){ return({ struct Cyc_Absyn_Tqual _temp64; _temp64.q_const=
0; _temp64.q_volatile= 0; _temp64.q_restrict= 0; _temp64;});} struct Cyc_Absyn_Tqual
Cyc_Absyn_const_tqual(){ return({ struct Cyc_Absyn_Tqual _temp65; _temp65.q_const=
1; _temp65.q_volatile= 0; _temp65.q_restrict= 0; _temp65;});} int Cyc_Absyn_is_format_prim(
void* p){ void* _temp66= p; _LL68: if( _temp66 ==( void*) Cyc_Absyn_Printf){
goto _LL69;} else{ goto _LL70;} _LL70: if( _temp66 ==( void*) Cyc_Absyn_Fprintf){
goto _LL71;} else{ goto _LL72;} _LL72: if( _temp66 ==( void*) Cyc_Absyn_Xprintf){
goto _LL73;} else{ goto _LL74;} _LL74: if( _temp66 ==( void*) Cyc_Absyn_Scanf){
goto _LL75;} else{ goto _LL76;} _LL76: if( _temp66 ==( void*) Cyc_Absyn_Fscanf){
goto _LL77;} else{ goto _LL78;} _LL78: if( _temp66 ==( void*) Cyc_Absyn_Sscanf){
goto _LL79;} else{ goto _LL80;} _LL80: goto _LL81; _LL69: return 1; _LL71:
return 1; _LL73: return 1; _LL75: return 1; _LL77: return 1; _LL79: return 1;
_LL81: return 0; _LL67:;} struct Cyc_Absyn_Conref* Cyc_Absyn_new_conref( void* x){
return({ struct Cyc_Absyn_Conref* _temp82=( struct Cyc_Absyn_Conref*) GC_malloc(
sizeof( struct Cyc_Absyn_Conref)); _temp82->v=( void*)(( void*)({ struct Cyc_Absyn_Eq_constr_struct*
_temp83=( struct Cyc_Absyn_Eq_constr_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Eq_constr_struct));
_temp83[ 0]=({ struct Cyc_Absyn_Eq_constr_struct _temp84; _temp84.tag= Cyc_Absyn_Eq_constr;
_temp84.f1=( void*) x; _temp84;}); _temp83;})); _temp82;});} struct Cyc_Absyn_Conref*
Cyc_Absyn_empty_conref(){ return({ struct Cyc_Absyn_Conref* _temp85=( struct Cyc_Absyn_Conref*)
GC_malloc( sizeof( struct Cyc_Absyn_Conref)); _temp85->v=( void*)(( void*) Cyc_Absyn_No_constr);
_temp85;});} static struct Cyc_Absyn_Eq_constr_struct Cyc_Absyn_true_constraint={
0u,( void*) 1}; static struct Cyc_Absyn_Eq_constr_struct Cyc_Absyn_false_constraint={
0u,( void*) 0}; struct Cyc_Absyn_Conref Cyc_Absyn_true_conref_v={( void*)(( void*)&
Cyc_Absyn_true_constraint)}; struct Cyc_Absyn_Conref Cyc_Absyn_false_conref_v={(
void*)(( void*)& Cyc_Absyn_false_constraint)}; struct Cyc_Absyn_Conref* Cyc_Absyn_true_conref=&
Cyc_Absyn_true_conref_v; struct Cyc_Absyn_Conref* Cyc_Absyn_false_conref=& Cyc_Absyn_false_conref_v;
struct Cyc_Absyn_Conref* Cyc_Absyn_compress_conref( struct Cyc_Absyn_Conref* x){
void* _temp88=( void*) x->v; void* _temp96; struct Cyc_Absyn_Conref* _temp98;
struct Cyc_Absyn_Conref** _temp100; _LL90: if( _temp88 ==( void*) Cyc_Absyn_No_constr){
goto _LL91;} else{ goto _LL92;} _LL92: if(( unsigned int) _temp88 > 1u?*(( int*)
_temp88) == Cyc_Absyn_Eq_constr: 0){ _LL97: _temp96=( void*)(( struct Cyc_Absyn_Eq_constr_struct*)
_temp88)->f1; goto _LL93;} else{ goto _LL94;} _LL94: if(( unsigned int) _temp88
> 1u?*(( int*) _temp88) == Cyc_Absyn_Forward_constr: 0){ _LL99: _temp98=((
struct Cyc_Absyn_Forward_constr_struct*) _temp88)->f1; _temp100=&(( struct Cyc_Absyn_Forward_constr_struct*)
_temp88)->f1; goto _LL95;} else{ goto _LL89;} _LL91: return x; _LL93: return x;
_LL95: { struct Cyc_Absyn_Conref* _temp101=(( struct Cyc_Absyn_Conref*(*)(
struct Cyc_Absyn_Conref* x)) Cyc_Absyn_compress_conref)(* _temp100); goto _LL102;
_LL102:* _temp100= _temp101; return _temp101;} _LL89:;} void* Cyc_Absyn_conref_val(
struct Cyc_Absyn_Conref* x){ void* _temp103=( void*)((( struct Cyc_Absyn_Conref*(*)(
struct Cyc_Absyn_Conref* x)) Cyc_Absyn_compress_conref)( x))->v; void* _temp109;
_LL105: if(( unsigned int) _temp103 > 1u?*(( int*) _temp103) == Cyc_Absyn_Eq_constr:
0){ _LL110: _temp109=( void*)(( struct Cyc_Absyn_Eq_constr_struct*) _temp103)->f1;
goto _LL106;} else{ goto _LL107;} _LL107: goto _LL108; _LL106: return _temp109;
_LL108: return(( void*(*)( struct _tagged_string)) Cyc_Tcutil_impos)(({
unsigned char* _temp111=( unsigned char*)"conref_val"; struct _tagged_string
_temp112; _temp112.curr= _temp111; _temp112.base= _temp111; _temp112.last_plus_one=
_temp111 + 11; _temp112;})); _LL104:;} static struct Cyc_Absyn_IntType_struct
Cyc_Absyn_uchar_tt={ 5u,( void*)(( void*) 1u),( void*)(( void*) 0u)}; static
struct Cyc_Absyn_IntType_struct Cyc_Absyn_ushort_tt={ 5u,( void*)(( void*) 1u),(
void*)(( void*) 1u)}; static struct Cyc_Absyn_IntType_struct Cyc_Absyn_uint_tt={
5u,( void*)(( void*) 1u),( void*)(( void*) 2u)}; static struct Cyc_Absyn_IntType_struct
Cyc_Absyn_ulong_tt={ 5u,( void*)(( void*) 1u),( void*)(( void*) 3u)}; void* Cyc_Absyn_uchar_t=(
void*)& Cyc_Absyn_uchar_tt; void* Cyc_Absyn_ushort_t=( void*)& Cyc_Absyn_ushort_tt;
void* Cyc_Absyn_uint_t=( void*)& Cyc_Absyn_uint_tt; void* Cyc_Absyn_ulong_t=(
void*)& Cyc_Absyn_ulong_tt; static struct Cyc_Absyn_IntType_struct Cyc_Absyn_schar_tt={
5u,( void*)(( void*) 0u),( void*)(( void*) 0u)}; static struct Cyc_Absyn_IntType_struct
Cyc_Absyn_sshort_tt={ 5u,( void*)(( void*) 0u),( void*)(( void*) 1u)}; static
struct Cyc_Absyn_IntType_struct Cyc_Absyn_sint_tt={ 5u,( void*)(( void*) 0u),(
void*)(( void*) 2u)}; static struct Cyc_Absyn_IntType_struct Cyc_Absyn_slong_tt={
5u,( void*)(( void*) 0u),( void*)(( void*) 3u)}; void* Cyc_Absyn_schar_t=( void*)&
Cyc_Absyn_schar_tt; void* Cyc_Absyn_sshort_t=( void*)& Cyc_Absyn_sshort_tt; void*
Cyc_Absyn_sint_t=( void*)& Cyc_Absyn_sint_tt; void* Cyc_Absyn_slong_t=( void*)&
Cyc_Absyn_slong_tt; void* Cyc_Absyn_float_t=( void*) 1u; void* Cyc_Absyn_double_t=(
void*) 2u; static unsigned char _temp123[ 4u]="exn"; static struct
_tagged_string Cyc_Absyn_exn_string={ _temp123, _temp123, _temp123 + 4u}; static
struct Cyc_Absyn_Abs_n_struct Cyc_Absyn_abs_null={ 1u, 0}; static struct _tuple0
Cyc_Absyn_exn_name_v={( void*)& Cyc_Absyn_abs_null,& Cyc_Absyn_exn_string};
struct _tuple0* Cyc_Absyn_exn_name=& Cyc_Absyn_exn_name_v; static struct Cyc_Absyn_Tuniondecl
Cyc_Absyn_exn_xed_v={( void*)(( void*) 3u),& Cyc_Absyn_exn_name_v, 0, 0, 1};
static struct Cyc_Absyn_KnownTunion_struct Cyc_Absyn_exn_tinfou={ 1u,& Cyc_Absyn_exn_xed_v};
struct Cyc_Absyn_Tuniondecl* Cyc_Absyn_exn_xed=& Cyc_Absyn_exn_xed_v; static
struct Cyc_Absyn_TunionType_struct Cyc_Absyn_exn_typ_tt={ 2u,{( void*)(( void*)&
Cyc_Absyn_exn_tinfou), 0,( void*)(( void*) 3u)}}; void* Cyc_Absyn_exn_typ=( void*)&
Cyc_Absyn_exn_typ_tt; static struct Cyc_Core_Opt* Cyc_Absyn_string_t_opt= 0;
void* Cyc_Absyn_string_typ( void* rgn){ if( rgn !=( void*) Cyc_Absyn_HeapRgn){
return Cyc_Absyn_starb_typ( Cyc_Absyn_uchar_t, rgn, Cyc_Absyn_empty_tqual(),(
void*) Cyc_Absyn_Unknown_b);} else{ if( Cyc_Absyn_string_t_opt == 0){ void* t=
Cyc_Absyn_starb_typ( Cyc_Absyn_uchar_t,( void*) Cyc_Absyn_HeapRgn, Cyc_Absyn_empty_tqual(),(
void*) Cyc_Absyn_Unknown_b); Cyc_Absyn_string_t_opt=({ struct Cyc_Core_Opt*
_temp127=( struct Cyc_Core_Opt*) GC_malloc( sizeof( struct Cyc_Core_Opt));
_temp127->v=( void*) t; _temp127;});} return( void*)(( struct Cyc_Core_Opt*)
_check_null( Cyc_Absyn_string_t_opt))->v;}} static struct Cyc_Core_Opt* Cyc_Absyn_const_string_t_opt=
0; void* Cyc_Absyn_const_string_typ( void* rgn){ if( rgn !=( void*) Cyc_Absyn_HeapRgn){
return Cyc_Absyn_starb_typ( Cyc_Absyn_uchar_t, rgn, Cyc_Absyn_const_tqual(),(
void*) Cyc_Absyn_Unknown_b);} else{ if( Cyc_Absyn_const_string_t_opt == 0){ void*
t= Cyc_Absyn_starb_typ( Cyc_Absyn_uchar_t,( void*) Cyc_Absyn_HeapRgn, Cyc_Absyn_const_tqual(),(
void*) Cyc_Absyn_Unknown_b); Cyc_Absyn_const_string_t_opt=({ struct Cyc_Core_Opt*
_temp128=( struct Cyc_Core_Opt*) GC_malloc( sizeof( struct Cyc_Core_Opt));
_temp128->v=( void*) t; _temp128;});} return( void*)(( struct Cyc_Core_Opt*)
_check_null( Cyc_Absyn_const_string_t_opt))->v;}} static struct Cyc_Absyn_Int_c_struct
Cyc_Absyn_one_intc={ 2u,( void*)(( void*) 0u), 1}; static struct Cyc_Absyn_Const_e_struct
Cyc_Absyn_one_b_raw={ 0u,( void*)(( void*)& Cyc_Absyn_one_intc)}; static struct
Cyc_Absyn_Exp Cyc_Absyn_one_be={ 0,( void*)(( void*)& Cyc_Absyn_one_b_raw), 0};
static struct Cyc_Absyn_Upper_b_struct Cyc_Absyn_one_bt={ 0u,& Cyc_Absyn_one_be};
void* Cyc_Absyn_bounds_one=( void*)& Cyc_Absyn_one_bt; void* Cyc_Absyn_starb_typ(
void* t, void* r, struct Cyc_Absyn_Tqual tq, void* b){ return( void*)({ struct
Cyc_Absyn_PointerType_struct* _temp132=( struct Cyc_Absyn_PointerType_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_PointerType_struct)); _temp132[ 0]=({ struct
Cyc_Absyn_PointerType_struct _temp133; _temp133.tag= Cyc_Absyn_PointerType;
_temp133.f1=({ struct Cyc_Absyn_PtrInfo _temp134; _temp134.elt_typ=( void*) t;
_temp134.rgn_typ=( void*) r; _temp134.nullable= Cyc_Absyn_true_conref; _temp134.tq=
tq; _temp134.bounds=(( struct Cyc_Absyn_Conref*(*)( void* x)) Cyc_Absyn_new_conref)(
b); _temp134;}); _temp133;}); _temp132;});} void* Cyc_Absyn_atb_typ( void* t,
void* r, struct Cyc_Absyn_Tqual tq, void* b){ return( void*)({ struct Cyc_Absyn_PointerType_struct*
_temp135=( struct Cyc_Absyn_PointerType_struct*) GC_malloc( sizeof( struct Cyc_Absyn_PointerType_struct));
_temp135[ 0]=({ struct Cyc_Absyn_PointerType_struct _temp136; _temp136.tag= Cyc_Absyn_PointerType;
_temp136.f1=({ struct Cyc_Absyn_PtrInfo _temp137; _temp137.elt_typ=( void*) t;
_temp137.rgn_typ=( void*) r; _temp137.nullable= Cyc_Absyn_false_conref; _temp137.tq=
tq; _temp137.bounds=(( struct Cyc_Absyn_Conref*(*)( void* x)) Cyc_Absyn_new_conref)(
b); _temp137;}); _temp136;}); _temp135;});} void* Cyc_Absyn_star_typ( void* t,
void* r, struct Cyc_Absyn_Tqual tq){ return Cyc_Absyn_starb_typ( t, r, tq, Cyc_Absyn_bounds_one);}
void* Cyc_Absyn_cstar_typ( void* t, struct Cyc_Absyn_Tqual tq){ return Cyc_Absyn_starb_typ(
t,( void*) Cyc_Absyn_HeapRgn, tq, Cyc_Absyn_bounds_one);} void* Cyc_Absyn_at_typ(
void* t, void* r, struct Cyc_Absyn_Tqual tq){ return Cyc_Absyn_atb_typ( t, r, tq,
Cyc_Absyn_bounds_one);} void* Cyc_Absyn_tagged_typ( void* t, void* r, struct Cyc_Absyn_Tqual
tq){ return( void*)({ struct Cyc_Absyn_PointerType_struct* _temp138=( struct Cyc_Absyn_PointerType_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_PointerType_struct)); _temp138[ 0]=({ struct
Cyc_Absyn_PointerType_struct _temp139; _temp139.tag= Cyc_Absyn_PointerType;
_temp139.f1=({ struct Cyc_Absyn_PtrInfo _temp140; _temp140.elt_typ=( void*) t;
_temp140.rgn_typ=( void*) r; _temp140.nullable= Cyc_Absyn_true_conref; _temp140.tq=
tq; _temp140.bounds=(( struct Cyc_Absyn_Conref*(*)( void* x)) Cyc_Absyn_new_conref)((
void*) Cyc_Absyn_Unknown_b); _temp140;}); _temp139;}); _temp138;});} static
struct Cyc_Core_Opt* Cyc_Absyn_file_t_opt= 0; static unsigned char _temp143[ 8u]="__sFILE";
static struct _tagged_string Cyc_Absyn_sf_str={ _temp143, _temp143, _temp143 + 8u};
static struct _tagged_string* Cyc_Absyn_sf=& Cyc_Absyn_sf_str; static
unsigned char _temp146[ 4u]="Cyc"; static struct _tagged_string Cyc_Absyn_cyc_str={
_temp146, _temp146, _temp146 + 4u}; static struct _tagged_string* Cyc_Absyn_cyc=&
Cyc_Absyn_cyc_str; static unsigned char _temp149[ 6u]="Stdio"; static struct
_tagged_string Cyc_Absyn_st_str={ _temp149, _temp149, _temp149 + 6u}; static
struct _tagged_string* Cyc_Absyn_st=& Cyc_Absyn_st_str; static void Cyc_Absyn_file_typ_ns(
struct Cyc_List_List* ns){ struct _tuple0* file_t_name=({ struct _tuple0*
_temp156=( struct _tuple0*) GC_malloc( sizeof( struct _tuple0)); _temp156->f1=(
void*)({ struct Cyc_Absyn_Abs_n_struct* _temp157=( struct Cyc_Absyn_Abs_n_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Abs_n_struct)); _temp157[ 0]=({ struct Cyc_Absyn_Abs_n_struct
_temp158; _temp158.tag= Cyc_Absyn_Abs_n; _temp158.f1= ns; _temp158;}); _temp157;});
_temp156->f2= Cyc_Absyn_sf; _temp156;}); struct Cyc_Absyn_Structdecl* sd=({
struct Cyc_Absyn_Structdecl* _temp154=( struct Cyc_Absyn_Structdecl*) GC_malloc(
sizeof( struct Cyc_Absyn_Structdecl)); _temp154->sc=( void*)(( void*) Cyc_Absyn_Abstract);
_temp154->name=({ struct Cyc_Core_Opt* _temp155=( struct Cyc_Core_Opt*)
GC_malloc( sizeof( struct Cyc_Core_Opt)); _temp155->v=( void*) file_t_name;
_temp155;}); _temp154->tvs= 0; _temp154->fields= 0; _temp154->attributes= 0;
_temp154;}); void* file_struct_typ=( void*)({ struct Cyc_Absyn_StructType_struct*
_temp151=( struct Cyc_Absyn_StructType_struct*) GC_malloc( sizeof( struct Cyc_Absyn_StructType_struct));
_temp151[ 0]=({ struct Cyc_Absyn_StructType_struct _temp152; _temp152.tag= Cyc_Absyn_StructType;
_temp152.f1=( struct _tuple0*) file_t_name; _temp152.f2= 0; _temp152.f3=({
struct Cyc_Absyn_Structdecl** _temp153=( struct Cyc_Absyn_Structdecl**)
GC_malloc( sizeof( struct Cyc_Absyn_Structdecl*) * 1); _temp153[ 0]= sd;
_temp153;}); _temp152;}); _temp151;}); Cyc_Absyn_file_t_opt=({ struct Cyc_Core_Opt*
_temp150=( struct Cyc_Core_Opt*) GC_malloc( sizeof( struct Cyc_Core_Opt));
_temp150->v=( void*) Cyc_Absyn_at_typ( file_struct_typ,( void*) Cyc_Absyn_HeapRgn,
Cyc_Absyn_empty_tqual()); _temp150;});} struct _tagged_ptr1{ struct
_tagged_string** curr; struct _tagged_string** base; struct _tagged_string**
last_plus_one; } ; void* Cyc_Absyn_file_typ(){ if( Cyc_Absyn_file_t_opt == 0){
Cyc_Absyn_file_typ_ns(({ struct Cyc_List_List*(* _temp159)( struct _tagged_ptr1)=(
struct Cyc_List_List*(*)( struct _tagged_ptr1)) Cyc_List_list; struct
_tagged_string* _temp162= Cyc_Absyn_cyc; struct _tagged_string* _temp163= Cyc_Absyn_st;
struct _tagged_string* _temp160[ 2u]={ _temp162, _temp163}; struct _tagged_ptr1
_temp161={ _temp160, _temp160, _temp160 + 2u}; _temp159( _temp161);}));} return(
void*)(( struct Cyc_Core_Opt*) _check_null( Cyc_Absyn_file_t_opt))->v;} void*
Cyc_Absyn_file_typ_nocyc(){ if( Cyc_Absyn_file_t_opt == 0){ Cyc_Absyn_file_typ_ns(({
struct Cyc_List_List*(* _temp164)( struct _tagged_ptr1)=( struct Cyc_List_List*(*)(
struct _tagged_ptr1)) Cyc_List_list; struct _tagged_string* _temp167= Cyc_Absyn_st;
struct _tagged_string* _temp165[ 1u]={ _temp167}; struct _tagged_ptr1 _temp166={
_temp165, _temp165, _temp165 + 1u}; _temp164( _temp166);}));} return( void*)((
struct Cyc_Core_Opt*) _check_null( Cyc_Absyn_file_t_opt))->v;} static struct Cyc_Core_Opt*
Cyc_Absyn_void_star_t_opt= 0; void* Cyc_Absyn_void_star_typ(){ if( Cyc_Absyn_void_star_t_opt
== 0){ Cyc_Absyn_void_star_t_opt=({ struct Cyc_Core_Opt* _temp168=( struct Cyc_Core_Opt*)
GC_malloc( sizeof( struct Cyc_Core_Opt)); _temp168->v=( void*) Cyc_Absyn_star_typ((
void*) Cyc_Absyn_VoidType,( void*) Cyc_Absyn_HeapRgn, Cyc_Absyn_empty_tqual());
_temp168;});} return( void*)(( struct Cyc_Core_Opt*) _check_null( Cyc_Absyn_void_star_t_opt))->v;}
struct Cyc_Core_Opt* Cyc_Absyn_void_star_typ_opt(){ if( Cyc_Absyn_void_star_t_opt
== 0){ Cyc_Absyn_void_star_t_opt=({ struct Cyc_Core_Opt* _temp169=( struct Cyc_Core_Opt*)
GC_malloc( sizeof( struct Cyc_Core_Opt)); _temp169->v=( void*) Cyc_Absyn_star_typ((
void*) Cyc_Absyn_VoidType,( void*) Cyc_Absyn_HeapRgn, Cyc_Absyn_empty_tqual());
_temp169;});} return Cyc_Absyn_void_star_t_opt;} void* Cyc_Absyn_strct( struct
_tagged_string* name){ return( void*)({ struct Cyc_Absyn_StructType_struct*
_temp170=( struct Cyc_Absyn_StructType_struct*) GC_malloc( sizeof( struct Cyc_Absyn_StructType_struct));
_temp170[ 0]=({ struct Cyc_Absyn_StructType_struct _temp171; _temp171.tag= Cyc_Absyn_StructType;
_temp171.f1=({ struct _tuple0* _temp172=( struct _tuple0*) GC_malloc( sizeof(
struct _tuple0) * 1); _temp172[ 0]=({ struct _tuple0 _temp173; _temp173.f1=(
void*)({ struct Cyc_Absyn_Abs_n_struct* _temp174=( struct Cyc_Absyn_Abs_n_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Abs_n_struct)); _temp174[ 0]=({ struct Cyc_Absyn_Abs_n_struct
_temp175; _temp175.tag= Cyc_Absyn_Abs_n; _temp175.f1= 0; _temp175;}); _temp174;});
_temp173.f2= name; _temp173;}); _temp172;}); _temp171.f2= 0; _temp171.f3= 0;
_temp171;}); _temp170;});} void* Cyc_Absyn_union_typ( struct _tagged_string*
name){ return( void*)({ struct Cyc_Absyn_UnionType_struct* _temp176=( struct Cyc_Absyn_UnionType_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_UnionType_struct)); _temp176[ 0]=({ struct
Cyc_Absyn_UnionType_struct _temp177; _temp177.tag= Cyc_Absyn_UnionType; _temp177.f1=({
struct _tuple0* _temp178=( struct _tuple0*) GC_malloc( sizeof( struct _tuple0) *
1); _temp178[ 0]=({ struct _tuple0 _temp179; _temp179.f1=( void*)({ struct Cyc_Absyn_Abs_n_struct*
_temp180=( struct Cyc_Absyn_Abs_n_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Abs_n_struct));
_temp180[ 0]=({ struct Cyc_Absyn_Abs_n_struct _temp181; _temp181.tag= Cyc_Absyn_Abs_n;
_temp181.f1= 0; _temp181;}); _temp180;}); _temp179.f2= name; _temp179;});
_temp178;}); _temp177.f2= 0; _temp177.f3= 0; _temp177;}); _temp176;});} void*
Cyc_Absyn_strctq( struct _tuple0* name){ return( void*)({ struct Cyc_Absyn_StructType_struct*
_temp182=( struct Cyc_Absyn_StructType_struct*) GC_malloc( sizeof( struct Cyc_Absyn_StructType_struct));
_temp182[ 0]=({ struct Cyc_Absyn_StructType_struct _temp183; _temp183.tag= Cyc_Absyn_StructType;
_temp183.f1=( struct _tuple0*) name; _temp183.f2= 0; _temp183.f3= 0; _temp183;});
_temp182;});} void* Cyc_Absyn_unionq_typ( struct _tuple0* name){ return( void*)({
struct Cyc_Absyn_UnionType_struct* _temp184=( struct Cyc_Absyn_UnionType_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_UnionType_struct)); _temp184[ 0]=({ struct
Cyc_Absyn_UnionType_struct _temp185; _temp185.tag= Cyc_Absyn_UnionType; _temp185.f1=(
struct _tuple0*) name; _temp185.f2= 0; _temp185.f3= 0; _temp185;}); _temp184;});}
struct Cyc_Absyn_Exp* Cyc_Absyn_new_exp( void* r, struct Cyc_Position_Segment*
loc){ return({ struct Cyc_Absyn_Exp* _temp186=( struct Cyc_Absyn_Exp*) GC_malloc(
sizeof( struct Cyc_Absyn_Exp)); _temp186->topt= 0; _temp186->r=( void*) r;
_temp186->loc= loc; _temp186;});} struct Cyc_Absyn_Exp* Cyc_Absyn_New_exp(
struct Cyc_Absyn_Exp* rgn_handle, struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_exp(( void*)({ struct Cyc_Absyn_New_e_struct*
_temp187=( struct Cyc_Absyn_New_e_struct*) GC_malloc( sizeof( struct Cyc_Absyn_New_e_struct));
_temp187[ 0]=({ struct Cyc_Absyn_New_e_struct _temp188; _temp188.tag= Cyc_Absyn_New_e;
_temp188.f1= rgn_handle; _temp188.f2= e; _temp188;}); _temp187;}), loc);} struct
Cyc_Absyn_Exp* Cyc_Absyn_copy_exp( struct Cyc_Absyn_Exp* e){ return({ struct Cyc_Absyn_Exp*
_temp189=( struct Cyc_Absyn_Exp*) GC_malloc( sizeof( struct Cyc_Absyn_Exp));
_temp189->topt= e->topt; _temp189->r=( void*)(( void*) e->r); _temp189->loc= e->loc;
_temp189;});} struct Cyc_Absyn_Exp* Cyc_Absyn_const_exp( void* c, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_exp(( void*)({ struct Cyc_Absyn_Const_e_struct*
_temp190=( struct Cyc_Absyn_Const_e_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Const_e_struct));
_temp190[ 0]=({ struct Cyc_Absyn_Const_e_struct _temp191; _temp191.tag= Cyc_Absyn_Const_e;
_temp191.f1=( void*) c; _temp191;}); _temp190;}), loc);} struct Cyc_Absyn_Exp*
Cyc_Absyn_null_exp( struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp((
void*)({ struct Cyc_Absyn_Const_e_struct* _temp192=( struct Cyc_Absyn_Const_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Const_e_struct)); _temp192[ 0]=({ struct Cyc_Absyn_Const_e_struct
_temp193; _temp193.tag= Cyc_Absyn_Const_e; _temp193.f1=( void*)(( void*) Cyc_Absyn_Null_c);
_temp193;}); _temp192;}), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_int_exp( void*
s, int i, struct Cyc_Position_Segment* seg){ return Cyc_Absyn_const_exp(( void*)({
struct Cyc_Absyn_Int_c_struct* _temp194=( struct Cyc_Absyn_Int_c_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Int_c_struct)); _temp194[ 0]=({ struct Cyc_Absyn_Int_c_struct
_temp195; _temp195.tag= Cyc_Absyn_Int_c; _temp195.f1=( void*) s; _temp195.f2= i;
_temp195;}); _temp194;}), seg);} struct Cyc_Absyn_Exp* Cyc_Absyn_signed_int_exp(
int i, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_int_exp(( void*) Cyc_Absyn_Signed,
i, loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_uint_exp( unsigned int i, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_int_exp(( void*) Cyc_Absyn_Unsigned,( int) i, loc);}
struct Cyc_Absyn_Exp* Cyc_Absyn_bool_exp( int b, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_signed_int_exp( b? 1: 0, loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_true_exp(
struct Cyc_Position_Segment* loc){ return Cyc_Absyn_bool_exp( 1, loc);} struct
Cyc_Absyn_Exp* Cyc_Absyn_false_exp( struct Cyc_Position_Segment* loc){ return
Cyc_Absyn_bool_exp( 0, loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_char_exp(
unsigned char c, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_const_exp((
void*)({ struct Cyc_Absyn_Char_c_struct* _temp196=( struct Cyc_Absyn_Char_c_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Char_c_struct)); _temp196[ 0]=({ struct Cyc_Absyn_Char_c_struct
_temp197; _temp197.tag= Cyc_Absyn_Char_c; _temp197.f1=( void*)(( void*) Cyc_Absyn_Unsigned);
_temp197.f2= c; _temp197;}); _temp196;}), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_float_exp(
struct _tagged_string f, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_const_exp((
void*)({ struct Cyc_Absyn_Float_c_struct* _temp198=( struct Cyc_Absyn_Float_c_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Float_c_struct)); _temp198[ 0]=({ struct Cyc_Absyn_Float_c_struct
_temp199; _temp199.tag= Cyc_Absyn_Float_c; _temp199.f1= f; _temp199;}); _temp198;}),
loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_string_exp( struct _tagged_string s,
struct Cyc_Position_Segment* loc){ return Cyc_Absyn_const_exp(( void*)({ struct
Cyc_Absyn_String_c_struct* _temp200=( struct Cyc_Absyn_String_c_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_String_c_struct)); _temp200[ 0]=({ struct
Cyc_Absyn_String_c_struct _temp201; _temp201.tag= Cyc_Absyn_String_c; _temp201.f1=
s; _temp201;}); _temp200;}), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_var_exp(
struct _tuple0* q, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp((
void*)({ struct Cyc_Absyn_Var_e_struct* _temp202=( struct Cyc_Absyn_Var_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Var_e_struct)); _temp202[ 0]=({ struct Cyc_Absyn_Var_e_struct
_temp203; _temp203.tag= Cyc_Absyn_Var_e; _temp203.f1= q; _temp203.f2=( void*)((
void*) Cyc_Absyn_Unresolved_b); _temp203;}); _temp202;}), loc);} struct Cyc_Absyn_Exp*
Cyc_Absyn_varb_exp( struct _tuple0* q, void* b, struct Cyc_Position_Segment* loc){
return Cyc_Absyn_new_exp(( void*)({ struct Cyc_Absyn_Var_e_struct* _temp204=(
struct Cyc_Absyn_Var_e_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Var_e_struct));
_temp204[ 0]=({ struct Cyc_Absyn_Var_e_struct _temp205; _temp205.tag= Cyc_Absyn_Var_e;
_temp205.f1= q; _temp205.f2=( void*) b; _temp205;}); _temp204;}), loc);} struct
Cyc_Absyn_Exp* Cyc_Absyn_unknownid_exp( struct _tuple0* q, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_exp(( void*)({ struct Cyc_Absyn_UnknownId_e_struct*
_temp206=( struct Cyc_Absyn_UnknownId_e_struct*) GC_malloc( sizeof( struct Cyc_Absyn_UnknownId_e_struct));
_temp206[ 0]=({ struct Cyc_Absyn_UnknownId_e_struct _temp207; _temp207.tag= Cyc_Absyn_UnknownId_e;
_temp207.f1= q; _temp207;}); _temp206;}), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_primop_exp(
void* p, struct Cyc_List_List* es, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp((
void*)({ struct Cyc_Absyn_Primop_e_struct* _temp208=( struct Cyc_Absyn_Primop_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Primop_e_struct)); _temp208[ 0]=({ struct
Cyc_Absyn_Primop_e_struct _temp209; _temp209.tag= Cyc_Absyn_Primop_e; _temp209.f1=(
void*) p; _temp209.f2= es; _temp209;}); _temp208;}), loc);} struct Cyc_Absyn_Exp*
Cyc_Absyn_prim1_exp( void* p, struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_primop_exp( p,({ struct Cyc_List_List* _temp210=( struct
Cyc_List_List*) GC_malloc( sizeof( struct Cyc_List_List)); _temp210->hd=( void*)
e; _temp210->tl= 0; _temp210;}), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_prim2_exp(
void* p, struct Cyc_Absyn_Exp* e1, struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_primop_exp( p,({ struct Cyc_List_List* _temp211=( struct
Cyc_List_List*) GC_malloc( sizeof( struct Cyc_List_List)); _temp211->hd=( void*)
e1; _temp211->tl=({ struct Cyc_List_List* _temp212=( struct Cyc_List_List*)
GC_malloc( sizeof( struct Cyc_List_List)); _temp212->hd=( void*) e2; _temp212->tl=
0; _temp212;}); _temp211;}), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_add_exp(
struct Cyc_Absyn_Exp* e1, struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_prim2_exp(( void*) Cyc_Absyn_Plus, e1, e2, loc);} struct
Cyc_Absyn_Exp* Cyc_Absyn_subtract_exp( struct Cyc_Absyn_Exp* e1, struct Cyc_Absyn_Exp*
e2, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_prim2_exp(( void*) Cyc_Absyn_Minus,
e1, e2, loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_times_exp( struct Cyc_Absyn_Exp*
e1, struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_prim2_exp((
void*) Cyc_Absyn_Times, e1, e2, loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_divide_exp(
struct Cyc_Absyn_Exp* e1, struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_prim2_exp(( void*) Cyc_Absyn_Div, e1, e2, loc);} struct
Cyc_Absyn_Exp* Cyc_Absyn_eq_exp( struct Cyc_Absyn_Exp* e1, struct Cyc_Absyn_Exp*
e2, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_prim2_exp(( void*) Cyc_Absyn_Eq,
e1, e2, loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_neq_exp( struct Cyc_Absyn_Exp* e1,
struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_prim2_exp((
void*) Cyc_Absyn_Neq, e1, e2, loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_gt_exp(
struct Cyc_Absyn_Exp* e1, struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_prim2_exp(( void*) Cyc_Absyn_Gt, e1, e2, loc);} struct
Cyc_Absyn_Exp* Cyc_Absyn_lt_exp( struct Cyc_Absyn_Exp* e1, struct Cyc_Absyn_Exp*
e2, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_prim2_exp(( void*) Cyc_Absyn_Lt,
e1, e2, loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_gte_exp( struct Cyc_Absyn_Exp* e1,
struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_prim2_exp((
void*) Cyc_Absyn_Gte, e1, e2, loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_lte_exp(
struct Cyc_Absyn_Exp* e1, struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_prim2_exp(( void*) Cyc_Absyn_Lte, e1, e2, loc);} struct
Cyc_Absyn_Exp* Cyc_Absyn_assignop_exp( struct Cyc_Absyn_Exp* e1, struct Cyc_Core_Opt*
popt, struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp((
void*)({ struct Cyc_Absyn_AssignOp_e_struct* _temp213=( struct Cyc_Absyn_AssignOp_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_AssignOp_e_struct)); _temp213[ 0]=({ struct
Cyc_Absyn_AssignOp_e_struct _temp214; _temp214.tag= Cyc_Absyn_AssignOp_e;
_temp214.f1= e1; _temp214.f2= popt; _temp214.f3= e2; _temp214;}); _temp213;}),
loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_assign_exp( struct Cyc_Absyn_Exp* e1,
struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_assignop_exp(
e1, 0, e2, loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_increment_exp( struct Cyc_Absyn_Exp*
e, void* i, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp(( void*)({
struct Cyc_Absyn_Increment_e_struct* _temp215=( struct Cyc_Absyn_Increment_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Increment_e_struct)); _temp215[ 0]=({ struct
Cyc_Absyn_Increment_e_struct _temp216; _temp216.tag= Cyc_Absyn_Increment_e;
_temp216.f1= e; _temp216.f2=( void*) i; _temp216;}); _temp215;}), loc);} struct
Cyc_Absyn_Exp* Cyc_Absyn_post_inc_exp( struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_increment_exp( e,( void*) Cyc_Absyn_PostInc, loc);}
struct Cyc_Absyn_Exp* Cyc_Absyn_pre_inc_exp( struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_increment_exp( e,( void*) Cyc_Absyn_PreInc, loc);} struct
Cyc_Absyn_Exp* Cyc_Absyn_pre_dec_exp( struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_increment_exp( e,( void*) Cyc_Absyn_PreDec, loc);} struct
Cyc_Absyn_Exp* Cyc_Absyn_post_dec_exp( struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_increment_exp( e,( void*) Cyc_Absyn_PostDec, loc);}
struct Cyc_Absyn_Exp* Cyc_Absyn_conditional_exp( struct Cyc_Absyn_Exp* e1,
struct Cyc_Absyn_Exp* e2, struct Cyc_Absyn_Exp* e3, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_exp(( void*)({ struct Cyc_Absyn_Conditional_e_struct*
_temp217=( struct Cyc_Absyn_Conditional_e_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Conditional_e_struct));
_temp217[ 0]=({ struct Cyc_Absyn_Conditional_e_struct _temp218; _temp218.tag=
Cyc_Absyn_Conditional_e; _temp218.f1= e1; _temp218.f2= e2; _temp218.f3= e3;
_temp218;}); _temp217;}), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_and_exp( struct
Cyc_Absyn_Exp* e1, struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment* loc){
return Cyc_Absyn_conditional_exp( e1, e2, Cyc_Absyn_false_exp( loc), loc);}
struct Cyc_Absyn_Exp* Cyc_Absyn_or_exp( struct Cyc_Absyn_Exp* e1, struct Cyc_Absyn_Exp*
e2, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_conditional_exp( e1, Cyc_Absyn_true_exp(
loc), e2, loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_seq_exp( struct Cyc_Absyn_Exp*
e1, struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp((
void*)({ struct Cyc_Absyn_SeqExp_e_struct* _temp219=( struct Cyc_Absyn_SeqExp_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_SeqExp_e_struct)); _temp219[ 0]=({ struct
Cyc_Absyn_SeqExp_e_struct _temp220; _temp220.tag= Cyc_Absyn_SeqExp_e; _temp220.f1=
e1; _temp220.f2= e2; _temp220;}); _temp219;}), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_unknowncall_exp(
struct Cyc_Absyn_Exp* e, struct Cyc_List_List* es, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_exp(( void*)({ struct Cyc_Absyn_UnknownCall_e_struct*
_temp221=( struct Cyc_Absyn_UnknownCall_e_struct*) GC_malloc( sizeof( struct Cyc_Absyn_UnknownCall_e_struct));
_temp221[ 0]=({ struct Cyc_Absyn_UnknownCall_e_struct _temp222; _temp222.tag=
Cyc_Absyn_UnknownCall_e; _temp222.f1= e; _temp222.f2= es; _temp222;}); _temp221;}),
loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_fncall_exp( struct Cyc_Absyn_Exp* e,
struct Cyc_List_List* es, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp((
void*)({ struct Cyc_Absyn_FnCall_e_struct* _temp223=( struct Cyc_Absyn_FnCall_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_FnCall_e_struct)); _temp223[ 0]=({ struct
Cyc_Absyn_FnCall_e_struct _temp224; _temp224.tag= Cyc_Absyn_FnCall_e; _temp224.f1=
e; _temp224.f2= es; _temp224.f3= 0; _temp224;}); _temp223;}), loc);} struct Cyc_Absyn_Exp*
Cyc_Absyn_noinstantiate_exp( struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_exp(( void*)({ struct Cyc_Absyn_NoInstantiate_e_struct*
_temp225=( struct Cyc_Absyn_NoInstantiate_e_struct*) GC_malloc( sizeof( struct
Cyc_Absyn_NoInstantiate_e_struct)); _temp225[ 0]=({ struct Cyc_Absyn_NoInstantiate_e_struct
_temp226; _temp226.tag= Cyc_Absyn_NoInstantiate_e; _temp226.f1= e; _temp226;});
_temp225;}), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_instantiate_exp( struct Cyc_Absyn_Exp*
e, struct Cyc_List_List* ts, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp((
void*)({ struct Cyc_Absyn_Instantiate_e_struct* _temp227=( struct Cyc_Absyn_Instantiate_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Instantiate_e_struct)); _temp227[ 0]=({
struct Cyc_Absyn_Instantiate_e_struct _temp228; _temp228.tag= Cyc_Absyn_Instantiate_e;
_temp228.f1= e; _temp228.f2= ts; _temp228;}); _temp227;}), loc);} struct Cyc_Absyn_Exp*
Cyc_Absyn_cast_exp( void* t, struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_exp(( void*)({ struct Cyc_Absyn_Cast_e_struct*
_temp229=( struct Cyc_Absyn_Cast_e_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Cast_e_struct));
_temp229[ 0]=({ struct Cyc_Absyn_Cast_e_struct _temp230; _temp230.tag= Cyc_Absyn_Cast_e;
_temp230.f1=( void*) t; _temp230.f2= e; _temp230;}); _temp229;}), loc);} struct
Cyc_Absyn_Exp* Cyc_Absyn_throw_exp( struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_exp(( void*)({ struct Cyc_Absyn_Throw_e_struct*
_temp231=( struct Cyc_Absyn_Throw_e_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Throw_e_struct));
_temp231[ 0]=({ struct Cyc_Absyn_Throw_e_struct _temp232; _temp232.tag= Cyc_Absyn_Throw_e;
_temp232.f1= e; _temp232;}); _temp231;}), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_address_exp(
struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp((
void*)({ struct Cyc_Absyn_Address_e_struct* _temp233=( struct Cyc_Absyn_Address_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Address_e_struct)); _temp233[ 0]=({ struct
Cyc_Absyn_Address_e_struct _temp234; _temp234.tag= Cyc_Absyn_Address_e; _temp234.f1=
e; _temp234;}); _temp233;}), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_sizeoftyp_exp(
void* t, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp(( void*)({
struct Cyc_Absyn_Sizeoftyp_e_struct* _temp235=( struct Cyc_Absyn_Sizeoftyp_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Sizeoftyp_e_struct)); _temp235[ 0]=({ struct
Cyc_Absyn_Sizeoftyp_e_struct _temp236; _temp236.tag= Cyc_Absyn_Sizeoftyp_e;
_temp236.f1=( void*) t; _temp236;}); _temp235;}), loc);} struct Cyc_Absyn_Exp*
Cyc_Absyn_sizeofexp_exp( struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_exp(( void*)({ struct Cyc_Absyn_Sizeofexp_e_struct*
_temp237=( struct Cyc_Absyn_Sizeofexp_e_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Sizeofexp_e_struct));
_temp237[ 0]=({ struct Cyc_Absyn_Sizeofexp_e_struct _temp238; _temp238.tag= Cyc_Absyn_Sizeofexp_e;
_temp238.f1= e; _temp238;}); _temp237;}), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_deref_exp(
struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp((
void*)({ struct Cyc_Absyn_Deref_e_struct* _temp239=( struct Cyc_Absyn_Deref_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Deref_e_struct)); _temp239[ 0]=({ struct Cyc_Absyn_Deref_e_struct
_temp240; _temp240.tag= Cyc_Absyn_Deref_e; _temp240.f1= e; _temp240;}); _temp239;}),
loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_structmember_exp( struct Cyc_Absyn_Exp* e,
struct _tagged_string* n, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp((
void*)({ struct Cyc_Absyn_StructMember_e_struct* _temp241=( struct Cyc_Absyn_StructMember_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_StructMember_e_struct)); _temp241[ 0]=({
struct Cyc_Absyn_StructMember_e_struct _temp242; _temp242.tag= Cyc_Absyn_StructMember_e;
_temp242.f1= e; _temp242.f2= n; _temp242;}); _temp241;}), loc);} struct Cyc_Absyn_Exp*
Cyc_Absyn_structarrow_exp( struct Cyc_Absyn_Exp* e, struct _tagged_string* n,
struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp(( void*)({ struct
Cyc_Absyn_StructArrow_e_struct* _temp243=( struct Cyc_Absyn_StructArrow_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_StructArrow_e_struct)); _temp243[ 0]=({
struct Cyc_Absyn_StructArrow_e_struct _temp244; _temp244.tag= Cyc_Absyn_StructArrow_e;
_temp244.f1= e; _temp244.f2= n; _temp244;}); _temp243;}), loc);} struct Cyc_Absyn_Exp*
Cyc_Absyn_arrow_exp( struct Cyc_Absyn_Exp* e, struct _tagged_string* n, struct
Cyc_Position_Segment* loc){ return Cyc_Absyn_deref_exp( Cyc_Absyn_structmember_exp(
e, n, loc), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_subscript_exp( struct Cyc_Absyn_Exp*
e1, struct Cyc_Absyn_Exp* e2, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp((
void*)({ struct Cyc_Absyn_Subscript_e_struct* _temp245=( struct Cyc_Absyn_Subscript_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Subscript_e_struct)); _temp245[ 0]=({ struct
Cyc_Absyn_Subscript_e_struct _temp246; _temp246.tag= Cyc_Absyn_Subscript_e;
_temp246.f1= e1; _temp246.f2= e2; _temp246;}); _temp245;}), loc);} struct Cyc_Absyn_Exp*
Cyc_Absyn_tuple_exp( struct Cyc_List_List* es, struct Cyc_Position_Segment* loc){
return Cyc_Absyn_new_exp(( void*)({ struct Cyc_Absyn_Tuple_e_struct* _temp247=(
struct Cyc_Absyn_Tuple_e_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Tuple_e_struct));
_temp247[ 0]=({ struct Cyc_Absyn_Tuple_e_struct _temp248; _temp248.tag= Cyc_Absyn_Tuple_e;
_temp248.f1= es; _temp248;}); _temp247;}), loc);} struct Cyc_Absyn_Exp* Cyc_Absyn_stmt_exp(
struct Cyc_Absyn_Stmt* s, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp((
void*)({ struct Cyc_Absyn_StmtExp_e_struct* _temp249=( struct Cyc_Absyn_StmtExp_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_StmtExp_e_struct)); _temp249[ 0]=({ struct
Cyc_Absyn_StmtExp_e_struct _temp250; _temp250.tag= Cyc_Absyn_StmtExp_e; _temp250.f1=
s; _temp250;}); _temp249;}), loc);} static unsigned char _temp253[ 15u]="Null_Exception";
static struct _tagged_string Cyc_Absyn_ne_str={ _temp253, _temp253, _temp253 +
15u}; static struct Cyc_Absyn_Abs_n_struct Cyc_Absyn_top_ns={ 1u, 0}; static
struct _tuple0 Cyc_Absyn_ne={( void*)& Cyc_Absyn_top_ns,& Cyc_Absyn_ne_str};
struct Cyc_Absyn_Exp* Cyc_Absyn_null_pointer_exn_exp( struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_var_exp(& Cyc_Absyn_ne, loc);} struct _tuple5{ struct Cyc_List_List*
f1; struct Cyc_Absyn_Exp* f2; } ; struct Cyc_Absyn_Exp* Cyc_Absyn_array_exp(
struct Cyc_List_List* es, struct Cyc_Position_Segment* loc){ struct Cyc_List_List*
_temp255= 0; goto _LL256; _LL256: for( 0; es != 0; es=(( struct Cyc_List_List*)
_check_null( es))->tl){ _temp255=({ struct Cyc_List_List* _temp257=( struct Cyc_List_List*)
GC_malloc( sizeof( struct Cyc_List_List)); _temp257->hd=( void*)({ struct
_tuple5* _temp258=( struct _tuple5*) GC_malloc( sizeof( struct _tuple5));
_temp258->f1= 0; _temp258->f2=( struct Cyc_Absyn_Exp*)(( struct Cyc_List_List*)
_check_null( es))->hd; _temp258;}); _temp257->tl= _temp255; _temp257;});}
_temp255=(( struct Cyc_List_List*(*)( struct Cyc_List_List* x)) Cyc_List_imp_rev)(
_temp255); return Cyc_Absyn_new_exp(( void*)({ struct Cyc_Absyn_Array_e_struct*
_temp259=( struct Cyc_Absyn_Array_e_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Array_e_struct));
_temp259[ 0]=({ struct Cyc_Absyn_Array_e_struct _temp260; _temp260.tag= Cyc_Absyn_Array_e;
_temp260.f1= _temp255; _temp260;}); _temp259;}), loc);} struct Cyc_Absyn_Exp*
Cyc_Absyn_unresolvedmem_exp( struct Cyc_Core_Opt* n, struct Cyc_List_List* dles,
struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_exp(( void*)({ struct
Cyc_Absyn_UnresolvedMem_e_struct* _temp261=( struct Cyc_Absyn_UnresolvedMem_e_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_UnresolvedMem_e_struct)); _temp261[ 0]=({
struct Cyc_Absyn_UnresolvedMem_e_struct _temp262; _temp262.tag= Cyc_Absyn_UnresolvedMem_e;
_temp262.f1= n; _temp262.f2= dles; _temp262;}); _temp261;}), loc);} struct Cyc_Absyn_Stmt*
Cyc_Absyn_new_stmt( void* s, struct Cyc_Position_Segment* loc){ return({ struct
Cyc_Absyn_Stmt* _temp263=( struct Cyc_Absyn_Stmt*) GC_malloc( sizeof( struct Cyc_Absyn_Stmt));
_temp263->r=( void*) s; _temp263->loc= loc; _temp263->non_local_preds= 0;
_temp263->try_depth= 0; _temp263->annot=( void*)(( void*) Cyc_Absyn_EmptyAnnot);
_temp263;});} struct Cyc_Absyn_Stmt* Cyc_Absyn_skip_stmt( struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_stmt(( void*) Cyc_Absyn_Skip_s, loc);} struct Cyc_Absyn_Stmt*
Cyc_Absyn_exp_stmt( struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment* loc){
return Cyc_Absyn_new_stmt(( void*)({ struct Cyc_Absyn_Exp_s_struct* _temp264=(
struct Cyc_Absyn_Exp_s_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Exp_s_struct));
_temp264[ 0]=({ struct Cyc_Absyn_Exp_s_struct _temp265; _temp265.tag= Cyc_Absyn_Exp_s;
_temp265.f1= e; _temp265;}); _temp264;}), loc);} struct Cyc_Absyn_Stmt* Cyc_Absyn_seq_stmts(
struct Cyc_List_List* ss, struct Cyc_Position_Segment* loc){ if( ss == 0){
return Cyc_Absyn_skip_stmt( loc);} else{ if((( struct Cyc_List_List*)
_check_null( ss))->tl == 0){ return( struct Cyc_Absyn_Stmt*)(( struct Cyc_List_List*)
_check_null( ss))->hd;} else{ return Cyc_Absyn_seq_stmt(( struct Cyc_Absyn_Stmt*)((
struct Cyc_List_List*) _check_null( ss))->hd, Cyc_Absyn_seq_stmts((( struct Cyc_List_List*)
_check_null( ss))->tl, loc), loc);}}} struct Cyc_Absyn_Stmt* Cyc_Absyn_return_stmt(
struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_stmt((
void*)({ struct Cyc_Absyn_Return_s_struct* _temp266=( struct Cyc_Absyn_Return_s_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Return_s_struct)); _temp266[ 0]=({ struct
Cyc_Absyn_Return_s_struct _temp267; _temp267.tag= Cyc_Absyn_Return_s; _temp267.f1=
e; _temp267;}); _temp266;}), loc);} struct Cyc_Absyn_Stmt* Cyc_Absyn_ifthenelse_stmt(
struct Cyc_Absyn_Exp* e, struct Cyc_Absyn_Stmt* s1, struct Cyc_Absyn_Stmt* s2,
struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_stmt(( void*)({ struct
Cyc_Absyn_IfThenElse_s_struct* _temp268=( struct Cyc_Absyn_IfThenElse_s_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_IfThenElse_s_struct)); _temp268[ 0]=({
struct Cyc_Absyn_IfThenElse_s_struct _temp269; _temp269.tag= Cyc_Absyn_IfThenElse_s;
_temp269.f1= e; _temp269.f2= s1; _temp269.f3= s2; _temp269;}); _temp268;}), loc);}
struct Cyc_Absyn_Stmt* Cyc_Absyn_while_stmt( struct Cyc_Absyn_Exp* e, struct Cyc_Absyn_Stmt*
s, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_stmt(( void*)({
struct Cyc_Absyn_While_s_struct* _temp270=( struct Cyc_Absyn_While_s_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_While_s_struct)); _temp270[ 0]=({ struct Cyc_Absyn_While_s_struct
_temp271; _temp271.tag= Cyc_Absyn_While_s; _temp271.f1=({ struct _tuple2
_temp272; _temp272.f1= e; _temp272.f2= Cyc_Absyn_skip_stmt( e->loc); _temp272;});
_temp271.f2= s; _temp271;}); _temp270;}), loc);} struct Cyc_Absyn_Stmt* Cyc_Absyn_break_stmt(
struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_stmt(( void*)({ struct
Cyc_Absyn_Break_s_struct* _temp273=( struct Cyc_Absyn_Break_s_struct*) GC_malloc(
sizeof( struct Cyc_Absyn_Break_s_struct)); _temp273[ 0]=({ struct Cyc_Absyn_Break_s_struct
_temp274; _temp274.tag= Cyc_Absyn_Break_s; _temp274.f1= 0; _temp274;}); _temp273;}),
loc);} struct Cyc_Absyn_Stmt* Cyc_Absyn_continue_stmt( struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_stmt(( void*)({ struct Cyc_Absyn_Continue_s_struct*
_temp275=( struct Cyc_Absyn_Continue_s_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Continue_s_struct));
_temp275[ 0]=({ struct Cyc_Absyn_Continue_s_struct _temp276; _temp276.tag= Cyc_Absyn_Continue_s;
_temp276.f1= 0; _temp276;}); _temp275;}), loc);} struct Cyc_Absyn_Stmt* Cyc_Absyn_for_stmt(
struct Cyc_Absyn_Exp* e1, struct Cyc_Absyn_Exp* e2, struct Cyc_Absyn_Exp* e3,
struct Cyc_Absyn_Stmt* s, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_stmt((
void*)({ struct Cyc_Absyn_For_s_struct* _temp277=( struct Cyc_Absyn_For_s_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_For_s_struct)); _temp277[ 0]=({ struct Cyc_Absyn_For_s_struct
_temp278; _temp278.tag= Cyc_Absyn_For_s; _temp278.f1= e1; _temp278.f2=({ struct
_tuple2 _temp279; _temp279.f1= e2; _temp279.f2= Cyc_Absyn_skip_stmt( e3->loc);
_temp279;}); _temp278.f3=({ struct _tuple2 _temp280; _temp280.f1= e3; _temp280.f2=
Cyc_Absyn_skip_stmt( e3->loc); _temp280;}); _temp278.f4= s; _temp278;});
_temp277;}), loc);} struct Cyc_Absyn_Stmt* Cyc_Absyn_switch_stmt( struct Cyc_Absyn_Exp*
e, struct Cyc_List_List* scs, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_stmt((
void*)({ struct Cyc_Absyn_Switch_s_struct* _temp281=( struct Cyc_Absyn_Switch_s_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Switch_s_struct)); _temp281[ 0]=({ struct
Cyc_Absyn_Switch_s_struct _temp282; _temp282.tag= Cyc_Absyn_Switch_s; _temp282.f1=
e; _temp282.f2= scs; _temp282;}); _temp281;}), loc);} struct Cyc_Absyn_Stmt* Cyc_Absyn_seq_stmt(
struct Cyc_Absyn_Stmt* s1, struct Cyc_Absyn_Stmt* s2, struct Cyc_Position_Segment*
loc){ void* _temp283=( void*) s1->r; _LL285: if( _temp283 ==( void*) Cyc_Absyn_Skip_s){
goto _LL286;} else{ goto _LL287;} _LL287: goto _LL288; _LL286: return s2; _LL288:
return Cyc_Absyn_new_stmt(( void*)({ struct Cyc_Absyn_Seq_s_struct* _temp289=(
struct Cyc_Absyn_Seq_s_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Seq_s_struct));
_temp289[ 0]=({ struct Cyc_Absyn_Seq_s_struct _temp290; _temp290.tag= Cyc_Absyn_Seq_s;
_temp290.f1= s1; _temp290.f2= s2; _temp290;}); _temp289;}), loc); _LL284:;}
struct Cyc_Absyn_Stmt* Cyc_Absyn_fallthru_stmt( struct Cyc_List_List* el, struct
Cyc_Position_Segment* loc){ return Cyc_Absyn_new_stmt(( void*)({ struct Cyc_Absyn_Fallthru_s_struct*
_temp291=( struct Cyc_Absyn_Fallthru_s_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Fallthru_s_struct));
_temp291[ 0]=({ struct Cyc_Absyn_Fallthru_s_struct _temp292; _temp292.tag= Cyc_Absyn_Fallthru_s;
_temp292.f1= el; _temp292.f2= 0; _temp292;}); _temp291;}), loc);} struct Cyc_Absyn_Stmt*
Cyc_Absyn_decl_stmt( struct Cyc_Absyn_Decl* d, struct Cyc_Absyn_Stmt* s, struct
Cyc_Position_Segment* loc){ return Cyc_Absyn_new_stmt(( void*)({ struct Cyc_Absyn_Decl_s_struct*
_temp293=( struct Cyc_Absyn_Decl_s_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Decl_s_struct));
_temp293[ 0]=({ struct Cyc_Absyn_Decl_s_struct _temp294; _temp294.tag= Cyc_Absyn_Decl_s;
_temp294.f1= d; _temp294.f2= s; _temp294;}); _temp293;}), loc);} struct Cyc_Absyn_Stmt*
Cyc_Absyn_declare_stmt( struct _tuple0* x, void* t, struct Cyc_Absyn_Exp* init,
struct Cyc_Absyn_Stmt* s, struct Cyc_Position_Segment* loc){ struct Cyc_Absyn_Decl*
d= Cyc_Absyn_new_decl(( void*)({ struct Cyc_Absyn_Var_d_struct* _temp297=(
struct Cyc_Absyn_Var_d_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Var_d_struct));
_temp297[ 0]=({ struct Cyc_Absyn_Var_d_struct _temp298; _temp298.tag= Cyc_Absyn_Var_d;
_temp298.f1= Cyc_Absyn_new_vardecl( x, t, init); _temp298;}); _temp297;}), loc);
return Cyc_Absyn_new_stmt(( void*)({ struct Cyc_Absyn_Decl_s_struct* _temp295=(
struct Cyc_Absyn_Decl_s_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Decl_s_struct));
_temp295[ 0]=({ struct Cyc_Absyn_Decl_s_struct _temp296; _temp296.tag= Cyc_Absyn_Decl_s;
_temp296.f1= d; _temp296.f2= s; _temp296;}); _temp295;}), loc);} struct Cyc_Absyn_Stmt*
Cyc_Absyn_cut_stmt( struct Cyc_Absyn_Stmt* s, struct Cyc_Position_Segment* loc){
return Cyc_Absyn_new_stmt(( void*)({ struct Cyc_Absyn_Cut_s_struct* _temp299=(
struct Cyc_Absyn_Cut_s_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Cut_s_struct));
_temp299[ 0]=({ struct Cyc_Absyn_Cut_s_struct _temp300; _temp300.tag= Cyc_Absyn_Cut_s;
_temp300.f1= s; _temp300;}); _temp299;}), loc);} struct Cyc_Absyn_Stmt* Cyc_Absyn_splice_stmt(
struct Cyc_Absyn_Stmt* s, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_stmt((
void*)({ struct Cyc_Absyn_Splice_s_struct* _temp301=( struct Cyc_Absyn_Splice_s_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Splice_s_struct)); _temp301[ 0]=({ struct
Cyc_Absyn_Splice_s_struct _temp302; _temp302.tag= Cyc_Absyn_Splice_s; _temp302.f1=
s; _temp302;}); _temp301;}), loc);} struct Cyc_Absyn_Stmt* Cyc_Absyn_label_stmt(
struct _tagged_string* v, struct Cyc_Absyn_Stmt* s, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_stmt(( void*)({ struct Cyc_Absyn_Label_s_struct*
_temp303=( struct Cyc_Absyn_Label_s_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Label_s_struct));
_temp303[ 0]=({ struct Cyc_Absyn_Label_s_struct _temp304; _temp304.tag= Cyc_Absyn_Label_s;
_temp304.f1= v; _temp304.f2= s; _temp304;}); _temp303;}), loc);} struct Cyc_Absyn_Stmt*
Cyc_Absyn_do_stmt( struct Cyc_Absyn_Stmt* s, struct Cyc_Absyn_Exp* e, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_stmt(( void*)({ struct Cyc_Absyn_Do_s_struct*
_temp305=( struct Cyc_Absyn_Do_s_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Do_s_struct));
_temp305[ 0]=({ struct Cyc_Absyn_Do_s_struct _temp306; _temp306.tag= Cyc_Absyn_Do_s;
_temp306.f1= s; _temp306.f2=({ struct _tuple2 _temp307; _temp307.f1= e; _temp307.f2=
Cyc_Absyn_skip_stmt( e->loc); _temp307;}); _temp306;}); _temp305;}), loc);}
struct Cyc_Absyn_Stmt* Cyc_Absyn_trycatch_stmt( struct Cyc_Absyn_Stmt* s, struct
Cyc_List_List* scs, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_stmt((
void*)({ struct Cyc_Absyn_TryCatch_s_struct* _temp308=( struct Cyc_Absyn_TryCatch_s_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_TryCatch_s_struct)); _temp308[ 0]=({ struct
Cyc_Absyn_TryCatch_s_struct _temp309; _temp309.tag= Cyc_Absyn_TryCatch_s;
_temp309.f1= s; _temp309.f2= scs; _temp309;}); _temp308;}), loc);} struct Cyc_Absyn_Stmt*
Cyc_Absyn_goto_stmt( struct _tagged_string* lab, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_stmt(( void*)({ struct Cyc_Absyn_Goto_s_struct*
_temp310=( struct Cyc_Absyn_Goto_s_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Goto_s_struct));
_temp310[ 0]=({ struct Cyc_Absyn_Goto_s_struct _temp311; _temp311.tag= Cyc_Absyn_Goto_s;
_temp311.f1= lab; _temp311.f2= 0; _temp311;}); _temp310;}), loc);} struct Cyc_Absyn_Stmt*
Cyc_Absyn_assign_stmt( struct Cyc_Absyn_Exp* e1, struct Cyc_Absyn_Exp* e2,
struct Cyc_Position_Segment* loc){ return Cyc_Absyn_exp_stmt( Cyc_Absyn_assign_exp(
e1, e2, loc), loc);} struct Cyc_Absyn_Pat* Cyc_Absyn_new_pat( void* p, struct
Cyc_Position_Segment* s){ return({ struct Cyc_Absyn_Pat* _temp312=( struct Cyc_Absyn_Pat*)
GC_malloc( sizeof( struct Cyc_Absyn_Pat)); _temp312->r=( void*) p; _temp312->topt=
0; _temp312->loc= s; _temp312;});} struct Cyc_Absyn_Decl* Cyc_Absyn_new_decl(
void* r, struct Cyc_Position_Segment* loc){ return({ struct Cyc_Absyn_Decl*
_temp313=( struct Cyc_Absyn_Decl*) GC_malloc( sizeof( struct Cyc_Absyn_Decl));
_temp313->r=( void*) r; _temp313->loc= loc; _temp313;});} struct Cyc_Absyn_Decl*
Cyc_Absyn_let_decl( struct Cyc_Absyn_Pat* p, struct Cyc_Core_Opt* t_opt, struct
Cyc_Absyn_Exp* e, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_decl((
void*)({ struct Cyc_Absyn_Let_d_struct* _temp314=( struct Cyc_Absyn_Let_d_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Let_d_struct)); _temp314[ 0]=({ struct Cyc_Absyn_Let_d_struct
_temp315; _temp315.tag= Cyc_Absyn_Let_d; _temp315.f1= p; _temp315.f2= 0;
_temp315.f3= t_opt; _temp315.f4= e; _temp315.f5= 0; _temp315;}); _temp314;}),
loc);} struct Cyc_Absyn_Decl* Cyc_Absyn_letv_decl( struct Cyc_List_List* vds,
struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_decl(( void*)({ struct
Cyc_Absyn_Letv_d_struct* _temp316=( struct Cyc_Absyn_Letv_d_struct*) GC_malloc(
sizeof( struct Cyc_Absyn_Letv_d_struct)); _temp316[ 0]=({ struct Cyc_Absyn_Letv_d_struct
_temp317; _temp317.tag= Cyc_Absyn_Letv_d; _temp317.f1= vds; _temp317;});
_temp316;}), loc);} struct Cyc_Absyn_Vardecl* Cyc_Absyn_new_vardecl( struct
_tuple0* x, void* t, struct Cyc_Absyn_Exp* init){ return({ struct Cyc_Absyn_Vardecl*
_temp318=( struct Cyc_Absyn_Vardecl*) GC_malloc( sizeof( struct Cyc_Absyn_Vardecl));
_temp318->sc=( void*)(( void*) Cyc_Absyn_Public); _temp318->name= x; _temp318->tq=
Cyc_Absyn_empty_tqual(); _temp318->type=( void*) t; _temp318->initializer= init;
_temp318->rgn= 0; _temp318->attributes= 0; _temp318;});} struct Cyc_Absyn_Vardecl*
Cyc_Absyn_static_vardecl( struct _tuple0* x, void* t, struct Cyc_Absyn_Exp* init){
return({ struct Cyc_Absyn_Vardecl* _temp319=( struct Cyc_Absyn_Vardecl*)
GC_malloc( sizeof( struct Cyc_Absyn_Vardecl)); _temp319->sc=( void*)(( void*)
Cyc_Absyn_Static); _temp319->name= x; _temp319->tq= Cyc_Absyn_empty_tqual();
_temp319->type=( void*) t; _temp319->initializer= init; _temp319->rgn= 0;
_temp319->attributes= 0; _temp319;});} struct Cyc_Absyn_Decl* Cyc_Absyn_struct_decl(
void* s, struct Cyc_Core_Opt* n, struct Cyc_List_List* ts, struct Cyc_Core_Opt*
fs, struct Cyc_List_List* atts, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_decl((
void*)({ struct Cyc_Absyn_Struct_d_struct* _temp320=( struct Cyc_Absyn_Struct_d_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Struct_d_struct)); _temp320[ 0]=({ struct
Cyc_Absyn_Struct_d_struct _temp321; _temp321.tag= Cyc_Absyn_Struct_d; _temp321.f1=({
struct Cyc_Absyn_Structdecl* _temp322=( struct Cyc_Absyn_Structdecl*) GC_malloc(
sizeof( struct Cyc_Absyn_Structdecl)); _temp322->sc=( void*) s; _temp322->name=
n; _temp322->tvs= ts; _temp322->fields= fs; _temp322->attributes= atts; _temp322;});
_temp321;}); _temp320;}), loc);} struct Cyc_Absyn_Decl* Cyc_Absyn_union_decl(
void* s, struct Cyc_Core_Opt* n, struct Cyc_List_List* ts, struct Cyc_Core_Opt*
fs, struct Cyc_List_List* atts, struct Cyc_Position_Segment* loc){ return Cyc_Absyn_new_decl((
void*)({ struct Cyc_Absyn_Union_d_struct* _temp323=( struct Cyc_Absyn_Union_d_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_Union_d_struct)); _temp323[ 0]=({ struct Cyc_Absyn_Union_d_struct
_temp324; _temp324.tag= Cyc_Absyn_Union_d; _temp324.f1=({ struct Cyc_Absyn_Uniondecl*
_temp325=( struct Cyc_Absyn_Uniondecl*) GC_malloc( sizeof( struct Cyc_Absyn_Uniondecl));
_temp325->sc=( void*) s; _temp325->name= n; _temp325->tvs= ts; _temp325->fields=
fs; _temp325->attributes= atts; _temp325;}); _temp324;}); _temp323;}), loc);}
struct Cyc_Absyn_Decl* Cyc_Absyn_tunion_decl( void* s, struct _tuple0* n, struct
Cyc_List_List* ts, struct Cyc_Core_Opt* fs, int is_xtunion, struct Cyc_Position_Segment*
loc){ return Cyc_Absyn_new_decl(( void*)({ struct Cyc_Absyn_Tunion_d_struct*
_temp326=( struct Cyc_Absyn_Tunion_d_struct*) GC_malloc( sizeof( struct Cyc_Absyn_Tunion_d_struct));
_temp326[ 0]=({ struct Cyc_Absyn_Tunion_d_struct _temp327; _temp327.tag= Cyc_Absyn_Tunion_d;
_temp327.f1=({ struct Cyc_Absyn_Tuniondecl* _temp328=( struct Cyc_Absyn_Tuniondecl*)
GC_malloc( sizeof( struct Cyc_Absyn_Tuniondecl)); _temp328->sc=( void*) s;
_temp328->name= n; _temp328->tvs= ts; _temp328->fields= fs; _temp328->is_xtunion=
is_xtunion; _temp328;}); _temp327;}); _temp326;}), loc);} static struct _tuple1*
Cyc_Absyn_expand_arg( struct _tuple1* a){ return({ struct _tuple1* _temp329=(
struct _tuple1*) GC_malloc( sizeof( struct _tuple1)); _temp329->f1=(* a).f1;
_temp329->f2=(* a).f2; _temp329->f3= Cyc_Absyn_pointer_expand((* a).f3);
_temp329;});} void* Cyc_Absyn_function_typ( struct Cyc_List_List* tvs, struct
Cyc_Core_Opt* eff_typ, void* ret_typ, struct Cyc_List_List* args, int c_varargs,
struct Cyc_Absyn_VarargInfo* cyc_varargs, struct Cyc_List_List* atts){ return(
void*)({ struct Cyc_Absyn_FnType_struct* _temp330=( struct Cyc_Absyn_FnType_struct*)
GC_malloc( sizeof( struct Cyc_Absyn_FnType_struct)); _temp330[ 0]=({ struct Cyc_Absyn_FnType_struct
_temp331; _temp331.tag= Cyc_Absyn_FnType; _temp331.f1=({ struct Cyc_Absyn_FnInfo
_temp332; _temp332.tvars= tvs; _temp332.ret_typ=( void*) Cyc_Absyn_pointer_expand(
ret_typ); _temp332.effect= eff_typ; _temp332.args=(( struct Cyc_List_List*(*)(
struct _tuple1*(* f)( struct _tuple1*), struct Cyc_List_List* x)) Cyc_List_map)(
Cyc_Absyn_expand_arg, args); _temp332.c_varargs= c_varargs; _temp332.cyc_varargs=
cyc_varargs; _temp332.attributes= atts; _temp332;}); _temp331;}); _temp330;});}
void* Cyc_Absyn_pointer_expand( void* t){ void* _temp333= t; struct Cyc_Absyn_FnInfo
_temp339; _LL335: if(( unsigned int) _temp333 > 4u?*(( int*) _temp333) == Cyc_Absyn_FnType:
0){ _LL340: _temp339=(( struct Cyc_Absyn_FnType_struct*) _temp333)->f1; goto
_LL336;} else{ goto _LL337;} _LL337: goto _LL338; _LL336: return Cyc_Absyn_at_typ(
t,( void*) Cyc_Absyn_HeapRgn, Cyc_Absyn_empty_tqual()); _LL338: return t; _LL334:;}
int Cyc_Absyn_is_lvalue( struct Cyc_Absyn_Exp* e){ void* _temp341=( void*) e->r;
void* _temp365; struct Cyc_Absyn_Fndecl* _temp367; struct _tuple0* _temp369;
void* _temp371; struct Cyc_Absyn_Vardecl* _temp373; struct _tuple0* _temp375;
void* _temp377; struct Cyc_Absyn_Vardecl* _temp379; struct _tuple0* _temp381;
void* _temp383; struct _tuple0* _temp385; struct Cyc_Absyn_Exp* _temp387; struct
Cyc_Absyn_Exp* _temp389; struct _tagged_string* _temp391; struct Cyc_Absyn_Exp*
_temp393; struct _tagged_string* _temp395; struct Cyc_Absyn_Exp* _temp397;
struct Cyc_Absyn_Exp* _temp399; struct Cyc_List_List* _temp401; struct Cyc_Absyn_Exp*
_temp403; struct Cyc_Absyn_Exp* _temp405; _LL343: if(*(( int*) _temp341) == Cyc_Absyn_Var_e){
_LL370: _temp369=(( struct Cyc_Absyn_Var_e_struct*) _temp341)->f1; goto _LL366;
_LL366: _temp365=( void*)(( struct Cyc_Absyn_Var_e_struct*) _temp341)->f2; if((
unsigned int) _temp365 > 1u?*(( int*) _temp365) == Cyc_Absyn_Funname_b: 0){
_LL368: _temp367=(( struct Cyc_Absyn_Funname_b_struct*) _temp365)->f1; goto
_LL344;} else{ goto _LL345;}} else{ goto _LL345;} _LL345: if(*(( int*) _temp341)
== Cyc_Absyn_Var_e){ _LL376: _temp375=(( struct Cyc_Absyn_Var_e_struct*)
_temp341)->f1; goto _LL372; _LL372: _temp371=( void*)(( struct Cyc_Absyn_Var_e_struct*)
_temp341)->f2; if(( unsigned int) _temp371 > 1u?*(( int*) _temp371) == Cyc_Absyn_Global_b:
0){ _LL374: _temp373=(( struct Cyc_Absyn_Global_b_struct*) _temp371)->f1; goto
_LL346;} else{ goto _LL347;}} else{ goto _LL347;} _LL347: if(*(( int*) _temp341)
== Cyc_Absyn_Var_e){ _LL382: _temp381=(( struct Cyc_Absyn_Var_e_struct*)
_temp341)->f1; goto _LL378; _LL378: _temp377=( void*)(( struct Cyc_Absyn_Var_e_struct*)
_temp341)->f2; if(( unsigned int) _temp377 > 1u?*(( int*) _temp377) == Cyc_Absyn_Local_b:
0){ _LL380: _temp379=(( struct Cyc_Absyn_Local_b_struct*) _temp377)->f1; goto
_LL348;} else{ goto _LL349;}} else{ goto _LL349;} _LL349: if(*(( int*) _temp341)
== Cyc_Absyn_Var_e){ _LL386: _temp385=(( struct Cyc_Absyn_Var_e_struct*)
_temp341)->f1; goto _LL384; _LL384: _temp383=( void*)(( struct Cyc_Absyn_Var_e_struct*)
_temp341)->f2; goto _LL350;} else{ goto _LL351;} _LL351: if(*(( int*) _temp341)
== Cyc_Absyn_Subscript_e){ _LL390: _temp389=(( struct Cyc_Absyn_Subscript_e_struct*)
_temp341)->f1; goto _LL388; _LL388: _temp387=(( struct Cyc_Absyn_Subscript_e_struct*)
_temp341)->f2; goto _LL352;} else{ goto _LL353;} _LL353: if(*(( int*) _temp341)
== Cyc_Absyn_StructMember_e){ _LL394: _temp393=(( struct Cyc_Absyn_StructMember_e_struct*)
_temp341)->f1; goto _LL392; _LL392: _temp391=(( struct Cyc_Absyn_StructMember_e_struct*)
_temp341)->f2; goto _LL354;} else{ goto _LL355;} _LL355: if(*(( int*) _temp341)
== Cyc_Absyn_StructArrow_e){ _LL398: _temp397=(( struct Cyc_Absyn_StructArrow_e_struct*)
_temp341)->f1; goto _LL396; _LL396: _temp395=(( struct Cyc_Absyn_StructArrow_e_struct*)
_temp341)->f2; goto _LL356;} else{ goto _LL357;} _LL357: if(*(( int*) _temp341)
== Cyc_Absyn_Deref_e){ _LL400: _temp399=(( struct Cyc_Absyn_Deref_e_struct*)
_temp341)->f1; goto _LL358;} else{ goto _LL359;} _LL359: if(*(( int*) _temp341)
== Cyc_Absyn_Instantiate_e){ _LL404: _temp403=(( struct Cyc_Absyn_Instantiate_e_struct*)
_temp341)->f1; goto _LL402; _LL402: _temp401=(( struct Cyc_Absyn_Instantiate_e_struct*)
_temp341)->f2; goto _LL360;} else{ goto _LL361;} _LL361: if(*(( int*) _temp341)
== Cyc_Absyn_NoInstantiate_e){ _LL406: _temp405=(( struct Cyc_Absyn_NoInstantiate_e_struct*)
_temp341)->f1; goto _LL362;} else{ goto _LL363;} _LL363: goto _LL364; _LL344:
return 0; _LL346: _temp379= _temp373; goto _LL348; _LL348: { void* _temp407= Cyc_Tcutil_compress((
void*) _temp379->type); struct Cyc_Absyn_Exp* _temp413; struct Cyc_Absyn_Tqual
_temp415; void* _temp417; _LL409: if(( unsigned int) _temp407 > 4u?*(( int*)
_temp407) == Cyc_Absyn_ArrayType: 0){ _LL418: _temp417=( void*)(( struct Cyc_Absyn_ArrayType_struct*)
_temp407)->f1; goto _LL416; _LL416: _temp415=(( struct Cyc_Absyn_ArrayType_struct*)
_temp407)->f2; goto _LL414; _LL414: _temp413=(( struct Cyc_Absyn_ArrayType_struct*)
_temp407)->f3; goto _LL410;} else{ goto _LL411;} _LL411: goto _LL412; _LL410:
return 0; _LL412: return 1; _LL408:;} _LL350: return 1; _LL352: return 1; _LL354:
return Cyc_Absyn_is_lvalue( _temp393); _LL356: return 1; _LL358: return 1;
_LL360: return Cyc_Absyn_is_lvalue( _temp403); _LL362: return Cyc_Absyn_is_lvalue(
_temp405); _LL364: return 0; _LL342:;} struct Cyc_Absyn_Structfield* Cyc_Absyn_lookup_field(
struct Cyc_List_List* fields, struct _tagged_string* v){{ struct Cyc_List_List*
fs= fields; for( 0; fs != 0; fs=(( struct Cyc_List_List*) _check_null( fs))->tl){
struct Cyc_Absyn_Structfield* _temp419=( struct Cyc_Absyn_Structfield*)(( struct
Cyc_List_List*) _check_null( fs))->hd; goto _LL420; _LL420: if( Cyc_String_zstrptrcmp(
_temp419->name, v) == 0){ return( struct Cyc_Absyn_Structfield*) _temp419;}}}
return 0;} struct Cyc_Absyn_Structfield* Cyc_Absyn_lookup_struct_field( struct
Cyc_Absyn_Structdecl* sd, struct _tagged_string* v){ return sd->fields == 0? 0:
Cyc_Absyn_lookup_field(( struct Cyc_List_List*)(( struct Cyc_Core_Opt*)
_check_null( sd->fields))->v, v);} struct Cyc_Absyn_Structfield* Cyc_Absyn_lookup_union_field(
struct Cyc_Absyn_Uniondecl* ud, struct _tagged_string* v){ return ud->fields ==
0? 0: Cyc_Absyn_lookup_field(( struct Cyc_List_List*)(( struct Cyc_Core_Opt*)
_check_null( ud->fields))->v, v);} struct _tuple3* Cyc_Absyn_lookup_tuple_field(
struct Cyc_List_List* ts, int i){ for( 0; i != 0; -- i){ if( ts == 0){ return 0;}
ts=(( struct Cyc_List_List*) _check_null( ts))->tl;} if( ts == 0){ return 0;}
return( struct _tuple3*)(( struct _tuple3*)(( struct Cyc_List_List*) _check_null(
ts))->hd);} struct _tagged_string Cyc_Absyn_attribute2string( void* a){ void*
_temp421= a; int _temp461; int _temp463; struct _tagged_string _temp465; _LL423:
if(( unsigned int) _temp421 > 16u?*(( int*) _temp421) == Cyc_Absyn_Regparm_att:
0){ _LL462: _temp461=(( struct Cyc_Absyn_Regparm_att_struct*) _temp421)->f1;
goto _LL424;} else{ goto _LL425;} _LL425: if( _temp421 ==( void*) Cyc_Absyn_Stdcall_att){
goto _LL426;} else{ goto _LL427;} _LL427: if( _temp421 ==( void*) Cyc_Absyn_Cdecl_att){
goto _LL428;} else{ goto _LL429;} _LL429: if( _temp421 ==( void*) Cyc_Absyn_Fastcall_att){
goto _LL430;} else{ goto _LL431;} _LL431: if( _temp421 ==( void*) Cyc_Absyn_Noreturn_att){
goto _LL432;} else{ goto _LL433;} _LL433: if( _temp421 ==( void*) Cyc_Absyn_Const_att){
goto _LL434;} else{ goto _LL435;} _LL435: if(( unsigned int) _temp421 > 16u?*((
int*) _temp421) == Cyc_Absyn_Aligned_att: 0){ _LL464: _temp463=(( struct Cyc_Absyn_Aligned_att_struct*)
_temp421)->f1; goto _LL436;} else{ goto _LL437;} _LL437: if( _temp421 ==( void*)
Cyc_Absyn_Packed_att){ goto _LL438;} else{ goto _LL439;} _LL439: if((
unsigned int) _temp421 > 16u?*(( int*) _temp421) == Cyc_Absyn_Section_att: 0){
_LL466: _temp465=(( struct Cyc_Absyn_Section_att_struct*) _temp421)->f1; goto
_LL440;} else{ goto _LL441;} _LL441: if( _temp421 ==( void*) Cyc_Absyn_Nocommon_att){
goto _LL442;} else{ goto _LL443;} _LL443: if( _temp421 ==( void*) Cyc_Absyn_Shared_att){
goto _LL444;} else{ goto _LL445;} _LL445: if( _temp421 ==( void*) Cyc_Absyn_Unused_att){
goto _LL446;} else{ goto _LL447;} _LL447: if( _temp421 ==( void*) Cyc_Absyn_Weak_att){
goto _LL448;} else{ goto _LL449;} _LL449: if( _temp421 ==( void*) Cyc_Absyn_Dllimport_att){
goto _LL450;} else{ goto _LL451;} _LL451: if( _temp421 ==( void*) Cyc_Absyn_Dllexport_att){
goto _LL452;} else{ goto _LL453;} _LL453: if( _temp421 ==( void*) Cyc_Absyn_No_instrument_function_att){
goto _LL454;} else{ goto _LL455;} _LL455: if( _temp421 ==( void*) Cyc_Absyn_Constructor_att){
goto _LL456;} else{ goto _LL457;} _LL457: if( _temp421 ==( void*) Cyc_Absyn_Destructor_att){
goto _LL458;} else{ goto _LL459;} _LL459: if( _temp421 ==( void*) Cyc_Absyn_No_check_memory_usage_att){
goto _LL460;} else{ goto _LL422;} _LL424: return( struct _tagged_string) xprintf("regparm(%d)",
_temp461); _LL426: return({ unsigned char* _temp467=( unsigned char*)"stdcall";
struct _tagged_string _temp468; _temp468.curr= _temp467; _temp468.base= _temp467;
_temp468.last_plus_one= _temp467 + 8; _temp468;}); _LL428: return({
unsigned char* _temp469=( unsigned char*)"cdecl"; struct _tagged_string _temp470;
_temp470.curr= _temp469; _temp470.base= _temp469; _temp470.last_plus_one=
_temp469 + 6; _temp470;}); _LL430: return({ unsigned char* _temp471=(
unsigned char*)"fastcall"; struct _tagged_string _temp472; _temp472.curr=
_temp471; _temp472.base= _temp471; _temp472.last_plus_one= _temp471 + 9;
_temp472;}); _LL432: return({ unsigned char* _temp473=( unsigned char*)"noreturn";
struct _tagged_string _temp474; _temp474.curr= _temp473; _temp474.base= _temp473;
_temp474.last_plus_one= _temp473 + 9; _temp474;}); _LL434: return({
unsigned char* _temp475=( unsigned char*)"const"; struct _tagged_string _temp476;
_temp476.curr= _temp475; _temp476.base= _temp475; _temp476.last_plus_one=
_temp475 + 6; _temp476;}); _LL436: if( _temp463 == - 1){ return({ unsigned char*
_temp477=( unsigned char*)"aligned"; struct _tagged_string _temp478; _temp478.curr=
_temp477; _temp478.base= _temp477; _temp478.last_plus_one= _temp477 + 8;
_temp478;});} else{ return( struct _tagged_string) xprintf("aligned(%d)",
_temp463);} _LL438: return({ unsigned char* _temp479=( unsigned char*)"packed";
struct _tagged_string _temp480; _temp480.curr= _temp479; _temp480.base= _temp479;
_temp480.last_plus_one= _temp479 + 7; _temp480;}); _LL440: return( struct
_tagged_string)({ struct _tagged_string _temp481= _temp465; xprintf("section(\"%.*s\")",
_temp481.last_plus_one - _temp481.curr, _temp481.curr);}); _LL442: return({
unsigned char* _temp482=( unsigned char*)"nocommon"; struct _tagged_string
_temp483; _temp483.curr= _temp482; _temp483.base= _temp482; _temp483.last_plus_one=
_temp482 + 9; _temp483;}); _LL444: return({ unsigned char* _temp484=(
unsigned char*)"shared"; struct _tagged_string _temp485; _temp485.curr= _temp484;
_temp485.base= _temp484; _temp485.last_plus_one= _temp484 + 7; _temp485;});
_LL446: return({ unsigned char* _temp486=( unsigned char*)"unused"; struct
_tagged_string _temp487; _temp487.curr= _temp486; _temp487.base= _temp486;
_temp487.last_plus_one= _temp486 + 7; _temp487;}); _LL448: return({
unsigned char* _temp488=( unsigned char*)"weak"; struct _tagged_string _temp489;
_temp489.curr= _temp488; _temp489.base= _temp488; _temp489.last_plus_one=
_temp488 + 5; _temp489;}); _LL450: return({ unsigned char* _temp490=(
unsigned char*)"dllimport"; struct _tagged_string _temp491; _temp491.curr=
_temp490; _temp491.base= _temp490; _temp491.last_plus_one= _temp490 + 10;
_temp491;}); _LL452: return({ unsigned char* _temp492=( unsigned char*)"dllexport";
struct _tagged_string _temp493; _temp493.curr= _temp492; _temp493.base= _temp492;
_temp493.last_plus_one= _temp492 + 10; _temp493;}); _LL454: return({
unsigned char* _temp494=( unsigned char*)"no_instrument_function"; struct
_tagged_string _temp495; _temp495.curr= _temp494; _temp495.base= _temp494;
_temp495.last_plus_one= _temp494 + 23; _temp495;}); _LL456: return({
unsigned char* _temp496=( unsigned char*)"constructor"; struct _tagged_string
_temp497; _temp497.curr= _temp496; _temp497.base= _temp496; _temp497.last_plus_one=
_temp496 + 12; _temp497;}); _LL458: return({ unsigned char* _temp498=(
unsigned char*)"destructor"; struct _tagged_string _temp499; _temp499.curr=
_temp498; _temp499.base= _temp498; _temp499.last_plus_one= _temp498 + 11;
_temp499;}); _LL460: return({ unsigned char* _temp500=( unsigned char*)"no_check_memory_usage";
struct _tagged_string _temp501; _temp501.curr= _temp500; _temp501.base= _temp500;
_temp501.last_plus_one= _temp500 + 22; _temp501;}); _LL422:;} int Cyc_Absyn_fntype_att(
void* a){ void* _temp502= a; int _temp516; _LL504: if(( unsigned int) _temp502 >
16u?*(( int*) _temp502) == Cyc_Absyn_Regparm_att: 0){ _LL517: _temp516=(( struct
Cyc_Absyn_Regparm_att_struct*) _temp502)->f1; goto _LL505;} else{ goto _LL506;}
_LL506: if( _temp502 ==( void*) Cyc_Absyn_Stdcall_att){ goto _LL507;} else{ goto
_LL508;} _LL508: if( _temp502 ==( void*) Cyc_Absyn_Cdecl_att){ goto _LL509;}
else{ goto _LL510;} _LL510: if( _temp502 ==( void*) Cyc_Absyn_Noreturn_att){
goto _LL511;} else{ goto _LL512;} _LL512: if( _temp502 ==( void*) Cyc_Absyn_Const_att){
goto _LL513;} else{ goto _LL514;} _LL514: goto _LL515; _LL505: goto _LL507;
_LL507: goto _LL509; _LL509: goto _LL511; _LL511: goto _LL513; _LL513: return 1;
_LL515: return 0; _LL503:;}