# 프로그래밍언어 4주 차

## Sematics

지금까지는 syntax에 대해서 배웠다. 이번에는 semantics에 대해서 배운다.

semantics에는 static semantics와 deeper semantics가 있다. 이번에는 static semantics에 대해서 배운다.

### static semantics

프로그램이 실행되는 동안 바뀌지 않는 부분을 다룬다. 우리는 AST(Abstract Syntax Tree)를 만들고 이를 통해 static semantics를 다룬다.

- CNF type checking
- N-CNF 이전에 선언된 변수인지?

또한 언어의 특징을 다루기 위해 BNF에 이어 AG(Attributed Grammar)을 사용한다.

### AG(Attributed Grammar)

- identifier가 선언되었는지 확인한다.
- type을 확인한다.
- 상속 관계를 확인한다.
- class는 한 번만 선언되어야 한다.
- method는 한 번만 선언되어야 한다.
- reserved identifier는 사용할 수 없다.
- etc

위와 같은 것들을 확인한다.

결국 AG는 제약조건 BNF는 규칙을 정의한다고 보면 된다.

- synthesized attribute
  - 자식 노드로부터 정의되는 attribute
- inherited
  - 부모 또는 형제 노드로부터 정의되는 attribute
- intrinsic
  - symbol table에 저장되는 attribute

위와 같이 정의되는 방향이 다양하기 때문에 top-down, bottom-up 둘다 사용하여 AG를 만들 수 있다.

<- 이러한 기호를 사용하는데 오른쪽은 반환값이 있는 함수고 왼쪽은 변수라고 생각하면 된다.

### Parse tree vs AST

Parse tree는 문법적으로 맞는지 확인하는 것이고 AST는 문법적으로 맞고 의미적으로 맞는지 확인하는 것이다. 따라서 불필요한 노드들을 제거하는데 보통 non-terminal node들을 제거한다.
