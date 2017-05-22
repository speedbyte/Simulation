/*=================================================================
 *
 * YPRIME.C	Sample .MEX file corresponding to YPRIME.M
 *	        Solves simple 3 body orbit problem 
 *
 * The calling syntax is:
 *
 *		[yp] = yprime(t, y)
 *
 *  You may also want to look at the corresponding M-code, yprime.m.
 *
 * This is a MEX-file for MATLAB.  
 * Copyright 1984-2006 The MathWorks, Inc.
 *
 *=================================================================*/
/* $Revision: 1.10.6.4 $ */
#include <math.h>
#include "mex.h"

/* Input Arguments */

#define	Y_IN	prhs[0]

/* Output Arguments */

#define	YP_OUT	plhs[0]

#if !defined(MAX)
#define	MAX(A, B)	((A) > (B) ? (A) : (B))
#endif

#if !defined(MIN)
#define	MIN(A, B)	((A) < (B) ? (A) : (B))
#endif

void mexFunction( int nlhs, mxArray *plhs[], 
		  int nrhs, const mxArray*prhs[] )
     
{ 
    double *yp; 
    double *t,*y; 
    mwSize m,n; 
    int yint;
    
    /* Check the dimensions of Y.  Y can be 4 X 1 or 1 X 4. */ 
    
    m = mxGetM(Y_IN); 
    n = mxGetN(Y_IN);
    
    //printf("Sizes Requested %i size m: %i size n: %i  !mxIsDouble(Y_IN) %i\n", N, m, n,!mxIsDouble(Y_IN));
    if ( !mxIsDouble(Y_IN) || m != 1 || n !=1 ) { //|
	mexErrMsgTxt("YPRIME requires that Y be a 4 x 1 vector."); 
    } 
    
    /* Create a matrix for the return argument */ 
    YP_OUT = mxCreateDoubleMatrix(2, 1, mxREAL); 
    
    /* Assign pointers to the various parameters */ 
    yp = mxGetPr(YP_OUT);
    
    //t = mxGetPr(T_IN); 
    y = mxGetPr(Y_IN);
    yint = (int)(y[0]);
    
    yp[0] = (yint >> 8)&0xFF;
    yp[1] = yint&0xFF;
        
    return;
    
}


