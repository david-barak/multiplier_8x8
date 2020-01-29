#include "mul.h"
#include <cmath>

void mul :: mulInit() {
    low.write(0);
    unsigned int i;

    for (i = 0; i < bitL; i++) {
        csa_a_in[i].write(A.read()[i]);
        csa_b_in[i].write(B.read()[i]);
    }
}

void mul :: getProduct() {
    mulInit();
    
    int result = 0, factor = 0;
    unsigned int i;

    for (i = 0; i < outL; i++) {
        factor = pow(2, i);

        if (i < bitL) {
            result += csa_sum_out[i][0].read() * factor;
        } else {
            result += cpa_sum_out[i-bitL].read() * factor;
        }
        
    }

    P.write(result);
}

void make_mul(){ }