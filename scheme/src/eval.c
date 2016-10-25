
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"

/* Regarder la forme ou primitive utilisée */
int is_form (char* name, object input ) {

	if ( input-> type == SFS_PAIR && input -> this.pair.car -> type == SFS_SYMBOL && 0 == strcmp(name, input->this.pair.car ->this.symbol) ) {
		return 1 ; 
	}
	return 0 ; 
}
/* Regarder si le premier éléments n'est une forme */
int isnot_form ( object input){
	if (input->type == SFS_PAIR && input -> this.pair.car -> type != SFS_SYMBOL) {
		return 1 ;
	}
	return 0; 
}

/*Regarder si le premier éléments est une fonction*/		
int is_fonction(object input) {
	if (input->type == SFS_PAIR && input->this.pair.car ->type == SFS_SYMBOL ){
		return 1 ;
	}
	else {
		return 0 ;
	}
}


object sfs_eval( object input ) {
	object output = NULL;
	object o = NULL;
	object o1 = NULL ; 
	long n;
	restart :
	/*auto-evaluants*/ 
	if ((input->type != SFS_SYMBOL) && (input->type != SFS_PAIR) && (input->type != SFS_NIL)) {
		return input ; 
	}
	

	/*Existence de la variable dans un environnement ?*/
	if( input->type == SFS_SYMBOL ){ 
		if (lenv -> this.pair.car == nil){
			WARNING_MSG("Variable non existante");
			return NULL; 
		}
		else {	
			object val = in_lenv(input);
			if(val != NULL) { /* pour l'instant lenv = environnement courant*/  
				return val;
			}	
			else {
				WARNING_MSG("Variable non existante");
				return NULL; 
			}
		}

	}
	
	/** formes et primitives **/ 
	/* quote */ 
	if ( is_form ( "quote", input)){
		if(cddr(input) == nil){
			return cadr(input);
		}
		else{
			WARNING_MSG("quote ne prend qu'un argument");
			return NULL;
		}
	}
	
	/*define*/
	if ( is_form("define",input)){
		output = cadr(input);
		if(cdddr(input) != nil){
			WARNING_MSG("Erreur, define prend au plus deux arguments");
			return NULL;
		}
		if ( lenv-> this.pair.car == nil ) {
			addvar(output,sfs_eval(caddr(input)));
			return output;
		}
		else {
			object val = in_envc(output);
			if (val == NULL ){
				addvar(output,sfs_eval(caddr(input)));
				return output;
			}
			else {
				o = sfs_eval(caddr(input));
				if(o == NULL){
					return NULL;
				}
				else{
					modify_object (val, o) ;
					return output ;
				}
			}
		}
	}
	
	/*set!*/
	if ( is_form("set!", input)){
		if (lenv -> this.pair.car == nil){
			WARNING_MSG("Variable %s non définie", cadr(input)->this.symbol);
			return nil;
		}
		else {
			object val = in_lenv(cadr(input));
			if(val == NULL){
				WARNING_MSG("Variable %s non définie", cadr(input)->this.symbol);
				return nil;
			}
			else {
				o = sfs_eval(caddr(input));
				if(o == NULL){
					return NULL;
				}
				else{
					modify_object (val, o) ;
					return cadr(input) ;
				}
			}
		}
	}
	
	/* if */
	if (is_form ("if", input ) ) {
		if(cdddr(input)->this.pair.cdr != nil){
			WARNING_MSG("Erreur, la forme if doit être formulée suivant le schéma : (if predicat consequence alternative)");
			return NULL;
		}
		if (faux == sfs_eval(cadr(input))) {
			input = cadddr(input) ; 
			goto restart ; 
		}
		else {
			input = caddr (input) ;
			goto restart ;
		}
	}
	
	/*Opérations + - * / */
	if ( is_form ("+", input ) || is_form ("-", input ) || is_form ("*", input ) || is_form ("/", input )){
		if((sfs_eval(cadr(input))->type == SFS_NUMBER) && (sfs_eval(caddr(input))->type == SFS_NUMBER)){
			if(cdddr(input)->type != SFS_NIL){
				WARNING_MSG("L'opération %s ne prend que deux arguments", input->this.pair.car ->this.symbol);
				return NULL;
			}
			if ( is_form ("+", input )){
				n =  sfs_eval(cadr(input))->this.number.this.integer + sfs_eval(caddr(input))->this.number.this.integer;
				output = make_integer(n);
				return(output);
			}
			if ( is_form ("-", input )){
				n =  sfs_eval(cadr(input))->this.number.this.integer - sfs_eval(caddr(input))->this.number.this.integer;
				output = make_integer(n);
				return(output);
			}
			if ( is_form ("*", input )){
				n =  sfs_eval(cadr(input))->this.number.this.integer * sfs_eval(caddr(input))->this.number.this.integer;
				output = make_integer(n);
				return(output);
			}
			if ( is_form ("/", input )){
				if(sfs_eval(caddr(input))->this.number.this.integer != 0){
					if(sfs_eval(cadr(input))->this.number.this.integer % sfs_eval(caddr(input))->this.number.this.integer == 0){
						n =  sfs_eval(cadr(input))->this.number.this.integer / sfs_eval(caddr(input))->this.number.this.integer;
						output = make_integer(n);
						return(output);
					}
					else{
						WARNING_MSG("Attention, pour l'instant notre interpréteur ne gère pas les nombres réels (nombres en virgule flottante)");
					}
				}
				else{
					WARNING_MSG("Attention, la division par 0 est impossible");
				}
			}
		}
		else{
			if(caddr(input)->type == SFS_NIL){
				WARNING_MSG("Erreur, l'opérateur %s doit prendre deux arguements", input->this.pair.car ->this.symbol);
				return NULL;
			}
			WARNING_MSG("Attention, cette opération s'applique uniquement à des nombres");
			return NULL;
		}
	}

	/* > < >= <= = */
	if(is_form ("=", input ) || is_form ("!=", input ) || is_form ("<", input ) || is_form (">", input ) || is_form ("<=", input ) || is_form (">=", input )){
		if(cddr(input)->type == SFS_NIL){
			WARNING_MSG("Erreur, l'opérateur de comparaison %s doit prendre deux arguments", input->this.pair.car ->this.symbol);
			return NULL;
		}
		if(cdddr(input)->type != SFS_NIL){
			WARNING_MSG("Erreur, l'opérateur de comparaison %s ne prend que deux arguments", input->this.pair.car ->this.symbol);
			return NULL;
		}
		o = sfs_eval(cadr(input));
		o1 = sfs_eval(caddr(input));
		if(o == NULL || o1 == NULL){
			return NULL;
		}
		else{
			if ( is_form ("=", input ) ) {
				if ( o->this.number.this.integer == o1->this.number.this.integer ) {
					return vrai ;
				}
				return faux ;
			}
			if ( is_form ("!=", input ) ) {
				if ( o->this.number.this.integer != o1->this.number.this.integer ) {
					return vrai ;
				}
				return faux ;
			}
			if  (is_form ("<" , input )) {
				if(o->this.number.this.integer < o1->this.number.this.integer  ) {
					return vrai ;
				}
				return faux ;
			}
			if ( is_form (">", input ) ) {
				if ( o->this.number.this.integer > o1->this.number.this.integer ) {
					return vrai ;
				}
				return faux ;
			}
			if ( is_form ("<=", input ) ) {
				if ( o->this.number.this.integer <= o1->this.number.this.integer ) {
					return vrai ;
				}
				return faux ;
			}
			if ( is_form (">=", input ) ) {
				if ( o->this.number.this.integer >= o1->this.number.this.integer ) {
					return vrai ;
				}
				return faux ;
			}
		}
	}
	
	/* or */
	if (is_form("or", input ) ) {
		if(cddr(input)->type == SFS_NIL){
			WARNING_MSG("Erreur, la forme or doit prendre deux arguments");
			return NULL;
		}
		if(cdddr(input)->type != SFS_NIL){
			WARNING_MSG("Erreur, la forme or ne prend que deux arguments");
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
		if(cddr(input)->type == SFS_NIL){
			WARNING_MSG("Erreur, la forme and doit prendre deux arguments");
			return NULL;
		}
		if(cdddr(input)->type != SFS_NIL){
			WARNING_MSG("Erreur, la forme and ne prend que deux arguments");
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
	
	/* pair invalide */
	
	
	if (isnot_form(input)) {
		WARNING_MSG("Erreur, l'expression est invalide"); 
		return NULL;
	}
	
	/* fonction invalide */ 
	
	if (is_fonction(input)) {
		if (lenv -> this.pair.car == nil){
			WARNING_MSG("La fonction %s n'est pas définie" , input->this.pair.car-> this.symbol) ; 
			return NULL ;
		}
		else {
			object val = in_lenv(input->this.pair.car) ; 
			if (val == NULL) {
				WARNING_MSG("La fonction %s n'est pas définie" , input->this.pair.car-> this.symbol) ; 
				return NULL ;
			}
		}
			
	}
	 


    return input;
}
