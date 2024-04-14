.686P
.MODEL FLAT, C
.CODE

get_time	PROC
			rdtsc
            shl edx, 32
            add eax, edx
			ret
get_time	ENDP

END
