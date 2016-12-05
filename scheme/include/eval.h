
/**
 * @file eval.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:10:38 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#ifndef _EVAL_H_
#define _EVAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"
#include "env.h"
  
int is_form (char* , object ) ;

object sfs_eval( object );
object sfs_eval_list( object input);

#ifdef __cplusplus
}
#endif

#endif /* _EVAL_H_ */
