# 자바 프로그래밍 실습 1주 차

간단한 소개, 설치, 코드 작성 등과 같은 간단한 OT 진행함

## C, Java, C++ 차이점

||C|Java|C++|
|-|-|-|-|
|지향|구조체 지향|객체 지향|객체 지향|
|포인터 Or 참조|포인터|참조|둘 다|
|전처리 과정|O|X|존재하지만 중요치 않음|
|구조체, unions, enum|O|X|O|

## 자바 특징

- 멀티쓰레딩
- 헤더 대신 API 클래스
- GC - 가비지 컬렉션
- unicode 지원

## 자바(Open JDK) 설치 in Mac

수업은 윈도우 기준으로 진행 되지만 굳이 VM을 사용해서 설치하고 싶지 않으니 Mac에 깔아보자

``` zsh
brew tap AdoptOpenJDK/openjdk
brew cask install adoptopenjdk11 // 원하는 버전의 숫자를 기재하면 됨
```

Homebrew 가 깔려 있으면 CLI로도 설치 가능

```zsh
java -version
```

위 명령어를 친 후 원하는 버전으로 설치됐으면 완료

## 자바 버전 변경 in Mac

```zsh
/usr/libexec/java_home -V
```

위 명령어를 치면 컴퓨터에 깔려 있는 여러 버전들이 보일 것이다. 원하는 버전을 맘 속으로 선택한 후

```zsh
export JAVA_HOME=`/usr/libexec/java_home -v 17`
```

17부분을 원하는 버전을 적고 터미널 init 파일에도 위 명령어를 입력해두고 터미널을 껏다 켜거나 init 파일을 재실행하면 원하는 버전으로 적용되어 있을 것이다.

## IDE 및 Editor

수업에서는 Eclipse를 사용하지만 vscode가 편하므로 vscode으로 진행하고자 한다.

환경 설정 방법은 따로 없고 Extension인 `Extension Pack for Java`와 `Code Runner`만 깔았다.

## 간단한 코딩

``` java
public class HelloWorld {
  public static void main(String[] args) {
    System.out.println("Hello Java!");
  }
}
```

위와 같은 Hello Java!를 출력하는 코드를 짜고 마무리했다.
