# GitHub에서 과제 체험하기
This example project is written in C, and tested with make and bash scripts.

### The assignment
- 2 x 2 행렬 이진 파일과 2 x 1 벡터 이진 파일에서 double 크기의 데이터를 읽어 배열 A와 벡터 B에 저장한 뒤, $AX = B$를 푸는 벡터 $X$를 찾아 2 x 1 벡터 이진 파일에 저장하는 프로그램을 완성한다. 이 세 개의 파일은 인자로 받으며 argv[1]과 argv[2]는 입력으로 각각 2 x 2 행렬 이진 파일과 2 x 1 벡터 이진 파일에 해당하고 $A$와 $B$에 로드된다. argv[3]은 답 $X$를 저장할 파일 이름이다. 부분적으로 실행되는 프로그램이 hw0.c로 제공된다. 주어진 hw0.c에는 $X$를 구하는 코드가 빠져있다. 
- $A = [ [ a_{00}, a_{01} ], [ a_{10}, a_{11} ] ], B = [ b_0, b_1 ], X = [ x_0, x_1 ]$ 일 때, 다음과 같이 구할 수 있다.
$$det = \frac{1}{a_{00} b_0 - a_{01} b_1}$$

$$X = det \cdot \left[ { \begin{array}{c} a_{11} b_0 - a_{01} b_1 \\ 
a_{00} b_1 - a_{10} b_0 \\ \end{array} } \right]$$

- 프로그램을 수정한 뒤 다음과 같이 컴파일한다. 정상적인 실행은 다음과 같다.

`./make all`

- 제대로 컴파일되면 hw0, hwdiff, showdata 실행 파일이 만들어진다. hw0는 다음과 같이 실행할 수 있다.

`./hw0 A.dat B.dat X.dat`

- 프로그램이 정상적으로 종료되면 쉘에게 0을 반환하고 이진 파일 X.dat를 생성한다. hw0가 3개의 인자를 받지 못하면 다음 에러 메시지를 표준에러로 출력하며 1을 반환한다.

`Usage: ./hw0 <mat> <invec> <outvec>`

- 이진 행렬들의 내용을 확인하려면 다음과 같이 실행한다. 세 개의 이진 파일들을 모두 기입해야 한다.

`./showdata A.dat B.dat X.dat`

- showdata로 확인하면 A.dat와 B.dat의 결과는 Xa.dat와 같다. 하지만, 다음과 같이 Linux의 diff로 동일 내용인지 체크하면 다르다고 나온다.

`diff X.dat Xa.dat`

- 이는 실수 연산 (floating point operation)의 round-off로 인해 발생하는 아주 작은 값의 오차 때문이다. 이 문제 때문에 결과 파일과 정답을 비교하기 위해 diff 대신 hwdiff를 다음과 같이 사용한다. diff와 마찬가지로 hwdiff는 두 파일의 내용이 같을 때 아무런 메시지를 출력하지 않으며 쉘에 0을 반환한다. 

`./hwdiff X.dat Xa.dat`

### Setup command
N/A

### Run command to test program
`make test ARG=1`

`make test ARG=2`

`make test ARG=3`

`make test ARG=4`

### Notes
- `gcc` can be used to compile and link C applications for use with existing test harnesses or C testing frameworks.
