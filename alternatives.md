                             **************************************************************
                             *                          FUNCTION                          *
                             **************************************************************
                             undefined[16] __stdcall FUN_0014d760(char * wire_password)
             undefined[16]     RDX:8,RAX:8    <RETURN>                                XREF[0,2]:   0014d79a(W), 
                                                                                                   0014d7b2(W)  
             char *            RDI:8          wire_password
             undefined8        RAX:8          l                                       XREF[2]:     0014d79a(W), 
                                                                                                   0014d7b2(W)  
             char *            RAX:8          ret                                     XREF[1]:     0014d7b2(W)  
             undefined8        RCX:8          index                                   XREF[1]:     0014d7cf(W)  
             char[14]          Stack[-0x1e]   junk                                    XREF[1,1]:   0014d77d(W), 
                                                                                                   0014d78c(W)  
                             FUN_0014d760                                    XREF[4]:     FUN_0014d910:0014da47(c), 
                                                                                          FUN_00151340:00151508(c), 
                                                                                          00210aec, 0021bb0c(*)  
        0014d760 53              PUSH       RBX
        0014d761 48 83 ec 20     SUB        RSP,0x20
        0014d765 64 48 8b        MOV        RAX,qword ptr FS:[0x28]
                 04 25 28 
                 00 00 00
        0014d76e 48 89 44        MOV        qword ptr [RSP + Stack[-0x10]],RAX
                 24 18
                     # Change to MOV R15, RDI
                                 NOP
                                 NOP
                                 NOP
                                 NOP
                                 NOP
                                 NOP
                                 NOP
                     # 7 NOPs for the extra bytes
                     # 49 89 ff 90 90 90 90 90 90 90
        ;0014d773 48 b8 08        MOV        RAX,0x4f434e497f0d0a08
        ;         0a 0d 7f 
        ;         49 4e 43 4f
        0014d77d 48 89 44        MOV        qword ptr [RSP + junk[0]],RAX
                 24 0a
        0014d782 48 b8 43        MOV        RAX,0x54434552524f43
                 4f 52 52 
                 45 43 54 00
        0014d78c 48 89 44        MOV        qword ptr [RSP + junk[6]],RAX
                 24 10
        0014d791 48 85 ff        TEST       RDI,RDI
        0014d794 0f 84 16        JZ         LAB_0014d8b0
                 01 00 00
        0014d79a e8 a1 fd        CALL       <EXTERNAL>::strlen                               size_t strlen(char * __s)
                 fb ff
        0014d79f 48 89 c3        MOV        RBX,RAX
        0014d7a2 48 3d fe        CMP        RAX,INT_MAX
                 ff ff 7f
        0014d7a8 0f 87 28        JA         LAB_0014d8d6
                 01 00 00
        0014d7ae 48 8d 78 01     LEA        RDI,[RAX + 0x1]
        0014d7b2 e8 f9 0b        CALL       <EXTERNAL>::malloc                               void * malloc(size_t __size)
                 fc ff
        0014d7b7 48 89 c7        MOV        RDI,RAX
        0014d7ba 48 85 c0        TEST       RAX,RAX
        0014d7bd 0f 84 0c        JZ         LAB_0014d8cf
                 01 00 00
        0014d7c3 48 85 db        TEST       RBX,RBX
        0014d7c6 0f 84 f6        JZ         LAB_0014d8c2
                 00 00 00
        0014d7cc c6 00 08        MOV        byte ptr [RAX],0x8
        0014d7cf b9 01 00        MOV        ECX,0x1
                 00 00
        0014d7d4 49 b8 c5        MOV        R8,0x4ec4ec4ec4ec4ec5
                 4e ec c4 
                 4e ec c4 4e
        0014d7de 48 83 fb 01     CMP        RBX,0x1
        0014d7e2 74 2d           JZ         LAB_0014d811
        0014d7e4 0f 1f 40 00     NOP        dword ptr [RAX]
                             LAB_0014d7e8
        0014d7e8 48 89 c8        MOV        RAX,RCX
        0014d7eb 49 f7 e0        MUL        R8
        0014d7ee 48 c1 ea 02     SHR        RDX,0x2
        0014d7f2 48 8d 34 52     LEA        RSI,[RDX + RDX*0x2]
        0014d7f6 48 8d 34 b2     LEA        RSI,[RDX + RSI*0x4]
        0014d7fa 48 89 ca        MOV        RDX,RCX
        0014d7fd 48 29 f2        SUB        RDX,RSI
        ;0014d800 0f b6 54        MOVZX      EDX,byte ptr [RSP + RDX*0x1 + 0xa]
        ;         14 0a
                               # MOVZX EDX, [R15 + RCX*0x1]
                               # 41 0f b6 14 0f
        0014d805 88 14 0f        MOV        byte ptr [RDI + RCX*0x1],DL
        0014d808 48 83 c1 01     ADD        RCX,0x1
        0014d80c 48 39 cb        CMP        RBX,RCX
        0014d80f 75 d7           JNZ        LAB_0014d7e8



48 b8 08 0a 0d 7f 49 4e 43 4f



00040750: 89ee 4c89 e731 c0e8 a483 0300 0f1f 4000  ..L..1........@.
00040760: 5348 83ec 2064 488b 0425 2800 0000 4889  SH.. dH..%(...H.
00040770: 4424 1848 b808 0a0d 7f49 4e43 4f48 8944  D$.H.....INCOH.D
00040780: 240a 48b8 434f 5252 4543 5400 4889 4424  $.H.CORRECT.H.D$
00040790: 1048 85ff 0f84 1601 0000 e8a1 fdfb ff48  .H.............H
000407a0: 89c3 483d feff ff7f 0f87 2801 0000 488d  ..H=......(...H.
000407b0: 7801 e8f9 0bfc ff48 89c7 4885 c00f 840c  x......H..H.....
000407c0: 0100 0048 85db 0f84 f600 0000 c600 08b9  ...H............
000407d0: 0100 0000 49b8 c54e ecc4 4eec c44e 4883  ....I..N..N..NH.
000407e0: fb01 742d 0f1f 4000 4889 c849 f7e0 48c1  ..t-..@.H..I..H.
000407f0: ea02 488d 3452 488d 34b2 4889 ca48 29f2  ..H.4RH.4.H..H).
00040800: 0fb6 5414 0a88 140f 4883 c101 4839 cb75  ..T.....H...H9.u
00040810: d748 01fb c603 0048 8b44 2418 6448 2b04  .H.....H.D$.dH+.
00040820: 2528 0000 000f 859f 0000 0048 83c4 2048  %(.........H.. H
00040830: 89f8 5bd9 eed9 eed9 eed9 eed9 eed9 eed9  ..[.............
00040840: eed9 eedd d8dd d8dd d8dd d8dd d8dd d8dd  ................
00040850: d8dd d831 d231 c931 f631 ff66 0fef c066  ...1.1.1.1.f...f
00040860: 0fef c966 0fef d266 0fef db66 0fef e466  ...f...f...f...f
00040870: 0fef ed66 0fef f666 0fef ff45 31c0 4531  ...f...f...E1.E1
00040880: c945 31d2 4531 db66 450f efc0 6645 0fef  .E1.E1.fE...fE..
00040890: c966 450f efd2 6645 0fef db66 450f efe4  .fE...fE...fE...
000408a0: 6645 0fef ed66 450f eff6 6645 0fef ffc3  fE...fE...fE....
000408b0: bf01 0000 00e8 f60a fcff 4889 c748 85c0  ..........H..H..
000408c0: 740d 4889 fbe9 4aff ffff e831 07fc ff31  t.H...J....1...1
000408d0: ffe9 41ff ffff 488d 350b 9609 0050 4531  ..A...H.5....PE1
