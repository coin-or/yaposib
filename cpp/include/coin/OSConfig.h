/* $Id: OSConfig.h 2698 2009-06-09 04:14:07Z kmartin $ */
/*
 * Include file for the configuration of OS.
 *
 * On systems where the code is configured with the configure script
 * (i.e., compilation is always done with HAVE_CONFIG_H defined), this
 * header file includes the automatically generated header file, and
 * undefines macros that might configure with other Config.h files.
 *
 * On systems that are compiled in other ways (e.g., with the
 * Developer Studio), a header files is included to define those
 * macros that depend on the operating system and the compiler.  The
 * macros that define the configuration of the particular user setting
 * (e.g., presence of other COIN packages or third party code) are set
 * here.  The project maintainer needs to remember to update this file
 * and choose reasonable defines.  A user can modify the default
 * setting by editing this file here.
 *
 */



     
#ifndef __OSCONFIG_H__
#define __COINUTILSCONFIG_H__ 



	#ifdef HAVE_CONFIG_H
		#include "config_os.h"


		//#ifndef MSVISUALSTUDIO 
		//#include "config_os.h"
		//#endif

		/* undefine macros that could conflict with those in other config.h
		   files */
		#undef PACKAGE
		#undef PACKAGE_BUGREPORT
		#undef PACKAGE_NAME
		#undef PACKAGE_STRING
		#undef PACKAGE_TARNAME
		#undef PACKAGE_VERSION
		#undef VERSION

	#else /* HAVE_CONFIG_H  NOT DEFINED */

		/* include the COIN-wide system specific configure header */
		// kipp look at this later
		#include "configall_system.h"

		#ifdef _MSC_VER   /* for MicroSoft Visual Studio */

		/***************************************************************************/
		/*             HERE DEFINE THE CONFIGURATION SPECIFIC MACROS               */
		/***************************************************************************/
				
			/* If defined, debug sanity checks are performed during runtime */
			/* #define COIN_DEBUG 1 */

			/* Define to 1 if the Clp package is used */
			#define COIN_HAS_CLP 1

			/* Define to 1 if the Cgl package is used */
			#define COIN_HAS_CGL 1

			/* Define to 1 if the CoinUtils package is used */
			#define COIN_HAS_COINUTILS 1

			/* Define to 1 if the OSI package is used */
			#define COIN_HAS_OSI 1

			/* Define to 1 if the DyLP package is used */
//			#define COIN_HAS_DYLP 1

			/* Define to 1 if the OSI package is used */
			#define COIN_HAS_OSI 1

			/* Define to 1 if the SYMPHONY package is used */
			#define COIN_HAS_SYMPHONY 1

			/* Define to 1 if the Vol package is used */
			#define COIN_HAS_VOL 1

			/* Define to 1 if the CppAD package is used */
			#define COIN_HAS_CPPAD 1
	
			/* Needed for OSFileUpload */
			#ifndef MY_C_FINITE
			#define MY_C_FINITE _finite
			#endif

		#endif	

		// needed for cygwin gcc 3.*,*
	#endif /* HAVE_CONFIG_H NOT DEFINED */
#endif /*__OSCONFIG_H___*/
//#ifdef WIN_
//	#ifndef _SYS_UNISTD_H
//	#define _SYS_UNISTD_H
//	#endif
//#endif
