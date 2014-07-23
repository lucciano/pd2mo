#include <stdio.h>
#include <iostream>
#include <getopt.h>    
#include <pd2mo.h>
#include <libgen.h>
using namespace std;
using namespace pd2mo;

int main (int argc, char* argv[]) {
    string path;
    string src_infile;
    string src_outfile("");

    int c;
    int digit_optind = 0;
    int aopt = 0, bopt = 0;
    
    static struct option long_options[] = {
        {"path", 1, 0, 'p'},
        {"output", 1, 0, 'o'},
        {"help", 0, 0, 'h'},
        {NULL, 0, NULL, 0}
    };
    int option_index = 0;

    while ((c = getopt_long(argc, argv, "hp:o:",
                 long_options, &option_index)) != -1) {
        int this_option_optind = optind ? optind : 1;
        switch (c) {
        case 'h':
	    cout << "Usage : " << argv[0] << " [-h|--help] "
		<< "[-p|--path=some/path] " 
		<< "[-o|--output=modelfile.mo] <modelfile.pds>"<< endl;
	    cout << "-h, --help\t\tPrint this help message"<< endl;
	    cout << "-p, --path\t\tpath with the .mo files" << endl;
	    cout << "-o, --output\t\toutput file of the modelica, by default we change the .pds extension for .mo" << endl;
	    return 0;
            break;
        case 'p':
	    path = string(optarg);
            break;
        case 'o':
	    src_outfile = string(optarg);
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
    ofstream outfile;
    if(src_outfile.compare("") == 0){
        src_outfile = src_infile;
        find_and_replace(src_outfile,".pds", ".mo");
	char * base = strdup(src_outfile.c_str());
	src_outfile = string(basename(base));
    }

    outfile.open(src_outfile.c_str());
    Pd2Mo q = Pd2Mo();
    q.transform(src_infile, &outfile, &cerr);
    outfile.close();
    return 0;
}
