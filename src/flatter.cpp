#include <src/flatter.h>
#include <pdppt/parser.h>

#include <iostream>


modelCoupled * flatter::flat(modelCoupled * c){
    int atomic = 0;
    modelCoupled * rtr = new modelCoupled();
    rtr->type = TOKROOT;
    rtr->name = c->name;
    int delta = 0;

    for (QList< modelChild * >::iterator childsIterator = c->childs.begin(); 
	childsIterator != c->childs.end(); 
	++childsIterator, ++atomic){

	if((*childsIterator)->childType == COUPLED){
		modelCoupled * coupled = (*childsIterator)->coupled;

		
		delta += coupled->childs.size() -1;
		for( QList< modelChild * >::iterator cI = coupled->childs.begin(); 
			cI != coupled->childs.end(); 
			++cI){
			if((*cI)->childType == ATOMIC){
				modelChild * m = new modelChild();
				m->childType = ATOMIC;
				m->atomic = new modelAtomic();
				m->atomic->path = (*cI)->atomic->path;
				m->atomic->params.append((*cI)->atomic->params);
				m->atomic->paramsString = (*cI)->atomic->paramsString;
				m->atomic->father = rtr;
				rtr->childs.append(m);
			}else{
				modelChild * m = new modelChild();
				m->childType = COUPLED;
				m->coupled = flatter::flat((*cI)->coupled);
				rtr->childs.append(m);
			}
		}

		//Remapeo de las Conecciones Internas
		for(QList < modelConnection * >::iterator ic = c->lsIC.begin();
			ic != c->lsIC.end(); ){

			bool eraseIc = false;

			if(((*ic)->childSource > atomic or (*ic)->childSink > atomic)
			and ((*ic)->childSource != atomic and (*ic)->childSink != atomic))
			{
				modelConnection * cNew = *ic;
				cNew->childSource += ((*ic)->childSource > atomic)?delta:0;
				cNew->sourcePort = (*ic)->sourcePort;
				cNew->childSink += ((*ic)->childSink > atomic)?delta:0;
				cNew->sinkPort = (*ic)->sinkPort;
				cout << cNew->childSource << "," << cNew->sourcePort << ";" << cNew->childSink <<","<< cNew->sinkPort << endl;
				eraseIc = true;
				rtr->lsIC.append(cNew);
			}

			if((*ic)->childSource == atomic){
			// internal connection with a coupled (sub) module.
				for(QList < modelConnection * >::iterator eoc = coupled->lsEOC.begin();
					eoc != coupled->lsEOC.end();
					eoc++){

					if((*ic)->sourcePort == (*eoc)->sinkPort){
						modelConnection * cNew = new modelConnection;
						cNew->childSource = (*eoc)->childSource+ atomic;
						cNew->sourcePort = (*eoc)->sourcePort;
						cNew->childSink = (*ic)->childSink
							+ (((*ic)->childSink > atomic)?delta:0);
						cNew->sinkPort = (*ic)->sinkPort;
						rtr->lsIC.append(cNew);
						//c->lsIC.erase(ic);
						eraseIc = true;
					}
				}
			} 
			if((*ic)->childSink == atomic){
			// internal connection with a coupled (sub) module.
				for(QList < modelConnection * >::iterator eic = coupled->lsEIC.begin();
					eic != coupled->lsEIC.end();
					eic++){
					if((*ic)->sinkPort == (*eic)->sourcePort){
						modelConnection * cNew = new modelConnection;
						cNew->childSource = (*ic)->childSource 
							+ (((*ic)->childSource > atomic)?delta:0);
						cNew->sourcePort = (*ic)->sourcePort;
						cNew->childSink = (*eic)->childSink + atomic;
						cNew->sinkPort = (*eic)->sinkPort;
						rtr->lsIC.append(cNew);
						//c->lsIC.erase(ic);
						eraseIc = true;
					}
				}
			}
			if(eraseIc){
				ic = c->lsIC.erase(ic);
			}else{ 
				ic++;
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

		for(QList < modelConnection * >::iterator ic = c->lsIC.begin();
			ic != c->lsIC.end();
			ic++){
			if( (*ic)->childSink == atomic or
			    (*ic)->childSource  == atomic){
				c->lsIC.erase(ic);
				ic=c->lsIC.begin();
			}
		}
	}else{
		modelChild * m = new modelChild();
		m->atomic = new modelAtomic();
		m->atomic->path = (*childsIterator)->atomic->path;
		m->atomic->params.append((*childsIterator)->atomic->params);
		m->atomic->paramsString = (*childsIterator)->atomic->paramsString;
		m->atomic->father = rtr;
		rtr->childs.append(m);

		for(QList < modelConnection * >::iterator ic = c->lsIC.begin();
			ic != c->lsIC.end();
			ic++){

			if(( (*ic)->childSource == atomic and (*ic)->childSink <= atomic)
					or
			     ((*ic)->childSink == atomic and (*ic)->childSource <= atomic)){
				rtr->lsIC.append(*ic);
				
			}
		}


	}
    }
    return rtr;
}
