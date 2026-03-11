/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__IOU
#define _nrn_initial _nrn_initial__IOU
#define nrn_cur _nrn_cur__IOU
#define _nrn_current _nrn_current__IOU
#define nrn_jacob _nrn_jacob__IOU
#define nrn_state _nrn_state__IOU
#define _net_receive _net_receive__IOU 
#define new_seed new_seed__IOU 
#define oup oup__IOU 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define mean_i _p[0]
#define std_i _p[1]
#define tau_i _p[2]
#define i _p[3]
#define i1 _p[4]
#define D_i _p[5]
#define exp_i _p[6]
#define amp_i _p[7]
#define _g _p[8]
#define _nd_area  *_ppvar[0]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 /* declaration of user functions */
 static double _hoc_new_seed();
 static double _hoc_oup();
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 "new_seed", _hoc_new_seed,
 "oup", _hoc_oup,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "mean_i", "nA",
 "std_i", "nA",
 "tau_i", "ms",
 "i", "nA",
 0,0
};
 static double delta_t = 1;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 
static int _ode_count(int);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"IOU",
 "mean_i",
 "std_i",
 "tau_i",
 0,
 "i",
 0,
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 9, _prop);
 	/*initialize range parameters*/
 	mean_i = 0;
 	std_i = 0.3;
 	tau_i = 3;
  }
 	_prop->param = _p;
 	_prop->param_size = 9;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 2, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _IOU_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 9, 2);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
 	hoc_register_cvode(_mechtype, _ode_count, 0, 0, 0);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 IOU C:/Users/bpg/Desktop/Projects/Contextual Data Science/Projects/L5PC PID/Code/BahlEtAl2012 - BPG/channels/IOU.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int new_seed(double);
static int oup();
 
/*VERBATIM*/
  float gasdevi();
  float ran1i(long *idem);
 
static int  oup (  ) {
   if ( tau_i  != 0.0 ) {
     i1 = exp_i * i1 + amp_i * gasdevi ( _threadargs_ ) ;
     }
   else {
     i1 = std_i * gasdevi ( _threadargs_ ) ;
     }
    return 0; }
 
static double _hoc_oup(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 oup (  );
 return(_r);
}
 
/*VERBATIM*/

#include <math.h> 

#define IA 16807 
#define IM 2147483647 
#define AM (1.0/IM) 
#define IQ 127773 
#define IR 2836 
#define NTAB 32 
#define NDIV (1+(IM-1)/NTAB) 
#define EPS 1.2e-7 
#define RNMX (1.0-EPS)

long idumi;

//------------------------------------------------------------------------------
// Minimal" random number generator of Park and Miller with Bays-Durham 
// shuffle and added safeguards. Returns a uniform random deviate between 
// 0.0 and 1.0 (exclusive of the endpoint values). Call with idum a 
// negative integer to initialize; thereafter, do not alter idum between 
// successive deviates in a sequence. RNMX should approximate the largest 
// floating value that is less than 1.
//------------------------------------------------------------------------------
float ran1i(long *idum) 
{
  int j; 
  long k; 
  static long iy=0; 
  static long iv[NTAB]; 
  float temp;
  
  if (*idum <= 0 || !iy) 
  {
    if (-(*idum) < 1) *idum=1; 
    else *idum = -(*idum);
  
    for (j=NTAB+7;j>=0;j--) 
    {
      k=(*idum)/IQ; 
      *idum=IA*(*idum-k*IQ)-IR*k; 
      if (*idum < 0) *idum += IM; 
      if (j < NTAB) iv[j] = *idum; 
    } 
    
    iy=iv[0]; 
  } 

  k=(*idum)/IQ;
  *idum=IA*(*idum-k*IQ)-IR*k;
  if (*idum < 0) *idum += IM;
  j=iy/NDIV;
  iy=iv[j];
  iv[j] = *idum;
  
  if ((temp=AM*iy) > RNMX) return RNMX;
  else return temp; 
}

//------------------------------------------------------------------------------
// Returns a normally distributed deviate with zero mean and 
// unit variance, using ran1(idum) as the source of uniform deviates. 
//------------------------------------------------------------------------------
float gasdevi() 
{ 
  float ran1i(long *idum); 
  static int iset=0; 
  static float gset; 
  float fac,rsq,v1,v2; 
  
  if (idumi < 0) iset=0;
  
  if (iset == 0) 
  {
    do 
    {
      v1=2.0*ran1i(&idumi)-1.0;
      v2=2.0*ran1i(&idumi)-1.0;    
      rsq=v1*v1+v2*v2;
    } while (rsq >= 1.0 || rsq == 0.0);
    
    fac=sqrt(-2.0*log(rsq)/rsq);    
    // Now make the Box-Muller transformation to get two normal
    // deviates. Return one and save the other for next time. 
    gset=v1*fac; iset=1;
    return v2*fac;
  } 
  else 
  {
    iset=0;
    return gset;
  }
}
    
 
static int  new_seed (  double _lseed ) {
   
/*VERBATIM*/
    idumi = _lseed;
  return 0; }
 
static double _hoc_new_seed(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 new_seed (  *getarg(1) );
 return(_r);
}
 
static int _ode_count(int _type){ hoc_execerror("IOU", "cannot be used with CVODE"); return 0;}

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
 {
   i = mean_i ;
   if ( tau_i  != 0.0 ) {
     D_i = 2.0 * std_i * std_i / tau_i ;
     exp_i = exp ( - dt / tau_i ) ;
     amp_i = std_i * sqrt ( ( 1.0 - exp ( - 2.0 * dt / tau_i ) ) ) ;
     }
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if EXTRACELLULAR
 _nd = _ml->_nodelist[_iml];
 if (_nd->_extnode) {
    _v = NODEV(_nd) +_nd->_extnode->_v[0];
 }else
#endif
 {
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 }
 v = _v;
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   i = mean_i + i1 ;
   }
 _current += i;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if EXTRACELLULAR
 _nd = _ml->_nodelist[_iml];
 if (_nd->_extnode) {
    _v = NODEV(_nd) +_nd->_extnode->_v[0];
 }else
#endif
 {
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 }
 _g = _nrn_current(_v + .001);
 	{ _rhs = _nrn_current(_v);
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) += _rhs;
  }else
#endif
  {
	NODERHS(_nd) += _rhs;
  }
  if (_nt->_nrn_fast_imem) { _nt->_nrn_fast_imem->_nrn_sav_rhs[_ni[_iml]] += _rhs; }
#if EXTRACELLULAR
 if (_nd->_extnode) {
   *_nd->_extnode->_rhs[0] += _rhs;
 }
#endif
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) -= _g;
  }else
#endif
  {
	NODED(_nd) -= _g;
  }
  if (_nt->_nrn_fast_imem) { _nt->_nrn_fast_imem->_nrn_sav_d[_ni[_iml]] -= _g; }
#if EXTRACELLULAR
 if (_nd->_extnode) {
   *_nd->_extnode->_d[0] += _g;
 }
#endif
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if EXTRACELLULAR
 _nd = _ml->_nodelist[_iml];
 if (_nd->_extnode) {
    _v = NODEV(_nd) +_nd->_extnode->_v[0];
 }else
#endif
 {
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 }
 v=_v;
{
 { error =  oup();
 if(error){fprintf(stderr,"at line 96 in file IOU.mod:\n\n"); nrn_complain(_p); abort_run(error);}
 }}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "IOU.mod";
static const char* nmodl_file_text = 
  "://=============================================================================\n"
  "://  IOU  -  fluctuating current model for synaptic bombardment\n"
  "://    (from Larkum et al Cerebral Cortex 14:1059-1070, 2004; \n"
  "://            doi:10.1093/cercor/bhh065)\n"
  "://=============================================================================\n"
  "://\n"
  "://  THEORY:\n"
  "://    Synaptic bombardment is represented by a stochastic model of a\n"
  "://    fluctuating current descibed by an Ornstein-Uhlenbeck (OU) process:\n"
  "://\n"
  "://      I(t+dt) = I(t) + ((mean-I(t))/tau)*dt + sqrt(2*dt/tau)*std*Gt\n"
  "://\n"
  "://    where mean mu, standard deviation sigma, correlation length tau \n"
  "://    and Gt is a Gaussian white noise of mean 0 and unit standard deviation.\n"
  "://\n"
  "://  REMARKS:\n"
  "://     - code adapted from ggSBA.mod due to Destexhe and Rudolph\n"
  "://     - mechanism is implemented as a nonspecific current defined\n"
  "://       as a point process.\n"
  "://     - requires fixed-time-step integration\n"
  "://\n"
  "://  NUMERICAL RESOLUTION: (from Destexhe and Rudolph)\n"
  "://    The numerical scheme for integration of OU processes takes advantage\n"
  "://    of the fact that these processes are gaussian, which led to an exact\n"
  "://    update rule independent of the time step dt (see Gillespie DT,\n"
  "://    Am J Phys 64: 225, 1996):\n"
  "://\n"
  "://      x(t+dt) = x(t) * exp(-dt/tau) + A * N(0,1)\n"
  "://\n"
  "://    where A = sqrt( D*tau/2 * (1-exp(-2*dt/tau)) ) and N(0,1) is a normal\n"
  "://    random number (avg=0, sigma=1)\n"
  "://\n"
  "://  PARAMETERS:\n"
  "://    The mechanism takes the following parameters (Larkum et al 2004):\n"
  "://\n"
  "://    meam = 0  (nA)           : absolute mean of current\n"
  "://    std = 0.3 (nA)           : standard deviation of current\n"
  "://    tau = 3 (ms)             : correlation time constant\n"
  "://\n"
  "://-----------------------------------------------------------------------------\n"
  "://\n"
  "://  IMPROVED RANDOM NUMBER GENERATOR (from Michael Rudolph):\n"
  "://    source: Numerical Recipes in C\n"
  "://            gasdev() random generator for normal distributed random numbers\n"
  "://\n"
  "://-----------------------------------------------------------------------------\n"
  "://\n"
  "://  IMPLEMENTATION: B. Graham, University of Stirling, 2022\n"
  "://\n"
  "://=============================================================================\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "  POINT_PROCESS IOU\n"
  "  RANGE mean_i, std_i, tau_i\n"
  "  RANGE new_seed\n"
  "  ELECTRODE_CURRENT i\n"
  ":  NONSPECIFIC_CURRENT i\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "  (nA) = (nanoamp)\n"
  "  (mV) = (millivolt)\n"
  "  (umho) = (micromho)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "  dt (ms)\n"
  "\n"
  "  mean_i = 0  (nA)             : absolute mean of current\n"
  "  std_i = 0.3 (nA)         : standard deviation of current\n"
  "  tau_i = 3 (ms)             : correlation time constant\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "  v (mV)                :// membrane voltage\n"
  "  i (nA)                :// fluctuating current\n"
  "  i1 (nA)             :// fluctuating current\n"
  "  D_i (nA nA /ms)   :// diffusion coefficient\n"
  "  exp_i\n"
  "  amp_i (nA)\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "  i = mean_i\n"
  "  if(tau_i != 0) {\n"
  "    D_i = 2 * std_i * std_i / tau_i\n"
  "    exp_i = exp(-dt/tau_i)\n"
  "    amp_i = std_i * sqrt( (1-exp(-2*dt/tau_i)) )\n"
  "  }\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "  SOLVE oup\n"
  "\n"
  "  i = mean_i + i1\n"
  "\n"
  "}\n"
  "\n"
  ":// decleare gasdev() and ran1() functions for random generator\n"
  "VERBATIM\n"
  "  float gasdevi();\n"
  "  float ran1i(long *idem);\n"
  "ENDVERBATIM\n"
  "\n"
  "\n"
  "PROCEDURE oup() {       :// use \"Numerical Recipes in C\" function gasdev()\n"
  "  if(tau_i!=0) { \n"
  "    i1 =  exp_i * i1 + amp_i * gasdevi() \n"
  "  } else {\n"
  "    i1 = std_i * gasdevi()\n"
  "  }\n"
  "}\n"
  "\n"
  "\n"
  "://=============================================================================\n"
  "://  IMPROVED RANDOM NUMBER GENERATOR\n"
  "://    source: Numerical Recipes in C\n"
  "://=============================================================================\n"
  "\n"
  "VERBATIM\n"
  "\n"
  "#include <math.h> \n"
  "\n"
  "#define IA 16807 \n"
  "#define IM 2147483647 \n"
  "#define AM (1.0/IM) \n"
  "#define IQ 127773 \n"
  "#define IR 2836 \n"
  "#define NTAB 32 \n"
  "#define NDIV (1+(IM-1)/NTAB) \n"
  "#define EPS 1.2e-7 \n"
  "#define RNMX (1.0-EPS)\n"
  "\n"
  "long idumi;\n"
  "\n"
  "//------------------------------------------------------------------------------\n"
  "// Minimal\" random number generator of Park and Miller with Bays-Durham \n"
  "// shuffle and added safeguards. Returns a uniform random deviate between \n"
  "// 0.0 and 1.0 (exclusive of the endpoint values). Call with idum a \n"
  "// negative integer to initialize; thereafter, do not alter idum between \n"
  "// successive deviates in a sequence. RNMX should approximate the largest \n"
  "// floating value that is less than 1.\n"
  "//------------------------------------------------------------------------------\n"
  "float ran1i(long *idum) \n"
  "{\n"
  "  int j; \n"
  "  long k; \n"
  "  static long iy=0; \n"
  "  static long iv[NTAB]; \n"
  "  float temp;\n"
  "  \n"
  "  if (*idum <= 0 || !iy) \n"
  "  {\n"
  "    if (-(*idum) < 1) *idum=1; \n"
  "    else *idum = -(*idum);\n"
  "  \n"
  "    for (j=NTAB+7;j>=0;j--) \n"
  "    {\n"
  "      k=(*idum)/IQ; \n"
  "      *idum=IA*(*idum-k*IQ)-IR*k; \n"
  "      if (*idum < 0) *idum += IM; \n"
  "      if (j < NTAB) iv[j] = *idum; \n"
  "    } \n"
  "    \n"
  "    iy=iv[0]; \n"
  "  } \n"
  "\n"
  "  k=(*idum)/IQ;\n"
  "  *idum=IA*(*idum-k*IQ)-IR*k;\n"
  "  if (*idum < 0) *idum += IM;\n"
  "  j=iy/NDIV;\n"
  "  iy=iv[j];\n"
  "  iv[j] = *idum;\n"
  "  \n"
  "  if ((temp=AM*iy) > RNMX) return RNMX;\n"
  "  else return temp; \n"
  "}\n"
  "\n"
  "//------------------------------------------------------------------------------\n"
  "// Returns a normally distributed deviate with zero mean and \n"
  "// unit variance, using ran1(idum) as the source of uniform deviates. \n"
  "//------------------------------------------------------------------------------\n"
  "float gasdevi() \n"
  "{ \n"
  "  float ran1i(long *idum); \n"
  "  static int iset=0; \n"
  "  static float gset; \n"
  "  float fac,rsq,v1,v2; \n"
  "  \n"
  "  if (idumi < 0) iset=0;\n"
  "  \n"
  "  if (iset == 0) \n"
  "  {\n"
  "    do \n"
  "    {\n"
  "      v1=2.0*ran1i(&idumi)-1.0;\n"
  "      v2=2.0*ran1i(&idumi)-1.0;    \n"
  "      rsq=v1*v1+v2*v2;\n"
  "    } while (rsq >= 1.0 || rsq == 0.0);\n"
  "    \n"
  "    fac=sqrt(-2.0*log(rsq)/rsq);    \n"
  "    // Now make the Box-Muller transformation to get two normal\n"
  "    // deviates. Return one and save the other for next time. \n"
  "    gset=v1*fac; iset=1;\n"
  "    return v2*fac;\n"
  "  } \n"
  "  else \n"
  "  {\n"
  "    iset=0;\n"
  "    return gset;\n"
  "  }\n"
  "}\n"
  "    \n"
  "ENDVERBATIM\n"
  "    \n"
  "://=============================================================================\n"
  "\n"
  "PROCEDURE new_seed(seed) {      :// procedure to set the seed\n"
  "  VERBATIM\n"
  "    idumi = _lseed;\n"
  "  ENDVERBATIM\n"
  "}\n"
  "\n"
  "://=============================================================================\n"
  ;
#endif
