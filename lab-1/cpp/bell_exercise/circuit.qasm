OPENQASM 3.0;
include "stdgates.inc";
qubit[2] q;
bit[0] c1;
h q[0];
cx q[0], q[1];
x q[1];
