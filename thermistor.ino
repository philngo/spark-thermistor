#include <math.h>

int analogvalue = 0;
double v_in = 3.3;
double v_out = 0.0;
double r_2 = 10000.0;
double resistance = 0.0;
double temperature = 100.0;
double a = 0.0;
double b = 0.0;
double c = 0.0;

void setup()
{
    double t1 = 273.15;
    double t2 = 298.15;
    double t3 = 323.15;

    double r1 = 500.;
    double r2 = 300.;
    double r3 = 200.;

    double params[3] = {0.,0.,0.};
    parameters(t1,t2,t3,r1,r2,r3,params);

    a = params[0];
    b = params[1];
    c = params[2];

    Spark.variable("analogvalue", &analogvalue, INT);
    Spark.variable("v_out", &v_out, DOUBLE);
    Spark.variable("resistance", &resistance, DOUBLE);
    Spark.variable("temperature", &temperature, DOUBLE);
    pinMode(A0, INPUT);
}

void loop()
{
    analogvalue = analogRead(A0);

    v_out = 3.3 * (analogvalue / 4095.0);

    resistance = r_2 * ((v_in/v_out) - 1.0);

    temperature = 1/(a + b*log(resistance) + c*pow(log(resistance),3));
    delay(200);
}

double * parameters(double t1,double t2, double t3, double r1, double r2, double r3, double * params)
{

    double l1 = 1. / log(r1);
    double l2 = 1. / log(r2);
    double l3 = 1. / log(r3);

    double y1 = 1. / t1;
    double y2 = 1. / t2;
    double y3 = 1. / t3;

    double g2 = (y2 - y1)/(l2 - l1);
    double g3 = (y3 - y1)/(l3 - l1);

    double C = ((g3 - g2)/(l3 - l2))/(l1 + l2 + l3);
    double B = g2 - C*pow(l1 + l2,2);
    double A = y1 - (B + pow(l1,2)*C)*l1;

    params[0] = A;
    params[1] = B;
    params[2] = C;
    return params;
}
