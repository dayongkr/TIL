# 자바 프로그래밍 실습 4주 차

## 객체 지향 프로그래밍 - OOP

같은 property를 가진 것들을 묶어서 표현하기 좋은 프로그래밍 기법이다. Class에는 data를 저장하는 field와 그 데이터를 다루는 행위들인 method를 가지고 있다.

### Class, Object

한 클래스는 오직 하나의 부모 클래스로부터 상속을 받을 수 있고 interface을 구현할 수 있다. 한 object는 다른 object와 reference를 통해 관계를 설립할 수 있고 다른 object가 접근할 때 데이터 접근 권한을 설정하기 위해 encapsulate라는 것을 사용한다.

### Class in Java

``` java
public class Baby {
  // field 부분
  String name;
  boolean gender;
  double weight = 5.0;
  int numcry = 0;
  Baby[] siblings; // 자기 자신도 가질 수 있다.

  // method 부분
  void cry() {
    numcry += 1;
    System.out.println("Dear mother, " + "I have cried.");
  }

  void sayHi() {
    System.out.println("Hi, my name is.." + name);
  }

  void eat(double foodWeight) {
    if (foodWeigth >= 0 && foodWeight < weight) {
      weight += foodWeight;
    }
  }

  // Constructor 부분
  Baby() {}

  Baby(String myName, boolean myGender) {
    name = myName;
    gender= myGender;
  }
}
```

``` java
public static void main(String[] args) {
  Baby baby = new Baby(); // Instance
  baby.cry(); // 메소드 호출
  System.out.println(baby.weight) // accessing fields
}
```

name, gender 등의 변수를 field라고 하고 cry, sayHi 와 같은 함수를 method라고 한다.

#### Constructors

``` java
public class CLASSNAME {
  CLASSNAME() {

  }
  
  CLASSNAME([PARAMETERS]) {

  }
}
```

class name과 똑같이 지어주면 된다.

모든 클래스는 최소한 하나의 constructor를 가져야 하지만 따로 적지 않아도 컴파일러가 자동으로 default constructor를 만들어준다.

### References

아무래도 object 같은 경우에는 많은 데이터들을 담고 있기 때문에 변수 안에 object의 value를 넣기보다는 object의 address를 담는 것이 효율적이기 때문에 주소를 담는다.

#### Self reference

``` java
class Baby{
  String name;
  
  void setName(String name) {
    this.name = name;
  }
}
```

변수간의 혼동을 막기 위해 Java에서는 자기 자신(해당 클래스 또는 인스턴스) 뜻하는 this를 붙여서 지정한다.

### Encapsualtion

``` java
public class Baby {
  private String nickname;
  public void setNickname(String nickname) {
    this.nickname = nickname;
  }
  public String getNickname(){
    return this.nickname;
  }
  public static void main(String[] args) {
    Baby shiloh = new Baby();
    Stranger stranger1 = new Stranger();
    stranger1.setandgetNicknameOf(shiloh);
  }
  class Stranger {
    void setandgetNicknameOf(Baby b){
      b.setNickname("cuty");
      System.out.println(b.getNickname());
    }
  }
}
```

privacy를 가진 변수를 만들 때 사용하는 개념이다. 변수 앞에 붙여서 사용하며 된다.

- public
  - 모든 객체에서 접근 및 수정이 가능하다.
- private
  - 자기 자신만 접근할 수 있다.
  - 따로 mutator(setter) method를 만들어서 수정 할 수 있다.

### Random Class

`java.utils` 패키지에 있는 Random Class 이름 그대로 랜덤한 수를 반환하는 method가 있는 Class이다. 수업에서는 1~4 사이의 정수를 무작위로 받으면 됐다.

``` java
Random random = new Random();
int people = random.nextInt(4) + 1;
```

nextInt method는 0에서부터 parameter - 1까지 범위를 가지고 랜덤한 정수를 반환한다. 하지만 우리는 1~4 범위를 원하기 때문에 +1을 함으로써 1~4로 범위를 맞출 수 있다.
