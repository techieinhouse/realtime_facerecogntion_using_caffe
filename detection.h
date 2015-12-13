#include "defs.h"

using namespace std;
using namespace cv;

class detection {
public:
    
    void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade);
void display(string g,string s,Scalar color);
};


