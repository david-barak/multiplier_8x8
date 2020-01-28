#ifndef MUL_H
#define MUL_H

#include <systemc.h>
#include "csa.h"
#include "cpa.h"

void make_mul();

SC_MODULE(mul) {
    // Declare Constants
    static const int bitL = 8;
    static const int outL = 2*bitL;

    // Declare Input and Output Ports
    sc_in<bool> clk, A[bitL], B[bitL];
    sc_out<bool> P[outL];

    // Declare CSA and CPA Arrays
    csa *csaArray[bitL][bitL];
    cpa *cpaArray[bitL];

    // Declare Signals
    sc_signal<bool> low, high;
    sc_signal<bool> csa_a_in[bitL], csa_b_in[bitL];
    sc_signal<bool> csa_sum_out[bitL][bitL], csa_c_out[bitL][bitL];
    sc_signal<bool> cpa_sum_out[bitL], cpa_c_out[bitL];
    sc_signal<bool> p_out[outL];

    // Loop Control Variables
    unsigned int i, j;

    void getProduct() {
        for (i = 0; i < outL; i++) {
            P[i].write(p_out[i]);
        }
    }

    void mulInit() {
        for (i = 0; i < bitL; i++) {
            csa_a_in[i].write(A[i].read());
            csa_b_in[i].write(B[i].read());
        }

        low.write(0);
        high.write(1);
    }

    SC_CTOR(mul) {
        
        // Initialize all of the CSA and CPA Modules
        for (i = 0; i < bitL; i++) {
            cpaArray[i] = new cpa("cpa");

            for (j = 0; j < bitL; j++) {
                csaArray[i][j] = new csa("csa");
            }
        }

        for (i = 0; i < bitL; i++) {
            for (j = 0; j < bitL; j++) {
                // Map Clk, A and B for each CSA
                csaArray[i][j]->clk(clk);
                csaArray[i][j]->a_in(csa_a_in[i]);
                csaArray[i][j]->b_in(csa_b_in[i]);

                /*
                * Map CSA Sum_In to low if it is in the first row or last column of the array,
                * Otherwise the Sum_In is mapped to the Sum_Out of another CSA which exists in the row before and column after.
                */
                if (j == 0 || i == bitL-1) {
                    csaArray[i][j]->sum_in(low);  
                } else {
                    csaArray[i][j]->sum_in(csa_sum_out[i+1][j-1]);
                }

                /*
                * Map CSA Carry In to low if it is in the first row, otherwise to the carry out of the CSA before it.
                */
                if (j == 0) {
                    csaArray[i][j]->c_in(low);
                } else {
                    csaArray[i][j]->c_in(csa_c_out[i][j-1]);
                }                

                /*
                * Map CSA Sum_Out to the product if it exists in the first common, otherwise to the appropriate signal.
                */
                if (i == 0) {
                    csaArray[i][j]->sum_out(p_out[j]);
                } else {
                    csaArray[i][j]->sum_out(csa_sum_out[i][j]);
                }

                // Map CSA Carry Out
                csaArray[i][j]->c_out(csa_c_out[i][j]);
            }

            cpaArray[i]->clk(clk);
            cpaArray[i]->c_out(cpa_c_out[i]);

            if (i == bitL-1) {
                cpaArray[i]->a_in(csa_c_out[i][bitL-1]);
                cpaArray[i]->b_in(cpa_c_out[i-1]);
                cpaArray[i]->c_in(low);
            } else {
                cpaArray[i]->a_in(csa_sum_out[i+1][bitL-1]);
                cpaArray[i]->b_in(csa_c_out[i][bitL-1]);
                if (i == 0) {
                    cpaArray[i]->c_in(low);
                } else {
                    cpaArray[i]->c_in(cpa_c_out[i-1]);
                }
            }

            cpaArray[i]->sum_out(p_out[bitL+i]);
        }

        SC_METHOD(getProduct);
        //dont_initialize();
        sensitive << clk.neg();


    }
};

#endif