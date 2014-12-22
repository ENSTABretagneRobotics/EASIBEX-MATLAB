#ifndef INTERVALX_ADAPT_H
#define INTERVALX_ADAPT_H

#ifdef _WIN32
#ifdef INTERVALX_ADAPT_EXPORTS
#define INTERVALX_ADAPT_API __declspec(dllexport) 
#else
#define INTERVALX_ADAPT_API __declspec(dllimport) 
#endif // INTERVALX_ADAPT_EXPORTS
#else
#define INTERVALX_ADAPT_API 
#endif // _WIN32

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------
// Operators
//----------------------------------------------------------------------
INTERVALX_ADAPT_API void Addx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Subx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Mulx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Mulimatrixboxx(double* pc, double* pA, double* pb, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Divx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
//----------------------------------------------------------------------
// Functions
//----------------------------------------------------------------------
INTERVALX_ADAPT_API void Minx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Maxx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Absx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Sqrx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Sqrtx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Powx(double* pY, double* pX, double* pn_exp, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Expx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Logx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cosx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Sinx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Tanx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Acosx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Asinx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Atanx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Transposex(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Concatx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Interx(double* pr, double* px, unsigned int nb, unsigned int n);
INTERVALX_ADAPT_API void Unionx(double* pr, double* px, unsigned int nb, unsigned int n);
INTERVALX_ADAPT_API void Sizex(int* py, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Infx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Supx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Centerx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Widthx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Volumex(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Radx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void ToRealx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void IsBoxx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Updatex(double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Anglex(double* pz, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Disjointx(double* pz, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Subsetx(double* pz, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void SubsetStrictx(double* pz, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Inx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void decreasex(double* pz, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
//----------------------------------------------------------------------
// Contractors
//----------------------------------------------------------------------
INTERVALX_ADAPT_API void Caddx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Csubx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cmulx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cmulimatrixboxx(double* pc, double* pA, double* pb, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cdivx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cequalx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cminx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cmaxx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cabsx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Csignx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cchix(double* pZ, double* pW, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cgeqx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cintegerx(double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cbooleanx(double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Crotx(double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cantisymx(double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Csqrx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cexpx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Clogx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cpowx(double* pY, double* pX, int* pn_exp, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Ccosx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Csinx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Ctanx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Catanx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cnormx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cnorm3Dx(double* pN, double* pX, double* pY, double* pZ, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cdistx(double* pZ, double* pV, double* pW, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cscalx(double* pZ, double* pV, double* pW, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cdetx(double* pZ, double* pV, double* pW, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void CinRingx(double* pX, double* pY, double* pcx, double* pcy, double* pR, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void CinSegmentx(double* pX, double* pY, double* pax, double* pay, double* pbx, double* pby, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void CinSegmentsx(double* pX, double* pY, double* pax, double* pay, double* pbx, double* pby, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void CinCirclex(double* pX, double* pY, double* pcx, double* pcy, double* pr, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void CinCirclesx(double* pX, double* pY, double* pcx, double* pcy, double* pr, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void CinSegmentsOrCirclesx(double* pX, double* pY, double* pax, double* pay, double* pbx, double* pby, double* pcx, double* pcy, double* pr, unsigned int nbs, unsigned int nbc, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Corthox(double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void Cnotinx(double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);
INTERVALX_ADAPT_API void C_q_inx(double* px, int q, double* pyj, unsigned int nb, unsigned int n);
//----------------------------------------------------------------------
// Separators
//----------------------------------------------------------------------
INTERVALX_ADAPT_API void SinRingx(double* pX, double* pY, double* pcx, double* pcy, double* pR, int* pbOuter, unsigned int nb, unsigned int n, unsigned int m);
//----------------------------------------------------------------------
// Other
//----------------------------------------------------------------------
INTERVALX_ADAPT_API void Bisectx(double* pX, double* pX1, double* pX2, unsigned int n);

#ifdef __cplusplus
}
#endif

#endif // INTERVALX_ADAPT_H
