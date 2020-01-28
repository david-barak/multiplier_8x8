#include "mul_main.h"
#include <cmath>

int sc_main(int argc, char* argv[]) {
    if (strcmp(argv[0], "./mul.x") == 0) {
        //make_cpa();
        //make_csa();
        startMUL();
    } else if (strcmp(argv[1], "-h") == 0) {
        cout << "Usage: ./mul.x" << endl;
        return 1;
    }else {
        cout << "For help please enter: ./mul -h" << endl;
        return 1;
    }

    return 0;
}

int boolToInt(sc_signal<bool> arrayIn[], int length) {
    int res = 0;
    int tmp = 0;

    unsigned int i = 0;
    for (i = 0; i < length; i++) {
        tmp = arrayIn[i];
        res += tmp*pow(2, i);
    }

    return res;
}

void startMUL() {
    sc_trace_file *tf;

    sc_signal<bool> a[8], b[8], res[16];
    int anum, bnum, resnum;

    sc_clock clk("clk", 5, SC_NS, 0.5);

    mul mul("mul");
    
    unsigned int i, j;
    mul.clk(clk);

    for(i = 0; i < 8; i ++) {
        mul.A[i](a[i]);
        mul.B[i](b[i]);
    }

    for (i = 0; i < 16; i++) {
        mul.P[i](res[i]);
    }

    tf = sc_create_vcd_trace_file("mul_trace");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, clk, "clk");

    sc_trace(tf, a, "a");
    sc_trace(tf, b, "b");
    sc_trace(tf, res, "res");

    int time = 150;
    for (i = 0; i < 8; i++) {
        if (i == 1) {
            a[i].write(1);
            b[i].write(1);
        } else {
            a[i].write(0);
            b[i].write(0);
        }
    }

    
    mul.mulInit();
    for (i = 0; i < time; i++) {
        
        sc_start(1, SC_NS);
       
    }

     mul.getProduct();

    anum = boolToInt(a, 8);
    bnum = boolToInt(b, 8);
    resnum = boolToInt(res, 16);
    /*
    cout << "A: ";
    for (i = 0; i < 8; i++) {
        cout << a[i];
    }

    cout << endl << "B: ";
    for (i = 0; i < 8; i++) {
        cout << b[i];
    }

    cout << endl << "Result: ";
    for (i = 0; i < 16; i++) {
        cout << res[i];
    }
    */
    cout << endl;
    cout << "A: " << anum << " B: " << bnum << " Result: " << resnum << endl;
}