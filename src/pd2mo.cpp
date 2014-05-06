#include <pd2mo.h>

using namespace std;

namespace pd2mo{
Pd2Mo::Pd2Mo(){ 
        classMap = new map<string, string>();
        pd2mo_dir = getFullPath();
}

char * Pd2Mo::getFullPath(){
        char szTmp[320];
        char pBuf[320];
        int len = 320;
        sprintf(szTmp, "/proc/%d/exe", getpid());
        int bytes = readlink(szTmp, pBuf, len);
        if(bytes >= 0)
                pBuf[bytes] = '\0';
        return dirname(pBuf);
}

void Pd2Mo::loadConfigFile(string file, ostream * log){
        //Class Mapping
        INIReader reader(file);
        if (reader.ParseError() < 0) {
            (* log )<< "Can't load '"<< file <<"'\n";
        }else{
                map<string, list <string> >::iterator it;
                map<string, list <string> > * keys = reader.getKeys();
                foreach(it, keys){
                        (*classMap)[(it->first)] = reader.Get(it->first, "Path", "n");
                }
        }
        //Model Parameters
}
void Pd2Mo::transform(string filename, ostream * output, ostream * log){

        QString qfilename = QString::fromStdString(filename);
        
        (*log) << "Open File " << filename << endl;
        modelCoupled *model = parsePDS(qfilename);

        //Load class based on the coupledModel from file
        (*log) << "Load class list based on class map." << endl;
        AST_ClassList classList = getAsClassList(model, classMap, log); 

        //Rename each AST_Class variable based on name and position in the coupledmodel
        AST_ClassListIterator it;
        foreach(it, classList){
                if(current_element(it)){
                        cout << current_element(it)->name() << endl;    
                }else{  
                cout << "<<No Mapped Class>>" << endl;
                }
        }

        //Add coupledmodel connections
        //Move all AST_Class List to a new "Model"
}

/**

*/
AST_ClassList Pd2Mo::getAsClassList(modelCoupled * c, map<string, string> * m, ostream * log){
        (*log) << __PRETTY_FUNCTION__ << endl  ;
        QList< modelChild * >::iterator childsIterator;
        AST_ClassList st = new list<AST_Class>();
        int r;
        for (childsIterator = c->childs.begin(); 
                childsIterator != c->childs.end(); 
                ++childsIterator){
                modelChild * modelC = *childsIterator;
                if(m->count(modelC->atomic->path.toStdString())>0){
                        string pdfile = modelC->atomic->path.toStdString();
                        string mofile = (*m)[pdfile];
                        (*log) << "PowerDevs File " << pdfile << " to " << mofile << endl;
                        AST_StoredDefinition sd = parseFile(mofile, &r);
                        st->insert(st->end(), *(sd->models()->begin()));
                }else{
                        st->insert(st->end(), NULL);
                }
        }
        return st;
}
}
