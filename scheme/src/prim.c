/**
 * @file prim.c
 * @author Agosta Lucie and Noé Paul-Gauthier>
 * @date Sat Nov 12 17:44:05 2016
 */

#include <stdio.h>
#include "prim.h"
#include "eval.h"

object plus(object nums) {
	long a = 0 ;
	object somme ;
	object t ;
	while (nums -> this.pair.cdr != nil ) {
		t = sfs_eval(nums -> this.pair.car);
		if(t == NULL){
			return NULL;
		}
		a +=  sfs_eval(nums -> this.pair.car)->this.number.this.integer ;
		nums = nums ->this.pair.cdr ;
	}
	t = sfs_eval(nums -> this.pair.car);
	if(t == NULL){
		return NULL;
	}
	a +=  sfs_eval(nums -> this.pair.car)->this.number.this.integer ;
	somme = make_integer (a) ;
	return somme ;
}

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
object cons(object list) {
	object newobject = NULL ;
	if (list == nil || list->this.pair.cdr == nil ) {
		WARNING_MSG("Erreur, cons prend deux arguments");
		return NULL ; 
		
	}
	if (cddr(list) != nil ){
		WARNING_MSG("Erreur, cons ne prend que deux arguments");
		return NULL ; 
	}
	if (sfs_eval (list->this.pair.car) == NULL || sfs_eval (cadr(list)) == NULL ){
		return NULL ;
	}
	
	newobject = make_pair(sfs_eval(list->this.pair.car), sfs_eval(cadr(list))) ;
	return newobject ;
}

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
