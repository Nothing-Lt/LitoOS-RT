;;Name								Vector nr.			Type		Mnemonic	Error code?
;;Divide-by-zero Error				0 (0x0)				Fault		#DE			No
;;Debug								1 (0x1)				Fault/Trap	#DB			No
;;Non-maskable Interrupt			2 (0x2)				Interrupt	-			No
;;Breakpoint						3 (0x3)				Trap		#BP			No
;;Overflow							4 (0x4)				Trap		#OF			No
;;Bound Range Exceeded				5 (0x5)				Fault		#BR			No
;;Invalid Opcode					6 (0x6)				Fault		#UD			No
;;Device Not Available				7 (0x7)				Fault		#NM			No
;;Double Fault						8 (0x8)				Abort		#DF			Yes (Zero)
;;Coprocessor Segment Overrun		9 (0x9)				Fault		-			No
;;Invalid TSS						10 (0xA)			Fault		#TS			Yes
;;Segment Not Present				11 (0xB)			Fault		#NP			Yes
;;Stack-Segment Fault				12 (0xC)			Fault		#SS			Yes
;;General Protection Fault			13 (0xD)			Fault		#GP			Yes
;;Page Fault						14 (0xE)			Fault		#PF			Yes
;;Reserved							15 (0xF)			-			-			No
;;x87 Floating-Point Exception		16 (0x10)			Fault		#MF			No
;;Alignment Check					17 (0x11)			Fault		#AC			Yes
;;Machine Check						18 (0x12)			Abort		#MC			No
;;SIMD Floating-Point Exception		19 (0x13)			Fault		#XM/#XF		No
;;Virtualization Exception			20 (0x14)			Fault		#VE			No
;;Reserved							21-29 (0x15-0x1D)	-			-			No
;;Security Exception				30 (0x1E)			-			#SX			Yes
;;Reserved							31 (0x1F)			-			-			No
;;Triple Fault						-					-			-			No
;;FPU Error Interrupt				IRQ 13				Interrupt	#FERR		No

;;    |    SS    |  <---High address   this part only exsits when stack swith occur | 
;;    |    ESP   |                     this part only exsits when stack swith occur |  stack grows this direction
;;    |----------|----------------------------------------------------------------- |
;;    |  EFLAGS  |                                                                  |
;;    |    CS    |                                                                  |
;;    |    EIP   |                                                                  |
;;    |ERROR CODE|  <--- Low address   this exsits only exception with error code  \|/



	;; software exception handler
	extern handle0x00, handle0x01, handle0x02, handle0x03, handle0x04, handle0x05
	extern handle0x06, handle0x07, handle0x08, handle0x09, handle0x0a, handle0x0b
	extern handle0x0c, handle0x0d, handle0x0e, handle0x0f
	extern handle0x10, handle0x11, handle0x12, handle0x13, handle0x14, handle0x15
 	extern handle0x16, handle0x17, handle0x18, handle0x19, handle0x1a, handle0x1b
 	extern handle0x1c, handle0x1d, handle0x1e, handle0x1f
	;; hardware interrupt handler
	extern handle0x20, handle0x21, handle0x22, handle0x23, handle0x24, handle0x25
	extern handle0x26, handle0x27, handle0x28, handle0x29, handle0x2a, handle0x2b
	extern handle0x2c, handle0x2d, handle0x2e, handle0x2f
	extern handle0x30, handle0x31, handle0x32, handle0x33, handle0x34, handle0x35
	extern handle0x36, handle0x37, handle0x38, handle0x39, handle0x3a, handle0x3b
	extern handle0x3c, handle0x3d, handle0x3e, handle0x3f
 	extern handle0x40, handle0x41, handle0x42, handle0x43, handle0x44, handle0x45
	extern handle0x46, handle0x47, handle0x48, handle0x49, handle0x4a, handle0x4b
	extern handle0x4c, handle0x4d, handle0x4e, handle0x4f
	extern handle0x50, handle0x51, handle0x52, handle0x53, handle0x54, handle0x55
	extern handle0x56, handle0x57, handle0x58, handle0x59, handle0x5a, handle0x5b
	extern handle0x5c, handle0x5d, handle0x5e, handle0x5f
	extern handle0x60, handle0x61, handle0x62, handle0x63, handle0x64, handle0x65
	extern handle0x66, handle0x67, handle0x68, handle0x69, handle0x6a, handle0x6b
	extern handle0x6c, handle0x6d, handle0x6e, handle0x6f
	extern handle0x70, handle0x71, handle0x72, handle0x73, handle0x74, handle0x75
	extern handle0x76, handle0x77, handle0x78, handle0x79, handle0x7a, handle0x7b
	extern handle0x7c, handle0x7d, handle0x7e, handle0x7f
	extern handle0x80, handle0x81, handle0x82, handle0x83, handle0x84, handle0x85
	extern handle0x86, handle0x87, handle0x88, handle0x89, handle0x8a, handle0x8b
	extern handle0x8c, handle0x8d, handle0x8e, handle0x8f
	extern handle0x90, handle0x91, handle0x92, handle0x93, handle0x94, handle0x95
	extern handle0x96, handle0x97, handle0x98, handle0x99, handle0x9a, handle0x9b
	extern handle0x9c, handle0x9d, handle0x9e, handle0x9f
	extern handle0xa0, handle0xa1, handle0xa2, handle0xa3, handle0xa4, handle0xa5
	extern handle0xa6, handle0xa7, handle0xa8, handle0xa9, handle0xaa, handle0xab
	extern handle0xac, handle0xad, handle0xae, handle0xaf
	extern handle0xb0, handle0xb1, handle0xb2, handle0xb3, handle0xb4, handle0xb5
	extern handle0xb6, handle0xb7, handle0xb8, handle0xb9, handle0xba, handle0xbb
	extern handle0xbc, handle0xbd, handle0xbe, handle0xbf
	extern handle0xc0, handle0xc1, handle0xc2, handle0xc3, handle0xc4, handle0xc5
	extern handle0xc6, handle0xc7, handle0xc8, handle0xc9, handle0xca, handle0xcb
	extern handle0xcc, handle0xcd, handle0xce, handle0xcf
	extern handle0xd0, handle0xd1, handle0xd2, handle0xd3, handle0xd4, handle0xd5
	extern handle0xd6, handle0xd7, handle0xd8, handle0xd9, handle0xda, handle0xdb
	extern handle0xdc, handle0xdd, handle0xde, handle0xdf
	extern handle0xe0, handle0xe1, handle0xe2, handle0xe3, handle0xe4, handle0xe5
	extern handle0xe6, handle0xe7, handle0xe8, handle0xe9, handle0xea, handle0xeb
	extern handle0xec, handle0xed, handle0xee, handle0xef
	extern handle0xf0, handle0xf1, handle0xf2, handle0xf3, handle0xf4, handle0xf5
	extern handle0xf6, handle0xf7, handle0xf8, handle0xf9, handle0xfa, handle0xfb
	extern handle0xfc, handle0xfd, handle0xfe, handle0xff


	;; software system call handler
	extern sys_send_recv

[section .text]
	;; software exception handler
	global asm_handle0x00, asm_handle0x01, asm_handle0x02, asm_handle0x03, asm_handle0x04
	global asm_handle0x05, asm_handle0x06, asm_handle0x07, asm_handle0x08, asm_handle0x09
	global asm_handle0x0a, asm_handle0x0b, asm_handle0x0c, asm_handle0x0d, asm_handle0x0e
	global asm_handle0x0f
	global asm_handle0x10, asm_handle0x11, asm_handle0x12, asm_handle0x13, asm_handle0x14
    global asm_handle0x15, asm_handle0x16, asm_handle0x17, asm_handle0x18, asm_handle0x19
    global asm_handle0x1a, asm_handle0x1b, asm_handle0x1c, asm_handle0x1d, asm_handle0x1e
    global asm_handle0x1f
    
	;; hardware interrupt handler
	global asm_handle0x20, asm_handle0x21, asm_handle0x22, asm_handle0x23, asm_handle0x24, asm_handle0x25
	global asm_handle0x26, asm_handle0x27, asm_handle0x28, asm_handle0x29, asm_handle0x2a, asm_handle0x2b
	global asm_handle0x2c, asm_handle0x2d, asm_handle0x2e, asm_handle0x2f
	global asm_handle0x30, asm_handle0x31, asm_handle0x32, asm_handle0x33, asm_handle0x34, asm_handle0x35
	global asm_handle0x36, asm_handle0x37, asm_handle0x38, asm_handle0x39, asm_handle0x3a, asm_handle0x3b
	global asm_handle0x3c, asm_handle0x3d, asm_handle0x3e, asm_handle0x3f
 	global asm_handle0x40, asm_handle0x41, asm_handle0x42, asm_handle0x43, asm_handle0x44, asm_handle0x45
	global asm_handle0x46, asm_handle0x47, asm_handle0x48, asm_handle0x49, asm_handle0x4a, asm_handle0x4b
	global asm_handle0x4c, asm_handle0x4d, asm_handle0x4e, asm_handle0x4f
	global asm_handle0x50, asm_handle0x51, asm_handle0x52, asm_handle0x53, asm_handle0x54, asm_handle0x55
	global asm_handle0x56, asm_handle0x57, asm_handle0x58, asm_handle0x59, asm_handle0x5a, asm_handle0x5b
	global asm_handle0x5c, asm_handle0x5d, asm_handle0x5e, asm_handle0x5f
	global asm_handle0x60, asm_handle0x61, asm_handle0x62, asm_handle0x63, asm_handle0x64, asm_handle0x65
	global asm_handle0x66, asm_handle0x67, asm_handle0x68, asm_handle0x69, asm_handle0x6a, asm_handle0x6b
	global asm_handle0x6c, asm_handle0x6d, asm_handle0x6e, asm_handle0x6f
	global asm_handle0x70, asm_handle0x71, asm_handle0x72, asm_handle0x73, asm_handle0x74, asm_handle0x75
	global asm_handle0x76, asm_handle0x77, asm_handle0x78, asm_handle0x79, asm_handle0x7a, asm_handle0x7b
	global asm_handle0x7c, asm_handle0x7d, asm_handle0x7e, asm_handle0x7f
	global asm_handle0x80, asm_handle0x81, asm_handle0x82, asm_handle0x83, asm_handle0x84, asm_handle0x85
	global asm_handle0x86, asm_handle0x87, asm_handle0x88, asm_handle0x89, asm_handle0x8a, asm_handle0x8b
	global asm_handle0x8c, asm_handle0x8d, asm_handle0x8e, asm_handle0x8f
	global asm_handle0x90, asm_handle0x91, asm_handle0x92, asm_handle0x93, asm_handle0x94, asm_handle0x95
	global asm_handle0x96, asm_handle0x97, asm_handle0x98, asm_handle0x99, asm_handle0x9a, asm_handle0x9b
	global asm_handle0x9c, asm_handle0x9d, asm_handle0x9e, asm_handle0x9f
	global asm_handle0xa0, asm_handle0xa1, asm_handle0xa2, asm_handle0xa3, asm_handle0xa4, asm_handle0xa5
	global asm_handle0xa6, asm_handle0xa7, asm_handle0xa8, asm_handle0xa9, asm_handle0xaa, asm_handle0xab
	global asm_handle0xac, asm_handle0xad, asm_handle0xae, asm_handle0xaf
	global asm_handle0xb0, asm_handle0xb1, asm_handle0xb2, asm_handle0xb3, asm_handle0xb4, asm_handle0xb5
	global asm_handle0xb6, asm_handle0xb7, asm_handle0xb8, asm_handle0xb9, asm_handle0xba, asm_handle0xbb
	global asm_handle0xbc, asm_handle0xbd, asm_handle0xbe, asm_handle0xbf
	global asm_handle0xc0, asm_handle0xc1, asm_handle0xc2, asm_handle0xc3, asm_handle0xc4, asm_handle0xc5
	global asm_handle0xc6, asm_handle0xc7, asm_handle0xc8, asm_handle0xc9, asm_handle0xca, asm_handle0xcb
	global asm_handle0xcc, asm_handle0xcd, asm_handle0xce, asm_handle0xcf
	global asm_handle0xd0, asm_handle0xd1, asm_handle0xd2, asm_handle0xd3, asm_handle0xd4, asm_handle0xd5
	global asm_handle0xd6, asm_handle0xd7, asm_handle0xd8, asm_handle0xd9, asm_handle0xda, asm_handle0xdb
	global asm_handle0xdc, asm_handle0xdd, asm_handle0xde, asm_handle0xdf
	global asm_handle0xe0, asm_handle0xe1, asm_handle0xe2, asm_handle0xe3, asm_handle0xe4, asm_handle0xe5
	global asm_handle0xe6, asm_handle0xe7, asm_handle0xe8, asm_handle0xe9, asm_handle0xea, asm_handle0xeb
	global asm_handle0xec, asm_handle0xed, asm_handle0xee, asm_handle0xef
	global asm_handle0xf0, asm_handle0xf1, asm_handle0xf2, asm_handle0xf3, asm_handle0xf4, asm_handle0xf5
	global asm_handle0xf6, asm_handle0xf7, asm_handle0xf8, asm_handle0xf9, asm_handle0xfa, asm_handle0xfb
	global asm_handle0xfc, asm_handle0xfd, asm_handle0xfe, asm_handle0xff

	
	;; software system call handler
	global asm_send_recv

    ;;a code segment without 'push 0', means this interrupt have error code in stack

asm_handle0x00:
	push 0
	push handle0x00
	jmp handler

asm_handle0x01:
	push 0
	push handle0x01
	jmp handler

asm_handle0x02:
	push 0
	push handle0x02
	jmp handler

asm_handle0x03:
	push 0
	push handle0x03
	jmp handler

asm_handle0x04:
	push 0
	push handle0x04
	jmp handler

asm_handle0x05:
	push 0
	push handle0x05
	jmp handler

asm_handle0x06:
	push 0
	push handle0x06
	jmp handler

asm_handle0x07:
	push 0
	push handle0x07
	jmp handler

asm_handle0x08:
	push handle0x08
	jmp handler

asm_handle0x09:
	push 0
	push handle0x09
	jmp handler

asm_handle0x0a:
	push handle0x0a
	jmp handler

asm_handle0x0b:
	push handle0x0b
	jmp handler

asm_handle0x0c:
	push handle0x0c
	jmp handler

asm_handle0x0d:
	push handle0x0d
	jmp handler

asm_handle0x0e:
	push handle0x0e
	jmp handler

asm_handle0x0f:
	push handle0x0f
	jmp handler

asm_handle0x10:
	push 0
	push handle0x10
	jmp handler

asm_handle0x11:
	push handle0x11
	jmp handler

asm_handle0x12:
	push 0
	push handle0x12
	jmp handler

asm_handle0x13:
	push 0
	push handle0x13
	jmp handler

asm_handle0x14:
	push 0
	push handle0x14
	jmp handler

asm_handle0x15:
	push 0
	push handle0x15
	jmp handler

asm_handle0x16:
	push 0
	push handle0x16
	jmp handler

asm_handle0x17:
	push 0
	push handle0x17
	jmp handler

asm_handle0x18:
	push 0
	push handle0x18
	jmp handler

asm_handle0x19:
	push 0
	push handle0x19
	jmp handler

asm_handle0x1a:
	push 0
	push handle0x1a
	jmp handler

asm_handle0x1b:
	push 0
	push handle0x1b
	jmp handler

asm_handle0x1c:
	push 0
	push handle0x1c
	jmp handler

asm_handle0x1d:
	push 0
	push handle0x1d
	jmp handler

asm_handle0x1e:
	push 0
	push handle0x1e
	jmp handler

asm_handle0x1f:
	push 0
	push handle0x1f
	jmp handler

	
;;; hardware interrupt handler
asm_handle0x20:
	push handle0x20
	jmp hard_handler

asm_handle0x21:
	push handle0x21
	jmp hard_handler

asm_handle0x22:
	push handle0x22
	jmp hard_handler

asm_handle0x23:
	push handle0x23
	jmp hard_handler

asm_handle0x24:
	push handle0x24
	jmp hard_handler

asm_handle0x25:
	push handle0x25
	jmp hard_handler

asm_handle0x26:
	push handle0x26
	jmp hard_handler

asm_handle0x27:
	push handle0x27
	jmp hard_handler

asm_handle0x28:
	push handle0x28
	jmp hard_handler

asm_handle0x29:
	push handle0x29
	jmp hard_handler

asm_handle0x2a:
	push handle0x2a
	jmp hard_handler

asm_handle0x2b:
	push handle0x2b
	jmp hard_handler

asm_handle0x2c:
	push handle0x2c
	jmp hard_handler

asm_handle0x2d:
	push handle0x2d
	jmp hard_handler

asm_handle0x2e:
	push handle0x2e
	jmp hard_handler

asm_handle0x2f:
	push handle0x2f
	jmp hard_handler

asm_handle0x30:
	push handle0x30
	jmp hard_handler

asm_handle0x31:
	push handle0x31
	jmp hard_handler

asm_handle0x32:
	push handle0x32
	jmp hard_handler

asm_handle0x33:
	push handle0x33
	jmp hard_handler

asm_handle0x34:
	push handle0x34
	jmp hard_handler

asm_handle0x35:
	push handle0x35
	jmp hard_handler

asm_handle0x36:
	push handle0x36
	jmp hard_handler

asm_handle0x37:
	push handle0x37
	jmp hard_handler

asm_handle0x38:
	push handle0x38
	jmp hard_handler

asm_handle0x39:
	push handle0x39
	jmp hard_handler

asm_handle0x3a:
	push handle0x3a
	jmp hard_handler

asm_handle0x3b:
	push handle0x3b
	jmp hard_handler

asm_handle0x3c:
	push handle0x3c
	jmp hard_handler

asm_handle0x3d:
	push handle0x3d
	jmp hard_handler

asm_handle0x3e:
	push handle0x3e
	jmp hard_handler

asm_handle0x3f:
	push handle0x3f
	jmp hard_handler

asm_handle0x40:
	push handle0x40
	jmp hard_handler

asm_handle0x41:
	push handle0x41
	jmp hard_handler

asm_handle0x42:
	push handle0x42
	jmp hard_handler

asm_handle0x43:
	push handle0x43
	jmp hard_handler

asm_handle0x44:
	push handle0x44
	jmp hard_handler

asm_handle0x45:
	push handle0x45
	jmp hard_handler

asm_handle0x46:
	push handle0x46
	jmp hard_handler

asm_handle0x47:
	push handle0x47
	jmp hard_handler

asm_handle0x48:
	push handle0x48
	jmp hard_handler

asm_handle0x49:
	push handle0x49
	jmp hard_handler

asm_handle0x4a:
	push handle0x4a
	jmp hard_handler

asm_handle0x4b:
	push handle0x4b
	jmp hard_handler

asm_handle0x4c:
	push handle0x4c
	jmp hard_handler

asm_handle0x4d:
	push handle0x4d
	jmp hard_handler

asm_handle0x4e:
	push handle0x4e
	jmp hard_handler

asm_handle0x4f:
	push handle0x4f
	jmp hard_handler

asm_handle0x50:
	push handle0x50
	jmp hard_handler

asm_handle0x51:
	push handle0x51
	jmp hard_handler

asm_handle0x52:
	push handle0x52
	jmp hard_handler

asm_handle0x53:
	push handle0x53
	jmp hard_handler

asm_handle0x54:
	push handle0x54
	jmp hard_handler

asm_handle0x55:
	push handle0x55
	jmp hard_handler

asm_handle0x56:
	push handle0x56
	jmp hard_handler

asm_handle0x57:
	push handle0x57
	jmp hard_handler

asm_handle0x58:
	push handle0x58
	jmp hard_handler

asm_handle0x59:
	push handle0x59
	jmp hard_handler

asm_handle0x5a:
	push handle0x5a
	jmp hard_handler

asm_handle0x5b:
	push handle0x5b
	jmp hard_handler

asm_handle0x5c:
	push handle0x5c
	jmp hard_handler

asm_handle0x5d:
	push handle0x5d
	jmp hard_handler

asm_handle0x5e:
	push handle0x5e
	jmp hard_handler

asm_handle0x5f:
	push handle0x5f
	jmp hard_handler

asm_handle0x60:
	push handle0x60
	jmp hard_handler

asm_handle0x61:
	push handle0x61
	jmp hard_handler

asm_handle0x62:
	push handle0x62
	jmp hard_handler

asm_handle0x63:
	push handle0x63
	jmp hard_handler

asm_handle0x64:
	push handle0x64
	jmp hard_handler

asm_handle0x65:
	push handle0x65
	jmp hard_handler

asm_handle0x66:
	push handle0x66
	jmp hard_handler

asm_handle0x67:
	push handle0x67
	jmp hard_handler

asm_handle0x68:
	push handle0x68
	jmp hard_handler

asm_handle0x69:
	push handle0x69
	jmp hard_handler

asm_handle0x6a:
	push handle0x6a
	jmp hard_handler

asm_handle0x6b:
	push handle0x6b
	jmp hard_handler

asm_handle0x6c:
	push handle0x6c
	jmp hard_handler

asm_handle0x6d:
	push handle0x6d
	jmp hard_handler

asm_handle0x6e:
	push handle0x6e
	jmp hard_handler

asm_handle0x6f:
	push handle0x6f
	jmp hard_handler

asm_handle0x70:
	push handle0x70
	jmp hard_handler

asm_handle0x71:
	push handle0x71
	jmp hard_handler

asm_handle0x72:
	push handle0x72
	jmp hard_handler

asm_handle0x73:
	push handle0x73
	jmp hard_handler

asm_handle0x74:
	push handle0x74
	jmp hard_handler

asm_handle0x75:
	push handle0x75
	jmp hard_handler

asm_handle0x76:
	push handle0x76
	jmp hard_handler

asm_handle0x77:
	push handle0x77
	jmp hard_handler

asm_handle0x78:
	push handle0x78
	jmp hard_handler

asm_handle0x79:
	push handle0x79
	jmp hard_handler

asm_handle0x7a:
	push handle0x7a
	jmp hard_handler

asm_handle0x7b:
	push handle0x7b
	jmp hard_handler

asm_handle0x7c:
	push handle0x7c
	jmp hard_handler

asm_handle0x7d:
	push handle0x7d
	jmp hard_handler

asm_handle0x7e:
	push handle0x7e
	jmp hard_handler

asm_handle0x7f:
	push handle0x7f
	jmp hard_handler

asm_handle0x80:
	push handle0x80
	jmp hard_handler

asm_handle0x81:
	push handle0x81
	jmp hard_handler

asm_handle0x82:
	push handle0x82
	jmp hard_handler

asm_handle0x83:
	push handle0x83
	jmp hard_handler

asm_handle0x84:
	push handle0x84
	jmp hard_handler

asm_handle0x85:
	push handle0x85
	jmp hard_handler

asm_handle0x86:
	push handle0x86
	jmp hard_handler

asm_handle0x87:
	push handle0x87
	jmp hard_handler

asm_handle0x88:
	push handle0x88
	jmp hard_handler

asm_handle0x89:
	push handle0x89
	jmp hard_handler

asm_handle0x8a:
	push handle0x8a
	jmp hard_handler

asm_handle0x8b:
	push handle0x8b
	jmp hard_handler

asm_handle0x8c:
	push handle0x8c
	jmp hard_handler

asm_handle0x8d:
	push handle0x8d
	jmp hard_handler

asm_handle0x8e:
	push handle0x8e
	jmp hard_handler

asm_handle0x8f:
	push handle0x8f
	jmp hard_handler

asm_handle0x90:
	push handle0x90
	jmp hard_handler

asm_handle0x91:
	push handle0x91
	jmp hard_handler

asm_handle0x92:
	push handle0x92
	jmp hard_handler

asm_handle0x93:
	push handle0x93
	jmp hard_handler

asm_handle0x94:
	push handle0x94
	jmp hard_handler

asm_handle0x95:
	push handle0x95
	jmp hard_handler

asm_handle0x96:
	push handle0x96
	jmp hard_handler

asm_handle0x97:
	push handle0x97
	jmp hard_handler

asm_handle0x98:
	push handle0x98
	jmp hard_handler

asm_handle0x99:
	push handle0x99
	jmp hard_handler

asm_handle0x9a:
	push handle0x9a
	jmp hard_handler

asm_handle0x9b:
	push handle0x9b
	jmp hard_handler

asm_handle0x9c:
	push handle0x9c
	jmp hard_handler

asm_handle0x9d:
	push handle0x9d
	jmp hard_handler

asm_handle0x9e:
	push handle0x9e
	jmp hard_handler

asm_handle0x9f:
	push handle0x9f
	jmp hard_handler

asm_handle0xa0:
	push handle0xa0
	jmp hard_handler

asm_handle0xa1:
	push handle0xa1
	jmp hard_handler

asm_handle0xa2:
	push handle0xa2
	jmp hard_handler

asm_handle0xa3:
	push handle0xa3
	jmp hard_handler

asm_handle0xa4:
	push handle0xa4
	jmp hard_handler

asm_handle0xa5:
	push handle0xa5
	jmp hard_handler

asm_handle0xa6:
	push handle0xa6
	jmp hard_handler

asm_handle0xa7:
	push handle0xa7
	jmp hard_handler

asm_handle0xa8:
	push handle0xa8
	jmp hard_handler

asm_handle0xa9:
	push handle0xa9
	jmp hard_handler

asm_handle0xaa:
	push handle0xaa
	jmp hard_handler

asm_handle0xab:
	push handle0xab
	jmp hard_handler

asm_handle0xac:
	push handle0xac
	jmp hard_handler

asm_handle0xad:
	push handle0xad
	jmp hard_handler

asm_handle0xae:
	push handle0xae
	jmp hard_handler

asm_handle0xaf:
	push handle0xaf
	jmp hard_handler

asm_handle0xb0:
	push handle0xb0
	jmp hard_handler

asm_handle0xb1:
	push handle0xb1
	jmp hard_handler

asm_handle0xb2:
	push handle0xb2
	jmp hard_handler

asm_handle0xb3:
	push handle0xb3
	jmp hard_handler

asm_handle0xb4:
	push handle0xb4
	jmp hard_handler

asm_handle0xb5:
	push handle0xb5
	jmp hard_handler

asm_handle0xb6:
	push handle0xb6
	jmp hard_handler

asm_handle0xb7:
	push handle0xb7
	jmp hard_handler

asm_handle0xb8:
	push handle0xb8
	jmp hard_handler

asm_handle0xb9:
	push handle0xb9
	jmp hard_handler

asm_handle0xba:
	push handle0xba
	jmp hard_handler

asm_handle0xbb:
	push handle0xbb
	jmp hard_handler

asm_handle0xbc:
	push handle0xbc
	jmp hard_handler

asm_handle0xbd:
	push handle0xbd
	jmp hard_handler

asm_handle0xbe:
	push handle0xbe
	jmp hard_handler

asm_handle0xbf:
	push handle0xbf
	jmp hard_handler

asm_handle0xc0:
	push handle0xc0
	jmp hard_handler

asm_handle0xc1:
	push handle0xc1
	jmp hard_handler

asm_handle0xc2:
	push handle0xc2
	jmp hard_handler

asm_handle0xc3:
	push handle0xc3
	jmp hard_handler

asm_handle0xc4:
	push handle0xc4
	jmp hard_handler

asm_handle0xc5:
	push handle0xc5
	jmp hard_handler

asm_handle0xc6:
	push handle0xc6
	jmp hard_handler

asm_handle0xc7:
	push handle0xc7
	jmp hard_handler

asm_handle0xc8:
	push handle0xc8
	jmp hard_handler

asm_handle0xc9:
	push handle0xc9
	jmp hard_handler

asm_handle0xca:
	push handle0xca
	jmp hard_handler

asm_handle0xcb:
	push handle0xcb
	jmp hard_handler

asm_handle0xcc:
	push handle0xcc
	jmp hard_handler

asm_handle0xcd:
	push handle0xcd
	jmp hard_handler

asm_handle0xce:
	push handle0xce
	jmp hard_handler

asm_handle0xcf:
	push handle0xcf
	jmp hard_handler

asm_handle0xd0:
	push handle0xd0
	jmp hard_handler

asm_handle0xd1:
	push handle0xd1
	jmp hard_handler

asm_handle0xd2:
	push handle0xd2
	jmp hard_handler

asm_handle0xd3:
	push handle0xd3
	jmp hard_handler

asm_handle0xd4:
	push handle0xd4
	jmp hard_handler

asm_handle0xd5:
	push handle0xd5
	jmp hard_handler

asm_handle0xd6:
	push handle0xd6
	jmp hard_handler

asm_handle0xd7:
	push handle0xd7
	jmp hard_handler

asm_handle0xd8:
	push handle0xd8
	jmp hard_handler

asm_handle0xd9:
	push handle0xd9
	jmp hard_handler

asm_handle0xda:
	push handle0xda
	jmp hard_handler

asm_handle0xdb:
	push handle0xdb
	jmp hard_handler

asm_handle0xdc:
	push handle0xdc
	jmp hard_handler

asm_handle0xdd:
	push handle0xdd
	jmp hard_handler

asm_handle0xde:
	push handle0xde
	jmp hard_handler

asm_handle0xdf:
	push handle0xdf
	jmp hard_handler

asm_handle0xe0:
	push handle0xe0
	jmp hard_handler

asm_handle0xe1:
	push handle0xe1
	jmp hard_handler

asm_handle0xe2:
	push handle0xe2
	jmp hard_handler

asm_handle0xe3:
	push handle0xe3
	jmp hard_handler

asm_handle0xe4:
	push handle0xe4
	jmp hard_handler

asm_handle0xe5:
	push handle0xe5
	jmp hard_handler

asm_handle0xe6:
	push handle0xe6
	jmp hard_handler

asm_handle0xe7:
	push handle0xe7
	jmp hard_handler

asm_handle0xe8:
	push handle0xe8
	jmp hard_handler

asm_handle0xe9:
	push handle0xe9
	jmp hard_handler

asm_handle0xea:
	push handle0xea
	jmp hard_handler

asm_handle0xeb:
	push handle0xeb
	jmp hard_handler

asm_handle0xec:
	push handle0xec
	jmp hard_handler

asm_handle0xed:
	push handle0xed
	jmp hard_handler

asm_handle0xee:
	push handle0xee
	jmp hard_handler

asm_handle0xef:
	push handle0xef
	jmp hard_handler

asm_handle0xf0:
	push handle0xf0
	jmp hard_handler

asm_handle0xf1:
	push handle0xf1
	jmp hard_handler

asm_handle0xf2:
	push handle0xf2
	jmp hard_handler

asm_handle0xf3:
	push handle0xf3
	jmp hard_handler

asm_handle0xf4:
	push handle0xf4
	jmp hard_handler

asm_handle0xf5:
	push handle0xf5
	jmp hard_handler

asm_handle0xf6:
	push handle0xf6
	jmp hard_handler

asm_handle0xf7:
	push handle0xf7
	jmp hard_handler

asm_handle0xf8:
	push handle0xf8
	jmp hard_handler

asm_handle0xf9:
	push handle0xf9
	jmp hard_handler

asm_handle0xfa:
	push handle0xfa
	jmp hard_handler

asm_handle0xfb:
	push handle0xfb
	jmp hard_handler

asm_handle0xfc:
	push handle0xfc
	jmp hard_handler

asm_handle0xfd:
	push handle0xfd
	jmp hard_handler

asm_handle0xfe:
	push handle0xfe
	jmp hard_handler

asm_handle0xff:
	push handle0xff
	jmp hard_handler

	
	;; system call handler
asm_send_recv:
	cli
	push es
	push ds
	pushad
	mov eax,esp
	mov ax,ss
	mov ds,ax
	mov es,ax
	push edx
	call sys_send_recv
	pop edx
	popad
	pop ds
	pop es
	sti
	iretd
	
	;; stftware exception handler
	;; if there is error code,then it is there
	;; if not,use '0' to fill this place
handler:
	push es
	push ds
	push eax
	push ecx
	push edx
	push ebx
	push esp
	push ebp
	push esi
	push edi
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	mov ecx,[ss:esp+48]
	mov ebx,[ss:esp+52]
	mov eax,[ss:esp+44]
	push ecx           ;; error code
	push ebx           ;; ip address
	call eax
	add esp,12
	pop edi
	pop esi
	pop ebp
	pop esp
	pop ebx
	pop edx
	pop ecx
	pop eax
	pop ds
	pop es
	add esp,8
	iretd
	
	;; hardware interrupt
hard_handler:
	push es
	push ds
	push eax
	push ecx
	push edx
	push ebx
	push esp
	push ebp
	push esi
	push edi
	mov ax,ss
	mov ds,ax
	mov es,ax
	mov eax,[ss:esp+40]
	call eax
	pop edi
	pop esi
	pop ebp
	pop esp
	pop ebx
	pop edx
	pop ecx
	pop eax
	pop ds
	pop es
	add esp,4
	iretd
