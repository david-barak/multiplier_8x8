#ifndef CSA_H
#define CSA_H

#include <systemc.h>

void make_csa();
void print_csa(int c, bool a, bool b, bool carryin, bool sum, bool carryout);

SC_MODULE(csa) {
    sc_in<bool> clk, a_in, b_in, sum_in, c_in;
    sc_out<bool> sum_out, c_out;

    void csa_method();

    SC_CTOR(csa) {
        SC_METHOD(csa_method);
        dont_initialize();
        sensitive << clk.pos();
    }
};

#endif