# 운영체제 1주 차 Review

한 컴퓨터를 여러 사람이 나눠쓰는 형태에서 여러 컴퓨터를 한 사람이 사용하는 형태로 변해왔다.

## Trap, System call, Interrupt

- System call, exception은 cpu에서 발생
  - exception은 발생 즉시 instruction 처리를 중단하고 exception을 handling한다.
- Interrupt는 I/O device에서 발생
  - Interrupt는 발생해도 처리중인 instruction은 처리를 마친 후에 Interrupt를 처리한다.
- Trap을 통해 위 event들을 호출하고 각 handler를 통해 event를 처리한다.

### System call interface

- System call function은 메모리에 올라가 있기 때문에 추가적인 linking 과정은 필요없고 바로 사용할 수 있다.
- 다만 각 언어에 있는 library를 통해 system call을 호출하고 그 library는 system call handler을 통해 system call code를 호출한다.
- system call function은 각 번호를 가지고 있다.
