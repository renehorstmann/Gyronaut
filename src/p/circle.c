
#include "p/circle.h"

pIndices_s p_circle_og(pCircle_s a, const pCircle_s *b, int n) {
    pIndices_s res = {0};
    for(int i=0; i<n; i++) {
    	if(p_circle_oo(a, b[i]))
    	    res.data[res.num++] = i;
    }
    return res;	
}


