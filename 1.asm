.ORIG X3000
 AND R1,R1,0 ;clear R1 for n
 AND R2,R2,0 ; store the result of 3n
 AND R4, R4, 0;
 LD R1, NUM
 ADD R2,R1,R1
 ADD R2,R2,R1 ; 3n 
 ADD R4, R4, R2 ; store R2 to R4
 LD R3, MAX; max positive value
 NOT R3, R3;
 ADD R3, R3, #1 ; neigative R3
 ADD R4, R4, R3;
 BRzp END
 LD R5, SMALL 
 ADD R2, R2, R5 ; R2-32768
 ADD R2, R2, R5 ; R2-65536
END	
 HALT
NUM .FILL X2AF9
MAX .FILL X7FFF ;overflow of not
SMALL .FILL X8000
.END
