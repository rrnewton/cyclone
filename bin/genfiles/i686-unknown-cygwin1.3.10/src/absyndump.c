// This is a C header file to be used by the output of the Cyclone
// to C translator.  The corresponding definitions are in file lib/runtime_cyc.c
#ifndef _CYC_INCLUDE_H_
#define _CYC_INCLUDE_H_

#include <setjmp.h>

#ifdef NO_CYC_PREFIX
#define ADD_PREFIX(x) x
#else
#define ADD_PREFIX(x) Cyc_##x
#endif

#ifndef offsetof
// should be size_t, but int is fine.
#define offsetof(t,n) ((int)(&(((t *)0)->n)))
#endif

//// Tagged arrays
struct _tagged_arr { 
  unsigned char *curr; 
  unsigned char *base; 
  unsigned char *last_plus_one; 
};

//// Discriminated Unions
struct _xtunion_struct { char *tag; };

// Need one of these per thread (we don't have threads)
// The runtime maintains a stack that contains either _handler_cons
// structs or _RegionHandle structs.  The tag is 0 for a handler_cons
// and 1 for a region handle.  
struct _RuntimeStack {
  int tag; // 0 for an exception handler, 1 for a region handle
  struct _RuntimeStack *next;
};

//// Regions
struct _RegionPage {
#ifdef CYC_REGION_PROFILE
  unsigned total_bytes;
  unsigned free_bytes;
#endif
  struct _RegionPage *next;
  char data[0];
};

struct _RegionHandle {
  struct _RuntimeStack s;
  struct _RegionPage *curr;
  char               *offset;
  char               *last_plus_one;
#ifdef CYC_REGION_PROFILE
  const char         *name;
#endif
};

extern struct _RegionHandle _new_region(const char *);
extern void * _region_malloc(struct _RegionHandle *, unsigned);
extern void * _region_calloc(struct _RegionHandle *, unsigned t, unsigned n);
extern void   _free_region(struct _RegionHandle *);
extern void   _reset_region(struct _RegionHandle *);

//// Exceptions 
struct _handler_cons {
  struct _RuntimeStack s;
  jmp_buf handler;
};
extern void _push_handler(struct _handler_cons *);
extern void _push_region(struct _RegionHandle *);
extern void _npop_handler(int);
extern void _pop_handler();
extern void _pop_region();

#ifndef _throw
extern int _throw_null();
extern int _throw_arraybounds();
extern int _throw_badalloc();
extern int _throw(void* e);
#endif

extern struct _xtunion_struct *_exn_thrown;

//// Built-in Exceptions
extern struct _xtunion_struct ADD_PREFIX(Null_Exception_struct);
extern struct _xtunion_struct * ADD_PREFIX(Null_Exception);
extern struct _xtunion_struct ADD_PREFIX(Array_bounds_struct);
extern struct _xtunion_struct * ADD_PREFIX(Array_bounds);
extern struct _xtunion_struct ADD_PREFIX(Match_Exception_struct);
extern struct _xtunion_struct * ADD_PREFIX(Match_Exception);
extern struct _xtunion_struct ADD_PREFIX(Bad_alloc_struct);
extern struct _xtunion_struct * ADD_PREFIX(Bad_alloc);

//// Built-in Run-time Checks and company
#ifdef __APPLE__
#define _INLINE_FUNCTIONS
#endif

#ifdef NO_CYC_NULL_CHECKS
#define _check_null(ptr) (ptr)
#else
#ifdef _INLINE_FUNCTIONS
static inline void *
_check_null(void *ptr) {
  void*_check_null_temp = (void*)(ptr);
  if (!_check_null_temp) _throw_null();
  return _check_null_temp;
}
#else
#define _check_null(ptr) \
  ({ void*_check_null_temp = (void*)(ptr); \
     if (!_check_null_temp) _throw_null(); \
     _check_null_temp; })
#endif
#endif

#ifdef NO_CYC_BOUNDS_CHECKS
#define _check_known_subscript_null(ptr,bound,elt_sz,index) ({ \
  ((char *)ptr) + (elt_sz)*(index); })
#else
#ifdef _INLINE_FUNCTIONS
static inline char *
_check_known_subscript_null(void *ptr, unsigned bound, unsigned elt_sz, unsigned index) {
  void*_cks_ptr = (void*)(ptr);
  unsigned _cks_bound = (bound);
  unsigned _cks_elt_sz = (elt_sz);
  unsigned _cks_index = (index);
  if (!_cks_ptr) _throw_null();
  if (_cks_index >= _cks_bound) _throw_arraybounds();
  return ((char *)_cks_ptr) + _cks_elt_sz*_cks_index;
}
#else
#define _check_known_subscript_null(ptr,bound,elt_sz,index) ({ \
  void*_cks_ptr = (void*)(ptr); \
  unsigned _cks_bound = (bound); \
  unsigned _cks_elt_sz = (elt_sz); \
  unsigned _cks_index = (index); \
  if (!_cks_ptr) _throw_null(); \
  if (_cks_index >= _cks_bound) _throw_arraybounds(); \
  ((char *)_cks_ptr) + _cks_elt_sz*_cks_index; })
#endif
#endif

#ifdef NO_CYC_BOUNDS_CHECKS
#define _check_known_subscript_notnull(bound,index) (index)
#else
#ifdef _INLINE_FUNCTIONS
static inline unsigned
_check_known_subscript_notnull(unsigned bound,unsigned index) { 
  unsigned _cksnn_bound = (bound); 
  unsigned _cksnn_index = (index); 
  if (_cksnn_index >= _cksnn_bound) _throw_arraybounds(); 
  return _cksnn_index;
}
#else
#define _check_known_subscript_notnull(bound,index) ({ \
  unsigned _cksnn_bound = (bound); \
  unsigned _cksnn_index = (index); \
  if (_cksnn_index >= _cksnn_bound) _throw_arraybounds(); \
  _cksnn_index; })
#endif
#endif

#ifdef NO_CYC_BOUNDS_CHECKS
#ifdef _INLINE_FUNCTIONS
static inline unsigned char *
_check_unknown_subscript(struct _tagged_arr arr,unsigned elt_sz,unsigned index) {
  struct _tagged_arr _cus_arr = (arr);
  unsigned _cus_elt_sz = (elt_sz);
  unsigned _cus_index = (index);
  unsigned char *_cus_ans = _cus_arr.curr + _cus_elt_sz * _cus_index;
  return _cus_ans;
}
#else
#define _check_unknown_subscript(arr,elt_sz,index) ({ \
  struct _tagged_arr _cus_arr = (arr); \
  unsigned _cus_elt_sz = (elt_sz); \
  unsigned _cus_index = (index); \
  unsigned char *_cus_ans = _cus_arr.curr + _cus_elt_sz * _cus_index; \
  _cus_ans; })
#endif
#else
#ifdef _INLINE_FUNCTIONS
static inline unsigned char *
_check_unknown_subscript(struct _tagged_arr arr,unsigned elt_sz,unsigned index) {
  struct _tagged_arr _cus_arr = (arr);
  unsigned _cus_elt_sz = (elt_sz);
  unsigned _cus_index = (index);
  unsigned char *_cus_ans = _cus_arr.curr + _cus_elt_sz * _cus_index;
  if (!_cus_arr.base) _throw_null();
  if (_cus_ans < _cus_arr.base || _cus_ans >= _cus_arr.last_plus_one)
    _throw_arraybounds();
  return _cus_ans;
}
#else
#define _check_unknown_subscript(arr,elt_sz,index) ({ \
  struct _tagged_arr _cus_arr = (arr); \
  unsigned _cus_elt_sz = (elt_sz); \
  unsigned _cus_index = (index); \
  unsigned char *_cus_ans = _cus_arr.curr + _cus_elt_sz * _cus_index; \
  if (!_cus_arr.base) _throw_null(); \
  if (_cus_ans < _cus_arr.base || _cus_ans >= _cus_arr.last_plus_one) \
    _throw_arraybounds(); \
  _cus_ans; })
#endif
#endif

#ifdef _INLINE_FUNCTIONS
static inline struct _tagged_arr
_tag_arr(const void *tcurr,unsigned elt_sz,unsigned num_elts) {
  struct _tagged_arr _tag_arr_ans;
  _tag_arr_ans.base = _tag_arr_ans.curr = (void*)(tcurr);
  _tag_arr_ans.last_plus_one = _tag_arr_ans.base + (elt_sz) * (num_elts);
  return _tag_arr_ans;
}
#else
#define _tag_arr(tcurr,elt_sz,num_elts) ({ \
  struct _tagged_arr _tag_arr_ans; \
  _tag_arr_ans.base = _tag_arr_ans.curr = (void*)(tcurr); \
  _tag_arr_ans.last_plus_one = _tag_arr_ans.base + (elt_sz) * (num_elts); \
  _tag_arr_ans; })
#endif

#ifdef _INLINE_FUNCTIONS
static inline struct _tagged_arr *
_init_tag_arr(struct _tagged_arr *arr_ptr,
              void *arr, unsigned elt_sz, unsigned num_elts) {
  struct _tagged_arr *_itarr_ptr = (arr_ptr);
  void* _itarr = (arr);
  _itarr_ptr->base = _itarr_ptr->curr = _itarr;
  _itarr_ptr->last_plus_one = ((char *)_itarr) + (elt_sz) * (num_elts);
  return _itarr_ptr;
}
#else
#define _init_tag_arr(arr_ptr,arr,elt_sz,num_elts) ({ \
  struct _tagged_arr *_itarr_ptr = (arr_ptr); \
  void* _itarr = (arr); \
  _itarr_ptr->base = _itarr_ptr->curr = _itarr; \
  _itarr_ptr->last_plus_one = ((char *)_itarr) + (elt_sz) * (num_elts); \
  _itarr_ptr; })
#endif

#ifdef NO_CYC_BOUNDS_CHECKS
#define _untag_arr(arr,elt_sz,num_elts) ((arr).curr)
#else
#ifdef _INLINE_FUNCTIONS
static inline unsigned char *
_untag_arr(struct _tagged_arr arr, unsigned elt_sz,unsigned num_elts) {
  struct _tagged_arr _arr = (arr);
  unsigned char *_curr = _arr.curr;
  if (_curr < _arr.base || _curr + (elt_sz) * (num_elts) > _arr.last_plus_one)
    _throw_arraybounds();
  return _curr;
}
#else
#define _untag_arr(arr,elt_sz,num_elts) ({ \
  struct _tagged_arr _arr = (arr); \
  unsigned char *_curr = _arr.curr; \
  if (_curr < _arr.base || _curr + (elt_sz) * (num_elts) > _arr.last_plus_one)\
    _throw_arraybounds(); \
  _curr; })
#endif
#endif

#ifdef _INLINE_FUNCTIONS
static inline unsigned
_get_arr_size(struct _tagged_arr arr,unsigned elt_sz) {
  struct _tagged_arr _get_arr_size_temp = (arr);
  unsigned char *_get_arr_size_curr=_get_arr_size_temp.curr;
  unsigned char *_get_arr_size_last=_get_arr_size_temp.last_plus_one;
  return (_get_arr_size_curr < _get_arr_size_temp.base ||
          _get_arr_size_curr >= _get_arr_size_last) ? 0 :
    ((_get_arr_size_last - _get_arr_size_curr) / (elt_sz));
}
#else
#define _get_arr_size(arr,elt_sz) \
  ({struct _tagged_arr _get_arr_size_temp = (arr); \
    unsigned char *_get_arr_size_curr=_get_arr_size_temp.curr; \
    unsigned char *_get_arr_size_last=_get_arr_size_temp.last_plus_one; \
    (_get_arr_size_curr < _get_arr_size_temp.base || \
     _get_arr_size_curr >= _get_arr_size_last) ? 0 : \
    ((_get_arr_size_last - _get_arr_size_curr) / (elt_sz));})
#endif

#ifdef _INLINE_FUNCTIONS
static inline struct _tagged_arr
_tagged_arr_plus(struct _tagged_arr arr,unsigned elt_sz,int change) {
  struct _tagged_arr _ans = (arr);
  _ans.curr += ((int)(elt_sz))*(change);
  return _ans;
}
#else
#define _tagged_arr_plus(arr,elt_sz,change) ({ \
  struct _tagged_arr _ans = (arr); \
  _ans.curr += ((int)(elt_sz))*(change); \
  _ans; })
#endif

#ifdef _INLINE_FUNCTIONS
static inline struct _tagged_arr
_tagged_arr_inplace_plus(struct _tagged_arr *arr_ptr,unsigned elt_sz,int change) {
  struct _tagged_arr * _arr_ptr = (arr_ptr);
  _arr_ptr->curr += ((int)(elt_sz))*(change);
  return *_arr_ptr;
}
#else
#define _tagged_arr_inplace_plus(arr_ptr,elt_sz,change) ({ \
  struct _tagged_arr * _arr_ptr = (arr_ptr); \
  _arr_ptr->curr += ((int)(elt_sz))*(change); \
  *_arr_ptr; })
#endif

#ifdef _INLINE_FUNCTIONS
static inline struct _tagged_arr
_tagged_arr_inplace_plus_post(struct _tagged_arr *arr_ptr,unsigned elt_sz,int change) {
  struct _tagged_arr * _arr_ptr = (arr_ptr);
  struct _tagged_arr _ans = *_arr_ptr;
  _arr_ptr->curr += ((int)(elt_sz))*(change);
  return _ans;
}
#else
#define _tagged_arr_inplace_plus_post(arr_ptr,elt_sz,change) ({ \
  struct _tagged_arr * _arr_ptr = (arr_ptr); \
  struct _tagged_arr _ans = *_arr_ptr; \
  _arr_ptr->curr += ((int)(elt_sz))*(change); \
  _ans; })
#endif

// Decrease the upper bound on a fat pointer by numelts where sz is
// the size of the pointer's type.  Note that this can't be a macro
// if we're to get initializers right.
static struct _tagged_arr _tagged_ptr_decrease_size(struct _tagged_arr x,
                                                    unsigned int sz,
                                                    unsigned int numelts) {
  x.last_plus_one -= sz * numelts; 
  return x; 
}

// Add i to zero-terminated pointer x.  Checks for x being null and
// ensures that x[0..i-1] are not 0.
#ifdef NO_CYC_BOUNDS_CHECK
#define _zero_arr_plus(orig_x,orig_sz,orig_i) ((orig_x)+(orig_i))
#else
#define _zero_arr_plus(orig_x,orig_sz,orig_i) ({ \
  typedef _czs_tx = (*orig_x); \
  _czs_tx *_czs_x = (_czs_tx *)(orig_x); \
  unsigned int _czs_sz = (orig_sz); \
  int _czs_i = (orig_i); \
  unsigned int _czs_temp; \
  if ((_czs_x) == 0) _throw_null(); \
  if (_czs_i < 0) _throw_arraybounds(); \
  for (_czs_temp=_czs_sz; _czs_temp < _czs_i; _czs_temp++) \
    if (_czs_x[_czs_temp] == 0) _throw_arraybounds(); \
  _czs_x+_czs_i; })
#endif

// Calculates the number of elements in a zero-terminated, thin array.
// If non-null, the array is guaranteed to have orig_offset elements.
#define _get_zero_arr_size(orig_x,orig_offset) ({ \
  typedef _gres_tx = (*orig_x); \
  _gres_tx *_gres_x = (_gres_tx *)(orig_x); \
  unsigned int _gres_offset = (orig_offset); \
  unsigned int _gres = 0; \
  if (_gres_x != 0) { \
     _gres = _gres_offset; \
     _gres_x += _gres_offset - 1; \
     while (*_gres_x != 0) { _gres_x++; _gres++; } \
  } _gres; })

// Does in-place addition of a zero-terminated pointer (x += e and ++x).  
// Note that this expands to call _zero_arr_plus.
#define _zero_arr_inplace_plus(x,orig_i) ({ \
  typedef _zap_tx = (*x); \
  _zap_tx **_zap_x = &((_zap_tx*)x); \
  *_zap_x = _zero_arr_plus(*_zap_x,1,(orig_i)); })

// Does in-place increment of a zero-terminated pointer (e.g., x++).
// Note that this expands to call _zero_arr_plus.
#define _zero_arr_inplace_plus_post(x,orig_i) ({ \
  typedef _zap_tx = (*x); \
  _zap_tx **_zap_x = &((_zap_tx*)x); \
  _zap_tx *_zap_res = *_zap_x; \
  *_zap_x = _zero_arr_plus(_zap_res,1,(orig_i)); \
  _zap_res; })
  
//// Allocation
extern void* GC_malloc(int);
extern void* GC_malloc_atomic(int);
extern void* GC_calloc(unsigned,unsigned);
extern void* GC_calloc_atomic(unsigned,unsigned);

static inline void* _cycalloc(int n) {
  void * ans = (void *)GC_malloc(n);
  if(!ans)
    _throw_badalloc();
  return ans;
}
static inline void* _cycalloc_atomic(int n) {
  void * ans = (void *)GC_malloc_atomic(n);
  if(!ans)
    _throw_badalloc();
  return ans;
}
static inline void* _cyccalloc(unsigned n, unsigned s) {
  void* ans = (void*)GC_calloc(n,s);
  if (!ans)
    _throw_badalloc();
  return ans;
}
static inline void* _cyccalloc_atomic(unsigned n, unsigned s) {
  void* ans = (void*)GC_calloc_atomic(n,s);
  if (!ans)
    _throw_badalloc();
  return ans;
}
#define MAX_MALLOC_SIZE (1 << 28)
static inline unsigned int _check_times(unsigned x, unsigned y) {
  unsigned long long whole_ans = 
    ((unsigned long long)x)*((unsigned long long)y);
  unsigned word_ans = (unsigned)whole_ans;
  if(word_ans < whole_ans || word_ans > MAX_MALLOC_SIZE)
    _throw_badalloc();
  return word_ans;
}

#if defined(CYC_REGION_PROFILE) 
extern void* _profile_GC_malloc(int,char *file,int lineno);
extern void* _profile_GC_malloc_atomic(int,char *file,int lineno);
extern void* _profile_region_malloc(struct _RegionHandle *, unsigned,
                                     char *file,int lineno);
extern struct _RegionHandle _profile_new_region(const char *rgn_name,
						char *file,int lineno);
extern void _profile_free_region(struct _RegionHandle *,
				 char *file,int lineno);
#  if !defined(RUNTIME_CYC)
#define _new_region(n) _profile_new_region(n,__FILE__ ":" __FUNCTION__,__LINE__)
#define _free_region(r) _profile_free_region(r,__FILE__ ":" __FUNCTION__,__LINE__)
#define _region_malloc(rh,n) _profile_region_malloc(rh,n,__FILE__ ":" __FUNCTION__,__LINE__)
#  endif
#define _cycalloc(n) _profile_GC_malloc(n,__FILE__ ":" __FUNCTION__,__LINE__)
#define _cycalloc_atomic(n) _profile_GC_malloc_atomic(n,__FILE__ ":" __FUNCTION__,__LINE__)
#endif
#endif
 struct Cyc_Core_Opt{void*v;};extern char Cyc_Core_Invalid_argument[21];struct Cyc_Core_Invalid_argument_struct{
char*tag;struct _tagged_arr f1;};extern char Cyc_Core_Failure[12];struct Cyc_Core_Failure_struct{
char*tag;struct _tagged_arr f1;};extern char Cyc_Core_Impossible[15];struct Cyc_Core_Impossible_struct{
char*tag;struct _tagged_arr f1;};extern char Cyc_Core_Not_found[14];extern char Cyc_Core_Unreachable[
16];struct Cyc_Core_Unreachable_struct{char*tag;struct _tagged_arr f1;};struct Cyc___cycFILE;
extern struct Cyc___cycFILE*Cyc_stdout;struct Cyc_Cstdio___abstractFILE;struct Cyc_String_pa_struct{
int tag;struct _tagged_arr f1;};struct Cyc_Int_pa_struct{int tag;unsigned int f1;};
struct Cyc_Double_pa_struct{int tag;double f1;};struct Cyc_LongDouble_pa_struct{int
tag;long double f1;};struct Cyc_ShortPtr_pa_struct{int tag;short*f1;};struct Cyc_IntPtr_pa_struct{
int tag;unsigned int*f1;};struct _tagged_arr Cyc_aprintf(struct _tagged_arr,struct
_tagged_arr);int Cyc_fprintf(struct Cyc___cycFILE*,struct _tagged_arr,struct
_tagged_arr);int Cyc_fputc(int,struct Cyc___cycFILE*);struct Cyc_ShortPtr_sa_struct{
int tag;short*f1;};struct Cyc_UShortPtr_sa_struct{int tag;unsigned short*f1;};
struct Cyc_IntPtr_sa_struct{int tag;int*f1;};struct Cyc_UIntPtr_sa_struct{int tag;
unsigned int*f1;};struct Cyc_StringPtr_sa_struct{int tag;struct _tagged_arr f1;};
struct Cyc_DoublePtr_sa_struct{int tag;double*f1;};struct Cyc_FloatPtr_sa_struct{
int tag;float*f1;};struct Cyc_CharPtr_sa_struct{int tag;struct _tagged_arr f1;};
extern char Cyc_FileCloseError[19];extern char Cyc_FileOpenError[18];struct Cyc_FileOpenError_struct{
char*tag;struct _tagged_arr f1;};int Cyc_file_string_write(struct Cyc___cycFILE*,
struct _tagged_arr src,int src_offset,int max_count);struct Cyc_List_List{void*hd;
struct Cyc_List_List*tl;};int Cyc_List_length(struct Cyc_List_List*x);struct Cyc_List_List*
Cyc_List_map(void*(*f)(void*),struct Cyc_List_List*x);extern char Cyc_List_List_mismatch[
18];struct Cyc_List_List*Cyc_List_imp_rev(struct Cyc_List_List*x);struct Cyc_List_List*
Cyc_List_imp_append(struct Cyc_List_List*x,struct Cyc_List_List*y);extern char Cyc_List_Nth[
8];int Cyc_List_exists(int(*pred)(void*),struct Cyc_List_List*x);unsigned int Cyc_strlen(
struct _tagged_arr s);struct Cyc_Lineno_Pos{struct _tagged_arr logical_file;struct
_tagged_arr line;int line_no;int col;};extern char Cyc_Position_Exit[9];struct Cyc_Position_Segment;
struct Cyc_Position_Error{struct _tagged_arr source;struct Cyc_Position_Segment*seg;
void*kind;struct _tagged_arr desc;};extern char Cyc_Position_Nocontext[14];struct
_tagged_arr Cyc_Position_get_line_directive(struct Cyc_Position_Segment*loc);
struct Cyc_Absyn_Rel_n_struct{int tag;struct Cyc_List_List*f1;};struct Cyc_Absyn_Abs_n_struct{
int tag;struct Cyc_List_List*f1;};struct _tuple0{void*f1;struct _tagged_arr*f2;};
struct Cyc_Absyn_Conref;struct Cyc_Absyn_Tqual{int print_const: 1;int q_volatile: 1;
int q_restrict: 1;int real_const: 1;};struct Cyc_Absyn_Conref{void*v;};struct Cyc_Absyn_Eq_constr_struct{
int tag;void*f1;};struct Cyc_Absyn_Forward_constr_struct{int tag;struct Cyc_Absyn_Conref*
f1;};struct Cyc_Absyn_Eq_kb_struct{int tag;void*f1;};struct Cyc_Absyn_Unknown_kb_struct{
int tag;struct Cyc_Core_Opt*f1;};struct Cyc_Absyn_Less_kb_struct{int tag;struct Cyc_Core_Opt*
f1;void*f2;};struct Cyc_Absyn_Tvar{struct _tagged_arr*name;int*identity;void*kind;
};struct Cyc_Absyn_Upper_b_struct{int tag;struct Cyc_Absyn_Exp*f1;};struct Cyc_Absyn_AbsUpper_b_struct{
int tag;void*f1;};struct Cyc_Absyn_PtrAtts{void*rgn;struct Cyc_Absyn_Conref*
nullable;struct Cyc_Absyn_Conref*bounds;struct Cyc_Absyn_Conref*zero_term;};struct
Cyc_Absyn_PtrInfo{void*elt_typ;struct Cyc_Absyn_Tqual elt_tq;struct Cyc_Absyn_PtrAtts
ptr_atts;};struct Cyc_Absyn_VarargInfo{struct Cyc_Core_Opt*name;struct Cyc_Absyn_Tqual
tq;void*type;int inject;};struct Cyc_Absyn_FnInfo{struct Cyc_List_List*tvars;struct
Cyc_Core_Opt*effect;void*ret_typ;struct Cyc_List_List*args;int c_varargs;struct Cyc_Absyn_VarargInfo*
cyc_varargs;struct Cyc_List_List*rgn_po;struct Cyc_List_List*attributes;};struct
Cyc_Absyn_UnknownTunionInfo{struct _tuple0*name;int is_xtunion;};struct Cyc_Absyn_UnknownTunion_struct{
int tag;struct Cyc_Absyn_UnknownTunionInfo f1;};struct Cyc_Absyn_KnownTunion_struct{
int tag;struct Cyc_Absyn_Tuniondecl**f1;};struct Cyc_Absyn_TunionInfo{void*
tunion_info;struct Cyc_List_List*targs;void*rgn;};struct Cyc_Absyn_UnknownTunionFieldInfo{
struct _tuple0*tunion_name;struct _tuple0*field_name;int is_xtunion;};struct Cyc_Absyn_UnknownTunionfield_struct{
int tag;struct Cyc_Absyn_UnknownTunionFieldInfo f1;};struct Cyc_Absyn_KnownTunionfield_struct{
int tag;struct Cyc_Absyn_Tuniondecl*f1;struct Cyc_Absyn_Tunionfield*f2;};struct Cyc_Absyn_TunionFieldInfo{
void*field_info;struct Cyc_List_List*targs;};struct Cyc_Absyn_UnknownAggr_struct{
int tag;void*f1;struct _tuple0*f2;};struct Cyc_Absyn_KnownAggr_struct{int tag;struct
Cyc_Absyn_Aggrdecl**f1;};struct Cyc_Absyn_AggrInfo{void*aggr_info;struct Cyc_List_List*
targs;};struct Cyc_Absyn_ArrayInfo{void*elt_type;struct Cyc_Absyn_Tqual tq;struct
Cyc_Absyn_Exp*num_elts;struct Cyc_Absyn_Conref*zero_term;};struct Cyc_Absyn_Evar_struct{
int tag;struct Cyc_Core_Opt*f1;struct Cyc_Core_Opt*f2;int f3;struct Cyc_Core_Opt*f4;}
;struct Cyc_Absyn_VarType_struct{int tag;struct Cyc_Absyn_Tvar*f1;};struct Cyc_Absyn_TunionType_struct{
int tag;struct Cyc_Absyn_TunionInfo f1;};struct Cyc_Absyn_TunionFieldType_struct{int
tag;struct Cyc_Absyn_TunionFieldInfo f1;};struct Cyc_Absyn_PointerType_struct{int
tag;struct Cyc_Absyn_PtrInfo f1;};struct Cyc_Absyn_IntType_struct{int tag;void*f1;
void*f2;};struct Cyc_Absyn_DoubleType_struct{int tag;int f1;};struct Cyc_Absyn_ArrayType_struct{
int tag;struct Cyc_Absyn_ArrayInfo f1;};struct Cyc_Absyn_FnType_struct{int tag;struct
Cyc_Absyn_FnInfo f1;};struct Cyc_Absyn_TupleType_struct{int tag;struct Cyc_List_List*
f1;};struct Cyc_Absyn_AggrType_struct{int tag;struct Cyc_Absyn_AggrInfo f1;};struct
Cyc_Absyn_AnonAggrType_struct{int tag;void*f1;struct Cyc_List_List*f2;};struct Cyc_Absyn_EnumType_struct{
int tag;struct _tuple0*f1;struct Cyc_Absyn_Enumdecl*f2;};struct Cyc_Absyn_AnonEnumType_struct{
int tag;struct Cyc_List_List*f1;};struct Cyc_Absyn_SizeofType_struct{int tag;void*f1;
};struct Cyc_Absyn_RgnHandleType_struct{int tag;void*f1;};struct Cyc_Absyn_TypedefType_struct{
int tag;struct _tuple0*f1;struct Cyc_List_List*f2;struct Cyc_Absyn_Typedefdecl*f3;
void**f4;};struct Cyc_Absyn_TagType_struct{int tag;void*f1;};struct Cyc_Absyn_TypeInt_struct{
int tag;int f1;};struct Cyc_Absyn_AccessEff_struct{int tag;void*f1;};struct Cyc_Absyn_JoinEff_struct{
int tag;struct Cyc_List_List*f1;};struct Cyc_Absyn_RgnsEff_struct{int tag;void*f1;};
struct Cyc_Absyn_NoTypes_struct{int tag;struct Cyc_List_List*f1;struct Cyc_Position_Segment*
f2;};struct Cyc_Absyn_WithTypes_struct{int tag;struct Cyc_List_List*f1;int f2;struct
Cyc_Absyn_VarargInfo*f3;struct Cyc_Core_Opt*f4;struct Cyc_List_List*f5;};struct Cyc_Absyn_Regparm_att_struct{
int tag;int f1;};struct Cyc_Absyn_Aligned_att_struct{int tag;int f1;};struct Cyc_Absyn_Section_att_struct{
int tag;struct _tagged_arr f1;};struct Cyc_Absyn_Format_att_struct{int tag;void*f1;
int f2;int f3;};struct Cyc_Absyn_Initializes_att_struct{int tag;int f1;};struct Cyc_Absyn_Mode_att_struct{
int tag;struct _tagged_arr f1;};struct Cyc_Absyn_Carray_mod_struct{int tag;struct Cyc_Absyn_Conref*
f1;};struct Cyc_Absyn_ConstArray_mod_struct{int tag;struct Cyc_Absyn_Exp*f1;struct
Cyc_Absyn_Conref*f2;};struct Cyc_Absyn_Pointer_mod_struct{int tag;struct Cyc_Absyn_PtrAtts
f1;struct Cyc_Absyn_Tqual f2;};struct Cyc_Absyn_Function_mod_struct{int tag;void*f1;
};struct Cyc_Absyn_TypeParams_mod_struct{int tag;struct Cyc_List_List*f1;struct Cyc_Position_Segment*
f2;int f3;};struct Cyc_Absyn_Attributes_mod_struct{int tag;struct Cyc_Position_Segment*
f1;struct Cyc_List_List*f2;};struct Cyc_Absyn_Char_c_struct{int tag;void*f1;char f2;
};struct Cyc_Absyn_Short_c_struct{int tag;void*f1;short f2;};struct Cyc_Absyn_Int_c_struct{
int tag;void*f1;int f2;};struct Cyc_Absyn_LongLong_c_struct{int tag;void*f1;
long long f2;};struct Cyc_Absyn_Float_c_struct{int tag;struct _tagged_arr f1;};struct
Cyc_Absyn_String_c_struct{int tag;struct _tagged_arr f1;};struct Cyc_Absyn_VarargCallInfo{
int num_varargs;struct Cyc_List_List*injectors;struct Cyc_Absyn_VarargInfo*vai;};
struct Cyc_Absyn_StructField_struct{int tag;struct _tagged_arr*f1;};struct Cyc_Absyn_TupleIndex_struct{
int tag;unsigned int f1;};struct Cyc_Absyn_MallocInfo{int is_calloc;struct Cyc_Absyn_Exp*
rgn;void**elt_type;struct Cyc_Absyn_Exp*num_elts;int fat_result;};struct Cyc_Absyn_Const_e_struct{
int tag;void*f1;};struct Cyc_Absyn_Var_e_struct{int tag;struct _tuple0*f1;void*f2;};
struct Cyc_Absyn_UnknownId_e_struct{int tag;struct _tuple0*f1;};struct Cyc_Absyn_Primop_e_struct{
int tag;void*f1;struct Cyc_List_List*f2;};struct Cyc_Absyn_AssignOp_e_struct{int tag;
struct Cyc_Absyn_Exp*f1;struct Cyc_Core_Opt*f2;struct Cyc_Absyn_Exp*f3;};struct Cyc_Absyn_Increment_e_struct{
int tag;struct Cyc_Absyn_Exp*f1;void*f2;};struct Cyc_Absyn_Conditional_e_struct{int
tag;struct Cyc_Absyn_Exp*f1;struct Cyc_Absyn_Exp*f2;struct Cyc_Absyn_Exp*f3;};
struct Cyc_Absyn_SeqExp_e_struct{int tag;struct Cyc_Absyn_Exp*f1;struct Cyc_Absyn_Exp*
f2;};struct Cyc_Absyn_UnknownCall_e_struct{int tag;struct Cyc_Absyn_Exp*f1;struct
Cyc_List_List*f2;};struct Cyc_Absyn_FnCall_e_struct{int tag;struct Cyc_Absyn_Exp*f1;
struct Cyc_List_List*f2;struct Cyc_Absyn_VarargCallInfo*f3;};struct Cyc_Absyn_Throw_e_struct{
int tag;struct Cyc_Absyn_Exp*f1;};struct Cyc_Absyn_NoInstantiate_e_struct{int tag;
struct Cyc_Absyn_Exp*f1;};struct Cyc_Absyn_Instantiate_e_struct{int tag;struct Cyc_Absyn_Exp*
f1;struct Cyc_List_List*f2;};struct Cyc_Absyn_Cast_e_struct{int tag;void*f1;struct
Cyc_Absyn_Exp*f2;int f3;void*f4;};struct Cyc_Absyn_Address_e_struct{int tag;struct
Cyc_Absyn_Exp*f1;};struct Cyc_Absyn_New_e_struct{int tag;struct Cyc_Absyn_Exp*f1;
struct Cyc_Absyn_Exp*f2;};struct Cyc_Absyn_Sizeoftyp_e_struct{int tag;void*f1;};
struct Cyc_Absyn_Sizeofexp_e_struct{int tag;struct Cyc_Absyn_Exp*f1;};struct Cyc_Absyn_Offsetof_e_struct{
int tag;void*f1;void*f2;};struct Cyc_Absyn_Gentyp_e_struct{int tag;struct Cyc_List_List*
f1;void*f2;};struct Cyc_Absyn_Deref_e_struct{int tag;struct Cyc_Absyn_Exp*f1;};
struct Cyc_Absyn_AggrMember_e_struct{int tag;struct Cyc_Absyn_Exp*f1;struct
_tagged_arr*f2;};struct Cyc_Absyn_AggrArrow_e_struct{int tag;struct Cyc_Absyn_Exp*
f1;struct _tagged_arr*f2;};struct Cyc_Absyn_Subscript_e_struct{int tag;struct Cyc_Absyn_Exp*
f1;struct Cyc_Absyn_Exp*f2;};struct Cyc_Absyn_Tuple_e_struct{int tag;struct Cyc_List_List*
f1;};struct _tuple1{struct Cyc_Core_Opt*f1;struct Cyc_Absyn_Tqual f2;void*f3;};
struct Cyc_Absyn_CompoundLit_e_struct{int tag;struct _tuple1*f1;struct Cyc_List_List*
f2;};struct Cyc_Absyn_Array_e_struct{int tag;struct Cyc_List_List*f1;};struct Cyc_Absyn_Comprehension_e_struct{
int tag;struct Cyc_Absyn_Vardecl*f1;struct Cyc_Absyn_Exp*f2;struct Cyc_Absyn_Exp*f3;
int f4;};struct Cyc_Absyn_Struct_e_struct{int tag;struct _tuple0*f1;struct Cyc_List_List*
f2;struct Cyc_List_List*f3;struct Cyc_Absyn_Aggrdecl*f4;};struct Cyc_Absyn_AnonStruct_e_struct{
int tag;void*f1;struct Cyc_List_List*f2;};struct Cyc_Absyn_Tunion_e_struct{int tag;
struct Cyc_List_List*f1;struct Cyc_Absyn_Tuniondecl*f2;struct Cyc_Absyn_Tunionfield*
f3;};struct Cyc_Absyn_Enum_e_struct{int tag;struct _tuple0*f1;struct Cyc_Absyn_Enumdecl*
f2;struct Cyc_Absyn_Enumfield*f3;};struct Cyc_Absyn_AnonEnum_e_struct{int tag;
struct _tuple0*f1;void*f2;struct Cyc_Absyn_Enumfield*f3;};struct Cyc_Absyn_Malloc_e_struct{
int tag;struct Cyc_Absyn_MallocInfo f1;};struct Cyc_Absyn_UnresolvedMem_e_struct{int
tag;struct Cyc_Core_Opt*f1;struct Cyc_List_List*f2;};struct Cyc_Absyn_StmtExp_e_struct{
int tag;struct Cyc_Absyn_Stmt*f1;};struct Cyc_Absyn_Codegen_e_struct{int tag;struct
Cyc_Absyn_Fndecl*f1;};struct Cyc_Absyn_Fill_e_struct{int tag;struct Cyc_Absyn_Exp*
f1;};struct Cyc_Absyn_Exp{struct Cyc_Core_Opt*topt;void*r;struct Cyc_Position_Segment*
loc;void*annot;};struct _tuple2{struct Cyc_Absyn_Exp*f1;struct Cyc_Absyn_Stmt*f2;};
struct Cyc_Absyn_ForArrayInfo{struct Cyc_List_List*defns;struct _tuple2 condition;
struct _tuple2 delta;struct Cyc_Absyn_Stmt*body;};struct Cyc_Absyn_Exp_s_struct{int
tag;struct Cyc_Absyn_Exp*f1;};struct Cyc_Absyn_Seq_s_struct{int tag;struct Cyc_Absyn_Stmt*
f1;struct Cyc_Absyn_Stmt*f2;};struct Cyc_Absyn_Return_s_struct{int tag;struct Cyc_Absyn_Exp*
f1;};struct Cyc_Absyn_IfThenElse_s_struct{int tag;struct Cyc_Absyn_Exp*f1;struct Cyc_Absyn_Stmt*
f2;struct Cyc_Absyn_Stmt*f3;};struct Cyc_Absyn_While_s_struct{int tag;struct _tuple2
f1;struct Cyc_Absyn_Stmt*f2;};struct Cyc_Absyn_Break_s_struct{int tag;struct Cyc_Absyn_Stmt*
f1;};struct Cyc_Absyn_Continue_s_struct{int tag;struct Cyc_Absyn_Stmt*f1;};struct
Cyc_Absyn_Goto_s_struct{int tag;struct _tagged_arr*f1;struct Cyc_Absyn_Stmt*f2;};
struct Cyc_Absyn_For_s_struct{int tag;struct Cyc_Absyn_Exp*f1;struct _tuple2 f2;
struct _tuple2 f3;struct Cyc_Absyn_Stmt*f4;};struct Cyc_Absyn_Switch_s_struct{int tag;
struct Cyc_Absyn_Exp*f1;struct Cyc_List_List*f2;};struct Cyc_Absyn_SwitchC_s_struct{
int tag;struct Cyc_Absyn_Exp*f1;struct Cyc_List_List*f2;};struct Cyc_Absyn_Fallthru_s_struct{
int tag;struct Cyc_List_List*f1;struct Cyc_Absyn_Switch_clause**f2;};struct Cyc_Absyn_Decl_s_struct{
int tag;struct Cyc_Absyn_Decl*f1;struct Cyc_Absyn_Stmt*f2;};struct Cyc_Absyn_Cut_s_struct{
int tag;struct Cyc_Absyn_Stmt*f1;};struct Cyc_Absyn_Splice_s_struct{int tag;struct
Cyc_Absyn_Stmt*f1;};struct Cyc_Absyn_Label_s_struct{int tag;struct _tagged_arr*f1;
struct Cyc_Absyn_Stmt*f2;};struct Cyc_Absyn_Do_s_struct{int tag;struct Cyc_Absyn_Stmt*
f1;struct _tuple2 f2;};struct Cyc_Absyn_TryCatch_s_struct{int tag;struct Cyc_Absyn_Stmt*
f1;struct Cyc_List_List*f2;};struct Cyc_Absyn_Region_s_struct{int tag;struct Cyc_Absyn_Tvar*
f1;struct Cyc_Absyn_Vardecl*f2;int f3;struct Cyc_Absyn_Stmt*f4;};struct Cyc_Absyn_ForArray_s_struct{
int tag;struct Cyc_Absyn_ForArrayInfo f1;};struct Cyc_Absyn_ResetRegion_s_struct{int
tag;struct Cyc_Absyn_Exp*f1;};struct Cyc_Absyn_Stmt{void*r;struct Cyc_Position_Segment*
loc;struct Cyc_List_List*non_local_preds;int try_depth;void*annot;};struct Cyc_Absyn_Var_p_struct{
int tag;struct Cyc_Absyn_Vardecl*f1;};struct Cyc_Absyn_Reference_p_struct{int tag;
struct Cyc_Absyn_Vardecl*f1;};struct Cyc_Absyn_TagInt_p_struct{int tag;struct Cyc_Absyn_Tvar*
f1;struct Cyc_Absyn_Vardecl*f2;};struct Cyc_Absyn_Tuple_p_struct{int tag;struct Cyc_List_List*
f1;};struct Cyc_Absyn_Pointer_p_struct{int tag;struct Cyc_Absyn_Pat*f1;};struct Cyc_Absyn_Aggr_p_struct{
int tag;struct Cyc_Absyn_AggrInfo f1;struct Cyc_List_List*f2;struct Cyc_List_List*f3;
};struct Cyc_Absyn_Tunion_p_struct{int tag;struct Cyc_Absyn_Tuniondecl*f1;struct Cyc_Absyn_Tunionfield*
f2;struct Cyc_List_List*f3;};struct Cyc_Absyn_Int_p_struct{int tag;void*f1;int f2;};
struct Cyc_Absyn_Char_p_struct{int tag;char f1;};struct Cyc_Absyn_Float_p_struct{int
tag;struct _tagged_arr f1;};struct Cyc_Absyn_Enum_p_struct{int tag;struct Cyc_Absyn_Enumdecl*
f1;struct Cyc_Absyn_Enumfield*f2;};struct Cyc_Absyn_AnonEnum_p_struct{int tag;void*
f1;struct Cyc_Absyn_Enumfield*f2;};struct Cyc_Absyn_UnknownId_p_struct{int tag;
struct _tuple0*f1;};struct Cyc_Absyn_UnknownCall_p_struct{int tag;struct _tuple0*f1;
struct Cyc_List_List*f2;};struct Cyc_Absyn_Pat{void*r;struct Cyc_Core_Opt*topt;
struct Cyc_Position_Segment*loc;};struct Cyc_Absyn_Switch_clause{struct Cyc_Absyn_Pat*
pattern;struct Cyc_Core_Opt*pat_vars;struct Cyc_Absyn_Exp*where_clause;struct Cyc_Absyn_Stmt*
body;struct Cyc_Position_Segment*loc;};struct Cyc_Absyn_SwitchC_clause{struct Cyc_Absyn_Exp*
cnst_exp;struct Cyc_Absyn_Stmt*body;struct Cyc_Position_Segment*loc;};struct Cyc_Absyn_Global_b_struct{
int tag;struct Cyc_Absyn_Vardecl*f1;};struct Cyc_Absyn_Funname_b_struct{int tag;
struct Cyc_Absyn_Fndecl*f1;};struct Cyc_Absyn_Param_b_struct{int tag;struct Cyc_Absyn_Vardecl*
f1;};struct Cyc_Absyn_Local_b_struct{int tag;struct Cyc_Absyn_Vardecl*f1;};struct
Cyc_Absyn_Pat_b_struct{int tag;struct Cyc_Absyn_Vardecl*f1;};struct Cyc_Absyn_Vardecl{
void*sc;struct _tuple0*name;struct Cyc_Absyn_Tqual tq;void*type;struct Cyc_Absyn_Exp*
initializer;struct Cyc_Core_Opt*rgn;struct Cyc_List_List*attributes;int escapes;};
struct Cyc_Absyn_Fndecl{void*sc;int is_inline;struct _tuple0*name;struct Cyc_List_List*
tvs;struct Cyc_Core_Opt*effect;void*ret_type;struct Cyc_List_List*args;int
c_varargs;struct Cyc_Absyn_VarargInfo*cyc_varargs;struct Cyc_List_List*rgn_po;
struct Cyc_Absyn_Stmt*body;struct Cyc_Core_Opt*cached_typ;struct Cyc_Core_Opt*
param_vardecls;struct Cyc_List_List*attributes;};struct Cyc_Absyn_Aggrfield{struct
_tagged_arr*name;struct Cyc_Absyn_Tqual tq;void*type;struct Cyc_Absyn_Exp*width;
struct Cyc_List_List*attributes;};struct Cyc_Absyn_AggrdeclImpl{struct Cyc_List_List*
exist_vars;struct Cyc_List_List*rgn_po;struct Cyc_List_List*fields;};struct Cyc_Absyn_Aggrdecl{
void*kind;void*sc;struct _tuple0*name;struct Cyc_List_List*tvs;struct Cyc_Absyn_AggrdeclImpl*
impl;struct Cyc_List_List*attributes;};struct Cyc_Absyn_Tunionfield{struct _tuple0*
name;struct Cyc_List_List*typs;struct Cyc_Position_Segment*loc;void*sc;};struct Cyc_Absyn_Tuniondecl{
void*sc;struct _tuple0*name;struct Cyc_List_List*tvs;struct Cyc_Core_Opt*fields;int
is_xtunion;};struct Cyc_Absyn_Enumfield{struct _tuple0*name;struct Cyc_Absyn_Exp*
tag;struct Cyc_Position_Segment*loc;};struct Cyc_Absyn_Enumdecl{void*sc;struct
_tuple0*name;struct Cyc_Core_Opt*fields;};struct Cyc_Absyn_Typedefdecl{struct
_tuple0*name;struct Cyc_Absyn_Tqual tq;struct Cyc_List_List*tvs;struct Cyc_Core_Opt*
kind;struct Cyc_Core_Opt*defn;struct Cyc_List_List*atts;};struct Cyc_Absyn_Var_d_struct{
int tag;struct Cyc_Absyn_Vardecl*f1;};struct Cyc_Absyn_Fn_d_struct{int tag;struct Cyc_Absyn_Fndecl*
f1;};struct Cyc_Absyn_Let_d_struct{int tag;struct Cyc_Absyn_Pat*f1;struct Cyc_Core_Opt*
f2;struct Cyc_Absyn_Exp*f3;};struct Cyc_Absyn_Letv_d_struct{int tag;struct Cyc_List_List*
f1;};struct Cyc_Absyn_Aggr_d_struct{int tag;struct Cyc_Absyn_Aggrdecl*f1;};struct
Cyc_Absyn_Tunion_d_struct{int tag;struct Cyc_Absyn_Tuniondecl*f1;};struct Cyc_Absyn_Enum_d_struct{
int tag;struct Cyc_Absyn_Enumdecl*f1;};struct Cyc_Absyn_Typedef_d_struct{int tag;
struct Cyc_Absyn_Typedefdecl*f1;};struct Cyc_Absyn_Namespace_d_struct{int tag;
struct _tagged_arr*f1;struct Cyc_List_List*f2;};struct Cyc_Absyn_Using_d_struct{int
tag;struct _tuple0*f1;struct Cyc_List_List*f2;};struct Cyc_Absyn_ExternC_d_struct{
int tag;struct Cyc_List_List*f1;};struct Cyc_Absyn_Decl{void*r;struct Cyc_Position_Segment*
loc;};struct Cyc_Absyn_ArrayElement_struct{int tag;struct Cyc_Absyn_Exp*f1;};struct
Cyc_Absyn_FieldName_struct{int tag;struct _tagged_arr*f1;};extern char Cyc_Absyn_EmptyAnnot[
15];struct Cyc_Absyn_Tqual Cyc_Absyn_empty_tqual();void*Cyc_Absyn_conref_def(void*,
struct Cyc_Absyn_Conref*x);void*Cyc_Absyn_compress_kb(void*);void*Cyc_Absyn_new_evar(
struct Cyc_Core_Opt*k,struct Cyc_Core_Opt*tenv);extern void*Cyc_Absyn_bounds_one;
struct Cyc_Absyn_Exp*Cyc_Absyn_times_exp(struct Cyc_Absyn_Exp*,struct Cyc_Absyn_Exp*,
struct Cyc_Position_Segment*);struct Cyc_Absyn_Exp*Cyc_Absyn_sizeoftyp_exp(void*t,
struct Cyc_Position_Segment*);struct _tagged_arr Cyc_Absyn_attribute2string(void*);
struct _tuple3{void*f1;struct _tuple0*f2;};struct _tuple3 Cyc_Absyn_aggr_kinded_name(
void*);struct Cyc_PP_Ppstate;struct Cyc_PP_Out;struct Cyc_PP_Doc;struct Cyc_Absynpp_Params{
int expand_typedefs: 1;int qvar_to_Cids: 1;int add_cyc_prefix: 1;int to_VC: 1;int
decls_first: 1;int rewrite_temp_tvars: 1;int print_all_tvars: 1;int print_all_kinds: 1;
int print_all_effects: 1;int print_using_stmts: 1;int print_externC_stmts: 1;int
print_full_evars: 1;int print_zeroterm: 1;int generate_line_directives: 1;int
use_curr_namespace: 1;struct Cyc_List_List*curr_namespace;};void Cyc_Absynpp_set_params(
struct Cyc_Absynpp_Params*fs);int Cyc_Absynpp_is_anon_aggrtype(void*t);extern
struct _tagged_arr*Cyc_Absynpp_cyc_stringptr;int Cyc_Absynpp_exp_prec(struct Cyc_Absyn_Exp*);
struct _tagged_arr Cyc_Absynpp_char_escape(char);struct _tagged_arr Cyc_Absynpp_string_escape(
struct _tagged_arr);struct _tagged_arr Cyc_Absynpp_prim2str(void*p);int Cyc_Absynpp_is_declaration(
struct Cyc_Absyn_Stmt*s);struct _tuple4{struct _tagged_arr*f1;struct Cyc_Absyn_Tqual
f2;void*f3;};struct _tuple1*Cyc_Absynpp_arg_mk_opt(struct _tuple4*arg);struct
_tuple5{struct Cyc_Absyn_Tqual f1;void*f2;struct Cyc_List_List*f3;};struct _tuple5
Cyc_Absynpp_to_tms(struct Cyc_Absyn_Tqual tq,void*t);struct _tuple6{unsigned int f1;
int f2;};struct _tuple6 Cyc_Evexp_eval_const_uint_exp(struct Cyc_Absyn_Exp*e);struct
Cyc_Iter_Iter{void*env;int(*next)(void*env,void*dest);};int Cyc_Iter_next(struct
Cyc_Iter_Iter,void*);struct Cyc_Set_Set;extern char Cyc_Set_Absent[11];struct Cyc_Dict_Dict;
extern char Cyc_Dict_Present[12];extern char Cyc_Dict_Absent[11];struct _tuple7{void*
f1;void*f2;};struct _tuple7*Cyc_Dict_rchoose(struct _RegionHandle*r,struct Cyc_Dict_Dict*
d);struct _tuple7*Cyc_Dict_rchoose(struct _RegionHandle*,struct Cyc_Dict_Dict*d);
struct Cyc_RgnOrder_RgnPO;struct Cyc_RgnOrder_RgnPO*Cyc_RgnOrder_initial_fn_po(
struct Cyc_List_List*tvs,struct Cyc_List_List*po,void*effect,struct Cyc_Absyn_Tvar*
fst_rgn);struct Cyc_RgnOrder_RgnPO*Cyc_RgnOrder_add_outlives_constraint(struct Cyc_RgnOrder_RgnPO*
po,void*eff,void*rgn);struct Cyc_RgnOrder_RgnPO*Cyc_RgnOrder_add_youngest(struct
Cyc_RgnOrder_RgnPO*po,struct Cyc_Absyn_Tvar*rgn,int resetable);int Cyc_RgnOrder_is_region_resetable(
struct Cyc_RgnOrder_RgnPO*po,struct Cyc_Absyn_Tvar*r);int Cyc_RgnOrder_effect_outlives(
struct Cyc_RgnOrder_RgnPO*po,void*eff,void*rgn);int Cyc_RgnOrder_satisfies_constraints(
struct Cyc_RgnOrder_RgnPO*po,struct Cyc_List_List*constraints,void*default_bound,
int do_pin);int Cyc_RgnOrder_eff_outlives_eff(struct Cyc_RgnOrder_RgnPO*po,void*
eff1,void*eff2);struct Cyc_Tcenv_VarRes_struct{int tag;void*f1;};struct Cyc_Tcenv_AggrRes_struct{
int tag;struct Cyc_Absyn_Aggrdecl*f1;};struct Cyc_Tcenv_TunionRes_struct{int tag;
struct Cyc_Absyn_Tuniondecl*f1;struct Cyc_Absyn_Tunionfield*f2;};struct Cyc_Tcenv_EnumRes_struct{
int tag;struct Cyc_Absyn_Enumdecl*f1;struct Cyc_Absyn_Enumfield*f2;};struct Cyc_Tcenv_AnonEnumRes_struct{
int tag;void*f1;struct Cyc_Absyn_Enumfield*f2;};struct Cyc_Tcenv_Genv{struct Cyc_Set_Set*
namespaces;struct Cyc_Dict_Dict*aggrdecls;struct Cyc_Dict_Dict*tuniondecls;struct
Cyc_Dict_Dict*enumdecls;struct Cyc_Dict_Dict*typedefs;struct Cyc_Dict_Dict*
ordinaries;struct Cyc_List_List*availables;};struct Cyc_Tcenv_Fenv;struct Cyc_Tcenv_Stmt_j_struct{
int tag;struct Cyc_Absyn_Stmt*f1;};struct Cyc_Tcenv_Outermost_struct{int tag;void*f1;
};struct Cyc_Tcenv_Frame_struct{int tag;void*f1;void*f2;};struct Cyc_Tcenv_Hidden_struct{
int tag;void*f1;void*f2;};struct Cyc_Tcenv_Tenv{struct Cyc_List_List*ns;struct Cyc_Dict_Dict*
ae;struct Cyc_Core_Opt*le;};void*Cyc_Tcutil_impos(struct _tagged_arr fmt,struct
_tagged_arr ap);void*Cyc_Tcutil_compress(void*t);static int Cyc_Absyndump_expand_typedefs;
static int Cyc_Absyndump_qvar_to_Cids;static int Cyc_Absyndump_add_cyc_prefix;static
int Cyc_Absyndump_generate_line_directives;static int Cyc_Absyndump_to_VC;void Cyc_Absyndump_set_params(
struct Cyc_Absynpp_Params*fs){Cyc_Absyndump_expand_typedefs=fs->expand_typedefs;
Cyc_Absyndump_qvar_to_Cids=fs->qvar_to_Cids;Cyc_Absyndump_add_cyc_prefix=fs->add_cyc_prefix;
Cyc_Absyndump_to_VC=fs->to_VC;Cyc_Absyndump_generate_line_directives=fs->generate_line_directives;
Cyc_Absynpp_set_params(fs);}void Cyc_Absyndump_dumptyp(void*);void Cyc_Absyndump_dumpntyp(
void*t);void Cyc_Absyndump_dumpexp(struct Cyc_Absyn_Exp*);void Cyc_Absyndump_dumpexp_prec(
int,struct Cyc_Absyn_Exp*);void Cyc_Absyndump_dumppat(struct Cyc_Absyn_Pat*);void
Cyc_Absyndump_dumpstmt(struct Cyc_Absyn_Stmt*);void Cyc_Absyndump_dumpvardecl(
struct Cyc_Absyn_Vardecl*,struct Cyc_Position_Segment*);void Cyc_Absyndump_dumpdecl(
struct Cyc_Absyn_Decl*);void Cyc_Absyndump_dumptms(struct Cyc_List_List*tms,void(*f)(
void*),void*a);void Cyc_Absyndump_dumptqtd(struct Cyc_Absyn_Tqual,void*,void(*f)(
void*),void*);void Cyc_Absyndump_dumpaggrfields(struct Cyc_List_List*fields);void
Cyc_Absyndump_dumpenumfields(struct Cyc_List_List*fields);void Cyc_Absyndump_dumploc(
struct Cyc_Position_Segment*);struct Cyc___cycFILE**Cyc_Absyndump_dump_file=& Cyc_stdout;
void Cyc_Absyndump_ignore(void*x){return;}static unsigned int Cyc_Absyndump_pos=0;
static char Cyc_Absyndump_prev_char='x';int Cyc_Absyndump_need_space_before(){
switch(Cyc_Absyndump_prev_char){case '{': _LL0: goto _LL1;case '}': _LL1: goto _LL2;case
'(': _LL2: goto _LL3;case ')': _LL3: goto _LL4;case '[': _LL4: goto _LL5;case ']': _LL5: goto
_LL6;case ';': _LL6: goto _LL7;case ',': _LL7: goto _LL8;case '=': _LL8: goto _LL9;case '?':
_LL9: goto _LLA;case '!': _LLA: goto _LLB;case ' ': _LLB: goto _LLC;case '\n': _LLC: goto _LLD;
case '*': _LLD: return 0;default: _LLE: return 1;}}void Cyc_Absyndump_dump(struct
_tagged_arr s){int sz=(int)Cyc_strlen((struct _tagged_arr)s);Cyc_Absyndump_pos +=sz;
if(Cyc_Absyndump_pos > 80){Cyc_Absyndump_pos=(unsigned int)sz;Cyc_fputc((int)'\n',*
Cyc_Absyndump_dump_file);}else{if(Cyc_Absyndump_need_space_before())Cyc_fputc((
int)' ',*Cyc_Absyndump_dump_file);}if(sz >= 1){Cyc_Absyndump_prev_char=*((const
char*)_check_unknown_subscript(s,sizeof(char),sz - 1));Cyc_file_string_write(*Cyc_Absyndump_dump_file,
s,0,sz);}}void Cyc_Absyndump_dump_nospace(struct _tagged_arr s){int sz=(int)Cyc_strlen((
struct _tagged_arr)s);Cyc_Absyndump_pos +=sz;if(sz >= 1){Cyc_file_string_write(*Cyc_Absyndump_dump_file,
s,0,sz);Cyc_Absyndump_prev_char=*((const char*)_check_unknown_subscript(s,sizeof(
char),sz - 1));}}void Cyc_Absyndump_dump_char(int c){++ Cyc_Absyndump_pos;Cyc_fputc(
c,*Cyc_Absyndump_dump_file);Cyc_Absyndump_prev_char=(char)c;}void Cyc_Absyndump_dumploc(
struct Cyc_Position_Segment*loc){if(loc == 0)return;if(!Cyc_Absyndump_generate_line_directives)
return;{struct _tagged_arr _tmp0=Cyc_Position_get_line_directive(loc);Cyc_Absyndump_dump(
_tmp0);}}void Cyc_Absyndump_dump_str(struct _tagged_arr*s){Cyc_Absyndump_dump(*s);}
void Cyc_Absyndump_dump_semi(){Cyc_Absyndump_dump_char((int)';');}void Cyc_Absyndump_dump_sep(
void(*f)(void*),struct Cyc_List_List*l,struct _tagged_arr sep){if(l == 0)return;for(
0;l->tl != 0;l=l->tl){f((void*)l->hd);Cyc_Absyndump_dump_nospace(sep);}f((void*)l->hd);}
void Cyc_Absyndump_dump_sep_c(void(*f)(void*,void*),void*env,struct Cyc_List_List*
l,struct _tagged_arr sep){if(l == 0)return;for(0;l->tl != 0;l=l->tl){f(env,(void*)l->hd);
Cyc_Absyndump_dump_nospace(sep);}f(env,(void*)l->hd);}void Cyc_Absyndump_group(
void(*f)(void*),struct Cyc_List_List*l,struct _tagged_arr start,struct _tagged_arr
end,struct _tagged_arr sep){Cyc_Absyndump_dump_nospace(start);Cyc_Absyndump_dump_sep(
f,l,sep);Cyc_Absyndump_dump_nospace(end);}void Cyc_Absyndump_group_c(void(*f)(
void*,void*),void*env,struct Cyc_List_List*l,struct _tagged_arr start,struct
_tagged_arr end,struct _tagged_arr sep){Cyc_Absyndump_dump_nospace(start);Cyc_Absyndump_dump_sep_c(
f,env,l,sep);Cyc_Absyndump_dump_nospace(end);}void Cyc_Absyndump_egroup(void(*f)(
void*),struct Cyc_List_List*l,struct _tagged_arr start,struct _tagged_arr end,struct
_tagged_arr sep){if(l != 0)Cyc_Absyndump_group(f,l,start,end,sep);}void Cyc_Absyndump_dumpqvar(
struct _tuple0*v){struct Cyc_List_List*_tmp1=0;{void*_tmp2=(*v).f1;struct Cyc_List_List*
_tmp3;struct Cyc_List_List*_tmp4;_LL11: if((int)_tmp2 != 0)goto _LL13;_LL12: _tmp3=0;
goto _LL14;_LL13: if(_tmp2 <= (void*)1?1:*((int*)_tmp2)!= 0)goto _LL15;_tmp3=((
struct Cyc_Absyn_Rel_n_struct*)_tmp2)->f1;_LL14: _tmp1=_tmp3;goto _LL10;_LL15: if(
_tmp2 <= (void*)1?1:*((int*)_tmp2)!= 1)goto _LL10;_tmp4=((struct Cyc_Absyn_Abs_n_struct*)
_tmp2)->f1;_LL16: _tmp1=(Cyc_Absyndump_qvar_to_Cids?Cyc_Absyndump_add_cyc_prefix:
0)?({struct Cyc_List_List*_tmp5=_cycalloc(sizeof(*_tmp5));_tmp5->hd=Cyc_Absynpp_cyc_stringptr;
_tmp5->tl=_tmp4;_tmp5;}): _tmp4;goto _LL10;_LL10:;}if(_tmp1 != 0){Cyc_Absyndump_dump_str((
struct _tagged_arr*)_tmp1->hd);for(_tmp1=_tmp1->tl;_tmp1 != 0;_tmp1=_tmp1->tl){if(
Cyc_Absyndump_qvar_to_Cids)Cyc_Absyndump_dump_char((int)'_');else{Cyc_Absyndump_dump_nospace(({
const char*_tmp6="::";_tag_arr(_tmp6,sizeof(char),_get_zero_arr_size(_tmp6,3));}));}
Cyc_Absyndump_dump_nospace(*((struct _tagged_arr*)_tmp1->hd));}if(Cyc_Absyndump_qvar_to_Cids)
Cyc_Absyndump_dump_nospace(({const char*_tmp7="_";_tag_arr(_tmp7,sizeof(char),
_get_zero_arr_size(_tmp7,2));}));else{Cyc_Absyndump_dump_nospace(({const char*
_tmp8="::";_tag_arr(_tmp8,sizeof(char),_get_zero_arr_size(_tmp8,3));}));}Cyc_Absyndump_dump_nospace(*(*
v).f2);}else{Cyc_Absyndump_dump_str((*v).f2);}}void Cyc_Absyndump_dumptq(struct
Cyc_Absyn_Tqual tq){if(tq.q_restrict)Cyc_Absyndump_dump(({const char*_tmp9="restrict";
_tag_arr(_tmp9,sizeof(char),_get_zero_arr_size(_tmp9,9));}));if(tq.q_volatile)
Cyc_Absyndump_dump(({const char*_tmpA="volatile";_tag_arr(_tmpA,sizeof(char),
_get_zero_arr_size(_tmpA,9));}));if(tq.print_const)Cyc_Absyndump_dump(({const
char*_tmpB="const";_tag_arr(_tmpB,sizeof(char),_get_zero_arr_size(_tmpB,6));}));}
void Cyc_Absyndump_dumpscope(void*sc){void*_tmpC=sc;_LL18: if((int)_tmpC != 0)goto
_LL1A;_LL19: Cyc_Absyndump_dump(({const char*_tmpD="static";_tag_arr(_tmpD,sizeof(
char),_get_zero_arr_size(_tmpD,7));}));return;_LL1A: if((int)_tmpC != 2)goto _LL1C;
_LL1B: return;_LL1C: if((int)_tmpC != 3)goto _LL1E;_LL1D: Cyc_Absyndump_dump(({const
char*_tmpE="extern";_tag_arr(_tmpE,sizeof(char),_get_zero_arr_size(_tmpE,7));}));
return;_LL1E: if((int)_tmpC != 4)goto _LL20;_LL1F: Cyc_Absyndump_dump(({const char*
_tmpF="extern \"C\"";_tag_arr(_tmpF,sizeof(char),_get_zero_arr_size(_tmpF,11));}));
return;_LL20: if((int)_tmpC != 1)goto _LL22;_LL21: Cyc_Absyndump_dump(({const char*
_tmp10="abstract";_tag_arr(_tmp10,sizeof(char),_get_zero_arr_size(_tmp10,9));}));
return;_LL22: if((int)_tmpC != 5)goto _LL17;_LL23: Cyc_Absyndump_dump(({const char*
_tmp11="register";_tag_arr(_tmp11,sizeof(char),_get_zero_arr_size(_tmp11,9));}));
return;_LL17:;}void Cyc_Absyndump_dumpkind(void*k){void*_tmp12=k;_LL25: if((int)
_tmp12 != 0)goto _LL27;_LL26: Cyc_Absyndump_dump(({const char*_tmp13="A";_tag_arr(
_tmp13,sizeof(char),_get_zero_arr_size(_tmp13,2));}));return;_LL27: if((int)
_tmp12 != 1)goto _LL29;_LL28: Cyc_Absyndump_dump(({const char*_tmp14="M";_tag_arr(
_tmp14,sizeof(char),_get_zero_arr_size(_tmp14,2));}));return;_LL29: if((int)
_tmp12 != 2)goto _LL2B;_LL2A: Cyc_Absyndump_dump(({const char*_tmp15="B";_tag_arr(
_tmp15,sizeof(char),_get_zero_arr_size(_tmp15,2));}));return;_LL2B: if((int)
_tmp12 != 3)goto _LL2D;_LL2C: Cyc_Absyndump_dump(({const char*_tmp16="R";_tag_arr(
_tmp16,sizeof(char),_get_zero_arr_size(_tmp16,2));}));return;_LL2D: if((int)
_tmp12 != 4)goto _LL2F;_LL2E: Cyc_Absyndump_dump(({const char*_tmp17="E";_tag_arr(
_tmp17,sizeof(char),_get_zero_arr_size(_tmp17,2));}));return;_LL2F: if((int)
_tmp12 != 5)goto _LL24;_LL30: Cyc_Absyndump_dump(({const char*_tmp18="I";_tag_arr(
_tmp18,sizeof(char),_get_zero_arr_size(_tmp18,2));}));return;_LL24:;}void Cyc_Absyndump_dumpaggr_kind(
void*k){void*_tmp19=k;_LL32: if((int)_tmp19 != 0)goto _LL34;_LL33: Cyc_Absyndump_dump(({
const char*_tmp1A="struct";_tag_arr(_tmp1A,sizeof(char),_get_zero_arr_size(_tmp1A,
7));}));return;_LL34: if((int)_tmp19 != 1)goto _LL31;_LL35: Cyc_Absyndump_dump(({
const char*_tmp1B="union";_tag_arr(_tmp1B,sizeof(char),_get_zero_arr_size(_tmp1B,
6));}));return;_LL31:;}void Cyc_Absyndump_dumptps(struct Cyc_List_List*ts){Cyc_Absyndump_egroup(
Cyc_Absyndump_dumptyp,ts,({const char*_tmp1C="<";_tag_arr(_tmp1C,sizeof(char),
_get_zero_arr_size(_tmp1C,2));}),({const char*_tmp1D=">";_tag_arr(_tmp1D,sizeof(
char),_get_zero_arr_size(_tmp1D,2));}),({const char*_tmp1E=",";_tag_arr(_tmp1E,
sizeof(char),_get_zero_arr_size(_tmp1E,2));}));}void Cyc_Absyndump_dumptvar(
struct Cyc_Absyn_Tvar*tv){Cyc_Absyndump_dump_str(tv->name);}void Cyc_Absyndump_dumpkindedtvar(
struct Cyc_Absyn_Tvar*tv){Cyc_Absyndump_dump_str(tv->name);{void*_tmp1F=Cyc_Absyn_compress_kb((
void*)tv->kind);void*_tmp20;void*_tmp21;_LL37: if(*((int*)_tmp1F)!= 0)goto _LL39;
_tmp20=(void*)((struct Cyc_Absyn_Eq_kb_struct*)_tmp1F)->f1;if((int)_tmp20 != 2)
goto _LL39;_LL38: goto _LL3A;_LL39: if(*((int*)_tmp1F)!= 2)goto _LL3B;_LL3A: goto _LL3C;
_LL3B: if(*((int*)_tmp1F)!= 1)goto _LL3D;_LL3C: Cyc_Absyndump_dump(({const char*
_tmp22="::?";_tag_arr(_tmp22,sizeof(char),_get_zero_arr_size(_tmp22,4));}));goto
_LL36;_LL3D: if(*((int*)_tmp1F)!= 0)goto _LL36;_tmp21=(void*)((struct Cyc_Absyn_Eq_kb_struct*)
_tmp1F)->f1;_LL3E: Cyc_Absyndump_dump(({const char*_tmp23="::";_tag_arr(_tmp23,
sizeof(char),_get_zero_arr_size(_tmp23,3));}));Cyc_Absyndump_dumpkind(_tmp21);
goto _LL36;_LL36:;}}void Cyc_Absyndump_dumptvars(struct Cyc_List_List*tvs){((void(*)(
void(*f)(struct Cyc_Absyn_Tvar*),struct Cyc_List_List*l,struct _tagged_arr start,
struct _tagged_arr end,struct _tagged_arr sep))Cyc_Absyndump_egroup)(Cyc_Absyndump_dumptvar,
tvs,({const char*_tmp24="<";_tag_arr(_tmp24,sizeof(char),_get_zero_arr_size(
_tmp24,2));}),({const char*_tmp25=">";_tag_arr(_tmp25,sizeof(char),
_get_zero_arr_size(_tmp25,2));}),({const char*_tmp26=",";_tag_arr(_tmp26,sizeof(
char),_get_zero_arr_size(_tmp26,2));}));}void Cyc_Absyndump_dumpkindedtvars(
struct Cyc_List_List*tvs){((void(*)(void(*f)(struct Cyc_Absyn_Tvar*),struct Cyc_List_List*
l,struct _tagged_arr start,struct _tagged_arr end,struct _tagged_arr sep))Cyc_Absyndump_egroup)(
Cyc_Absyndump_dumpkindedtvar,tvs,({const char*_tmp27="<";_tag_arr(_tmp27,sizeof(
char),_get_zero_arr_size(_tmp27,2));}),({const char*_tmp28=">";_tag_arr(_tmp28,
sizeof(char),_get_zero_arr_size(_tmp28,2));}),({const char*_tmp29=",";_tag_arr(
_tmp29,sizeof(char),_get_zero_arr_size(_tmp29,2));}));}struct _tuple8{struct Cyc_Absyn_Tqual
f1;void*f2;};void Cyc_Absyndump_dumparg(struct _tuple8*pr){((void(*)(struct Cyc_Absyn_Tqual,
void*,void(*f)(int),int))Cyc_Absyndump_dumptqtd)((*pr).f1,(*pr).f2,(void(*)(int x))
Cyc_Absyndump_ignore,0);}void Cyc_Absyndump_dumpargs(struct Cyc_List_List*ts){((
void(*)(void(*f)(struct _tuple8*),struct Cyc_List_List*l,struct _tagged_arr start,
struct _tagged_arr end,struct _tagged_arr sep))Cyc_Absyndump_group)(Cyc_Absyndump_dumparg,
ts,({const char*_tmp2A="(";_tag_arr(_tmp2A,sizeof(char),_get_zero_arr_size(_tmp2A,
2));}),({const char*_tmp2B=")";_tag_arr(_tmp2B,sizeof(char),_get_zero_arr_size(
_tmp2B,2));}),({const char*_tmp2C=",";_tag_arr(_tmp2C,sizeof(char),
_get_zero_arr_size(_tmp2C,2));}));}void Cyc_Absyndump_dump_callconv(struct Cyc_List_List*
atts){for(0;atts != 0;atts=atts->tl){void*_tmp2D=(void*)atts->hd;_LL40: if((int)
_tmp2D != 0)goto _LL42;_LL41: Cyc_Absyndump_dump(({const char*_tmp2E="_stdcall";
_tag_arr(_tmp2E,sizeof(char),_get_zero_arr_size(_tmp2E,9));}));return;_LL42: if((
int)_tmp2D != 1)goto _LL44;_LL43: Cyc_Absyndump_dump(({const char*_tmp2F="_cdecl";
_tag_arr(_tmp2F,sizeof(char),_get_zero_arr_size(_tmp2F,7));}));return;_LL44: if((
int)_tmp2D != 2)goto _LL46;_LL45: Cyc_Absyndump_dump(({const char*_tmp30="_fastcall";
_tag_arr(_tmp30,sizeof(char),_get_zero_arr_size(_tmp30,10));}));return;_LL46:;
_LL47: goto _LL3F;_LL3F:;}}void Cyc_Absyndump_dump_noncallconv(struct Cyc_List_List*
atts){int hasatt=0;{struct Cyc_List_List*atts2=atts;for(0;atts2 != 0;atts2=atts2->tl){
void*_tmp31=(void*)((struct Cyc_List_List*)_check_null(atts))->hd;_LL49: if((int)
_tmp31 != 0)goto _LL4B;_LL4A: goto _LL4C;_LL4B: if((int)_tmp31 != 1)goto _LL4D;_LL4C:
goto _LL4E;_LL4D: if((int)_tmp31 != 2)goto _LL4F;_LL4E: goto _LL48;_LL4F:;_LL50: hasatt=
1;goto _LL48;_LL48:;}}if(!hasatt)return;Cyc_Absyndump_dump(({const char*_tmp32="__declspec(";
_tag_arr(_tmp32,sizeof(char),_get_zero_arr_size(_tmp32,12));}));for(0;atts != 0;
atts=atts->tl){void*_tmp33=(void*)atts->hd;_LL52: if((int)_tmp33 != 0)goto _LL54;
_LL53: goto _LL55;_LL54: if((int)_tmp33 != 1)goto _LL56;_LL55: goto _LL57;_LL56: if((int)
_tmp33 != 2)goto _LL58;_LL57: goto _LL51;_LL58:;_LL59: Cyc_Absyndump_dump(Cyc_Absyn_attribute2string((
void*)atts->hd));goto _LL51;_LL51:;}Cyc_Absyndump_dump_char((int)')');}void Cyc_Absyndump_dumpatts(
struct Cyc_List_List*atts){if(atts == 0)return;if(Cyc_Absyndump_to_VC){Cyc_Absyndump_dump_noncallconv(
atts);return;}Cyc_Absyndump_dump(({const char*_tmp34=" __attribute__((";_tag_arr(
_tmp34,sizeof(char),_get_zero_arr_size(_tmp34,17));}));for(0;atts != 0;atts=atts->tl){
Cyc_Absyndump_dump(Cyc_Absyn_attribute2string((void*)atts->hd));if(atts->tl != 0)
Cyc_Absyndump_dump(({const char*_tmp35=",";_tag_arr(_tmp35,sizeof(char),
_get_zero_arr_size(_tmp35,2));}));}Cyc_Absyndump_dump(({const char*_tmp36=")) ";
_tag_arr(_tmp36,sizeof(char),_get_zero_arr_size(_tmp36,4));}));}int Cyc_Absyndump_next_is_pointer(
struct Cyc_List_List*tms){if(tms == 0)return 0;{void*_tmp37=(void*)tms->hd;_LL5B:
if(*((int*)_tmp37)!= 2)goto _LL5D;_LL5C: return 1;_LL5D:;_LL5E: return 0;_LL5A:;}}
static void Cyc_Absyndump_dumprgn(void*t){void*_tmp38=Cyc_Tcutil_compress(t);_LL60:
if((int)_tmp38 != 2)goto _LL62;_LL61: Cyc_Absyndump_dump(({const char*_tmp39="`H";
_tag_arr(_tmp39,sizeof(char),_get_zero_arr_size(_tmp39,3));}));goto _LL5F;_LL62:;
_LL63: Cyc_Absyndump_dumpntyp(t);goto _LL5F;_LL5F:;}struct _tuple9{struct Cyc_List_List*
f1;struct Cyc_List_List*f2;};static struct _tuple9 Cyc_Absyndump_effects_split(void*
t){struct Cyc_List_List*rgions=0;struct Cyc_List_List*effects=0;{void*_tmp3A=Cyc_Tcutil_compress(
t);void*_tmp3B;struct Cyc_List_List*_tmp3C;_LL65: if(_tmp3A <= (void*)3?1:*((int*)
_tmp3A)!= 19)goto _LL67;_tmp3B=(void*)((struct Cyc_Absyn_AccessEff_struct*)_tmp3A)->f1;
_LL66: rgions=({struct Cyc_List_List*_tmp3D=_cycalloc(sizeof(*_tmp3D));_tmp3D->hd=(
void*)_tmp3B;_tmp3D->tl=rgions;_tmp3D;});goto _LL64;_LL67: if(_tmp3A <= (void*)3?1:*((
int*)_tmp3A)!= 20)goto _LL69;_tmp3C=((struct Cyc_Absyn_JoinEff_struct*)_tmp3A)->f1;
_LL68: for(0;_tmp3C != 0;_tmp3C=_tmp3C->tl){struct Cyc_List_List*_tmp3F;struct Cyc_List_List*
_tmp40;struct _tuple9 _tmp3E=Cyc_Absyndump_effects_split((void*)_tmp3C->hd);_tmp3F=
_tmp3E.f1;_tmp40=_tmp3E.f2;rgions=Cyc_List_imp_append(_tmp3F,rgions);effects=Cyc_List_imp_append(
_tmp40,effects);}goto _LL64;_LL69:;_LL6A: effects=({struct Cyc_List_List*_tmp41=
_cycalloc(sizeof(*_tmp41));_tmp41->hd=(void*)t;_tmp41->tl=effects;_tmp41;});goto
_LL64;_LL64:;}return({struct _tuple9 _tmp42;_tmp42.f1=rgions;_tmp42.f2=effects;
_tmp42;});}static void Cyc_Absyndump_dumpeff(void*t){struct Cyc_List_List*_tmp44;
struct Cyc_List_List*_tmp45;struct _tuple9 _tmp43=Cyc_Absyndump_effects_split(t);
_tmp44=_tmp43.f1;_tmp45=_tmp43.f2;_tmp44=Cyc_List_imp_rev(_tmp44);_tmp45=Cyc_List_imp_rev(
_tmp45);for(0;_tmp45 != 0;_tmp45=_tmp45->tl){Cyc_Absyndump_dumpntyp((void*)_tmp45->hd);
Cyc_Absyndump_dump_char((int)'+');}Cyc_Absyndump_dump_char((int)'{');for(0;
_tmp44 != 0;_tmp44=_tmp44->tl){Cyc_Absyndump_dumprgn((void*)_tmp44->hd);if(_tmp44->tl
!= 0)Cyc_Absyndump_dump_char((int)',');}Cyc_Absyndump_dump_char((int)'}');}void
Cyc_Absyndump_dumpntyp(void*t){void*_tmp46=t;struct Cyc_Absyn_Tvar*_tmp47;struct
Cyc_Core_Opt*_tmp48;struct Cyc_Core_Opt*_tmp49;int _tmp4A;struct Cyc_Core_Opt*
_tmp4B;struct Cyc_Core_Opt*_tmp4C;struct Cyc_Core_Opt _tmp4D;void*_tmp4E;int _tmp4F;
struct Cyc_Absyn_TunionInfo _tmp50;void*_tmp51;struct Cyc_List_List*_tmp52;void*
_tmp53;struct Cyc_Absyn_TunionFieldInfo _tmp54;void*_tmp55;struct Cyc_List_List*
_tmp56;void*_tmp57;void*_tmp58;void*_tmp59;void*_tmp5A;void*_tmp5B;void*_tmp5C;
void*_tmp5D;void*_tmp5E;void*_tmp5F;void*_tmp60;void*_tmp61;void*_tmp62;void*
_tmp63;void*_tmp64;void*_tmp65;void*_tmp66;void*_tmp67;void*_tmp68;void*_tmp69;
void*_tmp6A;void*_tmp6B;void*_tmp6C;void*_tmp6D;void*_tmp6E;void*_tmp6F;void*
_tmp70;void*_tmp71;void*_tmp72;void*_tmp73;void*_tmp74;int _tmp75;struct Cyc_List_List*
_tmp76;struct Cyc_Absyn_AggrInfo _tmp77;void*_tmp78;struct Cyc_List_List*_tmp79;
void*_tmp7A;struct Cyc_List_List*_tmp7B;struct _tuple0*_tmp7C;struct Cyc_List_List*
_tmp7D;struct _tuple0*_tmp7E;struct Cyc_List_List*_tmp7F;void*_tmp80;void*_tmp81;
int _tmp82;void*_tmp83;_LL6C: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 7)goto _LL6E;
_LL6D: goto _LL6F;_LL6E: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 8)goto _LL70;_LL6F:
goto _LL71;_LL70: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 4)goto _LL72;_LL71:
return;_LL72: if((int)_tmp46 != 0)goto _LL74;_LL73: Cyc_Absyndump_dump(({const char*
_tmp84="void";_tag_arr(_tmp84,sizeof(char),_get_zero_arr_size(_tmp84,5));}));
return;_LL74: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 1)goto _LL76;_tmp47=((
struct Cyc_Absyn_VarType_struct*)_tmp46)->f1;_LL75: Cyc_Absyndump_dump_str(_tmp47->name);
return;_LL76: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 0)goto _LL78;_tmp48=((
struct Cyc_Absyn_Evar_struct*)_tmp46)->f1;_tmp49=((struct Cyc_Absyn_Evar_struct*)
_tmp46)->f2;if(_tmp49 != 0)goto _LL78;_tmp4A=((struct Cyc_Absyn_Evar_struct*)_tmp46)->f3;
_LL77: Cyc_Absyndump_dump(({const char*_tmp85="%";_tag_arr(_tmp85,sizeof(char),
_get_zero_arr_size(_tmp85,2));}));if(_tmp48 == 0)Cyc_Absyndump_dump(({const char*
_tmp86="?";_tag_arr(_tmp86,sizeof(char),_get_zero_arr_size(_tmp86,2));}));else{
Cyc_Absyndump_dumpkind((void*)_tmp48->v);}Cyc_Absyndump_dump((struct _tagged_arr)({
struct Cyc_Int_pa_struct _tmp89;_tmp89.tag=1;_tmp89.f1=(unsigned int)_tmp4A;{void*
_tmp87[1]={& _tmp89};Cyc_aprintf(({const char*_tmp88="(%d)";_tag_arr(_tmp88,
sizeof(char),_get_zero_arr_size(_tmp88,5));}),_tag_arr(_tmp87,sizeof(void*),1));}}));
return;_LL78: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 0)goto _LL7A;_tmp4B=((
struct Cyc_Absyn_Evar_struct*)_tmp46)->f1;_tmp4C=((struct Cyc_Absyn_Evar_struct*)
_tmp46)->f2;if(_tmp4C == 0)goto _LL7A;_tmp4D=*_tmp4C;_tmp4E=(void*)_tmp4D.v;_tmp4F=((
struct Cyc_Absyn_Evar_struct*)_tmp46)->f3;_LL79: Cyc_Absyndump_dumpntyp(_tmp4E);
return;_LL7A: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 2)goto _LL7C;_tmp50=((
struct Cyc_Absyn_TunionType_struct*)_tmp46)->f1;_tmp51=(void*)_tmp50.tunion_info;
_tmp52=_tmp50.targs;_tmp53=(void*)_tmp50.rgn;_LL7B:{void*_tmp8A=_tmp51;struct Cyc_Absyn_UnknownTunionInfo
_tmp8B;struct _tuple0*_tmp8C;int _tmp8D;struct Cyc_Absyn_Tuniondecl**_tmp8E;struct
Cyc_Absyn_Tuniondecl*_tmp8F;struct Cyc_Absyn_Tuniondecl _tmp90;struct _tuple0*
_tmp91;int _tmp92;_LLBD: if(*((int*)_tmp8A)!= 0)goto _LLBF;_tmp8B=((struct Cyc_Absyn_UnknownTunion_struct*)
_tmp8A)->f1;_tmp8C=_tmp8B.name;_tmp8D=_tmp8B.is_xtunion;_LLBE: _tmp91=_tmp8C;
_tmp92=_tmp8D;goto _LLC0;_LLBF: if(*((int*)_tmp8A)!= 1)goto _LLBC;_tmp8E=((struct
Cyc_Absyn_KnownTunion_struct*)_tmp8A)->f1;_tmp8F=*_tmp8E;_tmp90=*_tmp8F;_tmp91=
_tmp90.name;_tmp92=_tmp90.is_xtunion;_LLC0: if(_tmp92)Cyc_Absyndump_dump(({const
char*_tmp93="xtunion ";_tag_arr(_tmp93,sizeof(char),_get_zero_arr_size(_tmp93,9));}));
else{Cyc_Absyndump_dump(({const char*_tmp94="tunion ";_tag_arr(_tmp94,sizeof(char),
_get_zero_arr_size(_tmp94,8));}));}{void*_tmp95=Cyc_Tcutil_compress(_tmp53);
_LLC2: if((int)_tmp95 != 2)goto _LLC4;_LLC3: goto _LLC1;_LLC4:;_LLC5: Cyc_Absyndump_dumptyp(
_tmp53);Cyc_Absyndump_dump(({const char*_tmp96=" ";_tag_arr(_tmp96,sizeof(char),
_get_zero_arr_size(_tmp96,2));}));goto _LLC1;_LLC1:;}Cyc_Absyndump_dumpqvar(
_tmp91);Cyc_Absyndump_dumptps(_tmp52);goto _LLBC;_LLBC:;}goto _LL6B;_LL7C: if(
_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 3)goto _LL7E;_tmp54=((struct Cyc_Absyn_TunionFieldType_struct*)
_tmp46)->f1;_tmp55=(void*)_tmp54.field_info;_tmp56=_tmp54.targs;_LL7D:{void*
_tmp97=_tmp55;struct Cyc_Absyn_UnknownTunionFieldInfo _tmp98;struct _tuple0*_tmp99;
struct _tuple0*_tmp9A;int _tmp9B;struct Cyc_Absyn_Tuniondecl*_tmp9C;struct Cyc_Absyn_Tuniondecl
_tmp9D;struct _tuple0*_tmp9E;int _tmp9F;struct Cyc_Absyn_Tunionfield*_tmpA0;struct
Cyc_Absyn_Tunionfield _tmpA1;struct _tuple0*_tmpA2;_LLC7: if(*((int*)_tmp97)!= 0)
goto _LLC9;_tmp98=((struct Cyc_Absyn_UnknownTunionfield_struct*)_tmp97)->f1;_tmp99=
_tmp98.tunion_name;_tmp9A=_tmp98.field_name;_tmp9B=_tmp98.is_xtunion;_LLC8:
_tmp9E=_tmp99;_tmp9F=_tmp9B;_tmpA2=_tmp9A;goto _LLCA;_LLC9: if(*((int*)_tmp97)!= 1)
goto _LLC6;_tmp9C=((struct Cyc_Absyn_KnownTunionfield_struct*)_tmp97)->f1;_tmp9D=*
_tmp9C;_tmp9E=_tmp9D.name;_tmp9F=_tmp9D.is_xtunion;_tmpA0=((struct Cyc_Absyn_KnownTunionfield_struct*)
_tmp97)->f2;_tmpA1=*_tmpA0;_tmpA2=_tmpA1.name;_LLCA: if(_tmp9F)Cyc_Absyndump_dump(({
const char*_tmpA3="xtunion ";_tag_arr(_tmpA3,sizeof(char),_get_zero_arr_size(
_tmpA3,9));}));else{Cyc_Absyndump_dump(({const char*_tmpA4="tunion ";_tag_arr(
_tmpA4,sizeof(char),_get_zero_arr_size(_tmpA4,8));}));}Cyc_Absyndump_dumpqvar(
_tmp9E);Cyc_Absyndump_dump(({const char*_tmpA5=".";_tag_arr(_tmpA5,sizeof(char),
_get_zero_arr_size(_tmpA5,2));}));Cyc_Absyndump_dumpqvar(_tmpA2);Cyc_Absyndump_dumptps(
_tmp56);goto _LLC6;_LLC6:;}goto _LL6B;_LL7E: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)
!= 5)goto _LL80;_tmp57=(void*)((struct Cyc_Absyn_IntType_struct*)_tmp46)->f1;if((
int)_tmp57 != 2)goto _LL80;_tmp58=(void*)((struct Cyc_Absyn_IntType_struct*)_tmp46)->f2;
if((int)_tmp58 != 2)goto _LL80;_LL7F: goto _LL81;_LL80: if(_tmp46 <= (void*)3?1:*((int*)
_tmp46)!= 5)goto _LL82;_tmp59=(void*)((struct Cyc_Absyn_IntType_struct*)_tmp46)->f1;
if((int)_tmp59 != 0)goto _LL82;_tmp5A=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f2;if((int)_tmp5A != 2)goto _LL82;_LL81: Cyc_Absyndump_dump(({const char*
_tmpA6="int";_tag_arr(_tmpA6,sizeof(char),_get_zero_arr_size(_tmpA6,4));}));
return;_LL82: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 5)goto _LL84;_tmp5B=(void*)((
struct Cyc_Absyn_IntType_struct*)_tmp46)->f1;if((int)_tmp5B != 2)goto _LL84;_tmp5C=(
void*)((struct Cyc_Absyn_IntType_struct*)_tmp46)->f2;if((int)_tmp5C != 0)goto _LL84;
_LL83: Cyc_Absyndump_dump(({const char*_tmpA7="char";_tag_arr(_tmpA7,sizeof(char),
_get_zero_arr_size(_tmpA7,5));}));return;_LL84: if(_tmp46 <= (void*)3?1:*((int*)
_tmp46)!= 5)goto _LL86;_tmp5D=(void*)((struct Cyc_Absyn_IntType_struct*)_tmp46)->f1;
if((int)_tmp5D != 0)goto _LL86;_tmp5E=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f2;if((int)_tmp5E != 0)goto _LL86;_LL85: Cyc_Absyndump_dump(({const char*
_tmpA8="signed char";_tag_arr(_tmpA8,sizeof(char),_get_zero_arr_size(_tmpA8,12));}));
return;_LL86: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 5)goto _LL88;_tmp5F=(void*)((
struct Cyc_Absyn_IntType_struct*)_tmp46)->f1;if((int)_tmp5F != 1)goto _LL88;_tmp60=(
void*)((struct Cyc_Absyn_IntType_struct*)_tmp46)->f2;if((int)_tmp60 != 0)goto _LL88;
_LL87: Cyc_Absyndump_dump(({const char*_tmpA9="unsigned char";_tag_arr(_tmpA9,
sizeof(char),_get_zero_arr_size(_tmpA9,14));}));return;_LL88: if(_tmp46 <= (void*)
3?1:*((int*)_tmp46)!= 5)goto _LL8A;_tmp61=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f1;if((int)_tmp61 != 2)goto _LL8A;_tmp62=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f2;if((int)_tmp62 != 1)goto _LL8A;_LL89: goto _LL8B;_LL8A: if(_tmp46 <= (void*)
3?1:*((int*)_tmp46)!= 5)goto _LL8C;_tmp63=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f1;if((int)_tmp63 != 0)goto _LL8C;_tmp64=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f2;if((int)_tmp64 != 1)goto _LL8C;_LL8B: Cyc_Absyndump_dump(({const char*
_tmpAA="short";_tag_arr(_tmpAA,sizeof(char),_get_zero_arr_size(_tmpAA,6));}));
return;_LL8C: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 5)goto _LL8E;_tmp65=(void*)((
struct Cyc_Absyn_IntType_struct*)_tmp46)->f1;if((int)_tmp65 != 1)goto _LL8E;_tmp66=(
void*)((struct Cyc_Absyn_IntType_struct*)_tmp46)->f2;if((int)_tmp66 != 1)goto _LL8E;
_LL8D: Cyc_Absyndump_dump(({const char*_tmpAB="unsigned short";_tag_arr(_tmpAB,
sizeof(char),_get_zero_arr_size(_tmpAB,15));}));return;_LL8E: if(_tmp46 <= (void*)
3?1:*((int*)_tmp46)!= 5)goto _LL90;_tmp67=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f1;if((int)_tmp67 != 1)goto _LL90;_tmp68=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f2;if((int)_tmp68 != 2)goto _LL90;_LL8F: Cyc_Absyndump_dump(({const char*
_tmpAC="unsigned int";_tag_arr(_tmpAC,sizeof(char),_get_zero_arr_size(_tmpAC,13));}));
return;_LL90: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 5)goto _LL92;_tmp69=(void*)((
struct Cyc_Absyn_IntType_struct*)_tmp46)->f1;if((int)_tmp69 != 2)goto _LL92;_tmp6A=(
void*)((struct Cyc_Absyn_IntType_struct*)_tmp46)->f2;if((int)_tmp6A != 3)goto _LL92;
if(!Cyc_Absyndump_to_VC)goto _LL92;_LL91: goto _LL93;_LL92: if(_tmp46 <= (void*)3?1:*((
int*)_tmp46)!= 5)goto _LL94;_tmp6B=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f1;if((int)_tmp6B != 0)goto _LL94;_tmp6C=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f2;if((int)_tmp6C != 3)goto _LL94;if(!Cyc_Absyndump_to_VC)goto _LL94;_LL93:
Cyc_Absyndump_dump(({const char*_tmpAD="__int64";_tag_arr(_tmpAD,sizeof(char),
_get_zero_arr_size(_tmpAD,8));}));return;_LL94: if(_tmp46 <= (void*)3?1:*((int*)
_tmp46)!= 5)goto _LL96;_tmp6D=(void*)((struct Cyc_Absyn_IntType_struct*)_tmp46)->f1;
if((int)_tmp6D != 2)goto _LL96;_tmp6E=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f2;if((int)_tmp6E != 3)goto _LL96;_LL95: goto _LL97;_LL96: if(_tmp46 <= (void*)
3?1:*((int*)_tmp46)!= 5)goto _LL98;_tmp6F=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f1;if((int)_tmp6F != 0)goto _LL98;_tmp70=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f2;if((int)_tmp70 != 3)goto _LL98;_LL97: Cyc_Absyndump_dump(({const char*
_tmpAE="long long";_tag_arr(_tmpAE,sizeof(char),_get_zero_arr_size(_tmpAE,10));}));
return;_LL98: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 5)goto _LL9A;_tmp71=(void*)((
struct Cyc_Absyn_IntType_struct*)_tmp46)->f1;if((int)_tmp71 != 1)goto _LL9A;_tmp72=(
void*)((struct Cyc_Absyn_IntType_struct*)_tmp46)->f2;if((int)_tmp72 != 3)goto _LL9A;
if(!Cyc_Absyndump_to_VC)goto _LL9A;_LL99: Cyc_Absyndump_dump(({const char*_tmpAF="unsigned __int64";
_tag_arr(_tmpAF,sizeof(char),_get_zero_arr_size(_tmpAF,17));}));return;_LL9A: if(
_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 5)goto _LL9C;_tmp73=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f1;if((int)_tmp73 != 1)goto _LL9C;_tmp74=(void*)((struct Cyc_Absyn_IntType_struct*)
_tmp46)->f2;if((int)_tmp74 != 3)goto _LL9C;_LL9B: Cyc_Absyndump_dump(({const char*
_tmpB0="unsigned long long";_tag_arr(_tmpB0,sizeof(char),_get_zero_arr_size(
_tmpB0,19));}));return;_LL9C: if((int)_tmp46 != 1)goto _LL9E;_LL9D: Cyc_Absyndump_dump(({
const char*_tmpB1="float";_tag_arr(_tmpB1,sizeof(char),_get_zero_arr_size(_tmpB1,
6));}));return;_LL9E: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 6)goto _LLA0;_tmp75=((
struct Cyc_Absyn_DoubleType_struct*)_tmp46)->f1;_LL9F: if(_tmp75)Cyc_Absyndump_dump(({
const char*_tmpB2="long double";_tag_arr(_tmpB2,sizeof(char),_get_zero_arr_size(
_tmpB2,12));}));else{Cyc_Absyndump_dump(({const char*_tmpB3="double";_tag_arr(
_tmpB3,sizeof(char),_get_zero_arr_size(_tmpB3,7));}));}return;_LLA0: if(_tmp46 <= (
void*)3?1:*((int*)_tmp46)!= 9)goto _LLA2;_tmp76=((struct Cyc_Absyn_TupleType_struct*)
_tmp46)->f1;_LLA1: Cyc_Absyndump_dump_char((int)'$');Cyc_Absyndump_dumpargs(
_tmp76);return;_LLA2: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 10)goto _LLA4;
_tmp77=((struct Cyc_Absyn_AggrType_struct*)_tmp46)->f1;_tmp78=(void*)_tmp77.aggr_info;
_tmp79=_tmp77.targs;_LLA3: {void*_tmpB5;struct _tuple0*_tmpB6;struct _tuple3 _tmpB4=
Cyc_Absyn_aggr_kinded_name(_tmp78);_tmpB5=_tmpB4.f1;_tmpB6=_tmpB4.f2;Cyc_Absyndump_dumpaggr_kind(
_tmpB5);Cyc_Absyndump_dumpqvar(_tmpB6);Cyc_Absyndump_dumptps(_tmp79);return;}
_LLA4: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 11)goto _LLA6;_tmp7A=(void*)((
struct Cyc_Absyn_AnonAggrType_struct*)_tmp46)->f1;_tmp7B=((struct Cyc_Absyn_AnonAggrType_struct*)
_tmp46)->f2;_LLA5: Cyc_Absyndump_dumpaggr_kind(_tmp7A);Cyc_Absyndump_dump_char((
int)'{');Cyc_Absyndump_dumpaggrfields(_tmp7B);Cyc_Absyndump_dump_char((int)'}');
return;_LLA6: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 12)goto _LLA8;_tmp7C=((
struct Cyc_Absyn_EnumType_struct*)_tmp46)->f1;_LLA7: Cyc_Absyndump_dump(({const
char*_tmpB7="enum ";_tag_arr(_tmpB7,sizeof(char),_get_zero_arr_size(_tmpB7,6));}));
Cyc_Absyndump_dumpqvar(_tmp7C);return;_LLA8: if(_tmp46 <= (void*)3?1:*((int*)
_tmp46)!= 13)goto _LLAA;_tmp7D=((struct Cyc_Absyn_AnonEnumType_struct*)_tmp46)->f1;
_LLA9: Cyc_Absyndump_dump(({const char*_tmpB8="enum {";_tag_arr(_tmpB8,sizeof(char),
_get_zero_arr_size(_tmpB8,7));}));Cyc_Absyndump_dumpenumfields(_tmp7D);Cyc_Absyndump_dump(({
const char*_tmpB9="}";_tag_arr(_tmpB9,sizeof(char),_get_zero_arr_size(_tmpB9,2));}));
return;_LLAA: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 16)goto _LLAC;_tmp7E=((
struct Cyc_Absyn_TypedefType_struct*)_tmp46)->f1;_tmp7F=((struct Cyc_Absyn_TypedefType_struct*)
_tmp46)->f2;_LLAB:(Cyc_Absyndump_dumpqvar(_tmp7E),Cyc_Absyndump_dumptps(_tmp7F));
return;_LLAC: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 14)goto _LLAE;_tmp80=(void*)((
struct Cyc_Absyn_SizeofType_struct*)_tmp46)->f1;_LLAD: Cyc_Absyndump_dump(({const
char*_tmpBA="sizeof_t<";_tag_arr(_tmpBA,sizeof(char),_get_zero_arr_size(_tmpBA,
10));}));Cyc_Absyndump_dumpntyp(_tmp80);Cyc_Absyndump_dump(({const char*_tmpBB=">";
_tag_arr(_tmpBB,sizeof(char),_get_zero_arr_size(_tmpBB,2));}));return;_LLAE: if(
_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 15)goto _LLB0;_tmp81=(void*)((struct Cyc_Absyn_RgnHandleType_struct*)
_tmp46)->f1;_LLAF: Cyc_Absyndump_dumprgn(_tmp81);return;_LLB0: if(_tmp46 <= (void*)
3?1:*((int*)_tmp46)!= 18)goto _LLB2;_tmp82=((struct Cyc_Absyn_TypeInt_struct*)
_tmp46)->f1;_LLB1: Cyc_Absyndump_dump((struct _tagged_arr)({struct Cyc_Int_pa_struct
_tmpBE;_tmpBE.tag=1;_tmpBE.f1=(unsigned int)_tmp82;{void*_tmpBC[1]={& _tmpBE};Cyc_aprintf(({
const char*_tmpBD="`%d";_tag_arr(_tmpBD,sizeof(char),_get_zero_arr_size(_tmpBD,4));}),
_tag_arr(_tmpBC,sizeof(void*),1));}}));return;_LLB2: if(_tmp46 <= (void*)3?1:*((
int*)_tmp46)!= 17)goto _LLB4;_tmp83=(void*)((struct Cyc_Absyn_TagType_struct*)
_tmp46)->f1;_LLB3: Cyc_Absyndump_dump(({const char*_tmpBF="tag_t<";_tag_arr(_tmpBF,
sizeof(char),_get_zero_arr_size(_tmpBF,7));}));Cyc_Absyndump_dumpntyp(_tmp83);
Cyc_Absyndump_dump(({const char*_tmpC0=">";_tag_arr(_tmpC0,sizeof(char),
_get_zero_arr_size(_tmpC0,2));}));return;_LLB4: if((int)_tmp46 != 2)goto _LLB6;
_LLB5: goto _LLB7;_LLB6: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 19)goto _LLB8;
_LLB7: goto _LLB9;_LLB8: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 21)goto _LLBA;
_LLB9: goto _LLBB;_LLBA: if(_tmp46 <= (void*)3?1:*((int*)_tmp46)!= 20)goto _LL6B;
_LLBB: return;_LL6B:;}void Cyc_Absyndump_dumpvaropt(struct Cyc_Core_Opt*vo){if(vo != 
0)Cyc_Absyndump_dump_str((struct _tagged_arr*)vo->v);}void Cyc_Absyndump_dumpfunarg(
struct _tuple1*t){((void(*)(struct Cyc_Absyn_Tqual,void*,void(*f)(struct Cyc_Core_Opt*),
struct Cyc_Core_Opt*))Cyc_Absyndump_dumptqtd)((*t).f2,(*t).f3,Cyc_Absyndump_dumpvaropt,(*
t).f1);}void Cyc_Absyndump_dump_rgncmp(struct _tuple7*cmp){struct _tuple7 _tmpC2;
void*_tmpC3;void*_tmpC4;struct _tuple7*_tmpC1=cmp;_tmpC2=*_tmpC1;_tmpC3=_tmpC2.f1;
_tmpC4=_tmpC2.f2;Cyc_Absyndump_dumpeff(_tmpC3);Cyc_Absyndump_dump_char((int)'>');
Cyc_Absyndump_dumprgn(_tmpC4);}void Cyc_Absyndump_dump_rgnpo(struct Cyc_List_List*
rgn_po){((void(*)(void(*f)(struct _tuple7*),struct Cyc_List_List*l,struct
_tagged_arr sep))Cyc_Absyndump_dump_sep)(Cyc_Absyndump_dump_rgncmp,rgn_po,({const
char*_tmpC5=",";_tag_arr(_tmpC5,sizeof(char),_get_zero_arr_size(_tmpC5,2));}));}
void Cyc_Absyndump_dumpfunargs(struct Cyc_List_List*args,int c_varargs,struct Cyc_Absyn_VarargInfo*
cyc_varargs,struct Cyc_Core_Opt*effopt,struct Cyc_List_List*rgn_po){Cyc_Absyndump_dump_char((
int)'(');for(0;args != 0;args=args->tl){Cyc_Absyndump_dumpfunarg((struct _tuple1*)
args->hd);if((args->tl != 0?1: c_varargs)?1: cyc_varargs != 0)Cyc_Absyndump_dump_char((
int)',');}if(c_varargs)Cyc_Absyndump_dump(({const char*_tmpC6="...";_tag_arr(
_tmpC6,sizeof(char),_get_zero_arr_size(_tmpC6,4));}));else{if(cyc_varargs != 0){
struct _tuple1*_tmpC7=({struct _tuple1*_tmpCA=_cycalloc(sizeof(*_tmpCA));_tmpCA->f1=
cyc_varargs->name;_tmpCA->f2=cyc_varargs->tq;_tmpCA->f3=(void*)cyc_varargs->type;
_tmpCA;});Cyc_Absyndump_dump(({const char*_tmpC8="...";_tag_arr(_tmpC8,sizeof(
char),_get_zero_arr_size(_tmpC8,4));}));if(cyc_varargs->inject)Cyc_Absyndump_dump(({
const char*_tmpC9=" inject ";_tag_arr(_tmpC9,sizeof(char),_get_zero_arr_size(
_tmpC9,9));}));Cyc_Absyndump_dumpfunarg(_tmpC7);}}if(effopt != 0){Cyc_Absyndump_dump_semi();
Cyc_Absyndump_dumpeff((void*)effopt->v);}if(rgn_po != 0){Cyc_Absyndump_dump_char((
int)':');Cyc_Absyndump_dump_rgnpo(rgn_po);}Cyc_Absyndump_dump_char((int)')');}
void Cyc_Absyndump_dumptyp(void*t){((void(*)(struct Cyc_Absyn_Tqual,void*,void(*f)(
int),int))Cyc_Absyndump_dumptqtd)(Cyc_Absyn_empty_tqual(),t,(void(*)(int x))Cyc_Absyndump_ignore,
0);}void Cyc_Absyndump_dumpdesignator(void*d){void*_tmpCB=d;struct Cyc_Absyn_Exp*
_tmpCC;struct _tagged_arr*_tmpCD;_LLCC: if(*((int*)_tmpCB)!= 0)goto _LLCE;_tmpCC=((
struct Cyc_Absyn_ArrayElement_struct*)_tmpCB)->f1;_LLCD: Cyc_Absyndump_dump(({
const char*_tmpCE=".[";_tag_arr(_tmpCE,sizeof(char),_get_zero_arr_size(_tmpCE,3));}));
Cyc_Absyndump_dumpexp(_tmpCC);Cyc_Absyndump_dump_char((int)']');goto _LLCB;_LLCE:
if(*((int*)_tmpCB)!= 1)goto _LLCB;_tmpCD=((struct Cyc_Absyn_FieldName_struct*)
_tmpCB)->f1;_LLCF: Cyc_Absyndump_dump_char((int)'.');Cyc_Absyndump_dump_nospace(*
_tmpCD);goto _LLCB;_LLCB:;}struct _tuple10{struct Cyc_List_List*f1;struct Cyc_Absyn_Exp*
f2;};void Cyc_Absyndump_dumpde(struct _tuple10*de){Cyc_Absyndump_egroup(Cyc_Absyndump_dumpdesignator,(*
de).f1,({const char*_tmpCF="";_tag_arr(_tmpCF,sizeof(char),_get_zero_arr_size(
_tmpCF,1));}),({const char*_tmpD0="=";_tag_arr(_tmpD0,sizeof(char),
_get_zero_arr_size(_tmpD0,2));}),({const char*_tmpD1="=";_tag_arr(_tmpD1,sizeof(
char),_get_zero_arr_size(_tmpD1,2));}));Cyc_Absyndump_dumpexp((*de).f2);}void Cyc_Absyndump_dumpexps_prec(
int inprec,struct Cyc_List_List*es){((void(*)(void(*f)(int,struct Cyc_Absyn_Exp*),
int env,struct Cyc_List_List*l,struct _tagged_arr start,struct _tagged_arr end,struct
_tagged_arr sep))Cyc_Absyndump_group_c)(Cyc_Absyndump_dumpexp_prec,inprec,es,({
const char*_tmpD2="";_tag_arr(_tmpD2,sizeof(char),_get_zero_arr_size(_tmpD2,1));}),({
const char*_tmpD3="";_tag_arr(_tmpD3,sizeof(char),_get_zero_arr_size(_tmpD3,1));}),({
const char*_tmpD4=",";_tag_arr(_tmpD4,sizeof(char),_get_zero_arr_size(_tmpD4,2));}));}
void Cyc_Absyndump_dumpexp_prec(int inprec,struct Cyc_Absyn_Exp*e){int myprec=Cyc_Absynpp_exp_prec(
e);if(inprec >= myprec)Cyc_Absyndump_dump_nospace(({const char*_tmpD5="(";_tag_arr(
_tmpD5,sizeof(char),_get_zero_arr_size(_tmpD5,2));}));{void*_tmpD6=(void*)e->r;
void*_tmpD7;void*_tmpD8;char _tmpD9;void*_tmpDA;void*_tmpDB;short _tmpDC;void*
_tmpDD;void*_tmpDE;int _tmpDF;void*_tmpE0;void*_tmpE1;int _tmpE2;void*_tmpE3;void*
_tmpE4;int _tmpE5;void*_tmpE6;void*_tmpE7;long long _tmpE8;void*_tmpE9;struct
_tagged_arr _tmpEA;void*_tmpEB;void*_tmpEC;struct _tagged_arr _tmpED;struct _tuple0*
_tmpEE;struct _tuple0*_tmpEF;void*_tmpF0;struct Cyc_List_List*_tmpF1;struct Cyc_Absyn_Exp*
_tmpF2;struct Cyc_Core_Opt*_tmpF3;struct Cyc_Absyn_Exp*_tmpF4;struct Cyc_Absyn_Exp*
_tmpF5;void*_tmpF6;struct Cyc_Absyn_Exp*_tmpF7;void*_tmpF8;struct Cyc_Absyn_Exp*
_tmpF9;void*_tmpFA;struct Cyc_Absyn_Exp*_tmpFB;void*_tmpFC;struct Cyc_Absyn_Exp*
_tmpFD;struct Cyc_Absyn_Exp*_tmpFE;struct Cyc_Absyn_Exp*_tmpFF;struct Cyc_Absyn_Exp*
_tmp100;struct Cyc_Absyn_Exp*_tmp101;struct Cyc_Absyn_Exp*_tmp102;struct Cyc_List_List*
_tmp103;struct Cyc_Absyn_Exp*_tmp104;struct Cyc_List_List*_tmp105;struct Cyc_Absyn_Exp*
_tmp106;struct Cyc_Absyn_Exp*_tmp107;struct Cyc_Absyn_Exp*_tmp108;void*_tmp109;
struct Cyc_Absyn_Exp*_tmp10A;struct Cyc_Absyn_Exp*_tmp10B;struct Cyc_Absyn_Exp*
_tmp10C;struct Cyc_Absyn_Exp*_tmp10D;void*_tmp10E;struct Cyc_Absyn_Exp*_tmp10F;
void*_tmp110;void*_tmp111;struct _tagged_arr*_tmp112;void*_tmp113;void*_tmp114;
unsigned int _tmp115;struct Cyc_List_List*_tmp116;void*_tmp117;struct Cyc_Absyn_Exp*
_tmp118;struct Cyc_Absyn_Exp*_tmp119;struct _tagged_arr*_tmp11A;struct Cyc_Absyn_Exp*
_tmp11B;struct _tagged_arr*_tmp11C;struct Cyc_Absyn_Exp*_tmp11D;struct Cyc_Absyn_Exp*
_tmp11E;struct Cyc_List_List*_tmp11F;struct _tuple1*_tmp120;struct Cyc_List_List*
_tmp121;struct Cyc_List_List*_tmp122;struct Cyc_Absyn_Vardecl*_tmp123;struct Cyc_Absyn_Exp*
_tmp124;struct Cyc_Absyn_Exp*_tmp125;struct _tuple0*_tmp126;struct Cyc_List_List*
_tmp127;struct Cyc_List_List*_tmp128;struct Cyc_List_List*_tmp129;struct Cyc_List_List*
_tmp12A;struct Cyc_Absyn_Tunionfield*_tmp12B;struct _tuple0*_tmp12C;struct _tuple0*
_tmp12D;struct Cyc_Absyn_MallocInfo _tmp12E;int _tmp12F;struct Cyc_Absyn_Exp*_tmp130;
void**_tmp131;struct Cyc_Absyn_Exp*_tmp132;struct Cyc_Core_Opt*_tmp133;struct Cyc_List_List*
_tmp134;struct Cyc_Absyn_Stmt*_tmp135;struct Cyc_Absyn_Fndecl*_tmp136;struct Cyc_Absyn_Exp*
_tmp137;_LLD1: if(*((int*)_tmpD6)!= 0)goto _LLD3;_tmpD7=(void*)((struct Cyc_Absyn_Const_e_struct*)
_tmpD6)->f1;if(_tmpD7 <= (void*)1?1:*((int*)_tmpD7)!= 0)goto _LLD3;_tmpD8=(void*)((
struct Cyc_Absyn_Char_c_struct*)_tmpD7)->f1;_tmpD9=((struct Cyc_Absyn_Char_c_struct*)
_tmpD7)->f2;_LLD2: Cyc_Absyndump_dump_char((int)'\'');Cyc_Absyndump_dump_nospace(
Cyc_Absynpp_char_escape(_tmpD9));Cyc_Absyndump_dump_char((int)'\'');goto _LLD0;
_LLD3: if(*((int*)_tmpD6)!= 0)goto _LLD5;_tmpDA=(void*)((struct Cyc_Absyn_Const_e_struct*)
_tmpD6)->f1;if(_tmpDA <= (void*)1?1:*((int*)_tmpDA)!= 1)goto _LLD5;_tmpDB=(void*)((
struct Cyc_Absyn_Short_c_struct*)_tmpDA)->f1;_tmpDC=((struct Cyc_Absyn_Short_c_struct*)
_tmpDA)->f2;_LLD4: Cyc_Absyndump_dump((struct _tagged_arr)({struct Cyc_Int_pa_struct
_tmp13A;_tmp13A.tag=1;_tmp13A.f1=(unsigned int)((int)_tmpDC);{void*_tmp138[1]={&
_tmp13A};Cyc_aprintf(({const char*_tmp139="%d";_tag_arr(_tmp139,sizeof(char),
_get_zero_arr_size(_tmp139,3));}),_tag_arr(_tmp138,sizeof(void*),1));}}));goto
_LLD0;_LLD5: if(*((int*)_tmpD6)!= 0)goto _LLD7;_tmpDD=(void*)((struct Cyc_Absyn_Const_e_struct*)
_tmpD6)->f1;if(_tmpDD <= (void*)1?1:*((int*)_tmpDD)!= 2)goto _LLD7;_tmpDE=(void*)((
struct Cyc_Absyn_Int_c_struct*)_tmpDD)->f1;if((int)_tmpDE != 2)goto _LLD7;_tmpDF=((
struct Cyc_Absyn_Int_c_struct*)_tmpDD)->f2;_LLD6: _tmpE2=_tmpDF;goto _LLD8;_LLD7:
if(*((int*)_tmpD6)!= 0)goto _LLD9;_tmpE0=(void*)((struct Cyc_Absyn_Const_e_struct*)
_tmpD6)->f1;if(_tmpE0 <= (void*)1?1:*((int*)_tmpE0)!= 2)goto _LLD9;_tmpE1=(void*)((
struct Cyc_Absyn_Int_c_struct*)_tmpE0)->f1;if((int)_tmpE1 != 0)goto _LLD9;_tmpE2=((
struct Cyc_Absyn_Int_c_struct*)_tmpE0)->f2;_LLD8: Cyc_Absyndump_dump((struct
_tagged_arr)({struct Cyc_Int_pa_struct _tmp13D;_tmp13D.tag=1;_tmp13D.f1=(
unsigned int)_tmpE2;{void*_tmp13B[1]={& _tmp13D};Cyc_aprintf(({const char*_tmp13C="%d";
_tag_arr(_tmp13C,sizeof(char),_get_zero_arr_size(_tmp13C,3));}),_tag_arr(_tmp13B,
sizeof(void*),1));}}));goto _LLD0;_LLD9: if(*((int*)_tmpD6)!= 0)goto _LLDB;_tmpE3=(
void*)((struct Cyc_Absyn_Const_e_struct*)_tmpD6)->f1;if(_tmpE3 <= (void*)1?1:*((
int*)_tmpE3)!= 2)goto _LLDB;_tmpE4=(void*)((struct Cyc_Absyn_Int_c_struct*)_tmpE3)->f1;
if((int)_tmpE4 != 1)goto _LLDB;_tmpE5=((struct Cyc_Absyn_Int_c_struct*)_tmpE3)->f2;
_LLDA: Cyc_Absyndump_dump((struct _tagged_arr)({struct Cyc_Int_pa_struct _tmp140;
_tmp140.tag=1;_tmp140.f1=(unsigned int)_tmpE5;{void*_tmp13E[1]={& _tmp140};Cyc_aprintf(({
const char*_tmp13F="%u";_tag_arr(_tmp13F,sizeof(char),_get_zero_arr_size(_tmp13F,
3));}),_tag_arr(_tmp13E,sizeof(void*),1));}}));goto _LLD0;_LLDB: if(*((int*)_tmpD6)
!= 0)goto _LLDD;_tmpE6=(void*)((struct Cyc_Absyn_Const_e_struct*)_tmpD6)->f1;if(
_tmpE6 <= (void*)1?1:*((int*)_tmpE6)!= 3)goto _LLDD;_tmpE7=(void*)((struct Cyc_Absyn_LongLong_c_struct*)
_tmpE6)->f1;_tmpE8=((struct Cyc_Absyn_LongLong_c_struct*)_tmpE6)->f2;_LLDC: Cyc_Absyndump_dump(({
const char*_tmp141="<<FIX LONG LONG CONSTANT>>";_tag_arr(_tmp141,sizeof(char),
_get_zero_arr_size(_tmp141,27));}));goto _LLD0;_LLDD: if(*((int*)_tmpD6)!= 0)goto
_LLDF;_tmpE9=(void*)((struct Cyc_Absyn_Const_e_struct*)_tmpD6)->f1;if(_tmpE9 <= (
void*)1?1:*((int*)_tmpE9)!= 4)goto _LLDF;_tmpEA=((struct Cyc_Absyn_Float_c_struct*)
_tmpE9)->f1;_LLDE: Cyc_Absyndump_dump(_tmpEA);goto _LLD0;_LLDF: if(*((int*)_tmpD6)
!= 0)goto _LLE1;_tmpEB=(void*)((struct Cyc_Absyn_Const_e_struct*)_tmpD6)->f1;if((
int)_tmpEB != 0)goto _LLE1;_LLE0: Cyc_Absyndump_dump(({const char*_tmp142="NULL";
_tag_arr(_tmp142,sizeof(char),_get_zero_arr_size(_tmp142,5));}));goto _LLD0;_LLE1:
if(*((int*)_tmpD6)!= 0)goto _LLE3;_tmpEC=(void*)((struct Cyc_Absyn_Const_e_struct*)
_tmpD6)->f1;if(_tmpEC <= (void*)1?1:*((int*)_tmpEC)!= 5)goto _LLE3;_tmpED=((struct
Cyc_Absyn_String_c_struct*)_tmpEC)->f1;_LLE2: Cyc_Absyndump_dump_char((int)'"');
Cyc_Absyndump_dump_nospace(Cyc_Absynpp_string_escape(_tmpED));Cyc_Absyndump_dump_char((
int)'"');goto _LLD0;_LLE3: if(*((int*)_tmpD6)!= 2)goto _LLE5;_tmpEE=((struct Cyc_Absyn_UnknownId_e_struct*)
_tmpD6)->f1;_LLE4: _tmpEF=_tmpEE;goto _LLE6;_LLE5: if(*((int*)_tmpD6)!= 1)goto _LLE7;
_tmpEF=((struct Cyc_Absyn_Var_e_struct*)_tmpD6)->f1;_LLE6: Cyc_Absyndump_dumpqvar(
_tmpEF);goto _LLD0;_LLE7: if(*((int*)_tmpD6)!= 3)goto _LLE9;_tmpF0=(void*)((struct
Cyc_Absyn_Primop_e_struct*)_tmpD6)->f1;_tmpF1=((struct Cyc_Absyn_Primop_e_struct*)
_tmpD6)->f2;_LLE8: {struct _tagged_arr _tmp143=Cyc_Absynpp_prim2str(_tmpF0);
switch(((int(*)(struct Cyc_List_List*x))Cyc_List_length)(_tmpF1)){case 1: _LL135:
if(_tmpF0 == (void*)((void*)19)){Cyc_Absyndump_dumpexp_prec(myprec,(struct Cyc_Absyn_Exp*)((
struct Cyc_List_List*)_check_null(_tmpF1))->hd);Cyc_Absyndump_dump(({const char*
_tmp144=".size";_tag_arr(_tmp144,sizeof(char),_get_zero_arr_size(_tmp144,6));}));}
else{Cyc_Absyndump_dump(_tmp143);Cyc_Absyndump_dumpexp_prec(myprec,(struct Cyc_Absyn_Exp*)((
struct Cyc_List_List*)_check_null(_tmpF1))->hd);}break;case 2: _LL136: Cyc_Absyndump_dumpexp_prec(
myprec,(struct Cyc_Absyn_Exp*)((struct Cyc_List_List*)_check_null(_tmpF1))->hd);
Cyc_Absyndump_dump(_tmp143);Cyc_Absyndump_dump_char((int)' ');Cyc_Absyndump_dumpexp_prec(
myprec,(struct Cyc_Absyn_Exp*)((struct Cyc_List_List*)_check_null(_tmpF1->tl))->hd);
break;default: _LL137:(int)_throw((void*)({struct Cyc_Core_Failure_struct*_tmp145=
_cycalloc(sizeof(*_tmp145));_tmp145[0]=({struct Cyc_Core_Failure_struct _tmp146;
_tmp146.tag=Cyc_Core_Failure;_tmp146.f1=({const char*_tmp147="Absyndump -- Bad number of arguments to primop";
_tag_arr(_tmp147,sizeof(char),_get_zero_arr_size(_tmp147,47));});_tmp146;});
_tmp145;}));}goto _LLD0;}_LLE9: if(*((int*)_tmpD6)!= 4)goto _LLEB;_tmpF2=((struct
Cyc_Absyn_AssignOp_e_struct*)_tmpD6)->f1;_tmpF3=((struct Cyc_Absyn_AssignOp_e_struct*)
_tmpD6)->f2;_tmpF4=((struct Cyc_Absyn_AssignOp_e_struct*)_tmpD6)->f3;_LLEA: Cyc_Absyndump_dumpexp_prec(
myprec,_tmpF2);if(_tmpF3 != 0)Cyc_Absyndump_dump(Cyc_Absynpp_prim2str((void*)
_tmpF3->v));Cyc_Absyndump_dump_nospace(({const char*_tmp148="=";_tag_arr(_tmp148,
sizeof(char),_get_zero_arr_size(_tmp148,2));}));Cyc_Absyndump_dumpexp_prec(
myprec,_tmpF4);goto _LLD0;_LLEB: if(*((int*)_tmpD6)!= 5)goto _LLED;_tmpF5=((struct
Cyc_Absyn_Increment_e_struct*)_tmpD6)->f1;_tmpF6=(void*)((struct Cyc_Absyn_Increment_e_struct*)
_tmpD6)->f2;if((int)_tmpF6 != 0)goto _LLED;_LLEC: Cyc_Absyndump_dump(({const char*
_tmp149="++";_tag_arr(_tmp149,sizeof(char),_get_zero_arr_size(_tmp149,3));}));
Cyc_Absyndump_dumpexp_prec(myprec,_tmpF5);goto _LLD0;_LLED: if(*((int*)_tmpD6)!= 5)
goto _LLEF;_tmpF7=((struct Cyc_Absyn_Increment_e_struct*)_tmpD6)->f1;_tmpF8=(void*)((
struct Cyc_Absyn_Increment_e_struct*)_tmpD6)->f2;if((int)_tmpF8 != 2)goto _LLEF;
_LLEE: Cyc_Absyndump_dump(({const char*_tmp14A="--";_tag_arr(_tmp14A,sizeof(char),
_get_zero_arr_size(_tmp14A,3));}));Cyc_Absyndump_dumpexp_prec(myprec,_tmpF7);
goto _LLD0;_LLEF: if(*((int*)_tmpD6)!= 5)goto _LLF1;_tmpF9=((struct Cyc_Absyn_Increment_e_struct*)
_tmpD6)->f1;_tmpFA=(void*)((struct Cyc_Absyn_Increment_e_struct*)_tmpD6)->f2;if((
int)_tmpFA != 1)goto _LLF1;_LLF0: Cyc_Absyndump_dumpexp_prec(myprec,_tmpF9);Cyc_Absyndump_dump(({
const char*_tmp14B="++";_tag_arr(_tmp14B,sizeof(char),_get_zero_arr_size(_tmp14B,
3));}));goto _LLD0;_LLF1: if(*((int*)_tmpD6)!= 5)goto _LLF3;_tmpFB=((struct Cyc_Absyn_Increment_e_struct*)
_tmpD6)->f1;_tmpFC=(void*)((struct Cyc_Absyn_Increment_e_struct*)_tmpD6)->f2;if((
int)_tmpFC != 3)goto _LLF3;_LLF2: Cyc_Absyndump_dumpexp_prec(myprec,_tmpFB);Cyc_Absyndump_dump(({
const char*_tmp14C="--";_tag_arr(_tmp14C,sizeof(char),_get_zero_arr_size(_tmp14C,
3));}));goto _LLD0;_LLF3: if(*((int*)_tmpD6)!= 6)goto _LLF5;_tmpFD=((struct Cyc_Absyn_Conditional_e_struct*)
_tmpD6)->f1;_tmpFE=((struct Cyc_Absyn_Conditional_e_struct*)_tmpD6)->f2;_tmpFF=((
struct Cyc_Absyn_Conditional_e_struct*)_tmpD6)->f3;_LLF4: Cyc_Absyndump_dumpexp_prec(
myprec,_tmpFD);Cyc_Absyndump_dump_char((int)'?');Cyc_Absyndump_dumpexp_prec(0,
_tmpFE);Cyc_Absyndump_dump_char((int)':');Cyc_Absyndump_dumpexp_prec(myprec,
_tmpFF);goto _LLD0;_LLF5: if(*((int*)_tmpD6)!= 7)goto _LLF7;_tmp100=((struct Cyc_Absyn_SeqExp_e_struct*)
_tmpD6)->f1;_tmp101=((struct Cyc_Absyn_SeqExp_e_struct*)_tmpD6)->f2;_LLF6: Cyc_Absyndump_dump_char((
int)'(');Cyc_Absyndump_dumpexp_prec(myprec,_tmp100);Cyc_Absyndump_dump_char((int)',');
Cyc_Absyndump_dumpexp_prec(myprec,_tmp101);Cyc_Absyndump_dump_char((int)')');
goto _LLD0;_LLF7: if(*((int*)_tmpD6)!= 8)goto _LLF9;_tmp102=((struct Cyc_Absyn_UnknownCall_e_struct*)
_tmpD6)->f1;_tmp103=((struct Cyc_Absyn_UnknownCall_e_struct*)_tmpD6)->f2;_LLF8:
_tmp104=_tmp102;_tmp105=_tmp103;goto _LLFA;_LLF9: if(*((int*)_tmpD6)!= 9)goto _LLFB;
_tmp104=((struct Cyc_Absyn_FnCall_e_struct*)_tmpD6)->f1;_tmp105=((struct Cyc_Absyn_FnCall_e_struct*)
_tmpD6)->f2;_LLFA: Cyc_Absyndump_dumpexp_prec(myprec,_tmp104);Cyc_Absyndump_dump_nospace(({
const char*_tmp14D="(";_tag_arr(_tmp14D,sizeof(char),_get_zero_arr_size(_tmp14D,2));}));
Cyc_Absyndump_dumpexps_prec(20,_tmp105);Cyc_Absyndump_dump_nospace(({const char*
_tmp14E=")";_tag_arr(_tmp14E,sizeof(char),_get_zero_arr_size(_tmp14E,2));}));
goto _LLD0;_LLFB: if(*((int*)_tmpD6)!= 10)goto _LLFD;_tmp106=((struct Cyc_Absyn_Throw_e_struct*)
_tmpD6)->f1;_LLFC: Cyc_Absyndump_dump(({const char*_tmp14F="throw";_tag_arr(
_tmp14F,sizeof(char),_get_zero_arr_size(_tmp14F,6));}));Cyc_Absyndump_dumpexp_prec(
myprec,_tmp106);goto _LLD0;_LLFD: if(*((int*)_tmpD6)!= 11)goto _LLFF;_tmp107=((
struct Cyc_Absyn_NoInstantiate_e_struct*)_tmpD6)->f1;_LLFE: _tmp108=_tmp107;goto
_LL100;_LLFF: if(*((int*)_tmpD6)!= 12)goto _LL101;_tmp108=((struct Cyc_Absyn_Instantiate_e_struct*)
_tmpD6)->f1;_LL100: Cyc_Absyndump_dumpexp_prec(inprec,_tmp108);goto _LLD0;_LL101:
if(*((int*)_tmpD6)!= 13)goto _LL103;_tmp109=(void*)((struct Cyc_Absyn_Cast_e_struct*)
_tmpD6)->f1;_tmp10A=((struct Cyc_Absyn_Cast_e_struct*)_tmpD6)->f2;_LL102: Cyc_Absyndump_dump_char((
int)'(');Cyc_Absyndump_dumptyp(_tmp109);Cyc_Absyndump_dump_char((int)')');Cyc_Absyndump_dumpexp_prec(
myprec,_tmp10A);goto _LLD0;_LL103: if(*((int*)_tmpD6)!= 14)goto _LL105;_tmp10B=((
struct Cyc_Absyn_Address_e_struct*)_tmpD6)->f1;_LL104: Cyc_Absyndump_dump_char((
int)'&');Cyc_Absyndump_dumpexp_prec(myprec,_tmp10B);goto _LLD0;_LL105: if(*((int*)
_tmpD6)!= 15)goto _LL107;_tmp10C=((struct Cyc_Absyn_New_e_struct*)_tmpD6)->f1;
_tmp10D=((struct Cyc_Absyn_New_e_struct*)_tmpD6)->f2;_LL106: Cyc_Absyndump_dump(({
const char*_tmp150="new ";_tag_arr(_tmp150,sizeof(char),_get_zero_arr_size(
_tmp150,5));}));Cyc_Absyndump_dumpexp_prec(myprec,_tmp10D);goto _LLD0;_LL107: if(*((
int*)_tmpD6)!= 16)goto _LL109;_tmp10E=(void*)((struct Cyc_Absyn_Sizeoftyp_e_struct*)
_tmpD6)->f1;_LL108: Cyc_Absyndump_dump(({const char*_tmp151="sizeof(";_tag_arr(
_tmp151,sizeof(char),_get_zero_arr_size(_tmp151,8));}));Cyc_Absyndump_dumptyp(
_tmp10E);Cyc_Absyndump_dump_char((int)')');goto _LLD0;_LL109: if(*((int*)_tmpD6)!= 
17)goto _LL10B;_tmp10F=((struct Cyc_Absyn_Sizeofexp_e_struct*)_tmpD6)->f1;_LL10A:
Cyc_Absyndump_dump(({const char*_tmp152="sizeof(";_tag_arr(_tmp152,sizeof(char),
_get_zero_arr_size(_tmp152,8));}));Cyc_Absyndump_dumpexp(_tmp10F);Cyc_Absyndump_dump_char((
int)')');goto _LLD0;_LL10B: if(*((int*)_tmpD6)!= 18)goto _LL10D;_tmp110=(void*)((
struct Cyc_Absyn_Offsetof_e_struct*)_tmpD6)->f1;_tmp111=(void*)((struct Cyc_Absyn_Offsetof_e_struct*)
_tmpD6)->f2;if(*((int*)_tmp111)!= 0)goto _LL10D;_tmp112=((struct Cyc_Absyn_StructField_struct*)
_tmp111)->f1;_LL10C: Cyc_Absyndump_dump(({const char*_tmp153="offsetof(";_tag_arr(
_tmp153,sizeof(char),_get_zero_arr_size(_tmp153,10));}));Cyc_Absyndump_dumptyp(
_tmp110);Cyc_Absyndump_dump_char((int)',');Cyc_Absyndump_dump_nospace(*_tmp112);
Cyc_Absyndump_dump_char((int)')');goto _LLD0;_LL10D: if(*((int*)_tmpD6)!= 18)goto
_LL10F;_tmp113=(void*)((struct Cyc_Absyn_Offsetof_e_struct*)_tmpD6)->f1;_tmp114=(
void*)((struct Cyc_Absyn_Offsetof_e_struct*)_tmpD6)->f2;if(*((int*)_tmp114)!= 1)
goto _LL10F;_tmp115=((struct Cyc_Absyn_TupleIndex_struct*)_tmp114)->f1;_LL10E: Cyc_Absyndump_dump(({
const char*_tmp154="offsetof(";_tag_arr(_tmp154,sizeof(char),_get_zero_arr_size(
_tmp154,10));}));Cyc_Absyndump_dumptyp(_tmp113);Cyc_Absyndump_dump_char((int)',');
Cyc_Absyndump_dump((struct _tagged_arr)({struct Cyc_Int_pa_struct _tmp157;_tmp157.tag=
1;_tmp157.f1=(unsigned int)((int)_tmp115);{void*_tmp155[1]={& _tmp157};Cyc_aprintf(({
const char*_tmp156="%d";_tag_arr(_tmp156,sizeof(char),_get_zero_arr_size(_tmp156,
3));}),_tag_arr(_tmp155,sizeof(void*),1));}}));Cyc_Absyndump_dump_char((int)')');
goto _LLD0;_LL10F: if(*((int*)_tmpD6)!= 19)goto _LL111;_tmp116=((struct Cyc_Absyn_Gentyp_e_struct*)
_tmpD6)->f1;_tmp117=(void*)((struct Cyc_Absyn_Gentyp_e_struct*)_tmpD6)->f2;_LL110:
Cyc_Absyndump_dump(({const char*_tmp158="__gen(";_tag_arr(_tmp158,sizeof(char),
_get_zero_arr_size(_tmp158,7));}));Cyc_Absyndump_dumptvars(_tmp116);Cyc_Absyndump_dumptyp(
_tmp117);Cyc_Absyndump_dump_char((int)')');goto _LLD0;_LL111: if(*((int*)_tmpD6)!= 
20)goto _LL113;_tmp118=((struct Cyc_Absyn_Deref_e_struct*)_tmpD6)->f1;_LL112: Cyc_Absyndump_dump_char((
int)'*');Cyc_Absyndump_dumpexp_prec(myprec,_tmp118);goto _LLD0;_LL113: if(*((int*)
_tmpD6)!= 21)goto _LL115;_tmp119=((struct Cyc_Absyn_AggrMember_e_struct*)_tmpD6)->f1;
_tmp11A=((struct Cyc_Absyn_AggrMember_e_struct*)_tmpD6)->f2;_LL114: Cyc_Absyndump_dumpexp_prec(
myprec,_tmp119);Cyc_Absyndump_dump_char((int)'.');Cyc_Absyndump_dump_nospace(*
_tmp11A);goto _LLD0;_LL115: if(*((int*)_tmpD6)!= 22)goto _LL117;_tmp11B=((struct Cyc_Absyn_AggrArrow_e_struct*)
_tmpD6)->f1;_tmp11C=((struct Cyc_Absyn_AggrArrow_e_struct*)_tmpD6)->f2;_LL116: Cyc_Absyndump_dumpexp_prec(
myprec,_tmp11B);Cyc_Absyndump_dump_nospace(({const char*_tmp159="->";_tag_arr(
_tmp159,sizeof(char),_get_zero_arr_size(_tmp159,3));}));Cyc_Absyndump_dump_nospace(*
_tmp11C);goto _LLD0;_LL117: if(*((int*)_tmpD6)!= 23)goto _LL119;_tmp11D=((struct Cyc_Absyn_Subscript_e_struct*)
_tmpD6)->f1;_tmp11E=((struct Cyc_Absyn_Subscript_e_struct*)_tmpD6)->f2;_LL118: Cyc_Absyndump_dumpexp_prec(
myprec,_tmp11D);Cyc_Absyndump_dump_char((int)'[');Cyc_Absyndump_dumpexp(_tmp11E);
Cyc_Absyndump_dump_char((int)']');goto _LLD0;_LL119: if(*((int*)_tmpD6)!= 24)goto
_LL11B;_tmp11F=((struct Cyc_Absyn_Tuple_e_struct*)_tmpD6)->f1;_LL11A: Cyc_Absyndump_dump(({
const char*_tmp15A="$(";_tag_arr(_tmp15A,sizeof(char),_get_zero_arr_size(_tmp15A,
3));}));Cyc_Absyndump_dumpexps_prec(20,_tmp11F);Cyc_Absyndump_dump_char((int)')');
goto _LLD0;_LL11B: if(*((int*)_tmpD6)!= 25)goto _LL11D;_tmp120=((struct Cyc_Absyn_CompoundLit_e_struct*)
_tmpD6)->f1;_tmp121=((struct Cyc_Absyn_CompoundLit_e_struct*)_tmpD6)->f2;_LL11C:
Cyc_Absyndump_dump_char((int)'(');Cyc_Absyndump_dumptyp((*_tmp120).f3);Cyc_Absyndump_dump_char((
int)')');((void(*)(void(*f)(struct _tuple10*),struct Cyc_List_List*l,struct
_tagged_arr start,struct _tagged_arr end,struct _tagged_arr sep))Cyc_Absyndump_group)(
Cyc_Absyndump_dumpde,_tmp121,({const char*_tmp15B="{";_tag_arr(_tmp15B,sizeof(
char),_get_zero_arr_size(_tmp15B,2));}),({const char*_tmp15C="}";_tag_arr(_tmp15C,
sizeof(char),_get_zero_arr_size(_tmp15C,2));}),({const char*_tmp15D=",";_tag_arr(
_tmp15D,sizeof(char),_get_zero_arr_size(_tmp15D,2));}));goto _LLD0;_LL11D: if(*((
int*)_tmpD6)!= 26)goto _LL11F;_tmp122=((struct Cyc_Absyn_Array_e_struct*)_tmpD6)->f1;
_LL11E:((void(*)(void(*f)(struct _tuple10*),struct Cyc_List_List*l,struct
_tagged_arr start,struct _tagged_arr end,struct _tagged_arr sep))Cyc_Absyndump_group)(
Cyc_Absyndump_dumpde,_tmp122,({const char*_tmp15E="{";_tag_arr(_tmp15E,sizeof(
char),_get_zero_arr_size(_tmp15E,2));}),({const char*_tmp15F="}";_tag_arr(_tmp15F,
sizeof(char),_get_zero_arr_size(_tmp15F,2));}),({const char*_tmp160=",";_tag_arr(
_tmp160,sizeof(char),_get_zero_arr_size(_tmp160,2));}));goto _LLD0;_LL11F: if(*((
int*)_tmpD6)!= 27)goto _LL121;_tmp123=((struct Cyc_Absyn_Comprehension_e_struct*)
_tmpD6)->f1;_tmp124=((struct Cyc_Absyn_Comprehension_e_struct*)_tmpD6)->f2;
_tmp125=((struct Cyc_Absyn_Comprehension_e_struct*)_tmpD6)->f3;_LL120: Cyc_Absyndump_dump(({
const char*_tmp161="new {for";_tag_arr(_tmp161,sizeof(char),_get_zero_arr_size(
_tmp161,9));}));Cyc_Absyndump_dump_str((*_tmp123->name).f2);Cyc_Absyndump_dump_char((
int)'<');Cyc_Absyndump_dumpexp(_tmp124);Cyc_Absyndump_dump_char((int)':');Cyc_Absyndump_dumpexp(
_tmp125);Cyc_Absyndump_dump_char((int)'}');goto _LLD0;_LL121: if(*((int*)_tmpD6)!= 
28)goto _LL123;_tmp126=((struct Cyc_Absyn_Struct_e_struct*)_tmpD6)->f1;_tmp127=((
struct Cyc_Absyn_Struct_e_struct*)_tmpD6)->f2;_tmp128=((struct Cyc_Absyn_Struct_e_struct*)
_tmpD6)->f3;_LL122: Cyc_Absyndump_dumpqvar(_tmp126);Cyc_Absyndump_dump_char((int)'{');
if(_tmp127 != 0)Cyc_Absyndump_dumptps(_tmp127);((void(*)(void(*f)(struct _tuple10*),
struct Cyc_List_List*l,struct _tagged_arr start,struct _tagged_arr end,struct
_tagged_arr sep))Cyc_Absyndump_group)(Cyc_Absyndump_dumpde,_tmp128,({const char*
_tmp162="";_tag_arr(_tmp162,sizeof(char),_get_zero_arr_size(_tmp162,1));}),({
const char*_tmp163="}";_tag_arr(_tmp163,sizeof(char),_get_zero_arr_size(_tmp163,2));}),({
const char*_tmp164=",";_tag_arr(_tmp164,sizeof(char),_get_zero_arr_size(_tmp164,2));}));
goto _LLD0;_LL123: if(*((int*)_tmpD6)!= 29)goto _LL125;_tmp129=((struct Cyc_Absyn_AnonStruct_e_struct*)
_tmpD6)->f2;_LL124:((void(*)(void(*f)(struct _tuple10*),struct Cyc_List_List*l,
struct _tagged_arr start,struct _tagged_arr end,struct _tagged_arr sep))Cyc_Absyndump_group)(
Cyc_Absyndump_dumpde,_tmp129,({const char*_tmp165="{";_tag_arr(_tmp165,sizeof(
char),_get_zero_arr_size(_tmp165,2));}),({const char*_tmp166="}";_tag_arr(_tmp166,
sizeof(char),_get_zero_arr_size(_tmp166,2));}),({const char*_tmp167=",";_tag_arr(
_tmp167,sizeof(char),_get_zero_arr_size(_tmp167,2));}));goto _LLD0;_LL125: if(*((
int*)_tmpD6)!= 30)goto _LL127;_tmp12A=((struct Cyc_Absyn_Tunion_e_struct*)_tmpD6)->f1;
_tmp12B=((struct Cyc_Absyn_Tunion_e_struct*)_tmpD6)->f3;_LL126: Cyc_Absyndump_dumpqvar(
_tmp12B->name);if(_tmp12A != 0)((void(*)(void(*f)(struct Cyc_Absyn_Exp*),struct Cyc_List_List*
l,struct _tagged_arr start,struct _tagged_arr end,struct _tagged_arr sep))Cyc_Absyndump_group)(
Cyc_Absyndump_dumpexp,_tmp12A,({const char*_tmp168="(";_tag_arr(_tmp168,sizeof(
char),_get_zero_arr_size(_tmp168,2));}),({const char*_tmp169=")";_tag_arr(_tmp169,
sizeof(char),_get_zero_arr_size(_tmp169,2));}),({const char*_tmp16A=",";_tag_arr(
_tmp16A,sizeof(char),_get_zero_arr_size(_tmp16A,2));}));goto _LLD0;_LL127: if(*((
int*)_tmpD6)!= 31)goto _LL129;_tmp12C=((struct Cyc_Absyn_Enum_e_struct*)_tmpD6)->f1;
_LL128: Cyc_Absyndump_dumpqvar(_tmp12C);goto _LLD0;_LL129: if(*((int*)_tmpD6)!= 32)
goto _LL12B;_tmp12D=((struct Cyc_Absyn_AnonEnum_e_struct*)_tmpD6)->f1;_LL12A: Cyc_Absyndump_dumpqvar(
_tmp12D);goto _LLD0;_LL12B: if(*((int*)_tmpD6)!= 33)goto _LL12D;_tmp12E=((struct Cyc_Absyn_Malloc_e_struct*)
_tmpD6)->f1;_tmp12F=_tmp12E.is_calloc;_tmp130=_tmp12E.rgn;_tmp131=_tmp12E.elt_type;
_tmp132=_tmp12E.num_elts;_LL12C: if(_tmp12F){if(_tmp130 != 0){Cyc_Absyndump_dump(({
const char*_tmp16B="rcalloc(";_tag_arr(_tmp16B,sizeof(char),_get_zero_arr_size(
_tmp16B,9));}));Cyc_Absyndump_dumpexp((struct Cyc_Absyn_Exp*)_tmp130);Cyc_Absyndump_dump(({
const char*_tmp16C=",";_tag_arr(_tmp16C,sizeof(char),_get_zero_arr_size(_tmp16C,2));}));}
else{Cyc_Absyndump_dump(({const char*_tmp16D="calloc";_tag_arr(_tmp16D,sizeof(
char),_get_zero_arr_size(_tmp16D,7));}));}Cyc_Absyndump_dumpexp(_tmp132);Cyc_Absyndump_dump(({
const char*_tmp16E=",";_tag_arr(_tmp16E,sizeof(char),_get_zero_arr_size(_tmp16E,2));}));
Cyc_Absyndump_dumpexp(Cyc_Absyn_sizeoftyp_exp(*((void**)_check_null(_tmp131)),0));
Cyc_Absyndump_dump(({const char*_tmp16F=")";_tag_arr(_tmp16F,sizeof(char),
_get_zero_arr_size(_tmp16F,2));}));}else{if(_tmp130 != 0){Cyc_Absyndump_dump(({
const char*_tmp170="rmalloc(";_tag_arr(_tmp170,sizeof(char),_get_zero_arr_size(
_tmp170,9));}));Cyc_Absyndump_dumpexp((struct Cyc_Absyn_Exp*)_tmp130);Cyc_Absyndump_dump(({
const char*_tmp171=",";_tag_arr(_tmp171,sizeof(char),_get_zero_arr_size(_tmp171,2));}));}
else{Cyc_Absyndump_dump(({const char*_tmp172="malloc(";_tag_arr(_tmp172,sizeof(
char),_get_zero_arr_size(_tmp172,8));}));}if(_tmp131 != 0)Cyc_Absyndump_dumpexp(
Cyc_Absyn_times_exp(Cyc_Absyn_sizeoftyp_exp(*_tmp131,0),_tmp132,0));else{Cyc_Absyndump_dumpexp(
_tmp132);}Cyc_Absyndump_dump(({const char*_tmp173=")";_tag_arr(_tmp173,sizeof(
char),_get_zero_arr_size(_tmp173,2));}));}goto _LLD0;_LL12D: if(*((int*)_tmpD6)!= 
34)goto _LL12F;_tmp133=((struct Cyc_Absyn_UnresolvedMem_e_struct*)_tmpD6)->f1;
_tmp134=((struct Cyc_Absyn_UnresolvedMem_e_struct*)_tmpD6)->f2;_LL12E:((void(*)(
void(*f)(struct _tuple10*),struct Cyc_List_List*l,struct _tagged_arr start,struct
_tagged_arr end,struct _tagged_arr sep))Cyc_Absyndump_group)(Cyc_Absyndump_dumpde,
_tmp134,({const char*_tmp174="{";_tag_arr(_tmp174,sizeof(char),_get_zero_arr_size(
_tmp174,2));}),({const char*_tmp175="}";_tag_arr(_tmp175,sizeof(char),
_get_zero_arr_size(_tmp175,2));}),({const char*_tmp176=",";_tag_arr(_tmp176,
sizeof(char),_get_zero_arr_size(_tmp176,2));}));goto _LLD0;_LL12F: if(*((int*)
_tmpD6)!= 35)goto _LL131;_tmp135=((struct Cyc_Absyn_StmtExp_e_struct*)_tmpD6)->f1;
_LL130: Cyc_Absyndump_dump_nospace(({const char*_tmp177="({";_tag_arr(_tmp177,
sizeof(char),_get_zero_arr_size(_tmp177,3));}));Cyc_Absyndump_dumpstmt(_tmp135);
Cyc_Absyndump_dump_nospace(({const char*_tmp178="})";_tag_arr(_tmp178,sizeof(char),
_get_zero_arr_size(_tmp178,3));}));goto _LLD0;_LL131: if(*((int*)_tmpD6)!= 36)goto
_LL133;_tmp136=((struct Cyc_Absyn_Codegen_e_struct*)_tmpD6)->f1;_LL132: Cyc_Absyndump_dump(({
const char*_tmp179="codegen(";_tag_arr(_tmp179,sizeof(char),_get_zero_arr_size(
_tmp179,9));}));Cyc_Absyndump_dumpdecl(({struct Cyc_Absyn_Decl*_tmp17A=_cycalloc(
sizeof(*_tmp17A));_tmp17A->r=(void*)((void*)({struct Cyc_Absyn_Fn_d_struct*
_tmp17B=_cycalloc(sizeof(*_tmp17B));_tmp17B[0]=({struct Cyc_Absyn_Fn_d_struct
_tmp17C;_tmp17C.tag=1;_tmp17C.f1=_tmp136;_tmp17C;});_tmp17B;}));_tmp17A->loc=e->loc;
_tmp17A;}));Cyc_Absyndump_dump(({const char*_tmp17D=")";_tag_arr(_tmp17D,sizeof(
char),_get_zero_arr_size(_tmp17D,2));}));goto _LLD0;_LL133: if(*((int*)_tmpD6)!= 
37)goto _LLD0;_tmp137=((struct Cyc_Absyn_Fill_e_struct*)_tmpD6)->f1;_LL134: Cyc_Absyndump_dump(({
const char*_tmp17E="fill(";_tag_arr(_tmp17E,sizeof(char),_get_zero_arr_size(
_tmp17E,6));}));Cyc_Absyndump_dumpexp(_tmp137);Cyc_Absyndump_dump(({const char*
_tmp17F=")";_tag_arr(_tmp17F,sizeof(char),_get_zero_arr_size(_tmp17F,2));}));
goto _LLD0;_LLD0:;}if(inprec >= myprec)Cyc_Absyndump_dump_char((int)')');}void Cyc_Absyndump_dumpexp(
struct Cyc_Absyn_Exp*e){Cyc_Absyndump_dumpexp_prec(0,e);}void Cyc_Absyndump_dumpswitchclauses(
struct Cyc_List_List*scs){for(0;scs != 0;scs=scs->tl){struct Cyc_Absyn_Switch_clause*
_tmp180=(struct Cyc_Absyn_Switch_clause*)scs->hd;if(_tmp180->where_clause == 0?(
void*)(_tmp180->pattern)->r == (void*)((void*)0): 0)Cyc_Absyndump_dump(({const char*
_tmp181="default:";_tag_arr(_tmp181,sizeof(char),_get_zero_arr_size(_tmp181,9));}));
else{Cyc_Absyndump_dump(({const char*_tmp182="case";_tag_arr(_tmp182,sizeof(char),
_get_zero_arr_size(_tmp182,5));}));Cyc_Absyndump_dumppat(_tmp180->pattern);if(
_tmp180->where_clause != 0){Cyc_Absyndump_dump(({const char*_tmp183="&&";_tag_arr(
_tmp183,sizeof(char),_get_zero_arr_size(_tmp183,3));}));Cyc_Absyndump_dumpexp((
struct Cyc_Absyn_Exp*)_check_null(_tmp180->where_clause));}Cyc_Absyndump_dump_nospace(({
const char*_tmp184=":";_tag_arr(_tmp184,sizeof(char),_get_zero_arr_size(_tmp184,2));}));}
Cyc_Absyndump_dumpstmt(_tmp180->body);}}void Cyc_Absyndump_dumpstmt(struct Cyc_Absyn_Stmt*
s){void*_tmp185=(void*)s->r;struct Cyc_Absyn_Exp*_tmp186;struct Cyc_Absyn_Stmt*
_tmp187;struct Cyc_Absyn_Stmt*_tmp188;struct Cyc_Absyn_Exp*_tmp189;struct Cyc_Absyn_Exp*
_tmp18A;struct Cyc_Absyn_Exp*_tmp18B;struct Cyc_Absyn_Stmt*_tmp18C;struct Cyc_Absyn_Stmt*
_tmp18D;struct _tuple2 _tmp18E;struct Cyc_Absyn_Exp*_tmp18F;struct Cyc_Absyn_Stmt*
_tmp190;struct _tagged_arr*_tmp191;struct Cyc_Absyn_Exp*_tmp192;struct _tuple2
_tmp193;struct Cyc_Absyn_Exp*_tmp194;struct _tuple2 _tmp195;struct Cyc_Absyn_Exp*
_tmp196;struct Cyc_Absyn_Stmt*_tmp197;struct Cyc_Absyn_ForArrayInfo _tmp198;struct
Cyc_List_List*_tmp199;struct _tuple2 _tmp19A;struct Cyc_Absyn_Exp*_tmp19B;struct
_tuple2 _tmp19C;struct Cyc_Absyn_Exp*_tmp19D;struct Cyc_Absyn_Stmt*_tmp19E;struct
Cyc_Absyn_Exp*_tmp19F;struct Cyc_List_List*_tmp1A0;struct Cyc_Absyn_Decl*_tmp1A1;
struct Cyc_Absyn_Stmt*_tmp1A2;struct _tagged_arr*_tmp1A3;struct Cyc_Absyn_Stmt*
_tmp1A4;struct Cyc_Absyn_Stmt*_tmp1A5;struct _tuple2 _tmp1A6;struct Cyc_Absyn_Exp*
_tmp1A7;struct Cyc_Absyn_Exp*_tmp1A8;struct Cyc_List_List*_tmp1A9;struct Cyc_List_List*
_tmp1AA;struct Cyc_List_List*_tmp1AB;struct Cyc_Absyn_Stmt*_tmp1AC;struct Cyc_List_List*
_tmp1AD;struct Cyc_Absyn_Tvar*_tmp1AE;struct Cyc_Absyn_Vardecl*_tmp1AF;int _tmp1B0;
struct Cyc_Absyn_Stmt*_tmp1B1;struct Cyc_Absyn_Exp*_tmp1B2;struct Cyc_Absyn_Stmt*
_tmp1B3;struct Cyc_Absyn_Stmt*_tmp1B4;_LL13A: if((int)_tmp185 != 0)goto _LL13C;
_LL13B: Cyc_Absyndump_dump_semi();goto _LL139;_LL13C: if(_tmp185 <= (void*)1?1:*((
int*)_tmp185)!= 0)goto _LL13E;_tmp186=((struct Cyc_Absyn_Exp_s_struct*)_tmp185)->f1;
_LL13D: Cyc_Absyndump_dumploc(s->loc);Cyc_Absyndump_dumpexp(_tmp186);Cyc_Absyndump_dump_semi();
goto _LL139;_LL13E: if(_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 1)goto _LL140;
_tmp187=((struct Cyc_Absyn_Seq_s_struct*)_tmp185)->f1;_tmp188=((struct Cyc_Absyn_Seq_s_struct*)
_tmp185)->f2;_LL13F: if(Cyc_Absynpp_is_declaration(_tmp187)){Cyc_Absyndump_dump_char((
int)'{');Cyc_Absyndump_dumpstmt(_tmp187);Cyc_Absyndump_dump_char((int)'}');}
else{Cyc_Absyndump_dumpstmt(_tmp187);}if(Cyc_Absynpp_is_declaration(_tmp188)){
Cyc_Absyndump_dump_char((int)'{');Cyc_Absyndump_dumpstmt(_tmp188);Cyc_Absyndump_dump_char((
int)'}');}else{Cyc_Absyndump_dumpstmt(_tmp188);}goto _LL139;_LL140: if(_tmp185 <= (
void*)1?1:*((int*)_tmp185)!= 2)goto _LL142;_tmp189=((struct Cyc_Absyn_Return_s_struct*)
_tmp185)->f1;if(_tmp189 != 0)goto _LL142;_LL141: Cyc_Absyndump_dumploc(s->loc);Cyc_Absyndump_dump(({
const char*_tmp1B5="return;";_tag_arr(_tmp1B5,sizeof(char),_get_zero_arr_size(
_tmp1B5,8));}));goto _LL139;_LL142: if(_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 2)
goto _LL144;_tmp18A=((struct Cyc_Absyn_Return_s_struct*)_tmp185)->f1;_LL143: Cyc_Absyndump_dumploc(
s->loc);Cyc_Absyndump_dump(({const char*_tmp1B6="return";_tag_arr(_tmp1B6,sizeof(
char),_get_zero_arr_size(_tmp1B6,7));}));Cyc_Absyndump_dumpexp((struct Cyc_Absyn_Exp*)
_check_null(_tmp18A));Cyc_Absyndump_dump_semi();goto _LL139;_LL144: if(_tmp185 <= (
void*)1?1:*((int*)_tmp185)!= 3)goto _LL146;_tmp18B=((struct Cyc_Absyn_IfThenElse_s_struct*)
_tmp185)->f1;_tmp18C=((struct Cyc_Absyn_IfThenElse_s_struct*)_tmp185)->f2;_tmp18D=((
struct Cyc_Absyn_IfThenElse_s_struct*)_tmp185)->f3;_LL145: Cyc_Absyndump_dumploc(s->loc);
Cyc_Absyndump_dump(({const char*_tmp1B7="if(";_tag_arr(_tmp1B7,sizeof(char),
_get_zero_arr_size(_tmp1B7,4));}));Cyc_Absyndump_dumpexp(_tmp18B);{void*_tmp1B8=(
void*)_tmp18C->r;_LL16B: if(_tmp1B8 <= (void*)1?1:*((int*)_tmp1B8)!= 1)goto _LL16D;
_LL16C: goto _LL16E;_LL16D: if(_tmp1B8 <= (void*)1?1:*((int*)_tmp1B8)!= 12)goto
_LL16F;_LL16E: goto _LL170;_LL16F: if(_tmp1B8 <= (void*)1?1:*((int*)_tmp1B8)!= 3)
goto _LL171;_LL170: goto _LL172;_LL171: if(_tmp1B8 <= (void*)1?1:*((int*)_tmp1B8)!= 
15)goto _LL173;_LL172: Cyc_Absyndump_dump_nospace(({const char*_tmp1B9="){";
_tag_arr(_tmp1B9,sizeof(char),_get_zero_arr_size(_tmp1B9,3));}));Cyc_Absyndump_dumpstmt(
_tmp18C);Cyc_Absyndump_dump_char((int)'}');goto _LL16A;_LL173:;_LL174: Cyc_Absyndump_dump_char((
int)')');Cyc_Absyndump_dumpstmt(_tmp18C);_LL16A:;}{void*_tmp1BA=(void*)_tmp18D->r;
_LL176: if((int)_tmp1BA != 0)goto _LL178;_LL177: goto _LL175;_LL178:;_LL179: Cyc_Absyndump_dump(({
const char*_tmp1BB="else{";_tag_arr(_tmp1BB,sizeof(char),_get_zero_arr_size(
_tmp1BB,6));}));Cyc_Absyndump_dumpstmt(_tmp18D);Cyc_Absyndump_dump_char((int)'}');
goto _LL175;_LL175:;}goto _LL139;_LL146: if(_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 
4)goto _LL148;_tmp18E=((struct Cyc_Absyn_While_s_struct*)_tmp185)->f1;_tmp18F=
_tmp18E.f1;_tmp190=((struct Cyc_Absyn_While_s_struct*)_tmp185)->f2;_LL147: Cyc_Absyndump_dumploc(
s->loc);Cyc_Absyndump_dump(({const char*_tmp1BC="while(";_tag_arr(_tmp1BC,sizeof(
char),_get_zero_arr_size(_tmp1BC,7));}));Cyc_Absyndump_dumpexp(_tmp18F);Cyc_Absyndump_dump_nospace(({
const char*_tmp1BD="){";_tag_arr(_tmp1BD,sizeof(char),_get_zero_arr_size(_tmp1BD,
3));}));Cyc_Absyndump_dumpstmt(_tmp190);Cyc_Absyndump_dump_char((int)'}');goto
_LL139;_LL148: if(_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 5)goto _LL14A;_LL149: Cyc_Absyndump_dumploc(
s->loc);Cyc_Absyndump_dump(({const char*_tmp1BE="break;";_tag_arr(_tmp1BE,sizeof(
char),_get_zero_arr_size(_tmp1BE,7));}));goto _LL139;_LL14A: if(_tmp185 <= (void*)1?
1:*((int*)_tmp185)!= 6)goto _LL14C;_LL14B: Cyc_Absyndump_dumploc(s->loc);Cyc_Absyndump_dump(({
const char*_tmp1BF="continue;";_tag_arr(_tmp1BF,sizeof(char),_get_zero_arr_size(
_tmp1BF,10));}));goto _LL139;_LL14C: if(_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 7)
goto _LL14E;_tmp191=((struct Cyc_Absyn_Goto_s_struct*)_tmp185)->f1;_LL14D: Cyc_Absyndump_dumploc(
s->loc);Cyc_Absyndump_dump(({const char*_tmp1C0="goto";_tag_arr(_tmp1C0,sizeof(
char),_get_zero_arr_size(_tmp1C0,5));}));Cyc_Absyndump_dump_str(_tmp191);Cyc_Absyndump_dump_semi();
goto _LL139;_LL14E: if(_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 8)goto _LL150;
_tmp192=((struct Cyc_Absyn_For_s_struct*)_tmp185)->f1;_tmp193=((struct Cyc_Absyn_For_s_struct*)
_tmp185)->f2;_tmp194=_tmp193.f1;_tmp195=((struct Cyc_Absyn_For_s_struct*)_tmp185)->f3;
_tmp196=_tmp195.f1;_tmp197=((struct Cyc_Absyn_For_s_struct*)_tmp185)->f4;_LL14F:
Cyc_Absyndump_dumploc(s->loc);Cyc_Absyndump_dump(({const char*_tmp1C1="for(";
_tag_arr(_tmp1C1,sizeof(char),_get_zero_arr_size(_tmp1C1,5));}));Cyc_Absyndump_dumpexp(
_tmp192);Cyc_Absyndump_dump_semi();Cyc_Absyndump_dumpexp(_tmp194);Cyc_Absyndump_dump_semi();
Cyc_Absyndump_dumpexp(_tmp196);Cyc_Absyndump_dump_nospace(({const char*_tmp1C2="){";
_tag_arr(_tmp1C2,sizeof(char),_get_zero_arr_size(_tmp1C2,3));}));Cyc_Absyndump_dumpstmt(
_tmp197);Cyc_Absyndump_dump_char((int)'}');goto _LL139;_LL150: if(_tmp185 <= (void*)
1?1:*((int*)_tmp185)!= 19)goto _LL152;_tmp198=((struct Cyc_Absyn_ForArray_s_struct*)
_tmp185)->f1;_tmp199=_tmp198.defns;_tmp19A=_tmp198.condition;_tmp19B=_tmp19A.f1;
_tmp19C=_tmp198.delta;_tmp19D=_tmp19C.f1;_tmp19E=_tmp198.body;_LL151: Cyc_Absyndump_dumploc(
s->loc);Cyc_Absyndump_dump(({const char*_tmp1C3="forarray(";_tag_arr(_tmp1C3,
sizeof(char),_get_zero_arr_size(_tmp1C3,10));}));for(0;_tmp199 != 0;_tmp199=
_tmp199->tl){Cyc_Absyndump_dumpvardecl((struct Cyc_Absyn_Vardecl*)_tmp199->hd,s->loc);}
Cyc_Absyndump_dumpexp(_tmp19B);Cyc_Absyndump_dump_semi();Cyc_Absyndump_dumpexp(
_tmp19D);Cyc_Absyndump_dump_nospace(({const char*_tmp1C4="){";_tag_arr(_tmp1C4,
sizeof(char),_get_zero_arr_size(_tmp1C4,3));}));Cyc_Absyndump_dumpstmt(_tmp19E);
Cyc_Absyndump_dump_char((int)'}');goto _LL139;_LL152: if(_tmp185 <= (void*)1?1:*((
int*)_tmp185)!= 9)goto _LL154;_tmp19F=((struct Cyc_Absyn_Switch_s_struct*)_tmp185)->f1;
_tmp1A0=((struct Cyc_Absyn_Switch_s_struct*)_tmp185)->f2;_LL153: Cyc_Absyndump_dumploc(
s->loc);Cyc_Absyndump_dump(({const char*_tmp1C5="switch(";_tag_arr(_tmp1C5,
sizeof(char),_get_zero_arr_size(_tmp1C5,8));}));Cyc_Absyndump_dumpexp(_tmp19F);
Cyc_Absyndump_dump_nospace(({const char*_tmp1C6="){";_tag_arr(_tmp1C6,sizeof(char),
_get_zero_arr_size(_tmp1C6,3));}));Cyc_Absyndump_dumpswitchclauses(_tmp1A0);Cyc_Absyndump_dump_char((
int)'}');goto _LL139;_LL154: if(_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 12)goto
_LL156;_tmp1A1=((struct Cyc_Absyn_Decl_s_struct*)_tmp185)->f1;_tmp1A2=((struct Cyc_Absyn_Decl_s_struct*)
_tmp185)->f2;_LL155: Cyc_Absyndump_dumpdecl(_tmp1A1);Cyc_Absyndump_dumpstmt(
_tmp1A2);goto _LL139;_LL156: if(_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 15)goto
_LL158;_tmp1A3=((struct Cyc_Absyn_Label_s_struct*)_tmp185)->f1;_tmp1A4=((struct
Cyc_Absyn_Label_s_struct*)_tmp185)->f2;_LL157: if(Cyc_Absynpp_is_declaration(
_tmp1A4)){Cyc_Absyndump_dump_str(_tmp1A3);Cyc_Absyndump_dump_nospace(({const char*
_tmp1C7=": {";_tag_arr(_tmp1C7,sizeof(char),_get_zero_arr_size(_tmp1C7,4));}));
Cyc_Absyndump_dumpstmt(_tmp1A4);Cyc_Absyndump_dump_char((int)'}');}else{Cyc_Absyndump_dump_str(
_tmp1A3);Cyc_Absyndump_dump_char((int)':');Cyc_Absyndump_dumpstmt(_tmp1A4);}goto
_LL139;_LL158: if(_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 16)goto _LL15A;_tmp1A5=((
struct Cyc_Absyn_Do_s_struct*)_tmp185)->f1;_tmp1A6=((struct Cyc_Absyn_Do_s_struct*)
_tmp185)->f2;_tmp1A7=_tmp1A6.f1;_LL159: Cyc_Absyndump_dumploc(s->loc);Cyc_Absyndump_dump(({
const char*_tmp1C8="do{";_tag_arr(_tmp1C8,sizeof(char),_get_zero_arr_size(_tmp1C8,
4));}));Cyc_Absyndump_dumpstmt(_tmp1A5);Cyc_Absyndump_dump_nospace(({const char*
_tmp1C9="}while(";_tag_arr(_tmp1C9,sizeof(char),_get_zero_arr_size(_tmp1C9,8));}));
Cyc_Absyndump_dumpexp(_tmp1A7);Cyc_Absyndump_dump_nospace(({const char*_tmp1CA=");";
_tag_arr(_tmp1CA,sizeof(char),_get_zero_arr_size(_tmp1CA,3));}));goto _LL139;
_LL15A: if(_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 10)goto _LL15C;_tmp1A8=((struct
Cyc_Absyn_SwitchC_s_struct*)_tmp185)->f1;_tmp1A9=((struct Cyc_Absyn_SwitchC_s_struct*)
_tmp185)->f2;_LL15B: Cyc_Absyndump_dumploc(s->loc);Cyc_Absyndump_dump(({const char*
_tmp1CB="switch \"C\"(";_tag_arr(_tmp1CB,sizeof(char),_get_zero_arr_size(_tmp1CB,
12));}));Cyc_Absyndump_dumpexp(_tmp1A8);Cyc_Absyndump_dump_nospace(({const char*
_tmp1CC="){";_tag_arr(_tmp1CC,sizeof(char),_get_zero_arr_size(_tmp1CC,3));}));
for(0;_tmp1A9 != 0;_tmp1A9=_tmp1A9->tl){struct Cyc_Absyn_SwitchC_clause _tmp1CE;
struct Cyc_Absyn_Exp*_tmp1CF;struct Cyc_Absyn_Stmt*_tmp1D0;struct Cyc_Absyn_SwitchC_clause*
_tmp1CD=(struct Cyc_Absyn_SwitchC_clause*)_tmp1A9->hd;_tmp1CE=*_tmp1CD;_tmp1CF=
_tmp1CE.cnst_exp;_tmp1D0=_tmp1CE.body;if(_tmp1CF == 0)Cyc_Absyndump_dump(({const
char*_tmp1D1="default:";_tag_arr(_tmp1D1,sizeof(char),_get_zero_arr_size(_tmp1D1,
9));}));else{Cyc_Absyndump_dump(({const char*_tmp1D2="case";_tag_arr(_tmp1D2,
sizeof(char),_get_zero_arr_size(_tmp1D2,5));}));Cyc_Absyndump_dumpexp((struct Cyc_Absyn_Exp*)
_tmp1CF);Cyc_Absyndump_dump_char((int)':');}Cyc_Absyndump_dumpstmt(_tmp1D0);}Cyc_Absyndump_dump_char((
int)'}');goto _LL139;_LL15C: if(_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 11)goto
_LL15E;_tmp1AA=((struct Cyc_Absyn_Fallthru_s_struct*)_tmp185)->f1;if(_tmp1AA != 0)
goto _LL15E;_LL15D: Cyc_Absyndump_dump(({const char*_tmp1D3="fallthru;";_tag_arr(
_tmp1D3,sizeof(char),_get_zero_arr_size(_tmp1D3,10));}));goto _LL139;_LL15E: if(
_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 11)goto _LL160;_tmp1AB=((struct Cyc_Absyn_Fallthru_s_struct*)
_tmp185)->f1;_LL15F: Cyc_Absyndump_dump(({const char*_tmp1D4="fallthru(";_tag_arr(
_tmp1D4,sizeof(char),_get_zero_arr_size(_tmp1D4,10));}));Cyc_Absyndump_dumpexps_prec(
20,_tmp1AB);Cyc_Absyndump_dump_nospace(({const char*_tmp1D5=");";_tag_arr(_tmp1D5,
sizeof(char),_get_zero_arr_size(_tmp1D5,3));}));goto _LL139;_LL160: if(_tmp185 <= (
void*)1?1:*((int*)_tmp185)!= 17)goto _LL162;_tmp1AC=((struct Cyc_Absyn_TryCatch_s_struct*)
_tmp185)->f1;_tmp1AD=((struct Cyc_Absyn_TryCatch_s_struct*)_tmp185)->f2;_LL161:
Cyc_Absyndump_dumploc(s->loc);Cyc_Absyndump_dump(({const char*_tmp1D6="try";
_tag_arr(_tmp1D6,sizeof(char),_get_zero_arr_size(_tmp1D6,4));}));Cyc_Absyndump_dumpstmt(
_tmp1AC);Cyc_Absyndump_dump(({const char*_tmp1D7="catch{";_tag_arr(_tmp1D7,
sizeof(char),_get_zero_arr_size(_tmp1D7,7));}));Cyc_Absyndump_dumpswitchclauses(
_tmp1AD);Cyc_Absyndump_dump_char((int)'}');goto _LL139;_LL162: if(_tmp185 <= (void*)
1?1:*((int*)_tmp185)!= 18)goto _LL164;_tmp1AE=((struct Cyc_Absyn_Region_s_struct*)
_tmp185)->f1;_tmp1AF=((struct Cyc_Absyn_Region_s_struct*)_tmp185)->f2;_tmp1B0=((
struct Cyc_Absyn_Region_s_struct*)_tmp185)->f3;_tmp1B1=((struct Cyc_Absyn_Region_s_struct*)
_tmp185)->f4;_LL163: Cyc_Absyndump_dumploc(s->loc);Cyc_Absyndump_dump(({const char*
_tmp1D8="region";_tag_arr(_tmp1D8,sizeof(char),_get_zero_arr_size(_tmp1D8,7));}));
if(_tmp1B0)Cyc_Absyndump_dump(({const char*_tmp1D9="[resetable]";_tag_arr(_tmp1D9,
sizeof(char),_get_zero_arr_size(_tmp1D9,12));}));Cyc_Absyndump_dump(({const char*
_tmp1DA="<";_tag_arr(_tmp1DA,sizeof(char),_get_zero_arr_size(_tmp1DA,2));}));Cyc_Absyndump_dumptvar(
_tmp1AE);Cyc_Absyndump_dump(({const char*_tmp1DB="> ";_tag_arr(_tmp1DB,sizeof(
char),_get_zero_arr_size(_tmp1DB,3));}));Cyc_Absyndump_dumpqvar(_tmp1AF->name);
Cyc_Absyndump_dump(({const char*_tmp1DC="{";_tag_arr(_tmp1DC,sizeof(char),
_get_zero_arr_size(_tmp1DC,2));}));Cyc_Absyndump_dumpstmt(_tmp1B1);Cyc_Absyndump_dump(({
const char*_tmp1DD="}";_tag_arr(_tmp1DD,sizeof(char),_get_zero_arr_size(_tmp1DD,2));}));
goto _LL139;_LL164: if(_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 20)goto _LL166;
_tmp1B2=((struct Cyc_Absyn_ResetRegion_s_struct*)_tmp185)->f1;_LL165: Cyc_Absyndump_dumploc(
s->loc);Cyc_Absyndump_dump(({const char*_tmp1DE="reset_region(";_tag_arr(_tmp1DE,
sizeof(char),_get_zero_arr_size(_tmp1DE,14));}));Cyc_Absyndump_dumpexp(_tmp1B2);
Cyc_Absyndump_dump(({const char*_tmp1DF=");";_tag_arr(_tmp1DF,sizeof(char),
_get_zero_arr_size(_tmp1DF,3));}));goto _LL139;_LL166: if(_tmp185 <= (void*)1?1:*((
int*)_tmp185)!= 13)goto _LL168;_tmp1B3=((struct Cyc_Absyn_Cut_s_struct*)_tmp185)->f1;
_LL167: Cyc_Absyndump_dump(({const char*_tmp1E0="cut";_tag_arr(_tmp1E0,sizeof(char),
_get_zero_arr_size(_tmp1E0,4));}));Cyc_Absyndump_dumpstmt(_tmp1B3);goto _LL139;
_LL168: if(_tmp185 <= (void*)1?1:*((int*)_tmp185)!= 14)goto _LL139;_tmp1B4=((struct
Cyc_Absyn_Splice_s_struct*)_tmp185)->f1;_LL169: Cyc_Absyndump_dump(({const char*
_tmp1E1="splice";_tag_arr(_tmp1E1,sizeof(char),_get_zero_arr_size(_tmp1E1,7));}));
Cyc_Absyndump_dumpstmt(_tmp1B4);goto _LL139;_LL139:;}struct _tuple11{struct Cyc_List_List*
f1;struct Cyc_Absyn_Pat*f2;};void Cyc_Absyndump_dumpdp(struct _tuple11*dp){Cyc_Absyndump_egroup(
Cyc_Absyndump_dumpdesignator,(*dp).f1,({const char*_tmp1E2="";_tag_arr(_tmp1E2,
sizeof(char),_get_zero_arr_size(_tmp1E2,1));}),({const char*_tmp1E3="=";_tag_arr(
_tmp1E3,sizeof(char),_get_zero_arr_size(_tmp1E3,2));}),({const char*_tmp1E4="=";
_tag_arr(_tmp1E4,sizeof(char),_get_zero_arr_size(_tmp1E4,2));}));Cyc_Absyndump_dumppat((*
dp).f2);}void Cyc_Absyndump_dumppat(struct Cyc_Absyn_Pat*p){void*_tmp1E5=(void*)p->r;
void*_tmp1E6;int _tmp1E7;void*_tmp1E8;int _tmp1E9;void*_tmp1EA;int _tmp1EB;char
_tmp1EC;struct _tagged_arr _tmp1ED;struct Cyc_Absyn_Vardecl*_tmp1EE;struct Cyc_List_List*
_tmp1EF;struct Cyc_Absyn_Pat*_tmp1F0;struct Cyc_Absyn_Vardecl*_tmp1F1;struct Cyc_Absyn_Tvar*
_tmp1F2;struct Cyc_Absyn_Vardecl*_tmp1F3;struct _tuple0*_tmp1F4;struct _tuple0*
_tmp1F5;struct Cyc_List_List*_tmp1F6;struct Cyc_Absyn_AggrInfo _tmp1F7;void*_tmp1F8;
struct Cyc_List_List*_tmp1F9;struct Cyc_List_List*_tmp1FA;struct Cyc_Absyn_Tunionfield*
_tmp1FB;struct Cyc_List_List*_tmp1FC;struct Cyc_Absyn_Enumfield*_tmp1FD;struct Cyc_Absyn_Enumfield*
_tmp1FE;_LL17B: if((int)_tmp1E5 != 0)goto _LL17D;_LL17C: Cyc_Absyndump_dump_char((
int)'_');goto _LL17A;_LL17D: if((int)_tmp1E5 != 1)goto _LL17F;_LL17E: Cyc_Absyndump_dump(({
const char*_tmp1FF="NULL";_tag_arr(_tmp1FF,sizeof(char),_get_zero_arr_size(
_tmp1FF,5));}));goto _LL17A;_LL17F: if(_tmp1E5 <= (void*)2?1:*((int*)_tmp1E5)!= 7)
goto _LL181;_tmp1E6=(void*)((struct Cyc_Absyn_Int_p_struct*)_tmp1E5)->f1;if((int)
_tmp1E6 != 2)goto _LL181;_tmp1E7=((struct Cyc_Absyn_Int_p_struct*)_tmp1E5)->f2;
_LL180: _tmp1E9=_tmp1E7;goto _LL182;_LL181: if(_tmp1E5 <= (void*)2?1:*((int*)_tmp1E5)
!= 7)goto _LL183;_tmp1E8=(void*)((struct Cyc_Absyn_Int_p_struct*)_tmp1E5)->f1;if((
int)_tmp1E8 != 0)goto _LL183;_tmp1E9=((struct Cyc_Absyn_Int_p_struct*)_tmp1E5)->f2;
_LL182: Cyc_Absyndump_dump((struct _tagged_arr)({struct Cyc_Int_pa_struct _tmp202;
_tmp202.tag=1;_tmp202.f1=(unsigned int)_tmp1E9;{void*_tmp200[1]={& _tmp202};Cyc_aprintf(({
const char*_tmp201="%d";_tag_arr(_tmp201,sizeof(char),_get_zero_arr_size(_tmp201,
3));}),_tag_arr(_tmp200,sizeof(void*),1));}}));goto _LL17A;_LL183: if(_tmp1E5 <= (
void*)2?1:*((int*)_tmp1E5)!= 7)goto _LL185;_tmp1EA=(void*)((struct Cyc_Absyn_Int_p_struct*)
_tmp1E5)->f1;if((int)_tmp1EA != 1)goto _LL185;_tmp1EB=((struct Cyc_Absyn_Int_p_struct*)
_tmp1E5)->f2;_LL184: Cyc_Absyndump_dump((struct _tagged_arr)({struct Cyc_Int_pa_struct
_tmp205;_tmp205.tag=1;_tmp205.f1=(unsigned int)_tmp1EB;{void*_tmp203[1]={&
_tmp205};Cyc_aprintf(({const char*_tmp204="%u";_tag_arr(_tmp204,sizeof(char),
_get_zero_arr_size(_tmp204,3));}),_tag_arr(_tmp203,sizeof(void*),1));}}));goto
_LL17A;_LL185: if(_tmp1E5 <= (void*)2?1:*((int*)_tmp1E5)!= 8)goto _LL187;_tmp1EC=((
struct Cyc_Absyn_Char_p_struct*)_tmp1E5)->f1;_LL186: Cyc_Absyndump_dump(({const
char*_tmp206="'";_tag_arr(_tmp206,sizeof(char),_get_zero_arr_size(_tmp206,2));}));
Cyc_Absyndump_dump_nospace(Cyc_Absynpp_char_escape(_tmp1EC));Cyc_Absyndump_dump_nospace(({
const char*_tmp207="'";_tag_arr(_tmp207,sizeof(char),_get_zero_arr_size(_tmp207,2));}));
goto _LL17A;_LL187: if(_tmp1E5 <= (void*)2?1:*((int*)_tmp1E5)!= 9)goto _LL189;
_tmp1ED=((struct Cyc_Absyn_Float_p_struct*)_tmp1E5)->f1;_LL188: Cyc_Absyndump_dump(
_tmp1ED);goto _LL17A;_LL189: if(_tmp1E5 <= (void*)2?1:*((int*)_tmp1E5)!= 0)goto
_LL18B;_tmp1EE=((struct Cyc_Absyn_Var_p_struct*)_tmp1E5)->f1;_LL18A: Cyc_Absyndump_dumpqvar(
_tmp1EE->name);goto _LL17A;_LL18B: if(_tmp1E5 <= (void*)2?1:*((int*)_tmp1E5)!= 3)
goto _LL18D;_tmp1EF=((struct Cyc_Absyn_Tuple_p_struct*)_tmp1E5)->f1;_LL18C:((void(*)(
void(*f)(struct Cyc_Absyn_Pat*),struct Cyc_List_List*l,struct _tagged_arr start,
struct _tagged_arr end,struct _tagged_arr sep))Cyc_Absyndump_group)(Cyc_Absyndump_dumppat,
_tmp1EF,({const char*_tmp208="$(";_tag_arr(_tmp208,sizeof(char),
_get_zero_arr_size(_tmp208,3));}),({const char*_tmp209=")";_tag_arr(_tmp209,
sizeof(char),_get_zero_arr_size(_tmp209,2));}),({const char*_tmp20A=",";_tag_arr(
_tmp20A,sizeof(char),_get_zero_arr_size(_tmp20A,2));}));goto _LL17A;_LL18D: if(
_tmp1E5 <= (void*)2?1:*((int*)_tmp1E5)!= 4)goto _LL18F;_tmp1F0=((struct Cyc_Absyn_Pointer_p_struct*)
_tmp1E5)->f1;_LL18E: Cyc_Absyndump_dump(({const char*_tmp20B="&";_tag_arr(_tmp20B,
sizeof(char),_get_zero_arr_size(_tmp20B,2));}));Cyc_Absyndump_dumppat(_tmp1F0);
goto _LL17A;_LL18F: if(_tmp1E5 <= (void*)2?1:*((int*)_tmp1E5)!= 1)goto _LL191;
_tmp1F1=((struct Cyc_Absyn_Reference_p_struct*)_tmp1E5)->f1;_LL190: Cyc_Absyndump_dump(({
const char*_tmp20C="*";_tag_arr(_tmp20C,sizeof(char),_get_zero_arr_size(_tmp20C,2));}));
Cyc_Absyndump_dumpqvar(_tmp1F1->name);goto _LL17A;_LL191: if(_tmp1E5 <= (void*)2?1:*((
int*)_tmp1E5)!= 2)goto _LL193;_tmp1F2=((struct Cyc_Absyn_TagInt_p_struct*)_tmp1E5)->f1;
_tmp1F3=((struct Cyc_Absyn_TagInt_p_struct*)_tmp1E5)->f2;_LL192: Cyc_Absyndump_dumpqvar(
_tmp1F3->name);Cyc_Absyndump_dump_char((int)'<');Cyc_Absyndump_dumptvar(_tmp1F2);
Cyc_Absyndump_dump_char((int)'>');goto _LL17A;_LL193: if(_tmp1E5 <= (void*)2?1:*((
int*)_tmp1E5)!= 12)goto _LL195;_tmp1F4=((struct Cyc_Absyn_UnknownId_p_struct*)
_tmp1E5)->f1;_LL194: Cyc_Absyndump_dumpqvar(_tmp1F4);goto _LL17A;_LL195: if(_tmp1E5
<= (void*)2?1:*((int*)_tmp1E5)!= 13)goto _LL197;_tmp1F5=((struct Cyc_Absyn_UnknownCall_p_struct*)
_tmp1E5)->f1;_tmp1F6=((struct Cyc_Absyn_UnknownCall_p_struct*)_tmp1E5)->f2;_LL196:
Cyc_Absyndump_dumpqvar(_tmp1F5);((void(*)(void(*f)(struct Cyc_Absyn_Pat*),struct
Cyc_List_List*l,struct _tagged_arr start,struct _tagged_arr end,struct _tagged_arr sep))
Cyc_Absyndump_group)(Cyc_Absyndump_dumppat,_tmp1F6,({const char*_tmp20D="(";
_tag_arr(_tmp20D,sizeof(char),_get_zero_arr_size(_tmp20D,2));}),({const char*
_tmp20E=")";_tag_arr(_tmp20E,sizeof(char),_get_zero_arr_size(_tmp20E,2));}),({
const char*_tmp20F=",";_tag_arr(_tmp20F,sizeof(char),_get_zero_arr_size(_tmp20F,2));}));
goto _LL17A;_LL197: if(_tmp1E5 <= (void*)2?1:*((int*)_tmp1E5)!= 5)goto _LL199;
_tmp1F7=((struct Cyc_Absyn_Aggr_p_struct*)_tmp1E5)->f1;_tmp1F8=(void*)_tmp1F7.aggr_info;
_tmp1F9=((struct Cyc_Absyn_Aggr_p_struct*)_tmp1E5)->f2;_tmp1FA=((struct Cyc_Absyn_Aggr_p_struct*)
_tmp1E5)->f3;_LL198: {struct _tuple0*_tmp211;struct _tuple3 _tmp210=Cyc_Absyn_aggr_kinded_name(
_tmp1F8);_tmp211=_tmp210.f2;Cyc_Absyndump_dumpqvar(_tmp211);Cyc_Absyndump_dump_char((
int)'{');((void(*)(void(*f)(struct Cyc_Absyn_Tvar*),struct Cyc_List_List*l,struct
_tagged_arr start,struct _tagged_arr end,struct _tagged_arr sep))Cyc_Absyndump_egroup)(
Cyc_Absyndump_dumptvar,_tmp1F9,({const char*_tmp212="[";_tag_arr(_tmp212,sizeof(
char),_get_zero_arr_size(_tmp212,2));}),({const char*_tmp213="]";_tag_arr(_tmp213,
sizeof(char),_get_zero_arr_size(_tmp213,2));}),({const char*_tmp214=",";_tag_arr(
_tmp214,sizeof(char),_get_zero_arr_size(_tmp214,2));}));((void(*)(void(*f)(
struct _tuple11*),struct Cyc_List_List*l,struct _tagged_arr start,struct _tagged_arr
end,struct _tagged_arr sep))Cyc_Absyndump_group)(Cyc_Absyndump_dumpdp,_tmp1FA,({
const char*_tmp215="";_tag_arr(_tmp215,sizeof(char),_get_zero_arr_size(_tmp215,1));}),({
const char*_tmp216="}";_tag_arr(_tmp216,sizeof(char),_get_zero_arr_size(_tmp216,2));}),({
const char*_tmp217=",";_tag_arr(_tmp217,sizeof(char),_get_zero_arr_size(_tmp217,2));}));
goto _LL17A;}_LL199: if(_tmp1E5 <= (void*)2?1:*((int*)_tmp1E5)!= 6)goto _LL19B;
_tmp1FB=((struct Cyc_Absyn_Tunion_p_struct*)_tmp1E5)->f2;_tmp1FC=((struct Cyc_Absyn_Tunion_p_struct*)
_tmp1E5)->f3;_LL19A: Cyc_Absyndump_dumpqvar(_tmp1FB->name);if(_tmp1FC != 0)((void(*)(
void(*f)(struct Cyc_Absyn_Pat*),struct Cyc_List_List*l,struct _tagged_arr start,
struct _tagged_arr end,struct _tagged_arr sep))Cyc_Absyndump_group)(Cyc_Absyndump_dumppat,
_tmp1FC,({const char*_tmp218="(";_tag_arr(_tmp218,sizeof(char),_get_zero_arr_size(
_tmp218,2));}),({const char*_tmp219=")";_tag_arr(_tmp219,sizeof(char),
_get_zero_arr_size(_tmp219,2));}),({const char*_tmp21A=",";_tag_arr(_tmp21A,
sizeof(char),_get_zero_arr_size(_tmp21A,2));}));goto _LL17A;_LL19B: if(_tmp1E5 <= (
void*)2?1:*((int*)_tmp1E5)!= 10)goto _LL19D;_tmp1FD=((struct Cyc_Absyn_Enum_p_struct*)
_tmp1E5)->f2;_LL19C: _tmp1FE=_tmp1FD;goto _LL19E;_LL19D: if(_tmp1E5 <= (void*)2?1:*((
int*)_tmp1E5)!= 11)goto _LL17A;_tmp1FE=((struct Cyc_Absyn_AnonEnum_p_struct*)
_tmp1E5)->f2;_LL19E: Cyc_Absyndump_dumpqvar(_tmp1FE->name);goto _LL17A;_LL17A:;}
void Cyc_Absyndump_dumptunionfield(struct Cyc_Absyn_Tunionfield*ef){Cyc_Absyndump_dumpqvar(
ef->name);if(ef->typs != 0)Cyc_Absyndump_dumpargs(ef->typs);}void Cyc_Absyndump_dumptunionfields(
struct Cyc_List_List*fields){((void(*)(void(*f)(struct Cyc_Absyn_Tunionfield*),
struct Cyc_List_List*l,struct _tagged_arr sep))Cyc_Absyndump_dump_sep)(Cyc_Absyndump_dumptunionfield,
fields,({const char*_tmp21B=",";_tag_arr(_tmp21B,sizeof(char),_get_zero_arr_size(
_tmp21B,2));}));}void Cyc_Absyndump_dumpenumfield(struct Cyc_Absyn_Enumfield*ef){
Cyc_Absyndump_dumpqvar(ef->name);if(ef->tag != 0){Cyc_Absyndump_dump(({const char*
_tmp21C=" = ";_tag_arr(_tmp21C,sizeof(char),_get_zero_arr_size(_tmp21C,4));}));
Cyc_Absyndump_dumpexp((struct Cyc_Absyn_Exp*)_check_null(ef->tag));}}void Cyc_Absyndump_dumpenumfields(
struct Cyc_List_List*fields){((void(*)(void(*f)(struct Cyc_Absyn_Enumfield*),
struct Cyc_List_List*l,struct _tagged_arr sep))Cyc_Absyndump_dump_sep)(Cyc_Absyndump_dumpenumfield,
fields,({const char*_tmp21D=",";_tag_arr(_tmp21D,sizeof(char),_get_zero_arr_size(
_tmp21D,2));}));}void Cyc_Absyndump_dumpaggrfields(struct Cyc_List_List*fields){
for(0;fields != 0;fields=fields->tl){struct Cyc_Absyn_Aggrfield _tmp21F;struct
_tagged_arr*_tmp220;struct Cyc_Absyn_Tqual _tmp221;void*_tmp222;struct Cyc_Absyn_Exp*
_tmp223;struct Cyc_List_List*_tmp224;struct Cyc_Absyn_Aggrfield*_tmp21E=(struct Cyc_Absyn_Aggrfield*)
fields->hd;_tmp21F=*_tmp21E;_tmp220=_tmp21F.name;_tmp221=_tmp21F.tq;_tmp222=(
void*)_tmp21F.type;_tmp223=_tmp21F.width;_tmp224=_tmp21F.attributes;((void(*)(
struct Cyc_Absyn_Tqual,void*,void(*f)(struct _tagged_arr*),struct _tagged_arr*))Cyc_Absyndump_dumptqtd)(
_tmp221,_tmp222,Cyc_Absyndump_dump_str,_tmp220);Cyc_Absyndump_dumpatts(_tmp224);
if(_tmp223 != 0){Cyc_Absyndump_dump_char((int)':');Cyc_Absyndump_dumpexp((struct
Cyc_Absyn_Exp*)_tmp223);}Cyc_Absyndump_dump_semi();}}void Cyc_Absyndump_dumptypedefname(
struct Cyc_Absyn_Typedefdecl*td){Cyc_Absyndump_dumpqvar(td->name);Cyc_Absyndump_dumptvars(
td->tvs);}static void Cyc_Absyndump_dump_atts_qvar(struct Cyc_Absyn_Fndecl*fd){Cyc_Absyndump_dumpatts(
fd->attributes);Cyc_Absyndump_dumpqvar(fd->name);}static void Cyc_Absyndump_dump_callconv_qvar(
struct _tuple3*pr){{void*_tmp225=(*pr).f1;_LL1A0: if((int)_tmp225 != 8)goto _LL1A2;
_LL1A1: goto _LL19F;_LL1A2: if((int)_tmp225 != 0)goto _LL1A4;_LL1A3: Cyc_Absyndump_dump(({
const char*_tmp226="_stdcall";_tag_arr(_tmp226,sizeof(char),_get_zero_arr_size(
_tmp226,9));}));goto _LL19F;_LL1A4: if((int)_tmp225 != 1)goto _LL1A6;_LL1A5: Cyc_Absyndump_dump(({
const char*_tmp227="_cdecl";_tag_arr(_tmp227,sizeof(char),_get_zero_arr_size(
_tmp227,7));}));goto _LL19F;_LL1A6: if((int)_tmp225 != 2)goto _LL1A8;_LL1A7: Cyc_Absyndump_dump(({
const char*_tmp228="_fastcall";_tag_arr(_tmp228,sizeof(char),_get_zero_arr_size(
_tmp228,10));}));goto _LL19F;_LL1A8:;_LL1A9: goto _LL19F;_LL19F:;}Cyc_Absyndump_dumpqvar((*
pr).f2);}static void Cyc_Absyndump_dump_callconv_fdqvar(struct Cyc_Absyn_Fndecl*fd){
Cyc_Absyndump_dump_callconv(fd->attributes);Cyc_Absyndump_dumpqvar(fd->name);}
static void Cyc_Absyndump_dumpids(struct Cyc_List_List*vds){for(0;vds != 0;vds=vds->tl){
Cyc_Absyndump_dumpqvar(((struct Cyc_Absyn_Vardecl*)vds->hd)->name);if(vds->tl != 0)
Cyc_Absyndump_dump_char((int)',');}}void Cyc_Absyndump_dumpvardecl(struct Cyc_Absyn_Vardecl*
vd,struct Cyc_Position_Segment*loc){struct Cyc_Absyn_Vardecl _tmp22A;void*_tmp22B;
struct _tuple0*_tmp22C;struct Cyc_Absyn_Tqual _tmp22D;void*_tmp22E;struct Cyc_Absyn_Exp*
_tmp22F;struct Cyc_List_List*_tmp230;struct Cyc_Absyn_Vardecl*_tmp229=vd;_tmp22A=*
_tmp229;_tmp22B=(void*)_tmp22A.sc;_tmp22C=_tmp22A.name;_tmp22D=_tmp22A.tq;
_tmp22E=(void*)_tmp22A.type;_tmp22F=_tmp22A.initializer;_tmp230=_tmp22A.attributes;
Cyc_Absyndump_dumploc(loc);if(Cyc_Absyndump_to_VC){Cyc_Absyndump_dumpatts(
_tmp230);Cyc_Absyndump_dumpscope(_tmp22B);{struct Cyc_Absyn_Tqual _tmp232;void*
_tmp233;struct Cyc_List_List*_tmp234;struct _tuple5 _tmp231=Cyc_Absynpp_to_tms(
_tmp22D,_tmp22E);_tmp232=_tmp231.f1;_tmp233=_tmp231.f2;_tmp234=_tmp231.f3;{void*
call_conv=(void*)8;{struct Cyc_List_List*tms2=_tmp234;for(0;tms2 != 0;tms2=tms2->tl){
void*_tmp235=(void*)tms2->hd;struct Cyc_List_List*_tmp236;_LL1AB: if(*((int*)
_tmp235)!= 5)goto _LL1AD;_tmp236=((struct Cyc_Absyn_Attributes_mod_struct*)_tmp235)->f2;
_LL1AC: for(0;_tmp236 != 0;_tmp236=_tmp236->tl){void*_tmp237=(void*)_tmp236->hd;
_LL1B0: if((int)_tmp237 != 0)goto _LL1B2;_LL1B1: call_conv=(void*)0;goto _LL1AF;
_LL1B2: if((int)_tmp237 != 1)goto _LL1B4;_LL1B3: call_conv=(void*)1;goto _LL1AF;
_LL1B4: if((int)_tmp237 != 2)goto _LL1B6;_LL1B5: call_conv=(void*)2;goto _LL1AF;
_LL1B6:;_LL1B7: goto _LL1AF;_LL1AF:;}goto _LL1AA;_LL1AD:;_LL1AE: goto _LL1AA;_LL1AA:;}}
Cyc_Absyndump_dumptq(_tmp232);Cyc_Absyndump_dumpntyp(_tmp233);{struct _tuple3
_tmp238=({struct _tuple3 _tmp239;_tmp239.f1=call_conv;_tmp239.f2=_tmp22C;_tmp239;});((
void(*)(struct Cyc_List_List*tms,void(*f)(struct _tuple3*),struct _tuple3*a))Cyc_Absyndump_dumptms)(
Cyc_List_imp_rev(_tmp234),Cyc_Absyndump_dump_callconv_qvar,& _tmp238);}}}}else{
if(_tmp22B == (void*)3?Cyc_Absyndump_qvar_to_Cids: 0){void*_tmp23A=Cyc_Tcutil_compress(
_tmp22E);_LL1B9: if(_tmp23A <= (void*)3?1:*((int*)_tmp23A)!= 8)goto _LL1BB;_LL1BA:
goto _LL1B8;_LL1BB:;_LL1BC: Cyc_Absyndump_dumpscope(_tmp22B);_LL1B8:;}else{Cyc_Absyndump_dumpscope(
_tmp22B);}((void(*)(struct Cyc_Absyn_Tqual,void*,void(*f)(struct _tuple0*),struct
_tuple0*))Cyc_Absyndump_dumptqtd)(_tmp22D,_tmp22E,Cyc_Absyndump_dumpqvar,_tmp22C);
Cyc_Absyndump_dumpatts(_tmp230);}if(_tmp22F != 0){Cyc_Absyndump_dump_char((int)'=');
Cyc_Absyndump_dumpexp((struct Cyc_Absyn_Exp*)_tmp22F);}Cyc_Absyndump_dump_semi();}
void Cyc_Absyndump_dumpdecl(struct Cyc_Absyn_Decl*d){void*_tmp23B=(void*)d->r;
struct Cyc_Absyn_Vardecl*_tmp23C;struct Cyc_Absyn_Fndecl*_tmp23D;struct Cyc_Absyn_Aggrdecl*
_tmp23E;struct Cyc_Absyn_Tuniondecl*_tmp23F;struct Cyc_Absyn_Tuniondecl _tmp240;
void*_tmp241;struct _tuple0*_tmp242;struct Cyc_List_List*_tmp243;struct Cyc_Core_Opt*
_tmp244;int _tmp245;struct Cyc_Absyn_Enumdecl*_tmp246;struct Cyc_Absyn_Enumdecl
_tmp247;void*_tmp248;struct _tuple0*_tmp249;struct Cyc_Core_Opt*_tmp24A;struct Cyc_Absyn_Pat*
_tmp24B;struct Cyc_Absyn_Exp*_tmp24C;struct Cyc_List_List*_tmp24D;struct Cyc_Absyn_Typedefdecl*
_tmp24E;struct _tagged_arr*_tmp24F;struct Cyc_List_List*_tmp250;struct _tuple0*
_tmp251;struct Cyc_List_List*_tmp252;struct Cyc_List_List*_tmp253;_LL1BE: if(*((int*)
_tmp23B)!= 0)goto _LL1C0;_tmp23C=((struct Cyc_Absyn_Var_d_struct*)_tmp23B)->f1;
_LL1BF: Cyc_Absyndump_dumpvardecl(_tmp23C,d->loc);goto _LL1BD;_LL1C0: if(*((int*)
_tmp23B)!= 1)goto _LL1C2;_tmp23D=((struct Cyc_Absyn_Fn_d_struct*)_tmp23B)->f1;
_LL1C1: Cyc_Absyndump_dumploc(d->loc);if(Cyc_Absyndump_to_VC)Cyc_Absyndump_dumpatts(
_tmp23D->attributes);if(_tmp23D->is_inline){if(Cyc_Absyndump_to_VC)Cyc_Absyndump_dump(({
const char*_tmp254="__inline";_tag_arr(_tmp254,sizeof(char),_get_zero_arr_size(
_tmp254,9));}));else{Cyc_Absyndump_dump(({const char*_tmp255="inline";_tag_arr(
_tmp255,sizeof(char),_get_zero_arr_size(_tmp255,7));}));}}Cyc_Absyndump_dumpscope((
void*)_tmp23D->sc);{void*t=(void*)({struct Cyc_Absyn_FnType_struct*_tmp256=
_cycalloc(sizeof(*_tmp256));_tmp256[0]=({struct Cyc_Absyn_FnType_struct _tmp257;
_tmp257.tag=8;_tmp257.f1=({struct Cyc_Absyn_FnInfo _tmp258;_tmp258.tvars=_tmp23D->tvs;
_tmp258.effect=_tmp23D->effect;_tmp258.ret_typ=(void*)((void*)_tmp23D->ret_type);
_tmp258.args=((struct Cyc_List_List*(*)(struct _tuple1*(*f)(struct _tuple4*),struct
Cyc_List_List*x))Cyc_List_map)(Cyc_Absynpp_arg_mk_opt,_tmp23D->args);_tmp258.c_varargs=
_tmp23D->c_varargs;_tmp258.cyc_varargs=_tmp23D->cyc_varargs;_tmp258.rgn_po=
_tmp23D->rgn_po;_tmp258.attributes=0;_tmp258;});_tmp257;});_tmp256;});((void(*)(
struct Cyc_Absyn_Tqual,void*,void(*f)(struct Cyc_Absyn_Fndecl*),struct Cyc_Absyn_Fndecl*))
Cyc_Absyndump_dumptqtd)(Cyc_Absyn_empty_tqual(),t,Cyc_Absyndump_to_VC?Cyc_Absyndump_dump_callconv_fdqvar:
Cyc_Absyndump_dump_atts_qvar,_tmp23D);Cyc_Absyndump_dump_char((int)'{');Cyc_Absyndump_dumpstmt(
_tmp23D->body);Cyc_Absyndump_dump_char((int)'}');goto _LL1BD;}_LL1C2: if(*((int*)
_tmp23B)!= 4)goto _LL1C4;_tmp23E=((struct Cyc_Absyn_Aggr_d_struct*)_tmp23B)->f1;
_LL1C3: Cyc_Absyndump_dumpscope((void*)_tmp23E->sc);Cyc_Absyndump_dumpaggr_kind((
void*)_tmp23E->kind);Cyc_Absyndump_dumpqvar(_tmp23E->name);Cyc_Absyndump_dumptvars(
_tmp23E->tvs);if(_tmp23E->impl == 0)Cyc_Absyndump_dump_semi();else{Cyc_Absyndump_dump_char((
int)'{');if(((struct Cyc_Absyn_AggrdeclImpl*)_check_null(_tmp23E->impl))->exist_vars
!= 0)((void(*)(void(*f)(struct Cyc_Absyn_Tvar*),struct Cyc_List_List*l,struct
_tagged_arr start,struct _tagged_arr end,struct _tagged_arr sep))Cyc_Absyndump_egroup)(
Cyc_Absyndump_dumpkindedtvar,((struct Cyc_Absyn_AggrdeclImpl*)_check_null(_tmp23E->impl))->exist_vars,({
const char*_tmp259="<";_tag_arr(_tmp259,sizeof(char),_get_zero_arr_size(_tmp259,2));}),({
const char*_tmp25A=">";_tag_arr(_tmp25A,sizeof(char),_get_zero_arr_size(_tmp25A,2));}),({
const char*_tmp25B=",";_tag_arr(_tmp25B,sizeof(char),_get_zero_arr_size(_tmp25B,2));}));
if(((struct Cyc_Absyn_AggrdeclImpl*)_check_null(_tmp23E->impl))->rgn_po != 0){Cyc_Absyndump_dump_char((
int)':');Cyc_Absyndump_dump_rgnpo(((struct Cyc_Absyn_AggrdeclImpl*)_check_null(
_tmp23E->impl))->rgn_po);}Cyc_Absyndump_dumpaggrfields(((struct Cyc_Absyn_AggrdeclImpl*)
_check_null(_tmp23E->impl))->fields);Cyc_Absyndump_dump(({const char*_tmp25C="}";
_tag_arr(_tmp25C,sizeof(char),_get_zero_arr_size(_tmp25C,2));}));Cyc_Absyndump_dumpatts(
_tmp23E->attributes);Cyc_Absyndump_dump(({const char*_tmp25D=";";_tag_arr(_tmp25D,
sizeof(char),_get_zero_arr_size(_tmp25D,2));}));}goto _LL1BD;_LL1C4: if(*((int*)
_tmp23B)!= 5)goto _LL1C6;_tmp23F=((struct Cyc_Absyn_Tunion_d_struct*)_tmp23B)->f1;
_tmp240=*_tmp23F;_tmp241=(void*)_tmp240.sc;_tmp242=_tmp240.name;_tmp243=_tmp240.tvs;
_tmp244=_tmp240.fields;_tmp245=_tmp240.is_xtunion;_LL1C5: Cyc_Absyndump_dumpscope(
_tmp241);Cyc_Absyndump_dump(_tmp245?({const char*_tmp25E="xtunion";_tag_arr(
_tmp25E,sizeof(char),_get_zero_arr_size(_tmp25E,8));}):({const char*_tmp25F="tunion";
_tag_arr(_tmp25F,sizeof(char),_get_zero_arr_size(_tmp25F,7));}));Cyc_Absyndump_dumpqvar(
_tmp242);Cyc_Absyndump_dumptvars(_tmp243);if(_tmp244 == 0)Cyc_Absyndump_dump_semi();
else{Cyc_Absyndump_dump_char((int)'{');Cyc_Absyndump_dumptunionfields((struct Cyc_List_List*)
_tmp244->v);Cyc_Absyndump_dump_nospace(({const char*_tmp260="};";_tag_arr(_tmp260,
sizeof(char),_get_zero_arr_size(_tmp260,3));}));}goto _LL1BD;_LL1C6: if(*((int*)
_tmp23B)!= 6)goto _LL1C8;_tmp246=((struct Cyc_Absyn_Enum_d_struct*)_tmp23B)->f1;
_tmp247=*_tmp246;_tmp248=(void*)_tmp247.sc;_tmp249=_tmp247.name;_tmp24A=_tmp247.fields;
_LL1C7: Cyc_Absyndump_dumpscope(_tmp248);Cyc_Absyndump_dump(({const char*_tmp261="enum ";
_tag_arr(_tmp261,sizeof(char),_get_zero_arr_size(_tmp261,6));}));Cyc_Absyndump_dumpqvar(
_tmp249);if(_tmp24A == 0)Cyc_Absyndump_dump_semi();else{Cyc_Absyndump_dump_char((
int)'{');Cyc_Absyndump_dumpenumfields((struct Cyc_List_List*)_tmp24A->v);Cyc_Absyndump_dump_nospace(({
const char*_tmp262="};";_tag_arr(_tmp262,sizeof(char),_get_zero_arr_size(_tmp262,
3));}));}return;_LL1C8: if(*((int*)_tmp23B)!= 2)goto _LL1CA;_tmp24B=((struct Cyc_Absyn_Let_d_struct*)
_tmp23B)->f1;_tmp24C=((struct Cyc_Absyn_Let_d_struct*)_tmp23B)->f3;_LL1C9: Cyc_Absyndump_dump(({
const char*_tmp263="let";_tag_arr(_tmp263,sizeof(char),_get_zero_arr_size(_tmp263,
4));}));Cyc_Absyndump_dumppat(_tmp24B);Cyc_Absyndump_dump_char((int)'=');Cyc_Absyndump_dumpexp(
_tmp24C);Cyc_Absyndump_dump_semi();goto _LL1BD;_LL1CA: if(*((int*)_tmp23B)!= 3)
goto _LL1CC;_tmp24D=((struct Cyc_Absyn_Letv_d_struct*)_tmp23B)->f1;_LL1CB: Cyc_Absyndump_dump(({
const char*_tmp264="let ";_tag_arr(_tmp264,sizeof(char),_get_zero_arr_size(
_tmp264,5));}));Cyc_Absyndump_dumpids(_tmp24D);Cyc_Absyndump_dump_semi();goto
_LL1BD;_LL1CC: if(*((int*)_tmp23B)!= 7)goto _LL1CE;_tmp24E=((struct Cyc_Absyn_Typedef_d_struct*)
_tmp23B)->f1;_LL1CD: if(!Cyc_Absyndump_expand_typedefs?1:(_tmp24E->defn != 0?Cyc_Absynpp_is_anon_aggrtype((
void*)((struct Cyc_Core_Opt*)_check_null(_tmp24E->defn))->v): 0)){Cyc_Absyndump_dump(({
const char*_tmp265="typedef";_tag_arr(_tmp265,sizeof(char),_get_zero_arr_size(
_tmp265,8));}));{void*t;if(_tmp24E->defn == 0)t=Cyc_Absyn_new_evar(_tmp24E->kind,
0);else{t=(void*)((struct Cyc_Core_Opt*)_check_null(_tmp24E->defn))->v;}((void(*)(
struct Cyc_Absyn_Tqual,void*,void(*f)(struct Cyc_Absyn_Typedefdecl*),struct Cyc_Absyn_Typedefdecl*))
Cyc_Absyndump_dumptqtd)(_tmp24E->tq,t,Cyc_Absyndump_dumptypedefname,_tmp24E);Cyc_Absyndump_dumpatts(
_tmp24E->atts);Cyc_Absyndump_dump_semi();}}goto _LL1BD;_LL1CE: if(*((int*)_tmp23B)
!= 8)goto _LL1D0;_tmp24F=((struct Cyc_Absyn_Namespace_d_struct*)_tmp23B)->f1;
_tmp250=((struct Cyc_Absyn_Namespace_d_struct*)_tmp23B)->f2;_LL1CF: Cyc_Absyndump_dump(({
const char*_tmp266="namespace";_tag_arr(_tmp266,sizeof(char),_get_zero_arr_size(
_tmp266,10));}));Cyc_Absyndump_dump_str(_tmp24F);Cyc_Absyndump_dump_char((int)'{');
for(0;_tmp250 != 0;_tmp250=_tmp250->tl){Cyc_Absyndump_dumpdecl((struct Cyc_Absyn_Decl*)
_tmp250->hd);}Cyc_Absyndump_dump_char((int)'}');goto _LL1BD;_LL1D0: if(*((int*)
_tmp23B)!= 9)goto _LL1D2;_tmp251=((struct Cyc_Absyn_Using_d_struct*)_tmp23B)->f1;
_tmp252=((struct Cyc_Absyn_Using_d_struct*)_tmp23B)->f2;_LL1D1: Cyc_Absyndump_dump(({
const char*_tmp267="using";_tag_arr(_tmp267,sizeof(char),_get_zero_arr_size(
_tmp267,6));}));Cyc_Absyndump_dumpqvar(_tmp251);Cyc_Absyndump_dump_char((int)'{');
for(0;_tmp252 != 0;_tmp252=_tmp252->tl){Cyc_Absyndump_dumpdecl((struct Cyc_Absyn_Decl*)
_tmp252->hd);}Cyc_Absyndump_dump_char((int)'}');goto _LL1BD;_LL1D2: if(*((int*)
_tmp23B)!= 10)goto _LL1BD;_tmp253=((struct Cyc_Absyn_ExternC_d_struct*)_tmp23B)->f1;
_LL1D3: Cyc_Absyndump_dump(({const char*_tmp268="extern \"C\" {";_tag_arr(_tmp268,
sizeof(char),_get_zero_arr_size(_tmp268,13));}));for(0;_tmp253 != 0;_tmp253=
_tmp253->tl){Cyc_Absyndump_dumpdecl((struct Cyc_Absyn_Decl*)_tmp253->hd);}Cyc_Absyndump_dump_char((
int)'}');goto _LL1BD;_LL1BD:;}static void Cyc_Absyndump_dump_upperbound(struct Cyc_Absyn_Exp*
e){struct _tuple6 pr=Cyc_Evexp_eval_const_uint_exp(e);if(pr.f1 != 1?1: !pr.f2){Cyc_Absyndump_dump_char((
int)'{');Cyc_Absyndump_dumpexp(e);Cyc_Absyndump_dump_char((int)'}');}}void Cyc_Absyndump_dumptms(
struct Cyc_List_List*tms,void(*f)(void*),void*a){if(tms == 0){f(a);return;}{void*
_tmp269=(void*)tms->hd;struct Cyc_Absyn_PtrAtts _tmp26A;void*_tmp26B;struct Cyc_Absyn_Conref*
_tmp26C;struct Cyc_Absyn_Conref*_tmp26D;struct Cyc_Absyn_Conref*_tmp26E;struct Cyc_Absyn_Tqual
_tmp26F;_LL1D5: if(*((int*)_tmp269)!= 2)goto _LL1D7;_tmp26A=((struct Cyc_Absyn_Pointer_mod_struct*)
_tmp269)->f1;_tmp26B=(void*)_tmp26A.rgn;_tmp26C=_tmp26A.nullable;_tmp26D=_tmp26A.bounds;
_tmp26E=_tmp26A.zero_term;_tmp26F=((struct Cyc_Absyn_Pointer_mod_struct*)_tmp269)->f2;
_LL1D6:{void*_tmp270=Cyc_Absyn_conref_def(Cyc_Absyn_bounds_one,_tmp26D);struct
Cyc_Absyn_Exp*_tmp271;void*_tmp272;_LL1DA: if((int)_tmp270 != 0)goto _LL1DC;_LL1DB:
Cyc_Absyndump_dump_char((int)'?');goto _LL1D9;_LL1DC: if(_tmp270 <= (void*)1?1:*((
int*)_tmp270)!= 0)goto _LL1DE;_tmp271=((struct Cyc_Absyn_Upper_b_struct*)_tmp270)->f1;
_LL1DD: Cyc_Absyndump_dump_char((int)(((int(*)(int,struct Cyc_Absyn_Conref*x))Cyc_Absyn_conref_def)(
1,_tmp26C)?'*':'@'));Cyc_Absyndump_dump_upperbound(_tmp271);goto _LL1D9;_LL1DE:
if(_tmp270 <= (void*)1?1:*((int*)_tmp270)!= 1)goto _LL1D9;_tmp272=(void*)((struct
Cyc_Absyn_AbsUpper_b_struct*)_tmp270)->f1;_LL1DF: Cyc_Absyndump_dump_char((int)(((
int(*)(int,struct Cyc_Absyn_Conref*x))Cyc_Absyn_conref_def)(1,_tmp26C)?'*':'@'));
Cyc_Absyndump_dump_char((int)'{');Cyc_Absyndump_dumptyp(_tmp272);Cyc_Absyndump_dump_char((
int)'}');_LL1D9:;}if(((int(*)(int,struct Cyc_Absyn_Conref*x))Cyc_Absyn_conref_def)(
0,_tmp26E))Cyc_Absyndump_dump(({const char*_tmp273="ZEROTERM";_tag_arr(_tmp273,
sizeof(char),_get_zero_arr_size(_tmp273,9));}));{void*_tmp274=Cyc_Tcutil_compress(
_tmp26B);struct Cyc_Absyn_Tvar*_tmp275;_LL1E1: if((int)_tmp274 != 2)goto _LL1E3;
_LL1E2: goto _LL1E0;_LL1E3: if(_tmp274 <= (void*)3?1:*((int*)_tmp274)!= 1)goto _LL1E5;
_tmp275=((struct Cyc_Absyn_VarType_struct*)_tmp274)->f1;_LL1E4: Cyc_Absyndump_dump_str(
_tmp275->name);goto _LL1E0;_LL1E5:;_LL1E6:({void*_tmp276[0]={};Cyc_Tcutil_impos(({
const char*_tmp277="dumptms: bad rgn type in Pointer_mod";_tag_arr(_tmp277,
sizeof(char),_get_zero_arr_size(_tmp277,37));}),_tag_arr(_tmp276,sizeof(void*),0));});
_LL1E0:;}Cyc_Absyndump_dumptq(_tmp26F);Cyc_Absyndump_dumptms(tms->tl,f,a);
return;_LL1D7:;_LL1D8: {int next_is_pointer=0;if(tms->tl != 0){void*_tmp278=(void*)((
struct Cyc_List_List*)_check_null(tms->tl))->hd;_LL1E8: if(*((int*)_tmp278)!= 2)
goto _LL1EA;_LL1E9: next_is_pointer=1;goto _LL1E7;_LL1EA:;_LL1EB: goto _LL1E7;_LL1E7:;}
if(next_is_pointer)Cyc_Absyndump_dump_char((int)'(');Cyc_Absyndump_dumptms(tms->tl,
f,a);if(next_is_pointer)Cyc_Absyndump_dump_char((int)')');{void*_tmp279=(void*)
tms->hd;struct Cyc_Absyn_Conref*_tmp27A;struct Cyc_Absyn_Exp*_tmp27B;struct Cyc_Absyn_Conref*
_tmp27C;void*_tmp27D;struct Cyc_List_List*_tmp27E;int _tmp27F;struct Cyc_Absyn_VarargInfo*
_tmp280;struct Cyc_Core_Opt*_tmp281;struct Cyc_List_List*_tmp282;void*_tmp283;
struct Cyc_List_List*_tmp284;struct Cyc_Position_Segment*_tmp285;struct Cyc_List_List*
_tmp286;struct Cyc_Position_Segment*_tmp287;int _tmp288;struct Cyc_List_List*
_tmp289;_LL1ED: if(*((int*)_tmp279)!= 0)goto _LL1EF;_tmp27A=((struct Cyc_Absyn_Carray_mod_struct*)
_tmp279)->f1;_LL1EE: Cyc_Absyndump_dump(({const char*_tmp28A="[]";_tag_arr(_tmp28A,
sizeof(char),_get_zero_arr_size(_tmp28A,3));}));if(((int(*)(int,struct Cyc_Absyn_Conref*
x))Cyc_Absyn_conref_def)(0,_tmp27A))Cyc_Absyndump_dump(({const char*_tmp28B="ZEROTERM";
_tag_arr(_tmp28B,sizeof(char),_get_zero_arr_size(_tmp28B,9));}));goto _LL1EC;
_LL1EF: if(*((int*)_tmp279)!= 1)goto _LL1F1;_tmp27B=((struct Cyc_Absyn_ConstArray_mod_struct*)
_tmp279)->f1;_tmp27C=((struct Cyc_Absyn_ConstArray_mod_struct*)_tmp279)->f2;
_LL1F0: Cyc_Absyndump_dump_char((int)'[');Cyc_Absyndump_dumpexp(_tmp27B);Cyc_Absyndump_dump_char((
int)']');if(((int(*)(int,struct Cyc_Absyn_Conref*x))Cyc_Absyn_conref_def)(0,
_tmp27C))Cyc_Absyndump_dump(({const char*_tmp28C="ZEROTERM";_tag_arr(_tmp28C,
sizeof(char),_get_zero_arr_size(_tmp28C,9));}));goto _LL1EC;_LL1F1: if(*((int*)
_tmp279)!= 3)goto _LL1F3;_tmp27D=(void*)((struct Cyc_Absyn_Function_mod_struct*)
_tmp279)->f1;if(*((int*)_tmp27D)!= 1)goto _LL1F3;_tmp27E=((struct Cyc_Absyn_WithTypes_struct*)
_tmp27D)->f1;_tmp27F=((struct Cyc_Absyn_WithTypes_struct*)_tmp27D)->f2;_tmp280=((
struct Cyc_Absyn_WithTypes_struct*)_tmp27D)->f3;_tmp281=((struct Cyc_Absyn_WithTypes_struct*)
_tmp27D)->f4;_tmp282=((struct Cyc_Absyn_WithTypes_struct*)_tmp27D)->f5;_LL1F2: Cyc_Absyndump_dumpfunargs(
_tmp27E,_tmp27F,_tmp280,_tmp281,_tmp282);goto _LL1EC;_LL1F3: if(*((int*)_tmp279)!= 
3)goto _LL1F5;_tmp283=(void*)((struct Cyc_Absyn_Function_mod_struct*)_tmp279)->f1;
if(*((int*)_tmp283)!= 0)goto _LL1F5;_tmp284=((struct Cyc_Absyn_NoTypes_struct*)
_tmp283)->f1;_tmp285=((struct Cyc_Absyn_NoTypes_struct*)_tmp283)->f2;_LL1F4:((
void(*)(void(*f)(struct _tagged_arr*),struct Cyc_List_List*l,struct _tagged_arr
start,struct _tagged_arr end,struct _tagged_arr sep))Cyc_Absyndump_group)(Cyc_Absyndump_dump_str,
_tmp284,({const char*_tmp28D="(";_tag_arr(_tmp28D,sizeof(char),_get_zero_arr_size(
_tmp28D,2));}),({const char*_tmp28E=")";_tag_arr(_tmp28E,sizeof(char),
_get_zero_arr_size(_tmp28E,2));}),({const char*_tmp28F=",";_tag_arr(_tmp28F,
sizeof(char),_get_zero_arr_size(_tmp28F,2));}));goto _LL1EC;_LL1F5: if(*((int*)
_tmp279)!= 4)goto _LL1F7;_tmp286=((struct Cyc_Absyn_TypeParams_mod_struct*)_tmp279)->f1;
_tmp287=((struct Cyc_Absyn_TypeParams_mod_struct*)_tmp279)->f2;_tmp288=((struct
Cyc_Absyn_TypeParams_mod_struct*)_tmp279)->f3;_LL1F6: if(_tmp288)Cyc_Absyndump_dumpkindedtvars(
_tmp286);else{Cyc_Absyndump_dumptvars(_tmp286);}goto _LL1EC;_LL1F7: if(*((int*)
_tmp279)!= 5)goto _LL1F9;_tmp289=((struct Cyc_Absyn_Attributes_mod_struct*)_tmp279)->f2;
_LL1F8: Cyc_Absyndump_dumpatts(_tmp289);goto _LL1EC;_LL1F9: if(*((int*)_tmp279)!= 2)
goto _LL1EC;_LL1FA:({void*_tmp290[0]={};Cyc_Tcutil_impos(({const char*_tmp291="dumptms";
_tag_arr(_tmp291,sizeof(char),_get_zero_arr_size(_tmp291,8));}),_tag_arr(_tmp290,
sizeof(void*),0));});_LL1EC:;}return;}_LL1D4:;}}void Cyc_Absyndump_dumptqtd(
struct Cyc_Absyn_Tqual tq,void*t,void(*f)(void*),void*a){struct Cyc_Absyn_Tqual
_tmp293;void*_tmp294;struct Cyc_List_List*_tmp295;struct _tuple5 _tmp292=Cyc_Absynpp_to_tms(
tq,t);_tmp293=_tmp292.f1;_tmp294=_tmp292.f2;_tmp295=_tmp292.f3;Cyc_Absyndump_dumptq(
_tmp293);Cyc_Absyndump_dumpntyp(_tmp294);Cyc_Absyndump_dumptms(Cyc_List_imp_rev(
_tmp295),f,a);}void Cyc_Absyndump_dumpdecllist2file(struct Cyc_List_List*tdl,
struct Cyc___cycFILE*f){Cyc_Absyndump_pos=0;*Cyc_Absyndump_dump_file=f;for(0;tdl
!= 0;tdl=tdl->tl){Cyc_Absyndump_dumpdecl((struct Cyc_Absyn_Decl*)tdl->hd);}({void*
_tmp296[0]={};Cyc_fprintf(f,({const char*_tmp297="\n";_tag_arr(_tmp297,sizeof(
char),_get_zero_arr_size(_tmp297,2));}),_tag_arr(_tmp296,sizeof(void*),0));});}