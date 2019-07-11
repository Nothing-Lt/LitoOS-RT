# LitoOS-RT
Real-time version of LitoOS(plan).Currently only support x86 platform.(Future, maybe ARM and MIPS RISC-V).
In micro-kernel, external handler just send message to task, after task received messgae, system put it into ready queue,
this is OK for general purpose OS, but for Realtime OS, the behaviour is completelly depend on the scheduler.
In monolithic kernel, it has no such problem, but handler is developed by developer, so if the handler execute for a long time, some of the interrupt will not catched by OS.
I am trying to use this LitoOS to solve this problem, hope I can do it. :)


Compile:
$make.

Compiled result:
One image file named LitoOS.img in 1.44 floppy disk format. 

Adapt:
When adapting to other platform, modify include/stdint.h for data type.
