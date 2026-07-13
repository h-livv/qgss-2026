OPENQASM 3.0;
include "stdgates.inc";
qubit[5] q;
bit[0] c1;
h q[2];
cx q[2], q[1];
cx q[2], q[3];
cx q[1], q[0];
cx q[3], q[4];
