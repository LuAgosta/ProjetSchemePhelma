
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"
int is_form (char* name, object input ) {

	if ( input-> type == SFS_PAIR && input -> this.pair.car -> type == SFS_SYMBOL && 0 == strcmp(name, input->this.pair.car ->this.symbol) ) {
		return 1 ; 
	}
	return 0 ; 
}

object sfs_eval( object input ) {
/**auto-evaluants**/ 
	if (input -> type != ( SFS_SYMBOL && SFS_PAIR ) ) {
		return input ; 
	}
	if (input -> type == SFS_PAIR && input -> this.pair.car -> type != ( SFS_SYMBOL && SFS_PAIR ) ) {
		return input -> this.pair.car ;
	}
	
/* quote */ 

		if ( is_form ( "quote" , input ) ) { 
			return cdar (input) ; 
		}

 
/** formes **/ 
	/* > < >= <= = */ 
	if ( is_form ("=", input ) ) {
		if ( sfs_eval(input->this.pair.cdr) == sfs_eval(cddr(input)) ) {
			return vrai ; 
		}
		return faux ; 
	}
	if ( is_form ("!=", input ) ) {
		if ( sfs_eval(input->this.pair.cdr) != sfs_eval(cddr(input)) ) {
			return vrai ; 
		}
		return faux ; 
	}
	if  (is_form ("<" , input )) { 
		if(sfs_eval(input-> this.pair.cdr) < sfs_eval(cddr (input))  ) {
			return vrai ; 
		}
		return faux ; 
	}
	if ( is_form (">", input ) ) {
		if ( sfs_eval(input->this.pair.cdr) > sfs_eval(cddr(input)) ) {
			return vrai ; 
		}
		return faux ; 
	}
	if ( is_form ("<=", input ) ) {
		if ( sfs_eval(input->this.pair.cdr) <= sfs_eval(cddr(input)) ) {
			return vrai ; 
		}
		return faux ; 
	}
	if ( is_form (">=", input ) ) {
		if ( sfs_eval(input->this.pair.cdr) >= sfs_eval(cddr(input)) ) {
			return vrai ; 
		}
		return faux ; 
	}
	/* if */
	if (is_form ("if", input ) ) {
		if ( vrai == eval ( input->this.pair.cdr ) ) { 



	 


    return input;
}
