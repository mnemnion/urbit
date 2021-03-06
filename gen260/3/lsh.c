/* j/3/lsh.c
**
** This file is in the public domain.
*/
#include "all.h"
#include "../pit.h"

/* functions
*/
  u2_weak                                                         //  transfer
  j2_mbc(Pt3, lsh)(u2_wire wir_r, 
                   u2_atom a,                                     //  retain
                   u2_atom b,                                     //  retain
                   u2_atom c)                                     //  retain
  {
    if ( !u2_fly_is_cat(a) || (a >= 32) ) {
      return u2_none;
    }
    else if ( !u2_fly_is_cat(b) ) {
      return u2_none;
    }
    else {
      c3_g a_g   = a;
      c3_w b_w   = b;
      c3_w len_w = u2_met(a_g, c);

      if ( _0 == len_w ) {
        return _0;
      } 
      else if ( (b_w + len_w) < len_w ) {
        return u2_none;
      }
      else {
        u2_ray sal_r = u2_rl_slaq(wir_r, a_g, (b_w + len_w));

        if ( 0 == sal_r ) {
          return u2_none;
        }
        u2_chop(a_g, 0, len_w, b_w, sal_r, c);

        return u2_rl_moot(wir_r, sal_r);
      }
    }
  }
  u2_weak                                                         //  transfer
  j2_mb(Pt3, lsh)(u2_wire wir_r, 
                  u2_noun cor)                                    //  retain
  {
    u2_noun a, b, c;

    if ( (u2_no == u2_mean(cor, u2_cv_sam_2, &a, 
                                u2_cv_sam_6, &b, 
                                u2_cv_sam_7, &c, 0)) ||
         (u2_no == u2_stud(a)) ||
         (u2_no == u2_stud(b)) ||
         (u2_no == u2_stud(c)) )
    {
      return u2_none;
    } else {
      return j2_mbc(Pt3, lsh)(wir_r, a, b, c);
    }
  }

/* structures
*/
  u2_ho_jet 
  j2_mbj(Pt3, lsh)[] = {
    { ".3", c3__lite, j2_mb(Pt3, lsh), Tier3, u2_none, u2_none },
    { }
  };
