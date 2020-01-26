#include "mux_main.h"

int sc_main(int argc, char* argv[]) {
    if (strcmp(argv[0], "./mux.x") == 0) {
        //make_cpa();
        make_csa();
    } else if (strcmp(argv[1], "-h") == 0) {
        cout << "Usage: ./alu.x" << endl;
        return 1;
    }else {
        cout << "For help please enter: ./mux -h" << endl;
        return 1;
    }

    return 0;
}

