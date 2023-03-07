# 디지털 논리 회로 기초 개념

## 게이트 및 간단 소개

- X AND Y
  - X, Y 모두 1이면 1
- X NAND Y
  - X, Y 모두 1이면 0
- X OR Y
  - 둘 중의 하나 또는 모두 1이면 1
- X XOR Y
  - 둘 중의 하나만 1이면 1
- X XNOR Y
  - 둘 중의 하나만 1이면 0

특정한 Voltage Level 위이면 1, 아래이면 0이다. 그 사이는 Undefined이다.

회로에는 전류를 흘리는 Power Source(VDD)와 전류가 나가는 Ground(GND)가 있다.

## MOS Transistors

- pMOS
  - Source(GND), Drain(Circuit의 Output), Gate로 이루워짐
  - 0이어야 연결됨
- nMOS
  - Source(VDD), Drain, Gate로 이루워짐
  - 1이어야 연결됨

회로 그림에서 게이트에 붙어 있는 작은 원은 Invert를 의미한다.

### Inverter (NOT Gate) Operation

pMOS와 nMOS의 결합으로 작동하게 된다.

> Output이 Ground와 연결되어 있으면 0, VDD에 연결되어 있으면 1

## Binary Number System

- Byte: 8bit
- 16bit: Half Word
- 32bit: Word
- Most significant bit(MSB): Word 맨 왼쪽
  - Sign bit가 보통 MSB에 존재
- Least significant bit(LSB): Word 맨 오른쪽

32bit 컴퓨터 기준이다.

디지털 시스템은 고정된 bits로 작동하는데 결과가 고정된 bits로 표현 안될만큼 크면 overflow가 발생한다.

### Base 16

4bits를 16진수로 단축해서 표현하는 방법이다.

> 0xECA96420과 같이 0x를 붙여 16진수임을 표현

### Sign / Magnitude Number

N-bit의 sign/magnitude number의 범위는 [-(2^(N-1) - 1), 2^(N-1) - 1]

다만 문제점이 있는데 비트 연산을 통해 더하기 연산을 하면 원치 않는 결과가 나오고 0을 표현하는 방법이 +0, -0으로 두 개로 나누어지게 된다.

### Two's Complement

양의 정수를 음의 정수로 바꾸는 방법이다.

1. 모든 bits를 Flip(Invert) 한다.
2. 1을 더한다.

이를 통해 위의 두 문제를 해결할 수 있고 범위가 [-2^(N-1), 2^(N-1) - 1]로 음수를 하나 더 표현할 수 있다.

따라서 위와 같은 장점을 가지고 있으므로 모든 컴퓨터 시스템은 Two's Complement를 사용한다.

## Combinational vs Sequential circuits

Combinational은 Memory-less를 의미한다. Sequential은 당연히 반대로 with memory이다.

### Combinational Logic - Mux / Demux

Mux(Multiplexer)는 여러 입력 신호 중 하나를 선택해서 출력을 결정한다.

Demux(DeMux)는 하나의 입력 신호를 받아서 여러 출력 중 하나를 선택해서 출력을 결정한다.

### Combinational Logic - 1bit Binary Adder

0 + 0 = 0 (Cout 0)
1 + 0 = 1 (Cout 0)
0 + 1 = 1 (Cout 0)
1 + 1 = 0 (Cout 1)

NAND Gate와 같은 결과가 나온다.

Full Adder는 Cin가 추가로 있어서 전 연산에서 나온 Cout을 포함해서 계산한다는 차이가 있다.

Nbit 연산은 N개의 Full Adder을 붙여서 연산하는데 Ripple Carry Adder라고 한다.

### Pulse Propagation

Gate 연산은 Delay가 발생하는데 때문에 결과도 이에 따라 변하게 된다.

예를들어 1 AND 1 연산 후 둘 중의 하나가 0으로 바뀌면 바로 결괏값이 0으로 바뀌는 것이 아니라 지연 시간 후 바뀌게 된다.

이와 같이 컴퓨터 시스템은 빠르지만, 지연 때문에 무한히 빠르지 않다. 따라서 이러한 지연 문제를 부분적으로 해결하기 위해 파이프라인을 사용한다.

## Sequential logic

D -> Clock -> Q

다양한 것들이 존재하지만 이번 수업에서는 1bit에 저장하는 flip-flops를 다룬다.

CPU에서 3.4GHz 이런 것들이 Clock이 얼마나 빠르게 0과 1을 반복하는 지를 의미한다.

Clock이 Rising edge일 때 저장된 후 바로 Q를 통해 Output이 나온다. 따라서 Clock이 얼마나 빠르게 주기를 반복하는지에 따라 속도가 변하는 것이다.
