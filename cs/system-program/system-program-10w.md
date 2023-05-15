# 시스템프로그램 10주 차

## Optimizing Program Performance

저번에 이어서 optimization에 대해서 공부했다.

### Loop Optimization

저번에는 단순히 compiler의 optimization level을 통해 높였는데 오늘은 몇 가지 수정을 통해 최적화를 진행했다.

#### V2. Code motion

반복문의 조건을 보게 되면 함수가 호출되는 것을 볼 수 있다. 따라서 따지고 보면 시간복잡도가 O(n)이 아니라 O(n^2)이 된다. 해당 함수는 어차피 반복문과의 dependece가 없기 때문에 반복문 밖으로 빼서 최적화를 진행했다.

compiler 입장에서는 해당 함수가 반복문 수행과정에서 변하지 않는다는 것을 알 수 없기 때문에 개발자가 직접 최적화를 진행해야 한다.

#### V3. Reducing procedure calls

이제는 반복문 안을 최적화해보자. 현재는 함수를 통해 각 요소를 가져오는데 이렇게 하지 않고 반복문 밖에서 data가 들어있는 배열을 가르키는 포인터를 가져오고 반복문 안에서는 배열 인덱싱을 통해서 접근하는 식으로 바꿨다.

다만 이렇게 해도 성능상 차이가 전혀 없었다. 왜냐하면 결국엔 포인터를 사용했기 때문에 매번 memory access가 일어나기 때문이다.

#### V4. Reducing memory references

따라서 포인터가 아닌 임시 변수를 선언한 후 해당 변수에 연산한 결과들을 저장하고 반복문이 끝나면 그 값을 dest에 저장하는 방식으로 바꾸니 성능이 향상되었다.

### Understanding modern processors

이제는 computer architecture에 dependence가 있는 optimization을 진행해보자. 그 전에 modern processor의 구조에 대해서 알아보자.

요즘은 program 성능의 극대화를 위해 HW가 복잡해졌다. machine level programs 입장에서는 sequential하게 실행되는 것처럼 보이지만 실제로는 parallel하게 실행된다. 따라서 약 100개 이상의 instruction이 동시에 실행된다. 당연히 결과는 sequential하게 실행된 것과 같다.

프로그램 성능을 표현하는 데에는 2 가지 lower bound가 있다.

- Latency bound
  - sequential하게 실행 했을 때 최소 실행 시간
- Throughput bound
  - parallel하게 실행 했을 때 최소 실행 시간

#### Architecture of a modern processor

CPU(i7 haswell 기준)의 architecture에 대해서도 알아 봤는데 이는 컴퓨터구조 수업 때 배웠던 내용과 동일하므로 동일한 내용은 생략한다.

일단 instruction을 fetch, decode등을 하는 ICU 부분과 ICU에서 받은 operations을 실행하는 EU 부분으로 나뉜다.

ICU는 다음 실행 될 instruction을 미리 fetch하는 prefetching과 prefetching 과정에서 jump instruction을 만나면 branch prediction을 통해 다음 실행될 instruction을 예측한다. 이들을 speculative execution이라고 한다.

> instruction을 decode 하는 과정에서 multiple operations로 convert하는 과정도 포함될 수 있다.

EU의 연산 과정 또한 ICU와 같이 Speculative execution이 가능하다. 이러한 과정에서 나온 결과는 temporary area에 저장되는데 이는 Retirement unit에서 관리 및 저장한다. 만약에 branch prediction이 틀렸다면 해당 결과는 flush되고 맞았다면 retire 되어 program register를 update한다.

#### Functional unit performance

EU는 operation에 맞는 functional unit으로 dispatch해 실제 연산을 수행한다.

- Functional units(8 units)
  - Integer arithmetic, FP multiplication, integer and FP division, branches
  - Integer arithmetic, FP addition, intger and FP multiplication
  - Load, address computation
  - Load, address computation
  - Store
  - Integer arithmetic
  - Integer arithmetic, branch
  - Store, address computation

근데 결국 4 개의 integer arithmetic unit, 1개의 integer multiplication unit, 1 개의 FP addition, 2 개의 FP multiplication, 2 개의 load operation unit가 있다는 정도의 사실을 알고 있으면 된다.

이러한 functional unit의 performance의 특징으로는 다음과 같다.

- Latency
  - 한 개의 operation을 수행하는데 걸리는 시간
  - 복잡한 data type 또는 연산(divid)일수록 latency가 높다.
- Issue-time
  - 동일한 type의 두 operation 사이에 필요한 최소 시간
  - 1 cycle이면 fully pipelined라고 한다.
- Capacity
  - operation을 수행하기 위해 사용 가능한 functional unit의 개수
- Max throughput
  - 한 cycle에 수행할 수 있는 operation의 최대 개수
  - Capacity * 1 / issue-time
  - 역수는 throughput bound를 의미한다.

저번에 최적화 했던 combine 함수의 CPE를 보면 Latency과 비슷하므로 sequential하게 실행했을 때의 최소 실행 시간이라고 볼 수 있다. 하지만 parallel하게 하면 더 최적화가 가능하다.

#### Data-flow representation

machine-level program의 performance를 분석하는 도구로 다른 operations와의 data dependecies를 보여줌 으로써 ciritical path를 찾을 수 있다.

먼저 data-flow representation을 그리기 전 register의 종류에 대해서 알아보자.

- Read-only
  - source register
- Write-only
  - destination register
- Local (Compare Conditions)
  - loop에서 사용되고 업데이트 되지만 반복문 밖에서는 사용되지 않는 register
- Loop register
  - source register이자 destination register 즉 iteration에 dependece가 있는 register

우리는 dependency가 있는 loop register에 집중하여 최적화를 진행할 것이다. 따라서 loop register를 제외한 나머지 register는 data path에 표시하지 않는다. 이렇게 하고 각 반복문 별 그림을 그리면 어떤 regs 또는 operations가 critical path인지 알 수 있다. combine4 함수 같은 경우에는 곱셈이 critical path이다.

#### Loop unrolling

저번에도 배운 개념인데 각 반복에 처리하는 요소 수를 증가시켜 반복문의 수를 줄이는 방법으로 반복문 안에 처리하는 요소 수가 k라고 하면 k way unrolling이라고 한다.
