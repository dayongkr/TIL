# 자바프로그래밍실습 7주 차

## File I/O

### Standard Streams

System.in, System.out, System.err가 있는데 각각 InputStream, PrintStream, PrintStream의 인스턴스이다. 참고로 PrintStream은 OutputStream을 상속받은 클래스이다.

System.in은 1바이트씩 읽어들이는데 이는 한글이나 다른 언어를 읽을 수 없다. 따라서 지금까지 Scanner를 사용해서 입력을 받은 것이다.

### File Streams

FileInputStream과 FileOutputStream을 사용해서 파일을 읽고 쓸 수 있다. 이는 Standard Stream를 상속받은 클래스이다.

#### InputStreamReader

InputStreamReader는 InputStream을 Reader로 변환해주는 클래스이다.

``` java
import java.io.*;

public class Main {
  public static void main(String[] args) {
    try {
      InputStreamReader isr = new InputStreamReader(System.in);
      int c;
      while ((c = isr.read()) != -1) { // -1은 EOF
        System.out.print((char) c);
      }
      isr.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}
```

read할 때 한 문자씩 읽어들이기 때문에 한글 등 다른 언어를 읽을 수 있다.

#### BufferedReader

BufferedReader는 Reader를 상속받은 클래스이다. BufferedReader는 readLine() 메소드를 제공하는데 이는 한 줄씩 읽어들이는 메소드이다.

생성하는 방법은 InputStreamReader를 BufferedReader에 넣어주면 된다.

따라서 byte는 InputStream, char은 InputStreamReader, String은 BufferedReader를 사용하면 된다.

### Writer

Reader와 똑같이 Writer도 있다. Writer는 OutputStreamWriter와 BufferedWriter가 있다. 사용법은 동일하다.

참고로 OutputStreamWriter는 Write 하는 동안은 lock이 걸리기 때문에 여러 스레드에서 동시에 write하면 안된다. 하지만 BufferWriter를 사용하면 write할 때 lock이 걸리지 않기 때문에 여러 스레드에서 동시에 write할 수 있다.
