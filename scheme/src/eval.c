
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"
#include "prim.h"
/* Regarder la forme ou l'opérateur */
int is_form (char* name, object input ) {

	if ( input-> type == SFS_PAIR && input -> this.pair.car -> type == SFS_SYMBOL && 0 == strcmp(name, input->this.pair.car ->this.symbol) ) {
		return 1 ;
	}
	return 0 ;
}

object sfs_eval_list( object input){
	object output = input;
	object o;
	while (input->this.pair.cdr->type != SFS_NIL){
		o = sfs_eval(input->this.pair.car);
		if(o==NULL){
			return NULL;
		}
		input->this.pair.car = o;
		input = input->this.pair.cdr;
	}
	o = sfs_eval(input->this.pair.car);
	if(o==NULL){
		return NULL;
	}
	input->this.pair.car = o;
	return output;
}

object sfs_eval( object input ) {
	object output = NULL;
	object o = NULL;
	restart :
	/*auto-evaluants*/
	if ((input->type != SFS_SYMBOL) && (input->type != SFS_PAIR) && (input->type != SFS_NIL)) {
		return input ;
	}

	/*Pour faire un test évolué de set! et define (voir le README dans ../scheme/tests_step1/setdefenv)*/
	/*if(input->type == SFS_SYMBOL){
		if(strcmp(input->this.symbol,"addenv") == 0){
			addenv();
			INFO_MSG("Un nouvelle environnement a été créé");
		}
	}*/

	/*Existence de la variable dans un environnement ?*/
	if( input->type == SFS_SYMBOL ){
		/*if(strcmp(input->this.symbol,"addenv") != 0){*/
		if (lenv -> this.pair.car == nil){
			WARNING_MSG("Erreur, la variable %s n'est pas définie",input->this.symbol);
			return NULL;
		}
		else {
			object val = in_lenv(input);
			if(val == NULL){
				return NULL;
			}
			val = val->this.pair.cdr;
			if(val != NULL) { /* pour l'instant lenv = environnement courant*/
				return val;
			}
			else {
				return NULL;
			}
		}
	/*}*/
	}


	/** formes**/
	/* quote */
	if ( is_form ( "quote", input)){
		if(cddr(input) == nil){
			return cadr(input);
		}
		else{
			WARNING_MSG("Erreur, quote ne prend qu'un argument");
			return NULL;
		}
	}

	/*define*/
	if ( is_form("define",input)){
		output = cadr(input);
		if(cdddr(input) != nil){
			WARNING_MSG("Erreur, define prend deux arguments");
			return NULL;
		}
		if ( lenv-> this.pair.car == nil ) {
			o = sfs_eval(caddr(input));
			if(o == NULL){
				return NULL;
			}
			addvar(output,o);
			return output;
		}
		else {
			object val = in_envc(output);
			if (val == NULL ){
				o = sfs_eval(caddr(input));
				if(o == NULL){
					return NULL;
				}
				addvar(output,sfs_eval(caddr(input)));
				return output;
			}
			else {
				o = sfs_eval(caddr(input));
				if(o == NULL){
					return NULL;
				}
				else{
					WARNING_MSG("La variable %s est déjà définie, utilisez la forme set! pour modifier sa valeur.",cadr(input)->this.symbol);
					return NULL;
				}
			}
		}
	}

	/*set!*/
	if ( is_form("set!", input)){
		object o = NULL;
		object pairvar = NULL;
		if (lenv -> this.pair.car == nil){
			WARNING_MSG("Erreur, la variable %s n'est pas définie", cadr(input)->this.symbol);
			return nil;
		}
		else {
			pairvar = in_lenv(cadr(input));
			if(pairvar == NULL){
				return nil;
			}
			else {
				o = sfs_eval(caddr(input));
				if(o == NULL){
					return NULL;
				}
				else{
					*pairvar=*make_pair(cadr(input),o);
					return cadr(input) ;
				}
			}
		}
	}

	/* if */
	if (is_form ("if", input ) ) {
		if(input->this.pair.cdr->type == SFS_NIL || cddr(input)->type == SFS_NIL){
			WARNING_MSG("Erreur, la forme if doit être formulée suivant le schéma : (if predicat consequence alternative)");
			return NULL;
		}
		/*if(cdddr(input)->this.pair.cdr != nil){
			WARNING_MSG("Erreur, la forme if doit être formulée suivant le schéma : (if predicat consequence alternative)");
			return NULL;
		}*/
		if (faux == sfs_eval(cadr(input))) {
			input = cadddr(input) ;
			goto restart ;
		}
		else {
			input = caddr (input) ;
			goto restart ;
		}
	}

		/* or */
		if (is_form("or", input ) ) {
			if(input->this.pair.cdr->type == SFS_NIL ) {
				WARNING_MSG("Erreur, la forme or doit prendre minimum deux arguments");
				return NULL;
			}
			if(cddr(input)->type == SFS_NIL){
				WARNING_MSG("Erreur, la forme or doit prendre minimum deux arguments");
				return NULL;
			}
			while (input->this.pair.cdr != nil ) {
				input = input->this.pair.cdr ;
				if (sfs_eval(input->this.pair.car) == vrai ) {
					return vrai ;
				}

			}
			return faux ;
		}

		/* and */
		if (is_form ("and", input )) {
			if(input->this.pair.cdr->type == SFS_NIL ) {
				WARNING_MSG("Erreur, la forme and doit prendre minimum deux arguments");
				return NULL;
			}
			if(cddr(input)->type == SFS_NIL){
				WARNING_MSG("Erreur, la forme and doit prendre minimum deux arguments");
				return NULL;
			}
			while (input->this.pair.cdr != nil ) {
				input = input->this.pair.cdr ;
				if (sfs_eval(input->this.pair.car) == faux ){
					return faux ;
				}
			}
			return vrai;
		}

		/* begin */
		if (is_form ("begin" , input)) {
			if (input->this.pair.cdr == nil) {
				WARNING_MSG("Erreur, la forme begin doit prendre minimum un argument");
				return NULL;
			}
			object output = NULL ; 
			while (input->this.pair.cdr != nil) {
				input = input->this.pair.cdr ;
				output = input->this.pair.car ;
				if (sfs_eval(output) == NULL ) {
					return NULL ; 
				}
				else { 
					output = sfs_eval(output) ; 
				}
			}
			return output ; 
		}

/* pair invalide */
	if (input->type == SFS_PAIR ) {
		
		switch (input->this.pair.car->type ) {
		
		
			case SFS_NUMBER : 
				WARNING_MSG(" %ld n'est pas une fonction" , input->this.pair.car-> this.number.this.integer) ;
				return NULL ;

			case SFS_STRING :
				WARNING_MSG(" %s n'est pas un fonction" , input->this.pair.car-> this.string) ;
				return NULL ;

			case SFS_CHARACTER : 
				WARNING_MSG(" %c n'est pas une fonction" , input->this.pair.car-> this.character) ;
				return NULL ;
			
			case SFS_BOOLEAN : 
				if (input-> this.pair.car == vrai ) {
				WARNING_MSG(" #t n'est pas une fonction" ) ;
				return NULL ;
				}
				if (input-> this.pair.car == faux ) {
				WARNING_MSG(" #f n'est pas une fonction") ;
				return NULL ;
				}
			case SFS_NIL : 
				WARNING_MSG(" () n'est pas une fonction" ) ;
				return NULL ;		
		
				
		}
	}	
	/**primitives**/
	if(input->type == SFS_PAIR){
		if(input->this.pair.car->type == SFS_SYMBOL){
			object val = in_lenv(input->this.pair.car);
			if(val ==NULL){
				return NULL;
			}
			val = val->this.pair.cdr;
			if(val != NULL) {
				if(val->type == SFS_PRIMITIVE){
					o = sfs_eval_list(input->this.pair.cdr);
					if(o==NULL){
						return NULL;
					}
					return((val->this.primitive)(o));
				}
				else {
					WARNING_MSG(" %s n'est pas une fonction" , input->this.pair.car-> this.symbol) ;
					return NULL ;
				}
			}
		}
		return NULL;
	}

  return input;
}
