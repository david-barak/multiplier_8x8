#ifndef MUL_H
#define MUL_H

#include <systemc.h>
#include <cpa.h>
#include <csa.h>

SC_MODULE(mul) {

    const static unsigned int bitL = 8;
    const static unsigned int outL = bitL * 2;

    sc_in<bool> clk;
    sc_in<sc_uint<bitL>> A, B;
    sc_out<sc_uint<outL>> P;

    csa *csaArray[bitL][bitL];
    cpa *cpaArray[bitL];

    sc_signal<bool> csa_a_in[bitL], csa_b_in[bitL];
    sc_signal<bool> csa_c_out[bitL][bitL], csa_sum_out[bitL][bitL], csaA[bitL], csaB[bitL];
    sc_signal<bool> cpa_c_out[bitL], cpa_sum_out[bitL];
    sc_signal<bool> low;
    
    void getProduct();
    void mulInit();

    SC_CTOR(mul) {
        unsigned int i, j;
        for (i = 0; i < bitL; i++) {
            cpaArray[i] = new cpa("cpa");

            for (j = 0; j < bitL; j++) {
                csaArray[i][j] = new csa("csa"); 
            }
        }

        for (i = 0; i < bitL; i++) {
            for (j = 0; j < bitL; j++) {
                csaArray[i][j]->clk(clk);
                csaArray[i][j]->a_in(csa_a_in[j]);
                csaArray[i][j]->b_in(csa_b_in[i]);
                csaArray[i][j]->c_out(csa_c_out[i][j]);
                csaArray[i][j]->sum_out(csa_sum_out[i][j]);
                
                if (i == 0) {
                    csaArray[i][j]->sum_in(low);
                    csaArray[i][j]->c_in(low);
                } else {
                    if (j == bitL - 1) {
                        csaArray[i][j]->sum_in(low);
                    } else {
                        csaArray[i][j]->sum_in(csa_sum_out[i - 1][j + 1]);
                    }
                    csaArray[i][j]->c_in(csa_c_out[i - 1][j]);
                }
            }
        }

        for (j = 0; j < bitL; j++) {
            cpaArray[j]->clk(clk);
            cpaArray[j]->a_in(csa_sum_out[bitL - 1][j + 1]);
            cpaArray[j]->b_in(csa_c_out[bitL - 1][j]);
            cpaArray[j]->c_out(cpa_c_out[j]);
            cpaArray[j]->sum_out(cpa_sum_out[j]);

            if (j == 0 || j == bitL - 1) {
                cpaArray[j]->c_in(low);
            } else {
                cpaArray[j]->c_in(cpa_c_out[j-1]);
            }
        }

        SC_METHOD(getProduct);
        sensitive << clk.neg();
    }
};
#endif
