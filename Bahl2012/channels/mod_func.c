#include <stdio.h>
#include "hocdec.h"
#define IMPORT extern __declspec(dllimport)
IMPORT int nrnmpi_myid, nrn_nobanner_;

extern void _Bcount_reg();
extern void _Ca_LVAst_reg();
extern void _IKM_reg();
extern void _IOU_reg();
extern void _IOUa_reg();
extern void _SlowCa_reg();
extern void _cad_reg();
extern void _epsp_reg();
extern void _exp2stoch_reg();
extern void _gclamp_reg();
extern void _ggSBA_reg();
extern void _h_reg();
extern void _hl_reg();
extern void _kca_reg();
extern void _kfast_reg();
extern void _kslow_reg();
extern void _nap_reg();
extern void _nat_reg();

void modl_reg(){
	//nrn_mswindll_stdio(stdin, stdout, stderr);
    if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
	fprintf(stderr, "Additional mechanisms from files\n");

fprintf(stderr," Bcount.mod");
fprintf(stderr," Ca_LVAst.mod");
fprintf(stderr," IKM.mod");
fprintf(stderr," IOU.mod");
fprintf(stderr," IOUa.mod");
fprintf(stderr," SlowCa.mod");
fprintf(stderr," cad.mod");
fprintf(stderr," epsp.mod");
fprintf(stderr," exp2stoch.mod");
fprintf(stderr," gclamp.mod");
fprintf(stderr," ggSBA.mod");
fprintf(stderr," h.mod");
fprintf(stderr," hl.mod");
fprintf(stderr," kca.mod");
fprintf(stderr," kfast.mod");
fprintf(stderr," kslow.mod");
fprintf(stderr," nap.mod");
fprintf(stderr," nat.mod");
fprintf(stderr, "\n");
    }
_Bcount_reg();
_Ca_LVAst_reg();
_IKM_reg();
_IOU_reg();
_IOUa_reg();
_SlowCa_reg();
_cad_reg();
_epsp_reg();
_exp2stoch_reg();
_gclamp_reg();
_ggSBA_reg();
_h_reg();
_hl_reg();
_kca_reg();
_kfast_reg();
_kslow_reg();
_nap_reg();
_nat_reg();
}
