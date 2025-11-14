-----

# 📁 디렉토리 구조 (Directory Structure)

본 프로젝트는 일관성 있는 빌드 및 유지보수를 위해 표준 C 프로젝트 구조를 따릅니다.


| 디렉토리           | 목적                 | 내용물                                                                        |
| :------------- | :----------------- | :------------------------------------------------------------------------- |
| **`src/`**     | **소스 코드**          | 프로그램의 핵심 로직(`.c`, `.cpp`)을 포함합니다.                                          |
| **`include/`** | **공개 헤더 파일**       | 외부에 공개되는 함수, 구조체 등의 선언(`.h`, `.hpp`)을 포함합니다. 컴파일 시 `-I` 옵션으로 참조됩니다.        |
| **`lib/`**     | **외부 라이브러리 (선택적)** | 프로젝트가 의존하는 외부 바이너리 라이브러리(`.a`, `.so`, `.lib` 등)를 보관합니다. (시스템 라이브러리는 제외)    |
| **`docs/`**    | **문서**             | 프로젝트 설명서, API 레퍼런스 등 기타 문서를 포함합니다.                                         |
| **`build/`**   | **빌드 임시 파일**       | GCC/Make 등의 빌드 시스템이 생성하는 오브젝트 파일(`.o`) 및 임시 파일이 저장되는 공간입니다. (Git 관리 대상 제외) |
| **`bin/`**     | **최종 실행 파일**       | 빌드 완료 후 생성되는 최종 실행 파일 또는 라이브러리 파일이 저장됩니다. (Git 관리 대상 제외)                   |


-----

## 🛠️ 선행 환경 설정

- 다운로드 준비
	1. [오라클 Precompiler](https://www.oracle.com/kr/database/technologies/instant-client/precompiler-downloads.html)
	2. SQL DEVELOPER 혹은 [SqlPlus](https://www.oracle.com/database/technologies/instant-client/linux-x86-64-downloads.html)

> 주의: Oracle instant-client 를 설치할 때 본인 운영체제에 설치된 glibc 버전과 호환되어야합니다.


1. 도커이미지로 데이터베이스 설치 및 실행
```bash
# 도커 설치
sudo apt update
sudo apt install docker.io

# 현재 사용자에게 도커 권한 부여 (쉘 재부팅 필요)
sudo usermod -aG docker $USER

# 데이터베이스 이미지 다운 및 실행
docker run -d -p 49161:1521 --name oracle11g -e ORACLE_ALLOW_REMOTE=true oracleinanutshell/oracle-xe-11g

docker ps # 도커 프로세스 확인
docker status # 상태확인
docker start oracle11g # 시작
docker stop oracle11g # 중지

# 기본 관리자 계정
# 아이디: system
# 비밀번호: oracle
```

2. 데이터베이스 외부 접근을 위한 방화벽 설정 및 포트허용 (선택)
```bash
# 패키지 목록 업데이트 
sudo apt update 

# ufw 설치 (대부분의 경우 이미 설치되어 있을 수 있습니다) 
sudo apt install ufw

sudo ufw status # 실행확인
sudo ufw enable # 방화벽 실행

sudo ufw allow 49161/tcp # 데이터베이스 접근을 위한 포트 허용

# 위 작업을 수행하면 SQL DEVELOPER 에서 접속이 가능합니다.
사용자이름: SYSTEM
비밀번호: oracle (접속해서 변경을 해주세요)
호스트이름: 해당 도커를 실행중인 리눅스 운영체제의 외부 아이피
포트: 49161
SID: XE
```
*위 작업을 수행해도 공유기를 사용하는 개인 서버일 경우 포트포워딩이 추가로 필요함*
3. gcc 설치
```bash
# 설치 확인
gcc -v

sudo apt update
sudo apt install -y gcc build-essential git
```

4. 사용자 환경 변수 수정 및 추가
- bash일 경우: (vim ~/.bashrc)
- zsh일 경우: (vim ~/zshrc)
```bash
# 터미널 명령줄에 해당 명령을 입력해서 cpu 아키텍쳐를 알아낸다.
uname -m

export LINUX_GNU=/usr/lib/(uname -m)값-linux-gnu

# Oracle Instantclient 설정
export ORACLE_HOME=/opt/oracle/설치한 버전별로 이름이 다릅니다.
export ORACLE_PROC=$ORACLE_HOME/sdk/proc

export LD_LIBRARY_PATH=$ORACLE_HOME:$LINUX_GNU:$LD_LIBRARY_PATH

# PATH에 ORACLE_HOME 및 sdk 경로를 추가하여 proc 명령어 사용 가능하게 함
export PATH=$PATH:$ORACLE_HOME:$ORACLE_HOME/sdk

# export LANG=en_US.UTF-8
export LANG="en_US.UTF-8" # 또는 ko_KR.UTF-8
export LC_ALL="en_US.UTF-8" # 또는 ko_KR.UTF-8

# 데이터베이스와 인코딩을 맟춰야합니다. (도커 오라클 데이터베이스 기본값 AL32UTF8)
# 확인 해 봐야 합니다.
export NLS_LANG=KOREAN_KOREA.AL32UTF8
```

5. SqlPlus, Precompiler 설치 및 SqlPlus 사용법
```bash
# 압축파일 디렉토리로 이동하지 않고 그냥 처음 디렉토리에서 실행해도 됩니다.

# 1. oracle 에서 다운받은 sqlplus와 precompiler를 서버로 업로드합니다.
# .zip 파일로 다운받아서 옮기는 것을 추천드립니다.

# 2. 다운받은 파일들을 /opt/oracle/에 붙혀넣습니다.
# 이제 해당 폴더가 $ORACLE_HOME이 됩니다.
sudo -p mkdir /opt/oracle
sudo mv ./*.zip /opt/oracle

# 3. 두 파일 전부 압축을 풉니다.
sudo apt update
sudo apt install unzip
sudo find "/opt/oracle" -maxdepth 1 -name "instantclient-*.zip" -exec unzip -o {} -d "$ORACLE_DIR" \;
sudo rm -rf "/opt/oracle"/*.zip

# 4. Sql plus 연결을 위한 라이브러리 다운
sudo apt update

# 라이브러리 검색 후 libaio와 유사한 이름으로 해당하는 것이 있으면 다운
# 배포판 별로 이름이 다른 것 같습니다.
sudo apt-cache search libaio
sudo apt install libaio1t64

sudo ldconfig # 라이브러리 갱신

# 심볼릭 링크 생성 (sql plus가 인식하는 파일 이름으로 수정)
cd /usr/lib/$(uname -m)-linux-gnu
sudo ln -s libaio.so.1t64 libaio.so.1
```

5.1 sql plus 및 pro\*c 연결을 위한 네트워크 설정
```bash
mkdir -p $ORACLE_HOME/network/admin
```

5.1 설정 파일 작성 tnsnames.ora
```shell
# $ORACLE_HOME/network/admin/tnsnames.ora 파일 내용
# PORT는 49161과 같이 실행할때 사용한 외부 포트 작성하면됩니다.
XE_DOCKER =
  (DESCRIPTION =
    (ADDRESS = (PROTOCOL = TCP)(HOST = localhost)(PORT = 1521))
    (CONNECT_DATA =
      (SERVER = DEDICATED)
      (SERVICE_NAME = XE)
    )
  )
```

5.3 sql\*plus로  리눅스에서 데이터베이스 접속 방법
```bash
sqlplus system/oracle@XE_DOCKER
```


6. Precompiler pcscfg.cfg 파일 수정
```bash
# 터미널 명령줄에 해당 명령을 입력해서 cpu 아키텍쳐를 알아낸다.
uname -m

# 터미널 명령줄에 해당 명령을 입력해서 gcc 버전을 알아낸다.
gcc --version 2>/dev/null | head -n 1 | awk '{print $3}' | cut -d'.' -f1


# 값 수정을 위해 vim 실행
sudo vim $ORACLE_HOME/precomp/admin/pcscfg.cfg

# 아래 값을 넣으면 됩니다.
# x86_64-linux-gnu/13/include 부분에서 x86_64와 13부분은 직접 확인해야합니다.
# x86_64는 CPU아키텍처 별로 다름 13은 gcc 버전입니다.
sys_include=($ORACLE_HOME/sdk/include,/usr/include,/usr/lib/gcc/x86_64-linux-gnu/13/include)
ltype=short
define=__x86_64__
define=_MATH_H
```

-----
## 🛠️ 빌드 방법 (Building the Project)

### 요구사항 (Prerequisites)
- 리눅스 계열 운영체제
* GCC
* Make
* Pro\*C (프로젝트 사용 버전 21C)

1. **빌드 실행** 
```bash
make
```
*프로젝트에 `Makefile`이 포함되어 있지 않다면, 직접 GCC 명령을 사용해야 합니다.*

2. **빌드 정리**
```bash
make clean
```

3. **실행 파일 확인**
빌드에 성공하면, 최종 실행 파일은 `./bin/` 디렉토리에 생성됩니다.
```bash
./bin/main
```

-----