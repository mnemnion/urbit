/* j/2/slag.c
**
** This file is in the public domain.
*/
#include "all.h"
#include "../pit.h"

/* functions
*/
  u2_weak                                                         //  transfer
  j2_mbc(Pit, slag)(u2_wire wir_r, 
                    u2_atom a,                                    //  retain
                    u2_noun b)                                    //  retain
  {
    if ( !u2_fly_is_cat(a) ) {
      return u2_none;
    }
    else {
      c3_w len_w = a;

      while ( len_w ) {
        if ( u2_no == u2_dust(a) ) {
          return u2_none;
        }
        a = u2_t(a);
        len_w--;
      }
      if ( u2_no == u2_dust(a) ) {
        return u2_none;
      }
      return u2_rx(wir_r, u2_t(a));
    }
  }
  u2_noun                                                         // transfer
  j2_mb(Pit, slag)(u2_wire wir_r, 
                   u2_noun cor)                                   // retain
  {
    u2_noun a, b;

    if ( (u2_no == u2_mean(cor, 8, &a, 9, &b, 0)) || 
         (u2_no == u2_stud(a)) ) 
    {
      return u2_none;
    } else {
      return j2_mbc(Pit, slag)(wir_r, a, b);
    }
  }

/* structures
*/
  u2_ho_jet 
  j2_mbj(Pit, slag)[] = {
    { ".3", c3__lite, j2_mb(Pit, slag), Tier2, u2_none, u2_none },
    { }
  };
