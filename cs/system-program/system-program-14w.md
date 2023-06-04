# 시스템프로그램 14주 차

## cache가 프로그램의 성능에 미치는 영향

행렬 곱셈을 수행하는 3중 반복문으로 예를 들었는데 여러가지 상황이 주어졌다. 결국에는 2 배열을 접근할 때 모두 row-major한 상황으로 만들어서 caching이 잘되게 한 프로그램이 제일 성능이 좋았다. 여기서 중요한 부분은 memory access의 횟수로 성능의 차이가 나는게 아니라 miss ratio에 의한 성능 차이가 더 크다는 것이다. 따라서 cachcing을 잘하는 것이 중요하다고 할 수 있다. 즉 stride 1 상황을 잘 만들어보자.

## Linking

여러 c 프로그램을 서로 연결하는 과정이다. modularity를 위해서 사용하는데 이를 통해 source file을 여러 개로 나눌 수 있어 협업에도 유리하다. 또한 컴파일 할 때에도 특정 모듈만 하면 되기 때문에 시간 적으로도 좋고 실제로 사용되는 코드만 가져오기 때문에 공간면에서 효율적이다.

### Relocatable Object Files

기존적으로 이러한 relocatbale object file은 ELF(Executable and Linkable Format)이라는 포맷으로 저장된다. 이 ELF Object File은 크게 3가지로 나뉜다.

- Relocatable Object File
  - 여러개의 relocatable object file을 하나로 합칠 수 있다.
  - 여러개의 relocatable object file을 하나의 executable file로 만들 수 있다.
- Executable Object File
  - 여러개의 relocatable object file을 하나로 합칠 수 있다.
- Shared Oject File
  - Window의 DLL(Dynamic Linking Library)와 같다.
  - load 또는 run time에 linking이 가능하다.

ELF는 head와 section으로 나뉘는데 header에는 파일의 포맷을 전반적으로 설명하는데 예를들어 word size, byte ordering, header size, section의 크기와 각 위치를 담은 section header table의 위치 등이 있다. section은 여러가지 section으로 나뉘는데 이는 아래와 같다.

- .text
  - code
- .data
  - initialized global variables
- .bss
  - uninitialized global variables
- .rodata
  - read only data
  - jump table and format string
- .symtab
  - symbol table
  - function name, 정의된 global variable
  - assembler에의해 생성된다.
- .rel.text
  - relocation information
- .rel.data
  - relocation information
- .debug
  - debugging information
  - -g 옵션을 사용하면 생성된다.
- .line
  - line number information
- .strtab
  - string table for symbol table, debugging information

링크를 하게되면 rel section은 없어지고 나머지는 하나로 합쳐진다. 추가로 segment header table이 생성되는데 이는 segment의 크기와 위치를 담고 있다. 그리고 실행을 위한 .init도 추가된다.

### Static Linking

fully linked excutable object file을 출력하는 방식이다. 이때 주로하는 일은 2가지가 있다.

- Symbol resolution
  - symbol reference을 결합한다.
- Relocation
  - symbol refereence를 수정 및 결합한다.

#### Symbol Resolution

symbol은 변수, 함수의 이름을 말한다. num, value, size, type, bind, ndx, name 등을 이 symbol tables에 저장하는데 변수이면 object type을 가지고 있고 함수이면 function type을 가지고 있다. 하지만 external storage class를 가지고 있으면 notype을 가지고 있는데 이는 symbol resolution 과정에서 결정된다.

이와 같이 symbol resolution은 assembly가 처리 못한 부분을 처리하고 이러한 각 tables들을 합쳐서 symbol table을 만드는데 몇 가지 규칙이 있다.

- multiple strong symbols
  - error
- strong symbol과 weak symbol
  - strong symbol이 weak symbol을 override한다.
- multiple weak symbols
  - random하게 하나를 선택한다.

> Strong symbol은 함수 또는 초기화된 변수를 의미하고 weak symbol은 초기화되지 않은 변수를 의미한다.

static library는 여러개의 relocatable object file을 하나로 합친 것이다. .a suffix를 가지며 linker는 이들과도 linking을 할 수 있다. 이때 library에서 사용하는 module만 copy해서 사용한다.

link을 할 떄 주의 할점은 순서에 맞게 linking을 해야한다는 것이다. 즉, 참조하는 순서대로 linking을 해야한다. 예를들어 a -> b -> c 순서로 linking을 해야한다면 gcc -o a a.o b.o c.o가 되어야한다.

#### Relocation

relocation은 symbol resolution을 통해 결정된 symbol reference를 수정하는 과정이다. 이때 relocation은 rel.data, rel.text에 있는 relocation entry를 통해 이루어진다. relocation entry는 어디를 수정해야하고 어디를 가르키고 있고 어떻게 수정해야하는지를 담고 있다. 이후 해당하는 위치를 수정하고 relocation entry를 제거한다.

### Dynamic Linking

먼저 executable object file의 data와 code를 메모리에 copy해서 실행시키는 loader을 알아본다. loader는 0x400000부터 시작되며 ASLR(Address Space Layout Randomization)을 통해 매번 다른 위치에 load된다. 이떄 static library는 매 실행마다 가져와야해서 공간 낭비도 심하고 매번 가져와야해서 시간도 오래걸린다. 따라서 shared library를 사용하는데 .so 또는 DLL suffix를 가진다. 이 shared library는 실행시에 load되거나 run time에 load된다. 이때 shared library는 여러개의 process에서 공유할 수 있다.
