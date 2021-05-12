/*HEADER FILES USED IN PROGRAM*/
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>


using namespace cv;
using namespace std;

int main()
{
    /*VARIABLES USED IN PROGRAM*/
    int Angle;
    int ImageCenterY = 0;
    int ImageCenterX = 0;
    string RotatedImage = "Rotated Image";
    string OriginalImage="Original Image";
    int choice;


    /*LOADING IMAGE*/
    Mat imgOriginal=imread( "Me.JPG", 1 );
    if(imgOriginal.empty())
    {
        cout<<"Could not open or find image......";
        cin.get();
        return -1;
    }


    cout<<"INPUT ANGLE: ";
    cin>>Angle;
    while(true)
    {
        cout<<"\n\n";
        cout<<"1.CLOCKWISE.\n";
        cout<<"2.ANTICLOCKWISE.\n";
        cout<<"\n\n";
        cout<<"INPUT CHOICE: ";
        cin>>choice;
        if(choice==1||choice==2)
            break;
    }


    Angle=choice==1?-Angle:Angle;
    ImageCenterY = imgOriginal.rows / 2;
    ImageCenterX = imgOriginal.cols / 2;


    /*DISPLAYING ORIGNAL IMAGE */
    namedWindow(OriginalImage,WINDOW_AUTOSIZE);
    imshow(OriginalImage,imgOriginal);


    /*ROTATING IMAGE */
    namedWindow(RotatedImage,WINDOW_AUTOSIZE);
    Mat matRotation = getRotationMatrix2D(Point(ImageCenterX,ImageCenterY ),Angle,0.75);
    Mat imgRotated;
    warpAffine(imgOriginal,imgRotated,matRotation,imgOriginal.size(),INTER_LINEAR);


    /*DISPLAYING ROTATED IMAGE */
    imshow(RotatedImage,imgRotated);
    waitKey(0);


    /*DESTROYING WINDOWS*/
    destroyWindow(OriginalImage);
    destroyWindow(RotatedImage);


    cout<<"\n\n";
    cout<<"WANT TO SAVE IMAGE(y/n): ";
    char ch;
    cin>>ch;
    if(ch=='y'||ch=='Y')
        {
            /*SAVING IMAGE*/
            bool isSuccess = imwrite("MyImage.JPG",imgRotated);
            if(!isSuccess)
                {
                    cout << "Failed to save the image....." << endl;
                    cin.get(); //wait for a key press
                    return -1;
                }
            cout << "Image is succesfully saved to a file......" << endl;
        }
    return 0;
}
