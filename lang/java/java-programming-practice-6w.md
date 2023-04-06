# 자바프로그래밍실습 6주 차

## Package

각 클래스는 package 아래에 있게 되는데 그냥 directory일뿐이다.

### Special Packages

java.lang은 import할 필요없다.

### Java API

자바에서는 많은 packages/classes를 제공한다.

예를 들어 Arrays 클래스에 있는 copyOf() 메소드를 사용해서 배열을 복사할 수 있는데 이는 다음과 같이 사용할 수 있다.

``` java
import java.util.Arrays;

int[] a = {1, 2, 3};
int[] b = Arrays.copyOf(a, 2); // b = {1, 2}
```

Generic도 집고 넘어갔다.

#### Generic

``` java
import java.util.*;
ArrayList<String> list = new ArrayList<String>(); // 확장 가능한 배열
Map<String, Integer> map = new HashMap<String, Integer>(); // key-value 쌍
HashMap<String, Integer> map = new HashMap<String, Integer>(); // key-value 쌍
```

위와 같이 Generic을 사용한 Interface를 사용할 수 있다.

### JAVADOC

주석에 정해진 형식에 맞춰 작성하면 JAVADOC을 사용해서 문서를 만들 수 있다.

## Weekly Assignment

패키지와 자바 API를 사용해서 연락처를 관리하는 프로그램을 만들어야했다.

- 모든 연락처 보여주기
- 이름과 전화번호로 해당 연락처를 찾기
- 이름 또는 전화번호로 해당 연락처 지우기
- 연락처 추가하기
  - 이름, 전화번호 중복 금지
  - 전화번호 형식 XXX-XXXX-XXXX
  - 이름 형식 알파벳
- 없거나 잘못된 부분은 에러 출력 안하고 그냥 넘어가기

위와 같은 구현이 필요한데 Skeleton code에는 각 연락처를 HashMap으로 저장하고 있었다.

### HashMap

HashMap은 key-value 쌍으로 저장하는 자료구조이다.

``` java
import java.util.HashMap;
public HashMap<String, String> listOfContacts = new HashMap<String, String>();
```

위와 같이 선언이 가능하며 사용 방법은 아래와 같다.

``` java
listOfContacts.put("name", "phone number");
listOfContacts.get("name");
listOfContacts.remove("name");
```

각각 추가, key로 value 찾기, key로 value 삭제를 할 수 있다.

> key는 name, value는 phone number으로 구현해야 한다.

또한 HashMap을 Iterator, Map, Set으로 반복문을 돌릴 수 있지만 그냥 keySet()을 사용해서 key를 Set으로 만들어서 for문을 돌리는게 더 간단한 것 같아서 이 방법을 사용했다.

``` java
for(String key : listOfContacts.keySet()) {
    // do something
}
```

### Regular Expression

정규표현식을 사용해서 전화번호 형식을 검사했다.

``` java
import java.util.regex.Pattern;
import java.util.regex.Matcher;

String regex = "정규식은 생략 아직 제출 마감 전!";
Pattern pattern = Pattern.compile(regex);
Matcher matcher = pattern.matcher(phoneNumber);
if(matcher.find()) {
    // do something
}
```

위와 같이 정규표현식을 사용해서 전화번호 형식을 검사할 수 있다. 참고로 자바에서 `\d`을 사용하려면 `\\d`로 사용해야 했다.
