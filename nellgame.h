#ifndef NELLGAME_H
#define NELLGAME_H
#include <graphics.h>
#include <math.h>
#include<fstream>
#include <iostream>
using namespace std;
int main1()
{
	cleardevice();
    initgraph( 600, 900 );	
	setcolor(BLACK);
	setfillcolor(GREEN);
	MUSIC mus,yinxiao;	//音乐
	mus.OpenFile("康康舞曲-奥芬巴赫-4091506.mp3");
	yinxiao.OpenFile("12299.mp3");
	mus.Play();
	int c[6]={},k;
	ifstream inputfile("passed_level.txt");
	for(int i=0;i<6;i++) inputfile>>c[i];
	inputfile.close();
	
	//难度选择界面
    loop:setbkcolor( EGERGB(0xff, 0xff,0xff) );
	setcaption("LEVEL");
	setfont(40,0,"宋体");
	setcolor(BLACK);
	outtextxy(10,10,"HIT 1 TO 5 TO CHOOSE");
	if(c[1]==0) setcolor(BLACK);
	else setcolor(GREEN);
	outtextxy(10,60,"1. 5 pins");
	if(c[2]==0) setcolor(BLACK);
	else setcolor(GREEN);
	outtextxy(10,120,"2. 10 pins");
	if(c[3]==0) setcolor(BLACK);
	else setcolor(GREEN);
	outtextxy(10,180,"3. 20 pins");
	if(c[4]==0) setcolor(BLACK);
	else setcolor(GREEN);
	outtextxy(10,240,"4. 30 pins");
	if(c[5]==0) setcolor(BLACK);
	else setcolor(GREEN);
	outtextxy(10,300,"5. 40 pins");
	setcolor(BLACK);
	outtextxy(10,360,"6. 音乐暂停");
	outtextxy(10,420,"7. 音乐开始");
	outtextxy(10,480,"8. 一键清空通关记录");
	outtextxy(10,540,"0. exit");
	int key,key2,tot=0;
	key=getch();
	switch(key){
		case key_1:
			k=1;
			tot=5;
			cleardevice();
			break;
		case key_2:
			k=2;
			tot=10;
			cleardevice();
			break;
		case key_3:
			k=3;
			tot=20;
			cleardevice();
			break;
		case key_4:
			k=4;
			tot=30;
			cleardevice();
			break;
		case key_5:
			k=5;
			tot=40;
			cleardevice();
			break;
		case key_6:
			mus.Pause();
			goto loop;
		case key_7:
			mus.Play(0);
			goto loop;
		case key_8:{
			for(int i=0;i<6;i++) {
				c[i]=0;
				ofstream outputfile2("passed_level.txt",ios::out);
				outputfile2<<c[i]<<endl;
				outputfile2.close();
			}
			goto loop;
		}
		case key_0:{
			ofstream outputfile2("passed_level.txt",ios::out);
			for(int i=0;i<6;i++) outputfile2<<c[i]<<endl;
			outputfile2.close();
			return 0;
		}	
		default:
			outtextxy(10,600,"输入无效！2秒后重输！");
			delay_ms(2000);
			cleardevice();
			goto loop;
	}
	setbkcolor( EGERGB(300, 300,300) );
	setcolor(GREEN);
	setcaption("GAME");
	//创建指针
	PIMAGE nell=newimage();
	getimage(nell,"nell.png");
	//针的最大个数的数组创建，游戏初始化
	int a[tot]={},t=tot;
	int num=0;
	//鼠标按下标志
	bool flag=1;
	//游戏状态标志
	bool star=true;
	setfillcolor(GREEN);
	//抗锯齿
	ege_enable_aa(true);
	//游戏主循环
	for(;is_run()&&star;delay_fps(45)){
		if(keystate(key_mouse_l)){
			yinxiao.SetVolume(0.2);
			yinxiao.Play(0);
			if(flag){
				num++;
				flag=0;
				//判断针是否重叠
				for(int i=1;i<num;i++){
					if(a[i-1]%360<5||a[i-1]%360>355) star=0;
				}
				t--;
			}
		}
		if(!keystate(key_mouse_l)) flag=1;
		for(int i=0;i<num;i++) a[i]+=2;//旋转角度
		cleardevice();
		putimage_withalpha(NULL,nell,300,100);//针初始位置图片
		for(int i=0;i<num;i++) putimage_rotate(NULL,nell,300,400,0.5,1.5,PI/180*a[i],1);//旋转针的图片
		fillellipse(300,400,50,50);	//中心圆	
		setfont(25,0,"宋体");
		setcolor(WHITE);
		if(t==0) setcolor(GREEN);
		else if(star==0) setcolor(RED);
		xyprintf(500,30,"剩余%d",t);
		setcolor(WHITE);
		delay_ms(10);
		setbkmode(TRANSPARENT);
		if(num==tot&&star) break;		//针的最大数量
	}
	if(star==0) {
		setcolor(RED);
		setfillcolor(RED);	
	}
	fillellipse(300,400,50,50);
	setfont(40,0,"宋体");
	if(star==0) outtextxy(50,200,"寄!");
	else {
		outtextxy(50,200,"WIN!");
		c[k]=1;
	}
	lop:setfont(25,0,"宋体");
	outtextxy(10,10,"continue or exit?");
	outtextxy(10,50,"1. continue");
	outtextxy(10,90,"2. exit");
	delay_ms(30);
	setbkmode(TRANSPARENT);
	key2=getch();
	switch(key2){
		case key_1:{
				cleardevice();
				ofstream outputfile2("passed_level.txt",ios::out);
				for(int i=0;i<6;i++) outputfile2<<c[i]<<endl;
				goto loop;
				break;
			}
			
		case key_2:{
			delimage(nell);
			ofstream outputfile2("passed_level.txt",ios::out);
			for(int i=0;i<6;i++) outputfile2<<c[i]<<endl;
			outputfile2.close();
			return 0;
			break;
		}
			
		default:
			outtextxy(10,550,"输入无效！2秒后重输！");
			delay_ms(2000);
			cleardevice();
			goto lop;
			break;
	}
	return 0;
}
#endif
