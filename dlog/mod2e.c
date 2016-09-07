/*
    Copyright (C) 2016 Pascal Molin

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "dlog.h"

ulong
dlog_mod2e(const dlog_modpe_t t, ulong b1)
{
    if (t->e == 2)
        return (b1 % 4) == 3;
    else
    {
        slong f;
        ulong pf1, pf, x, xf;
        pf1 = 1;
        pf = 4;
        x = 0;
        for (f = 2; f < t->e; f++)
        {
            if (b1 % pf != 1)
            {
                flint_printf("ERROR dlog_mod2e: %wu %% %wu != 1 mod %wu\n\n",
                        b1, pf, t->pe.n);
                abort();
            }
            xf = (b1 - 1) / pf;
            xf = (f == 2) ? xf % 4 : (xf % 2) * (pf1 / 2);
            b1 = nmod_mul(b1, nmod_pow_ui(t->inva, xf, t->pe), t->pe);
            x += xf;
            pf1 = pf;
            pf *= 2;
        }
        return x;
    }
}