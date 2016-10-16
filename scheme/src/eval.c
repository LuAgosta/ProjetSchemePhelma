
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
	if ((input->type != SFS_SYMBOL) && (input->type != SFS_PAIR) && (input->type != SFS_NIL)) {
		return input ; 
	}

	
 
/** formes **/ 
	/* quote */ 

		if ( is_form ( "quote" , input ) ) { 
			return cdar (input) ; 
		}
	/* > < >= <= = */ 
	if ( is_form ("=", input ) ) {
		if ( sfs_eval(cadr(input)) == sfs_eval(caddr(input)) ) {
			return vrai ; 
		}
		return faux ; 
	}
	if ( is_form ("!=", input ) ) {
		if ( sfs_eval(cadr(input)) != sfs_eval(caddr(input)) ) {
			return vrai ; 
		}
		return faux ; 
	}
	if  (is_form ("<" , input )) { 
		if(sfs_eval(cadr(input)) < sfs_eval(caddr (input))  ) {
			return vrai ; 
		}
		return faux ; 
	}
	if ( is_form (">", input ) ) {
		if ( sfs_eval(cadr(input)) > sfs_eval(caddr(input)) ) {
			return vrai ; 
		}
		return faux ; 
	}
	if ( is_form ("<=", input ) ) {
		if ( sfs_eval(cadr(input)) <= sfs_eval(caddr(input)) ) {
			return vrai ; 
		}
		return faux ; 
	}
	if ( is_form (">=", input ) ) {
		if ( sfs_eval(cadr(input)) >= sfs_eval(caddr(input)) ) {
			return vrai ; 
		}
	
	/* if */
	if (is_form ("if", input ) ) {
		if ( vrai == eval ( input->this.pair.cdr ) ) { 
		}



	 


    return input;
}
