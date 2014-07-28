#include <src/flatter.h>

modelCoupled * flatter::flat(modelCoupled * c){
    int desplazamiento = 0;
    modelCoupled * rtr = new modelCoupled();
    for (QList< modelChild * >::iterator childsIterator = c->childs.begin(); 
	childsIterator != c->childs.end(); 
	++childsIterator){

	if((*childsIterator)->childType == COUPLED){
		modelCoupled * coupled = (*childsIterator)->coupled;
		desplazamiento += coupled->childs.size();
		rtr->childs.append(coupled->childs);
	}else{
		rtr->childs.append(*childsIterator);
	}
    }
    return rtr;
}
