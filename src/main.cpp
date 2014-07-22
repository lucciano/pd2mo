#include <stdio.h>
#include <iostream>
#include <getopt.h>    
using namespace std;



int main (int argc, char* argv[]) {
    string path;
    string src_file;
    string src_outfile;

    int c;
    int digit_optind = 0;
    int aopt = 0, bopt = 0;
    char *copt = 0, *dopt = 0;
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
        case 0:
            printf ("option %s", long_options[option_index].name);
            if (optarg)
                printf (" with arg %s", optarg);
            printf ("\n");
            break;
        case '0':
        case '1':
        case '2':
            if (digit_optind != 0 && digit_optind != this_option_optind)
              printf ("digits occur in two different argv-elements.\n");
            digit_optind = this_option_optind;
            printf ("option %c\n", c);
            break;
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
            printf ("option p with value '%s'\n", optarg);
            copt = optarg;
            break;
        case 'o':
            printf ("option o with value '%s'\n", optarg);
            dopt = optarg;
            break;
        case '?':
            break;
        default:
            printf ("?? getopt returned character code 0%o ??\n", c);
        }
    }
    if (optind < argc) {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        printf ("\n");
    }
    return 0;
}
