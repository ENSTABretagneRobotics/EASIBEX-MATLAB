#include "intervalx_adapt.h"
#include "imatrix.h"

// Parameters : return value, interval/box/imatrix/vector<interval>/vector<box>, nb elements, box size, imatrix width.
INTERVALX_ADAPT_API void Addx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	// vector
	if (m == 1)
	{
		for (unsigned int k = 0; k < nb; k++)
		{
			box Z(n);
			box X(n);
			box Y(n);

			for (unsigned int i = 0; i < n; i++)
			{
				unsigned int index = 2*(n*k+i);
				Z[i+1] = interval(pZ[index],pZ[index+1]);
				X[i+1] = interval(pX[index],pX[index+1]);
				Y[i+1] = interval(pY[index],pY[index+1]);
			}

			Z = X + Y;

			for (unsigned int i = 0; i < n; i++)
			{
				unsigned int index = 2*(n*k+i);
				pZ[index] = Z[i+1].inf;
				pZ[index+1] = Z[i+1].sup;
			}
		}
	}

	// imatrix
	if ((nb == 1)&&(m > 1))
	{
		imatrix Z(n,m);
		imatrix X(n,m);
		imatrix Y(n,m);

		for (unsigned int j = 0; j < m; j++)
		{
			for (unsigned int i = 0; i < n; i++)
			{
				unsigned int index = 2*(n*j+i);
				Z.SetVal(i+1,j+1,interval(pZ[index],pZ[index+1]));
				X.SetVal(i+1,j+1,interval(pX[index],pX[index+1]));
				Y.SetVal(i+1,j+1,interval(pY[index],pY[index+1]));
			}
		}

		Z = X + Y;

		for (unsigned int j = 0; j < m; j++)
		{
			for (unsigned int i = 0; i < n; i++)
			{
				unsigned int index = 2*(n*j+i);
				pZ[index] = Z(i+1,j+1).inf;
				pZ[index+1] = Z(i+1,j+1).sup;
			}
		}
	}
}

// Parameters : interval/box/imatrix/vector<interval>/vector<box>, nb elements, box size, imatrix width.
INTERVALX_ADAPT_API void Caddx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	// imatrix not yet handled...

	// vector
	if (m == 1)
	{
		for (unsigned int k = 0; k < nb; k++)
		{
			box Z(n);
			box X(n);
			box Y(n);

			for (unsigned int i = 0; i < n; i++)
			{
				unsigned int index = 2*(n*k+i);
				Z[i+1] = interval(pZ[index],pZ[index+1]);
				X[i+1] = interval(pX[index],pX[index+1]);
				Y[i+1] = interval(pY[index],pY[index+1]);
			}

			Cadd(Z, X, Y);

			for (unsigned int i = 0; i < n; i++)
			{
				unsigned int index = 2*(n*k+i);
				pZ[index] = Z[i+1].inf;
				pZ[index+1] = Z[i+1].sup;
				pX[index] = X[i+1].inf;
				pX[index+1] = X[i+1].sup;
				pY[index] = Y[i+1].inf;
				pY[index+1] = Y[i+1].sup;
			}
		}
	}
}

// Parameters : return value, box, box, box size.
INTERVALX_ADAPT_API void Bisectx(double* pX, double* pX1, double* pX2, unsigned int n)
{
	box X(n);
	box X1 = Infinity(n);
	box X2 = Infinity(n);

	for (unsigned int i = 0; i < n; i++)
	{
		unsigned int index = 2*i;
		X[i+1] = interval(pX[index],pX[index+1]);
	}

	Bisect(X, X1, X2);

	for (unsigned int i = 0; i < n; i++)
	{
		unsigned int index = 2*i;
		pX1[index] = X1[i+1].inf;
		pX1[index+1] = X1[i+1].sup;
		pX2[index] = X2[i+1].inf;
		pX2[index+1] = X2[i+1].sup;
	}
}

// Parameters : return value, box, box size.
INTERVALX_ADAPT_API void Widthx(double* pr, double* pX, unsigned int n)
{
	double r = 0;
	box X(n);

	for (unsigned int i = 0; i < n; i++)
	{
		unsigned int index = 2*i;
		X[i+1] = interval(pX[index],pX[index+1]);
	}

	r = Width(X);

	*pr = r;
}

// Parameters : return value, vector<interval>/vector<box>, nb elements, box size.
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
