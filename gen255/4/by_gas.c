/* j/4/gas.c
**
** This file is in the public domain.
*/
#include "all.h"
#include "../pit.h"

/* functions
*/
  u2_weak                                                         //  transfer
  j2_mcc(Pt4, by, gas)(u2_wire wir_r, 
                       u2_noun a,                                 //  retain
                       u2_noun b)                                 //  retain
  {
    if ( u2_nul == b ) {
      return u2_rx(wir_r, a);
    }
    else {
      if ( u2_no == u2_dust(b) ) {
        return u2_none;
      } else {
        u2_noun i_b = u2_h(b);
        u2_noun t_b = u2_t(b);

        if ( u2_no == u2_dust(i_b) ) {
          return u2_none;
        } else {
          u2_noun pi_b = u2_h(i_b);
          u2_noun qi_b = u2_t(i_b);
          u2_noun c;

          if ( u2_none == (c = j2_mcc(Pt4, by, put)(wir_r, a, pi_b, qi_b)) ) {
            return u2_none;
          } else {
            u2_noun d = j2_mcc(Pt4, by, gas)(wir_r, c, t_b);

            u2_rl_lose(wir_r, c);
            return d;
          }
        }
      }
    }
  }
  u2_weak                                                         //  transfer
  j2_mc(Pt4, by, gas)(u2_wire wir_r, 
                      u2_noun cor)                                //  retain
  {
    u2_noun a, b;

    if ( u2_no == u2_mean(cor, u2_cw_con_sam, &a, u2_cw_sam, &b, 0) ) {
      return u2_none;
    } else {
      return j2_mcc(Pt4, by, gas)(wir_r, a, b);
    }
  }

/* structures
*/
  u2_ho_jet 
  j2_mcj(Pt4, by, gas)[] = {
    { ".3", c3__lite, j2_mc(Pt4, by, gas), Tier4, u2_none, u2_none },
    { }
  };
