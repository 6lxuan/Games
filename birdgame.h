#ifndef BIRDGAME_H
#define BIRDGAME_H
#include <iostream>
#include <fstream>  
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"image.h"
using namespace std;
//a��bΪ�������������
int gbr(int a,int b){
	return a+rand()%(b-a+1);
}
//��ײ���
bool touch(int x1,int y1,int x2,int y2,int n1,int m1,int n2,int m2){
	//��������ϵyֵΪ���ϵ��µݼ�
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
 	char st[]="�����С��";
	char starts[]="������������⴦��ʼ";
	bool stoploop=true;
	int a[8];
	sours=0;
	ingame=true;
	cleardevice();
	delay_ms(30);
	gameover=false;
	rad=gbr(10,690);
    brid.setloct(width-50,height/2-50);
    //��ʼ����ѭ��
	do{
		//����ѭ��
   	 	background1.changeloct(-2,0);
    	background2.changeloct(-2,0);
		background1.inloat(X,-600,600);
		background2.inloat(X,-600,600); 
		//����¼�
		if(keystate(key_mouse_l)!=0)
    	{
    		ingame=false;
		}		
		cleardevice();
		//ͼƬ���
		background1.putimg();
		background2.putimg();
		brid.putimg(100,height/2-50);
		setfont(50,0,"����");
		ege_drawtext(st,150,100);
		setfont(25,0,"����");
		ege_drawtext(starts,130,500);
   		delay_ms(30);
   		setbkmode(TRANSPARENT);
	}while(ingame);
    for(;is_run()&&stoploop==true;delay_fps(60)){
		//ˮ��,���������ƶ�
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
        //������ײ��
		a[0]=brid.img_x+3;
		a[1]=brid.img_y+12;
		a[2]=85;
		a[3]=49;
		a[4]=brid.img_x+19;
		a[5]=brid.img_y+61;
		a[6]=58;
		a[7]=15;
        //��ײ���
		if(touch(a[0],a[1],a[2],a[3],pip1.img_x,pip1.img_y,pip1.img_width,pip1.img_height)||
			touch(a[0],a[1],a[2],a[3],pip2.img_x,pip2.img_y,pip2.img_width,pip2.img_height))
			gameover=true;
		if(touch(a[4],a[5],a[6],a[7],pip1.img_x,pip1.img_y,pip1.img_width,pip1.img_height)||
			touch(a[4],a[5],a[6],a[7],pip2.img_x,pip2.img_y,pip2.img_width,pip2.img_height))
			gameover=true;
		if(sours%6==5&&speedchange){//ÿ5�����һ���ȼ��ٶ�
			speed++;
			speedchange=false;
		}
	    cleardevice();
		background1.putimg();//���ͼƬ
		background2.putimg();
		pip1.putimg();
		pip2.putimg();
		brid.putimg();
	    setfont(30,0,"����");
	    xyprintf(10,10,"��ͨ���ϰ�����%d",sours);
	    setfont(20,0,"����");
		if(sours<best) xyprintf(10,45,"��ʷ��߼�¼��%d",best);
		else xyprintf(10,45,"��ʷ��߼�¼��%d",sours);
		if(kbhit()){
			setfont(50,0,"����");
		    outtextxy(width/3,height/3,"��ͣ��");
			getch();
			getch();
		}
		setfont(25,0,"����");
		outtextxy(width-200,5,"��ͣ/��ʼ���ո�");
	    if(gameover){//�ж���Ϸʧ��
	    	xyprintf(width-150,100,"ʧ��");
	    	xyprintf(width-150,130,"ս����%d",sours);
	    	if(best<sours) {
				best=sours;
				ofstream myfile("record.txt");
				myfile<<best<<endl;
				myfile.close();
			}
			xyprintf(width-250,160,"��ʷ���ս����%d",best);
	    	stoploop=false;
	    	delay_ms(1000);
		}
	}
    getch();
    return best;
}
#endif
