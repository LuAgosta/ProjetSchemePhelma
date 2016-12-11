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
		WARNING_MSG("null? n'admet qu'un argument");
		return NULL;
	}
	if(o->this.pair.car->type == SFS_NIL){
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
		WARNING_MSG("boolean? n'admet qu'un argument");
		return NULL;
	}
	if(o->this.pair.car->type == SFS_BOOLEAN){
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
		WARNING_MSG("symbol? n'admet qu'un argument");
		return NULL;
	}
	if(o->this.pair.car->type == SFS_SYMBOL){
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
		WARNING_MSG("integer? n'admet qu'un argument");
		return NULL;
	}
	if(o->this.pair.car->type == SFS_NUMBER){
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
		WARNING_MSG("char? n'admet qu'un argument");
		return NULL;
	}
	if(o->this.pair.car->type == SFS_CHARACTER){
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
		WARNING_MSG("string? n'admet qu'un argument");
		return NULL;
	}
	if(o->this.pair.car->type == SFS_STRING){
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
		WARNING_MSG("pair? n'admet qu'un argument");
		return NULL;
	}
	if(o->this.pair.car->type == SFS_PAIR){
		return vrai;
	}
	return faux;
}

object ifprocedure(object o){
	if(o->type == SFS_NIL){
		WARNING_MSG("procedure? admet au moins un argument");
		return NULL;
	}
	if(o->this.pair.cdr->type != SFS_NIL){
		WARNING_MSG("procedure? n'admet qu'un argument");
		return NULL;
	}
	if(o->this.pair.car->type == SFS_COMPOUND){
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
		WARNING_MSG("char->interger n'admet qu'un argument");
		return NULL;
	}
	n=o->this.pair.car;
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
		WARNING_MSG("integer->char n'admet qu'un argument");
		return NULL;
	}
	c=o->this.pair.car;
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
		WARNING_MSG("number->string n'admet qu'un argument");
		return NULL;
	}
	s=o->this.pair.car;
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
		WARNING_MSG("string->number n'admet qu'un argument");
		return NULL;
	}
	s=o->this.pair.car;
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
		WARNING_MSG("symbol->string n'admet qu'un argument");
		return NULL;
	}
	s=o->this.pair.car;
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
		WARNING_MSG("string->symbol n'admet qu'un argument");
		return NULL;
	}
	s=o->this.pair.car;
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

		t = nums -> this.pair.car;
		if ( t -> type != SFS_NUMBER ) {
			WARNING_MSG("Erreur, + ne prend en argument que des entiers");
			return NULL ;
		}

		a += t->this.number.this.integer ;
		nums = nums ->this.pair.cdr ;
	}
	t = nums -> this.pair.car;
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
	t = nums->this.pair.car ;
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
		t =nums->this.pair.car;
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
		t = nums -> this.pair.car;
		if ( t -> type != SFS_NUMBER ) {
			WARNING_MSG("Erreur, * ne prend en argument que des entiers");
			return NULL ;
		}
		a *=  t->this.number.this.integer ;
		nums = nums ->this.pair.cdr ;
	}
	t = nums -> this.pair.car;
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
	t = nums->this.pair.car ;
	if (t ->type != SFS_NUMBER ){
		WARNING_MSG("Erreur, quotient ne prend en argument que des entiers");
		return NULL ;
	}
	a = t-> this .number.this.integer ;

	while (nums->this.pair.cdr != nil){
		nums = nums->this.pair.cdr ;
		t =nums->this.pair.car;
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
object remainder(object nums) {
	long a = 1 ;
	long b = 1 ;
	object quotient = NULL ;
	object t = NULL;
	if (nums == nil || nums->this.pair.cdr == nil  ) {
		WARNING_MSG("Erreur, remainder prend au moins deux arguments");
		return NULL ;
	}
	t = nums->this.pair.car ;
	if (t ->type != SFS_NUMBER ){
		WARNING_MSG("Erreur, remainder ne prend en argument que des entiers");
		return NULL ;
	}
	a = t-> this .number.this.integer ;

	while (nums->this.pair.cdr != nil){
		nums = nums->this.pair.cdr ;
		t =nums->this.pair.car;
		if (t ->type != SFS_NUMBER ){
			WARNING_MSG("Erreur, remainder ne prend en argument que des entiers");
			return NULL ;
		}
		if (t->this.number.this.integer == 0 ){
			WARNING_MSG("Erreur, division par 0 impossible");
			return NULL ;
		}
		b = t -> this.number.this.integer ;
		a = a % b ;
	}
	quotient = make_integer(a) ;
	return quotient;
}


object egal(object nums) {
	if (nums == nil || nums->this.pair.cdr == nil || cddr(nums)!= nil ) {
		WARNING_MSG("Erreur, = prend deux arguments");
		return NULL ;
	}
	if (nums->this.pair.car -> type != SFS_NUMBER || cadr(nums) -> type != SFS_NUMBER ) {
		WARNING_MSG("Erreur, = ne prend en argument que des entiers");
		return NULL ;
	}
	if( nums->this.pair.car->this.number.this.integer == cadr(nums)->this.number.this.integer) {
		return vrai;
	}
	else {
		return faux ;
	}
}


object inf(object nums) {

	if (nums == nil || nums->this.pair.cdr == nil || cddr(nums)!= nil ) {
		WARNING_MSG("Erreur, < prend deux arguments");
		return NULL ;
	}
	if (nums->this.pair.car -> type != SFS_NUMBER || cadr(nums) -> type != SFS_NUMBER ) {
		WARNING_MSG("Erreur, < ne prend en argument que des entiers");
		return NULL ;
	}

	if( nums->this.pair.car->this.number.this.integer < cadr(nums)->this.number.this.integer) {
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

	if (nums->this.pair.car -> type != SFS_NUMBER || cadr(nums) -> type != SFS_NUMBER ) {
		WARNING_MSG("Erreur, > ne prend en argument que des entiers");
		return NULL ;
	}

	if( nums->this.pair.car->this.number.this.integer > cadr(nums)->this.number.this.integer) {
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
		l->this.pair.car = l->this.pair.car;
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


	newobject = make_pair(list->this.pair.car, cadr(list)) ;
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


	if (list->this.pair.car ->type != SFS_PAIR ) {
		WARNING_MSG("Erreur, l'expression est invalide");
		return NULL ;
	}
	evalcar =  list->this.pair.car->this.pair.car ;
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

	if (list->this.pair.car ->type != SFS_PAIR ) {
		WARNING_MSG("Erreur, l'expression est invalide");
		return NULL ;
	}

	evalcar =  list->this.pair.car->this.pair.cdr ;
	return evalcar ;
}


object eqv(object o) {
	if (o == nil || o->this.pair.cdr == nil || cddr(o) != nil ) {
		WARNING_MSG("Erreur, eqv?  prend deux arguments");
		return NULL ;
	}
	if (o->this.pair.car == NULL || cadr(o) == NULL ) {
			return NULL ;
	}

	if (o->this.pair.car->type != cadr(o)->type ) {
		return faux ;
	}
	switch (o->this.pair.car->type) {

	 	case SFS_SYMBOL :
			if (o->this.pair.car == cadr(o) ) {
				return vrai;
			}
			else {
				return faux ;
			}

		case SFS_NUMBER :
			if( o->this.pair.car->this.number.this.integer == cadr(o)->this.number.this.integer ) {
				return vrai;
			}
			else {
				return faux ;
			}
		case SFS_CHARACTER :
			if( o->this.pair.car->this.character == cadr(o)->this.character ) {
				return vrai;
			}
			else {
				return faux ;
			}
		case SFS_STRING:
			if(o->this.pair.car == cadr(o)) {
				return vrai;
			}
			else {
				return faux ;
			}
			case SFS_PAIR:
				if(o->this.pair.car == cadr(o)) {
					return vrai;
				}
				else {
					return faux ;
				}
		case SFS_BOOLEAN :
			if (o->this.pair.car != cadr(o) ){
				return faux ;
			}
			else {
				return vrai ;
			}
	}
		return vrai ;
}


object eq(object o){
	if (o == nil || o->this.pair.cdr == nil || cddr(o) != nil ) {
		WARNING_MSG("Erreur, eq?  prend deux arguments");
		return NULL ;
	}
	if (o->this.pair.car == NULL || cadr(o) == NULL ) {
			return NULL ;
	}

	if (o->this.pair.car->type != cadr(o)->type ) {
		return faux ;
	}
	switch (o->this.pair.car->type) {

	 	case SFS_SYMBOL :			/* <=> eqv? */
			if (o->this.pair.car == cadr(o) ) {
				return vrai;
			}
			else {
				return faux ;
			}

		case SFS_NUMBER :			/*#t si même adresse en mémoire*/
			if(o->this.pair.car == cadr(o)) {
				return vrai;
			}
			else {
				return faux ;
			}
		case SFS_CHARACTER :	/*#t si même adresse en mémoire*/
			if(o->this.pair.car == cadr(o)) {
				return vrai;
			}
			else {
				return faux ;
			}
		case SFS_STRING:			/* <=> eqv? */
			if(o->this.pair.car == cadr(o)) {
				return vrai;
			}
			else {
				return faux ;
			}
			case SFS_PAIR:			/* <=> eqv? */
				if(o->this.pair.car == cadr(o)) {
					return vrai;
				}
				else {
					return faux ;
				}
		case SFS_BOOLEAN :			/* <=> eqv? */
			if (o->this.pair.car != cadr(o) ){
				return faux ;
			}
			else {
				return vrai ;
			}
	}
		return vrai ;
}

object setcar(object list) {
	if (list == nil || list->this.pair.cdr == nil || cddr(list) != nil ){
		WARNING_MSG("Erreur, set-car! prend deux arguments");
		return NULL ;
	}
	if (list->this.pair.car->type != SFS_PAIR ) {
		WARNING_MSG("Erreur, la primitive set-car! prend en premier argument une paire");
		return NULL ;
	}
	list->this.pair.car->this.pair.car = cadr (list);
	return list->this.pair.car;
}

object setcdr(object list) {
	if (list == nil || list->this.pair.cdr == nil || cddr(list) != nil ){
		WARNING_MSG("Erreur, set-cdr! prend deux arguments");
		return NULL ;
	}
	if (list->this.pair.car->type != SFS_PAIR ) {
		WARNING_MSG("Erreur, la primitive set-cdr! prend en premier argument une paire");
		return NULL ;
	}
	list->this.pair.car->this.pair.cdr = cadr (list);
	return list->this.pair.car;
}

