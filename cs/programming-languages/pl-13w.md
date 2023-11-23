# 프로그래밍언어 13주 차

## Object-Oriented Programming

### Object-Oriented Programming Concepts

- Object
  - data + method
  - data: attribute, field, property
  - method: operation, function
- Class, Type: 비슷한 objects의 category
- 재사용성과 유지보수성을 높인다.
- Encapsulation: 다른 객체의 접근을 제한한다.
- Inheritance: 상속을 통해 재사용성을 높인다.
- Reusability: 재사용성을 높인다.
- Polymorphism: 다형성을 제공한다.
  - Overloading: 같은 이름의 method를 여러 개 정의하는 것
- Abstraction: 필요한 부분만 노출한다.

### Python Object-Oriented Programming

- Multiple inheritance, Operator overloading, Signature-based polymorphism, Full oop language, garbage collection...
- Defining a Class: class ClassName(BaseClass): body
- Constructor: def **init**(self, ...): body
- self: instance
- Mangling: \_\_name
  - @property와 같이 쓰면 private처럼 사용할 수 있다.
- Only One Constructor
  - Overloading: default parameter
  - Overriding: super().**init**(...)
- Static Method: @staticmethod
  - no self
- getter: @property, self만 가질 수 있다.
- setter: @getterName.setter
- **slots**: instance variable을 제한한다.
- Operator overloading
  - **add**, **neg**, **pos**, **mul**, **truediv** 등등
- **dict**: instance variable을 dictionary로 보여준다.
- type(): class의 type을 보여준다.
