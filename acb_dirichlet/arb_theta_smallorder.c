/*
    Copyright (C) 2016 Pascal Molin

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "acb_dirichlet.h"
#include "acb_poly.h"

/* small order, multiply by chi at the end */
void
acb_dirichlet_arb_theta_smallorder(acb_t res, const arb_t x, int parity, const ulong *a, const acb_dirichlet_powers_t z, slong len, slong prec)
{
    slong k;
    ulong order = z->order;
    arb_t xk2, kxk2, dx, x2;
    acb_ptr t;
    arb_init(xk2);
    arb_init(dx);
    arb_init(x2);
    arb_init(kxk2);

    arb_set(dx, x);
    arb_set(xk2, x);
    arb_mul(x2, x, x, prec);

    t = _acb_vec_init(order);
    _acb_vec_zero(t, order);

    arb_set(acb_realref(t + 0), xk2);

    /* TODO: reduce precision at each step */
    for (k = 2; k < len; k++)
    {
        arb_mul(dx, dx, x2, prec);
        arb_mul(xk2, xk2, dx, prec);
        if (a[k] != ACB_DIRICHLET_CHI_NULL)
        {
           if (parity)
           {
               arb_mul_si(kxk2, xk2, k, prec);
               arb_add(acb_realref(t + a[k]), acb_realref(t + a[k]), kxk2, prec);
           }
           else
           {
               arb_add(acb_realref(t + a[k]), acb_realref(t + a[k]), xk2, prec);
           }
        }
    }

    /* now Hörner */
    _acb_poly_evaluate(res, t, order, z->z, prec);

    _acb_vec_clear(t, order);
    arb_clear(xk2);
    arb_clear(x2);
    arb_clear(dx);
}