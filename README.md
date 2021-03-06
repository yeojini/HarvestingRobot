# OpenCV 기반의 작물 수확 로봇

[시연 영상 on Youtube](https://www.youtube.com/watch?v=DG3KgWhRhZA&feature=youtu.be)

## 1. OpenCV 개발 환경 설정
### 1-1. OpenCV 다운로드
본 프로젝트는 2017년 6월에 개발이 완료되었고
Windows 운영체제에서 Visual Studio 2017 을 사용하므로<br>
[OpenCV – 2.4.13.2 버전](https://opencv.org/releases/page/4/) 을 사용하였습니다.
압축 해제할 경로를 선택해주시고 Extract 버튼을 눌러주세요

### 1-2. OpenCV 폴더 구성
- build : header 파일, 이미 빌드된 라이브러리 및 바이너리 파일
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
![workflow](https://user-images.githubusercontent.com/58680458/81286767-90641f00-909c-11ea-91ec-9c1a859e9ea7.png)
1. D C 모터를 이용하여 주행 후 물체가 인식되면 정지하고 과일수확기능을 수행한다. 적외선 센서를 통해서 끝부분을 인식한 후 일정 높이로 상승 후 과일수확기능을 반복한다.
2. Web Cam 의 영상을 노트북으로 받아서 OpenCV 를 통해 물체를 확인한다. 정해진 범위 내에 정해진 크기와 비율에 맞는 물체가 인식되면 로봇에게 주행 정지 및 높이에 대한 정보를 시리얼과 블루투스 통신으로 송신한다.
3. 수신한 높이 정보와 동일한 위치까지 올라가면 ToF 센서로 고추까지의 거리를 받고 로봇팔을 뻗은 후 서보모터가 장착된 gripper 로 고추를 수확한다. 수확동작이 끝나면 로봇팔을 원상복귀 시킨다.
4. 수확기능이 끝나면 원래의 높이까지 되돌아 온다. 이 후 물체가 인식될때 까지 전진하고 물체가 인식 시 수확기능을 반복수행한다.

### 3-2. H/W
![hardwaredesign](https://user-images.githubusercontent.com/58680458/81286819-a4a81c00-909c-11ea-8caf-719c1e68824a.png)
![hardware](https://user-images.githubusercontent.com/58680458/81286882-c3a6ae00-909c-11ea-8d50-4a5362818bca.png)



### 3-3. 기술 스택
- 개발 환경 : Visual Studio 2017, Arduino Sketch
- S/W : OpenCV 2.4.13.2
- H/W : 블루투스 모듈, 적외선 센서, ToF 센서, 아두이노 Mega

## 4. 프로젝트 결과
### 4-1. 영상 처리
1) 물체 인식 기능
![imageprocessing](https://user-images.githubusercontent.com/58680458/81286867-ba1d4600-909c-11ea-9d3e-e4a293832a01.GIF)
- 고추의 왼쪽 꼭지점의 x 좌표가 395 ~ 445 사이에 위치 할 때만 고추를 인식하도록 한다.
- 고추의 가로와 세로를 계산하여 가로세로의 비가 2 . 4 이상일 때만 고추를 인식하도록 한다.
- 화면에 고추가 인식되지 않을 때는 ‘d ’를, 고추의 왼쪽꼭지점의 y 좌표가 0 ~ 275 사이에 위치하면 ‘a ’를, 275 ~ 305 사이에 위치하면 ‘b ’를, 305 ~ 480 사이에 위치하면 ‘c ’를 보낸다

2) 작물 수확 기능
- a 수신 : 수확 x 범위 내에 있으나 목표 지점이 현재 gripper 가 위치한 지점보다 하단부에 있는 경우로 b 수신 할 때까지 하강
- b 수신 : 수확 x, y범위 내에 위치한 경우로 상하 이동 정지 후 ToF 센서로 거리 측정, 측정된 거리 만큼 로봇 팔 길이 조절해 수확 후 원래 높이로 복귀
- c 수신 : 수확 x 범위 내에 있으나 목표 지점이 현재 gripper 가 위치한 지점보다 상단부에 있는 경우로 b 수신 할 때까지 상승
- d 수신 : 수확 x 범위 내에 목표 지점이 인식되지 않은 경우로 직진 동작 수행

### 4-2. Master Bluetooth

- 영상신호처리 알고리즘으로 얻은 제어값을 시리얼 통신으로 아두이노에 보낸다
- 아두이노는 제어값을 블루투스 통신을 통해서 Slave Bluetooth 모듈로 보낸다.

### 4-3. Slave Bluetooth

- 주행 중에 고추를 인식하면 주행을 멈춘다.
- 블루투스 통신으로 얻은 제어값을 통해 로봇의 높이와 로봇팔을 제어한다 - ‘a ’를 받으면 로봇의 높이를 높이고 ‘c ’를 받으면 높이를 낮추며 ‘b ’를
받으면 높낮이 조절을 멈추고 로봇팔을 뻗는다.
- 로봇팔을 뻗고 그리퍼를 모으고 다시 로봇팔을 줄이고 그리퍼를 벌린다.
- 그리퍼를 벌린 후 로봇의 초기 높이로 돌아간다.



