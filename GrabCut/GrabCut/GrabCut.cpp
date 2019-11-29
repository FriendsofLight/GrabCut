/*Code nay ban dau lay tu duong link https://blog.csdn.net/qq_24946843/article/details/82827168
Sau do Viet hoa va sua chua mot so tham so de ra ban code cuoi cung nay
Nguoi Viet hoa: Thi giac may tinh
*/

/*         --- HUONG DAN ---
Sau khi chuong trinh khoi chay va hien thi anh tren cua so "input" ->
Dung chuot trai chon 1 vung anh chua muc tieu (ROI)
An phim "g" tren ban phim de tach boi canh.
*/
#include<opencv2\opencv.hpp>
using namespace cv;
void onMouse(int event, int x, int y, int flags, void* userdata);
Rect rect;
Mat src, roiImg, result;
void showImg();
int main(int arc, char** argv) {
	src = imread("3.jpg");
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	setMouseCallback("input", onMouse);
	//Dinh nghia output£¬Ket qua la£ºGC_BGD =0 (Boi canh) ,
	//GC_FGD =1 (muc tieu),GC_PR_BGD = 2 (kha nang la boi canh), GC_PR_FGD = 3 (kha nang la muc tieu)		
	Mat result = Mat::zeros(src.size(), CV_8UC1);
	// GrabCut 
	//Dinh nghia 2 bien ma tran tam thoi£¬lam bien trung gian 
	Mat bgModel, fgModel;
	char c = waitKey(0);
	if (c == 'g') {
		grabCut(src, result, rect, bgModel, fgModel, 1, GC_INIT_WITH_RECT);
		//So sanh cac kha nang nhan gia tri cua result de quyet dinh gia tri cuoi cung cua result
		compare(result, GC_PR_FGD, result, CMP_EQ);
		// Tao ra anh output
		Mat foreground(src.size(), CV_8UC3, Scalar(255, 255, 255));
		//Copy khu result (ROI) trong src vao foreground
		src.copyTo(foreground, result);
		imshow("output", foreground);
	}
	waitKey(0);
	return 0;
}


void showImg() {
	src.copyTo(roiImg);
	rectangle(roiImg, rect, Scalar(0, 0, 255), 2);
	imshow("input", roiImg);
}
//Dung chuot lua chon ROI
void onMouse(int event, int x, int y, int flags, void* userdata) {
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:// chuot trai an xuong
		rect.x = x;
		rect.y = y;
		rect.width = 1;
		rect.height = 1;
		break;
	case CV_EVENT_MOUSEMOVE:// Di chuyen chuot trai
		if (flags && CV_EVENT_FLAG_LBUTTON) {
			rect = Rect(Point(rect.x, rect.y), Point(x, y));
			showImg();
		}
		break;
	case EVENT_LBUTTONUP:// Chuot trai nha len
		if (rect.width > 1 && rect.height > 1) {
			showImg();
		}
		break;
	default:
		break;
	}
}