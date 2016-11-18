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

