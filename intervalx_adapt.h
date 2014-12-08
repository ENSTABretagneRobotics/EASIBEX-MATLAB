#ifdef _MSC_VER
#ifdef INTERVALX_ADAPT_EXPORTS
#define INTERVALX_ADAPT_API __declspec(dllexport) 
#else
#define INTERVALX_ADAPT_API __declspec(dllimport) 
#endif // INTERVALX_ADAPT_EXPORTS
#else
#define INTERVALX_ADAPT_API 
#endif // _MSC_VER

INTERVALX_ADAPT_API void Addx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);

//INTERVALX_ADAPT_API void Subx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Caddx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Csubx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Cmulx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Cdivx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Cequalx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Cabsx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Csqrx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Cexpx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Clogx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Cpowx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Ccosx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Csinx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Ctanx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Bisectx(double* pX, double* pX1, double* pX2, unsigned int n);

INTERVALX_ADAPT_API void Widthx(double* pr, double* pX, unsigned int n);

INTERVALX_ADAPT_API void Interx(double* pr, double* px, unsigned int nb, unsigned int n);
