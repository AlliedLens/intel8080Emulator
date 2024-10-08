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
            printf(" RLC; A <-- A>>1, bit 7 =  prev bit 0, CY = prev bit 0 ");
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
