### Install dependent libraries
Download OpenCV and install to local path using cmake. Specify the local path with -DCMAKE_INSTALL_PREFIX
```
wget https://github.com/opencv/opencv/archive/3.4.3.zip
unzip 3.4.3.zip -d ./opencv-3.4.3
mkdir -p opencv-3.4.3/build && cd opencv-3.4.3/build
cmake3 -DCMAKE_BUILD_TYPE=RELEASE -DWITH_OPENMP=ON -DCMAKE_INSTALL_PREFIX=~/local ..
make -j
make install
cd ../../ & rm -rf opencv-3.4.3
```
make sure OpenCV is intalled correctly, by checking the version
```
export PATH=$PATH:~/local/bin
opencv_version
```

### Make multiple copies of test_0.jpg in current directory
Edit copy.sh: specify the "loop count" to number of copies you would want to make. Keep the loop count < number of available processors
```
./copy.sh
```

### Compile test.cpp
Edit test.cpp: specify the  "loopCount" variable in main() to the number of copies you made with ./copy.sh

Add "OpenCV_installation_path/share" to PATH
```
export PATH=$PATH:~/local/share
cmake3 .
make
./DisplayImage
```

