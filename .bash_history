clear
make
cd build/
pintos --gdb -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
ls
cd threads/
vim interrupt.c
cd ..
cd userprog/
cd build/
clear
pintos --gdb -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
cd tests/
ls
cd threads/
ls
vim priority-fifo.c
clear
cd pintos/src/threads/
vim thread.h
cd ..
cd userprog/
vim syscall.c
vim syscall.h
clear
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
vim process.c
make
clear
cd build/
(exec-missing) begin
load: no-such-file: open failed
(exec-missing) exec("no-such-file"): -1
(exec-missing) end
exec-missing: exit(0)
no-such-file: exit(-1)
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
clear
vim process.c
make
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
vim process.c
clear
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
cd ..
vim process.
vim process.c
make
vim process.c
make
clear
cd build/
pintos --gdb -v --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
CLEAR
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
vim process.c
make
cd build/
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -j 1 -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -j 2 -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -v -k -T -j 1 60 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -v -k -j 2 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -v -k -j 3 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -v -k -j 4 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -v -k -j 5 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
ls
cd ..
vim process.c
make
vim process.c
make
cd build/
pintos --gdb -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
pintos -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
cd ..
ls
vim process.c
make
vim process.
vim process.c
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
pintos -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos --gdb -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
make
pintos -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
cd build/
ls
pintos -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clera
clear
pintos --gdb -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
cd ..
make clean
make
cd build/
clear
make
pintos -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
make
cd build/
pintos -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
make
cd build/
clear
pintos -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
make
pintos -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos --gdb -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
clear
vim process.c
ls
cd ..
cscope
clear
cd userprog/
cd build/
pintos --gdb -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
q!
cd ..
clear
vim process.c
make
make check
c;ear
clear
cd build/
pintos -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
make check
cd ..
clear
vim process.c
make
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
cd ..
cd build/
cd ..
cd process.c
vim process.c
make
clear
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
vim process.c
make
vim process.c
make
cd build/
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
cd ..
make
make check
vim syscall.c
ckear
clear
vim exception.c
make
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/bad-read -a bad-read -- -q  -f run bad-read
cd ..
make check
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/bad-write2 -a bad-write2 -- -q  -f run bad-write2
cd ,,
cd ..
cd threads/
ls
vim thread.h
cd ..
cd filesys/
ls
vim file.h
cd ..
cd userprog/
vim syscall.c
make
cd build/
Call stack: 0xc002aac4 0xc0023369 0xc002d4d3 0xc0021150 0xc002ed82 0xc002eded 0xc00220f7 0xc002234f 0xc002d50c 0xc0021150 0xc002f254 0xc002f796 0xc00220f7 0xc002234f 0x804b2f6 0x80481c0 0x80482a2 0x8048ba6.
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
backtrace Call stack: 0xc002aac4 0xc0023369 0xc002d4d3 0xc0021150 0xc002ed82 0xc002eded 0xc00220f7 0xc002234f 0xc002d50c 0xc0021150 0xc002f254 0xc002f796 0xc00220f7 0xc002234f 0x804b2f6 0x80481c0 0x80482a2 0x8048ba6.
cd ..
vim syscall.c
clear
cd ..
cd userprog/
vim exception.c
cd build/
pintos --gdb -v -k --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
cd pintos/src/
cscope
cd filesys/
vim file.h
cd ..
cd userprog/
ls
vim syscall.c
clear
vim syscall.c
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
ls
cd ..
cd build/
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
cd ..
cd build/
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
ls
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
cd ..
cd build/
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
ls
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
cd ..
cd build/
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
cd pintos/src/filesys/
vim filesys.c
vim file.c
cd ..
cd tests/userprog/
vim read-normal.c
vim exec-missing.c
vim exec-missing.ck
vim exec-missing.c
vim exec-missing.ck
vim rox-simple.c
vim rox-simple.ck
vim rox-simple.c
make
vim rox-simple.c
clear
vim exec-missing.c
vim exec-missing.ck
vim exec-missing.c
vim exec-missing.ck
vim exec-missing.c
vim exec-missing.ck
vim exec-missing.c
vim exec-missing.ck
ls
vim bad-read
vim bad-read.c
vim bad-read.ck
clear
vim bad-read2.c
vim bad-write2.c
vim bad-jump2.c
ls
cd no-vm/
ls
clear
vim multi-oom.c
ls
vim multi-oom.c
vim multi-oom.ck
vim multi-oom.c
cd pintos/src/
cd userprog/build/
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
clear
cd ..
vim syscall.c
make
vim exception.c
make
cd build/
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
cd ...
cd ..
ls
vim process.c
make
vim process.c
cd pintos/src/userprog/
make check
clear
make clean
make
clear
make check
clear
vim syscall.c
make
203
make
clear
make check
clear
cd build/
Acceptable output:
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-normal -a read-normal -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run read-normal
clear
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-normal -a read-normal -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run read-normal
clear
cd ..
make check
clear
make
clear
make check
clera
clear
vim process.c
make
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/wait-twice -a wait-twice -p tests/userprog/child-simple -a child-simple -- -q  -f run wait-twice
clear
cxd ..
cd ..
clear
vim process.c
make
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/wait-twice -a wait-twice -p tests/userprog/child-simple -a child-simple -- -q  -f run wait-twice
ckear
clear
cd ..
make check
cd build/
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/rox-simple -a rox-simple -- -q  -f run rox-simple
make
(rox-simple) begin
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/rox-simple -a rox-simple -- -q  -f run rox-simple
cd ..
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/rox-simple -a rox-simple -- -q  -f run rox-simple
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/rox-simple -a rox-simple -- -q  -f run rox-simple
cd ..
clear
make clean
make
clear
make
clear
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/rox-simple -a rox-simple -- -q  -f run rox-simple
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/rox-simple -a rox-simple -- -q  -f run rox-simple
cd ..
clear
make
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/rox-simple -a rox-simple -- -q  -f run rox-simple
cd..
cd ..
clear
vim process.c
make
vim process.c
make
clear
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/rox-simple -a rox-simple -- -q  -f run rox-simple
cd ..
make
clear
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/rox-simple -a rox-simple -- -q  -f run rox-simple
clear
cd ..
make check
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
cd ..
vim syscall.c
make
make check
clear
cd build/
(exec-missing) begin
load: no-such-file: open failed
no-such-file: exit(-1)
(exec-missing) exec("no-such-file"): -1
(exec-missing) end
exec-missing: exit(0)
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
make clean
make
clkear
clear
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
cd ..
ls
vim process.c
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
pintos --gdb -v --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
pintos --gdb -v --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
pintos --gdb -v --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
pintos --gdb -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
cd ..
vim process.c
make
vim process.c
cd ../devices/
vim timer.c
cd ..
vim devices/timer.
vim devices/timer.c
cd threads/
clear
vim thread.c
vim init.c
vim thread.c
cd ..
vim devices/timer.c
cd userprog/
cd build/
pintos --gdb -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
CLEAR
clear
cd ..
make
cd build/
pintos -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
make
make check
clear
vim process.c
cd ..
cd filesys/
ls
vim file.c
vim file.h
vim file.c
vim file.h
cd ..
cd threads/
vim thread.c
vim thread.h
cd ..
cd userprog/
vim syscall.c
cd build/
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
backtrace Call stack: 0xc002aac4 0xc0023369 0xc002d4d3 0xc0021150 0xc002ed82 0xc002eded 0xc00220f7 0xc002234f 0xc002d50c 0xc0021150 0xc002f254 0xc002f796 0xc00220f7 0xc002234f 0x804b2f6 0x80481c0 0x80482a2 0x8048ba6.
cd ..
vim syscall.c
clear
ls
vim process.c
vim syscall.c
cd pintos/src/filesys/
vim file.c
cd ..
cd threads/
vim interrupt.c
cd ..
cd threads/
vim init.c
clear
cd ..
ls
cd userprog/
ls
clear
vim syscall.c
make
make check
clear
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos --gdb -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
pintos -v -k -j 1 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -v -k -j 2 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -v -k -j 3 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -v -k -j 4 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -v -k -j 5 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -v -k -j 6 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -v -k -j 7 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
pintos -v -k -j 8 --bochs  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
clear
cd ..
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/exec-missing -a exec-missing -- -q  -f run exec-missing
cd ..
vim exception.c
vim pagedir.h
vim pagedir.c
cd ..
cscope
cd userprog/
vim exception.c
ls
vim exception.c
make
vim exception.c
majke
make
vim exception.c
make
vim syscall.c
vim exception.c
make
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/bad-read2 -a bad-read2 -- -q  -f run bad-read2
cd ..
vim exception.c
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/bad-jump2 -a bad-jump2 -- -q  -f run bad-jump2
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/bad-jump2 -a bad-jump2 -- -q  -f run bad-jump2
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/bad-jump2 -a bad-jump2 -- -q  -f run bad-jump2
clear
cd ..
make
make check
clear
vim process.c
make
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
cd build/
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
backtrace Call stack: 0xc002aac4 0xc0023369 0xc002d4d3 0xc0021150 0xc002ed82 0xc002eded 0xc00220f7 0xc002234f 0xc002d50c 0xc0021150 0xc002f254 0xc002f796 0xc00220f7 0xc002234f 0x804b2f6 0x80481c0 0x80482a2 0x8048ba6.
clear
cd ..
vim process.c
make check
clear
cd build/
ls
Call stack: 0xc002aac4 0xc0023369 0xc002d4d3 0xc0021150 0xc002ed82 0xc002eded 0xc00220f7 0xc002234f 0xc002d50c 0xc0021150 0xc002f254 0xc002f796 0xc00220f7 0xc002234f 0x804b2f6 0x80481c0 0x80482a2 0x8048ba6.
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
cd ..
vim process.c
make
0xc002aac4: debug_panic (.../../lib/kernel/debug.c:38)
0xc0023369: lock_acquire (...../../threads/synch.c:231)
0xc002d4d3: process_exit (...../userprog/process.c:181)
0xc0021150: thread_exit (..../../threads/thread.c:307)
0xc002ed82: page_fault (.../userprog/exception.c:130)
0xc002eded: page_fault (.../userprog/exception.c:160)
0xc00220f7: intr_handler (..../threads/interrupt.c:367)
0xc002234f: intr_entry (threads/intr-stubs.S:38)
0xc002d50c: process_exit (...../userprog/process.c:188)
0xc0021150: thread_exit (..../../threads/thread.c:307)
0xc002f254: sys_open (...../userprog/syscall.c:174)
0xc002f796: syscall_handler (...../userprog/syscall.c:360)
0xc00220f7: intr_handler (..../threads/interrupt.c:367)
0xc002234f: intr_entry (threads/intr-stubs.S:38)
0x0804b2f6: (unknown)
0x080481c0: (unknown)
0x080482a2: (unknown)
0x08048ba6: (unknown)
clear
cd build/
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
cd ..
clear
vim process.c
make
cd build/
pintos --gdb -v -k -T 360 --qmenu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
pintos -v -k -T 360 --qmenu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
cd ..
vim syscall.c
vim process.c
clear
make
cd build/
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
cd ..
cd build/
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
clear
pintos -v -k -T 360 --qmenu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
clear
cd pintos/src/userprog/
cd ..
cd filesys/
ls
vim file.c
vim file.h
ls
vim file.c
cd pintos/src/
cd userprog/
vim syscall.c
make
cd build/
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
clear
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
cd ..
vim syscall.c
make
cd build/
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
clear
cd pintos/src/tests/use
cd pintos/src/tests/userprog/
vim no-vm/
cd no-vm/
vim multi-oom.c
cd ..
cd userprog/
clear
ls
cd build/
pintos-gdb kernel.o
clar
clear
cd pintos/src/threads/
vim malloc.c
cd pintos/src/userprog/
ls
cd ..
cd tests/userprog/
vim open-boundary.c
vim open-missing.c
cd pintos/src/filesys/
ls
vim file.c
vim filesys.c
vim file.c
vim filesys.c
cd pintos/src/userprog/
vim process.c
make
vim process.c
make
cd build/
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
vim process.c
clear
ls
cd ..
vim process.c
vim exception.c
vim syscall.c
make
vim syscall.c
make
cd bio
cd build/
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
cd ..
vim process.c
vim syscall.c
vim process.c
make
make chck
make check
vim process.c
vim syscall.c
make
clear
make check
clear
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
cd ..
make
cd build/
cleraq
clear
Call stack: 0xc002aac4 0xc0023369 0xc002d4d3 0xc0021150 0xc002ed8a 0xc002ee44 0xc00220f7 0xc002234f 0xc002d50c 0xc0021150 0xc002f0b4 0xc002f6df 0xc00220f7 0xc002234f 0x804aab8 0x8048920.
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
clear
ls
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
quit
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
cd ..
vim process.c
make
makec check
make check
vim syscall.c
make
clear
make check
cd build/
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-missing -a open-missing -- -q  -f run open-missing
cd ..
cd by
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-missing -a open-missing -- -q  -f run open-missing
cd ..
make
clear
make check
cd ..
git add .
cd ..
git add .
cd team22a
ls
cd home/
ls
cd team22a
ls
git add .
git commit -m "except multi-o0m"
git push origin master
cd pintos/src/use
cd pintos/src/userprog/
cd build/
pintos -v -k -T 360 --qemu  --filesys-size=2 -p tests/userprog/no-vm/multi-oom -a multi-oom -- -q  -f run multi-oom
clear
ls
cd ..
ls
vim process.c
cd ..
cscope
cd userprog/
vim process.c
clear
ls
cd pintos/src/
ls
cd userprog
ls
make
make grade
cd ..
ls
cd ..
ls
tar -czvf team22_project2.tar.gz src Project_2_Document_Templet.docx
ls
vim team22_project2.tar.gz
cd pintos/src/userprog/
vim exception.c
vim syscall.c
clear
ls
vim process.c
vim syscall.c
make
cdlear
vim process.c
vim syscall.c
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
cd ..
vim syscall.c
make
clear
vim process.c
make
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
cd ..
vim syscall.c
vim process.c
vim exception.c
make
cd build/
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
cd ..
clear
cd build/
ls
cd ..
vim process.c
make
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
backtrace Call stack: 0xc002aac4 0xc0023369 0xc002d4d3 0xc0021150 0xc002ed8a 0xc002ee44 0xc00220f7 0xc002234f 0xc002d50c 0xc0021150 0xc002f0b4 0xc002f6df 0xc00220f7 0xc002234f 0x804aab8 0x8048920.
cd ..
clear
vim process.c
make
vim process.c
make
vim process.
vim process.c
make
clear
cd build/
cd ..
vim process.c
make
vim syscall.c
make
clear
make check
vim exception.c
clear
vim process.c
vim syscall.c
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
cd ..
vim syscall.c
vim process.c
vim syscall.c
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run open-boundary
cd ..
make check
make clean
make check
cd ..
git add .
git commit -m "project 2 finished"
git push origin master
clear
cd pintos/src/userprog/
make chek
make check
make clean
make check
ls
cd pintos/
cd src
cd userprog/
vim syscall.h
ls
vim process.h
vim exception.c
vim pagedir.c
vim pagedir.h
vim pagedir.c
vim pagedir.h
cscope
cd pintos/src/
ls
cd userprog
ls
vim process.c
cd ..
cd threads/
vim thread.c
cd ..
cd userprog/
vim process.c
exit
cd pintos/src/
cd userprog/
ls
cd syscall.c
vim syscall.c
cd ..
cd tests
cd userprog/
ls
vim args.c
vim create-long.c
vim exec-arg.c
vim multi-recurse
vim multi-recurse.c
exit
ls
cd pintos/src/
ls
cd vm
ls
cd ..
cd devices/
vim block.c
vim block.h
clear
cd pintos/src/
ls
cd devices/
ls
vim block.c
cd ..
cd threads/
clear
vim vaddr.h 
cd ..
ls
cd vm
ls
cd ..
cd userprog/
ls
vim pagedir.c
cd pintos/src/
cd threads/
vim thread.c
vim init.c
cd ..
cd userprog/
vim process.c
cd pintos/src/threads/
vim pte.h 
cd ..
cd vm/
ls
clear
cd ..
cd tests/vm/
ls
vim parallel-merge.c
cd ..
cscope
ls
cd threads/
ls
clear
cd ..
cd userprog/
ls
cd ..
cd filesys/
ls
cd ..
cscope
cd threads/
vim init.c
cd ..
cd devices/
ls
vim block.c
vim block.h
vim block.c
cd pintos/src/vm/
ls
cd ..
cd userprog/
vim process.c
cd pintos/src/userprog/
vim process.c
vim exception.c
clear
cd ..
cd userprog/
vim pagedir.c
EXIT
exit
cd pintos/src/userprog/
ls
vim process.c
vim exception.c
vim interrupt.h
cd ..
cd threads/
vim interrupt.c
vim interrupt.h
cd ..
cd userprog/
vim process.c
rm .process.c.swp 
vim process.c
cd ..
cd threads/
vim interrupt.c
cd ..
cd filesys/
ls
vim file.c
vim inode.c
cd ..
cd devices/
vim block.c
vim block.h
vim block.c
cd ..
cscope
cd userprog/
clear
vim process.c
vim syscall.c
exit
cd pintos/src/userprog/
vim process.c
clear
cd pintos/src/
ls
cd threads/
vim thread.h
vim synch.h
clear
ls
cd ..
cd tests/
ls
cd vm/
ls
vim child-inherit.c 
ccd ..
cd ..
cd userprog/
vim Makefile 
cd ..
vim Makefile
vim Makefile.build 
cd userprog/
ls
vim process.h
vim process.c
cd ..
cd threads/
vim thread.h
vim thread.c
vim thread.h
cd ..
cd userprog/
cd ..
cd vm/
vim frame.c
vim frame.h
vim frame.c
vim frame.h
vim frame.c
clear
vim frame.c
cd ..
cd pintos/
git commit
cd ..
clear
git add .
git status
git commit -m "make struct frame"
git push
cd pintos/src/vm/
ls
clear
vim frame.c
make check
clear
ls
vim frame.c
cd pintos/src/
ls
cd userprog/
ls
clear
vim process.c
make
clear
make check
cd ..
clear
ls
cd threads/
ls
cd ..
ls
cd userprog/
ls
vim pagedir.c
ls
clear
cd ..
cd vm
ls
cd ..
cd userprog/
vim process.c
cd ..
cd vm
ls
vim frame.c
vim Makefile 
vim Make.vars 
cd ..
ls
vim Makefile.build 
cd vm/
vim frame.c 
vim frame.h
vim frame.c
vim frame.h
clear
ls
clear
vim frame.c
vim frame.h
vim frame.c
vim frame.h
vim frame.c
vim frame.h
make
clear
make
clear
make
clear
make
clear
make
clear
make
clear
cd ..
cd userprog/
vim pagedir.c
cd ..
cscope
cd userprog/
vim pagedir.c
cd ..
cscope
cd pintos/src/vm/
ls
vim frame.c
ls -al
rm .frame.c.swp 
vim frame.c
vim frame.h
vim frame.c
vim frame.h
vim frame.c
make
vim frame.c
clear
vim frame.h
vim frame.c
vim frame.h
make
vim frame.c
make
clear
vim frame.c
make
vim frame.c
make
clear
vim frame.c
cd pintos/src/userprog/
vim pagedir.c
vim process.c
cd ..
cd threads/
vim thread.h
vim synch.c
vim init.c
vim synch.h
cd ..
cd userprog/
clear
ls
vim pagedir.c
cd pintos/src/vm/
ls
vim frame.h
cd pintos/src/userprog/
vim pagedir.c
cd ..
cd lib/
cd kernel/
vim list.c
cd ..
cd threads/
lks
ls
vim thread.c
vim thread.h
exit
xit
exit
cd pintos/src/vm/
lsa
ls
clear
vim frame.c
vim frame.h
make
clear
cd ..
ls
cd lib/kernel/
vim list.c
cd ../..
cd vm/
vim frame.c
vim frame.h
vim frame.c
make
vim frame.c
make
clear
make check
c d..
cd ../../
cd ..
git add .
git statgus
git status
git commit -m "Suggeted order 1 done"
git push
clear
cd pintos/src/vm/
clear
vim page.c
vim page.h
cd ..
vim Makefile.build 
cd vm/
cd pintos/src/threads/
vim palloc.c
vim palloc.h
cd pintos/src/vm/
lks
ls
vim frame.c
vim frame.h
cd ..
cd userprog/
vim exception.c
cd ..
cd vm
vim frame.c
cd pintos/src/userprog/
ls
vim process.c
vim exception.c
cd ..
cd vm
ls
vim frame.h
cd ..
cd userprog/
vim process.h
vim process.c
cd ..
cd vm/
vim frame.c
vim page.c
make
clear
make
clear
make
vim page.c
make
makle
make
clear
make
make check
cd ..
cd userprog/
make check
make
clear
make
cd ..
cd vm/
cd ..
cd threads/
vim init.c
cd ..
clear
cd lib/
ls
cd kernel/
ls
cd ..
ls
cd ..
cd tests/
ls
cd vm/
ls
vim pt-write-code
vim pt-write-code.c
clear
exit
cd pintos/src/vm
ls
clear
ls
vim page.c
cd ..
cd filesys/
vim filevim file.c
vim file.c
cd ..
cscope
cd threads/
vim synch.h
cd ..
cd vm
vim frame.h
cd ..
cd threads/
vim init.c
cd ..
cd userprog/
vim pagedir.c
vim process.c
cd ..
cd lib/kernel/
ls
cd ..
ls
vim inttypes.h 
cd ..
cscope
cd threads/
vim init.c
make
cd ..
cd userprog/
make
vim init.c
clear
make
make clean
clear
make
cd ..
cd vm
make
make check
clear
vim page.c
exit
cd pintos/src/vm/
ls
vim page.c
vim page.h
cd ..
cd userprog/
vim exception.c
cd ..
cd vm
ls
vim frame.c
vim page.h
vim page.c
vim page.h
cd ..
cd userprog/
ls
vim exception.c
cd ..
cd vm
vim page.h
vim page.c
vim page.h
clear
ls
clear
vim frame.c
exit
cd pintos/src/threads/
ls
vim thread.h
vim thread.c
cd ..
clear
ls
cd vm/
vim frame.h
cd ..
cd threads/
vim thread.h
cd ..
cd vm/
vim frame.h
vim page.h
vim frame.c
make
cd ..
cd threads/
vim init.c
cd ..
cd vm/
make
clar
clear
make 
make
clear
cd ..
git add .
git status
git commit -m "finish frame.c"
cd pintos/src/vm/
ls
clear
vim page.c
vim frame.c
vim page.h
make
vim page.c
vim page.h
clear
make
clear
make
cd ..
cscope
cd vm
clear
make
cd ..
cd vm/
make
clear
make
cd pintos/src/vm
vim page.c
vim frame.c
vim frame.h
vim vim page.c
vim page.c
vim page.h
clear
cd ..
cd userprog/
vim syscall.c
vim syscall.h
cd ..
cd vm
vim frame.c
cd ..
cd userprog/
vim pagedir.c
cd ..
cd vm/
vim frame.c
vim frame.h
vim frame.c
vim frame.h
vim page.c
vim page.h
maek
make
vim frame.c
cd pintos/src/filesys/
vim file.c
cd ..
cd vm
vim frame.h
cd ..
cd threads/
vim thread.c
cd ..
cd userprog/
vim process.c
vim page.c
clear
vim exception.c
vim process.c
vim exception.c
vim process.c
vim exception.c
vim process.c
vim exception.c
vim process.c
vim exception.c
cd ..
cd vm
clear
vim frame.c
CD ..
cd ..
cd userprog/
vim exception.c
vim exception.h
vim exception.c
vim exception.j
vim exception.h
cd ..
cd vm/
vim frame.c
cd pintos/src/filesys/
vim file.c
cd ..
cd userprog/
vim pagedir.c
vim process.c
vim exception.c
vim pagedir.c
cd ..
cd lib/kernel/
vim list.c
cd pintos/src/
cd lib/kernel/
vim hash.h
cd ../..
cd threads/
vim thread.h
cd ..
cd userprog/
vim pagedir.c
cd ..
cd filesys/
cd ..
cd vm
ls
clear
ls
vim page.c
vim page.h
vim frame.c
vim page.c
vim frame.c
cd ..
cd userprog/
vim process.c
cd ..
cd vm
vim frame.c
vim frame.h
cd pintos/src/vm
ls
cd ..
cd userprog/
ls
vim process.c
vim exception.c
cd ..
cd vm/
make
make check
cd pintos/src/vm/
vim frame.c
cd ..
ls
cd lib/kernel/
ls
cd ..
ls
vim string.g
vim string.h
vim string.c
cd ..
cscope
cd vm
ls
cd build/
cd ..
make clean
makec heck
make check
cd build/
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none 
clear
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none 
c d..
cd ..
clear
vim page.c
clear
vim page.h
vim page.c
vim frame.c
make
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none 
cd ..
make
clear
make check
make
clear
make check
cd pintos/src/vm/
make clean
make check
c d..
cd ..
cd threads/
ls
clear
vim thread.c
cd ..
cd vm
make
make check
clear
cd ..
cd userprog/
vim exception.v
vim exception.c
vim process.c
make
clear
vim process.c
cd pintos/src/vm/build/
pintos-gdb kernel.o
clear
pintos-gdb kernel.o
cd ..
cd vm
cd build/
pintos-gdb kernel.
pintos-gdb kernel.o
clear
ls
cd pintos/src/vm
ls
clear
cd ..
cd tests/
ls
cd userprog/
ls
vim read-boundary.c
make
vim read-boundary.c
cd pintos/src/vm
vim page.c
vim page.h
make
vim frame.c
make
vim frame.c
make
make check
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none 
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none 
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary 
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary --swap-size=4 -- -q  -f run open-boundary 
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
cd ..
cd lib/
vim round.h 
cd ..
cd vm/
cd build/
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
make check
cd pintos/src/vm
ls
clear
vim page.c
vim page.h
vim page.c
ls -al
rm .page.c.swp 
vim page.c
make
clear
make check
make
clear
make
make check
cd build/
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none 
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary 
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
clear
cd ..
make
cd build/
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
pintos -v -k --bochs  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
clear
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
clear
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
make
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
cd ..
make check
clear
make
makecheck
make check
clear
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary --swap-size=4 -- -q  -f run read-boundary
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-boundary -a open-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run open-boundary
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-normal -a open-normal -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run open-normal
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-normal -a open-normal -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run open-normal
make
clear
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
make
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/open-normal -a open-normal -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run open-normal
CD ..
cd ..
vim page.c
clear
make
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/open-normal -a open-normal -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run open-normal
pintos --gdb -v -k --bochs  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
make
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
make
clear
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/read-boundary -a read-boundary -p ../../tests/userprog/sample.txt -a sample.txt --swap-size=4 -- -q  -f run read-boundary
clear
cd ..
cd filesys/
vim file.c
vim inode.c
ls
cd ..
cd threads/
cd ..
ls
cscope
cd vm
make check
ls
cd pintos/
cd src
ls
cd tests/
ls
cd vm
ls
cd ..
cd userprog/
ls
vim read-boundary.c
vim open-boundary.c
vim read-boundary.c
vim read-bad-ptr.c
vim read-boundary.c
vim open-boundary.c
vim boundary.c
vim read-boundary.c
clear
ls
vim read-normal.c
vim open-empty.c
clear
ls
vim open-boundary.c
vim boundary.c
vim open-normal.c
vim boundary.c
vim open-boundary.c
clear
ls
vim open-boundary.c
vim read-boundary.c
vim open-bad-ptr.c
cd pintos/src/tests/
ls
cd userprog/
ls
vim open-boundary.c
cd lib/
ls
cd ..
vim sample.inc 
cd ..
cd vm/
cd ..
cd vm/
cd build/
pintos-gdb kernel.o
cd ..
cd build/
clear
make
pintos-gdb kernel.o
clear
cd ..
cd build/
pintos-gdb kernel.o
cd ..
cd userprog/
ls
vim exception.c
vim process.c
vim exception.c
vim syscall.c
cd pintos/src/userprog/
vim exception.c
vim process.c
cd ..
vim threads/
cd threads/
vim thread.c
cd ..
celar
clear
ls
cd userprog/
vim exception.c
make
clear
vim exception.c
ls
vim syscall.c
vim syscall.h
vim syscall.c
vim process.c
vim syscall.c
cd ..
cd lib/
ls
cd ..
cd tests/
ls
cd ..
cd userprog/
vim syscall.c
vim exception.c
vim syscall.c
vim exception.c
clear
vim syscall.c
vim exception.c
vim syscall.c
vim process.c
cd pintos/src/vm
make check
exit
cd pintos/src/vm
cd ..
ls
cd lib/
ls
vim kernel/
cd kernel/
ls
vim bitmap.c
clear
cd pintos/src/vm/
ls
cd ..
cd vm
ls
clear
ls
cd ..
cd threads/
ls
cd ..
cd devices/
vim block.c
vim block.h
vim block.c
vim block.h
vim block.c
ls
vim block.c
ls
vim block.h
ls
vim block.c
