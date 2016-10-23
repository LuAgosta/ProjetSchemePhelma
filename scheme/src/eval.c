
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

/*Modifier un object*/
void modify_object(object tomod, object mod) {

	tomod -> type = mod -> type ; 
	tomod -> this = mod -> this ;  

}

object sfs_eval( object input ) {
	object output = NULL;
	long n;
	restart :
	/*auto-evaluants*/ 
	if ((input->type != SFS_SYMBOL) && (input->type != SFS_PAIR) && (input->type != SFS_NIL)) {
		return input ; 
	}

	/*Existence de la variable dans un environnement ?*/
	if( input->type == SFS_SYMBOL ){ 
		if (lenv -> this.pair.car == nil){
			WARNING_MSG("Variable non trouvée");
			return NULL; 
		}
		else {	
			object val = in_lenv(input);
			if(val != nil) { /* pour l'instant lenv = environnement courant*/  
				return val;
			}	
			else {
				WARNING_MSG("Variable non trouvée");
				return NULL; 
			}
		}

	}
	
	/** formes et primitives **/ 
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
	
	/*set!*/
	if ( is_form("set!", input)){ 
		
		modify_object (in_lenv(cadr(input)), caddr(input)) ; 
		return cadr(input) ; 
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
	
	/*Opérations + - * / */
	if ( is_form ("+", input ) || is_form ("-", input ) || is_form ("*", input ) || is_form ("/", input )){
		if((sfs_eval(cadr(input))->type == SFS_NUMBER) && (sfs_eval(caddr(input))->type == SFS_NUMBER)){
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
			WARNING_MSG("Attention, cette opération s'applique uniquement à des nombres");
		}
	}
	
	/* > < >= <= = */ 
	if ( is_form ("=", input ) ) {
		if ( sfs_eval(cadr(input))->this.number.this.integer == sfs_eval(caddr (input))->this.number.this.integer ) {
			return vrai ; 
		}
		return faux ; 
	}

	if ( is_form ("!=", input ) ) {
		if ( sfs_eval(cadr(input))->this.number.this.integer != sfs_eval(caddr (input))->this.number.this.integer ) {
			return vrai ; 
		}
		return faux ; 
	}

	if  (is_form ("<" , input )) { 
		if(sfs_eval(cadr(input))->this.number.this.integer < sfs_eval(caddr (input))->this.number.this.integer ) {
			return vrai ; 
		}
		return faux ; 
	}

	if ( is_form (">", input ) ) {
		if ( sfs_eval(cadr(input))->this.number.this.integer > sfs_eval(caddr (input))->this.number.this.integer ) {
			return vrai ; 
		}
		return faux ; 
	}

	if ( is_form ("<=", input ) ) {
		if ( sfs_eval(cadr(input))->this.number.this.integer <= sfs_eval(caddr (input))->this.number.this.integer ) {
			return vrai ; 
		}
		return faux ; 
	}

	if ( is_form (">=", input ) ) {
		if (sfs_eval(cadr(input))->this.number.this.integer >= sfs_eval(caddr (input))->this.number.this.integer ) {
			return vrai ; 
		}
		return faux ; 
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
