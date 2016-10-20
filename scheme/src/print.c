
/**
 * @file print.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:12:17 2012
 * @brief Printing stuff for SFS.
 *
 * Printing stuff for SFS.
 */

#include "print.h"

#include <stdio.h>

void sfs_print_atom( object o ) {
	switch ( o->type ) {
		case SFS_STRING : 
	 		printf ("\"%s\"" , o->this.string ) ; 
		break ; 

		case SFS_CHARACTER : 
			if(o->this.character == '\n'){
				printf("#\\newline");
				break;
			}
			if(o->this.character == ' '){
				printf("#\\space");
				break;
			}
			printf ("#\\%c" , o->this.character ) ; 
		break ; 

		case SFS_SYMBOL : 
			printf ( "%s" , o->this.symbol ) ; 
		break ; 

	
		case SFS_NUMBER : 
			if ( o->this.number.numtype == NUM_INTEGER ) { 
				if(o->this.number.this.integer == LONG_MAX){
					printf("+inf");
					break;
				}
				if(o->this.number.this.integer == LONG_MIN){
					printf("-inf");
					break;
				}
				printf ("%ld" , o->this.number.this.integer ) ; 
			}
			else {
				printf ("%lf" , o->this.number.this.real ) ; 
			}
		
			break ; 

		case SFS_NIL :
			printf("()") ;
		break ;

		case SFS_BOOLEAN :
			if ( o->this.special == vrai ) {
				printf("#t") ; 
			}
			else {
				printf ("#f"); 
			} 
	
	}
		
} 

void sfs_print_pair( object o ) {

	sfs_print(o->this.pair.car);

	if(o->this.pair.cdr->type == SFS_NIL){
		printf(")");
	}
	if(o->this.pair.cdr->type == SFS_PAIR){
		printf(" ");
		sfs_print_pair(o -> this.pair.cdr);
	}
	if(o->this.pair.cdr->type == SFS_CHARACTER || o->this.pair.cdr->type == SFS_SYMBOL || o->this.pair.cdr->type == SFS_STRING || o->this.pair.cdr->type == SFS_NUMBER || o->this.pair.cdr->type == SFS_BOOLEAN){
		printf(".");
		sfs_print_atom(o->this.pair.cdr);
		printf(")");
	}
}



void sfs_print( object o ) {
	if(o == NULL){
		WARNING_MSG("Erreur");
		return;
	}
    if ( o->type == SFS_PAIR ) {
	printf("(");
        sfs_print_pair( o );
    }
    else {
        sfs_print_atom( o );
	
    }

}
