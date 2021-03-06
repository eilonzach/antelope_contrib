/* @(#)null_sac.h	1.2 12/28/93 */
/*======================================================================
 *
 *  include/null_sac.h
 *
 *  Define a null SAC header
 *
 *====================================================================*/
#ifndef null_sac_h_included
#define null_sac_h_included

#include "sacio.h"

static struct sac_header null_sac_header = {
-12345., -12345., -12345., -12345., -12345.,
-12345., -12345., -12345., -12345., -12345.,
-12345., -12345., -12345., -12345., -12345.,
-12345., -12345., -12345., -12345., -12345.,
-12345., -12345., -12345., -12345., -12345.,
-12345., -12345., -12345., -12345., -12345.,
-12345., -12345., -12345., -12345., -12345.,
-12345., -12345., -12345., -12345., -12345.,
-12345., -12345., -12345., -12345., -12345.,
-12345., -12345., -12345., -12345., -12345.,
-12345., -12345., -12345., -12345., -12345.,
-12345., -12345., -12345., -12345., -12345.,
-12345., -12345., -12345., -12345., -12345.,
-12345., -12345., -12345., -12345., -12345.,
-12345, -12345, -12345, -12345, -12345,
-12345, -12345, -12345, -12345, -12345,
-12345, -12345, -12345, -12345, -12345,
-12345, -12345, -12345, -12345, -12345,
-12345, -12345, -12345, -12345, -12345,
-12345, -12345, -12345, -12345, -12345,
-12345, -12345, -12345, -12345, -12345,
-12345, -12345, -12345, -12345, -12345,
{ '-','1','2','3','4','5',' ',' ' },
{ '-','1','2','3','4','5',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' },
{ '-','1','2','3','4','5',' ',' ' },{ '-','1','2','3','4','5',' ',' ' },
{ '-','1','2','3','4','5',' ',' ' },{ '-','1','2','3','4','5',' ',' ' },
{ '-','1','2','3','4','5',' ',' ' },{ '-','1','2','3','4','5',' ',' ' },
{ '-','1','2','3','4','5',' ',' ' },{ '-','1','2','3','4','5',' ',' ' },
{ '-','1','2','3','4','5',' ',' ' },{ '-','1','2','3','4','5',' ',' ' },
{ '-','1','2','3','4','5',' ',' ' },{ '-','1','2','3','4','5',' ',' ' },
{ '-','1','2','3','4','5',' ',' ' },{ '-','1','2','3','4','5',' ',' ' },
{ '-','1','2','3','4','5',' ',' ' },{ '-','1','2','3','4','5',' ',' ' },
{ '-','1','2','3','4','5',' ',' ' },{ '-','1','2','3','4','5',' ',' ' },
{ '-','1','2','3','4','5',' ',' ' },{ '-','1','2','3','4','5',' ',' ' },
{ '-','1','2','3','4','5',' ',' ' }
};

#endif
