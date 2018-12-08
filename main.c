/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 * Time-stamp: <Tue Jul 17 16:02:29 EDT 2018 ferguson>
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"
#include "math.h"

/**
 * Two AND gates connected to make a 3-input AND circuit.
 */




static char* b2s(bool b) {
    return b ? "T" : "F";
}


static void test3input(Circuit* circuit, bool in0, bool in1, bool in2) {
    Circuit_setInput(circuit, 0, in0);
    Circuit_setInput(circuit, 1, in1);
    Circuit_setInput(circuit, 2, in2);
    Circuit_update(circuit);
    bool out0 = Circuit_getOutput(circuit, 0);
    printf("%s %s %s -> %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0));
}
static void test2input(Circuit* circuit, bool in0, bool in1) {
    Circuit_setInput(circuit, 0, in0);
    Circuit_setInput(circuit, 1, in1);
    Circuit_update(circuit);
    bool out0 = Circuit_getOutput(circuit, 0);
    printf("%s %s -> %s\n", b2s(in0), b2s(in1), b2s(out0));
}
static void testAdder(Circuit* circuit, bool in0, bool in1, bool in2) {
    Circuit_setInput(circuit, 0, in0);
    Circuit_setInput(circuit, 1, in1);
    Circuit_setInput(circuit, 2, in2);
    Circuit_update(circuit);
    bool out0 = Circuit_getOutput(circuit, 0);
    bool out1 = Circuit_getOutput(circuit, 1);
    printf("%s %s %s -> z: %s d: %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0), b2s(out1));
}
static bool* numToBool(int num, int inputs){
    bool *set = (bool*) malloc(sizeof(bool)*3);
    bool a;
    bool b;
    bool c;
    if (inputs == 2){
        if(num%2 ==0){
            a = false;
        }
        else {
            a = true;
        }
        if(num > 2){
            b = false;
        }
        else{
            b = true;
        }
        set[0] = a;
        set[1] = b;
    }
    if(inputs == 3){
        if(num<5){
            a = false;
        }
        else {
            a = true;
        }
        if(num==3 || num == 4 || num == 7|| num ==8){
            b = true;
        }
        else{
            b = false;
        }
        if(num%2 ==0){
            c = true;
        }
        else{
            c = false;
        }
        set[0] = a;
        set[1] = b;
        set[2] = c;
    }
    return set;
}
static void testCircuit(Circuit* circuit){
    double inputs = Circuit_numInputs(circuit);
    if(inputs==2){
        for(int i =1; i<5; i++){
            bool* set = numToBool(i, 2);
            test2input(circuit, set[0], set[1]);
            free(set);
        }
    }
    else if(inputs ==3 && Circuit_numOutputs(circuit) == 2){
        for(int i =1; i<9; i++){
            bool* set = numToBool(i, 3);
            testAdder(circuit, set[0], set[1], set[2]);
            free(set);
        }
    }
    else if (inputs == 3){
        for(int i =1; i<9; i++){
            bool* set = numToBool(i, 3);
            test3input(circuit, set[0], set[1], set[2]);
            free(set);
        }
    }
}
static Circuit* first_circuit(){
    Boolean* x = new_Boolean(false);
    Boolean* y = new_Boolean(false);
    Boolean* z = new_Boolean(false);
    Boolean** inputs = new_Boolean_array(3);
    inputs[0] = x;
    inputs[1] = y;
    inputs[2] = z;


    Boolean* out = new_Boolean(false);
    Boolean** outputs = new_Boolean_array(1);
    outputs[0] = out;

    Gate* A1 = new_AndGate();
    Gate* A2 = new_AndGate();
    Gate* N1 = new_Inverter();
    Gate* O1 = new_OrGate();
    Gate** gates = new_Gate_array(4);
    gates[0] = N1;
    gates[1] = A1;
    gates[2] = A2;
    gates[3] = O1;
    Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 4, gates);

    Circuit_connect(circuit, y, Gate_getInput(N1, 0));
    Circuit_connect(circuit, x, Gate_getInput(A1, 0));
    Circuit_connect(circuit, z, Gate_getInput(A2, 0));
    Circuit_connect(circuit, Gate_getOutput(N1), Gate_getInput(A1, 1));
    Circuit_connect(circuit, y, Gate_getInput(A2, 1));
    Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(O1, 0));
    Circuit_connect(circuit, Gate_getOutput(A2), Gate_getInput(O1, 1));
    Circuit_connect(circuit, Gate_getOutput(O1), out);
    return circuit;
}

static Circuit* second_circuit(){
    Boolean* x = new_Boolean(false);
    Boolean* y = new_Boolean(false);
    Boolean* z = new_Boolean(false);
    Boolean** inputs = new_Boolean_array(3);
    inputs[0] = x;
    inputs[1] = y;
    inputs[2] = z;

    Boolean* out = new_Boolean(false);
    Boolean** outputs = new_Boolean_array(1);
    outputs[0] = out;

    Gate* A1 = new_AndGate();
    Gate* A2 = new_AndGate();
    Gate* N1 = new_Inverter();
    Gate* N2 = new_Inverter();
    Gate* N3 = new_Inverter();
    Gate* N4 = new_Inverter();
    Gate* O1 = new_OrGate();
    Gate** gates = new_Gate_array(7);
    gates[0] = N1;
    gates[1] = A1;
    gates[2] = A2;
    gates[3] = O1;
    gates[4] = N2;
    gates[5] = N3;
    gates[6] = N4;
    Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 7, gates);

    Circuit_connect(circuit, y, Gate_getInput(N1, 0));
    Circuit_connect(circuit, x, Gate_getInput(A1, 0));
    Circuit_connect(circuit, z, Gate_getInput(A2, 0));
    Circuit_connect(circuit, Gate_getOutput(N1), Gate_getInput(A1, 1));
    Circuit_connect(circuit, y, Gate_getInput(A2, 1));
    Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(N2, 0));
    Circuit_connect(circuit, Gate_getOutput(A2), Gate_getInput(N3, 0));
    Circuit_connect(circuit, Gate_getOutput(N3), Gate_getInput(O1, 0));
    Circuit_connect(circuit, Gate_getOutput(N2), Gate_getInput(O1, 1));
    Circuit_connect(circuit, Gate_getOutput(O1), Gate_getInput(N4, 0));
    Circuit_connect(circuit, Gate_getOutput(N4), out);
    return circuit;
}

static Circuit* third_circuit(){
    Boolean* x = new_Boolean(false);
    Boolean* y = new_Boolean(false);
    Boolean** inputs = new_Boolean_array(2);
    inputs[0] = x;
    inputs[1] = y;

    Boolean* out = new_Boolean(false);
    Boolean** outputs = new_Boolean_array(1);
    outputs[0] = out;

    Gate* A1 = new_AndGate();
    Gate* A2 = new_AndGate();
    Gate* N1 = new_Inverter();
    Gate* N2 = new_Inverter();
    Gate* O1 = new_OrGate();
    Gate** gates = new_Gate_array(5);
    gates[0] = N1;
    gates[1] = A1;
    gates[2] = A2;
    gates[3] = O1;
    gates[4] = N2;
    Circuit *circuit = new_Circuit(2, inputs, 1, outputs, 5, gates);
    Circuit_connect(circuit, x, Gate_getInput(N1, 0));
    Circuit_connect(circuit, y, Gate_getInput(N2, 0));
    Circuit_connect(circuit, x, Gate_getInput(A1, 0));
    Circuit_connect(circuit, y, Gate_getInput(A1, 1));
    Circuit_connect(circuit, Gate_getOutput(N1), Gate_getInput(A2, 0));
    Circuit_connect(circuit, Gate_getOutput(N2), Gate_getInput(A2, 1));
    Circuit_connect(circuit, Gate_getOutput(A2), Gate_getInput(O1, 0));
    Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(O1, 1));
    Circuit_connect(circuit, Gate_getOutput(O1), out);
    return circuit;
}
static Circuit* adder_circuit(){
    Boolean* x = new_Boolean(false);
    Boolean* y = new_Boolean(false);
    Boolean* c = new_Boolean(false);
    Boolean** inputs = new_Boolean_array(3);
    inputs[0] = x;
    inputs[1] = y;
    inputs[2] = c;

    Boolean* z = new_Boolean(false);
    Boolean* d = new_Boolean(false);
    Boolean** outputs = new_Boolean_array(2);
    outputs[0] = z;
    outputs[1] = d;

    Gate* A1 = new_AndGate();
    Gate* A2 = new_AndGate();
    Gate* xO1 = new_XORGate();
    Gate* xO2 = new_XORGate();
    Gate* O3 = new_OrGate();

    Gate** gates = new_Gate_array(5);
    gates[0] = xO2;
    gates[1] = xO1;
    gates[2] = A1;
    gates[3] = A2;
    gates[4] = O3;

    Circuit *circuit = new_Circuit(3, inputs, 2, outputs, 5, gates);
    Circuit_connect(circuit, x, Gate_getInput(xO1, 0));
    Circuit_connect(circuit, y, Gate_getInput(xO1, 1));

    Circuit_connect(circuit, c, Gate_getInput(xO2, 0));
    Circuit_connect(circuit, Gate_getOutput(xO1), Gate_getInput(xO2, 1));

    Circuit_connect(circuit, Gate_getOutput(xO2), z);

    Circuit_connect(circuit, x, Gate_getInput(A1, 0));
    Circuit_connect(circuit, y, Gate_getInput(A1, 1));

    Circuit_connect(circuit, Gate_getOutput(xO1), Gate_getInput(A2, 0));
    Circuit_connect(circuit, c, Gate_getInput(A2, 1));

    Circuit_connect(circuit, Gate_getOutput(A2), Gate_getInput(O3, 0));
    Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(O3, 1));
    Circuit_connect(circuit, Gate_getOutput(O3), d);

    return circuit;
}

int main() {
	Circuit* circuitOne = first_circuit();
	printf("The first circuit:\n");
	Circuit_dump(circuitOne);
	printf("\n");
	printf("Testing all inputs: \n");
	testCircuit(circuitOne);
	Circuit_free(circuitOne);

    Circuit* circuitTwo = second_circuit();
    printf("\n");
    printf("The second circuit:\n");
    Circuit_dump(circuitTwo);
    printf("\n");
    printf("Testing all inputs: \n");
    testCircuit(circuitTwo);
    Circuit_free(circuitTwo);


    printf("\n");

    Circuit* circuitThree = third_circuit();
    printf("The third circuit:\n");
    Circuit_dump(circuitThree);
    printf("\n");
    printf("Testing all inputs: \n");
    testCircuit(circuitThree);
    Circuit_free(circuitThree);
    printf("\n");

    Circuit* adder = adder_circuit();
    printf("The adder circuit:\n");
    Circuit_dump(adder);
    printf("\n");
    printf("Testing all inputs: \n");
    testCircuit(adder);
    Circuit_free(adder);
    return 1;



}
