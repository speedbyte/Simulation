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
#define	N_IN	prhs[1]


/* Output Arguments */

#define	YP_OUT	plhs[0]

#if !defined(MAX)
#define	MAX(A, B)	((A) > (B) ? (A) : (B))
#endif

#if !defined(MIN)
#define	MIN(A, B)	((A) < (B) ? (A) : (B))
#endif

static void Crc16(double ret[], double bytes[], char n)
{
  int crc = 0;
  int buffer = 0;
  char i = 0;
  char j = 0;

  for (i = 0; i < n; i++)                 /* loop for each data byte */
            {
                buffer = (int)bytes[i];
                ret[i] = bytes[i];
                for (j = 0; j < 8; j++)               /* loop for each bit in one data byte */
                {
                    if (((crc ^ buffer) & 1) != 0)
                    {
                        crc = (crc >> 1) ^ 0xA001;
                    }
                    else
                    {
                        crc = crc >> 1;
                    }
                    buffer = buffer >> 1;
                }
            }
 ret[n+1] = ((double)(crc & 0xFF));
 ret[n] = ((double)(crc>>8 & 0xFF));
  
}

void mexFunction( int nlhs, mxArray *plhs[], 
		  int nrhs, const mxArray*prhs[] )
     
{ 
    double *yp; 
    double *t,*y; 
    mwSize m,n; 
    double *N_pointer;
    char N;
    
   
    N_pointer = mxGetPr(N_IN);
    N = N_pointer[0];
    /* Check the dimensions of Y.  Y can be 4 X 1 or 1 X 4. */ 
    
    m = mxGetM(Y_IN); 
    n = mxGetN(Y_IN);
    
    //printf("Sizes Requested %i size m: %i size n: %i  !mxIsDouble(Y_IN) %i\n", N, m, n,!mxIsDouble(Y_IN));
    if ( m != N || n !=1 ) { //!mxIsDouble(Y_IN) ||
	mexErrMsgTxt("YPRIME requires that Y be a 4 x 1 vector."); 
    } 
    
    /* Create a matrix for the return argument */ 
    YP_OUT = mxCreateDoubleMatrix(N+2, 1, mxREAL); 
    
    /* Assign pointers to the various parameters */ 
    yp = mxGetPr(YP_OUT);
    
    //t = mxGetPr(T_IN); 
    y = mxGetPr(Y_IN);
        
    /* Do the actual computations in a subroutine */
    Crc16(yp,y,N); 
    return;
    
}


