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
