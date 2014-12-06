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

INTERVALX_ADAPT_API void Caddx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m);

INTERVALX_ADAPT_API void Bisectx(double* pX, double* pX1, double* pX2, unsigned int n);

INTERVALX_ADAPT_API void Widthx(double* pr, double* pX, unsigned int n);

INTERVALX_ADAPT_API void Interx(double* pr, double* px, unsigned int nb, unsigned int n);
