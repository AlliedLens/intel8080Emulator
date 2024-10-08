#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H


#include <stdio.h>
#include <stdlib.h>

//intel 8080 has 16bit memory addressing
//it has 64kb filesize


/*


         Intel 8080 Register Layout
         one register is 8 bits
         ------------------------------------------------
         | S   Z   -  AC   -  P   -   C | Flag Register
         ------------------------------------------------
         |   A (Accumulator)    |
         -----------------------
         |     B   |     C      |
         -----------------------
         |     D   |     E      |
         -----------------------
         |     H   |     L      |
         -----------------------
         |  SP (Stack Pointer)  |
         -----------------------
         |  PC (Program Counter)|
         -----------------------

There is a problem with trying to understand the flow of the dissasembler, in that if you look at some arbitrary chuk of memory that includes 8080 code, it probably
has data interleaved in it. For example, the sprites of the ingame chars, may be mixed in with the code, and the dissasembler will read i tas code. 

There is not a whole lot you can do with this, if you see things like:

a jump from known good to an instruction not in ur dissasembly listing, or a stream of nonsense code, then some portion of ur dissasembly is not readable code. 

*/

int disassemble8080(unsigned char* codebuffer, int pc){
    unsigned char* code = &codebuffer[pc];
    int opbytes = 1;

    printf("address: 0x%04x instruction: ", pc);
    switch(code[0]){
        case 0x00: // no operation
            printf(" NOP; no operation; ");
            break;
        case 0x01: // 16 bits are loaded onto reg B and reg C, i.e higher byte goes to B, lower byte goes to C
            printf(" LXI B, D16; B<--0x%02x C<--0x%02x ", code[2], code [1]);
            opbytes = 3;
            break;
        case 0x02: // byte stored by the address mentioned by register BC has the value of A
            printf(" STAX B; A <-- (BC) " );
            break;
        case 0x03: // increments the value stored in register BC combined by 1
            printf(" INX B; BC<-- BC + 1 ");
            break;
        case 0x04: // increments the value stored in regsiter B  by 1
            printf(" INR B; B <-- B + 1 "); 
            break;
        case 0x05: // decrements the value stored in register B by 1
            printf(" DCR B; B <-- B - 1 ");
            break;
        case 0x06: // assigns the second byte to reg B
            printf(" MVI B, D8;  B <-- 0x%02x ", code[1]);
            opbytes = 2;
            break;
        case 0x07: // left shifts A by 1 circularly, and assigns shifted bit to Cy flag
            printf(" RLC; A <-- A<<1, bit 0 = prev bit 7, CY = prev bit 7 ");
            break;
        case 0x08: //Not defined
            printf(" NOP; no operation ");
            break;
        case 0x09: // adds HL to BC 
            printf(" DAD B; HL = HL + BC ");
            break;
        case 0x0a: // value stored by BC address moved to A
            printf(" LDAX B; A <-- (BC) ");
            break;
        case 0x0b: // BC is decremented
            printf(" DCX B; BC <-- BC - 1 ");
            break;
        case 0x0c: // C is incremented
            printf(" INR C; C <-- C + 1 ");
            break;
        case 0x0d: // C is decremted
            printf(" DCR C; C <-- C - 1 ");
            break;
        case 0x0e: // Value of 2nd byte is moved to C
            printf(" MVI C, D8; C <-- 0x%02x ", code[1]);
            opbytes =2;
            break;
        case 0x0f: // right shift A by 1 circularly, and assigns shifted bit to CY flag
            printf(" RRC; A <-- A>>1, bit 7 =  prev bit 0, CY = prev bit 0 ");
            break;
        
        case 0x10: // nil
            printf(" NOP; no operation ");
            break;
        case 0x11:
            printf(" LXI D, D16; D <-- 0x%02x E <-- 0x%02x ", code[2], code[1]);
            opbytes=3;
            break;
        case 0x12:
            printf(" STAX D; (DE) <-- A ");
            break;
        case 0x13:
            printf(" INX D; DE <-- DE + 1 ");
            break;
        case 0x14: 
            printf(" INR D; D <-- D + 1 "); 
            break;
        case 0x15: 
            printf(" DCR D; D <-- D - 1 ");
            break;
        case 0x16: // assigns the second byte to reg D
            printf(" MVI D, D8;  D <-- 0x%02x ", code[1]);
            opbytes = 2;
            break;
        case 0x17:
            printf(" RLC; A <-- A<<1, bit 0 = prev CY, CY = prev bit 7 ");
            break;
        case 0x18: //Not defined
            printf(" NOP; no operation ");
            break;
        case 0x19:  
            printf(" DAD D; HL = HL + DE ");
            break;
        case 0x1a: 
            printf(" LDAX D; A <-- (DE) ");
            break;
        case 0x1b: 
            printf(" DCX D; DE <-- DE - 1 ");
            break;
        case 0x1c: 
            printf(" INR E; E <-- E + 1 ");
            break;
        case 0x1d: 
            printf(" DCR E; E <-- E - 1 ");
            break;
        case 0x1e: 
            printf(" MVI E, D8; E <-- 0x%02x ", code[1]);
            opbytes=2;
            break;
        case 0x1f: 
            printf(" RLC; A <-- A>>1, bit 7 =  prev bit 7, CY = prev bit 0 ");
            break;

        case 0x20: // nil
            printf(" NOP; no operation ");
            break;
        case 0x21:
            printf(" LXI H, D16; H <-- 0x%02x L <-- 0x%02x ", code[2], code[1]);
            opbytes=3;
            break;
        case 0x22: 
            printf(" SHLD adr ; (0x%04x) <-- L , (0x%04x) + 1 <-- H ", 
                (unsigned int)(code[2] << 8 | code[1]), 
                (unsigned int)(code[2] << 8 | code[1]));
            opbytes=3;
            break;
        case 0x23:
            printf(" INX H; HL <-- HL + 1 ");
            break;
        case 0x24: 
            printf(" INR H; H <-- H + 1 "); 
            break;
        case 0x25: 
            printf(" DCR H; H <-- H - 1 ");
            break;
        case 0x26: 
            printf(" MVI H, D8;  H <-- 0x%02x ", code[1]);
            opbytes=2;
            break;
        case 0x27:
            printf(" DAA; special? ");
            break;
        case 0x28: //Not defined
            printf(" NOP; no operation ");
            break;
        case 0x29:  
            printf(" DAD H; HL = HL + HI ");
            break;
        case 0x2a: 
            printf(" LHLD adr; (0x%04x) <-- L , (0x%04x) + 1 <-- H ", 
                (unsigned int)(code[2] << 8 | code[1]), 
                (unsigned int)(code[2] << 8 | code[1]));
            opbytes=3;
            break;
        case 0x2b: 
            printf(" DCX H; HL <-- HL - 1 ");
            break;
        case 0x2c: 
            printf(" INR L; L <-- L + 1 ");
            break;
        case 0x2d: 
            printf(" DCR L; L <-- L - 1 ");
            break;
        case 0x2e: 
            printf(" MVI L, D8; L <-- 0x%02x ", code[1]);
            opbytes=2;
            break;
        case 0x2f: 
            printf(" CMA; A <-- !A ");
            break;

        case 0x30: // nil
            printf(" NOP; no operation ");
            break;
        case 0x31:
            printf(" LXI SP, D16; SP.hi <-- 0x%02x SP.lo <-- 0x%02x ", code[2], code[1]);
            opbytes=3;
            break;
        case 0x32: 
            printf(" STA adr ; (0x%04x) <-- A ", code[2]<<8 | code[1]);
            opbytes=3;
            break;
        case 0x33:
            printf(" INX SP; SP <-- SP + 1 ");
            break;
        case 0x34: 
            printf(" INR M; (HL) <-- (HL) + 1 "); 
            break;
        case 0x35: 
            printf(" DCR M; (HL) <-- (HL) - 1 ");
            break;
        case 0x36: 
            printf(" MVI M, D8;  (HL) <-- 0x%02x ", code[1]);
            opbytes=2;
            break;
        case 0x37:
            printf(" STC; CY = 1 ");
            break;
        case 0x38: //Not defined
            printf(" NOP; no operation ");
            break;
        case 0x39:  
            printf(" DAD SP; HL = HL + SP ");
            break;
        case 0x3a: 
            printf(" LDA adr; A <-- (0x%04x) ", code[2]<<8 | code[1] );
            opbytes=3;
            break;
        case 0x3b: 
            printf(" DCX SP; SP <-- SP - 1 ");
            break;
        case 0x3c: 
            printf(" INR A; A <-- A + 1 ");
            break;
        case 0x3d: 
            printf(" DCR A; A <-- A - 1 ");
            break;
        case 0x3e: 
            printf(" MVI A, D8; A <-- 0x%02x ", code[1]);
            opbytes=2;
            break;
        case 0x3f: 
            printf(" CMA; CY <-- !CY ");
            break;
        
        case 0x40: 
            printf(" MOV B,B; B <-- B ");
            break;
        case 0x41:
            printf(" MOV B,C; B <-- C ");
            break;
        case 0x42: 
            printf(" MOV B,D; B <-- D ");
            break;
        case 0x43:
            printf(" MOV B,E; B <-- E ");
            break;
        case 0x44: 
            printf(" MOV B,H; B <-- H ");
            break;
        case 0x45: 
            printf(" MOV B,L; B <-- L ");
            break;
        case 0x46: 
            printf(" MOV B,M; B <-- (HL) ");
            break;
        case 0x47:
            printf(" MOV B,A; B <-- A ");
            break;
        case 0x48: 
            printf(" MOV C,B; C <-- B ");
            break;
        case 0x49:  
            printf(" MOV C,C; C <-- C ");
            break;
        case 0x4a: 
            printf(" MOV C,D; C <--  D" );
            break;
        case 0x4b: 
            printf(" MOV C,E; C <-- E ");
            break;
        case 0x4c: 
            printf(" MOV C,H; C <-- H ");
            break;
        case 0x4d: 
            printf(" MOV C,L; C <-- L ");
            break;
        case 0x4e: 
            printf(" MOV C,M; C <-- (HL) ");
            break;
        case 0x4f: 
            printf(" MOV C,A; C <-- A ");
            break;

        case 0x50: 
            printf(" MOV D,B; D <-- B ");
            break;
        case 0x51:
            break;
            printf(" MOV D,C; D <-- C ");
        case 0x52:
            break; 
            printf(" MOV D,D; D <-- D ");
        case 0x53:
            break;
            printf(" MOV D,E; D <-- E ");
        case 0x54: 
            printf(" MOV D,H; D <-- H ");
            break;
        case 0x55: 
            printf(" MOV D,L; D <-- L ");
            break;
        case 0x56: 
            printf(" MOV D,M; D <-- (HL) ");
            break;
        case 0x57:
            printf(" MOV D,A; D <-- A ");
            break;
        case 0x58: 
            printf(" MOV E,B; E <-- B ");
            break;
        case 0x59:  
            printf(" MOV E,C; E <-- C ");
            break;
        case 0x5a: 
            printf(" MOV E,D; E <--  D" );
            break;
        case 0x5b: 
            printf(" MOV E,E; E <-- E ");
            break;
        case 0x5c: 
            printf(" MOV E,H; E <-- H ");
            break;
        case 0x5d: 
            printf(" MOV E,L; E <-- L ");
            break;
        case 0x5e: 
            printf(" MOV E,M; E <-- (HL) ");
            break;
        case 0x5f: 
            printf(" MOV E,A; E <-- A ");
            break;

        case 0x60: 
            printf(" MOV H,B; H <-- B ");
            break;
        case 0x61:
            printf(" MOV H,C; H <-- C ");
            break;
        case 0x62: 
            printf(" MOV H,D; H <-- D ");
            break;
        case 0x63:
            printf(" MOV H,E; H <-- E ");
            break;
        case 0x64: 
            printf(" MOV H,H; H <-- H ");
            break;
        case 0x65: 
            printf(" MOV H,L; H <-- L ");
            break;
        case 0x66: 
            printf(" MOV H,M; H <-- (HL) ");
            break;
        case 0x67:
            printf(" MOV H,A; H <-- A ");
            break;
        case 0x68: 
            printf(" MOV L,B; L <-- B ");
            break;
        case 0x69:  
            printf(" MOV L,C; L <-- C ");
            break;
        case 0x6a: 
            printf(" MOV L,D; L <--  D" );
            break;
        case 0x6b: 
            printf(" MOV L,E; L <-- E ");
            break;
        case 0x6c: 
            printf(" MOV L,H; L <-- H ");
            break;
        case 0x6d: 
            printf(" MOV L,L; L <-- L ");
            break;
        case 0x6e: 
            printf(" MOV L,M; L <-- (HL) ");
            break;
        case 0x6f: 
            printf(" MOV L,A; L <-- A ");
            break;
        
        case 0x70: 
            printf(" MOV M,B; (HL) <-- B ");
            break;
        case 0x71:
            printf(" MOV M,C; (HL) <-- C ");
            break;
        case 0x72: 
            printf(" MOV M,D; (HL) <-- D ");
            break;
        case 0x73:
            printf(" MOV M,E; (HL) <-- E ");
            break;
        case 0x74: 
            printf(" MOV M,H; (HL) <-- H ");
            break;
        case 0x75: 
            printf(" MOV M,L; (HL) <-- L ");
            break;
        case 0x76: 
            printf(" HLT; special? ");
            break;
        case 0x77:
            printf(" MOV M,A; (HL) <-- A ");
            break;
        case 0x78: 
            printf(" MOV A,B; A <-- B ");
            break;
        case 0x79:  
            printf(" MOV A,C; A <-- C ");
            break;
        case 0x7a: 
            printf(" MOV A,D; A <--  D" );
            break;
        case 0x7b: 
            printf(" MOV A,E; A <-- E ");
            break;
        case 0x7c: 
            printf(" MOV A,H; A <-- H ");
            break;
        case 0x7d: 
            printf(" MOV A,L; A <-- L ");
            break;
        case 0x7e: 
            printf(" MOV A,M; A <-- (HL) ");
            break;
        case 0x7f: 
            printf(" MOV A,A; A <-- A ");
            break;

        case 0x80: 
            printf(" ADD B; A <-- A + B ");
            break;
        case 0x81:
            printf(" ADD C; A <-- A + C ");
            break;
        case 0x82: 
            printf(" ADD D; A <-- A + D ");
            break;
        case 0x83:
            printf(" ADD E; A <-- A + E ");
            break;
        case 0x84: 
            printf(" ADD H; A <-- A + H ");
            break;
        case 0x85: 
            printf(" ADD L; A <-- A + L ");
            break;
        case 0x86: 
            printf(" ADD M; A <-- A + (HL) ");
            break;
        case 0x87:
            printf(" ADD A; A <-- A + A ");
            break;
        case 0x88: 
            printf(" ADC B; A <-- A + B + CY ");
            break;
        case 0x89:  
            printf(" ADC C; A <-- A + C + CY ");
            break;
        case 0x8a: 
            printf(" ADC D; A <-- A + D + CY " );
            break;
        case 0x8b: 
            printf(" ADC E; A <-- A + E + CY ");
            break;
        case 0x8c: 
            printf(" ADC H; A <-- A + H + CY ");
            break;
        case 0x8d: 
            printf(" ADC L; A <-- A + L + CY ");
            break;
        case 0x8e: 
            printf(" ADC M; A <-- A + (HL) + CY ");
            break;
        case 0x8f: 
            printf(" ADC A; A <-- A + A + CY ");
            break;

        case 0x90: 
            printf(" SUB B; A <-- A + B ");
            break;
        case 0x91:
            printf(" SUB C; A <-- A - C ");
            break;
        case 0x92: 
            printf(" SUB D; A <-- A - D ");
            break;
        case 0x93:
            printf(" SUB E; A <-- A - E ");
            break;
        case 0x94: 
            printf(" SUB H; A <-- A - H ");
            break;
        case 0x95: 
            printf(" SUB L; A <-- A - L ");
            break;
        case 0x96: 
            printf(" SUB M; A <-- A - (HL) ");
            break;
        case 0x97:
            printf(" SUB A; A <-- A - A ");
            break;
        case 0x98: 
            printf(" SBB B; A <-- A - B - CY ");
            break;
        case 0x99:  
            printf(" SBB C; A <-- A - C - CY ");
            break;
        case 0x9a: 
            printf(" SBB D; A <-- A - D - CY " );
            break;
        case 0x9b: 
            printf(" SBB E; A <-- A - E - CY ");
            break;
        case 0x9c: 
            printf(" SBB H; A <-- A - H - CY ");
            break;
        case 0x9d: 
            printf(" SBB L; A <-- A - L - CY ");
            break;
        case 0x9e: 
            printf(" SBB M; A <-- A - (HL) - CY ");
            break;
        case 0x9f: 
            printf(" SBB A; A <-- A - A - CY ");
            break;

        case 0xA0: 
            printf(" ANA B; A <-- A & B ");
            break;
        case 0xA1:
            printf(" ANA C; A <-- A & C ");
            break;
        case 0xA2: 
            printf(" ANA D; A <-- A & D ");
            break;
        case 0xA3:
            printf(" ANA E; A <-- A & E ");
            break;
        case 0xA4: 
            printf(" ANA H; A <-- A & H ");
            break;
        case 0xA5: 
            printf(" ANA L; A <-- A & L ");
            break;
        case 0xA6: 
            printf(" ANA M; A <-- A & (HL) ");
            break;
        case 0xA7:
            printf(" ANA A; A <-- A & A ");
            break;
        case 0xA8: 
            printf(" XRA B; A <-- A ^ B ");
            break;
        case 0xA9:  
            printf(" XRA C; A <-- A ^ C ");
            break;
        case 0xAa: 
            printf(" XRA D; A <-- A ^ D " );
            break;
        case 0xAb: 
            printf(" XRA E; A <-- A ^ E ");
            break;
        case 0xAc: 
            printf(" XRA H; A <-- A ^ H ");
            break;
        case 0xAd: 
            printf(" XRA L; A <-- A ^ L ");
            break;
        case 0xAe: 
            printf(" XRA M; A <-- A ^ (HL) ");
            break;
        case 0xAf: 
            printf(" XRA A; A <-- A ^ A ");
            break;


        case 0xB0: 
            printf(" ORA B; A <-- A | B ");
            break;
        case 0xB1:
            printf(" ORA C; A <-- A | C ");
            break;
        case 0xB2: 
            printf(" ORA D; A <-- A | D ");
            break;
        case 0xB3:
            printf(" ORA E; A <-- A | E ");
            break;
        case 0xB4: 
            printf(" ORA H; A <-- A | H ");
            break;
        case 0xB5: 
            printf(" ORA L; A <-- A | L ");
            break;
        case 0xB6: 
            printf(" ORA M; A <-- A | (HL) ");
            break;
        case 0xB7:
            printf(" ORA A; A <-- A | A ");
            break;
        case 0xB8: 
            printf(" CMP B;  A - B ");
            break;
        case 0xB9:  
            printf(" CMP C;  A - C ");
            break;
        case 0xBa: 
            printf(" CMP D;  A - D " );
            break;
        case 0xBb: 
            printf(" CMP E;  A - E ");
            break;
        case 0xBc: 
            printf(" CMP H;  A - H ");
            break;
        case 0xBd: 
            printf(" CMP L;  A - L ");
            break;
        case 0xBe: 
            printf(" CMP M;  A - (HL) ");
            break;
        case 0xBf: 
            printf(" CMP A;  A - A ");
            break;

        case 0xC0: 
            printf(" RNZ; if NZ, Return ");
            break;
        case 0xC1:
            printf(" POP B; C <- (SP); B <- (SP+1); SP <- SP + 2 ");
            break;
        case 0xC2: 
            printf(" JNZ adr; if NZ, PC <-- 0x%04x ", code[2]<<8 | code[1]);
            opbytes=3;
            break;
        case 0xC3:
            printf(" JMP adr;  PC <-- 0x%04x ", code[2]<<8 | code[1]);
            opbytes=3;
            break;
        case 0xC4: 
            printf(" CNZ adr;  if NZ, CALL 0x%04x ", code[2]<<8 | code[1]);
            opbytes=3;
            break;
        case 0xC5: 
            printf(" PUSH B;  (SP-2) <-- C; (SP-1) <-- B ; SP <-- SP - 2 ");
            break;
        case 0xC6: 
            printf(" ADI D8; A <-- A + 0x%02x ", code[1]);
            opbytes=2;
            break;
        case 0xC7: //  all the code at the beginning of the ROM are interrupt service routines, and they can be software generated via the RST instruction
            printf(" RST 0; A <-- A | A ");
            break;
        case 0xC8: 
            printf(" RZ; if Z, Return ");
            break;
        case 0xC9:  
            printf(" RET;  	PC.lo <- (sp); PC.hi<-(sp+1); SP <- SP+2 ");
            break;
        case 0xCA: 
            printf(" JZ adr;  PC <-- 0x%04x ", code[2]<<8 | code[1] );
            opbytes=3;
            break;
        case 0xCB: 
            printf(" NOP; no operation ");
            break;
        case 0xCC: 
            printf(" CZ adr;  if Z,  CALL 0x%04x ", code[2]<<8 | code[1] );
            opbytes=3;
            break;
        case 0xCD: 
            printf(" CALL adr; (SP-1)<-PC.hi;(SP-2)<-PC.lo;SP<-SP-2;PC = 0x%04x", code[2]<<8 | code[1]);
            opbytes=3;
            break;
        case 0xCE: 
            printf(" ACI D8;  A <-- A + 0x%02x + CY ", code[1]);
            opbytes=2;
            break;
        case 0xCF: 
            printf(" RST 1;  CALL $8");
            break;

        case 0xD0: 
            printf(" RNC; if NCY, Return ");
            break;
        case 0xD1:
            printf(" POP D; E <- (SP); D <- (SP+1); SP <- SP + 2 ");
            break;
        case 0xD2: 
            printf(" JNC adr; if NCY, PC <-- 0x%04x ", code[2]<<8 | code[1]);
            opbytes=3;
            break;
        case 0xD3:
            printf(" OUT D8;  special? ");
            opbytes=2;
            break;
        case 0xD4: 
            printf(" CNC adr;  if NCY, CALL (0x%04x) ", code[2]<<8 | code[1]);
            opbytes=3;
            break;
        case 0xD5: 
            printf(" PUSH D;  (SP-2) <-- E; (SP-1) <-- D ; SP <-- SP - 2 ");
            break;
        case 0xD6: 
            printf(" SUI D8; A <-- A - 0x%02x ", code[1]);
            opbytes=2;
            break;
        case 0xD7: 
            printf(" RST 2; CALL $10");
            break;
        case 0xD8: 
            printf(" RC; if CY, Return ");
            break;
        case 0xD9:  
            printf(" NOP;  	no operation ");
            break;
        case 0xDA: 
            printf(" JC adr; if CY,  PC <-- 0x%04x ", code[2]<<8 | code[1] );
            opbytes=3;
            break;
        case 0xDB: 
            printf(" IN D8; special ");
            opbytes=2;
            break;
        case 0xDC: 
            printf(" CC adr;  if CY,  CALL 0x%04x ", code[2]<<8 | code[1] );
            opbytes=3;
            break;
        case 0xDD: 
            printf(" NOP; no operation");
            break;
        case 0xDE: 
            printf(" SBI D8;  A <-- A - 0x%02x - CY ", code[1]);
            opbytes=2;
            break;
        case 0xDF: 
            printf(" RST 3;  CALL $18");
            break;

        case 0xE0: 
            printf(" RPO; if PO, Return ");
            break;
        case 0xE1:
            printf(" POP H; L <- (SP); H <- (SP+1); SP <- SP + 2 ");
            break;
        case 0xE2: 
            printf(" JPO adr; if PO, PC <-- 0x%04x ", code[2]<<8 | code[1]);
            opbytes=3;
            break;
        case 0xE3:
            printf(" XTHL;  L <-> (SP); H <-> (SP+1) ");
            break;
        case 0xE4: 
            printf(" CPO adr;  if PO, CALL (0x%04x) ", code[2]<<8 | code[1]);
            opbytes=3;
            break;
        case 0xE5: 
            printf(" PUSH H;  (SP-2) <-- L; (SP-1) <-- H ; SP <-- SP - 2 ");
            break;
        case 0xE6: 
            printf(" ANI D8; A <-- A & 0x%02x ", code[1]);
            opbytes=2;
            break;
        case 0xE7: 
            printf(" RST 4; CALL $20");
            break;
        case 0xE8: 
            printf(" RPE; if PE, Return ");
            break;
        case 0xE9:  
            printf(" PCHL; PC.hi <- H; PC.lo <- L ");
            break;
        case 0xEA: 
            printf(" JPE adr; if PE,  PC <-- 0x%04x ", code[2]<<8 | code[1] );
            opbytes=3;
            break;
        case 0xEB: 
            printf(" XCHG; 	H <-> D; L <-> E ");
            opbytes=2;
            break;
        case 0xEC: 
            printf(" CPE adr;  if PE,  CALL 0x%04x ", code[2]<<8 | code[1] );
            opbytes=3;
            break;
        case 0xED: 
            printf(" NOP; no operation");
            break;
        case 0xEE: 
            printf(" XRI D8;  A <-- A ^ 0x%02x ", code[1]);
            opbytes=2;
            break;
        case 0xEF: 
            printf(" RST 5;  CALL $18");
            break;

        case 0xF0: 
            printf(" RP; if P, Return ");
            break;
        case 0xF1:
            printf(" POP PSW; L <- (SP); H <- (SP+1); SP <- SP + 2 ");
            break;
        case 0xF2: 
            printf(" JP adr; if P=1, PC <-- 0x%04x ", code[2]<<8 | code[1]);
            opbytes=3;
            break;
        case 0xF3:
            printf(" DI;  special? ");
            break;
        case 0xF4: 
            printf(" CP adr;  if P, CALL (0x%04x) ", code[2]<<8 | code[1]);
            opbytes=3;
            break;
        case 0xF5: 
            printf(" PUSH PSW;  (SP-2) <-- flags; (SP-1) <-- A ; SP <-- SP - 2 ");
            break;
        case 0xF6: 
            printf(" ORI D8; A <-- A | 0x%02x ", code[1]);
            opbytes=2;
            break;
        case 0xF7: 
            printf(" RST 6; CALL $30");
            break;
        case 0xF8: 
            printf(" RM; if M, Return ");
            break;
        case 0xF9:  
            printf(" SPHL; SP=HL ");
            break;
        case 0xFA: 
            printf(" JM adr; if M,  PC <-- 0x%04x ", code[2]<<8 | code[1] );
            opbytes=3;
            break;
        case 0xFB: 
            printf(" EI; special? ");
            break;
        case 0xFC: 
            printf(" CM adr;  if M,  CALL 0x%04x ", code[2]<<8 | code[1] );
            opbytes=3;
            break;
        case 0xFD: 
            printf(" NOP; no operation");
            break;
        case 0xFE: 
            printf(" CPI D8;  A - 0x%02x ", code[1]);
            opbytes=2;
            break;
        case 0xFF: 
            printf(" RST 7;  CALL $38");
            break;

        default:
            printf(" unmapped opcode ");

    }

    printf("opcodes: ");
    switch(opbytes){
        case(1):
            printf(" 0x%02x ", code[0]);
            break;
        case(2):
            printf(" 0x%02x 0x%02x ", code[0], code[1]);
            break;
        case(3):
            printf(" 0x%02x 0x%02x 0x%02x", code[0], code[1], code[2]);
            break;
    }
    printf("\n");

    return opbytes;
}

#endif