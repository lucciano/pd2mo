#include <src/flatter.h>
#include <pdppt/parser.h>
#include <pdppt/modelcoupled.h>
#include <iostream>

using namespace std;

modelCoupled * flatter::flat(modelCoupled * c){
    int atomic = 0;
    modelCoupled * rtr = new modelCoupled();
    rtr->type = TOKROOT;
    rtr->name = c->name;

    for (QList< modelChild * >::iterator childsIterator = c->childs.begin(); 
	childsIterator != c->childs.end(); 
	++childsIterator, ++atomic){

	if((*childsIterator)->childType == COUPLED){
		modelCoupled * coupled = (*childsIterator)->coupled;

		
		int delta = coupled->childs.size() -1;
		for( QList< modelChild * >::iterator cI = coupled->childs.begin(); 
			cI != coupled->childs.end(); 
			++cI){
			if((*cI)->childType == ATOMIC){
				modelChild * m = new modelChild();
				m->atomic = new modelAtomic();
				m->atomic->path = (*cI)->atomic->path;
				m->atomic->params.append((*cI)->atomic->params);
				m->atomic->father = rtr;
				cout << m->atomic->params.size() << endl;
				rtr->childs.append(m);
			}else{
				cout << "errro, recursivo..." << endl;
			}
		}

		//Remapeo de las Conecciones Internas
		for(QList < modelConnection * >::iterator ic = c->lsIC.begin();
			ic != c->lsIC.end();
			ic++){

			if((*ic)->childSource == atomic){ 
			// internal connection con un jerarquico. 
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
					}
				}
			}
			if((*ic)->childSink == atomic){
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
					}
				}
			
			}
			if(((*ic)->childSource > atomic or (*ic)->childSink > atomic)
			and ((*ic)->childSource != atomic and (*ic)->childSink != atomic))
			{
				modelConnection * cNew = new modelConnection;
				cNew->childSource = (*ic)->childSource 
							+ ((*ic)->childSource > atomic)?delta:0;
				cNew->sourcePort = (*ic)->sourcePort;
				cNew->childSink = (*ic)->childSink
							+ ((*ic)->childSink > atomic)?delta:0;
				cNew->sinkPort = (*ic)->sinkPort;
				rtr->lsIC.append(cNew);
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
		modelChild * m = new modelChild();
		m->atomic = new modelAtomic();
		m->atomic->path = (*childsIterator)->atomic->path;
		m->atomic->params.append((*childsIterator)->atomic->params);
		m->atomic->father = rtr;
		cout << m->atomic->params.size() << endl;
		rtr->childs.append(m);
	}
    }
    return rtr;
}
