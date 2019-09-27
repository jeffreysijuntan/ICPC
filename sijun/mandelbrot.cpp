#include <stdio.h>
#include <math.h>

int main(){
    double x, y;
    int i = 0, r;
    while(scanf("%lf %lf %d", &x, &y, &r) != EOF){
        i++;
        double t = 0, t1 = 0, t2 = 0;
        int f = 0;
        for(int j = 0; j < r; j++){
            t = t1*t1-t2*t2 + x;
            t2 = 2*t1*t2 + y;
            t1 = t;
            if(sqrt(t1*t1+t2*t2)>2.0) {
                printf("Case %d: OUT\n", i);
                f = -1;
                break;
            }
        }
        if(f == 0) printf("Case %d: IN\n", i);
    }
}
