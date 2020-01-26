#ifndef CPA_H
#define CPA_H

#include <systemc.h>

void make_cpa();
void print_cpa(int c, bool a, bool b, bool carryin, bool sum, bool carryout);

SC_MODULE(cpa) {
    sc_in<bool> clk, a_in, b_in, c_in;
    sc_out<bool> sum_out, c_out;

    void cpa_method();

    SC_CTOR(cpa) {
        SC_METHOD(cpa_method);
        dont_initialize();
        sensitive << clk.pos();
    }
};

#endif