#include <iostream>
using namespace std;


#define AND   1
#define OR    2
#define NOT   3
#define NAND  4
#define NOR   5
#define XOR   6


int evalGate(int type, int a, int b)
{


    if (type == AND)   return a && b;
    if (type == OR)    return a || b;
    if (type == NOT)   return !a;
    if (type == NAND)  return !(a && b);
    if (type == NOR)   return !(a || b);

    if (type == XOR)   return (a && !b) || (!a && b);
    return 0;


}


int evalCircuit(int inputs[],
                     int gateType[], int in1[], int in2[],
                int gates)
{
    int gateOut[10];

    for (int i = 0; i < gates; i++)
    {
        int a = (in1[i] < 10) ? inputs[in1[i]] : gateOut[in1[i] - 10];
        int b = 0;

        if (gateType[i] != NOT)
            b = (in2[i] < 10) ? inputs[in2[i]] : gateOut[in2[i] - 10];

        gateOut[i] = evalGate(gateType[i], a, b);
    }

    return gateOut[gates - 1];
}

void truthTable(int gateType[], int in1[], int in2[],
                int gates,
                bool &all0, bool &all1)
{
    all0 = true;
    all1 = true;

    cout << "A B C | F\n";


    for (int A = 0; A <= 1; A++)
        for (int B = 0; B <= 1; B++)
            for (int C = 0; C <= 1; C++)
            {
                int inputs[3] = {A, B, C};
                int F = evalCircuit(inputs, gateType, in1, in2, gates);

                cout << A << " " << B << " " << C << " | " << F << endl;

                if (F == 1) all0 = false;
                if (F == 0) all1 = false;
            }
}


void findSatisfyingInputs(int gateType[], int in1[], int in2[],
                                                                int gates, string circuitName)
{
    cout << "\nSatisfying inputs for " << circuitName << " circuit:\n";

    bool foundAny = false;

    for (int A = 0; A <= 1; A++)
        for (int B = 0; B <= 1; B++)
            for (int C = 0; C <= 1; C++)
            {
                int inputs[3] = {A, B, C};
                int output = evalCircuit(inputs, gateType, in1, in2, gates);

                if (output == 1)
                {
                    cout << "  A=" << A << " B=" << B << " C=" << C << endl;
                    foundAny = true;
                }
            }

    if (!foundAny)
        cout << "  No satisfying inputs (UNSATISFIABLE)\n";
}

int main()
{
    int gates1, gates2;
    int gateType1[10], in1_1[10], in2_1[10];
    int gateType2[10], in1_2[10], in2_2[10];

    cout << "Gate code:\n";
    cout << "1=AND  2=OR  3=NOT  4=NAND  5=NOR  6=XOR\n\n";

    bool repeat;


    do
    {
        repeat = false;


        cout << "Original circuit     number of gates: ";
        cin >> gates1;

        for (int i = 0; i < gates1; i++)
        {
            cout << "Gate " << i << " type: ";
            cin >> gateType1[i];

            cout << "Input 1 (0=A,1=B,2=C,10+=gate): ";
            cin >> in1_1[i];

            if (gateType1[i] != NOT)
            {
                cout << "Input 2: ";
                cin >> in2_1[i];
            }
        }


        cout << "\nSimplified circuit    number of gates: ";
        cin >> gates2;

        for (int i = 0; i < gates2; i++)
        {
            cout << "Gate " << i << " type: ";
            cin >> gateType2[i];

            cout << "Input 1 (0=A,1=B,2=C,10+=gate): ";
            cin >> in1_2[i];

            if (gateType2[i] != NOT)
            {
                cout << "Input 2: ";
                cin >> in2_2[i];
            }
        }

        bool all0_1, all1_1, all0_2, all1_2;


        cout << "\nOriginal Circuit \n";
        truthTable(gateType1, in1_1, in2_1, gates1, all0_1, all1_1);

        cout << "\n Simplified Circuit \n";
        truthTable(gateType2, in1_2, in2_2, gates2, all0_2, all1_2);


        bool equivalent = true;
        for (int A = 0; A <= 1; A++)
            for (int B = 0; B <= 1; B++)
                for (int C = 0; C <= 1; C++)
                {
                    int inputs[3] = {A, B, C};
                    if (evalCircuit(inputs, gateType1, in1_1, in2_1, gates1) !=
                        evalCircuit(inputs, gateType2, in1_2, in2_2, gates2))
                        equivalent = false;
                }

        cout << "\nEquivalence: " << (equivalent ? "YES\n" : "NO\n");


        findSatisfyingInputs(gateType1, in1_1, in2_1, gates1, "ORIGINAL");
        findSatisfyingInputs(gateType2, in1_2, in2_2, gates2, "SIMPLIFIED");


        if (all0_1 || all1_1)
        {

            cout << "  Original circuit is ";
            if (all0_1) {
                cout << "UNSATISFIABLE (always 0)";
            } else {
                cout << "TAUTOLOGY (always 1)";
            }


            cout << "\nPlease change ONE gate and re-enter BOTH circuits.\n";
            repeat = true;
        }
        else
        {

            cout << "  Original circuit is SATISFIABLE\n";

        }

    } while (repeat);


    return 0;
}