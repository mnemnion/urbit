/* j/3/mug.c
**
** This file is in the public domain.
*/
#include "all.h"
#include "../pit.h"

/* functions
*/
  u2_weak                                                         //  transfer
  j2_mb(Pt3, mug)(u2_wire wir_r, 
                  u2_noun cor)                                    //  retain
  {
    u2_noun sam;

    if ( u2_none == (sam = u2_frag(u2_cw_sam, cor)) ) {
      return u2_none;
    } else {
      return u2_mug(sam);
    }
  }

/* structures
*/
  u2_ho_jet 
  j2_mbj(Pt3, mug)[] = { 
    { ".3", c3__lite, j2_mb(Pt3, mug), Tier3, u2_none, u2_none },
    { }
  };
