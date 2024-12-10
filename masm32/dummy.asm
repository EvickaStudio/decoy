; -----------------------------------------------------
; A dummy MASM32 program that runs indefinitely,
; using minimal resources by sleeping in an infinite loop.
; -----------------------------------------------------

include \masm32\include\masm32rt.inc

; No need for uninitialized or initialized data, 
; but if needed, they can be declared here.
.data?
; (No variables needed)

.data
; (No initialized variables needed)

.code

; The program entry point
start:
    ; Call our main procedure and then exit if it ever returned (it won't).
    call main
    exit

main proc
    ; Infinite loop: Sleep for 1000 ms, then repeat.
    loop_start:
        invoke Sleep, 1000  ; Sleep(1000 ms) to reduce CPU usage
        jmp loop_start
main endp

end start

