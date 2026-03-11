://=============================================================================
://  IOUa  -  fluctuating current model for synaptic bombardment
://    (from Larkum et al Cerebral Cortex 14:1059-1070, 2004; 
://            doi:10.1093/cercor/bhh065)
://=============================================================================
://
://  THEORY:
://    Synaptic bombardment is represented by a stochastic model of a
://    fluctuating current descibed by an Ornstein-Uhlenbeck (OU) process:
://
://      I(t+dt) = I(t) + ((mu-I(t))/tau)*dt + sqrt(2*dt/tau)*sigma*Gt
://
://    where mean mu, standard deviation sigma, correlation length tau 
://    and Gt is a Gaussian white noise of mean 0 and unit standard deviation.
://
://  REMARKS:
://	- NUMERICS SUSPECT! DO NOT USE
://     - mechanism is implemented as a nonspecific current defined
://       as a point process.
://     - requires fixed-time-step integration
://
://  PARAMETERS:
://    The mechanism takes the following parameters (Larkum et al 2004):
://
://    mu = 0  (nA)             : absolute mean of current
://    sigma = 0.3 (nA)         : standard deviation of current
://    tau = 3 (ms)             : correlation time constant
://
://-----------------------------------------------------------------------------
://
://  IMPROVED RANDOM NUMBER GENERATOR (from Michael Rudolph):
://    source: Numerical Recipes in C
://            gasdev() random generator for normal distributed random numbers
://
://-----------------------------------------------------------------------------
://
://  IMPLEMENTATION: B. Graham, University of Stirling, 2022
://
://=============================================================================

INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}

NEURON {
  POINT_PROCESS IOUa
  RANGE mu, sigma, tau
  RANGE new_seed
  ELECTRODE_CURRENT i
:  NONSPECIFIC_CURRENT i
}

UNITS {
  (nA) = (nanoamp)
  (mV) = (millivolt)
  (umho) = (micromho)
}

PARAMETER {
  dt (ms)

  mu = 0  (nA)             : absolute mean of current
  sigma = 0.3 (nA)         : standard deviation of current
  tau = 3 (ms)             : correlation time constant
}

ASSIGNED {
  v (mV)                :// membrane voltage
  i (nA)                :// fluctuating current
  exp_i
  amp_i (nA)
}

INITIAL {
  i = mu
  if(tau != 0) {
    amp_i = sigma * sqrt(2*dt/tau)
  }
}

BREAKPOINT {
  if(tau!=0) { 
    i =  i + ((mu-i)/tau)*dt + amp_i*gasdeva() 
  } else {
    i = mu + sigma*gasdeva()
  }
}

:// decleare gasdev() and ran1() functions for random generator
VERBATIM
  float gasdeva();
  float ran1a(long *idem);
ENDVERBATIM


://=============================================================================
://  IMPROVED RANDOM NUMBER GENERATOR
://    source: Numerical Recipes in C
://=============================================================================

VERBATIM

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

long iduma;

//------------------------------------------------------------------------------
// Minimal" random number generator of Park and Miller with Bays-Durham 
// shuffle and added safeguards. Returns a uniform random deviate between 
// 0.0 and 1.0 (exclusive of the endpoint values). Call with idum a 
// negative integer to initialize; thereafter, do not alter idum between 
// successive deviates in a sequence. RNMX should approximate the largest 
// floating value that is less than 1.
//------------------------------------------------------------------------------
float ran1a(long *idum) 
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
float gasdeva() 
{ 
  float ran1a(long *idum); 
  static int iset=0; 
  static float gset; 
  float fac,rsq,v1,v2; 
  
  if (iduma < 0) iset=0;
  
  if (iset == 0) 
  {
    do 
    {
      v1=2.0*ran1a(&iduma)-1.0;
      v2=2.0*ran1a(&iduma)-1.0;    
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
    
ENDVERBATIM
    
://=============================================================================

PROCEDURE new_seed(seed) {      :// procedure to set the seed
  VERBATIM
    iduma = _lseed;
  ENDVERBATIM
}

://=============================================================================
