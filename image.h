#ifndef IMAGE_H
#define IMAGE_H
#include<graphics.h>
using namespace ege;
enum isxy {X,Y};
class image{
    public:
    PIMAGE pim;
    int img_x;
    int img_y;
    int img_width;
    int img_height;
    image();
    image(LPCSTR imgfile);
    image(LPCSTR imgfile,int x,int y);
    void changeloct(int dx,int dy);
    void setloct(int x,int y);
    void putimg();
    void putimg(int x,int y);
    void inloat(isxy flag,int max=-1,int min=-1);
    bool islow(isxy flag,int max);
    ~image();
};
image::image(){}
image::image(LPCSTR imgfile){
    pim=newimage();
    getimage(pim,imgfile);
    img_width=getwidth(pim);
    img_height=getheight(pim);
}
image::image(LPCSTR imgfile,int x,int y){
    pim=newimage();
    getimage(pim,imgfile);
    img_x=x;
    img_y=y;
    img_width=getwidth(pim);
    img_height=getheight(pim);
}
void image::setloct(int x,int y){
    img_x=x;
    img_y=y;
}
void image::changeloct(int dx,int dy){
    img_x+=dx;
    img_y+=dy;
}
void image::putimg(){
    putimage_withalpha(NULL,pim,img_x,img_y);
}
void image::putimg(int x,int y){
    img_x=x;
    img_y=y;
    putimage_withalpha(NULL,pim,img_x,img_y);
}
void image::inloat(isxy flag,int min,int max){
    if(flag==X){
        if(img_x<=min)
    	    img_x=max;		
	}
    else{
	    if(img_y<=min)
	    	img_y=max;  	
	}
}
bool image::islow(isxy flag,int max){
    if(flag==X)
    return img_x<=max?true:false;
    else
    return img_y<=max?true:false;
}
image::~image(){
    if(pim!=NULL)
        delimage(pim);
}
#endif
