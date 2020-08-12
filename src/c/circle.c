
#include "c/circle.h"

cIndices_s c_circle_og(cCircle_s a, const cCircle_s *b, int n, int ignore) {
    cIndices_s res = {0};
    for(int i=0; i<n; i++) {
    	if(i==ignore)
    	    continue;
    	if(c_circle_oo(a, b[i]))
    	    res.data[res.num++] = i;
    }
    return res;	
}
