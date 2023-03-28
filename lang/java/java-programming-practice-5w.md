# 자바 프로그래밍 실습 5주 차

## Inheritance

``` java
class A {
    int a;
}

class B extends A {
    int b;
}
```

위와 같이 클래스 A를 상속받는 클래스 B를 만들 수 있다. 이때 클래스 B는 클래스 A의 모든 멤버를 상속받는다. 클래스 B는 클래스 A의 멤버를 사용할 수 있고, 클래스 B의 멤버를 사용할 수 있다.

### super

``` java
class A {
    int a;
    A(int a) {
        this.a = a;
    }
    void print() {
        System.out.println("A");
    }
}

class B extends A {
    int b;
    B(int a, int b) {
        super(a);
        this.b = b;
    }
    void print() {
        System.out.println("B");
    }
    void printA() {
        super.print();
    }
}
```

위와 같이 클래스 B에서 클래스 A의 멤버를 사용하고 싶을 때 `super`를 사용할 수 있다. 또한 클래스 B에서 클래스 A의 생성자를 호출하고 싶을 때 `super(params)`를 사용할 수 있다.

### overriding

``` java
class A {
    int a;
    void print() {
        System.out.println("A");
    }
}

class B extends A {
    int b;
    void print() {
        System.out.println("B");
    }
}
```

위와 같이 클래스 A의 멤버를 클래스 B에서 재정의할 수 있다. 이때 클래스 B의 멤버는 클래스 A의 멤버를 가리게 된다. 이것을 overriding이라고 한다.

#### Rules for Method Overriding

- argument list와 return type이 같아야 한다.
- final method는 overriding할 수 없다.
- static method는 항상 재정의된다.
- Constructor는 overriding할 수 없다.

### final

``` java
class A {
    final void print() {
        System.out.println("A");
    }
}
```

- Variable: 값을 변경할 수 없다.
- Method: overriding할 수 없다.
- Class: 상속할 수 없다.

### static

``` java
class A {
    static int a;
    static void print() {
        System.out.println("A");
    }
}
```

- Variable: 클래스 변수
- Method: 클래스 메소드

클래스 변수 및 메소드는 클래스가 메모리에 로드될 때 생성된다. 클래스 변수는 모든 인스턴스가 공유한다. 클래스 메소드는 인스턴스를 생성하지 않고도 호출할 수 있다.

### Polymorphism - 다형성

다형성이란 하나의 변수가 여러 타입을 가질 수 있는 것을 의미한다. 이를 위해서는 상속 관계가 있어야 한다.

``` java
class A {
    void print() {
        System.out.println("A");
    }
}

class B extends A {
    void print() {
        System.out.println("B");
    }
}

A[] arr = new A[2];
arr[0] = new A();
arr[1] = new B();
```

위와 같이 클래스 A를 상속받는 클래스 B가 있을 때, 클래스 A 타입의 배열에 클래스 B의 인스턴스를 넣을 수 있다. 이때 클래스 B의 인스턴스는 클래스 A의 인스턴스이기 때문에 가능하다.

### Overloading

``` java
class A {
    void print() {
        System.out.println("A");
    }
    void print(int a) {
        System.out.println("A" + a);
    }
}
```

위와 같이 클래스 A의 멤버를 같은 이름으로 여러 개 만들 수 있다. 이때 argument list와 반환 값이 다르면 같은 이름의 멤버를 만들 수 있다. 이를 Overloading이라고 한다.

## Special Classes

### Abstract Class

``` java
abstract class A {
    abstract void print();
}
```

abstract method는 구현되지 않은 method이다. abstract class는 abstract method를 가질 수 있고 당연히 일반적인 method도 가질 수 있다. abstract class는 인스턴스를 생성할 수 없다. 결국 구현을 하지 않고 싶을 때 즉 Encapsulation을 위해 사용한다.

### Interface

``` java
interface A {
    void print();
}
```

interface는 abstract method만 가질 수 있다. interface는 인스턴스를 생성할 수 없다. interface는 다중 상속이 가능하다.

#### Abstract Class vs Interface

- abstract class는 일반적인 method를 가질 수 있지만 interface는 abstract method만 가질 수 있다.
- interface는 constructor를 가질 수 없다.
- interface는 instace variable을 가질 수 없다.
- interface는 implements를 사용하고 abstract class는 extends를 사용한다.

