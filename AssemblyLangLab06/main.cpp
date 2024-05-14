#include <iostream>
#include <cmath>

using namespace std;

const unsigned n = 5;
const double half = 0.5;
const double four = 4.0;
const double sixteen = 16.0;
double temp;
double temp1;

double c;
double d;
double a[n];
double y[n];

void CalculateAsm()
{
    __asm
    {
        finit
        mov esi, offset a
        mov edi, offset y
        mov ecx, n

        calculate_loop :
            fld half
            fld qword ptr[esi]
            fabs
            fmul
            fld d
            fabs
            fmul four
            fsub
            fstp temp

            fld1
            fsubr temp
            fstp temp1

            fld d
            fabs
            fadd sixteen
            fptan
            fxch
            fld c
            fmul
            fdiv temp1

            fstp qword ptr[edi]

            add esi, 8
            add edi, 8
            loop calculate_loop
    }
}



void Start() 
{
    cout << "Enter c and d (c > d): ";
    cin >> c >> d;
    if (!(c > d)) 
    {
        swap(c, d);
    }
    cout << "c = " << c << "\nd = " << d << endl;
    for (unsigned i = 0; i < n; ++i) 
    {
        cout << "Enter a[" << (i + 1) << "]: ";
        cin >> a[i];
    }
}

void PrintY() 
{
    for (unsigned i = 0; i < n; ++i) 
    {
        cout << " y[" << (i + 1) << "]: " << y[i] << endl;
    }
}

void CalculateCpp() 
{
    for (unsigned i = 0; i < n; ++i) 
    {
        y[i] = ((c * tan(d + sixteen)) / ((a[i] * half) - (four * d) - 1));
    }
}

int main() 
{
    Start();
    CalculateAsm();
    cout << "ASM\n";
    PrintY();
    CalculateCpp();
    cout << "CPP\n";
    PrintY();
    system("pause");
    return 0;
}
