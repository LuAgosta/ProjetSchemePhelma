#include <stdio.h>
#include "env.h"

/*Ajouter un environnement*/
object addenv(object env){
	return make_pair(nil,env);
}

/*Ajouter une variable et sa valeur dans l'environnement courant*/
void addvar(object var, object val){
	object o = lenv->this.pair.car;
	lenv->this.pair.car = make_pair(make_pair(var,val),o);
}

/*Ajouter une variable et sa valeur dans l'environnement env*/
void addvarenv(object var, object val, object env){
	object o = env->this.pair.car;
	env->this.pair.car = make_pair(make_pair(var,val),o);
}

/*Recherche d'une variable dans l'environnements courant*/
object in_envc(object var){
	object l = lenv->this.pair.car;
	while(l->this.pair.cdr != nil){
		if(strcmp(caar(l)->this.string,var->this.string)==0){
			return(cdar(l));
		}
		l = l->this.pair.cdr;
	}
	if(strcmp(caar(l)->this.string,var->this.string)==0){
		return(cdar(l));
	}
	return NULL;
}

/*Recherche d'une variable dans l'ensemble des environnements*/
object in_envs(object var, object env){
	object k = env;
	object l;
	while(k->this.pair.cdr != nil){
		l = k->this.pair.car;
		while(l->this.pair.cdr != nil){
			if(strcmp(caar(l)->this.string,var->this.string)==0){
				return(l->this.pair.car);
			}
			l = l->this.pair.cdr;
		}
		if(strcmp(caar(l)->this.string,var->this.string)==0){
			return(l->this.pair.car);
		}
		k=k->this.pair.cdr;
	}
	l = k->this.pair.car;
	while(l->this.pair.cdr != nil){
		if(strcmp(caar(l)->this.string,var->this.string)==0){
			return(l->this.pair.car);
		}
		l = l->this.pair.cdr;
	}
	if(strcmp(caar(l)->this.string,var->this.string)==0){
		return(l->this.pair.car);
	}
	WARNING_MSG("Erreur, la variable %s n'est pas définie",var->this.string);
	return NULL;
}

