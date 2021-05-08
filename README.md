# Virtual Memory Manager 
CPSC 351 - Kalena Singbandith 


Your program will read a file containing several 32-it integer numbers that represent logical addresses.<br>
However, you need only be concerned with 16-bit addresses, so you must mask the rightmost 16 bits of
each logical address. These 16 bits are divided into (1) an 8-bit page number, and (2) an 8-bit offset.
Hence, the addresses are structured as shown as:<br>
Other specifics include the following: <br>
• 2^8 (256) entries in the page table <br>
• Page size of 2^8 bytes (256 bytes per page) <br>
• 16 entries in the TLB<br>
• Frame size of 2^8 bytes (256 bytes), so one page == one frame. This is not normally the
case, and it won’t be the case in the second part of this simulation. <br>
• 256 frames<br>
• Physical memory of 65,536 bytes (256 frames x 256-byte frame size)<br>
Also, your program need only be concerned with reading logical addresses and translating them to their
corresponding physical addresses. You don’t need to support writing to the logical address space.


After completion, your program is to report the following statistics:
1. Page-fault rate -- the percentage of address references that resulted in page faults.
2. TLB hit rate -- the percentage of address references that were resolved in the TLB.
Since the logical address in addresses.txt were generated randomly, and do not reflect any memory
access locality, do not expect to have a high TLB hit rate
