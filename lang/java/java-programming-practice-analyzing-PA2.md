# 자바프로그래밍실습 PA2 분석

## Battle ship

제목은 Battle ship이다.

- 10x10 좌표를 가진다.
- 각 플레이어는 자신의 배들을 숨긴다.
- 플레이어들은 자신의 차례 때 폭탄의 위치를 조정시킨다.
  - 상대방은 hit 또는 miss를 말해야 한다.
  - 만약에 맞으면 상대방은 배의 type 또한 말해야한다.

### 배의 종류

|   Type of Ship   | Size | Number |
| :--------------: | :--: | :----: |
| Aircraft Carrier |  6   |   1    |
|    Battleship    |  4   |   2    |
|    Submarine     |  3   |   2    |
|    Destroyer     |  3   |   1    |
|   Patrol Boat    |  2   |   4    |

### Computer's Board

- 외부 파일을 input으로 가져온다.
- battleships을 board에 랜덤하게 배치시킨다.
  - x좌표는 A-J, Y좌표는 1-10이다.
  - 배는 숮서대로 배치된다.
  - 서로 겹치거나 붙어있지 않다.

### Bombing Battle ships

- 플레이어는 폭탄을 던진다.
- computer player는 hit 또는 miss를 말한다.
  - 폭탄자리에 'X'를 mark한다. 맞으면 'X' + type of ship in lower case
- Player은 N개의 폭탄을 던질 수 있다.
- 마지막엔 score를 보여준다.

### Data structures

![상속 관계](./imgs/2023-04-26-20-23-30.png)

해당 사진을 참고해서 상속 관계를 구현

### Program Flow

- 시작하면 inputs을 받는다.
- 폭탄의 갯수
  - 양수의 정수가 아니면 BombInputException을 던진다.
- Program mode
  - d 또는 D는 Debug mode
  - r 또는 R은 Release mode
  - 만약에 위 4개가 아닌 값이 들어오면 ModeInputException을 던진다.
- board input file의 이름을 입력 받는다.
  - 파일이 없으면 랜덤으로 board를 만든다. -> 취소됨 구현 X -> 없으면 Exception 발생
  - input은 10x10 format으로 배들은 A/B/S/D/P로 표현하고 빈 칸은 No Ship을 의미한다.
- 입력은 자유롭게 받으면 된다.

#### Debug mode

- 매 턴마다 board를 보여준다.
- input은 초록색 output은 black으로 표시한다.
- input은 alphabet + number(C4)로 받는다.
- 만약에 맞으면 Hit + Ship type을 보여준다.
- 틀리면 Miss를 출력한다.
- 만약에 bombs을 다 쓰면 끝난다.
  - 최종 board를 보여준다.
  - 그리고 Score + Final_score을 print 한다.
- 이미 맞은 곳을 다시 맞추면 HitException을 던지고 Try again을 출력한다.

#### Release mode

Debug mode랑 비슷하지만 board를 매 턴마다 보여주지 않는다. 마지막에만 출력된다.
