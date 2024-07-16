#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void DiceCoefficientCC(int** Truth, int** output,int wid,int height)
{
	float TP = 0, FP = 0, FN = 0;
	for (int i = 0; i < height; i++)//iterating over images
	{
		for (int j = 0; j < wid; j++)
		{
			if (Truth[i][j] == output[i][j] && Truth[i][j] == 255)//for true positive
			{
				TP++;
			}
			if (output[i][j] == 255 && Truth[i][j] == 0)//for false positive
			{
				FP++;
			}
			if (output[i][j] == 0 && Truth[i][j] == 255)//for false negative
			{
				FN++;
			}
		}
	}
	cout << "Connected Components\nTP: " << TP << " FP: " << FP << " FN: " << FN << endl;
	float Dice = (2 * TP) / (FN + (2 * TP) + FP);
	cout << "Dice coefficient for Connected Components: " << Dice << endl<<endl;
}
void DiceCoefficientKMC(int** Truth, int** output, int wid, int height)
{
	float TP = 0, FP = 0, FN = 0;
	for (int i = 0; i < height; i++)//iterating over images
	{
		for (int j = 0; j < wid; j++)
		{
			if (Truth[i][j] == output[i][j] && Truth[i][j] == 255)//for true positive values
			{
				TP++;
			}
			if (output[i][j] == 255 && Truth[i][j] == 0)//for false positive values
			{
				FP++;
			}
			if (output[i][j] == 0 && Truth[i][j] == 255)//for false negative values
			{
				FN++;
			}
		}
	}
	cout << "K Means Clustering\nTP: " << TP << " FP: " << FP << " FN: " << FN << endl;
	float Dice = (2 * TP) / (FN + (2 * TP) + FP);
	cout << "Dice coefficient for K Means Clustering: " << Dice << endl;
}
int main()
{
	//testing outputs from folder
	string path = "Ground Truths/IMD018_lesion.bmp";//getting ground truth
	string pathCC = "CC Output/mIMD018.bmp";//getting connected component output
	string pathKMC = "KMC Output/IMD018.bmp";//getting KMC output
	Mat image = imread(path);
	Mat imageCC = imread(pathCC);
	Mat imageKMC = imread(pathKMC);
	imshow("Image", image);
	imshow("Image CC", imageCC);
	imshow("Image KMC", imageKMC);
	int x = image.rows;
	int y = image.cols;
	int** arr = new int* [x];//creating array for truth
	for (int i = 0; i < x; i++) {
		arr[i] = new int[y];
	}
	int** arrCC = new int* [imageCC.rows];//for CC
	for (int i = 0; i < x; i++) {
		arrCC[i] = new int[imageCC.cols];
	}
	int** arrKMC = new int* [imageKMC.rows];//for KMC
	for (int i = 0; i < x; i++) {
		arrKMC[i] = new int[imageKMC.cols];
	}
	cout << "testing from main" << image.rows << "  " << image.cols << endl;
	for (int i = 0; i < image.rows; i++)//reading images
	{
		for (int j = 0; j < image.cols; j++)
		{
			arr[i][j] = image.at<Vec3b>(i, j)[0];
		}
	}
	for (int i = 0; i < imageCC.rows; i++)
	{
		for (int j = 0; j < imageCC.cols; j++)
		{
			arrCC[i][j] = imageCC.at<Vec3b>(i, j)[0];
		}
	}
	for (int i = 0; i < imageKMC.rows; i++)
	{
		for (int j = 0; j < imageKMC.cols; j++)
		{
			arrKMC[i][j] = imageKMC.at<Vec3b>(i, j)[0];
		}
	}
	DiceCoefficientCC(arr, arrCC, y, x);//for CC
	DiceCoefficientKMC(arr, arrKMC, y, x);//for KMC
	waitKey(0);
	return 0;
}