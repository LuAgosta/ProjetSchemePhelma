
/**
 * @file object.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:02:57 2012
 * @brief Object definitions for SFS.
 *
 * Object definitions for SFS.
 */

#include "object.h"
#include "mem.h"


object make_object( uint type ) {

    object t = sfs_malloc( sizeof( *t ) );

    t->type = type;

    return t;
}

object make_primitive(primitive p){

  object o = make_object(SFS_PRIMITIVE);

  o->this.primitive = p;
  
  return o;

}

object make_nil( void ) {

    object t = make_object( SFS_NIL );

    t->this.special = t;

    return t;
}

object make_empty_list(void) {
	
	object eptl = make_nil();

	return eptl;

}


object make_boolean(void) {

	object B = make_object(SFS_BOOLEAN);

	B->this.special = B;

	return B;

}

object make_integer(long n) {

	object i = make_object(SFS_NUMBER);
	
	i->this.number.numtype = NUM_INTEGER;
	i->this.number.this.integer = n;

	return i;

}

object make_symbol(char* sym) {
	object s = tsym;
	while(s->this.pair.cdr != nil){
		if(strcmp(s->this.pair.car->this.string,sym)==0){
			return(s->this.pair.car);					/*le symbole existe déjà, on renvoie l'adresse*/
   		 }
    		s=s->this.pair.cdr;
 	}
  	if(s->this.pair.car != nil){
      		if(strcmp(s->this.pair.car->this.string,sym)==0){
      			return(s->this.pair.car);
    		}
  	}
	s = make_object(SFS_SYMBOL);  /*il n'existe pas encore, on le crée et on renvoie sont adresse*/
	strcpy(s->this.symbol, sym);
  	tsym = make_pair(s,tsym);     /*ajout du symbole créé à la table des symboles*/
	return s;
}

object make_char(char ch) {

	object c = make_object(SFS_CHARACTER);

	c->this.character = ch;

	return c;

}

object make_pair(object o1, object o2) {

	object p = make_object(SFS_PAIR);

	p->this.pair.car = o1;
	p->this.pair.cdr = o2;

	return p;

}

object make_string(char* st) {

	object s = make_object(SFS_STRING);

	strcpy(s->this.string, st);

	return s;

}

object make_noreturnscheme(void){

    object t = make_object( SFS_NORETURNSCHEME );

    t->this.special = t;

    return t;
}


object make_compound ( object parms, object body, object env) {

	object comp = make_object(SFS_COMPOUND) ; 

	comp->this.compound.parms = parms ;
	comp->this.compound.body = body ;
	comp->this.compound.env = env ;

	return comp ; 
}



object caar(object o){
	return(o->this.pair.car->this.pair.car);
	}

object cadr(object o){
	return(o->this.pair.cdr->this.pair.car);
	}

object cdar(object o){
	return(o->this.pair.car->this.pair.cdr);
	}

object cddr(object o){
	return(o->this.pair.cdr->this.pair.cdr);
	}

object cadar(object o){
	return(cdar(o)->this.pair.car);
}

object caddr(object o){
	return(cddr(o)->this.pair.car);
}

object cdaar(object o){
	return(caar(o)->this.pair.cdr);
}

object caadr(object o){
	return(cadr(o)->this.pair.car);
}

object cdadr(object o){
	return(cadr(o)->this.pair.cdr);
}

object cdddr(object o){
	return(cddr(o)->this.pair.cdr);
}

object cadddr(object o){
	return(cdddr(o)->this.pair.car);
}

object copyobject(object input){    /*pas les primitives et les coumpounds pour l'instant*/
  object output = NULL;
  switch(input->type){

    case SFS_NIL :
      output = nil;
    break;

    case SFS_NUMBER :
      output = make_integer(input->this.number.this.integer);
    break;

    case SFS_SYMBOL :
      output = make_symbol(input->this.symbol);
    break;

    case SFS_STRING :
      output = make_string(input->this.string);
    break;

    case SFS_BOOLEAN :
      if (input == vrai){
        output = vrai;
      }
      output = faux;
    break;

    case SFS_PAIR :
      output = make_pair(copyobject(input->this.pair.car),copyobject(input->this.pair.cdr));
    break;

    case SFS_CHARACTER :
      output = make_char(input->this.character);
    break;
  }
  return output;
}

int nbelem(object o){
	object listelem = NULL;
	int nb = 0;
	listelem = o;
	if(listelem== nil){
		return 0;
	}
	while(listelem->this.pair.cdr != nil){
		nb += 1;
		listelem = listelem->this.pair.cdr;
	}
	nb += 1;
	return nb;
}

