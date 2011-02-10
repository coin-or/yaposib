/* $Id: OSdtoa.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** @file MathUtil.h
 * 
 * @author  Robert Fourer,  Jun Ma, Kipp Martin, 
 * @version 1.0, 10/05/2005
 * @since   OS1.0
 *
 * \remarks
 * Copyright (C) 2005, Robert Fourer, Jun Ma, Kipp Martin,
 * Northwestern University, and the University of Chicago.
 * All Rights Reserved.
 * This software is licensed under the Common Public License. 
 * Please see the accompanying LICENSE file in root directory for terms.
 *
 * <p>The <code>MathUtil</code> class contains methods for performing
 * mathematics related operations used by many classes in the
 * Optimization Services (OS) framework. </p>
 * 
 */
 
 
#ifndef OSDTOA_H
#define OSDTOA_H
 






#ifdef __cplusplus
extern "C" double os_strtod(const char *str, char **strEnd );
extern "C" char *os_dtoa(double d, int mode, int ndigits, int *decpt, int *sign, char **rve);
extern "C" void os_freedtoa(char *s);
#else
#ifdef __STDC__
double os_strtod(const char * str, char ** endptr );
char  *os_dtoa(double d, int mode, int ndigits, int *decpt, int *sign, char **rve);
void  os_freedtoa(char *s);	
#endif
#endif 







#endif // end  OSDTOA_H
