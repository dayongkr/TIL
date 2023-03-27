# Typescript 기초

캡틴 판교님의 [타입스크립트 핸드북](https://joshua1988.github.io/ts/)를 보고 정리한 내용입니다.

다만 해당 핸드북이 2019년에 작성되었기 때문에 일단 기초를 떼고 나중엔 공식 문서를 보고 변경 사항을 체크하면서 다시 정리하고자 한다.

## 타입스크립트란?

JS에서 type을 선언할 수 있게 하는 확장판이라고 생각하면 되는데, 타입스크립트는 JS의 superset 이다. 즉, JS의 모든 기능을 포함하고 있으며, 타입스크립트를 컴파일하면 JS로 변환된다.

JS는 JIT(Just-In-Time) compiler를 사용해서 상황에 따라 interpret과 compile 둘 다 수행하긴 하지만 타입을 선언하지 않기 때문에 runtime 아닌 이상 어떠한 값이 들어올지 모르기 때문에 runtime 과정에서 오류를 발견하게 된다. 이러한 문제를 타입스크립트로 해결할 수 있다. 또한 이렇게 타입을 선언하면 IDE에서 자동완성을 지원해주기 때문에 개발자의 생산성을 높일 수 있다.

## 기본 타입

- boolean
- number
- string
- object
- array
- tuple
- enum
- any
- void
- null
- undefined
- never

위와 같이 12가지의 기본 타입이 있다.

### string

```ts
let str: string = 'hello';
```

위와 같이 `:`을 사용해서 type annotation을 할 수 있다.

### number

```ts
let num: number = 10;
```

### boolean

```ts
let isDone: boolean = false;
```

### object

```ts
let obj: object = {};
let person: object = {
  name: 'captain',
  age: 100
};
```

### array

```ts
let arr: number[] = [1, 2, 3];
let items: Array<number> = [1, 2, 3];
```

> 밑에 같은 경우엔 제네릭을 사용해서 타입을 지정해준 것이다.

### tuple

```ts
let address: [string, number] = ['gangnam', 100];
```

Tuple은 배열의 특정 인덱스에 해당하는 타입을 지정할 수 있다. 정의되지 않은 인덱스에 접근하면 에러가 발생한다.

Python에서의 Tuple은 수정이 불가능한 자료형이지만, TS는 수정이 가능한 자료형이다.

### enum

```ts
enum Shoes {
  Nike,
  Adidas
}
let myShoes: Shoes = Shoes.Nike;
console.log(myShoes); // 0
```

Enum 타입은 숫자형 값 집합에 이름을 지정한 것이다. 위의 예시에서 `Nike`는 0, `Adidas`는 1로 지정되어 있다.

```ts
enum Shoes {
  Nike = 3,
  Adidas = 0
}
let myShoes: Shoes = Shoes.Nike;
console.log(myShoes); // 3
```

위와 같이 직접 값을 지정해줄 수도 있다.

### any

```ts
let notSure: any = 0;
notSure = 'hello';
```

any 타입은 어떤 타입이든 할당할 수 있다. 하지만 any 타입을 사용하는 것은 좋지 않다. any 타입을 사용하면 타입스크립트의 장점을 잃게 되기 때문이다.

### void

```ts
function returnVoid(): void {
  ...
}
```

void 타입은 함수에서 반환값이 없을 때 사용한다.

### null, undefined

```ts
let u: undefined = undefined;
let n: null = null;
```

### never

```ts
function error(message: string): never {
  while ture {
  }
}
```

never 타입은 절대 발생하지 않는 타입이다. 위의 예시에서는 while문이 끝나지 않기 때문에 never 타입이다.

## Function

```ts
function sum(a: number, b?: number): number {
  return a + b;
}
```

위와 같이 함수를 선언할 수 있다. JS는 `?`를 사용해서 선택적 매개변수를 선언할 수 있다.

```ts
function sum(a: number,...nums: number[]): number {
  return nums;
}
```

위와 같이 REST 문법 `...`을 사용해서 가변 인자를 받을 수 있다.

this도 type을 지정할 수 있고 arrow function은 this를 바인딩하지 않기 때문에 this:void로 지정해서 사용하는 것을 추천한다.

## Interface

Interface는 상호 간에 정의한 약속 같은 것이다. Interface는 타입을 지정하는 것이 아니라 타입을 정의하는 것이다. 그 외 Interface에서 사용할 수 있는 것들은 다음과 같다.

- 객체의 스펙(속성과 속성의 타입)
- 함수의 파라미터
- 함수의 스펙
- 배열과 객체를 접근하는 방식
- 클래스

### 객체의 스펙

```ts
interface Person {
  name: string;
  age?: number;
}

const person: Person = {
  name: 'captain',
  sex: 'Male' // error
};
```

위와 같이 interface를 사용해서 객체를 선언할 수 있다. interface를 사용하면 객체의 속성을 빠뜨리는 실수를 방지할 수 있다. 또한 ?를 사용해서 선택적 속성을 지정할 수 있다. 그리고 정의 되지 않은 속성을 추가하면 에러가 발생한다.

```ts
interface Person {
  readonly name: string;
  age?: number;
  [propName: string]: any;
}
```

readonly를 사용하면 속성을 변경할 수 없다. 또한 `[propName: string]: any;`를 사용하면 정의되지 않은 속성을 추가할 수 있다. 근데 이렇게 사용하면 일부로 제약을 두기 위해 TS를 사용하는 의미가 없어진다고 생각한다.

### 함수의 타입

```ts
interface SumFunction {
  (a: number, b: number): number;
}

const sum: SumFunction = (a: number, b: number) => {
  return a + b;
};
```

위와 같이 interface를 사용해서 함수의 타입(반환 값의 타입도)을 지정할 수 있다.

### 클래스 타입

```ts
interface Person {
  name: string;
  age?: number;
}

class Captain implements Person {
  name: string;
  age?: number | undefined;
  constructor(name: string, age?: number) {
    this.name = name;
    this.age = age;
  }
}
```

위와 같이 interface를 사용해서 클래스를 선언할 수 있다.

### 인터페이스 확장

```ts
interface Person {
  name: string;
  age?: number;
}

interface Developer extends Person {
  skill: string;
}

const captain: Developer = {
  name: 'captain',
  skill: 'web'
};
```

위와 같이 interface를 확장해서 사용할 수 있다.

``` ts
interface Person {
  name: string;
  age?: number;
}

interface Drinker {
  drink: string;
}

interface Developer extends Person, Drinker {
  skill: string;
}

const captain: Developer = {
  name: 'captain',
  skill: 'web',
  drink: 'beer'
};
```

위와 같이 여러 interface를 확장해서 사용할 수 있다.

