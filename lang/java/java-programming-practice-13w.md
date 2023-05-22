# 자바프로그래밍실습 13주 차

## Generic

code를 multiple types을 위해 재사용할 수 있도록 해준다.

```java
public class Box<T> {
    private T t;
    public void set(T t) { this.t = t; }
    public T get() { return t; }
}
```

```java
Box<Integer> integerBox = new Box<Integer>();
```

위와 같이 사용할 수 있다.

### Generic Class

```java
class Pair<T, U> {
  private T first;
  private U second;
  ...
}
```

class를 정의할 때 classname 옆에 <T, U>를 붙여주면 된다. compile time에 error를 찾고 class와 methods의 reusability를 높여준다.

### Generic Methods

```java
class GeneriClass<T> {
  public T genericMethod(T t) {
    ...
  }
}
```

위와 같이 return type을 제네릭으로 만들 수 있다. 컴파일 타임에는 T가 무엇인지 알 수 없기 때문에, T를 사용하는 모든 코드는 Object로 변환된다. 그 후 Object를 들어온 변수의 타입으로 bound한다.

### Wildcards

<?>를 사용하면 모든 타입을 받을 수 있다. <? extends T>는 T의 subclass만 받을 수 있다. <? super T>는 T의 superclass만 받을 수 있다. 이를 통해 좀 유연한 코드를 작성할 수 있다.
