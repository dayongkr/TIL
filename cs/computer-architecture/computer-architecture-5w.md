# 컴퓨터구조개론 5주 차

## Procedure Call

호출하는 부분을 caller 라고 하고, 호출되는 부분을 callee 라고 한다. 앞으로 어떻게 parameters를 calle로 전달하고 callee의 loca variables를 위한 memory space를 reserve하고 caller로 return value를 전달할지에 대해 알아보자.

### Procedure, Function

Procedure는 Function과 비슷하지만 정교한 작업을 위해 만든 instructions의 집합이다.

### Regs Usage

|Regs Num|Name|Usage|
|:---:|:---:|:---:|
|x0|zero|Constant 0|
|x1|ra|Return address|
|x2|sp|Stack pointer|
|x3|gp|Global pointer|
|x4|tp|Thread pointer|
|x5 - x7, x28 - x31|t0-t6|Temporary|
|x8|s0 / fp|Saved register / Frame pointer|
|x9, x18 - x27|s1 - s11|Saved register|
|x10 - x11|a0 - a1|Function arguments / results|
|x12 - x17|a2 - a7|Function arguments|

#### Arguement Passing

x10 - x17에 function이 calling 되기 전에 arguements로 설정된다. 만약에 8개 이상의 arguments가 필요하다면 memory를 사용한다.

#### Return Value

lower 32-bit는 x10에 저장되고, upper 32-bit는 x11에 저장된다. 만약에 64-bit 이상의 return value가 필요하다면 memory를 사용한다.

### Procedure Call Instruction

- jal: jump and link
  - e.g. jal x1, ProcedureLabel
  - Jumps to the target address
  - Stores the address of the next instruction in x1
    - x1 is the return address
- jalr: jump and link register
  - e.g. jalr x0, Offset(x2)
  - Jumps to offset + address
  - Stores the address of the next instruction in x0

### Memory space for procedure

만약에 여러 procedure을 사용한다면 local values가 같은 regs 주소를 가진 주소가 있을 수 있기 때문에 이를 위해 procedure마다 memory space를 따로 만들어야 한다. 이 memory space는 stack구조를 가지고 있고 각 procedure마다 allocate되고 반환할 때 deallocate된다.

memory space는 원래 fixed되어 있지만 dynamic하게 할당할 수도 있다. 또한 같은 procedure이 여러번 호출되어도 서로 meomory space를 공유하지는 않는다.

#### Managing & Accessing Stack

Stack frame은 memory에 아무 위치에 있을 수 있다. 하지만 stack pointer(x2)는 항상 stack frame의 lowest address을 가리키고 있어야 한다. Stack은 Higher address에서 lower address로 쌓인다.

```assembly
addi sp, sp, -20 # stack pointer를 20 bytes lower로 이동시킨다.
sw x1, 0(sp) # x1의 값을 stack pointer가 가리키는 곳에 저장한다.
addi sp, sp, 20 # stack pointer를 20 bytes higher로 이동시킨다.
```

만약에 function이 20 btes의 space를 필요하다면 function이 시작할 때 stack pointer를 20 bytes lower로 이동시킨다. 또한 return 할 땐 stack pointer를 20 bytes higher로 이동시킨다.
