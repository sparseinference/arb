/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2013 Fredrik Johansson

******************************************************************************/

#include "fmpcb_poly.h"

void
fmpcb_poly_set_coeff_si(fmpcb_poly_t poly, long n, long x)
{
    fmpcb_poly_fit_length(poly, n + 1);

    if (n + 1 > poly->length)
    {
        _fmpcb_vec_zero(poly->coeffs + poly->length, n - poly->length);
        poly->length = n + 1;
    }

    fmpcb_set_si(poly->coeffs + n, x);
    _fmpcb_poly_normalise(poly);
}
