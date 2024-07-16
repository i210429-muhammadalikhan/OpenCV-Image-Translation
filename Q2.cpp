#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int** KMC(int** img, int wid, int height)
{
	int k1 = rand() % 60;
	int k2 = 180 + rand() % 75;
	//cout << k1 << "  " << k2 << endl;
	int k1Sum = 0;//to store centroid1 sum
	int k2Sum = 0;//to store centroid2 sum
	int diff1 = 0;//for difference
	int diff2 = 0;
	int counter1 = 0;//for counter
	int counter2 = 0;
	bool check = false;
	while (check == false)
	{
		//cout << "in loop" << endl;
		for (int i = 0; i < height; i++)//over the whole image
		{
			for (int j = 0; j < wid; j++)
			{
				//cout << img[i][j] << endl;
				diff1 = k1 - img[i][j];
				diff2 = k2 - img[i][j];//getting difference from centroids
				if (diff1 < 0)//multiplying by -1 if negative
				{
					diff1 *= -1;
				}
	
				if (diff2 < 0)
				{
					diff2 *= -1;
				}
				//cout << diff1 << "  " << diff2 << endl;
				if (diff1 < diff2)//assigning to closer one
				{
					k1Sum += img[i][j];
					counter1++;
				}
				if (diff2 < diff1)
				{
					k2Sum += img[i][j];
					counter2++;
				}
			}
		}
		k1Sum += k1;
		k2Sum += k2;
		counter1++;
		counter2++;
		int k1avg = k1Sum / counter1;//getting avg
		int k2avg = k2Sum / counter2; 
		//cout << "k1=" << k1 << " k2=" << k2 << " k1sum=" << k1Sum << " k2Sum=" << k2Sum << " c1=" << counter1 << " c2=" << counter2 <<" k1avg"<<k1avg <<" k2avg" << k2avg<<endl;
		if (k1 == k1avg && k2 == k2avg)//if equal to avg, exit the loop
		{
			check = true;
		}
		else//reset the variables
		{
			k1 = k1avg;
			k2 = k2avg;
			k1Sum = 0;
			k2Sum = 0;
			counter1 = 0;
			counter2 = 0;
		}
	}
	//cout << "k1" << k1 << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < wid; j++)
		{
			if (img[i][j] >= 0 && img[i][j] < k1)//as mentioned,
			{
				img[i][j] = 255;
			}
			else
			{
				img[i][j] = 0;
			}
		}
	}
	return img;
}


int main()
{
//keeping the same name of image in output folder for testing in q3
	string path = "Original Images/IMD018.bmp";
	string path1 = "KMC Output/IMD018.bmp";
	Mat image = imread(path);
	imshow("Before", image);
	int x = image.rows;
	int y = image.cols;
	int** arr = new int* [x];
	for (int i = 0; i < x; i++) {
		arr[i] = new int[y];
	}
	cout << "testing from main " << image.rows << "  " << image.cols << endl;
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			arr[i][j] = image.at<Vec3b>(i, j)[0];
		}
	}
	arr=KMC(arr, y, x);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			image.at<Vec3b>(i, j)[0] = arr[i][j];
			image.at<Vec3b>(i, j)[1] = arr[i][j];
			image.at<Vec3b>(i, j)[2] = arr[i][j];
		}
	}
	imshow("After", image);
	imwrite(path1, image);
	waitKey(0);
	return 0;
}
