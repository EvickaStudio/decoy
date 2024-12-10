# Dummy implementation using MASM32

This is the implementation of the dummy program using MASM32.

## How to build

1. Install [MASM32](https://www.masm32.com/download.htm).
2. Execute the `makeit.bat` script.
3. Now you should have the `dummy.exe` file in the masm32 directory.

## Replacement?

I just tested this implementation briefly, so I'm not sure if it's a good replacement for the original c implementation. It works of course, but without a deep analysis. The compiled size is only 3KB, the C implementation is 12KB without using an packer like UPX. It might be a little smaller in size, but looking at the Task Manager, the C implementation uses less memory. The C implementation uses 0.3MB of memory, the MASM32 implementation uses 0.4MB. This might be due to different optimizations of the C-Compiler. As is didn't analyzed it deeply, I can't say it might use less CPU or not, as the Task Manager doesn't show a difference in CPU usage (0% for both). So, it might be a good replacement, but I can't say it for sure.
