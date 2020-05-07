# OpenCV 기반의 작물 수확 로봇

## 1. OpenCV 개발 환경 설정
### 1-1. OpenCV 다운로드
본 프로젝트는 2017년 6월에 개발이 완료되었고
Windows 운영체제에서 Visual Studio 2017 을 사용하므로
[OpenCV – 2.4.13.2 버전](https://opencv.org/releases/page/4/) 을 사용하였습니다.
압축 해제할 경로를 선택해주시고 Extract 버튼을 눌러주세요

### 1-2. OpenCV 폴더 구성
- build : header 파일, 이미 빌드된 라이브러리 및 바이너리 팡ㄹ
- sources : OpenCV 소스 코드

### 1-3. Visual Studio 프로젝트 생성
- File - New - Project - Creat a new project
- Visual C++ - Windows Console App
- 속성 x64 로 변경

### 1-4. Visual Studio & OpenCV
- Header 파일 위치 지정 : Project - Properties - VC++ Directories - Include Directories - Edit.. - (경로\opencv\build\include)
- 라이브러리 파일 경로 추가 : Library Directories - Edit.. -  (경로\opencv\build\x64\vc15\lib)
- 빌드된 라이브러리 파일 linker : Project - Properties - Linker - input - Additional Dependencies
- OpenCV 바이너리 (.dll 경로 지정) : Project - Properties - Debugging - Environment - Edit. - PATH=C:\opencv\build\x64\vc14\bin;%PATH%
