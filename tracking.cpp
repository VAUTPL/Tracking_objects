/*################################################
#     UNIVERSIDAD TECNICA PARTICULAR DE LOJA     #
##################################################
# Profesor:            				 #
# Rodrigo Barba	     	lrbarba@utpl.edu.ec      #
##################################################
# Estudiante:				         #
# Manuel Coronel     	mfcoronel2@utpl.edu.ec 	 #
# Patricio Jaramillo	pajaramillo2@utpl.edu.ec #
##################################################
# Tema: 				         #
# Detección y seguimiento de objetos mediante la #
# transformada de Houg				 #
#################################################*/


#include <opencv/cvaux.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <iostream>
int main(int argc, char* argv[])
{
	//variables para creacion de cuadros 
	int x1,y1,x2,y2,x3,y3,x4,y4;
	int long_lado; 
	int x,y;

    // Tamaño de captura por defecto - 640x480
    CvSize size = cvSize(640,480);
    // Open capture device. 0 is /dev/video0, 1 is /dev/video1, etc.
    CvCapture* capture = cvCaptureFromCAM(0);
    if( !capture )	
    {
            fprintf( stderr, "ERROR: No se reconoce el dispositivo \n" );
            getchar();
            return -1;
    }

    // Crear ventana donde se mostrara los resultados de las capturas
    cvNamedWindow( "Camera", CV_WINDOW_AUTOSIZE );
    //cvNamedWindow( "HSV", CV_WINDOW_AUTOSIZE ); //ventana hsv
    //cvNamedWindow( "EdgeDetection", CV_WINDOW_AUTOSIZE ); // ventana de deteccion de borde
    	// Detectar una pelota azul
    	CvScalar hsv_min_r = cvScalar(110, 150, 50, 0);
    	CvScalar hsv_max_r = cvScalar(130, 255, 255, 0);
	// Detectar una pelota amarilla
    	CvScalar hsv_min_a = cvScalar(20, 150, 100, 0);
    	CvScalar hsv_max_a = cvScalar(30, 255, 255, 0);
	//Detectar pelota verde 
	CvScalar hsv_min_v = cvScalar(50, 100, 100, 0);
    	CvScalar hsv_max_v = cvScalar(70, 255, 255, 0);

	//Inicializacion de los umbrales
    IplImage *  hsv_frame    = cvCreateImage(size, IPL_DEPTH_8U, 3);
    	IplImage*  thresholded_1   = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage*  thresholded_2   = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage*  thresholded_3   = cvCreateImage(size, IPL_DEPTH_8U, 1);
    while( 1 )
    {
        // Optener el marco
        IplImage* frame = cvQueryFrame( capture );
        if( !frame )
        {
                fprintf( stderr, "ERROR: marco esta vacio...\n" );
                getchar();
                break;
        }
	//Invertir la imagen
        cvFlip(frame, frame, 1);

        // Espacio de color encubierto a HSV ya que es mucho más fácil filtrar los colores en el espacio de color HSV.
        cvCvtColor(frame, hsv_frame, CV_BGR2HSV);
        // Filter out colors which are out of range.
        cvInRangeS(hsv_frame, hsv_min_r, hsv_max_r, thresholded_1);
	cvInRangeS(hsv_frame, hsv_min_a, hsv_max_a, thresholded_2);
	cvInRangeS(hsv_frame, hsv_min_v, hsv_max_v, thresholded_3);

        // Memory for hough circles
        CvMemStorage* storage = cvCreateMemStorage(0);
        // hough detector works better with some smoothing of the image
        cvSmooth( thresholded_1, thresholded_1, CV_GAUSSIAN, 9, 9 );
        CvSeq* circles_1 = cvHoughCircles(thresholded_1, storage, CV_HOUGH_GRADIENT, 2,
                                        thresholded_1->height/4, 100, 50, 5, 80);

	cvSmooth( thresholded_2, thresholded_2, CV_GAUSSIAN, 9, 9 );
        CvSeq* circles_2 = cvHoughCircles(thresholded_2, storage, CV_HOUGH_GRADIENT, 2,
                                        thresholded_2->height/4, 100, 50, 5, 80);

	cvSmooth( thresholded_3, thresholded_3, CV_GAUSSIAN, 9, 9 );
        CvSeq* circles_3 = cvHoughCircles(thresholded_3, storage, CV_HOUGH_GRADIENT, 2,
                                        thresholded_3->height/4, 100, 50, 5, 80);

	//IplImage* img1 =  cvLoadImage("/home/rodrigo/Escritorio/tracking/1.png"); 

	cvRectangle(frame, cvPoint(10,10), cvPoint(150, 150), cvScalar(0, 255, 0, 0), 1, 8, 0);
	cvRectangle(frame, cvPoint(10,320), cvPoint(160,470), cvScalar(0, 255, 0, 0), 1, 8, 0);
	cvRectangle(frame, cvPoint(480,10), cvPoint(630,160), cvScalar(0, 255, 0, 0), 1, 8, 0);
	cvRectangle(frame, cvPoint(480,320), cvPoint(630,470), cvScalar(0, 255, 0, 0), 1, 8, 0);

	//cuadrado 1 supeerior-izquierdo
  	x1=10,y1=10;
	//cuadrado 2 superior-derecho
  	x2=10,y2=320;
	//cuadrado 3 inferior-izquierdo
  	x3=480,y3=10;
	//cuadrado 4 inferior-derecho
  	x4=480,y4=320;
	//longitud del cuadrado
  	long_lado = 150; 

        for (int i = 0; i < circles_1->total; i++)
        {
            float* p = (float*)cvGetSeqElem( circles_1, i );
            printf("Ball blue! x=%f y=%f r=%f\n\r",p[0],p[1],p[2] );
            cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),
                                    3, CV_RGB(0,255,0), -1, 8, 0 );
            /*cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),
                                    cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );*/
 		x=p[0],y=p[1];
		if ( (x1<=x) && (x <=x1+long_lado) && (y1<=y) && (y<=y1+long_lado) ) {
			cvRectangle(frame, cvPoint(10,10), cvPoint(150, 150), cvScalar(255, 0, 0, 0), CV_FILLED);
		} 
		if ( (x2<=x) && (x <=x2+long_lado) && (y2<=y) && (y<=y2+long_lado) ) {
			cvRectangle(frame, cvPoint(10,320), cvPoint(160,470), cvScalar(255, 0, 0, 0), CV_FILLED);
		} 
		if ( (x3<=x) && (x <=x3+long_lado) && (y3<=y) && (y<=y3+long_lado) ) {
			cvRectangle(frame, cvPoint(480,10), cvPoint(630,160), cvScalar(255, 0, 0, 0), CV_FILLED);
		} 
		if ( (x4<=x) && (x <=x4+long_lado) && (y4<=y) && (y<=y4+long_lado) ) {
			cvRectangle(frame, cvPoint(480,320), cvPoint(630,470), cvScalar(255, 0, 0, 0), CV_FILLED);
		} 
        }
	for (int i = 0; i < circles_2->total; i++)
        {
            float* p = (float*)cvGetSeqElem( circles_2, i );
            printf("Ball yellow! x=%f y=%f r=%f\n\r",p[0],p[1],p[2] );
            cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),
                                    3, CV_RGB(0,255,0), -1, 8, 0 );
            /*cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),
                                    cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );*/
		x=p[0],y=p[1];
		if ( (x1<=x) && (x <=x1+long_lado) && (y1<=y) && (y<=y1+long_lado) ) {
			cvRectangle(frame, cvPoint(10,10), cvPoint(150, 150), cvScalar(0, 255, 255, 0), CV_FILLED);
		} 
		if ( (x2<=x) && (x <=x2+long_lado) && (y2<=y) && (y<=y2+long_lado) ) {
			cvRectangle(frame, cvPoint(10,320), cvPoint(160,470), cvScalar(0, 255, 255, 0), CV_FILLED);
		} 
		if ( (x3<=x) && (x <=x3+long_lado) && (y3<=y) && (y<=y3+long_lado) ) {
			cvRectangle(frame, cvPoint(480,10), cvPoint(630,160), cvScalar(0, 255, 255, 0), CV_FILLED);
		} 
		if ( (x4<=x) && (x <=x4+long_lado) && (y4<=y) && (y<=y4+long_lado) ) {
			cvRectangle(frame, cvPoint(480,320), cvPoint(630,470), cvScalar(0, 255, 255, 0), CV_FILLED);
		} 
        }
	for (int i = 0; i < circles_3->total; i++)
        {
            float* p = (float*)cvGetSeqElem( circles_3, i );
            printf("Ball green! x=%f y=%f r=%f\n\r",p[0],p[1],p[2] );
            cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),
                                    3, CV_RGB(0,255,0), -1, 8, 0 );
            /*cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),
                                    cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );*/
		x=p[0],y=p[1];
		if ( (x1<=x) && (x <=x1+long_lado) && (y1<=y) && (y<=y1+long_lado) ) {
			cvRectangle(frame, cvPoint(10,10), cvPoint(150, 150), cvScalar(0, 255, 0, 0), CV_FILLED);
		} 
		if ( (x2<=x) && (x <=x2+long_lado) && (y2<=y) && (y<=y2+long_lado) ) {
			cvRectangle(frame, cvPoint(10,320), cvPoint(160,470), cvScalar(0, 255, 0, 0), CV_FILLED);
		} 
		if ( (x3<=x) && (x <=x3+long_lado) && (y3<=y) && (y<=y3+long_lado) ) {
			cvRectangle(frame, cvPoint(480,10), cvPoint(630,160), cvScalar(0, 255, 0, 0), CV_FILLED);
		} 
		if ( (x4<=x) && (x <=x4+long_lado) && (y4<=y) && (y<=y4+long_lado) ) {
			cvRectangle(frame, cvPoint(480,320), cvPoint(630,470), cvScalar(0, 255, 0, 0), CV_FILLED);
		} 
        }
	
        cvShowImage( "Camera", frame ); // Flujo original con superposición de bola detectada
        //cvShowImage( "HSV", hsv_frame); // Original stream in the HSV color space
        //cvShowImage( "EdgeDetection", thresholded_1 ); // The stream after color filtering
        cvReleaseMemStorage(&storage);
        // Do not release the frame!
        //If ESC key pressed, Key=0x10001B under OpenCV 0.9.7(linux version),
        //remove higher bits using AND operator
        if( (cvWaitKey(10) & 255) == 27 ) break;
    }
     // Release the capture device housekeeping
     cvReleaseCapture( &capture );
     cvDestroyWindow( "mywindow" );
     return 0;
   }
