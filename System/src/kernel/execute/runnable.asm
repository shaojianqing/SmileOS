global _start
extern initApplication

[bits 32]

_start:
	call initApplication
	ret
