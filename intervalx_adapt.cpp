#include "intervalx_adapt.h"
#include "imatrix.h"

// Parameters : double/vector<double> (return value), interval/vector<interval> (arg), nb elements.
inline void defaultdoublefn1intervalarg(double* py, double* pX, unsigned int nb, double (*pFunction)(const interval&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		unsigned int index = 2*k;
		interval X = interval(pX[index],pX[index+1]);
		py[k] = pFunction(X);
	}
}

// Parameters : double/vector<double> (return value), box/vector<box> (arg), nb elements, box size.
inline void defaultdoublefn1boxarg(double* py, double* pX, unsigned int nb, unsigned int n, double (*pFunction)(const box&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		box X(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			X[i+1] = interval(pX[index],pX[index+1]);
		}
		py[k] = pFunction(X);
	}
}

// Parameters : double/vector<double> (return value), box/vector<box> (arg), box/vector<box> (arg), nb elements, box size.
inline void defaultdoublefn2boxarg(double* pz, double* pX, double* pY, unsigned int nb, unsigned int n, double (*pFunction)(const box&, const box&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		box X(n), Y(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			X[i+1] = interval(pX[index],pX[index+1]);
			Y[i+1] = interval(pY[index],pY[index+1]);
		}
		pz[k] = pFunction(X, Y);
	}
}

// Parameters : int/vector<int> (return value), box/vector<box> (arg), nb elements, box size.
inline void defaultintfn1boxarg(int* py, double* pX, unsigned int nb, unsigned int n, int (*pFunction)(const box&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		box X(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			X[i+1] = interval(pX[index],pX[index+1]);
		}
		py[k] = pFunction(X);
	}
}

// Parameters : double/vector<double> (return value), box/vector<box> (arg), nb elements, box size.
inline void defaultboolfn1boxarg(double* py, double* pX, unsigned int nb, unsigned int n, bool (*pFunction)(const box&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		box X(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			X[i+1] = interval(pX[index],pX[index+1]);
		}
		py[k] = (double)pFunction(X);
	}
}

// Parameters : double/vector<double> (return value), interval/vector<interval> (arg), interval/vector<interval> (arg), nb elements.
inline void defaultboolfn2intervalarg(double* pz, double* pX, double* pY, unsigned int nb, bool (*pFunction)(const interval&, const interval&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		unsigned int index = 2*k;
		interval X = interval(pX[index],pX[index+1]);
		interval Y = interval(pY[index],pY[index+1]);
		pz[k] = (double)pFunction(X, Y);
	}
}

// Parameters : double/vector<double> (return value), box/vector<box> (arg), box/vector<box> (arg), nb elements, box size.
inline void defaultboolfn2boxarg(double* pz, double* pX, double* pY, unsigned int nb, unsigned int n, bool (*pFunction)(const box&, const box&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		box X(n), Y(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			X[i+1] = interval(pX[index],pX[index+1]);
			Y[i+1] = interval(pY[index],pY[index+1]);
		}
		pz[k] = (double)pFunction(X, Y);
	}
}

// Parameters : iboolean/vector<iboolean> (return value), interval/vector<interval> (arg), interval/vector<interval> (arg), nb elements.
inline void defaultibooleanfn2intervalarg(double* pZ, double* pX, double* pY, unsigned int nb, iboolean (*pFunction)(const interval&, const interval&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		unsigned int index = 2*k;
		interval X = interval(pX[index],pX[index+1]);
		interval Y = interval(pY[index],pY[index+1]);
		iboolean Z = pFunction(X, Y);
		pZ[index] = NAN; pZ[index+1] = NAN;
		if (Z == itrue) { pZ[index] = 1; pZ[index+1] = 1; }
		if (Z == ifalse) { pZ[index] = 0; pZ[index+1] = 0; }
		if (Z == iperhaps) { pZ[index] = 0; pZ[index+1] = 1; }
	}		
}

// Parameters : iboolean/vector<iboolean> (return value), box/vector<box> (arg), box/vector<box> (arg), nb elements, box size.
inline void defaultibooleanfn2boxarg(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, iboolean (*pFunction)(const box&, const box&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		box X(n), Y(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			X[i+1] = interval(pX[index],pX[index+1]);
			Y[i+1] = interval(pY[index],pY[index+1]);
		}
		iboolean Z = pFunction(X, Y);
		unsigned int index = 2*k;
		pZ[index] = NAN; pZ[index+1] = NAN;
		if (Z == itrue) { pZ[index] = 1; pZ[index+1] = 1; }
		if (Z == ifalse) { pZ[index] = 0; pZ[index+1] = 0; }
		if (Z == iperhaps) { pZ[index] = 0; pZ[index+1] = 1; }
	}
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), nb elements.
inline void defaultibexIntervalfn1arg(double* pY, double* pX, unsigned int nb, ibex::Interval (*pFunction)(const ibex::Interval&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		unsigned int index = 2*k;
		ibex::Interval X = ibex::Interval(pX[index],pX[index+1]);
		ibex::Interval Y = pFunction(X);
		pY[index] = Y.lb(); pY[index+1] = Y.ub();
	}
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), nb elements.
inline void defaultintervalfn1arg(double* pY, double* pX, unsigned int nb, interval (*pFunction)(const interval&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		unsigned int index = 2*k;
		interval X = interval(pX[index],pX[index+1]);
		interval Y = pFunction(X);
		pY[index] = Y.inf; pY[index+1] = Y.sup;
	}
}

// Parameters : box/vector<box> (return value), box/vector<box> (arg), nb elements, box size.
inline void defaultboxfn1arg(double* pY, double* pX, unsigned int nb, unsigned int n, box (*pFunction)(const box&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		box X(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			X[i+1] = interval(pX[index],pX[index+1]);
		}
		box Y = pFunction(X);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			pY[index] = Y[i+1].inf; pY[index+1] = Y[i+1].sup;
		}
	}
}

// Parameters : imatrix (return value), imatrix (arg), nb elements, box size, imatrix width.
inline void defaultimatrixfn1arg(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m, imatrix (*pFunction)(const imatrix&))
{
	if (nb != 1) return; // vector<imatrix> unsupported.
	imatrix X(n,m);
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < m; j++)
		{
			unsigned int index = 2*(n*j+i);
			X.SetVal(i+1,j+1,interval(pX[index],pX[index+1]));
		}
	}
	imatrix Y = pFunction(X);
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < m; j++)
		{
			unsigned int index = 2*(n*j+i);
			pY[index] = Y(i+1,j+1).inf; pY[index+1] = Y(i+1,j+1).sup;
		}
	}
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), interval/vector<interval> (arg), nb elements.
inline void defaultintervalfn2arg(double* pZ, double* pX, double* pY, unsigned int nb, interval (*pFunction)(const interval&, const interval&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		unsigned int index = 2*k;
		interval X = interval(pX[index],pX[index+1]);
		interval Y = interval(pY[index],pY[index+1]);
		interval Z = pFunction(X, Y);
		pZ[index] = Z.inf; pZ[index+1] = Z.sup;
	}
}

// Parameters : box/vector<box> (return value), box/vector<box> (arg), box/vector<box> (arg), nb elements, box size.
inline void defaultboxfn2arg(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, box (*pFunction)(const box&, const box&))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		box X(n), Y(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			X[i+1] = interval(pX[index],pX[index+1]);
			Y[i+1] = interval(pY[index],pY[index+1]);
		}
		box Z = pFunction(X, Y);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			pZ[index] = Z[i+1].inf; pZ[index+1] = Z[i+1].sup;
		}
	}
}

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
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < m; j++)
		{
			unsigned int index = 2*(n*j+i);
			X.SetVal(i+1,j+1,interval(pX[index],pX[index+1]));
		}
	}
	pFunction(X);
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < m; j++)
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
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < m; j++)
		{
			unsigned int index = 2*(n*j+i);
			Y.SetVal(i+1,j+1,interval(pY[index],pY[index+1]));
			X.SetVal(i+1,j+1,interval(pX[index],pX[index+1]));
		}
	}
	pFunction(Y, X);
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < m; j++)
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
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < m; j++)
		{
			unsigned int index = 2*(n*j+i);
			Z.SetVal(i+1,j+1,interval(pZ[index],pZ[index+1]));
			X.SetVal(i+1,j+1,interval(pX[index],pX[index+1]));
			Y.SetVal(i+1,j+1,interval(pY[index],pY[index+1]));
		}
	}
	pFunction(Z, X, Y);
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < m; j++)
		{
			unsigned int index = 2*(n*j+i);
			pZ[index] = Z(i+1,j+1).inf; pZ[index+1] = Z(i+1,j+1).sup;
			pX[index] = X(i+1,j+1).inf; pX[index+1] = X(i+1,j+1).sup;
			pY[index] = Y(i+1,j+1).inf; pY[index+1] = Y(i+1,j+1).sup;
		}
	}
}

// Parameters : interval/vector<interval>, interval/vector<interval>, interval/vector<interval>, interval/vector<interval>, nb elements.
inline void Cdefaultintervalquaternarycontractor(double* pZ, double* pW, double* pX, double* pY, unsigned int nb, void (*pFunction)(interval&, interval&, interval&, interval&, int))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		unsigned int index = 2*k;
		interval Z = interval(pZ[index],pZ[index+1]);
		interval W = interval(pW[index],pW[index+1]);
		interval X = interval(pX[index],pX[index+1]);
		interval Y = interval(pY[index],pY[index+1]);
		pFunction(Z, W, X, Y, 0);
		pZ[index] = Z.inf; pZ[index+1] = Z.sup;
		pW[index] = W.inf; pW[index+1] = W.sup;
		pX[index] = X.inf; pX[index+1] = X.sup;
		pY[index] = Y.inf; pY[index+1] = Y.sup;
	}
}

// Parameters : box/vector<box>, box/vector<box>, box/vector<box>, box/vector<box>, nb elements, box size.
inline void Cdefaultboxquaternarycontractor(double* pZ, double* pW, double* pX, double* pY, unsigned int nb, unsigned int n, void (*pFunction)(box&, box&, box&, box&, int))
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
		pFunction(Z, W, X, Y, 0);
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

// Parameters : interval/vector<interval>, interval/vector<interval>, interval/vector<interval>, interval/vector<interval>, interval/vector<interval>, nb elements.
inline void Cdefaultintervalquinarycontractor(double* pZ, double* pV, double* pW, double* pX, double* pY, unsigned int nb, void (*pFunction)(interval&, interval&, interval&, interval&, interval&, int))
{
	for (unsigned int k = 0; k < nb; k++)
	{
		unsigned int index = 2*k;
		interval Z = interval(pZ[index],pZ[index+1]);
		interval V = interval(pV[index],pV[index+1]);
		interval W = interval(pW[index],pW[index+1]);
		interval X = interval(pX[index],pX[index+1]);
		interval Y = interval(pY[index],pY[index+1]);
		pFunction(Z, V, W, X, Y, 0);
		pZ[index] = Z.inf; pZ[index+1] = Z.sup;
		pV[index] = V.inf; pV[index+1] = V.sup;
		pW[index] = W.inf; pW[index+1] = W.sup;
		pX[index] = X.inf; pX[index+1] = X.sup;
		pY[index] = Y.inf; pY[index+1] = Y.sup;
	}
}

// Parameters : interval/box/imatrix/vector<interval>/vector<box> (return value), interval/box/imatrix/vector<interval>/vector<box>, interval/box/imatrix/vector<interval>/vector<box>, nb elements, box size, imatrix width.
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

// Parameters : interval/box/imatrix/vector<interval>/vector<box> (return value), interval/box/imatrix/vector<interval>/vector<box>, interval/box/imatrix/vector<interval>/vector<box>, nb elements, box size, imatrix width.
INTERVALX_ADAPT_API void Subx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		for (unsigned int k = 0; k < nb; k++)
		{
			box Z(n), X(n), Y(n);
			for (unsigned int i = 0; i < n; i++)
			{
				unsigned int index = 2*(n*k+i);
				X[i+1] = interval(pX[index],pX[index+1]);
				Y[i+1] = interval(pY[index],pY[index+1]);
			}
			Z = X - Y;
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
				X.SetVal(i+1,j+1,interval(pX[index],pX[index+1]));
				Y.SetVal(i+1,j+1,interval(pY[index],pY[index+1]));
			}
		}
		Z = X - Y;
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

// Parameters : interval/imatrix/vector<interval> (return value), interval/imatrix/vector<interval>, interval/imatrix/vector<interval>, nb elements, box size, imatrix width.
INTERVALX_ADAPT_API void Mulx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			for (unsigned int k = 0; k < nb; k++)
			{
				interval Z, X, Y;
				unsigned int index = 2*k;
				X = interval(pX[index],pX[index+1]);
				Y = interval(pY[index],pY[index+1]);
				Z = X * Y;
				pZ[index] = Z.inf; pZ[index+1] = Z.sup;
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
				X.SetVal(i+1,j+1,interval(pX[index],pX[index+1]));
				Y.SetVal(i+1,j+1,interval(pY[index],pY[index+1]));
			}
		}
		Z = X * Y;
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

// Parameters : box (return value), imatrix, box, nb elements, box size, imatrix width.
INTERVALX_ADAPT_API void Mulimatrixboxx(double* pc, double* pA, double* pb, unsigned int nb, unsigned int n, unsigned int m)
{
	if ((m > 1)&&(nb == 1))
	{
		imatrix A(n,m);
		box b(n), c(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*i;
			b[i+1] = interval(pb[index],pb[index+1]);
			for (unsigned int j = 0; j < m; j++)
			{
				unsigned int index = 2*(n*j+i);
				A.SetVal(i+1,j+1,interval(pA[index],pA[index+1]));
			}
		}
		c = A * b;
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*i;
			pc[index] = c[i+1].inf; pc[index+1] = c[i+1].sup;
		}
	}
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval>, interval/vector<interval>, nb elements, box size, imatrix width.
INTERVALX_ADAPT_API void Divx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			for (unsigned int k = 0; k < nb; k++)
			{
				interval Z, X, Y;
				unsigned int index = 2*k;
				X = interval(pX[index],pX[index+1]);
				Y = interval(pY[index],pY[index+1]);
				Z = X / Y;
				pZ[index] = Z.inf; pZ[index+1] = Z.sup;
			}
		}
	}
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), interval/vector<interval> (arg), nb elements.
INTERVALX_ADAPT_API void Minx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultintervalfn2arg(pZ, pX, pY, nb, Min);
		//else defaultboxfn2arg(pZ, pX, pY, nb, n, Min);
	}
	//else if (nb == 1) defaultimatrixfn2arg(pZ, pX, pY, nb, n, m, Min);
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), interval/vector<interval> (arg), nb elements.
INTERVALX_ADAPT_API void Maxx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultintervalfn2arg(pZ, pX, pY, nb, Max);
		//else defaultboxfn2arg(pZ, pX, pY, nb, n, Max);
	}
	//else if (nb == 1) defaultimatrixfn2arg(pZ, pX, pY, nb, n, m, Max);
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), nb elements.
INTERVALX_ADAPT_API void Absx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultibexIntervalfn1arg(pY, pX, nb, Abs);
		//else defaultboxfn1arg(pY, pX, nb, n, Abs);
	}
	//else if (nb == 1) defaultimatrixfn1arg(pY, pX, nb, n, m, Abs);
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), nb elements.
INTERVALX_ADAPT_API void Sqrx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultibexIntervalfn1arg(pY, pX, nb, Sqr);
		//else defaultboxfn1arg(pY, pX, nb, n, Sqr);
	}
	//else if (nb == 1) defaultimatrixfn1arg(pY, pX, nb, n, m, Sqr);
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), nb elements.
INTERVALX_ADAPT_API void Sqrtx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultibexIntervalfn1arg(pY, pX, nb, Sqrt);
		//else defaultboxfn1arg(pY, pX, nb, n, Sqrt);
	}
	//else if (nb == 1) defaultimatrixfn1arg(pY, pX, nb, n, m, Sqrt);
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), double/vector<double> (arg), nb elements.
INTERVALX_ADAPT_API void Powx(double* pY, double* pX, double* pn_exp, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			for (unsigned int k = 0; k < nb; k++)
			{
				unsigned int index = 2*k;
				double n_exp = pn_exp[k];
				ibex::Interval X = ibex::Interval(pX[index],pX[index+1]);
				ibex::Interval Y = Pow(X, n_exp);
				pY[index] = Y.lb(); pY[index+1] = Y.ub();
			}
		}
	}
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), nb elements.
INTERVALX_ADAPT_API void Expx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultibexIntervalfn1arg(pY, pX, nb, Exp);
		//else defaultboxfn1arg(pY, pX, nb, n, Exp);
	}
	//else if (nb == 1) defaultimatrixfn1arg(pY, pX, nb, n, m, Exp);
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), nb elements.
INTERVALX_ADAPT_API void Logx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultibexIntervalfn1arg(pY, pX, nb, Log);
		//else defaultboxfn1arg(pY, pX, nb, n, Log);
	}
	//else if (nb == 1) defaultimatrixfn1arg(pY, pX, nb, n, m, Log);
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), nb elements.
INTERVALX_ADAPT_API void Cosx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultibexIntervalfn1arg(pY, pX, nb, Cos);
		//else defaultboxfn1arg(pY, pX, nb, n, Cos);
	}
	//else if (nb == 1) defaultimatrixfn1arg(pY, pX, nb, n, m, Cos);
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), nb elements.
INTERVALX_ADAPT_API void Sinx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultibexIntervalfn1arg(pY, pX, nb, Sin);
		//else defaultboxfn1arg(pY, pX, nb, n, Sin);
	}
	//else if (nb == 1) defaultimatrixfn1arg(pY, pX, nb, n, m, Sin);
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), nb elements.
INTERVALX_ADAPT_API void Tanx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultibexIntervalfn1arg(pY, pX, nb, Tan);
		//else defaultboxfn1arg(pY, pX, nb, n, Tan);
	}
	//else if (nb == 1) defaultimatrixfn1arg(pY, pX, nb, n, m, Tan);
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), nb elements.
INTERVALX_ADAPT_API void Acosx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultibexIntervalfn1arg(pY, pX, nb, Acos);
		//else defaultboxfn1arg(pY, pX, nb, n, Acos);
	}
	//else if (nb == 1) defaultimatrixfn1arg(pY, pX, nb, n, m, Acos);
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), nb elements.
INTERVALX_ADAPT_API void Asinx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultibexIntervalfn1arg(pY, pX, nb, Asin);
		//else defaultboxfn1arg(pY, pX, nb, n, Asin);
	}
	//else if (nb == 1) defaultimatrixfn1arg(pY, pX, nb, n, m, Asin);
}

// Parameters : interval/vector<interval> (return value), interval/vector<interval> (arg), nb elements.
INTERVALX_ADAPT_API void Atanx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultibexIntervalfn1arg(pY, pX, nb, Atan);
		//else defaultboxfn1arg(pY, pX, nb, n, Atan);
	}
	//else if (nb == 1) defaultimatrixfn1arg(pY, pX, nb, n, m, Atan);
}

// Parameters : imatrix (return value), imatrix (arg), nb elements.
INTERVALX_ADAPT_API void Transposex(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (nb == 1) defaultimatrixfn1arg(pY, pX, nb, n, m, Transpose);
}

// Parameters : box/vector<box> (return value), box/vector<box> (arg), box/vector<box> (arg), nb elements.
INTERVALX_ADAPT_API void Concatx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		defaultboxfn2arg(pZ, pX, pY, nb, n, Concat);
	}
	//else if (nb == 1) defaultimatrixfn2arg(pZ, pX, pY, nb, n, m, Concat);
}

// Parameters : box (return value), vector<interval>/vector<box> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Interx(double* pr, double* px, unsigned int nb, unsigned int n)
{
	box r(n); vector<box> x(nb, r);
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
		pr[index] = r[i+1].inf; pr[index+1] = r[i+1].sup;
	}
}

// Parameters : box (return value), vector<interval>/vector<box> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Unionx(double* pr, double* px, unsigned int nb, unsigned int n)
{
	box r(n); vector<box> x(nb, r);
	for (unsigned int k = 0; k < nb; k++)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			r[i+1] = interval(px[index],px[index+1]);
		}
		x[k] = r;
	}
	r = Union(x);
	for (unsigned int i = 0; i < n; i++)
	{
		unsigned int index = 2*i;
		pr[index] = r[i+1].inf; pr[index+1] = r[i+1].sup;
	}
}

// Parameters : int/vector<int> (return value), box/vector<box> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Sizex(int* py, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		defaultintfn1boxarg(py, pX, nb, n, Size);
	}
}

// Parameters : double/vector<double> (return value), interval/vector<interval> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Infx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultdoublefn1intervalarg(py, pX, nb, Inf);
		else defaultboxfn1arg(py, pX, nb, n, Inf);
	}
	//else if (nb == 1) defaultimatrixfn1arg(py, pX, nb, n, m, Inf);
}

// Parameters : double/vector<double> (return value), interval/vector<interval> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Supx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultdoublefn1intervalarg(py, pX, nb, Sup);
		else defaultboxfn1arg(py, pX, nb, n, Sup);
	}
	//else if (nb == 1) defaultimatrixfn1arg(py, pX, nb, n, m, Sup);
}

// Parameters : double/vector<double> (return value), interval/vector<interval> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Centerx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultdoublefn1intervalarg(py, pX, nb, Center);
		else defaultboxfn1arg(py, pX, nb, n, Center);
	}
	//else if (nb == 1) defaultimatrixfn1arg(py, pX, nb, n, m, Center);
}

// Parameters : double/vector<double> (return value), interval/box/vector<interval>/vector<box> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Widthx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultdoublefn1intervalarg(py, pX, nb, Width);
		else defaultdoublefn1boxarg(py, pX, nb, n, Width);
	}
	//else if (nb == 1) defaultdoublefn1imatrixarg(py, pX, nb, n, m, Width);
}

// Parameters : double/vector<double> (return value), interval/box/vector<interval>/vector<box> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Volumex(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultdoublefn1intervalarg(py, pX, nb, Volume);
		else defaultdoublefn1boxarg(py, pX, nb, n, Volume);
	}
	//else if (nb == 1) defaultdoublefn1imatrixarg(py, pX, nb, n, m, Volume);
}

// Parameters : double/vector<double> (return value), interval/vector<interval> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Radx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultdoublefn1intervalarg(py, pX, nb, Rad);
		//else defaultdoublefn1boxarg(py, pX, nb, n, Rad);
	}
	//else if (nb == 1) defaultdoublefn1imatrixarg(py, pX, nb, n, m, Rad);
}

// Parameters : double/vector<double> (return value), interval/vector<interval> (arg), nb elements, box size.
INTERVALX_ADAPT_API void ToRealx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultdoublefn1intervalarg(py, pX, nb, ToReal);
		//else defaultdoublefn1boxarg(py, pX, nb, n, ToReal);
	}
	//else if (nb == 1) defaultdoublefn1imatrixarg(py, pX, nb, n, m, ToReal);
}

// Parameters : double/vector<double> (return value), box/vector<box> (arg), nb elements, box size.
INTERVALX_ADAPT_API void IsBoxx(double* py, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		defaultboolfn1boxarg(py, pX, nb, n, IsBox);
	}
}

// Parameters : box/vector<box> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Updatex(double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		for (unsigned int k = 0; k < nb; k++)
		{
			box X(n);
			for (unsigned int i = 0; i < n; i++)
			{
				unsigned int index = 2*(n*k+i);
				X[i+1] = interval(pX[index],pX[index+1]);
			}
			Update(X);
			for (unsigned int i = 0; i < n; i++)
			{
				unsigned int index = 2*(n*k+i);
				pX[index] = X[i+1].inf; pX[index+1] = X[i+1].sup;
			}
		}
	}
}

// Parameters : double/vector<double> (return value), box/vector<box> (arg), box/vector<box> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Anglex(double* pz, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 2) defaultdoublefn2boxarg(pz, pX, pY, nb, n, Angle);
	}
}

// Parameters : double/vector<double> (return value), interval/box/vector<interval>/vector<box> (arg), interval/box/vector<interval>/vector<box> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Disjointx(double* pz, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultboolfn2intervalarg(pz, pX, pY, nb, Disjoint);
		else defaultboolfn2boxarg(pz, pX, pY, nb, n, Disjoint);
	}
}

// Parameters : double/vector<double> (return value), interval/box/vector<interval>/vector<box> (arg), interval/box/vector<interval>/vector<box> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Subsetx(double* pz, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultboolfn2intervalarg(pz, pX, pY, nb, Subset);
		else defaultboolfn2boxarg(pz, pX, pY, nb, n, Subset);
	}
}

// Parameters : double/vector<double> (return value), interval/box/vector<interval>/vector<box> (arg), interval/box/vector<interval>/vector<box> (arg), nb elements, box size.
INTERVALX_ADAPT_API void SubsetStrictx(double* pz, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultboolfn2intervalarg(pz, pX, pY, nb, SubsetStrict);
		else defaultboolfn2boxarg(pz, pX, pY, nb, n, SubsetStrict);
	}
}

// Parameters : iboolean/vector<iboolean> (return value), interval/box/vector<interval>/vector<box> (arg), interval/box/vector<interval>/vector<box> (arg), nb elements, box size.
INTERVALX_ADAPT_API void Inx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) defaultibooleanfn2intervalarg(pZ, pX, pY, nb, In);
		else defaultibooleanfn2boxarg(pZ, pX, pY, nb, n, In);
	}
}

// Parameters : double/vector<double> (return value), interval/box/vector<interval>/vector<box> (arg), interval/box/vector<interval>/vector<box> (arg), nb elements, box size.
INTERVALX_ADAPT_API void decreasex(double* pz, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n >= 1) defaultdoublefn2boxarg(pz, pX, pY, nb, n, decrease);
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

INTERVALX_ADAPT_API void Cmulimatrixboxx(double* pc, double* pA, double* pb, unsigned int nb, unsigned int n, unsigned int m)
{
	if ((m > 1)&&(nb == 1))
	{
		imatrix A(n,m);
		box b(n), c(n);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*i;
			b[i+1] = interval(pb[index],pb[index+1]);
			c[i+1] = interval(pc[index],pc[index+1]);
			for (unsigned int j = 0; j < m; j++)
			{
				unsigned int index = 2*(n*j+i);
				A.SetVal(i+1,j+1,interval(pA[index],pA[index+1]));
			}
		}
		Cmul(c, A, b);
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*i;
			pb[index] = b[i+1].inf; pb[index+1] = b[i+1].sup;
			pc[index] = c[i+1].inf; pc[index+1] = c[i+1].sup;
			for (unsigned int j = 0; j < m; j++)
			{
				unsigned int index = 2*(n*j+i);
				pA[index] = A(i+1,j+1).inf; pA[index+1] = A(i+1,j+1).sup;
			}
		}
	}
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
		if (n == 1) 
		{
			for (unsigned int k = 0; k < nb; k++)
			{
				unsigned int index = 2*k;
				interval Z = interval(pZ[index],pZ[index+1]);
				interval W = interval(pW[index],pW[index+1]);
				interval X = interval(pX[index],pX[index+1]);
				interval Y = interval(pY[index],pY[index+1]);
				Cchi(Z, W, X, Y);
				pZ[index] = Z.inf; pZ[index+1] = Z.sup;
				pW[index] = W.inf; pW[index+1] = W.sup;
				pX[index] = X.inf; pX[index+1] = X.sup;
				pY[index] = Y.inf; pY[index+1] = Y.sup;
			}
		}
		//else Cdefaultboxquaternarycontractor(pZ, pW, pX, pY, nb, n, Cchi);
	}
	//else if (nb == 1) Cdefaultimatrixquaternarycontractor(pZ, pW, pX, pY, nb, n, m, Cchi);
}

INTERVALX_ADAPT_API void Cgeqx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
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
				Cgeq(Y, X);
				pY[index] = Y.inf; pY[index+1] = Y.sup;
				pX[index] = X.inf; pX[index+1] = X.sup;
			}
		}
		//else Cdefaultboxbinarycontractor(pY, pX, nb, n, Cgeq);
	}
	//else if (nb == 1) Cdefaultimatrixbinarycontractor(pY, pX, nb, n, m, Cgeq);
}

INTERVALX_ADAPT_API void Cintegerx(double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalunarycontractor(pX, nb, Cinteger);
		//else Cdefaultboxunarycontractor(pX, nb, n, Cinteger);
	}
	//else if (nb == 1) Cdefaultimatrixunarycontractor(pX, nb, n, m, Cinteger);
}

INTERVALX_ADAPT_API void Cbooleanx(double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalunarycontractor(pX, nb, Cboolean);
		//else Cdefaultboxunarycontractor(pX, nb, n, Cboolean);
	}
	//else if (nb == 1) Cdefaultimatrixunarycontractor(pX, nb, n, m, Cboolean);
}

INTERVALX_ADAPT_API void Crotx(double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (nb == 1) Cdefaultimatrixunarycontractor(pX, nb, n, m, Crot);
}

INTERVALX_ADAPT_API void Cantisymx(double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (nb == 1) Cdefaultimatrixunarycontractor(pX, nb, n, m, Cantisym);
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

INTERVALX_ADAPT_API void Cpowx(double* pY, double* pX, int* pn_exp, unsigned int nb, unsigned int n, unsigned int m)
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
				int n_exp = pn_exp[k];
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

INTERVALX_ADAPT_API void Catanx(double* pY, double* pX, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalbinarycontractor(pY, pX, nb, Catan);
		//else Cdefaultboxbinarycontractor(pY, pX, nb, n, Catan);
	}
	//else if (nb == 1) Cdefaultimatrixbinarycontractor(pY, pX, nb, n, m, Catan);
}

INTERVALX_ADAPT_API void Cnormx(double* pZ, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			for (unsigned int k = 0; k < nb; k++)
			{
				unsigned int index = 2*k;
				interval Z = interval(pZ[index],pZ[index+1]);
				interval X = interval(pX[index],pX[index+1]);
				interval Y = interval(pY[index],pY[index+1]);
				Cnorm(Z, X, Y);
				pZ[index] = Z.inf; pZ[index+1] = Z.sup;
				pX[index] = X.inf; pX[index+1] = X.sup;
				pY[index] = Y.inf; pY[index+1] = Y.sup;
			}
		}
		//else Cdefaultboxternarycontractor(pZ, pX, pY, nb, n, Cnorm);
	}
	//else if (nb == 1) Cdefaultimatrixternarycontractor(pZ, pX, pY, nb, n, m, Cnorm);
}

INTERVALX_ADAPT_API void Cnorm3Dx(double* pN, double* pX, double* pY, double* pZ, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalquaternarycontractor(pN, pX, pY, pZ, nb, Cnorm);
		//else Cdefaultboxquaternarycontractor(pN, pX, pY, pZ, nb, n, Cnorm);
	}
	//else if (nb == 1) Cdefaultimatrixquaternarycontractor(pN, pX, pY, pZ, nb, n, m, Cnorm);
}

INTERVALX_ADAPT_API void Cdistx(double* pZ, double* pV, double* pW, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			for (unsigned int k = 0; k < nb; k++)
			{
				unsigned int index = 2*k;
				interval Z = interval(pZ[index],pZ[index+1]);
				interval V = interval(pV[index],pV[index+1]);
				interval W = interval(pW[index],pW[index+1]);
				interval X = interval(pX[index],pX[index+1]);
				interval Y = interval(pY[index],pY[index+1]);
				Cdist(Z, V, W, X, Y);
				pZ[index] = Z.inf; pZ[index+1] = Z.sup;
				pV[index] = V.inf; pV[index+1] = V.sup;
				pW[index] = W.inf; pW[index+1] = W.sup;
				pX[index] = X.inf; pX[index+1] = X.sup;
				pY[index] = Y.inf; pY[index+1] = Y.sup;
			}
		}
		//else Cdefaultboxquinarycontractor(pZ, pV, pW, pX, pY, nb, n, Cdist);
	}
	//else if (nb == 1) Cdefaultimatrixquinarycontractor(pZ, pV, pW, pX, pY, nb, n, m, Cdist);
}

INTERVALX_ADAPT_API void Cscalx(double* pZ, double* pV, double* pW, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			for (unsigned int k = 0; k < nb; k++)
			{
				unsigned int index = 2*k;
				interval Z = interval(pZ[index],pZ[index+1]);
				interval V = interval(pV[index],pV[index+1]);
				interval W = interval(pW[index],pW[index+1]);
				interval X = interval(pX[index],pX[index+1]);
				interval Y = interval(pY[index],pY[index+1]);
				Cscal(Z, V, W, X, Y);
				pZ[index] = Z.inf; pZ[index+1] = Z.sup;
				pV[index] = V.inf; pV[index+1] = V.sup;
				pW[index] = W.inf; pW[index+1] = W.sup;
				pX[index] = X.inf; pX[index+1] = X.sup;
				pY[index] = Y.inf; pY[index+1] = Y.sup;
			}
		}
		//else Cdefaultboxquinarycontractor(pZ, pV, pW, pX, pY, nb, n, Cscal);
	}
	//else if (nb == 1) Cdefaultimatrixquinarycontractor(pZ, pV, pW, pX, pY, nb, n, m, Cscal);
}

INTERVALX_ADAPT_API void Cdetx(double* pZ, double* pV, double* pW, double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalquinarycontractor(pZ, pV, pW, pX, pY, nb, Cdet);
		//else Cdefaultboxquinarycontractor(pZ, pV, pW, pX, pY, nb, n, Cdet);
	}
	//else if (nb == 1) Cdefaultimatrixquinarycontractor(pZ, pV, pW, pX, pY, nb, n, m, Cdet);
}

INTERVALX_ADAPT_API void CinRingx(double* pX, double* pY, double* pcx, double* pcy, double* pR, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			for (unsigned int k = 0; k < nb; k++)
			{
				unsigned int index = 2*k;
				interval X = interval(pX[index],pX[index+1]), Y = interval(pY[index],pY[index+1]);
				double cx = pcx[k], cy = pcy[k];
				interval R = interval(pR[index],pR[index+1]);
				CPointInRing(X, Y, cx, cy, R);
				pX[index] = X.inf; pX[index+1] = X.sup;
				pY[index] = Y.inf; pY[index+1] = Y.sup;
			}
		}
	}
}

INTERVALX_ADAPT_API void CinSegmentx(double* pX, double* pY, double* pax, double* pay, double* pbx, double* pby, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			for (unsigned int k = 0; k < nb; k++)
			{
				unsigned int index = 2*k;
				interval X = interval(pX[index],pX[index+1]), Y = interval(pY[index],pY[index+1]);
				double ax = pax[k], ay = pay[k], bx = pbx[k], by = pby[k];
				CPointInSegment(X, Y, ax, ay, bx, by);
				pX[index] = X.inf; pX[index+1] = X.sup;
				pY[index] = Y.inf; pY[index+1] = Y.sup;
			}
		}
	}
}

INTERVALX_ADAPT_API void CinSegmentsx(double* pX, double* pY, double* pax, double* pay, double* pbx, double* pby, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			vector<double> ax(nb), ay(nb), bx(nb), by(nb);
			for (unsigned int k = 0; k < nb; k++)
			{
				ax[k] = pax[k]; ay[k] = pay[k]; bx[k] = pbx[k]; by[k] = pby[k];
			}
			interval X = interval(pX[0],pX[1]), Y = interval(pY[0],pY[1]);
			CPointInSegments(X, Y, ax, ay, bx, by);
			pX[0] = X.inf; pX[1] = X.sup;
			pY[0] = Y.inf; pY[1] = Y.sup;
		}
	}
}

INTERVALX_ADAPT_API void CinCirclex(double* pX, double* pY, double* pcx, double* pcy, double* pr, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			for (unsigned int k = 0; k < nb; k++)
			{
				unsigned int index = 2*k;
				interval X = interval(pX[index],pX[index+1]), Y = interval(pY[index],pY[index+1]);
				double cx = pcx[k], cy = pcy[k], r = pr[k];
				CPointInCircle(X, Y, cx, cy, r);
				pX[index] = X.inf; pX[index+1] = X.sup;
				pY[index] = Y.inf; pY[index+1] = Y.sup;
			}
		}
	}
}

INTERVALX_ADAPT_API void CinCirclesx(double* pX, double* pY, double* pcx, double* pcy, double* pr, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			vector<double> cx(nb), cy(nb), r(nb);
			for (unsigned int k = 0; k < nb; k++)
			{
				cx[k] = pcx[k]; cy[k] = pcy[k]; r[k] = pr[k];
			}
			interval X = interval(pX[0],pX[1]), Y = interval(pY[0],pY[1]);
			CPointInCircles(X, Y, cx, cy, r);
			pX[0] = X.inf; pX[1] = X.sup;
			pY[0] = Y.inf; pY[1] = Y.sup;
		}
	}
}

INTERVALX_ADAPT_API void CinSegmentsOrCirclesx(double* pX, double* pY, double* pax, double* pay, double* pbx, double* pby, double* pcx, double* pcy, double* pr, unsigned int nbs, unsigned int nbc, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			vector<double> ax(nbs), ay(nbs), bx(nbs), by(nbs), cx(nbc), cy(nbc), r(nbc);
			for (unsigned int k = 0; k < nbs; k++)
			{
				ax[k] = pax[k]; ay[k] = pay[k]; bx[k] = pbx[k]; by[k] = pby[k];
			}
			for (unsigned int k = 0; k < nbc; k++)
			{
				cx[k] = pcx[k]; cy[k] = pcy[k]; r[k] = pr[k];
			}
			interval X = interval(pX[0],pX[1]), Y = interval(pY[0],pY[1]);
			CPointInSegmentsOrCircles(X, Y, ax, ay, bx, by, cx, cy, r);
			pX[0] = X.inf; pX[1] = X.sup;
			pY[0] = Y.inf; pY[1] = Y.sup;
		}
	}
}

INTERVALX_ADAPT_API void Corthox(double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		Cdefaultboxbinarycontractor(pX, pY, nb, n, Cortho);
	}
}

INTERVALX_ADAPT_API void Cnotinx(double* pX, double* pY, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) Cdefaultintervalbinarycontractor(pX, pY, nb, Cnotin);
		else Cdefaultboxbinarycontractor(pX, pY, nb, n, Cnotin);
	}
	//else if (nb == 1) Cdefaultimatrixbinarycontractor(pY, pX, nb, n, m, Catan);
}

// Parameters : interval/box, q, vector<interval>/vector<box>, nb elements, box size.
INTERVALX_ADAPT_API void C_q_inx(double* px, int q, double* pyj, unsigned int nb, unsigned int n)
{
	box x(n); vector<box> yj(nb, x);
	for (unsigned int k = 0; k < nb; k++)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			unsigned int index = 2*(n*k+i);
			x[i+1] = interval(pyj[index],pyj[index+1]);
		}
		yj[k] = x;
	}
	for (unsigned int i = 0; i < n; i++)
	{
		unsigned int index = 2*i;
		x[i+1] = interval(px[index],px[index+1]);
	}
	C_q_in(x, q, yj);
	for (unsigned int i = 0; i < n; i++)
	{
		unsigned int index = 2*i;
		px[index] = x[i+1].inf; px[index+1] = x[i+1].sup;
	}
}

INTERVALX_ADAPT_API void SinRingx(double* pX, double* pY, double* pcx, double* pcy, double* pR, int* pbOuter, unsigned int nb, unsigned int n, unsigned int m)
{
	if (m == 1)
	{
		if (n == 1) 
		{
			for (unsigned int k = 0; k < nb; k++)
			{
				unsigned int index = 2*k;
				interval X = interval(pX[index],pX[index+1]), Y = interval(pY[index],pY[index+1]);
				double cx = pcx[k], cy = pcy[k];
				interval R = interval(pR[index],pR[index+1]);
				bool outer = (pbOuter[index])?true:false;
				SinRing(X, Y, cx, cy, R, outer);
				pX[index] = X.inf; pX[index+1] = X.sup;
				pY[index] = Y.inf; pY[index+1] = Y.sup;
			}
		}
	}
}

// Parameters : box, box, box, box size.
INTERVALX_ADAPT_API void Bisectx(double* pX, double* pX1, double* pX2, unsigned int n)
{
	box X(n); box X1 = Infinity(n); box X2 = Infinity(n);
	for (unsigned int i = 0; i < n; i++)
	{
		unsigned int index = 2*i;
		X[i+1] = interval(pX[index],pX[index+1]);
	}
	Bisect(X, X1, X2);
	for (unsigned int i = 0; i < n; i++)
	{
		unsigned int index = 2*i;
		pX1[index] = X1[i+1].inf; pX1[index+1] = X1[i+1].sup;
		pX2[index] = X2[i+1].inf; pX2[index+1] = X2[i+1].sup;
	}
}
