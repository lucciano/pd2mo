#include <stdio.h>
#include <iostream>
#include <getopt.h>    
#include <pd2mo.h>
#include <src/flatter.h>
#include <src/mda.h>
#include <src/uda.h>
#include <src/range.h>
#include <src/prodint.h>
#include <src/if.h>
#include <pdppt/codegenerator.h>
#include <libgen.h>
using namespace std;
using namespace pd2mo;

int main (int argc, char* argv[]) {
    string path =  getFullPath() + "/data/";
    string src_infile;
    string src_outfile("");
    string logfile("");
    string flatted("");
    string mmodelica_src_outfile("");

    int c;
    int digit_optind = 0;
    int aopt = 0, bopt = 0;
    
    static struct option long_options[] = {
        {"path", 1, 0, 'p'},
        {"output", 1, 0, 'o'},
        {"flatted", 1, 0, 'f'},
        {"log", 1, 0, 'l'},
        {"mmodelica", 1, 0, 'm'},
        {"help", 0, 0, 'h'},
        {NULL, 0, NULL, 0}
    };
    int option_index = 0;

    while ((c = getopt_long(argc, argv, "hp:o:l:m:",
                 long_options, &option_index)) != -1) {
        int this_option_optind = optind ? optind : 1;
        switch (c) {
        case 'h':
	    cout << "Usage : " << argv[0] << " [-h|--help] "
		<< "[-p|--path=some/path] " 
		<< "[-l|--log=modelfile.log] " 
		<< "[-o|--output=modelfile.mo] "
		<< "[-m|--mmodelica=modelfile.mo] "
		<< "[-f|--flatted=modelfile.flatted.pds] <modelfile.pds>"<< endl;
	    cout << "-h, --help\t\tPrint this help message"<< endl;
	    cout << "-p, --path\t\tpath with the .mo files, defaults to \"" << path <<"\""<< endl;
	    cout << "-o, --output\t\toutput file of the modelica, by default we change the .pds extension to .mo" << endl;
	    return 0;
            break;
        case 'l':
            logfile = string(optarg);
            break;
        case 'p':
	    path = string(optarg);
            break;
        case 'f':
	    flatted = string(optarg);
            break;
        case 'o':
	    src_outfile = string(optarg);
            break;
        case 'm':
	    mmodelica_src_outfile = string(optarg);
            break;
        case '?':
            break;
        default:
            printf ("?? getopt returned character code 0%o ??\n", c);
        }
    }
    if (optind < argc) {

	bool first = true;
        while (optind < argc){
		if(!first){
			cerr << "to many arguments." <<endl;
			return 1;
		}
		src_infile = string(argv[optind++]);
		first = false;
	}
    }else{
	cerr << "not enough arguments." <<endl;
	return 1;
    }
    if(src_outfile.compare("") == 0){
        src_outfile = src_infile;
        find_and_replace(src_outfile,".pds", ".mo");
	char * base = strdup(src_outfile.c_str());
	src_outfile = string(basename(base));
    }
    ofstream outfile;
    outfile.open(src_outfile.c_str(), ios::trunc);

    if(mmodelica_src_outfile.compare("") == 0){
        mmodelica_src_outfile = src_outfile;
    }

    if(logfile.compare("") == 0){
        logfile = src_infile;
        find_and_replace(logfile,".pds", ".log");
	char * base = strdup(logfile.c_str());
	logfile = string(basename(base));
    }

    if(flatted.compare("") == 0){
        flatted = src_infile;
        find_and_replace(flatted,".pds", ".flatted.pds");
	char * base = strdup(flatted.c_str());
	flatted = string(basename(base));
    }

    
    modelCoupled *cm = parsePDS(QString::fromStdString(src_infile));
    modelCoupled *qm = flatter::flat(cm);
    generateCode(qm, QString::fromStdString(flatted), false, true);

    ofstream oFlogfile;
    oFlogfile.open(logfile.c_str(), ios::trunc);

    Pd2Mo q = Pd2Mo();
    q.setPath(path);
 	
    char * file = basename((char *) src_infile.c_str());
	file[strlen(file)-4] = 0;
    char * mname = strdup(file);
    //modelname.copy( src_infile.c_str(), (sizeof src_infile) - 3, 0);
    string modelname(mname); // = string(src_infile);

    cout << modelname << "....."<<  endl;


    q.transform(flatted, modelname, &outfile, &oFlogfile);
    outfile.close();

    int r = 0;
    AST_StoredDefinition sd = parseFile(src_outfile.c_str(),&r);

    mda *m = new mda();
    range *ran = new range();
    prodint *  prod = new prodint();
    If *i = new If();
    uda *u = new uda();
    outfile.open(mmodelica_src_outfile.c_str(), ios::trunc);
    outfile << m->visitClass(
		//u->visitClass(
		//ran->visitClass(
		prod->visitClass(
		i->visitClass(
			*sd->models()->begin()
				)
				)
				)
				/*))*/ << endl;

    outfile.close();

    return 0;
}
