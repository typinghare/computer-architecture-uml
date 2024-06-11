# Homework 4

## Contact

> Name: Zhuojian Chen (James)  
> ID: 02151380  
> Section: 051  
> Email: Zhuojian_Chen@student.uml.edu

## Description

Degree of Success: 100%

First of all, I went through the original `masm.c`, extended and refactored some code to enable its compatibility to `RSHIFT`, `MULT` and `DIV` macro instructions.

Next, I extended the `lex.yy.ll` file by adding the tokens for the three macro instructions.

Finally, I started to extend the microcode, which was the hardest part. The microcode for the `RSHIFT` instruction has been given in the helper directory, so I copied and pasted to my microprogram. The following is the microcode for the  `MULT` instruction:

```Pascal
82:  a := lshift(1);                            { 1111 1111 00 = MULT }
83:  a := lshift(a + 1);
84:  a := lshift(a + 1);
85:  a := lshift(a + 1);
86:  a := lshift(a + 1);
87:  a := a + 1;                                { a = 11 1111 }
88:  b := band(ir, a);                          { b stores the argument }
89:  mar := sp; rd;
90:  rd;                                        { mbr stores m[sp] }
91:  a := mbr;                                  { a stores m[sp] }
92:  c := 0;                                    { c is the result }
93:  alu := b; if z then goto 103;              { if b == 0, write m[sp] = 0 }
94:  alu := a; if n then goto 96;               { start: d = a < 0 ? -1 : 1}
95:  d := 1; goto 97;
96:  d := -1;                                   { end: d = a < 0 ? -1 : 1 }
97:  b := b + (-1); if n then goto 99;          { start: addition }
98:  c := c + a; goto 97;
99:  alu := c; if n then goto 101;              { check the result's sign }
100: d := d + 1; goto 102;
101: d:= d + (-1);
102: alu := d; if z then goto 105;              { overflow: goto ac := -1 }
103: mbr := c; wr;                              { write the result to m[sp] }
104: ac := 0; goto 0;
105: ac := -1; goto 0;                          { END: MULT }
```

Lines 82 to 87 create a mask `111111` and perform a bitwise AND on the
`ir` to obtain a 6-bit argument. Lines 89 to 91 access memory, storing the value from the top of the stack into register A. Line 92 initializes the result, storing it in register C. If the multiplier is zero, the result is written directly to the stack. Otherwise, since the multiplier is positive, the sign of the result should match the multiplicand's sign. Therefore, lines 94 to 96 store the multiplicand's sign in register D: 1 if positive, -1 if negative. A loop then calculates the result, ensuring the correct sign (lines 99 to 101). If there is an overflow,
`ac` is set to -1; otherwise, the result is written back to the stack.

The following is the microcode for the `DIV` instruction:

```Pascal
114: mar := sp; a := sp + 1; rd;                { 1111 1111 10 = DIV }
115: rd;
116: mar := a; b := mbr; rd;                    { b is the dividend }
117: rd;
118: a := mbr;                                  { a is the divisor }
119: e := 0;                                    { e: remainder }
120: f := 0;                                    { f: quotient }
121: alu := a; if z then goto 150;              { check if a is 0, illegal }
122: alu := a; if n then goto 126;              { start: set c; a = -|a| }
123: c := 1;
124: a := inv(a);
125: a := a + 1; goto 127;                      { a = -|divisor| }
126: c := -1;                                   { c stores divisor's sign }
127: alu := b; if n then goto 129;              { start: set d }
128: d := 1; goto 132;                          { goto legal case }
129: d := -1;                                   { d stores dividend's sign }
130: b := inv(b);
131: b := b + 1;                                { b = |dividend| }
132: ac := 0;                                   { legal case }
133: alu := b; if z then goto 152;              { no remainder, goto write }
134: alu := b; if n then goto 137;              { remainder is negative }
135: b := b + a;                                { b - |divisor| }
136: f := f + 1; goto 133;
137: a := inv(a);
138: a := a + 1;
139: e := a + b;                                { remainder = b + |a| }
140: f := f + (-1);
141: alu := d; if n then goto 144;              { d < 0 }
142: alu := c; if n then goto 148;              { c < 0 }
143: goto 152;
144: f := f + 1;                                { d is negative }
145: e := inv(e);
146: e := e + 1;
147: e := a + e; goto 152;
148: f := inv(f);                               { c is negative }
149: f := f + 1; goto 152;
150: ac := -1;                                  { illegal case }
151: e := -1;
152: sp := sp + (-1);                           { start: write to memory }
153: mar := sp; mbr := e; wr;                   { push the remainder to stack }
154: sp := sp + (-1);
155: mar := sp; mbr := f; wr;                   { push the quotient to stack }
156: goto 0;
```

The microcode for this instruction is complicated, so I wrote a draft to
`draft.txt`. Line 114 to 131 sets the following registers up:

* Register A: the absolute value of the divisor
* Register B: negative of the absolute value of the dividend
* Register C: the divisor's sign
* Register D: the dividend's sign
* Register E: 0 (remainder)
* Register F: 0 (quotient)

Line 132 to 149 is associated with legal cases, in which a loop (line 133 to 136) is used to find the quotient and remainder. Line 137 to 140 make the remainder to positive. Line 141 to 149 adjust the remainder and quotient according to the signs of divisor and dividend, the math deduction of which is found in the draft.
Line 150 and 151 is associated with the illegal cases, in which the accumulator is set to 0, and the remainder is -1.

Line 152 to 155 pushes the remainder and quotient to the stack.

## Available Makefile Targets

~~~shell
make              # Build all required target files (masm and prom.dat)
make clean        # Clean all target files
make test-rshift  # Run rshift.test.asm using mic1
make test-mult    # Run mult.test.asm using mic1
make test-div     # Run div.test.asm using mic1
~~~

## Resulting Output

The resulting output is available in
`output.txt`, which includes the output of the following commands in sequence:

```shell
./mic1 prom.dat rshift.test.obj 0 4000
./mic1 prom.dat mult.test.obj 0 4000
./mic1 prom.dat div.test.obj 0 4000
```