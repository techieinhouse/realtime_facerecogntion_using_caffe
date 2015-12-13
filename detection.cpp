#include "defs.h"
#include "detection.h"
using namespace std;
using namespace cv;
/*to get coordinates to display text*/
int  pos_x,pos_y;
/*counter activated whenever face is detected*/
static bool counter=false;
Mat img2,face_img,img1;
 /* used to avoid overwriting of images*/
   int static z=0;
 static  Scalar color=CV_RGB(0,0,255);

            
void detection::detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade
                     )
{ img2 =img;
   
    vector<Rect> faces;
   
    Mat gray, smallImg( cvRound (img2.rows), cvRound(img2.cols), CV_32FC3 );

    cvtColor( img2, gray, CV_BGR2GRAY );
    resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );

   
    cascade.detectMultiScale( smallImg, faces,
        1.1, 2, 0
        //|CV_HAAR_FIND_BIGGEST_OBJECT
        //|CV_HAAR_DO_ROUGH_SEARCH
        |CV_HAAR_SCALE_IMAGE
        ,
        Size(100,100) );
    
   
    
    
    for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++ )
    {

         rectangle( img2, cvPoint(cvRound(r->x), cvRound(r->y)),
                       cvPoint(cvRound((r->x + r->width-1)), cvRound((r->y + r->height-1))),
                     color, 3, 8, 0);
          int edge_size = max(r->width, r->height);
          Rect square(r->x, r->y, edge_size-20, edge_size-10);
            face_img = (img2)(square);

          
            pos_x = r->x;
             pos_y = r->y;
             resize(face_img,face_img,Size(256,256));
           
                img=face_img;
              
                counter=true;
            
    }
      
}
void detection::display(string gen,string pred,Scalar color)
{ // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   
 char* s= ctime(&now);
   
 string dt(s, 24);
 

     if(!img2.empty()){
       
            string box_text = format("Name = %s %s",pred.c_str(),gen.c_str());
            // Calculate the position for annotated text (make sure we don't
            // put illegal values in there):
            
            // And now put it into the image:
            
         flip(img2,img2, 1); 
         
           putText(img2, dt.c_str(),Point( 280,450), FONT_HERSHEY_PLAIN, 2.0, CV_RGB(255,128,0), 2.0);
             
         
         
       
        if(counter){
            putText(img2, box_text, Point((-pos_x)+350, pos_y-10), FONT_HERSHEY_PLAIN, 2.0, color, 2.0);
            if(pred=="unknown"){
               string face_path = format("%s/%s%d.bmp", "Recognized/", pred.c_str(),z);
                imwrite(face_path,img2);
                          }
            else{
            string face_path = format("%s/%s.bmp", "Recognized/", pred.c_str());
            imwrite(face_path,img2);
              } 
         counter=false;
        
          }
        else{
            putText(img2, "hello,anybody there", Point(100, 100), FONT_HERSHEY_PLAIN,3.0, CV_RGB(255,0,0), 2.0); 
            
            z++;
         }
          putText(img2, "press esc to quit",Point( 180,25), FONT_HERSHEY_PLAIN, 1.5, CV_RGB(255,0,102), 0.8);
          cv::imshow( "Recognition", img2 );
     
          
     }
}
