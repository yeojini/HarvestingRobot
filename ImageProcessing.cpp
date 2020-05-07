#include<opencv2\\core\\core.hpp>
#include<opencv2\\highgui.hpp>
#include<opencv2\\highgui\\highgui_c.h>
#include<opencv2\\imgproc\\imgproc.hpp>
#include<opencv2\\imgproc\\imgproc_c.h>
#include<vector>
#include<iostream>
#include<fstream>
#include"math.h"
#include"SerialUtil.h"
#include<string>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
using namespace std;
using namespace cv;
string coordinate;


void Delay(clock_t wait) {
	clock_t goal;
	goal = wait + clock();
	while (goal > clock());
}
Point xchange(Point& x) {
	for (int i = 0; i < 32; i += 20) {
		if (x.x >= i && x.x < i + 20) {
			x.x = i + 20;
		}
	}for (int i = 0; i < 24; i += 20) {
		if (x.y >= i && x.y < i + 20) {
			x.y = i + 20;
		}
	}
	return Point(x.x, x.y);
}

int main()
{
	HANDLE hSerial = CreateFile(L"COM4", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial != INVALID_HANDLE_VALUE) {
		printf("Port opened! \n");
		DCB dcbSerialParams;
		GetCommState(hSerial, &dcbSerialParams);
		dcbSerialParams.BaudRate = CBR_9600;
		dcbSerialParams.ByteSize = 8;
		dcbSerialParams.Parity = NOPARITY;
		dcbSerialParams.StopBits = ONESTOPBIT;
		SetCommState(hSerial, &dcbSerialParams);
	}
	else {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			printf("Serialportdoesn'texist!\n");
		}
		printf("Errorwhilesettingupserialport!\n");
	}
	
	char outputChars[] = "c";

	DWORD btsIO;
	Mat img, img_gray, channel[3];
	VideoCapture cam(0);
	double distance = 0;
	cam.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cam.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	cam.set(CV_CAP_PROP_CONVERT_RGB, 1);
	namedWindow("Frame", WINDOW_AUTOSIZE);
	while (waitKey(10) != 'a') {
		cam >> img;
		cvtColor(img, img_gray, COLOR_RGB2GRAY);
		split(img, channel);
		subtract(channel[2], img_gray, img_gray);
		threshold(img_gray, img_gray, 90, 255, THRESH_BINARY);
		erode(img_gray, img_gray, Mat(), Point(-1, -1), 4);
		dilate(img_gray, img_gray, Mat(), Point(-1, -1), 4);
		vector<vector<Size>>contors;
		vector<Vec4i>heirarcy;
		findContours(img_gray, contors, heirarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		vector<Rect>boundRect(contors.size());

		vector<vector<Point>>contor_poly(contors.size());
		for (int i = 0; i < contors.size(); i++) {
			approxPolyDP(Mat(contors[i]), contor_poly[i], 3, true);
			boundRect[i] = boundingRect(Mat(contor_poly[i]));
		}int max_index = 0, max_area = 0;
		for (int i = 0; i < boundRect.size();
			i++) {
			int a = boundRect[i].area();
			if (a > max_area) {
				max_area = a;
				max_index = i;
			}
		}
		cout.precision(3);
		
		if (boundRect.size() > 0 && (boundRect[max_index].br().y - boundRect[max_index].tl().y) > 67 && 
			((boundRect[max_index].tl() + boundRect[max_index].br())/2).x > 395 && 
			((boundRect[max_index].tl() + boundRect[max_index].br())/2).x < 445 )
		{
			rectangle(img,xchange(boundRect[max_index].tl()), xchange(boundRect[max_index].br()), Scalar(0, 255, 0), 2, 8, 0);
			cout << boundRect[max_index].tl().y - boundRect[max_index].br().y << endl;
			if (boundRect[max_index].tl().y - 50 < 225) {
				coordinate = "a";
				cout << coordinate;
				outputChars[0] = 'a';
				WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
			}
			else if(boundRect[max_index].tl().y - 50 >= 225 && (boundRect[max_index].tl().y - 50 <= 245)) {
				coordinate = "b";
				cout << coordinate;
				outputChars[0] = 'b';
				WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
			}
			else if(boundRect[max_index].tl().y - 50 > 245) {
				coordinate = "c";
				cout << coordinate;
				outputChars[0] = 'c';
				WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
			}
			cout << (float)boundRect[max_index].height / boundRect[max_index].width << fixed << "";
			imshow("Frame", img);
		}
		else {
			coordinate = "d";
			cout << coordinate;
			outputChars[0] = 'd';
			WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
			imshow("Frame", img);
		}
		
	}
	cam.release();
	CloseHandle(hSerial);
	return 0;
}
