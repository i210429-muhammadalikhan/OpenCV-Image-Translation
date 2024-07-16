#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
struct RLCNode {
	int data;
	struct RLCNode* next;
};
struct RLCNode* list = NULL;
void insertData(int num)//inserting data in the list
{
	RLCNode* temp = new RLCNode();
	RLCNode* last = list;
	temp->data = num;
	temp->next = NULL;
	if (list == NULL)
	{
		list = temp;
		return;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = temp;
}
void display() {//display function to show the output
	struct RLCNode* ptr;
	ptr = list;
	cout << ptr->data << " ";
	ptr = ptr->next;
	cout << ptr->data << " "<<endl;
	ptr = ptr->next;
	while (ptr != NULL) {
		cout << ptr->data << " ";
		if (ptr->data==-1)
			cout << endl;
		ptr = ptr->next;
	}
}
void RLC(int** img, int wid, int height)
{
	insertData(wid);
	insertData(height);
	for (int i = 0; i < height; i++)//iterating over the rows
	{
		for(int j=0;j<wid;j++)//iterating over the columns
		{
			if (img[i][j] != 0)//if any pixel is non zero
			{
				bool flag = false;
				insertData(j);//inserting the starting point of area in list
				while (img[i][j] != 0)//continue until zero pixel come up
				{
					flag = true;
					j++;
				}
				if (flag == true)
					insertData(j - 1);//inserting the end point if there are more non zero pixel
				else
					insertData(j);//inserting the exaact pixel if there is only one non zero pixel
			}
		}
		insertData(-1);//inserting row break;
	}
}


int main()
{
	string path = "Segmented Outputs/mIMD171.bmp";
	Mat image = imread(path);
	//imshow("Before", image);
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
	RLC(arr, y, x);
	display();
	waitKey(0);
	return 0;
}
