#include "intervalx_adapt.h"
#include "imatrix.h"

// Parameters : interval/vector<interval>, nb elements.
inline void Cdefaultintervalunarycontractor(double* pX, unsigned int nb, void (*pFunction)(interval&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		unsigned int index = 2*k;
		interval X = interval(pX[index],pX[index+1]);
		pFunction(X);
		pX[index] = X.inf; pX[index+1] = X.sup;
	}
}

// Parameters : box/vector<box>, nb elements, box size.
inline void Cdefaultboxunarycontractor(double* pX, unsigned int nb, unsigned int n, void (*pFunction)(box&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		box X(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			X[i+1] = interval(pX[index],pX[index+1]);
		}
		pFunction(X);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			pX[index] = X[i+1].inf; pX[index+1] = X[i+1].sup;
		}
	}
}

// Parameters : imatrix, nb elements, box size, imatrix width.
inline void Cdefaultimatrixunarycontractor(double* pX, unsigned int nb, unsigned int n, unsigned int m, void (*pFunction)(imatrix&))
{
	if (nb != 1) return; // vector<imatrix> unsupported.
	imatrix X(n,m);
	for (unsigned int j = 0; j < m; j++)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*j+i);
			X.SetVal(i+1,j+1,interval(pX[index],pX[index+1]));
		}
	}
	pFunction(X);
	for (unsigned int j = 0; j < m; j++)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*j+i);
			pX[index] = X(i+1,j+1).inf; pX[index+1] = X(i+1,j+1).sup;
		}
	}
}

// Parameters : interval/vector<interval>, interval/vector<interval>, nb elements.
inline void Cdefaultintervalbinarycontractor(double* pY, double* pX, unsigned int nb, void (*pFunction)(interval&, interval&, int))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		unsigned int index = 2*k;
		interval Y = interval(pY[index],pY[index+1]);
		interval X = interval(pX[index],pX[index+1]);
		pFunction(Y, X, 0);
		pY[index] = Y.inf; pY[index+1] = Y.sup;
		pX[index] = X.inf; pX[index+1] = X.sup;
	}
}

// Parameters : box/vector<box>, box/vector<box>, nb elements, box size.
inline void Cdefaultboxbinarycontractor(double* pY, double* pX, unsigned int nb, unsigned int n, void (*pFunction)(box&, box&, int))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		box Y(n), X(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			Y[i+1] = interval(pY[index],pY[index+1]);
			X[i+1] = interval(pX[index],pX[index+1]);
		}
		pFunction(Y, X, 0);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			pY[index] = Y[i+1].inf; pY[index+1] = Y[i+1].sup;
			pX[index] = X[i+1].inf; pX[index+1] = X[i+1].sup;
		}
	}
}

// Parameters : imatrix, imatrix, nb elements, box size, imatrix width.
inline void Cdefaultimatrixbinarycontractor(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m, void (*pFunction)(imatrix&, imatrix&))
{
	if (nb != 1) return; // vector<imatrix> unsupported.
	imatrix Y(n,m), X(n,m);
	for (unsigned int j = 0; j < m; j++)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*j+i);
			Y.SetVal(i+1,j+1,interval(pY[index],pY[index+1]));
			X.SetVal(i+1,j+1,interval(pX[index],pX[index+1]));
		}
	}
	pFunction(Y, X);
	for (unsigned int j = 0; j < m; j++)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*j+i);
			pY[index] = Y(i+1,j+1).inf; pY[index+1] = Y(i+1,j+1).sup;
			pX[index] = X(i+1,j+1).inf; pX[index+1] = X(i+1,j+1).sup;
		}
	}
}

// Parameters : interval/vector<interval>, interval/vector<interval>, interval/vector<interval>, nb elements.
inline void Cdefaultintervalternarycontractor(double* pZ, double* pX, double* pY, unsigned int nb, void (*pFunction)(interval&, interval&, interval&, int))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		unsigned int index = 2*k;
		interval Z = interval(pZ[index],pZ[index+1]);
		interval X = interval(pX[index],pX[index+1]);
		interval Y = interval(pY[index],pY[index+1]);
		pFunction(Z, X, Y, 0);
		pZ[index] = Z.inf; pZ[index+1] = Z.sup;
		pX[index] = X.inf; pX[index+1] = X.sup;
		pY[index] = Y.inf; pY[index+1] = Y.sup;
	}
}

// Parameters : box/vector<box>, box/vector<box>, box/vector<box>, nb elements, box size.
inline void Cdefaultboxternarycontractor(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, void (*pFunction)(box&, box&, box&, int))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		box Z(n), X(n), Y(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			Z[i+1] = interval(pZ[index],pZ[index+1]);
			X[i+1] = interval(pX[index],pX[index+1]);
			Y[i+1] = interval(pY[index],pY[index+1]);
		}
		pFunction(Z, X, Y, 0);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			pZ[index] = Z[i+1].inf; pZ[index+1] = Z[i+1].sup;
			pX[index] = X[i+1].inf; pX[index+1] = X[i+1].sup;
			pY[index] = Y[i+1].inf; pY[index+1] = Y[i+1].sup;
		}
	}
}

// Parameters : imatrix, imatrix, imatrix, nb elements, box size, imatrix width.
inline void Cdefaultimatrixternarycontractor(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m, void (*pFunction)(imatrix&, imatrix&, imatrix&))
{
	if (nb != 1) return; // vector<imatrix> unsupported.
	imatrix Z(n,m), X(n,m), Y(n,m);
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
	pFunction(Z, X, Y);
	for (unsigned int j = 0; j < m; j++)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*j+i);
			pZ[index] = Z(i+1,j+1).inf; pZ[index+1] = Z(i+1,j+1).sup;
			pX[index] = X(i+1,j+1).inf; pX[index+1] = X(i+1,j+1).sup;
			pY[index] = Y(i+1,j+1).inf; pY[index+1] = Y(i+1,j+1).sup;
		}
	}
}

// Parameters : interval/vector<interval>, interval/vector<interval>, interval/vector<interval>, interval/vector<interval>, nb elements.
inline void Cdefaultintervalquaternarycontractor(double* pZ, double* pW, double* pX, double* pY, unsigned int nb, void (*pFunction)(interval&, interval&, interval&, interval&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		unsigned int index = 2*k;
		interval Z = interval(pZ[index],pZ[index+1]);
		interval W = interval(pW[index],pW[index+1]);
		interval X = interval(pX[index],pX[index+1]);
		interval Y = interval(pY[index],pY[index+1]);
		pFunction(Z, W, X, Y);
		pZ[index] = Z.inf; pZ[index+1] = Z.sup;
		pW[index] = W.inf; pW[index+1] = W.sup;
		pX[index] = X.inf; pX[index+1] = X.sup;
		pY[index] = Y.inf; pY[index+1] = Y.sup;
	}
}

// Parameters : box/vector<box>, box/vector<box>, box/vector<box>, box/vector<box>, nb elements, box size.
inline void Cdefaultboxquaternarycontractor(double* pZ, double* pW, double* pX, double* pY, unsigned int nb, unsigned int n, void (*pFunction)(box&, box&, box&, box&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		box Z(n), W(n), X(n), Y(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			Z[i+1] = interval(pZ[index],pZ[index+1]);
			W[i+1] = interval(pW[index],pW[index+1]);
			X[i+1] = interval(pX[index],pX[index+1]);
			Y[i+1] = interval(pY[index],pY[index+1]);
		}
		pFunction(Z, W, X, Y);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			pZ[index] = Z[i+1].inf; pZ[index+1] = Z[i+1].sup;
			pW[index] = W[i+1].inf; pW[index+1] = W[i+1].sup;
			pX[index] = X[i+1].inf; pX[index+1] = X[i+1].sup;
			pY[index] = Y[i+1].inf; pY[index+1] = Y[i+1].sup;
		}
	}
}

// Parameters : return value, interval/box/imatrix/vector<interval>/vector<box>, interval/box/imatrix/vector<interval>/vector<box>, nb elements, box size, imatrix width.
INTERVALX_ADAPT_API void Addx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		for (unsigned int k = 0; k < nb; k++)
		{
			box Z(n), X(n), Y(n);
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
				pZ[index] = Z[i+1].inf; pZ[index+1] = Z[i+1].sup;
			}
		}
	}
	else if (nb == 1)
	{
		imatrix Z(n,m), X(n,m), Y(n,m);

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
				pZ[index] = Z(i+1,j+1).inf; pZ[index+1] = Z(i+1,j+1).sup;
			}
		}
	}
}

INTERVALX_ADAPT_API void Caddx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalternarycontractor(pZ, pX, pY, nb, Cadd);
		else Cdefaultboxternarycontractor(pZ, pX, pY, nb, n, Cadd);
	}
	//else if (nb == 1) Cdefaultimatrixternarycontractor(pZ, pX, pY, nb, n, m, Cadd);
}

INTERVALX_ADAPT_API void Csubx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalternarycontractor(pZ, pX, pY, nb, Csub);
		else Cdefaultboxternarycontractor(pZ, pX, pY, nb, n, Csub);
	}
	//else if (nb == 1) Cdefaultimatrixternarycontractor(pZ, pX, pY, nb, n, m, Csub);
}

INTERVALX_ADAPT_API void Cmulx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalternarycontractor(pZ, pX, pY, nb, Cmul);
		//else Cdefaultboxternarycontractor(pZ, pX, pY, nb, n, Cmul);
	}
	else if (nb == 1) Cdefaultimatrixternarycontractor(pZ, pX, pY, nb, n, m, Cmul);
}

INTERVALX_ADAPT_API void Cdivx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalternarycontractor(pZ, pX, pY, nb, Cdiv);
		//else Cdefaultboxternarycontractor(pZ, pX, pY, nb, n, Cdiv);
	}
	//else if (nb == 1) Cdefaultimatrixternarycontractor(pZ, pX, pY, nb, n, m, Cdiv);
}

INTERVALX_ADAPT_API void Cequalx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalbinarycontractor(pY, pX, nb, Cequal);
		//else Cdefaultboxbinarycontractor(pY, pX, nb, n, Cequal);
	}
	//else if (nb == 1) Cdefaultimatrixbinarycontractor(pY, pX, nb, n, m, Cequal);
}

INTERVALX_ADAPT_API void Cminx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalternarycontractor(pZ, pX, pY, nb, Cmin);
		//else Cdefaultboxternarycontractor(pZ, pX, pY, nb, n, Cmin);
	}
	//else if (nb == 1) Cdefaultimatrixternarycontractor(pZ, pX, pY, nb, n, m, Cmin);
}

INTERVALX_ADAPT_API void Cmaxx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalternarycontractor(pZ, pX, pY, nb, Cmax);
		//else Cdefaultboxternarycontractor(pZ, pX, pY, nb, n, Cmax);
	}
	//else if (nb == 1) Cdefaultimatrixternarycontractor(pZ, pX, pY, nb, n, m, Cmax);
}

INTERVALX_ADAPT_API void Cabsx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalbinarycontractor(pY, pX, nb, Cabs);
		//else Cdefaultboxbinarycontractor(pY, pX, nb, n, Cabs);
	}
	//else if (nb == 1) Cdefaultimatrixbinarycontractor(pY, pX, nb, n, m, Cabs);
}

INTERVALX_ADAPT_API void Csignx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			for (unsigned int k = 0; k < nb; k++)
			{
				unsigned int index = 2*k;
				interval Y = interval(pY[index],pY[index+1]);
				interval X = interval(pX[index],pX[index+1]);
				Csign(Y, X);
				pY[index] = Y.inf; pY[index+1] = Y.sup;
				pX[index] = X.inf; pX[index+1] = X.sup;
			}
		}
		//else Cdefaultboxbinarycontractor(pY, pX, nb, n, Csign);
	}
	//else if (nb == 1) Cdefaultimatrixbinarycontractor(pY, pX, nb, n, m, Csign);
}

INTERVALX_ADAPT_API void Cchix(double* pZ, double* pW, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalquaternarycontractor(pZ, pW, pX, pY, nb, Cchi);
		//else Cdefaultboxquaternarycontractor(pZ, pW, pX, pY, nb, n, Cchi);
	}
	//else if (nb == 1) Cdefaultimatrixquaternarycontractor(pZ, pW, pX, pY, nb, n, m, Cchi);
}

INTERVALX_ADAPT_API void Csqrx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalbinarycontractor(pY, pX, nb, Csqr);
		//else Cdefaultboxbinarycontractor(pY, pX, nb, n, Csqr);
	}
	//else if (nb == 1) Cdefaultimatrixbinarycontractor(pY, pX, nb, n, m, Csqr);
}

INTERVALX_ADAPT_API void Cexpx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalbinarycontractor(pY, pX, nb, Cexp);
		//else Cdefaultboxbinarycontractor(pY, pX, nb, n, Cexp);
	}
	//else if (nb == 1) Cdefaultimatrixbinarycontractor(pY, pX, nb, n, m, Cexp);
}

INTERVALX_ADAPT_API void Clogx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalbinarycontractor(pY, pX, nb, Clog);
		//else Cdefaultboxbinarycontractor(pY, pX, nb, n, Clog);
	}
	//else if (nb == 1) Cdefaultimatrixbinarycontractor(pY, pX, nb, n, m, Clog);
}

INTERVALX_ADAPT_API void Cpowx(double* pY, double* pX, unsigned int n_exp, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			for (unsigned int k = 0; k < nb; k++)
			{
				unsigned int index = 2*k;
				interval Y = interval(pY[index],pY[index+1]);
				interval X = interval(pX[index],pX[index+1]);
				Cpow(Y, X, n_exp);
				pY[index] = Y.inf; pY[index+1] = Y.sup;
				pX[index] = X.inf; pX[index+1] = X.sup;
			}
		}
	}
}

INTERVALX_ADAPT_API void Ccosx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalbinarycontractor(pY, pX, nb, Ccos);
		//else Cdefaultboxbinarycontractor(pY, pX, nb, n, Ccos);
	}
	//else if (nb == 1) Cdefaultimatrixbinarycontractor(pY, pX, nb, n, m, Ccos);
}

INTERVALX_ADAPT_API void Csinx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalbinarycontractor(pY, pX, nb, Csin);
		//else Cdefaultboxbinarycontractor(pY, pX, nb, n, Csin);
	}
	//else if (nb == 1) Cdefaultimatrixbinarycontractor(pY, pX, nb, n, m, Csin);
}

INTERVALX_ADAPT_API void Ctanx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalbinarycontractor(pY, pX, nb, Ctan);
		//else Cdefaultboxbinarycontractor(pY, pX, nb, n, Ctan);
	}
	//else if (nb == 1) Cdefaultimatrixbinarycontractor(pY, pX, nb, n, m, Ctan);
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
