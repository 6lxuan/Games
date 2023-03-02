#ifndef BIRDGAME_H
#define BIRDGAME_H
#include <iostream>
#include <fstream>  
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"image.h"
using namespace std;
//a、b为参数的随机函数
int gbr(int a,int b){
	return a+rand()%(b-a+1);
}
//碰撞检测
bool touch(int x1,int y1,int x2,int y2,int n1,int m1,int n2,int m2){
	//界面坐标系y值为从上到下递减
	if(x1-n1<0)
		if(y1-m1<0) return abs(x1-n1)<x2&&abs(y1-m1)<y2?1:0;
		else return abs(x1-n1)<x2&&abs(y1-m1)<m2?1:0;
	else
		if(y1-m1<0) return abs(x1-n1)<n2&&abs(y1-m1)<y2?1:0;
		else return abs(x1-n1)<n2&&abs(y1-m1)<m2?1:0;
	return true;
}
int main2(int best){
	ifstream inputfile("record.txt");
	inputfile>>best;
	inputfile.close();
	cleardevice();
	srand(time(NULL));
	int rad=gbr(10,550);
    int width = 600, height = 900;
    bool gameover=false;
    bool ingame=true;
    int sours=0;
	int speed=0;
	bool speedchange=false;
    initgraph(width, height); 
    setcolor(RED);
 	image background1("background.png",0,0);
 	image background2("background.png",600,0);
	image brid("brid.png",width-50,height/2-50);
    image pip1("pip1.png",width-100,-rad);
    image pip2("pip2.png",width-100,-rad+900);
 	char st[]="飞翔的小鸟";
	char starts[]="鼠标左键点击任意处开始";
	bool stoploop=true;
	int a[8];
	sours=0;
	ingame=true;
	cleardevice();
	delay_ms(30);
	gameover=false;
	rad=gbr(10,690);
    brid.setloct(width-50,height/2-50);
    //开始界面循环
	do{
		//背景循环
   	 	background1.changeloct(-2,0);
    	background2.changeloct(-2,0);
		background1.inloat(X,-600,600);
		background2.inloat(X,-600,600); 
		//鼠标事件
		if(keystate(key_mouse_l)!=0)
    	{
    		ingame=false;
		}		
		cleardevice();
		//图片输出
		background1.putimg();
		background2.putimg();
		brid.putimg(100,height/2-50);
		setfont(50,0,"宋体");
		ege_drawtext(st,150,100);
		setfont(25,0,"宋体");
		ege_drawtext(starts,130,500);
   		delay_ms(30);
   		setbkmode(TRANSPARENT);
	}while(ingame);
    for(;is_run()&&stoploop==true;delay_fps(60)){
		//水管,背景与鸟移动
		background1.changeloct(-2-speed,0);
   		background2.changeloct(-2-speed,0);
		brid.changeloct(0,2+speed);
		pip1.changeloct(-2-speed,0);
		pip2.changeloct(-2-speed,0);
		background1.inloat(X,-600,600);
		background2.inloat(X,-600,600); 
		if(pip1.islow(X,0)){
			speedchange=true;
			sours++;
			rad=gbr(10,550);
			pip1.setloct(width,-rad);
			pip2.setloct(width,-rad+900);
		}
    	if(keystate(key_mouse_l)!=0)
			brid.changeloct(0,-8-speed);
        //定义碰撞体
		a[0]=brid.img_x+3;
		a[1]=brid.img_y+12;
		a[2]=85;
		a[3]=49;
		a[4]=brid.img_x+19;
		a[5]=brid.img_y+61;
		a[6]=58;
		a[7]=15;
        //碰撞检测
		if(touch(a[0],a[1],a[2],a[3],pip1.img_x,pip1.img_y,pip1.img_width,pip1.img_height)||
			touch(a[0],a[1],a[2],a[3],pip2.img_x,pip2.img_y,pip2.img_width,pip2.img_height))
			gameover=true;
		if(touch(a[4],a[5],a[6],a[7],pip1.img_x,pip1.img_y,pip1.img_width,pip1.img_height)||
			touch(a[4],a[5],a[6],a[7],pip2.img_x,pip2.img_y,pip2.img_width,pip2.img_height))
			gameover=true;
		if(sours%6==5&&speedchange){//每5分提高一个等级速度
			speed++;
			speedchange=false;
		}
	    cleardevice();
		background1.putimg();//输出图片
		background2.putimg();
		pip1.putimg();
		pip2.putimg();
		brid.putimg();
	    setfont(30,0,"宋体");
	    xyprintf(10,10,"已通过障碍数：%d",sours);
	    setfont(20,0,"宋体");
		if(sours<best) xyprintf(10,45,"历史最高纪录：%d",best);
		else xyprintf(10,45,"历史最高纪录：%d",sours);
		if(kbhit()){
			setfont(50,0,"宋体");
		    outtextxy(width/3,height/3,"暂停中");
			getch();
			getch();
		}
		setfont(25,0,"宋体");
		outtextxy(width-200,5,"暂停/开始按空格");
	    if(gameover){//判断游戏失败
	    	xyprintf(width-150,100,"失败");
	    	xyprintf(width-150,130,"战绩：%d",sours);
	    	if(best<sours) {
				best=sours;
				ofstream myfile("record.txt");
				myfile<<best<<endl;
				myfile.close();
			}
			xyprintf(width-250,160,"历史最高战绩：%d",best);
	    	stoploop=false;
	    	delay_ms(1000);
		}
	}
    getch();
    return best;
}
#endif
