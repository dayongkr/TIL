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

만약에 function이 20 bytes의 space를 필요하다면 function이 시작할 때 stack pointer를 20 bytes lower로 이동시킨다. 또한 return 할 땐 stack pointer를 20 bytes higher로 이동시킨다.

### Saving Registers

- Caller-save regs
  - ra, t0-t6, a0-a7
  - 이 regs는 caller가 사용할 수 있지만 함수를 호출하고 나서 사용하려면 sf에 save해야 한다.
- Callee-save regs
  - s0-s11
  - fp
  - sp
  - 이 regs는 callee가 사용할 수 있지만 사용하려면 sf에 저장을 하고 반환하기 전 restore해야 한다.

#### Avoiding Unnecessary Save & Restore

- 짧은 기간 사용할거면 s1 - s11(Saved regs)를 사용하지 않고 t0 - t6(Temp regs)를 사용한다.
- 함수를 호출하기 전 또는 하고 나서 Saved regs를 사용해라
- 만약에 가능하다면 x10 - x17(Arguement, Result regs)을 Temp regs로 사용하라

### Leaf Procedure Example

``` c
int leaf_example(int g, int h, int i, int j) {
  int f;
  f = (g+h) - (i+j);
  return f;
}
```

- Argument passing
  - g = x10
  - h = x11
  - i = x12
  - j = x13
- f in x20
  - caller의 x20은 stack에 저장되어야 한다.
- Temp regs
  - x5(t0), x6(t1)
- Return value
  - x10

```assembly
leaf_example:
  addi sp, sp, -4 # Allocate space for f
  sw x20, 0(sp) # Save caller's x20
  add x5, x10, x11 # g + h
  add x6, x12, x13 # i + j
  sub x20, x5, x6 # f = (g+h) - (i+j)
  addi x10, x20, 0 # Return value
  lw x20, 0(sp) # Restore caller's x20
  addi sp, sp, 4 # Deallocate space for f
  jalr x0, 0(x1) # Return
```

### MIPS Procedure Example

```c
int fact (int n)
{ 
  if (n < 1) return 1;
  else return n * fact(n - 1);
}
```

- Argument passing
  - n = x10
- Return value
  - x10

x1(ra), x10(arguments)를 stack에 저장해야한다.

```assembly
fact:
  addi sp, sp, -8 # Allocate space for ra, n
  sw x1, 4(sp) # Save ra
  sw x10, 0(sp) # Save n

  addi x5, x0, 1 # ra = 1
  bge x10, x5, L1 # if (n < 1)

  addi x10, x0, 1 # return 1
  addi sp, sp, 8 # Deallocate space
  jalr x0, 0(x1) # Return
L1:
  addi x10, x10, -1 # n - 1
  jal x1, fact # fact(n - 1)

  lw x5, 0(sp) # Load n
  mul x10, x5, x10 # n * fact(n - 1)

  lw x1 4(sp) # Restore ra
  addi sp, sp, 8 # Deallocate space
  jalr x0, 0(x1) # Return
```

### Synchonization

만약에 여러 thread가 하나의 procedure을 사용한다면 이를 위해 synchonization을 해야한다. 이를 위해 RISC-V A Extension의 atomic instruction을 사용한다.

#### Atomic Operation

- lr.w
  - load word reserved
  - lr.w x1, (x2)
- sc.w
  - store word conditional
  - sc.w x1, (x2)

memory location이 lr.w을 사용한 후 다른 thread에 의해 변경되지 않았다면 memory location에 value를 저장한다. 저장에 성공하면 x1을 0으로, 실패하면 x1을 non-zero value로 설정한다. 따라서 x1이 non-zero이면 다시 저장을 수행하는 연산을 수행하면 안전하게 저장할 수 있다.
