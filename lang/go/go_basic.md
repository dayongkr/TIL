# GO 기초 공부

## INTROUDUCTION

- 3명의 멋진 개발자분들이 Google에서 설계한 정적 타입, 컴파일 기반 고급 언어이다.
- 구조적으로 C와 유사하다.
- 멀티 코어 시대에 프로그래밍 생산성을 향상시키기 위해 만들어졌다.
- C++을 싫어하는 것이 주된 동기로 만들어졌다.
- package는 보통 도메인/username/package_name으로 만드는데 이름 충돌 가능성을 피하기 위해서 이렇게 만든다.

```bash
go env GOROOT
go env GOPATH
```

위 명령어를 통해 go의 환경변수를 확인할 수 있는데 각각 go의 설치 경로와 go의 프로젝트 경로를 나타낸다. 우리는 go의 프로젝트 경로에 가서 src 폴더를 만들고 그 안에 main.go를 만들어 프로젝트를 시작한다.

## THEORY

### 메인 패키지

- 패키지 이름을 main으로 두면 프로젝트를 컴파일한다. 그렇지 않으면 외부 라이브러리로 사용하는 거로 간주한다.
- main.go 파일은 프로젝트의 시작점이다.
- c언어와 유사하게 main 함수를 가지고 있다.

### import

- 패키지를 가져올 때 사용하는데 주소는 src 폴더부터 시작하는 것 같다.
- 대문자로 시작하는 함수는 export가 되어있는 함수이다.

### Constants, Variables

```go
const name string = "dayong"
var name2 string = "dayong"
name3 := "dayong"
```

- 상수는 const로 선언하고 변수는 var로 선언한다.
- name3처럼 := 를 사용하면 타입을 추론해서 변수를 선언할 수 있다.

### Functions

```go
func multiply(a int, b int) int {
  return a * b
}
```

- 함수는 func로 선언한다.
- return type은 파라미터 뒤에 적는다.

```go
func lenAndUpper(name string) (int, string) {
  return len(name), strings.ToUpper(name)
}

a, b := lenAndUpper("dayong")
```

- 여러개의 return type을 가질 수 있다.

```go
func test(words ...string) {
  fmt.Println(words)
}

test("a", "b", "c")
```

- 가변인자를 사용할 수 있다.

```go
func test() {
  defer fmt.Println("I'm done")
  fmt.Println("Hello")
  return
}
```

- defer를 사용하면 함수가 끝나고 실행된다.

```go
func (a Account) Deposit(amount int) {
  a.balance += amount
}
```

- struct에 함수를 연결할 수 있다.
- receiver를 사용한다.
- 단 receiver는 struct의 복사본을 만든다.
- 따라서 (a \*Account)로 사용하면 struct의 포인터를 사용하게 된다.

### for, range

```go
func superAdd(numbers ...int) int {
  total := 0
  for index, number := range numbers {
    total += number
  }
  return total
}

for i:=0; i<10; i++ {
  fmt.Println(i)
}
```

- for문은 c언어와 유사하다.
- python의 range와 유사하게 사용할 수 있다.

### if

- if도 조건문에 괄호를 사용하지 않는다.

```go
if i := 2; i == 2 {
  fmt.Println("2")
}
```

- if문 안에서 변수를 선언할 수 있다.

### Pointers

- 똑같이 \*, & 연산자를 사용한다.

### Arrays and Slices

```go
names := []string{"a", "b", "c"}
names = append(names, "d")
```

- 배열은 python의 list와 유사하다.

### Maps

```go
dayong := map[string]string{"name": "dayong", "age": "12"}
for key, value := range dayong {
  fmt.Println(key, value)
}

delete(dayong, "name")

make(map[string]string)
```

- python의 dictionary와 유사하다.
- delete로 삭제할 수 있다.
  - 만약에 없는 key를 삭제하려고 하면 에러가 발생하지 않는다.
- make로 map을 만들 수 있다.

### Structs

```go
type person struct {
  name string
  age int
  favFood []string
}

func main() {
  dayong := person{name: "dayong", age: 12, favFood: []string{"a", "b"}}
  // dayong := person{"dayong", 12, []string{"a", "b"}} 도 가능하다.
  fmt.Println(dayong)
}
```

- member의 이름을 대문자로 시작해야 외부에서 접근할 수 있다.
- 하지만 보통 생성자를 만들어서 사용하는데 return type은 struct의 포인터이다. (c랑 유사)

### Errors

```go
func test() error {
  return errors.New("error")
}
```

- error를 반환할 수 있다.
- error 체크는 if문으로 한다.

### Dictionary

```go
type Dictionary map[string]string

a := Dictionary{"a": "b"}

item, ok := a["a"]
```

- map과 type으로 dictionary를 만들 수 있다.
- map은 찾았는지 여부도 같이 반환한다.

### standard library

- https://golang.org/pkg/ 에서 확인할 수 있다.
- 강의에서는 http 패키지를 사용했다.

### Goroutines and Channels

```go
func main() {
  c := make(chan string)
  people := [2]string{"a", "b"}
  for _, person := range people {
    go isSexy(person, c)
  }
  fmt.Println(<-c)
  fmt.Println(<-c)
}

func isSexy(person string, c chan string) {
  time.Sleep(time.Second * 5)
  c <- person + " is sexy"
}
```

- go의 가장 큰 특징인 동시성을 위해서 사용한다.
- go keyword를 사용한다.
- 프로그램이 끝나면 goroutine도 끝난다.
- 따라서 channel을 사용해서 goroutine과 통신해야 한다.
- chan keyword를 사용한다.
- <- 를 사용해서 channel에 값을 보내고 받는다.
