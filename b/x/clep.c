/* mill/x/stig.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

/* _stig_book(): bake a book.
*/
static u4_noun
_stig_book(u4_milr m, u4_noun pir, u4_type tip)
{
  u4_lane lane = m->lane;

  if ( u4_n_cell(u4_ch(pir)) ) {
    return u4_k_cell(lane, _stig_book(m, u4_ch(pir), tip),
                           _stig_book(m, u4_ct(pir), tip));
  }
  else {
    return _mill_bake(m, u4_ct(pir), tip);
  }
}


/* _mill_x_stig()::
*/
u4_loaf
_mill_x_stig(u4_milr m, 
             u4_noun pir,
             u4_type tip)
{
  u4_lane lane = m->lane;
  u4_type gan  = u4_k_trel(lane, u4_atom_cone, tip, pir);
  u4_noun fez  = _stig_book(m, pir, gan);

  return u4_k_cell
    (lane, gan,
           u4_k_cell
            (lane, u4_k_cell(lane, u4_noun_0, u4_noun_1),
                   u4_k_cell(lane, u4_noun_1, fez)));
}
