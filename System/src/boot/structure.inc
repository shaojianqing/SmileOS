

DA_DATA     EQU   0x00
;----------------------------------------------------------------------------
DA_32		EQU   0x04000	
DA_32_4K    EQU   0x0C000

DA_DPL0		EQU	  0x00	
DA_DPL1		EQU	  0x20	
DA_DPL2		EQU	  0x40	
DA_DPL3		EQU	  0x60	
;----------------------------------------------------------------------------

;----------------------------------------------------------------------------
DA_DR		EQU	  0x90	
DA_DRW		EQU	  0x92	
DA_DRWA		EQU	  0x93	
DA_C		EQU	  0x98	
DA_CR		EQU	  0x9A	
DA_CCO		EQU	  0x9C	
DA_CCOR		EQU	  0x9E	
;----------------------------------------------------------------------------

;----------------------------------------------------------------------------
DA_LDT		EQU	  0x82	
DA_TaskGate	EQU	  0x85	
DA_386TSS	EQU	  0x89	
DA_386CGate	EQU	  0x8C	
DA_386IGate	EQU	  0x8E	
DA_386TGate	EQU	  0x8F	
;----------------------------------------------------------------------------

; usage: Descriptor Base, Limit, Attr
;        Base:  dd
;        Limit: dd (low 20 bits available)
;        Attr:  dw (lower 4 bits of higher byte are always 0)
%macro Descriptor 3
	dw	%2 & 0xFFFF				
	dw	%1 & 0xFFFF				
	db	(%1 >> 16) & 0x00FF			
	dw	((%2 >> 8) & 0x0F00) | (%3 & 0xF0FF)	
	db	(%1 >> 24) & 0x00FF			
%endmacro 

; usage: Gate Selector, Offset, DCount, Attr
;        Selector:  dw
;        Offset:    dd
;        DCount:    db
;        Attr:      db
%macro Gate 4
	dw	(%2 & 0xFFFF)				
	dw	%1
	dw	(%3 & 0x001F) | ((%4 << 8) & 0xFF00)
	dw	((%2 >> 16) & 0xFFFF)
%endmacro


