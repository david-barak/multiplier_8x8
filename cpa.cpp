#include "cpa.h"

void cpa :: cpa_method() {
    bool a, b, carryin, carryout, sum;
    a = a_in.read();
    b = b_in.read();
    carryin = c_in.read();
    sum = carryin ^ (a ^ b);
    carryout = (a&b) | (b&carryin) | (a&carryin);   
    sum_out.write(sum);
    c_out.write(carryout);
}

void print_cpa(int c, bool a, bool b, bool carryin, bool sum, bool carryout) {
    cout << "|   " << c << "  | " << a << " | " << b << " |  " << carryin << "  |   " << carryout << "   |  "  << sum << "  |" << endl;

}

void make_cpa() {
    // Create Signals
    sc_trace_file *tf;
    sc_signal<bool> a, b, carryin, sum, carryout;

    // Create System Clock
    sc_clock clk("clk", 10, SC_NS, 0.5);

    // Create CPA Module
    cpa cpa("cpa");

    // Map Signals to Module
    cpa.clk(clk);
    cpa.a_in(a);
    cpa.b_in(b);
    cpa.c_in(carryin);
    cpa.sum_out(sum);
    cpa.c_out(carryout);

    // Create Trace File and Map Signals
    tf = sc_create_vcd_trace_file("cpa_trace");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, a, "A");
    sc_trace(tf, b, "B");
    sc_trace(tf, carryin, "Carry_In");
    sc_trace(tf, sum, "Sum");
    sc_trace(tf, carryout, "Carry_Out");

    // Begin Testing
    cout << "Beginning Test of the Carry Propogate Adder (CPA)..." << endl << endl;
    
    cout << "| Case | A | B | Cin | Cout  | Sum |" << endl;
    // Case 1: A = 0, B = 0, CIN = 0
    a.write(0);
    b.write(0);
    carryin.write(0);
    sc_start(10, SC_NS);
    print_cpa(1, a, b, carryin, sum, carryout);

    // Case 2: A = 0, B = 0, CIN = 1
    a.write(0);
    b.write(0);
    carryin.write(1);
    sc_start(10, SC_NS);
    print_cpa(2, a, b, carryin, sum, carryout);

    // Case 3 : A = 0, B = 1, CIN = 0
    a.write(0);
    b.write(1);
    carryin.write(0);
    sc_start(10, SC_NS);
    print_cpa(3, a, b, carryin, sum, carryout);

    // Case 4 : A = 0, B = 1, CIN = 1
    a.write(0);
    b.write(1);
    carryin.write(1);
    sc_start(10, SC_NS);
    print_cpa(4, a, b, carryin, sum, carryout);

    // Case 5: A = 1, B = 0, CIN = 0
    a.write(1);
    b.write(0);
    carryin.write(0);
    sc_start(10, SC_NS);
    print_cpa(5, a, b, carryin, sum, carryout);

    // Case 6: A = 1, B = 0, CIN = 1
    a.write(1);
    b.write(0);
    carryin.write(1);
    sc_start(10, SC_NS);
    print_cpa(6, a, b, carryin, sum, carryout);

    // Case 7: A = 1, B = 1, CIN = 0
    a.write(1);
    b.write(1);
    carryin.write(0);
    sc_start(10, SC_NS);
    print_cpa(7, a, b, carryin, sum, carryout);

    // Case 8: A = 1, B = 1, CIN = 1
    a.write(1);
    b.write(1);
    carryin.write(1);
    sc_start(10, SC_NS);
    print_cpa(8, a, b, carryin, sum, carryout);
    cout << endl;
}