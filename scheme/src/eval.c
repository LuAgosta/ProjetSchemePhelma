
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

/*Ajouter une variable et sa valeur dans l'environnement courant*/
void addvar(object var, object val){
	object o = lenv->this.pair.car;
	lenv->this.pair.car = make_pair(make_pair(var,val),o);
}

/*Recherche d'une variable dans environnements*/
object in_lenv(object var){
	object k = lenv;
	object l;
	while(k->this.pair.cdr != nil){
		l = k->this.pair.car;
		while(l->this.pair.cdr != nil){
			if(strcmp(caar(l)->this.string,var->this.string)==0){
				return(cdar(l));
			}
			l = l->this.pair.cdr;
		}
		if(strcmp(caar(l)->this.string,var->this.string)==0){
			return(cdar(l));
		}
		k=k->this.pair.cdr;
	}
	l = k->this.pair.car;
	while(l->this.pair.cdr != nil){
		if(strcmp(caar(l)->this.string,var->this.string)==0){
			return(cdar(l));
		}
		l = l->this.pair.cdr;
	}
	if(strcmp(caar(l)->this.string,var->this.string)==0){
		return(cdar(l));
	}
	return nil;		/*il faut afficher un msg d'erreur du type Unbound Variable*/
}


object sfs_eval( object input ) {
	restart : 
/**auto-evaluants**/ 
	if ((input->type != SFS_SYMBOL) && (input->type != SFS_PAIR) && (input->type != SFS_NIL)) {
		return input ; 
	}

	/*Existence de la variable dans un environnement ?*/
	if(input->type == SFS_SYMBOL){
		object val = in_lenv(input);
		if(val != nil) {
			return val;
		}
	/*else afficher message d'erreur !!!*/
	}
	
	/** formes **/ 
	/* quote */ 
	if ( is_form ( "quote" , input ) ) { 
		return cadr (input) ; 
	}
	
	/*define*/
	if ( is_form("define",input)){
		output = cadr(input);
		addvar(output,sfs_eval(caddr(input)));
		return output;
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
		return faux ; 
	}

	/* if */
	if (is_form ("if", input ) ) {
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
		while (input->this.pair.cdr != nil ) {
			input = input->this.pair.cdr ;
			if (sfs_eval(input->this.pair.car) == faux ){
				return faux ;
			}	
		}
		return vrai; 
	}
	
	 


    return input;
}
