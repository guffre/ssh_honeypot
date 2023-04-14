# Binary Patching

The `fake_password` function is responsible for overwriting the users password with the \b\n\r\177INCORRECT garbage.

Register information starting at top

* RAX = Buffer for "junk password", returned from `malloc()`

* RBP = pointer to original password

* ECX = index for loop

```nasm
c6 00 08        MOV        byte ptr [RAX],0x8
b9 01 00        MOV        ECX,0x1
49 b8 c5 4e ec c4 4e ec c4 4e   MOV R8,0x4ec4ec4ec4ec4ec5

48 83 fb 01     CMP        RBX,0x1
74 2d           JZ         LAB_0014d811
0f 1f 40 00     NOP        dword ptr [RAX]
                                                LAB_0014d7e8
48 89 c8        MOV        RAX,RCX
49 f7 e0        MUL        R8
48 c1 ea 02     SHR        RDX,0x2
48 8d 34 52     LEA        RSI,[RDX + RDX*0x2]
48 8d 34 b2     LEA        RSI,[RDX + RSI*0x4]
48 89 ca        MOV        RDX,RCX
48 29 f2        SUB        RDX,RSI
0f b6 54 14 0a  MOVZX      EDX,byte ptr [RSP + RDX*0x1 + 0xa]
88 14 0f        MOV        byte ptr [RDI + RCX*0x1],DL
48 83 c1 01     ADD        RCX,0x1
48 39 cb        CMP        RBX,RCX
75 d7           JNZ        LAB_0014d7e8
```

I analyzed two versions of this function. In both versions, the compiler optimized out the first character of the fake_password buffer. You can see it happening in the first two instructions, where it writes a 0x8 (which is \b) directly into the buffer, and sets the loop counter to 1 instead of 0.

To patch the binary, we will change the function to the following behaviour:

```nasm
c6 00 08        MOV        byte ptr [RAX],0x8
b9 01 00        MOV        ECX,0x1
40 88 28        MOV        byte ptr [RAX],BPL ; overwrite byte
8a 55 00        MOV        DL,byte ptr [RBP]  ; overwrite byte
90              NOP
90              NOP
90              NOP
48 83 fb 01     CMP        RBX,0x1
74 2d           JZ         LAB_0014d811
0f 1f 40 00     NOP        dword ptr [RAX]
                                                LAB_0014d7e8
48 89 c8        MOV        RAX,RCX
49 f7 e0        MUL        R8
48 c1 ea 02     SHR        RDX,0x2
48 8d 34 52     LEA        RSI,[RDX + RDX*0x2]
48 8d 34 b2     LEA        RSI,[RDX + RSI*0x4]
48 89 ca        MOV        RDX,RCX
48 29 f2        SUB        RDX,RSI
8a 54 15 00     MOV        DL,byte ptr [RBP + RDX*0x1] ; write from RBP
90              NOP
88 14 0f        MOV        byte ptr [RDI + RCX*0x1],DL
48 83 c1 01     ADD        RCX,0x1
48 39 cb        CMP        RBX,RCX
75 d7           JNZ        LAB_0014d7e8

```

This promply overwrites the first value of `[RAX]` with `BPL`, which is the low byte of the `RBP` register which contains the original password.

The reason for the next instruction: `DL,byte ptr [RBP]`, is the other version `sshd` that I looked at performed a `JMP` to the bottom of the loop, and had prepared `EDX` with a hardcoded value. This second instruction accounts for that behaviour

Finally, the last changed instruction writes from the `RBP` register, which simply copies the original password into the new `junk password` buffer.