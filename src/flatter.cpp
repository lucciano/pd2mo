#include <src/flatter.h>
#include <iostream>

modelCoupled * flatter::flat(modelCoupled * c){
    int atomic = 0;
    modelCoupled * rtr = new modelCoupled();
    rtr->lsIC.append(c->lsIC);
    for (QList< modelChild * >::iterator childsIterator = c->childs.begin(); 
	childsIterator != c->childs.end(); 
	++childsIterator, ++atomic){

	if((*childsIterator)->childType == COUPLED){
		modelCoupled * coupled = (*childsIterator)->coupled;

		
		int delta = coupled->childs.size() -1;
		rtr->childs.append(coupled->childs);

		//Remapeo de las Conecciones Internas
		for(QList < modelConnection * >::iterator ic = rtr->lsIC.begin();
			ic != rtr->lsIC.end();
			ic++){

			if((*ic)->childSource == atomic){
			}
			if((*ic)->childSink == atomic){
			}

			if((*ic)->childSource > atomic){
				(*ic)->childSource += delta;
			}

			if((*ic)->childSink > atomic){
				(*ic)->childSink += delta;
			}
		}

		//Agregamos las conecciones internas del modelo acoplado.
		for(QList < modelConnection * >::iterator ic = coupled->lsIC.begin();
			ic != coupled->lsIC.end();
			ic++){
			(*ic)->childSource += atomic;
			(*ic)->childSink += atomic;
			rtr->lsIC.append((*ic));
		}
	}else{
		rtr->childs.append(*childsIterator);
	}
    }
    return rtr;
}
