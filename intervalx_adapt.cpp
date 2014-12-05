#include "intervalx_adapt.h"
#include "box.h"

// Parameters : interval/box/imatrix/vector<interval>/vector<box>, nb elements, box size, imatrix width.
INTERVALX_ADAPT_API void Caddx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	// imatrix, vector not yet handled...

	// interval
	if ((nb == 1)&&(n == 1)&&(m == 1))
	{
		interval Z(pZ[0], pZ[1]);
		interval X(pX[0], pX[1]);
		interval Y(pY[0], pY[1]);

		Cadd(Z, X, Y);

		pZ[0] = Z.inf;
		pZ[1] = Z.sup;
		pX[0] = X.inf;
		pX[1] = X.sup;
		pY[0] = Y.inf;
		pY[1] = Y.sup;
	}

	// box
	if ((nb == 1)&&(n > 1)&&(m == 1))
	{
		box Z(n);
		box X(n);
		box Y(n);

		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*i;
			Z[i+1] = interval(pZ[index],pZ[index+1]);
			X[i+1] = interval(pX[index],pX[index+1]);
			Y[i+1] = interval(pY[index],pY[index+1]);
		}

		Cadd(Z, X, Y);

		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*i;
			pZ[index] = Z[i+1].inf;
			pZ[index+1] = Z[i+1].sup;
			pX[index] = X[i+1].inf;
			pX[index+1] = X[i+1].sup;
			pY[index] = Y[i+1].inf;
			pY[index+1] = Y[i+1].sup;
		}
	}
}

INTERVALX_ADAPT_API void Bisectx(double* pX, double* pX1, double* pX2, unsigned int n)
{
	box X(n);
	box X1(n);
	box X2(n);

	for (unsigned int i = 0; i < n; i++)
	{
		unsigned int index = 2*i;
		X[i+1] = interval(pX[index],pX[index+1]);
		X1[i+1] = interval(pX1[index],pX1[index+1]);
		X2[i+1] = interval(pX2[index],pX2[index+1]);
	}

	Bisect(X, X1, X2);

	for (unsigned int i = 0; i < n; i++)
	{
		unsigned int index = 2*i;
		pX[index] = X[i+1].inf;
		pX[index+1] = X[i+1].sup;
		pX1[index] = X1[i+1].inf;
		pX1[index+1] = X1[i+1].sup;
		pX2[index] = X2[i+1].inf;
		pX2[index+1] = X2[i+1].sup;
	}
}

// Parameters : return value, vector<interval>/boxes/vector<boxes>, nb elements, boxes size.
INTERVALX_ADAPT_API void Interx(double* pr, double* px, unsigned int nb, unsigned int n)
{
	box r(n);
	vector<box> x(nb, r);

	for (unsigned int k = 0; k < nb; k++)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			r[i+1] = interval(px[index],px[index+1]);
		}
		x[k] = r;
	}

	r = Inter(x);

	for (unsigned int i = 0; i < n; i++)
	{
		unsigned int index = 2*i;
		pr[index] = r[i+1].inf;
		pr[index+1] = r[i+1].sup;
	}
}
