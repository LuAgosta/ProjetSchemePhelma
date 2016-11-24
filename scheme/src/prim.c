/**
 * @file prim.c
 * @author Agosta Lucie and Noé Paul-Gauthier>
 * @date Sat Nov 12 17:44:05 2016
 */

#include <stdio.h>
#include "prim.h"
#include "eval.h"


/*Prédicats*/

object ifnull(object o){
	if(o->type == SFS_NIL){
		WARNING_MSG("null? admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("null? admet qu'un argument");
		return NULL;
	}
	if(sfs_eval(o->this.pair.car) == NULL){
		return NULL;
	}
	if(sfs_eval(o->this.pair.car)->type == SFS_NIL){
		return vrai;
	}
	return faux;
}


object ifboolean(object o){
	if(o->type == SFS_NIL){
		WARNING_MSG("boolean? admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("boolean? admet qu'un argument");
		return NULL;
	}
	if(sfs_eval(o->this.pair.car) == NULL){
		return NULL;
	}
	if(sfs_eval(o->this.pair.car)->type == SFS_BOOLEAN){
		return vrai;
	}
	return faux;
}


object ifsymbol(object o){
	if(o->type == SFS_NIL){
		WARNING_MSG("symbol? admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("symbol? admet qu'un argument");
		return NULL;
	}
	if(sfs_eval(o->this.pair.car) == NULL){
		return NULL;
	}
	if(sfs_eval(o->this.pair.car)->type == SFS_SYMBOL){
		return vrai;
	}
	return faux;
}


object ifinteger(object o){
	if(o->type == SFS_NIL){
		WARNING_MSG("integer? admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("integer? admet qu'un argument");
		return NULL;
	}
	if(sfs_eval(o->this.pair.car) == NULL){
		return NULL;
	}
	if(sfs_eval(o->this.pair.car)->type == SFS_NUMBER){
		return vrai;
	}
	return faux;
}


object ifchar(object o){
	if(o->type == SFS_NIL){
		WARNING_MSG("char? admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("char? admet qu'un argument");
		return NULL;
	}
	if(sfs_eval(o->this.pair.car) == NULL){
		return NULL;
	}
	if(sfs_eval(o->this.pair.car)->type == SFS_CHARACTER){
		return vrai;
	}
	return faux;
}


object ifstring(object o){
	if(o->type == SFS_NIL){
		WARNING_MSG("string? admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("string? admet qu'un argument");
		return NULL;
	}
	if(sfs_eval(o->this.pair.car) == NULL){
		return NULL;
	}
	if(sfs_eval(o->this.pair.car)->type == SFS_STRING){
		return vrai;
	}
	return faux;
}


object ifpair(object o){
	if(o->type == SFS_NIL){
		WARNING_MSG("pair? admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("pair? admet qu'un argument");
		return NULL;
	}
	if(sfs_eval(o->this.pair.car) == NULL){
		return NULL;
	}
	if(sfs_eval(o->this.pair.car)->type == SFS_PAIR){
		return vrai;
	}
	return faux;
}

/*Conversions de types*/

object chartointeger(object o){
	object n = NULL;
	if(o->type == SFS_NIL){
		WARNING_MSG("char->integer admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("pair? admet qu'un argument");
		return NULL;
	}
	n=sfs_eval(o->this.pair.car);
	if(n==NULL){
		return NULL;
	}
	if(n->type != SFS_CHARACTER){
		WARNING_MSG("L'argument doit être un caractère");
		return NULL;
	}
	n = make_integer((long) n->this.character);
	return n;
}


object integertochar(object o){
	object c = NULL;
	if(o->type == SFS_NIL){
		WARNING_MSG("integer->char admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("integer->char admet qu'un argument");
		return NULL;
	}
	c=sfs_eval(o->this.pair.car);
	if(c==NULL){
		return NULL;
	}
	if(c->type != SFS_NUMBER){
		WARNING_MSG("L'argument doit être un entier");
		return NULL;
	}
	c = make_char((char) c->this.number.this.integer);
	return c;
}


object numbertostring(object o){
	char str[BIGSTRING];
	object s = NULL;
	if(o->type == SFS_NIL){
		WARNING_MSG("number->string admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("number->string admet qu'un argument");
		return NULL;
	}
	s=sfs_eval(o->this.pair.car);
	if(s==NULL){
		return NULL;
	}
	if(s->type != SFS_NUMBER){
		WARNING_MSG("L'argument doit être un entier");
		return NULL;
	}
	sprintf(str, "%ld", s->this.number.this.integer),
	s = make_string(str);
	return s;
}


object stringtonumber(object o){
	long nb=0;
	uint k=0;
	char* str;
	object n = NULL;
	object s = NULL;
	if(o->type == SFS_NIL){
		WARNING_MSG("string->number admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("string->number admet qu'un argument");
		return NULL;
	}
	s=sfs_eval(o->this.pair.car);
	if(s==NULL){
		return NULL;
	}
	if(s->type != SFS_STRING){
		WARNING_MSG("L'argument doit être une chaîne de caractère");
		return NULL;
	}
	str = s->this.string;
	while(str[k] <= 57 && str[k]>=48){
		nb=10*nb+(str[k]-48);
		k++;
	}
	n=make_integer(nb);
	return n;
}


object symboltostring(object o){
	object s = NULL;
	if(o->type == SFS_NIL){
		WARNING_MSG("symbol->string admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("symbol->string admet qu'un argument");
		return NULL;
	}
	s=sfs_eval(o->this.pair.car);
	if(s==NULL){
		return NULL;
	}
	if(s->type != SFS_SYMBOL){
		WARNING_MSG("L'argument doit être un symbole");
		return NULL;
	}
	s=make_string(s->this.symbol);
	return s;
}


object stringtosymbol(object o){
	object s = NULL;
	if(o->type == SFS_NIL){
		WARNING_MSG("string->symbol admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("string->symbol admet qu'un argument");
		return NULL;
	}
	s=sfs_eval(o->this.pair.car);
	if(s==NULL){
		return NULL;
	}
	if(s->type != SFS_STRING){
		WARNING_MSG("L'argument doit être une chaîne de caractère");
		return NULL;
	}
	s=make_symbol(s->this.string);
	return s;
}

/*Arithmétiques*/
object plus(object nums) {
	long a = 0 ;
	object somme = NULL;
	object t = NULL;
	if (nums == nil ) {
		WARNING_MSG("Erreur, + prend au moins un argument");
		return NULL ;
	}
	while (nums -> this.pair.cdr != nil ) {

		t = sfs_eval(nums -> this.pair.car);
		if(t == NULL){
			return NULL;
		}
		if ( t -> type != SFS_NUMBER ) {
			WARNING_MSG("Erreur, + ne prend en argument que des entiers");
			return NULL ; 
		}

		a += t->this.number.this.integer ;
		nums = nums ->this.pair.cdr ;
	}
	t = sfs_eval(nums -> this.pair.car);
	if(t == NULL){
		return NULL;
	}
	if ( t -> type != SFS_NUMBER ) {
		WARNING_MSG("Erreur, + ne prend en argument que des entiers");
		return NULL ; 
	}
	a +=  t->this.number.this.integer ;
	somme = make_integer (a) ;
	return somme ;
}




object moins(object nums) {
	long a = 0 ;
	long b = 0 ;  
	object sous = NULL ;
	object t = NULL ;
	if (nums == nil ) {
		WARNING_MSG("Erreur, - prend au moins un argument");
		return NULL ;
	}
	t = sfs_eval (nums->this.pair.car) ; 
	if (t == NULL ){
		return NULL ;
	}
	if (t ->type != SFS_NUMBER ){
		WARNING_MSG("Erreur, - ne prend en argument que des entiers");
		return NULL ;
	}
	a = t-> this .number.this.integer ;
	if (nums->this.pair.cdr == nil ) {
		sous = make_integer(-a) ;
		return sous ; 
	}
	while (nums->this.pair.cdr != nil){
		nums = nums->this.pair.cdr ; 
		t =sfs_eval(nums->this.pair.car); 
		if (t == NULL ){
			return NULL ;
		}
		if (t ->type != SFS_NUMBER ){
			WARNING_MSG("Erreur, - ne prend en argument que des entiers");
			return NULL ;
		}
		b = t -> this.number.this.integer ; 
		a = a - b ; 
	}
	sous = make_integer(a) ; 
	return sous ; 
}

object multiple(object nums) {
	long a = 1 ;
	object produit = NULL ;
	object t = NULL;
	if (nums == nil || nums->this.pair.cdr == nil ) {
		WARNING_MSG("Erreur, * prend au moins deux arguments");
		return NULL ; 
	}
	while (nums -> this.pair.cdr != nil ) {
		t = sfs_eval(nums -> this.pair.car);
		if(t == NULL){
			return NULL;
		}
		if ( t -> type != SFS_NUMBER ) {
			WARNING_MSG("Erreur, * ne prend en argument que des entiers");
			return NULL ; 
		}
		a *=  t->this.number.this.integer ;
		nums = nums ->this.pair.cdr ;
	}
	t = sfs_eval(nums -> this.pair.car);
	if(t == NULL){
		return NULL;
	}
	if ( t -> type != SFS_NUMBER ) {
		WARNING_MSG("Erreur, * ne prend en argument que des entiers");
		return NULL ; 
		}
	a *=  t->this.number.this.integer ;
	produit = make_integer (a) ;
	return produit ;
}

object quotient(object nums) {
	long a = 1 ;
	long b = 1 ; 
	object quotient = NULL ;
	object t = NULL;
	if (nums == nil || nums->this.pair.cdr == nil) {
		WARNING_MSG("Erreur, quotient prend au moins deux arguments");
		return NULL ; 
	}
	t = sfs_eval (nums->this.pair.car) ; 
	if (t == NULL ){
		return NULL ;
	}
	if (t ->type != SFS_NUMBER ){
		WARNING_MSG("Erreur, quotient ne prend en argument que des entiers");
		return NULL ;
	}
	a = t-> this .number.this.integer ;

	while (nums->this.pair.cdr != nil){
		nums = nums->this.pair.cdr ; 
		t =sfs_eval(nums->this.pair.car); 
		if (t == NULL ){
			return NULL ;
		}
		if (t ->type != SFS_NUMBER ){
			WARNING_MSG("Erreur, quotient ne prend en argument que des entiers");
			return NULL ;
		}
		if (t->this.number.this.integer == 0 ){
			WARNING_MSG("Erreur, division par 0 impossible");
			return NULL ;
		}
		b = t -> this.number.this.integer ; 
		a = a / b ; 
	}
	quotient = make_integer(a) ; 
	return quotient; 
}


object egal(object nums) {
	
	if (nums == nil || nums->this.pair.cdr == nil || cddr(nums) != nil ) {
		WARNING_MSG("Erreur, =  prend deux arguments");
		return NULL ;
	}
	if (sfs_eval (nums->this.pair.car) == NULL || sfs_eval (cadr(nums)) == NULL ) {
			return NULL ;
	}
 
	if (sfs_eval (nums->this.pair.car)->type != sfs_eval(cadr(nums))->type ) {
		return NULL ; 
	}
	
	switch (sfs_eval (nums->this.pair.car)->type) {
	
	 	case SFS_SYMBOL : 
			if (sfs_eval (nums->this.pair.car) == sfs_eval (cadr(nums)) ) {
				return vrai; 
			}
			else {
				return faux ; 
			}

		case SFS_NUMBER :
			if( sfs_eval (nums->this.pair.car)->this.number.this.integer == sfs_eval (cadr(nums))->this.number.this.integer ) {
				return vrai; 
			}
			else {
				return faux ; 
			}
		case SFS_CHARACTER :
			if( sfs_eval (nums->this.pair.car)->this.character == sfs_eval (cadr(nums))->this.character ) {
				return vrai; 
			}
			else {
				return faux ; 
			}
		case SFS_STRING:
			if( strcmp (sfs_eval (nums->this.pair.car)->this.string, sfs_eval (cadr(nums))->this.string)==0) {
				return vrai; 
			}
			else {
				return faux ; 
			}
		
		
	}
	
		return faux; 
	
}

object inf(object nums) {
	
	if (nums == nil || nums->this.pair.cdr == nil || cddr(nums)!= nil ) {
		WARNING_MSG("Erreur, < prend deux arguments");
		return NULL ; 
	}	
	if (sfs_eval (nums->this.pair.car) == NULL || sfs_eval (cadr(nums)) == NULL ){
		return NULL ;
	}
	if (sfs_eval(nums->this.pair.car) -> type != SFS_NUMBER || sfs_eval(cadr(nums)) -> type != SFS_NUMBER ) {
		WARNING_MSG("Erreur, < ne prend en argument que des entiers");
		return NULL ; 
	}

	if( sfs_eval (nums->this.pair.car)->this.number.this.integer < sfs_eval(cadr(nums))->this.number.this.integer) {
		return vrai; 
	}
	else {
		return faux ; 
	}

}

object sup(object nums) {
	
	if (nums == nil || nums->this.pair.cdr == nil || cddr(nums)!= nil ) {
		WARNING_MSG("Erreur, > prend deux arguments");
		return NULL ; 
	}

	if (sfs_eval (nums->this.pair.car) == NULL || sfs_eval (cadr(nums)) == NULL ){
		return NULL ;
	}
	if (sfs_eval(nums->this.pair.car) -> type != SFS_NUMBER || sfs_eval(cadr(nums)) -> type != SFS_NUMBER ) {
		WARNING_MSG("Erreur, > ne prend en argument que des entiers");
		return NULL ; 
	}

	if( sfs_eval (nums->this.pair.car)->this.number.this.integer > sfs_eval(cadr(nums))->this.number.this.integer) {
		return vrai; 
	}
	else {
		return faux ; 
	}

}



/* Manipulation de liste*/



object list(object o){
	object l = o;
	object lr = l;
	if(l->type != SFS_PAIR){
		WARNING_MSG("list prend au moins un argument.");
		return NULL;
	}
	do{
		l->this.pair.car = sfs_eval(l->this.pair.car);
		l = l->this.pair.cdr;
	}
	while(l != nil);
	return lr;
}

object cons(object list) {
	object newobject = NULL ;
	if (list == nil || list->this.pair.cdr == nil || cddr(list) != nil) {
		WARNING_MSG("Erreur, cons prend deux arguments");
		return NULL ; 
		
	}

	if (sfs_eval (list->this.pair.car) == NULL || sfs_eval (cadr(list)) == NULL ){
		return NULL ;
	}
	
	newobject = make_pair(sfs_eval(list->this.pair.car), sfs_eval(cadr(list))) ;
	return newobject ;
}

object car(object list) {
	object evalcar = NULL ; 
	
	if (list == nil || list->this.pair.cdr != nil ){
		WARNING_MSG("Erreur, car prend un argument");
		return NULL ; 
	}

	if (list->this.pair.car->type != SFS_PAIR) {
		WARNING_MSG("Erreur, car ne prend en argument qu'une liste");
		return NULL ; 
	}


	
	if (sfs_eval (list->this.pair.car) == NULL ){
		return NULL ;
	}
	if (sfs_eval (list->this.pair.car) ->type != SFS_PAIR ) {
		WARNING_MSG("Erreur, l'expression est invalide");
		return NULL ;
	}
	evalcar =  sfs_eval(list->this.pair.car)->this.pair.car ; 
	return evalcar ;
}

object cdr(object list) {
	object evalcar = NULL ; 
	
	if (list == nil || list->this.pair.cdr != nil ){
		WARNING_MSG("Erreur, cdr prend un argument");
		return NULL ; 
	}	

	if (list->this.pair.car->type != SFS_PAIR) {
		WARNING_MSG("Erreur, cdr ne prend en argument qu'une liste");
		return NULL ; 
	}

	if (sfs_eval (list->this.pair.car) == NULL ){
		return NULL ;
	}
	if (sfs_eval (list->this.pair.car) ->type != SFS_PAIR ) {
		WARNING_MSG("Erreur, l'expression est invalide");
		return NULL ;
	}
	
	evalcar =  sfs_eval(list->this.pair.car)->this.pair.cdr ; 
	return evalcar ;
}

object eq(object o){
	object o1 = NULL;
	object o2 = NULL;
	if(o->type == SFS_NIL){
		WARNING_MSG("eq? admet deux arguments");
		return NULL;
	}
	if(cddr(o)->type != SFS_NIL){
		WARNING_MSG("eq? admet que deux arguments");
		return NULL;
	}
	o1 = o->this.pair.car;
	o2 = cadr(o);
	if(o1->type == SFS_NUMBER && o2->type == SFS_NUMBER){
		if(o2->this.number.this.integer == o1->this.number.this.integer){
			return vrai;
		}
		return faux;
	}
	if(o1->type == SFS_NUMBER && o2->type != SFS_NUMBER){
		if(sfs_eval(o2) == NULL){
			return NULL;
		}
		if(sfs_eval(o2)->type == SFS_NUMBER){
			if(sfs_eval(o2)->this.number.this.integer == o1->this.number.this.integer){
				return vrai;
			}
			return faux;
		}
		else{
			return faux;
		}
	}
	if(o1->type != SFS_NUMBER && o2->type == SFS_NUMBER){
		if(sfs_eval(o2) == NULL){
			return NULL;
		}
		if(sfs_eval(o1)->type == SFS_NUMBER){
			if(sfs_eval(o1)->this.number.this.integer == o2->this.number.this.integer){
				return vrai;
			}
			return faux;
		}
		else{
			return faux;
		}
	}
	if(sfs_eval(o2) == NULL || sfs_eval(o1) == NULL){
		return NULL;
	}
	if(sfs_eval(o2)==sfs_eval(o1)){
		return vrai;
	}
	return faux;
}



