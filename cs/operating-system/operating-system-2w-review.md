# 운영체제 2주 차 복습

## Virtualization

VMM Type-1은 OS을 사용하지 않고 하드웨어를 직접 제어하기 떄문에 더 빠르다.

## Process Management

주로 Unix에서의 process states를 복습해주셨다.

일단 첫 번째로 Unix는 보통 서버에서 사용하기 때문에 메모리가 충분하기 때문에 swap out을 잘 사용하지 않고 sleep 상태에서 swap in을 하지 못한다는 것을 알아봤다.

그 다음으로는 interrupt handler가 어떻게 동작하는지 알아봤다.

일단 interrupt가 발생하면 기존에 실행되던 process의 context saving 이후에 해당 프로세스을 사용해서 interrupt handler를 실행한다. interrupt handler는 함수일 뿐이기 때문에 프로세스가 필요하기 때문이다.

이렇게 해당 프로세스는 자기 일을 하지 않았음에도 cpu 누적 시간은 증가한다. 또한 interrupt handler는 sleep이 되지 않고 계속 실행된다. 그리고 끝나면 preempted가 필요에 따라 user process가 다시 실행된다.

마지막으로 linux에서의 asleep 상태를 복습해주셨다.

asleep은 2 가지 종류가 있는데 하나는 데이터가 오는 것이 보장되어 데이터가 올 때까지 기다리는 TASK_INTERRUPTIBLE이고 하나는 데이터가 오는 것이 보장되지 않아서 일정 시간이 지나면 깨어나는 TASK_UNINTERRUPTIBLE이다.
