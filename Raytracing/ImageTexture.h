#define STB_IMAGE_IMPLEMENTATION
#ifndef IMAGETEXTURE_H
#define IMAGETEXTURE_H
#include "Texture.h"
#include "stb_image.h"
class ImageTexture: public Texture{

public:

	ImageTexture(const char* filename){

		int width;
		int height;
		int channels =3;
		unsigned char* imageData = stbi_load(filename,&width,&height,&channels,channels); 
		if(imageData==nullptr){
		 std::cout<<"file cannot open"<<std::endl;
		}

		if(imageData!=nullptr){
			this->width = width;
			this->height = height;
			this->channels = channels;
			this->imageData = imageData;
		
		}

	
	}
	virtual Color getTexture(double s, double t, const Point3& point) override{
	
		double ss = s*(this->width-1);
		double tt = (1-t)*(this->height-1);

		int cols = int(ss);
		int rows = int(tt);
		int pos = rows*(this->width*this->channels) + cols*this->channels;
		unsigned char red = imageData[pos];
		unsigned char green = imageData[pos+1];
		unsigned char blue = imageData[pos+2];
		Color result = Color(double(red)/255.0f,double(green)/255.0,double(blue)/255.0);
		return result;
	}




public:

	int width;
	int height;
	int channels;
	unsigned char* imageData;


};



#endif