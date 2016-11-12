/**
 * @file prim.c
 * @author Agosta Lucie and Noé Paul-Gauthier>
 * @date Sat Nov 12 17:44:05 2016
 */

#include <stdio.h>


#include "prim.h"

object plus_p(object nums) {
	long a = 0 ; 
	object somme ;
	while (nums -> this.pair.cdr != nil ) {
		a +=  nums -> this.pair.car -> this.number.this.integer ; 
		nums = nums ->this.pair.cdr ;
	}
	somme = make_integer (a) ;
	return somme ; 
	
}

