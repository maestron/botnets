;startu-up code for Roman Legionar 32-bit
.386p
.model flat

EXTRN _main:PROC

.data
db 0


.code
start:

	call _main
	ret

end start
ends




