/* Macros to control TS 18661-3 glibc features on powerpc.
   Copyright (C) 2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _BITS_FLOATN_H
#define _BITS_FLOATN_H

#include <features.h>

/* Defined to 1 if the current compiler invocation provides a
   floating-point type with the IEEE 754 binary128 format, and this glibc
   includes corresponding *f128 interfaces for it.  */
#if defined _ARCH_PWR8 && defined __LITTLE_ENDIAN__ && (_CALL_ELF == 2) \
    && defined __FLOAT128__
# define __HAVE_FLOAT128 1
#else
# define __HAVE_FLOAT128 0
#endif

/* Defined to 1 if __HAVE_FLOAT128 is 1 and the type is ABI-distinct
   from the default float, double and long double types in this glibc.  */
#if __HAVE_FLOAT128
# define __HAVE_DISTINCT_FLOAT128 1
#else
# define __HAVE_DISTINCT_FLOAT128 0
#endif

/* Defined to concatenate the literal suffix to be used with _Float128
   types, if __HAVE_FLOAT128 is 1. */
#if __HAVE_FLOAT128
# if !__GNUC_PREREQ (7, 0) || defined __cplusplus
/* The literal suffix (f128) exist for powerpc only since GCC 7.0.  */
#  define __f128(x) x##q
# else
#  define __f128(x) x##f128
# endif
#endif

/* Defined to a complex binary128 type if __HAVE_FLOAT128 is 1.  */
#if __HAVE_FLOAT128
# if !__GNUC_PREREQ (7, 0) || defined __cplusplus
/* Add a typedef for older GCC compilers which don't natively support
   _Complex _Float128.  */
typedef _Complex float __cfloat128 __attribute__ ((__mode__ (__KC__)));
#  define __CFLOAT128 __cfloat128
# else
#  define __CFLOAT128 _Complex _Float128
# endif
#endif

/* The remaining of this file provides support for older compilers.  */
#if __HAVE_FLOAT128

/* The type _Float128 exist for powerpc only since GCC 7.0.  */
# if !__GNUC_PREREQ (7, 0) || defined __cplusplus
typedef __float128 _Float128;
# endif

/* Builtin __builtin_huge_valf128 doesn't exist before GCC 7.0.  */
# if !__GNUC_PREREQ (7, 0)
#  define __builtin_huge_valf128() ((_Float128) __builtin_huge_val ())
# endif

/* The following builtins (suffixed with 'q') are available in GCC >= 6.2,
   which is the minimum version required for float128 support on powerpc64le.
   Since GCC 7.0 the builtins suffixed with f128 are also available, then
   there is no need to redefined them.  */
# if !__GNUC_PREREQ (7, 0)
#  define __builtin_copysignf128 __builtin_copysignq
#  define __builtin_fabsf128 __builtin_fabsq
#  define __builtin_inff128 __builtin_infq
#  define __builtin_nanf128 __builtin_nanq
#  define __builtin_nansf128 __builtin_nansq
# endif

#endif

#endif /* _BITS_FLOATN_H */