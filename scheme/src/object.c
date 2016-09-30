
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

object make_integer(int n) {

	object i = make_object(SFS_NUMBER);
	
	i->this.number.numtype = NUM_INTEGER;
	i->this.number.this.integer = n;

	return i;

}

object make_symbol(char* sym) {

	object s = make_object(SFS_SYMBOL);

	strcpy(s->this.symbol , sym);
	
	return s;

}

object make_char(char ch) {

	object c = make_object(SFS_CHARACTER);

	c->this.character = ch;

	return c;

}

object make_pair(pair pa) {

	object p = make_object(SFS_PAIR);

	p->this.pair = pa;

	return p;

}

object make_string(char* st) {

	object s = make_object(SFS_STRING);

	strcpy(s->this.string, st);

	return s;

}
