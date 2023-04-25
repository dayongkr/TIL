# 컴퓨터구조개론 9주 차

## How Real Processors Are Made

지금까지 배운 datapath diagram은 설계를 위한 blueprint일 뿐이다. 오늘은 실제로 어떻게 processor가 만들어지는지 알아본다.

### Laguage for Hardware Design

Hardware도 설계를 위해 언어가 필요한데 크게 2가지가 있다.

- Verilog
- VHDL

#### Verilog Exa

```verilog
module test (clk, input_1, input_2, out);
  input clk;
  input [31:0] input_1;
  input [31:0] input_2;
  output reg [31:0] counter;

  wire [31:0] counter_new;

  always @(*) begin
    counter_new = counter;
    if(input_1 == input_2)
    counter_new = counter + 1;
  end

  always @(posedge clk) begin
    counter <= counter_new;
  endz
endmodule
```

위는 verilog로 작성된 코드이다. 이 코드는 2개의 32bit input을 받아서 같으면 counter를 1 증가시키는 코드이다. posedge clk는 clock의 rising edge(0 -> 1)를 의미하고 <=는 대입을 의미한다.

sw 프로그래밍은 sequential하게 실행되지만 hw는 parallel하게 실행된다. 그래서 위 코드는 2개의 always block으로 나누어져 있다. 하나는 combinational하게 실행되고 하나는 sequential하게 실행된다.

### Synthesis

이렇게 모듈별로 설계를 하고 나면 이를 합쳐서 하나의 chip으로 만들어야 한다. 이 과정을 synthesis라고 한다. 이 과정에서는 각 모듈들을 어떻게 합칠지, 어떻게 연결할지 등을 결정한다. 다만 실제로 어디에 어떻게 배치할지는 아니고 어떻게 연결할지만 결정한다.

### Physical Design

#### Placement

gate들의 물리적 위치를 배정하는데 가능한 연결된 gate들을 가까이 배치하도록 한다. 이렇게 하면 wire의 길이가 짧아지고 그에 따라 delay가 줄어든다. 이러한 과정을 optimization이라고 하는데 수많은 gate들이 존재하기 때문에 실질적으로 optimal한 위치를 찾는 것은 불가능하다. 그래서 heuristic한 방법을 사용한다. 요즘은 머신러닝을 사용해서 최적화를 하려고 하고 있다.

#### Routing

서로 어떻게 어떤 layer을통해 연결을 할건지도 결정해야 한다. 이것도 optimization 문제이다. layer을 많이 사용하면 wire의 길이가 짧아지고 delay가 줄어들지만 layer을 많이 사용하면 cost가 늘어난다. 따라서 이 또한 optimization이 중요한 문제이다.

### Design Verification / Validation is important

SW는 버그가 발생하면 업데이트를 통해 수정이 가능하지만 HW는 한 번 생산이 되면 수정이 불가능하다. 따라서 HW는 SW보다 훨씬 더 신중하게 설계되어야 한다. 그래서 HW는 SW보다 훨씬 더 많은 시간을 verification에 사용한다.

첫 번째 방법으로는 Logic Simulation이 있다. 이 방법은 SW와 비슷하게 testbench를 만들어서 test하는 방법이다. 하지만 이 방법은 너무 많은 시간이 걸린다.

두 번째 방법은 FPGA Emulation이다. 이 방법은 실제로 HW를 만들어서 test하는 방법이다. Programmable hardware를 사용해서 testbench를 만들어서 test한다. 이 방법은 Logic Simulation보다 훨씬 빠르다. 다만 real chip을 만드는 것보다는 느리다.
