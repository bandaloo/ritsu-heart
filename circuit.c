#include <stdio.h>
#include <math.h>

/*int main(void){
    
//    double M_PI = 3.1415926535;
    
    double Vlv = 100.0;
    double Pa = 80.0;
    
    double Pv = 10.0;
    double Po = 10.0;
    double Rv = 0.01;
    double R0 = 0.005;
    double R = 1.0;
    double C = 5.0;
    
    double maxtime = 1.0;
    double dt = 0.001;
    double trr = 1.0;
    double ts;
    double es = 1.0;
    double ed = 0.1;
    double e;
    
    int i;
    int maxstep;
    double t;

    ts = 0.3 * sqrt(trr);

    maxstep = maxtime / dt;
    printf("time Vlv Pa\n");
    
    for (i = 0; i < maxstep; i++) {
        
        // E(t)の計算
        t = fmod(i * dt, trr);
        if (t < ts) {
            e = ed + (es - ed)/2.0 * (1.0 - cos(M_PI * t / (0.3 * sqrt(trr))));
        } else if (t < (ts * 3.0 / 2.0)) {
            e = ed + (es - ed)/2.0 * (1.0 + cos(2.0 * M_PI * (t - 0.3 * sqrt(trr)) / (0.3 * sqrt(trr))));
        } else {
            e = ed;
        }
        
        double Plv = e * Vlv;
        
        // fv, f1, f2
        double fv = (Pv - Plv) / Rv;
        double f1 = (Plv - Pa) / R0;
        double f2 = (Pa - Po) / R;
        
        // Vlv, Pa
        Vlv += (fv - f1) * dt;
        Pa += (f1 - f2) * e * dt;
    
        printf("%lf %lf %lf\n", t, Vlv, Pa);
     }
}*/
