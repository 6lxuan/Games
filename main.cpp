#include <graphics.h>
#include <math.h>
#include"birdgame.h"
#include"nellgame.h"
int main()
{
    initgraph( 600, 900 );
    setcolor( RGB(0xff, 0xff, 0xff) );
    setfillcolor( RGB(0, 0, 0) );
    setcaption("小游戏合集");
	PIMAGE play=newimage();
	PIMAGE fyza=newimage();
	PIMAGE jfcz=newimage();
	PIMAGE youjiantou=newimage();
	PIMAGE zuojiantou=newimage();
	int best=0;
	
	lop:setbkcolor(RGB(50,50,50));
	setcolor(WHITE);
	setfont(20,0,"宋体");
	outtextxy(520,10,"Esc退出");
	setfont(50,0,"宋体");
	outtextxy(170,100,"小游戏选项");
	getimage(youjiantou,"向右.png");
	putimage_withalpha(NULL,youjiantou,500,400);
	getimage(play,"play.png");
	putimage_withalpha(NULL,play,125,750);
	getimage(jfcz,"见缝插针图标.png");  
	putimage_withalpha(NULL,jfcz,80,200);
	int key,k=0;

	loop:key=getch();
	switch(key){
		case 295:
		    cleardevice();
		    setcaption("小游戏合集");
		    setfont(20,0,"宋体");
		    outtextxy(520,10,"Esc退出");
		    setfont(50,0,"宋体");
		    outtextxy(170,100,"小游戏选项"); 
		    getimage(zuojiantou,"向左.png");
		    putimage_withalpha(NULL,zuojiantou,10,400);
		    putimage_withalpha(NULL,play,125,750);
		    getimage(fyza,"飞跃障碍图标.png");  
			putimage_withalpha(NULL,fyza,110,220);
			k=1;
			goto loop;
			break;
		case 293:
			cleardevice();
			goto lop;
			break;
		case 13:
			if(k==0) main1();
			if(k==1) best=main2(best);
			setfont(25,0,"宋体");
			outtextxy(300,240,"按下0回到主菜单");
			outtextxy(360,270," or ");
			outtextxy(290,300,"按下其他按键退出游戏");
			k=getch();
			if(k=='0') {
				cleardevice();
				goto lop;
			}
			else {
				cleardevice();
				closegraph();
				break;
			}
		case 27:
			cleardevice();
			closegraph();
			return 0;			
			break;
		default:
			setfont(25,0,"宋体");
			outtextxy(10,10,"输入无效！2秒后重输！");
			delay_ms(2000);
			cleardevice();
			goto lop;
			break;
	}
    return 0;
}
