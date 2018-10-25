#include <iostream>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <opencv2/opencv.hpp>
#include <fstream>

#include <pthread.h>

using namespace cv;
using namespace std;

/* Common function passed to both forked code and pthread code.
 * This function reads the image from disk and converts it to black & white image. But the output black & white image is not stored to disk.
 * All statements within this function OpenCV library calls.
 *
 * Argument: jpeg filename
 */
void* iread(void* nam){
  Mat image, thr;
  
  image = imread( (char*)nam, CV_LOAD_IMAGE_GRAYSCALE );  // read image from disk, as grayscale
  threshold( image, thr, 100,255,THRESH_BINARY );	  // convert grayscale to black & white  
  
  //Free the memory
  image.release();
  thr.release();
  
  //cout<<pthread_self()<<" ran on CPU: "<<sched_getcpu()%64<<endl;  
}


int main() { 
  
  struct timespec i1, i2;
  long long elapsed;
  clock_gettime(CLOCK_MONOTONIC, &i1);
  
  char prefix[60]="./test_";   
  /*
   * Since each child should read a separate image, set loopCount variable to the number of copies made using copy.sh 
   * Make sure that loopCount <= number of available processors, so that there is no context switching
   */
  int loopCount = 50; 
  
  // Code using fork()  
  for(int i=0; i<loopCount; i++){	
	if(fork() == 0){
	  char filname[60];
	  sprintf(filname,"%s%d%s",prefix,i,".jpg");	 
	  iread(filname);
	  exit(0);
	}
  }    
  
  for(int i=0; i<loopCount; i++){	
    wait(NULL);	
  }
   
  
  
  // Code using Pthread
  /*pthread_t tid[loopCount];
  for (int i = 0; i < loopCount; i++) {
      char filname[60];      
      sprintf(filname,"%s%d%s",prefix,i,".jpg");      
      pthread_create(&tid[i], NULL, iread, (void*)filname);
  }
  
  for (int i = 0; i < loopCount; i++)
      pthread_join(tid[i], NULL);*/


  
  clock_gettime(CLOCK_MONOTONIC, &i2);
  elapsed = i2.tv_sec*1000000000LL + i2.tv_nsec - i1.tv_sec*1000000000LL - i1.tv_nsec;
  cout.precision(10);
  cout<<"Total : "<<(double)elapsed/1000000000LL<<endl;
  
  return 0;
}
