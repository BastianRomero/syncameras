#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

#include <iostream>
#include <stdio.h>
#include <thread>
#include <omp.h>

#include <windows.h>
#include <map>


using namespace cv;
using namespace std;


void cam_fps(VideoCapture frame, int fps);

int main(int argc, char** argv)
{
	/*cout << "Librerias cargadas con exito" << endl;
	
	//String nombreImagen("uiharu.jpg");
	String nombreImagen("eso1532a.tif");
	String gris("Imagen gris");
	//if (argc > 1) { nombreImagen = argv[1]; }

	cout<< "Mostrando: " << nombreImagen << endl;

	Mat image;
	Mat imagenGris;
	Mat matrizCeros = Mat::zeros(10, 10, CV_8UC1);

	image = imread(samples::findFile(nombreImagen), IMREAD_COLOR);
	cvtColor(image,imagenGris, COLOR_BGR2GRAY);

	cout << "Guardando imagen en blanco y negro" << endl;
	imwrite("imagen_gris.tif", imagenGris);
	imwrite("prueba.jpg", matrizCeros);
	if(image.empty())
	{
		cout << "No se puede abrir la imagen" << endl;
		return -1;
	}

	namedWindow(nombreImagen, WINDOW_KEEPRATIO);
	namedWindow(gris, WINDOW_KEEPRATIO);
	imshow(nombreImagen, image);
	imshow(gris, imagenGris);

	cout << "Imagen Cargada con exito" << endl << "Presione una tecla para terminar" << endl;
	waitKey(0);

	cout << "Programa terminado" << endl;*/

	printf("iniciando ");
	for (int i = 0; i < 4; i++)
	{
		printf(".");
	}

	VideoCapture cap(0); 
	
	thread cam_fps(cap, 60);

	return 0;
}

void cam_fps(VideoCapture cap, int fps) {


	Mat frame;
	unsigned short time_fps = 1000 / fps;
	printf("Se muestran %d FPS \n", fps);
	printf("Cada uno dura %d [ms]", time_fps);

	while(true){
		
		cap >> frame;
		imwrite("imagen_1.jpg", frame);
		Mat muestra = imread("imagen_1.jpg");
		imshow("60 FPS", muestra);
		waitKey(time_fps);
		
	}
}
