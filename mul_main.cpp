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

void startMUL() {
    sc_trace_file *tf;

    sc_signal<sc_uint<8>> a, b; 
    sc_signal<sc_uint<16>> res;

    sc_clock clk("clk", 10, SC_NS, 0.5);

    mul mul("mul");
    
    mul.clk(clk);
    mul.A(a);
    mul.B(b);
    mul.P(res);

    tf = sc_create_vcd_trace_file("mul_trace");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, clk, "clk");
    sc_trace(tf, a, "a");
    sc_trace(tf, b, "b");
    sc_trace(tf, res, "res");

    cout << endl << endl << "Beginning Testing of the Multiplier Module..." << endl;
    a.write(1);
    b.write(1);
    sc_start(20, SC_NS);
    cout << "A: " << a << " B: " << b << " Result: " << res << endl;

    a.write(75);
    b.write(100);
    sc_start(20, SC_NS);
    cout << "A: " << a << " B: " << b << " Result: " << res << endl;

    a.write(63);
    b.write(63);
    sc_start(20, SC_NS);
    cout << "A: " << a << " B: " << b << " Result: " << res << endl;

    a.write(255);
    b.write(255);
    sc_start(20, SC_NS);
    cout << "A: " << a << " B: " << b << " Result: " << res << endl;
    sc_close_vcd_trace_file(tf);
    
}