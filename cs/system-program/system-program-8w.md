# 시스템프로그램 8주 차

지금까지 공부한 것들을 가지고 buffer overflow를 공부하면서 취약점을 배우게 된다.

## Buffer Overflow

C에서는 배열의 bound 확인을 수행하지 않고 local variables이 stack에 저장된다. 이러한 것들로 심각한 프로그램 에러를 발생시킨다.

### Vulnerable codes

```c
void echo()
{
  char buf[8];
  puts(buf);
  gets(buf);
}

int main(void) {
  printf("Type: ");
  echo();
  return 0;
}
```

위 코드는 echo 함수에서 buf를 8바이트만큼 선언하고, puts와 gets를 통해 buf를 출력하고 입력받는다. 이때 gets는 입력받은 문자열의 길이가 buf의 길이보다 길어도 에러를 발생시키지 않고 입력받는다. 따라서 buf의 길이를 넘어서는 문자열을 입력하면 stack에 저장된 local variables와 return address와 같은 stack에 저장된 데이터들을 overwrite할 수 있다. 또한 Segmentation fault가 발생한다.

### Malcious use of buffer overflow

악성 코드를 불러와서 stack에 저장한 후 %rsp를 알아내 return address 까지 overwrite해서 악성 코드를 실행시킬 수 있다.

### Avoiding buffer overflow

fgets를 사용하면 읽고 싶은 최대 길이를 지정할 수 있다. 따라서 buf의 길이보다 긴 문자열을 입력하면 뒤에는 읽지 않기 떄문에 buffer overflow를 막을 수 있다.

### System-level protection

위에서는 개발자가 buffer overflow를 막기 위해 코드를 작성했지만, 시스템에서는 buffer overflow를 막기 위해 시스템 레벨에서 protection을 제공한다.

#### Stack randomization

xploit code를 injection만 해서는 안 돼고 해당 code를 실행될 수 있게 해야 하기 때문에 rsp가 필요하다. 따라서 매번 프로그램이 시작할 때 stack의 위치를 매번 바꿔서 알기 어렵게 만드는 방법이다. 

Linux 32-bit 기준 0xff7fc59c ~ 0xffffd09c(range of 2^23)을 가진다. 이 범위에서 rsp를 맞출 확률은 로또 1등 확률과 비슷하다.  64-bit은 12byte를 사용하여 0x7fff0001b698 ~ 0x7ffffffaa4a8 (range of 2^32)을 가진다.

#### ASLR(Address Space Layout Randomization)

Stack randomization을 더 진화 시킨 것으로 모든 address을 randomization을 한다. 

이는 nop sled를 사용해서 뚫을 수 있다. nop는 아무것도 하지 않는 instruction으로 이를 무시하고 다음 instruction을 실행하는 성질을 가지고 있다. 따라서 return address에 nop이 하나만 걸려도 쭉 타고 올라가 exploit code가 실행될 수 있는 것이다.

#### Canary

Canary는 stack에 저장되는 값으로 stack이 overflow되는지 확인하는 값이다. 이 값이 변하지 않으면 정상적으로 실행되고 변하면 stack이 overflow되었다는 것을 알 수 있다. 스택 중간에 추가되며 OS에 있는 `%fs:40` 즉 fs regs에 있는 40 offset에 해당하는 정수 값을 가져와 저장한다.

컴파일러가 컴파일할 때 canary를 생성해서 buffer overflow를 막는 방법이다.

#### DEF(Data Execution Prevention)

대부분의 system에는 종류별로 access control(read, write, execute)을 가지고 있다. 하지만 x86에서는 read와 execute를 합쳐서 사용하기 때문에 read 권한만 가지고 있더라도 execute 권한을 가질 수 있다. DEF는 이러한 문제를 해결하기 위해 execute 권한을 가지지 않은 메모리에 있는 코드를 실행할 수 없게 한다. 따라서 stack에 있는 코드를 실행할 수 없게 한다.

이를 뚫는 방법이 있는데 이를 RTL(Return-to-Libc)이라고 한다. library에서는 execute 권한이 있기 때문에 system library의 함수에 malware 실행파일의 주소를 넣어서 실행하는 방법이다.

또 다른 방법으로는 ROP(Return Oriented Programming)이라는 방법이 있다. 이는 기존에 있는 코드를 조합해서 새로운 코드를 만드는 방법이다. 