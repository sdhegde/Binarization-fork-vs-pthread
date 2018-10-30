### Install dependent libraries
Download OpenCV and install to local path using cmake. Specify the local path with -DCMAKE_INSTALL_PREFIX
```
wget https://github.com/opencv/opencv/archive/3.4.3.zip
unzip opencv-3.4.3.zip
mkdir opencv-3.4.3/build && cd opencv-3.4.3/build
cmake3 -DCMAKE_BUILD_TYPE=RELEASE -DWITH_OPENMP=ON -DCMAKE_INSTALL_PREFIX=$HOME/local ..
make -j
make install
cd ../../ & rm -rf opencv-3.4.3
```
make sure OpenCV is intalled correctly, by checking the version
```
export PATH=$PATH:$HOME/local/bin
opencv_version
```

### Edit copy.sh and test.cpp
Edit the 2 files and set loop count to N <= number of processors.
* **Edit copy.sh:** Edit the for loop and set to N to make N copies of test_0.jpg in current directory.
```
./copy.sh
```
* **Edit test.cpp:** specify the  "loopCount" variable in main() to N (i.e. the number of copies you made with ./copy.sh)

### Compile test.cpp
For cmake to execute successfully, add "OpenCV_installation_path/share" to PATH, as in below
```
export PATH=$PATH:~/local/share
cmake3 .
make
./DisplayImage
```
