#ifndef OPEN_H
#define OPEN_H
	#include <stdio.h>
	#include <opencv2/opencv.hpp>
#endif
using namespace cv;

#include "util.hpp"

int display_image(String imagePath)
{
	Mat image;
	image = imread(imagePath, IMREAD_COLOR);
	if ( !image.data ) {
		printf("No image data \n");
		return -1;
	}
	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

int display_negative(String imagePath)
{
	int i, j;
	int aux;
	Mat image;
	Mat out;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		printf("display_negative: image empty\n");
		return -1;
	}

	out = negate(image);
	if (out.empty()) {
		printf("display_negative: out empty\n");
		return -1;
	}

	imshow("Image", image);
	imshow("Negative Image", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int add_value_to_grayscale_image(String imagePath, int value)
{
	int i, j;
	int aux;
	Mat image;
	Mat outImage;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (!image.data) {
		printf("add_value_to_grayscale_image: No image data\n");
		return -1;
	}

	outImage = Mat(image.rows, image.cols, CV_8UC1);

	for (i = 0; i < image.rows; i++) {
		for (j = 0; j < image.cols; j++) {
			aux = image.at<uchar>(i, j) + value;
			if (aux < 0) {
				outImage.at<uchar>(i, j) = 0;
			} else if (aux > 255) {
				outImage.at<uchar>(i, j) = 255;
			} else {
				outImage.at<uchar>(i, j) = aux;
			}
		}
	}
	imshow("Image", image);
	imshow("Final Image", outImage);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

int multiply_by_value_grayscale_image(String imagePath, float value)
{
	int i, j;
	float aux;
	Mat image;
	Mat outImage;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (!image.data) {
		printf("multiply_by_value_grayscale_image: No image data\n");
		return -1;
	}

	outImage = Mat(image.rows, image.cols, CV_8UC1);

	for (i = 0; i < image.rows; i++) {
		for (j = 0; j < image.cols; j++) {
			aux = (float)image.at<uchar>(i, j) * value;
			if (aux < 0) {
				outImage.at<uchar>(i, j) = 0;
			} else if (aux > 255) {
				outImage.at<uchar>(i, j) = 255;
			} else {
				outImage.at<uchar>(i, j) = (int)aux;
			}
		}
	}
	imshow("Image", image);
	imshow("Final Image", outImage);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void create_four_section_image()
{
	Mat image;
	int dim = 256;
	int i, j;
	Vec3b whitePixel, redPixel, greenPixel, yellowPixel;

	whitePixel[0] = 255;
	whitePixel[1] = 255;
	whitePixel[2] = 255;

	redPixel[0] = 0;
	redPixel[1] = 0;
	redPixel[2] = 255;

	greenPixel[0] = 0;
	greenPixel[1] = 255;
	greenPixel[2] = 0;

	yellowPixel[0] = 0;
	yellowPixel[1] = 255;
	yellowPixel[2] = 255;

	image = Mat(dim, dim, CV_8UC3);

	for (i = 0; i < dim/2; i++)
		for (j = 0; j < dim/2; j++)
			image.at<Vec3b>(i, j) = whitePixel;

	for (i = dim/2; i < dim; i++)
		for (j = 0; j < dim/2; j++)
			image.at<Vec3b>(i, j) = redPixel;

	for (i = 0; i < dim/2; i++)
		for (j = dim/2; j < dim; j++)
			image.at<Vec3b>(i, j) = greenPixel;

	for (i = dim/2; i < dim; i++)
		for (j = dim/2; j < dim; j++)
			image.at<Vec3b>(i, j) = yellowPixel;

	imshow("Image", image);
	waitKey(0);
	destroyAllWindows();
}

int extract_rgb_channels(String imagePath)
{
	int i, j;
	float aux;
	Mat image;
	Mat redImage, greenImage, blueImage;
	Vec3b pixel;

	image = imread(imagePath, IMREAD_COLOR);
	if (!image.data) {
		printf("extract_rgb_channels: No image data\n");
		return -1;
	}

	redImage = Mat(image.rows, image.cols, IMREAD_GRAYSCALE);
	greenImage = Mat(image.rows, image.cols, IMREAD_GRAYSCALE);
	blueImage = Mat(image.rows, image.cols, IMREAD_GRAYSCALE);

	for (i = 0; i < image.rows; i++) {
		for (j = 0; j < image.cols; j++) {
			pixel = image.at<Vec3b>(i, j);
			redImage.at<uchar>(i, j) = pixel[2];
			greenImage.at<uchar>(i, j) = pixel[1];
			blueImage.at<uchar>(i, j) = pixel[0];
		}
	}

	imshow("Image", image);
	imshow("Red Image", redImage);
	imshow("Green Image", greenImage);
	imshow("Blue Image", blueImage);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

int rgb_to_grayscale(String imagePath)
{
	int i, j;
	float aux;
	Mat image;
	Mat grayscaleImage;
	Vec3b pixel;

	image = imread(imagePath, IMREAD_COLOR);
	if (!image.data) {
		printf("rgb_to_grayscale: No image data\n");
		return -1;
	}

	grayscaleImage = Mat(image.rows, image.cols, IMREAD_GRAYSCALE);

	for (i = 0; i < image.rows; i++) {
		for (j = 0; j < image.cols; j++) {
			pixel = image.at<Vec3b>(i, j);
			grayscaleImage.at<uchar>(i, j) = (pixel[0] + pixel[1] + pixel[2]) / 3;
		}
	}

	imshow("Image", image);
	imshow("Grayscale Image", grayscaleImage);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

int display_grayscale_to_binary(String imagePath, int treshold)
{
	int i, j;
	Mat image;
	Mat binaryImage;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_grayscale_to_binary: image empty\n");
		return -1;
	}

	binaryImage = grayscale_to_binary(image, treshold);
	if (binaryImage.empty()) {
		perror("display_grayscale_to_binary: binaryImage empty\n");
		return -1;
	}

	imshow("Image", image);
	imshow("Binary Image", binaryImage);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_rgb_to_hsv(String imagePath)
{
	Mat image;
	Mat hue, saturation, value;

	image = imread(imagePath, IMREAD_COLOR);
	if (image.empty()) {
		perror("display_rgb_to_hsv: image empty\n");
		return -1;
	}

	hue = Mat(image.rows, image.cols, IMREAD_GRAYSCALE);
	saturation = Mat(image.rows, image.cols, IMREAD_GRAYSCALE);
	value = Mat(image.rows, image.cols, IMREAD_GRAYSCALE);

	rgb_to_hsv(image, hue, saturation, value);

	resize(image, image, Size(), 4, 4, INTER_NEAREST);
	resize(hue, hue, Size(), 4, 4, INTER_NEAREST);
	resize(saturation, saturation, Size(), 4, 4, INTER_NEAREST);
	resize(value, value, Size(), 4, 4, INTER_NEAREST);

	imshow("Image", image);
	imshow("Hue", hue);
	imshow("Saturation", saturation);
	imshow("Value", value);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_histogram(String imagePath)
{
	Mat image, histogramImage;
	int ret;
	int histogram[256];

	image = imread(imagePath, IMREAD_COLOR);
	if (image.empty()) {
		perror("display_histogram: image empty\n");
		return -1;
	}

	ret = compute_histogram(image, histogram);
	if (ret) {
		perror("display_histogram: Error in compute_histogram()\n");
		return -1;
	}

	histogramImage = create_histogram_image("Histogram", histogram, 256, 256);
	if (histogramImage.empty()) {
		perror("display_histogram: Error in create_histogram_image()\n");
		return -1;
	}

	imshow("Image", image);
	imshow("Histogram", histogramImage);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int print_histogram_bins(String imagePath, int numberBins)
{
	Mat image;
	int histogram[numberBins];
	int i;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (!image.data) {
		printf("print_histogram_bins: No image data\n");
		return -1;
	}

	compute_histogram_bins(image, histogram, numberBins);

	for (i = 0; i < numberBins; i++) {
		std::cout << histogram[i] << std::endl;
	}

	return 0;
}

int get_multilevel_tresholding_max(Mat image, int *numberMax, int *max,
				   int *valueMap, int windowHeight = 5,
				   float treshold = 0.0003)
{
	int ret;
	int histogram[256];
	float pdf[256];
	int i, j, k;
	float average;
	bool check;
	int count = 1;
	int maxValues[256];

	ret = compute_histogram(image, histogram, pdf);
	if (ret) {
		printf("get_multilevel_tresholding_max: Error in compute_histogram\n");
		return -1;
	}

	max[0] = 0;

	for (k = windowHeight; k < 256 - windowHeight; k++) {
		average = 0.0f;
		check = true;
		for (i = k - windowHeight; i < k + windowHeight; i++) {
			average += pdf[i];
			if (pdf[k] < pdf[i])
				check = false;
		}
		average = average / (2 * windowHeight + 1);
		if ((pdf[k] > average + treshold) && check) {
			max[count] = k;
			maxValues[count - 1] = (max[count - 1] + max[count]) / 2;
			count++;
		}
	}

	max[count] = 255;
	maxValues[count - 1] = (max[count - 1] + max[count]) / 2;
	maxValues[count] = 255;

	count++;
	*numberMax = count;

	k = 0;
	for (i = 0; i < count; i++) {
		for (j = k; j < maxValues[i]; j++) {
			valueMap[j] = max[i];
		}
		k = maxValues[i];
	}

	return 0;
}

int display_multilevel_tresholding(String imagePath, bool floydSteinbergDitheringOn = false)
{
	Mat image;
	Mat outImage;
	int ret;
	int numberMax;
	int max[256];
	int valueMap[256];
	int i, j;
	int oldPixel, newPixel;
	int error;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (!image.data) {
		printf("display_multilevel_tresholding: No image data\n");
		return -1;
	}

	ret = get_multilevel_tresholding_max(image, &numberMax, max, valueMap);
	if (ret) {
		printf("display_multilevel_tresholding: Error in get_multilevel_tresholding_max\n");
		return -1;
	}

	outImage = Mat(image.rows, image.cols, CV_8UC1);

	for (i = 0; i < image.rows; i++) {
		for (j = 0; j < image.cols; j++) {
			outImage.at<uchar>(i, j) = image.at<uchar>(i, j);
		}
	}

	for (i = 0; i < image.rows; i++) {
		for (j = 0; j < image.cols; j++) {
			oldPixel = outImage.at<uchar>(i, j);
			newPixel = valueMap[oldPixel];
			outImage.at<uchar>(i, j) = newPixel;
			if (floydSteinbergDitheringOn) {
				error = oldPixel - newPixel;
				if (i + 1 < image.rows)
					outImage.at<uchar>(i + 1, j) = outImage.at<uchar>(i + 1, j) + 7 * error / 16;
				if (i - 1 >= 0 && j + 1 < image.cols)
					outImage.at<uchar>(i - 1, j + 1) = outImage.at<uchar>(i - 1, j + 1) + 3 * error / 16;
				if (j + 1 < image.cols)
					outImage.at<uchar>(i, j + 1) = outImage.at<uchar>(i, j + 1) + 5 * error / 16;
				if (i + 1 < image.rows && j + 1 < image.cols)
					outImage.at<uchar>(i + 1, j + 1) = outImage.at<uchar>(i + 1, j + 1) + error / 16;
			}

		}
	}

	imshow("Multilevel Threshold", outImage);
	imshow("Image", image);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

int main(int argc, char **argv)
{
	int op;
	int ret = 0;
	String imagesPath;
	String imageName;
	String imagePath;
	char name[255];
	int val;
	float floatVal;
	char c;
	bool option;

	imagesPath = "src/images/";
	imageName = "lena.jpg";
	imagePath = imagesPath + imageName;

	do {
		op = 0;
		std::cout << "Operation = ";
		scanf("%d", &op);
		std::cout << "Selected operation " << op << std::endl;

		switch (op)
		{
		case 1:
			std::cout << "Image name = ";
			scanf("%s", name);
			std::cout << "Selected image name = " << name << std::endl;
			imageName = name;
			imagePath = imagesPath + imageName;
			std::cout << "Image path = " << imagePath << std::endl;
			break;
		case 2:
			std::cout << "Displaying image " << imageName << std::endl;
			ret = display_image(imagePath);
			if (ret)
				return -1;
			break;
		case 3:
			std::cout << "Negative image " << imageName << std::endl;
			ret = display_negative(imagePath);
			if (ret)
				return -1;
			break;
		case 4:
			std::cout << "Add value to the gray levels of image " << imageName << std::endl;
			std::cout << "Value = ";
			scanf("%d", &val);
			ret = add_value_to_grayscale_image(imagePath, val);
			if (ret)
				return -1;
			break;
		case 5:
			std::cout << "Multiply by value the gray levels of image " << imageName << std::endl;
			std::cout << "Value = ";
			scanf("%f", &floatVal);
			ret = multiply_by_value_grayscale_image(imagePath, floatVal);
			if (ret)
				return -1;
			break;
		case 6:
			std::cout << "Create image with four equal colored sections" << std::endl;
			create_four_section_image();
			break;
		case 7:
			std::cout << "Extract RGB channels from image " << imageName << std::endl;
			ret = extract_rgb_channels(imagePath);
			if (ret)
				return -1;
			break;
		case 8:
			std::cout << "RBG to grayscale " << imageName << std::endl;
			ret = rgb_to_grayscale(imagePath);
			if (ret)
				return -1;
			break;
		case 9:
			std::cout << "Grayscale to binary " << imageName << std::endl;
			std::cout << "Treshold = ";
			scanf("%d", &val);
			ret = display_grayscale_to_binary(imagePath, val);
			if (ret)
				return -1;
			break;
		case 10:
			std::cout << "RGB to HSV " << imageName << std::endl;
			ret = display_rgb_to_hsv(imagePath);
			if (ret)
				return -1;
			break;
		case 11:
			std::cout << "Histogram of " << imageName << std::endl;
			ret = display_histogram(imagePath);
			if (ret)
				return -1;
			break;
		case 12:
			std::cout << "Print histogram divided in bins " << imageName << std::endl;
			std::cout << "Number of bins = ";
			scanf("%d", &val);
			ret = print_histogram_bins(imagePath, val);
			if (ret)
				return -1;
			break;
		case 13:
			std::cout << "Multilevel tresholding " << imageName << std::endl;
			std::cout << "Use Floyd-Steinberg dithering? (y/n) ";
			scanf("\n%c", &c);
			printf("Chosen %c\n", c);
			option = false;
			if (c == 'y') {
				option = true;
			}
			ret = display_multilevel_tresholding(imagePath, option);
			if (ret)
				return -1;
			break;
		default:
			std::cout << "Unknown operation" << std::endl;
			break;
		}

		std::cout << std::endl;
	} while (op != 0);

	std::cout << "End" << std::endl;
	return 0;
}
