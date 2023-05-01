# 자바 프로그래밍 실습 10주 차

## GUI

### GUI in Java

- java.awt.\*
  - native libraries로 UI 생성
  - 각 OS 별로 약간씩 다르게 나온다
- javax.swing.\*
  - 어떠한 OS에서도 일관성 있게 나온다
  - JVM 기반으로 UI를 생성

#### Terminology of Java GUI

- Component
  - UI를 구성하는 기본 단위
  - Button, Label, TextField, CheckBox, RadioButton 등
  - J-prefix가 붙으면 Swing Component
- Container
  - 다른 Component를 포함할 수 있는 Component
  - Window, Frame, Panel, Dialog, Applet 등

### Getting Started with Swing

1. Frame 만들기
2. frame에 components 추가하기
3. Implement main

```java
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
```

위와 같은 라이브러리들을 import 해야 한다.

#### JFrame

```java
class MyFrame extends JFrame {
  MyFrame() {
    setTitle("First Frame");
    setSize(400, 400);
    setVisible(true);
  }
}
```

위와 같이 JFrame을 상속 받아서 새로운 Frame을 만들 수 있다.

이 안에 JPanel을 추가해 Sub Frame으로써 사용할 수 있고 또한 이 안에 JLabel 등을 추가 할 수 있다.

### Layout

- FlowLayout
  - 컴포넌트를 왼쪽에서 오른쪽으로 배치
  - 컴포넌트가 가득 차면 다음 줄로 넘어감
- BorderLayout
  - 5가지 방향으로 배치
    - North, South, East, West, Center
- GridLayout
  - 격자 모양으로 배치
  - 행과 열의 개수를 지정
- CardLayout
  - 여러 개의 컴포넌트를 겹쳐서 배치
  - 한 번에 하나의 컴포넌트만 보임

container 별로 기본적으로 설정되어 있는 Layout이 있지만 setLayout을 통해 layout을 변경할 수 있다.

### Event and Listener

- Event
  - software에 의해 알아채어진 일
- Listener
  - event를 처리하는 객체
  - event source에 등록되어 event가 발생하면 event source로부터 event를 전달받아 처리

Listener을 생성하고 각 Component에 등록해야 한다.

### Window Builder

Eclipse에서 GUI를 쉽게 만들 수 있게 해주는 플러그인 각 에디터 별로 존재한다.
