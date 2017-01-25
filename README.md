# Tracking objects
Detection and tracking of objects using the Hough transform

# UTPL

#Professor:
    Rodrigo Barba 		lrbarba@utpl.edu.ec

#Students:

    Patricio Jaramillo	pajaramillo2@utpl.edu.ec 
    Manuel Coronel     	mfcoronel2@utpl.edu.ec 

### System Requirements

* 2 GB or more RAM 
* Windows 7 or later (has only been tested on 10), OS X 10.8 or later, Linux 3.0+

# Installation - Ubuntu

Ejecutar el archivo "instalar_opencv.sh" o instalacion manual con los pasos a continuación.

### KEEP UBUNTU OR DEBIAN UP TO DATE

sudo apt-get -y update
sudo apt-get -y upgrade
sudo apt-get -y dist-upgrade
sudo apt-get -y autoremove


### INSTALL THE DEPENDENCIES

### Build tools:
sudo apt-get install -y build-essential cmake

### GUI:
sudo apt-get install -y qt5-default libvtk6-dev

### Media I/O:
sudo apt-get install -y zlib1g-dev libjpeg-dev libwebp-dev libpng-dev libtiff5-dev libjasper-dev libopenexr-dev libgdal-dev

### Video I/O:
sudo apt-get install -y libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev yasm libopencore-amrnb-dev libopencore-amrwb-dev libv4l-dev libxine2-dev

### Parallelism and linear algebra libraries:
sudo apt-get install -y libtbb-dev libeigen3-dev

### Python:
sudo apt-get install -y python-dev python-tk python-numpy python3-dev python3-tk python3-numpy

### Java:
sudo apt-get install -y ant default-jdk

### Documentation:
sudo apt-get install -y doxygen


### INSTALL THE LIBRARY (YOU CAN CHANGE '3.0.0' FOR THE LAST STABLE VERSION)

sudo apt-get install -y unzip wget
wget https://github.com/Itseez/opencv/archive/3.0.0.zip
unzip 3.0.0.zip
rm 3.0.0.zip
mv opencv-3.0.0 OpenCV
cd OpenCV
mkdir build
cd build
cmake -DWITH_QT=ON -DWITH_OPENGL=ON -DFORCE_VTK=ON -DWITH_TBB=ON -DWITH_GDAL=ON -DWITH_XINE=ON -DBUILD_EXAMPLES=ON ..
make -j4
sudo make install
sudo ldconfig


## Compilar archivos:
### Primera forma
       g++ -o my_example my_example.cpp `pkg-config opencv --cflags --libs`

### Segunda forma
Agregar el alias en .bashrc o .bash_aliases 

        $ alias opencv="~/.compile_opencv.sh"

opencv es un alinas para compilar archivos c o cpp, para ejecutar se usa el siguiente comando:

        $ opencv <nombre del archivo.cpp> 
        
ejemplo: 

        $ opencv opencvtest.c

para ejecutar se usa:

        $ ./opencvtest


