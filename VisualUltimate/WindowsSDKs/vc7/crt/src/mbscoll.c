/***
*mbscoll.c - Collate MBCS strings
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Collate MBCS strings
*
*******************************************************************************/

#ifdef _MBCS

#include <awint.h>
#include <mtdll.h>
#include <cruntime.h>
#include <internal.h>
#include <mbdata.h>
#include <mbctype.h>
#include <string.h>
#include <mbstring.h>


/***
* _mbscoll - Collate MBCS strings
*
*Purpose:
*       Collates two strings for lexical order.   Strings
*       are collated on a character basis, not a byte basis.
*
*Entry:
*       char *s1, *s2 = strings to collate
*
*Exit:
*       returns <0 if s1 < s2
*       returns  0 if s1 == s2
*       returns >0 if s1 > s2
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _mbscoll(
        const unsigned char *s1,
        const unsigned char *s2
        )
{
        int ret;
#ifdef _MT
        pthreadmbcinfo ptmbci = _getptd()->ptmbcinfo;

        if ( ptmbci != __ptmbcinfo )
            ptmbci = __updatetmbcinfo();

        if (0 == (ret = __crtCompareStringA( ptmbci->mblcid, 0, s1, -1, s2, -1,
                                             ptmbci->mbcodepage )))
#else  /* _MT */
        if (0 == (ret = __crtCompareStringA( __mblcid, 0, s1, -1, s2, -1,
                                             __mbcodepage )))
#endif  /* _MT */
            return _NLSCMPERROR;

        return ret - 2;

}

#endif  /* _MBCS */