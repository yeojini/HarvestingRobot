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

## 2. 프로젝트 개요
### 2-1. 프로젝트 기획 의도

- 현재 우리나라의 농가는 농업 인구 감소 및 고령화로 인한 노동력 부족 등의 어려움

    → 농업과 로봇 기술의 융합을 통한 기술의 발전으로 대체 노동력을 제공

- 농작물을 수확 할 때 사람의 손으로 일일이 따야 하는 경우 다수 → 영상 신호 처리를 통해 수확하고자 하는 농작물의 위치로 이동 하여 신속하고 정확하게 수확하는 무인 로봇의 필요성

### 2-2. 프로젝트 기간

2017.03.04 ~ 2017.06.01 약 3개월

## 3. 프로젝트 구성
### 3-1. Work Flow

1. D C 모터를 이용하여 주행 후 물체가 인식되면 정지하고 과일수확기능을 수행한다. 적외선 센서를 통해서 끝부분을 인식한 후 일정 높이로 상승 후 과일수확기능을 반복한다.
2. We b C a m 의 영상을 노트북으로 받아서 O p e n C V 를 통해 물체를 확인한다. 정해진 범위 내에 정해진 크기와 비율에 맞는 물체가 인식되면 로봇에게 주행 정지 및 높이에 대한 정보를 시리얼과 블루투스 통신으로 송신한다.
3. 수신한 높이 정보와 동일한 위치까지 올라가면 T O F 센서로 고추까지의 거리를 받고 로봇팔을 뻗은 후 서보모터가 장착된 g r i p p e r 로 고추를 수확한다. 수확동작이 끝나면 로봇팔을 원상복귀 시킨다.
4. 수확기능이 끝나면 원래의 높이까지 되돌아 온다. 이 후 물체가 인식될때 까지 전진하고 물체가 인식 시 수확기능을 반복수행한다.

### 3-2. H/W
