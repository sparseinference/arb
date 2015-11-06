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

    Copyright (C) 2015 Fredrik Johansson

******************************************************************************/

#include "acb_hypgeom.h"

int main()
{
    slong iter;
    flint_rand_t state;

    printf("legendre_p....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 2000; iter++)
    {
        acb_t n, na, nb, m, z, res1, res2, res3, t, u;
        slong prec1, prec2, ebits;
        int type;

        acb_init(n);
        acb_init(na);
        acb_init(nb);
        acb_init(m);
        acb_init(z);
        acb_init(res1);
        acb_init(res2);
        acb_init(res3);
        acb_init(t);
        acb_init(u);

        prec1 = 2 + n_randint(state, 300);
        prec2 = 2 + n_randint(state, 300);
        ebits = 1 + n_randint(state, 10);

        if (n_randint(state, 2))
        {
            acb_set_si(m, n_randint(state, 20) - 10);
            acb_set_si(n, n_randint(state, 20) - 10);
        }
        else
        {
            acb_randtest_param(n, state, 1 + n_randint(state, 400), ebits);
            acb_randtest_param(m, state, 1 + n_randint(state, 400), ebits);
        }

        acb_randtest_param(z, state, 1 + n_randint(state, 400), ebits);

        acb_sub_ui(na, n, 1, prec2);
        acb_add_ui(nb, n, 1, prec2);

        type = n_randint(state, 2);

        acb_hypgeom_legendre_p(res1, n, m, z, type, prec1);
        acb_hypgeom_legendre_p(res2, na, m, z, type, prec2);
        acb_hypgeom_legendre_p(res3, nb, m, z, type, prec2);

        acb_add(t, n, m, prec2);
        acb_mul(t, t, res2, prec2);
        acb_sub(u, n, m, prec2);
        acb_add_ui(u, u, 1, prec2);
        acb_mul(u, u, res3, prec2);
        acb_add(t, t, u, prec2);

        acb_mul_2exp_si(u, n, 1);
        acb_add_ui(u, u, 1, prec2);
        acb_mul(u, u, z, prec2);
        acb_mul(u, u, res1, prec2);

        if (!acb_overlaps(t, u))
        {
            printf("FAIL: consistency\n\n");
            printf("iter = %ld, prec1 = %ld, prec2 = %ld\n\n", iter, prec1, prec2);
            printf("type = %d\n\n", type);
            printf("n = "); acb_printd(n, 30); printf("\n\n");
            printf("m = "); acb_printd(m, 30); printf("\n\n");
            printf("z = "); acb_printd(z, 30); printf("\n\n");
            printf("res1 = "); acb_printd(res1, 30); printf("\n\n");
            printf("res2 = "); acb_printd(res2, 30); printf("\n\n");
            printf("res3 = "); acb_printd(res3, 30); printf("\n\n");
            printf("t = "); acb_printd(t, 30); printf("\n\n");
            printf("u = "); acb_printd(u, 30); printf("\n\n");
            abort();
        }

        acb_clear(n);
        acb_clear(na);
        acb_clear(nb);
        acb_clear(m);
        acb_clear(z);
        acb_clear(res1);
        acb_clear(res2);
        acb_clear(res3);
        acb_clear(t);
        acb_clear(u);
    }

    flint_randclear(state);
    flint_cleanup();
    printf("PASS\n");
    return EXIT_SUCCESS;
}
