int H = A0;
int C = A1;
int D = A2;
int E = A3;
int F = A4;
int G = A5;
int A = A6;
int H1= A7;
int C1= A8;
int D1= A9;
int SPK = 3;
int nh, nc, nd, ne, nf, ng, na, nh1, nc1;

void setup() {
    Serial.begin(9600);
 pinMode(H, INPUT);
 pinMode(C, INPUT);
 pinMode(D, INPUT);
 pinMode(E, INPUT);
 pinMode(F, INPUT);
 pinMode(G, INPUT);
 pinMode(A, INPUT);
 pinMode(H1, INPUT);
 //pinMode(C1, INPUT); 
pinMode(SPK, OUTPUT);
  }

void loop() {

nh= analogRead(H);
if (nh < 900)
tone (SPK, 123, 20);
Serial.println(nh);

nc= analogRead(C);
if (nc < 900)
tone (SPK, 131, 20);

nd= analogRead(D); 
if (nd < 900)
tone (SPK, 147, 20);

ne= analogRead(E);
if (ne < 900)
tone (SPK, 165, 20);

nf= analogRead(F);
if (nf < 900)
tone (SPK, 175, 20);

ng= analogRead(G);
if (ng < 900)
tone (SPK, 196, 20);

na= analogRead(A);
if (na < 900)
tone (SPK, 220, 20);

nh1= analogRead(H1);
if (nh1 < 900)
tone (SPK, 247, 20);

nc1= analogRead(C1);
if (nc1 < 900)
tone (SPK, 262, 20);

nc1= analogRead(D1);
if (nc1 < 900)
tone (SPK, 278, 20);

} 
