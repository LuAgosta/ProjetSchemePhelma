#include <stdio.h>
#include "env.h"

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
