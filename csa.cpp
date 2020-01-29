#include "csa.h"

void csa :: csa_method() {
    bool a, b, andab, carryin, sumin, carryout, sumout;

    // Read Inputs
    a = a_in.read() & b_in.read();
    b = sum_in.read();
    carryin = c_in.read();
    
    // CSA Logic
    sumout = (a ^ b) ^ carryin;
    carryout = (a & b) | (carryin & (a ^ b)); 

    // Write Outputs 
    sum_out.write(sumout);
    c_out.write(carryout);
}

void print_csa(int c, bool a, bool b, bool sumin, bool carryin, bool sumout, bool carryout) {
    if (c < 10){
        cout << "|   " << c << "  | " << a << " | " << b << " |  " << carryin << "  |   " << sumin << "    |   " << carryout << "   |    "  << sumout << "    |" << endl;
    } else {
        cout << "|  " << c << "  | " << a << " | " << b << " |  " << carryin << "  |   " << sumin << "    |   " << carryout << "   |    "  << sumout << "    |" << endl;
    }

}

void make_csa() {
    sc_trace_file *tf;
    sc_signal<bool> a, b, carryin, sumin, sumout, carryout;

    // Create System Clock
    sc_clock clk("clk", 10, SC_NS, 0.5);

    // Create CSA Module
    csa csa("csa");

    // Map Signals to Module
    csa.clk(clk);
    csa.a_in(a);
    csa.b_in(b);
    csa.c_in(carryin);
    csa.sum_in(sumin);
    csa.sum_out(sumout);
    csa.c_out(carryout);

    // Create Trace File and Map Signals
    tf = sc_create_vcd_trace_file("csa_trace");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, a, "A");
    sc_trace(tf, b, "B");
    sc_trace(tf, sumin, "Sum_In");
    sc_trace(tf, carryin, "Carry_In");
    sc_trace(tf, sumout, "Sum_Out");
    sc_trace(tf, carryout, "Carry_Out");

    // Begin Testing
    cout << "Beginning Test of the Carry Save Adder (CSA)..." << endl << endl;
    
    cout << "| Case | A | B | Cin | Sum In | Cout  | Sum Out |" << endl;
    //Case 1: A = 0, B = 0, Carry In = 0, Sum In = 0
    a.write(0);
    b.write(0);
    carryin.write(0);
    sumin.write(0);
    sc_start(10, SC_NS);
    print_csa(1,  a, b, sumin, carryin, sumout, carryout);

    //Case 2: A = 0, B = 0, Carry In = 0, Sum In = 1
    a.write(0);
    b.write(0);
    carryin.write(0);
    sumin.write(1);
    sc_start(10, SC_NS);
    print_csa(2,  a, b, sumin, carryin, sumout, carryout);

    //Case 3: A = 0, B = 0, Carry In = 1, Sum In = 0
    a.write(0);
    b.write(0);
    carryin.write(1);
    sumin.write(0);
    sc_start(10, SC_NS);
    print_csa(3,  a, b, sumin, carryin, sumout, carryout);

    //Case 4: A = 0, B = 0, Carry In = 1, Sum In = 1
    a.write(0);
    b.write(0);
    carryin.write(1);
    sumin.write(1);
    sc_start(10, SC_NS);
    print_csa(4,  a, b, sumin, carryin, sumout, carryout);

    //Case 5: A = 0, B = 1, Carry In = 0, Sum In = 0
    a.write(0);
    b.write(1);
    carryin.write(0);
    sumin.write(0);
    sc_start(10, SC_NS);
    print_csa(5,  a, b, sumin, carryin, sumout, carryout);

    //Case 6: A = 0, B = 1, Carry In = 0, Sum In = 1
    a.write(0);
    b.write(1);
    carryin.write(0);
    sumin.write(1);
    sc_start(10, SC_NS);
    print_csa(6,  a, b, sumin, carryin, sumout, carryout);

    //Case 7: A = 0, B = 1, Carry In = 1, Sum In = 0
    a.write(0);
    b.write(1);
    carryin.write(1);
    sumin.write(0);
    sc_start(10, SC_NS);
    print_csa(7,  a, b, sumin, carryin, sumout, carryout);

    //Case 8: A = 0, B = 1, Carry In = 1, Sum In = 1
    a.write(0);
    b.write(1);
    carryin.write(1);
    sumin.write(1);
    sc_start(10, SC_NS);
    print_csa(8,  a, b, sumin, carryin, sumout, carryout);

    //Case 9: A = 1, B = 0, Carry In = 0, Sum In = 0
    a.write(1);
    b.write(0);
    carryin.write(0);
    sumin.write(0);
    sc_start(10, SC_NS);
    print_csa(9,  a, b, sumin, carryin, sumout, carryout);

    //Case 10: A = 1, B = 0, Carry In = 0, Sum In = 1
    a.write(1);
    b.write(0);
    carryin.write(0);
    sumin.write(1);
    sc_start(10, SC_NS);
    print_csa(10,  a, b, sumin, carryin, sumout, carryout);

    //Case 11: A = 1, B = 0, Carry In = 1, Sum In = 0
    a.write(1);
    b.write(0);
    carryin.write(1);
    sumin.write(0);
    sc_start(10, SC_NS);
    print_csa(11,  a, b, sumin, carryin, sumout, carryout);

    //Case 12: A = 1, B = 0, Carry In = 1, Sum In = 1
    a.write(1);
    b.write(0);
    carryin.write(1);
    sumin.write(1);
    sc_start(10, SC_NS);
    print_csa(12,  a, b, sumin, carryin, sumout, carryout);

    //Case 13: A = 1, B = 1, Carry In = 0, Sum In = 0
    a.write(1);
    b.write(1);
    carryin.write(0);
    sumin.write(0);
    sc_start(10, SC_NS);
    print_csa(13,  a, b, sumin, carryin, sumout, carryout);

    //Case 14: A = 1, B = 1, Carry In = 0, Sum In = 1
    a.write(1);
    b.write(1);
    carryin.write(0);
    sumin.write(1);
    sc_start(10, SC_NS);
    print_csa(14,  a, b, sumin, carryin, sumout, carryout);

    //Case 15: A = 1, B = 1, Carry In = 1, Sum In = 0
    a.write(1);
    b.write(1);
    carryin.write(1);
    sumin.write(0);
    sc_start(10, SC_NS);
    print_csa(15,  a, b, sumin, carryin, sumout, carryout);

    //Case 16: A = 1, B = 1, Carry In = 1, Sum In = 1
    a.write(1);
    b.write(1);
    carryin.write(1);
    sumin.write(1);
    sc_start(10, SC_NS);
    print_csa(16,  a, b, sumin, carryin, sumout, carryout);

}