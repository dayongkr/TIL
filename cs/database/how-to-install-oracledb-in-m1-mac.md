# m1 Mac에 오라클 db 설치하기

아무래도 윈도우 사용자들이 많다 보니 학교에서는 윈도우 기준으로 수업들이 진행된다.

그래서 교수님들은 보통 vm 프로그램들을 사용해서 수업을 따라오라고 하시지만 m1 이상의 arm 칩셋으로 이루어진 Mac 시스템에서는 x86기반의 window를 돌리기 위해 에뮬레이팅을 하게 되는데 상당한 성능 저하가 일어나는 것을 몸소 느끼게 되었다.

> 진짜 이건 2023년도에 감당 안 되는 수준의 성능이었다.

이에 굴복하고 x86기반의 노트북을 사기에는 가난한 대학생으로서 너무 버거운 일이
였다. 따라서 아프니깐 청춘... 최대한 방법을 찾아내려고 노력했다.
 
그러다가 Docker container를 CLI로 실행시켜주는 Colima를 찾게 되었다.

## Colima

일단 Docker는 워낙 유명한 서비스이므로 간단하게 설명하자면 성능상으로 더 좋은 VM이다.

어쨋든 이 Docker는 원래 무료였지만 Docker Desktop이라는 프로그램이 부분 유료화가 되면서 다양한 대체제가 생겼는데 Colima도 그중에 하나인 것 같다.

다만 Colima는 최소한의 셋업(CLI)으로 Docker Container를 실행시킨다. 게다가 Colima를 실행 시킬때 x86으로 에뮬레이팅할 수 있는 기능도 있어서 M1 Mac을 지원한다.

## 설치를 해보자

일단 Docker와 Colima를 Homebrew를 이용해서 깔아보자

``` zsh
brew install docker colima
```

만약에 위 명령어가 수행이 안 되면 Homebrew가 안 깔린 것이니 먼저 깔고 오자.

``` zsh
colima start --memory 4 --arch x86_64
```

설치가 완료되면 이제 Colima를 구동시켜주면 된다. 위 명령어를 치면 x86 64bit architecture와 4gb 메모리를 가진 시스템이 구동된다. 프로세스를 보니 Colima 또한 Qemu 오픈 소스를 통해서 에뮬레이팅하는 것 같다.

그리고 에뮬레이팅하는 동안 설정한 메모리는 고정으로 차지하고 있으니 필요 없으면 `colima stop`을 통해 Colima를 꺼두자.

``` zsh
docker run --name oracle -e ORACLE_PASSWORD=pass -p 1521:1521 -d gvenzl/oracle-xe
```

위 명령어는 이제 docker에 oracle이라는 컨테이너를 만들고 그 위에 gvenzl 사용자가 만든 oracle-xe 이미지를 설치하겠다는 명령어인데 일단 oracle이 구동되게 하는 게 주목적이니 자세한 설명은 패스!

``` zsh
docker ps
```

잘 설치를 했다면 방금 만든 컨테이너를 위 명령어를 통해 확인 할 수 있을 것이다.

``` zsh
docker logs -f oracle
```

이제 oracle db가 제대로 설치되고 있는지 확인하기 위해 로그를 체크 해줘야 하는데 위 명령어를 치고 기다리다 보면 DATABASE IS READY TO USE!라는 문구가 뜰 텐데 이러면 설치가 완료된 것이다.

설치를 다 했는데 문제가 있다... 원래는 SCOTT라는 계정과 dump.sql 파일이 존재하는데 방금 설치한 이미지에는 해당 부분이 빠져있다. 따라서 따로 SCOTT 계정을 만들고 container로 sql 파일을 copy를 해주고 해당 스크립트를 실행 시켜줘야한다.

``` zsh
docker cp "로컬의 sql 파일 위치" oracle:/scott.sql
docker exec -it oracle sqlplus
---
// sqlplus 실행됨 (username = "system", password = "pass")
> CREATE USER scott identified by tiger; // scott 계정 생성
> GRANT CONNECT, resource, dba to scott; // 권한 설정
> conn scott/tiger; // scott 계정 접속
> @../../scott.sql; // scott.sql 스크립트 실행
```

위 명령어들을 한 줄씩 실행시키면 원활하게 dummy sql과 scott 계정을 만들 수 있을 것이다.

혹시 scott.sql이 필요할 수 있으니 남겨두겠다.

``` sql
Rem Copyright (c) 1990 by Oracle Corporation
Rem NAME
REM    UTLSAMPL.SQL
Rem  FUNCTION
Rem  NOTES
Rem  MODIFIED
Rem	gdudey	   06/28/95 -  Modified for desktop seed database
Rem	glumpkin   10/21/92 -  Renamed from SQLBLD.SQL
Rem	blinden   07/27/92 -  Added primary and foreign keys to EMP and DEPT
Rem	rlim	   04/29/91 -	      change char to varchar2
Rem	mmoore	   04/08/91 -	      use unlimited tablespace priv
Rem	pritto	   04/04/91 -	      change SYSDATE to 13-JUL-87
Rem   Mendels	 12/07/90 - bug 30123;add to_date calls so language independent
Rem
rem
rem $Header: utlsampl.sql 7020100.1 94/09/23 22:14:24 cli Generic<base> $ sqlbld.sql
rem
SET TERMOUT OFF
SET ECHO OFF

rem CONGDON    Invoked in RDBMS at build time.	 29-DEC-1988
rem OATES:     Created: 16-Feb-83

DROP TABLE DEPT;
CREATE TABLE DEPT
       (DEPTNO NUMBER(2) CONSTRAINT PK_DEPT PRIMARY KEY,
	DNAME VARCHAR2(14) ,
	LOC VARCHAR2(13) ) ;
DROP TABLE EMP;
CREATE TABLE EMP
       (EMPNO NUMBER(4) CONSTRAINT PK_EMP PRIMARY KEY,
	ENAME VARCHAR2(10),
	JOB VARCHAR2(9),
	MGR NUMBER(4),
	HIREDATE DATE,
	SAL NUMBER(7,2),
	COMM NUMBER(7,2),
	DEPTNO NUMBER(2) CONSTRAINT FK_DEPTNO REFERENCES DEPT);
INSERT INTO DEPT VALUES
	(10,'ACCOUNTING','NEW YORK');
INSERT INTO DEPT VALUES (20,'RESEARCH','DALLAS');
INSERT INTO DEPT VALUES
	(30,'SALES','CHICAGO');
INSERT INTO DEPT VALUES
	(40,'OPERATIONS','BOSTON');
INSERT INTO EMP VALUES
(7369,'SMITH','CLERK',7902,to_date('17-12-1980','dd-mm-yyyy'),800,NULL,20);
INSERT INTO EMP VALUES
(7499,'ALLEN','SALESMAN',7698,to_date('20-2-1981','dd-mm-yyyy'),1600,300,30);
INSERT INTO EMP VALUES
(7521,'WARD','SALESMAN',7698,to_date('22-2-1981','dd-mm-yyyy'),1250,500,30);
INSERT INTO EMP VALUES
(7566,'JONES','MANAGER',7839,to_date('2-4-1981','dd-mm-yyyy'),2975,NULL,20);
INSERT INTO EMP VALUES
(7654,'MARTIN','SALESMAN',7698,to_date('28-9-1981','dd-mm-yyyy'),1250,1400,30);
INSERT INTO EMP VALUES
(7698,'BLAKE','MANAGER',7839,to_date('1-5-1981','dd-mm-yyyy'),2850,NULL,30);
INSERT INTO EMP VALUES
(7782,'CLARK','MANAGER',7839,to_date('9-6-1981','dd-mm-yyyy'),2450,NULL,10);
INSERT INTO EMP VALUES
(7788,'SCOTT','ANALYST',7566,to_date('13-JUL-87','DD-MON-RR')-85,3000,NULL,20);
INSERT INTO EMP VALUES
(7839,'KING','PRESIDENT',NULL,to_date('17-11-1981','dd-mm-yyyy'),5000,NULL,10);
INSERT INTO EMP VALUES
(7844,'TURNER','SALESMAN',7698,to_date('8-9-1981','dd-mm-yyyy'),1500,0,30);
INSERT INTO EMP VALUES
(7876,'ADAMS','CLERK',7788,to_date('13-JUL-87','DD-MON-RR')-51,1100,NULL,20);
INSERT INTO EMP VALUES
(7900,'JAMES','CLERK',7698,to_date('3-12-1981','dd-mm-yyyy'),950,NULL,30);
INSERT INTO EMP VALUES
(7902,'FORD','ANALYST',7566,to_date('3-12-1981','dd-mm-yyyy'),3000,NULL,20);
INSERT INTO EMP VALUES
(7934,'MILLER','CLERK',7782,to_date('23-1-1982','dd-mm-yyyy'),1300,NULL,10);
DROP TABLE BONUS;
CREATE TABLE BONUS
	(
	ENAME VARCHAR2(10)	,
	JOB VARCHAR2(9)  ,
	SAL NUMBER,
	COMM NUMBER
	) ;
DROP TABLE SALGRADE;
CREATE TABLE SALGRADE
      ( GRADE NUMBER,
	LOSAL NUMBER,
	HISAL NUMBER );
INSERT INTO SALGRADE VALUES (1,700,1200);
INSERT INTO SALGRADE VALUES (2,1201,1400);
INSERT INTO SALGRADE VALUES (3,1401,2000);
INSERT INTO SALGRADE VALUES (4,2001,3000);
INSERT INTO SALGRADE VALUES (5,3001,9999);
COMMIT;

SET TERMOUT ON
SET ECHO ON
```

``` sql
select * from emp;
```

위 명령어를 쳐서 데이터들이 쭉 나오면 성공적으로 적용한 것이다.

정말 이 방법을 찾고 설치하는 과정에서도 많은 역경이 있었지만 결국 해냈다.. 물론 과제들을 수행하면서 제대로 설치했고 호환이 잘 되는지 확인을 해봐야겠지만 지금은 잘 작동하는 것 같아 만족이다.

진짜 m1... 아직은 쓰기 이른 것인가…?
