# 맥에서 C언어 다루기

많은 강의가 윈도우 기준으로 진행되기 때문에 보통 `visual studio` 혹은 `Dev-C++` 에디터 기준으로 진행돼서 많은 맥북 이용자가 당황할 수 있다.

하지만 맥에서도 간단한 설치 과정을 거치면 문제없이 원활하게 C언어를 배울 수 있을 것이다.

맥에서 C언어를 다루는 방법은 정말 다양하겠지만 많은 유저들도 있어서 도움받기 쉬운 `visual code`라는 에디터로 다루는 방법을 소개하겠습니다.

## Homebrew - CLI로 설치하기

먼저 다양한 프로그램 및 패키지를 설치할 수 있는 Homebrew(패키지 관리자)를 설치해봅시다.

``` zsh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

`terminal`에 위 명령어를 입력하면 설치할 수 있습니다.

## Visual code - CLI로 설치하기

``` zsh
brew install vscode
```

Homebrew 설치했을 때처럼 `terminal`에 위 명령어를 입력하면 vscode를 설치할 수 있다.

## Visual code Extension 설치

다양한 Extension이 있지만 C언어를 다룰 때 필히 설치해야 할 Extension은 Microsoft 사에서 만든 `C/C++` 그리고 간단하게 코드를 실행할 수 있는 `Code Runner`만 설치해도 아주 편안하게 C언어를 다룰 수 있을 거다.

vscode는 워낙 많은 유저들이 사용하고 있어서 유용한 Extension이 정말 많으니 직접 찾아보면서 즐거운 코딩 생활을 하기 바랍니다!

## 간단한 사용 방법

먼저 폴더를 만드신 후 `File > Open Folder...`로 해당 폴더를 열고 `command + N` 단축키를 사용하여 새 파일을 만들고 *.c 형태로 파일을 저장하면 됩니다.

그 후 코드를 작성한 후 `저장 > 화면 우클릭 > Run Code 클릭`하면 아래 terminal 창이 켜지면서 실행되는 것을 볼 수 있을 것입니다.

## Tip

코드를 실행하고 자동으로 종료하고 싶으면 `Code > Settings > Settings > run in terminal 입력 > Run code configuration > Code-runner: Run In Terminal 체크`를 하면 실행 후 자동 종료된다.
