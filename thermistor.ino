int analogvalue = 0;
double resistance = 0.0;
double v_in = 3.3;
double r_2 = 10000.0;
double v_out = 0.0;
double slope = -0.13;
double intercept = 145;
double temperature = 0.0;

void setup()
{
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
    temperature = (slope * resistance) + intercept;
    delay(200);
}
