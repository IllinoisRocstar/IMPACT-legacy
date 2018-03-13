//
//  Copyright@2013, Illinois Rocstar LLC. All rights reserved.
//        
//  See LICENSE file included with this source or
//  (opensource.org/licenses/NCSA) for license information. 
//

#ifndef RFC_TIMING_H
#define RFC_TIMING_H

#ifdef WIN32
#include <time.h>
#include <sys/types.h>  
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif // WIN32
#include "rfc_basic.h"

RFC_BEGIN_NAME_SPACE

inline double get_wtime() {
#ifdef WIN32
	time_t ltime;
	struct _timeb tstruct;
	time(&ltime);
	_ftime(&tstruct);
	return (long long)ltime*1. + tstruct.millitm*1.e-3;
#else
	::timeval tv;
	gettimeofday(&tv, NULL)
		return tv.tv_sec + tv.tv_usec*1.e-6;
#endif
}

RFC_END_NAME_SPACE

#endif


