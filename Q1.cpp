#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int** connectedComponents(int** img,int H, int W)
{
	int label = 1;
	int height = H;
	int width = W;
	int** labelTable = new int* [H];
	for (int i = 0; i < height; i++)
	{
		labelTable[i] = new int[W];
	}
	for (int i = 0; i < height; i++)//creating a 2d array to store the lables
	{
		for (int j = 0; j < width; j++)
		{
			labelTable[i][j] = 0;
		}
	}
	for (int i = 0; i < height; i++)//moving over 2d array
	{
		for (int j = 0; j < width; j++)
		{
			if (img[i][j] == 0)//if pixel is 0, no need to play with it
			{
				continue;
			}
			int left = 0;//variables for left box
			int up = 0;//variable for upper box
			if (j > 0)
			{
				left = labelTable[i][j - 1];//getting labels fro table
			}
			if (i > 0)
			{
				up = labelTable[i-1][j];//getting label from table
			}
			if (left == 0 && up == 0)//if both are zero, then assign a new label
			{
				labelTable[i][j] = label;
				label++;
			}
			else if (left != 0 && up != 0)//if both are not zero
			{
				labelTable[i][j] = min(left, up);//assign the minimum of the two
				if (left != up)//they are not equal so, replace max label with minimum label
				{
					for (int k = 0; k < height; k++)
					{
						for (int l = 0; l < width; l++)
						{
							if (labelTable[k][l] == max(left, up))
							{
								labelTable[k][l] = min(left, up);
							}
						}
					}
				}
			}
			else
			{
				labelTable[i][j] = max(left, up);//else continue to assign the max label
			}
		}
	}
		//check most occured number in 2d array
		int* count = new int[label];
		for (int i = 0; i < label; i++)
		{
			count[i] = 0;
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (labelTable[i][j] != 0)
				{
					count[labelTable[i][j]]++;
				}
			}
		}
		int max = 0;
		int maxIndex = 0;
		for (int i = 0; i < label; i++)
		{
			if (count[i] > max)
			{
				max = count[i];
				maxIndex = i;
			}
		}
		//cout << "Most occured number is " << maxIndex << " with " << max << " times" << endl;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (labelTable[i][j] != maxIndex)//assigning 0 if label is not from big region
				{
					labelTable[i][j] = 0;
				}
				else
					labelTable[i][j] = 255;
			}
		}
		cout << endl;
		return labelTable;
}


int main()
{
	//keeping the same name of image in output folder for testing in q3
	string path = "Segmented Outputs/mIMD018.bmp";
	string path1 = "CC Output/mIMD018.bmp";
	Mat image = imread(path);
	imshow("Before", image);
	int x = image.rows;
	int y = image.cols;
	int** arr = new int* [x];
	for (int i = 0; i < x; i++) {
		arr[i] = new int[y];
	}
	cout << "testing from main" << image.rows << "  " << image.cols << endl;
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			arr[i][j] = image.at<Vec3b>(i, j)[0];
		}
	}
	arr=connectedComponents(arr, x, y);
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
