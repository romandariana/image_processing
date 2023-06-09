#ifndef OPEN_H
#define OPEN_H
	#include <stdio.h>
	#include <opencv2/opencv.hpp>
#endif

#include <fstream>

#include "border.hpp"
#include "filter.hpp"
#include "label.hpp"
#include "morph.hpp"
#include "morphology.hpp"
#include "object.hpp"
#include "util.hpp"

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

void callback(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
		std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
	else if (event == EVENT_RBUTTONDOWN)
		std::cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
	else if (event == EVENT_MBUTTONDOWN)
		std::cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
	else if (event == EVENT_MOUSEMOVE)
		std::cout << "Mouse move over the window - position (" << x << ", " << y << ")" << std::endl;
}

int mouse_callback(String imagePath)
{
	Mat image;

	image = imread(imagePath, IMREAD_COLOR);

	if (image.empty()) {
		perror("mouse_callback: image is empty\n");
		return -1;
	}

	namedWindow("Image", 1);
	setMouseCallback("Image", callback, NULL);

	imshow("Image", image);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_breadth_first_traversal_labeling(String imagePath)
{
	Mat image, out;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_breadth_first_traversal_labeling: image is empty\n");
		return -1;
	}

	out = breadth_first_traversal_labeling(image);
	if (out.empty()) {
		perror("display_breadth_first_traversal_labeling: out is empty\n");
		return -1;
	}

	imshow("Image", image);
	imshow("Breadth First Traversal Labeling", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_two_pass_labeling(String imagePath)
{
	Mat image, out;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_two_pass_labeling: image is empty\n");
		return -1;
	}

	out = two_pass_labeling(image);
	if (out.empty()) {
		perror("display_two_pass_labeling: out is empty\n");
		return -1;
	}

	imshow("Image", image);
	imshow("Two-pass Traversal Labeling", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_border_of_single_object(String imagePath)
{
	Mat image, out;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty())
	{
		perror("display_border_of_single_object: image is empty\n");
		return -1;
	}

	out = border_of_single_object(image, NULL);
	if (out.empty())
	{
		perror("display_border_of_single_object: out is empty\n");
		return -1;
	}

	resize(image, image, Size(8 * image.cols, 8 * image.rows), 0, 0, INTER_NEAREST);
	resize(out, out, Size(8 * out.cols, 8 * out.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	imshow("Border", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_chain_code_single_object(String imagePath)
{
	Mat image, out;
	std::vector<int> chainCode;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty())
	{
		perror("display_chain_code_single_object: image is empty\n");
		return -1;
	}

	out = border_of_single_object(image, &chainCode);
	if (out.empty())
	{
		perror("display_chain_code_single_object: out is empty\n");
		return -1;
	}

	std::cout << "Chain Code: " << std::endl;
	for (int elem : chainCode)
		std::cout << elem << " ";
	std::cout << std::endl;

	resize(image, image, Size(8 * image.cols, 8 * image.rows), 0, 0, INTER_NEAREST);
	resize(out, out, Size(8 * out.cols, 8 * out.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	imshow("Border", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_object_reconstruction_from_chain_code(String inputPath)
{
	Mat image;
	int i, val;
	int startRow, startCol;
	int borderLength;
	std::vector<int> chainCode;
	std::ifstream inputFile(inputPath);

	image = imread("src/images/files_border_tracing/gray_background.bmp", IMREAD_GRAYSCALE);
	if (image.empty())
	{
		perror("display_object_reconstruction_from_chain_code: image is empty\n");
		return -1;
	}

	if (inputFile >> startRow >> startCol >> borderLength)
	{
		std::cout << "Start Row: " << startRow << std::endl;
		std::cout << "Start Col: " << startCol << std::endl;
		std::cout << "Border Length: " << borderLength << std::endl;
	}
	else
	{
		perror("display_object_reconstruction_from_chain_code: error reading input file\n");
		return -1;
	}

	for (i = 0; i < borderLength; i++)
	{
		if (inputFile >> val)
			chainCode.push_back(val);
		else
		{
			perror("display_object_reconstruction_from_chain_code: error reading input file\n");
			return -1;
		}
	}

	image = object_reconstruction_from_chain_code(image, chainCode, startRow, startCol);

	resize(image, image, Size(2 * image.cols, 2 * image.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_dilate_n_times(String imagePath, int n)
{
	int i;
	Mat image;
	Mat out;
	Mat structuringElement;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_dilate_n_times: image is empty\n");
		return -1;
	}

	out = image.clone();
	structuringElement = Mat::ones(3, 3, CV_8UC1);

	for (i = 0; i < n; i++)
		out = dilate(out, structuringElement);

	resize(image, image, Size(8 * image.cols, 8 * image.rows), 0, 0, INTER_NEAREST);
	resize(out, out, Size(8 * out.cols, 8 * out.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	imshow("Dilated", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_erode_n_times(String imagePath, int n)
{
	int i;
	Mat image;
	Mat out;
	Mat structuringElement;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_erode_n_times: image is empty\n");
		return -1;
	}

	out = image.clone();
	structuringElement = Mat::ones(3, 3, CV_8UC1);

	for (i = 0; i < n; i++)
		out = erode(out, structuringElement);

	resize(image, image, Size(4 * image.cols, 4 * image.rows), 0, 0, INTER_NEAREST);
	resize(out, out, Size(4 * out.cols, 4 * out.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	imshow("Eroded", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_opening(String imagePath)
{
	Mat image;
	Mat out;
	Mat structuringElement;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_opening: image is empty\n");
		return -1;
	}

	structuringElement = Mat::ones(3, 3, CV_8UC1);
	out = open(image, structuringElement);

	resize(image, image, Size(4 * image.cols, 4 * image.rows), 0, 0, INTER_NEAREST);
	resize(out, out, Size(4 * out.cols, 4 * out.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	imshow("Opening", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_closing(String imagePath)
{
	Mat image;
	Mat out;
	Mat structuringElement;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_closing: image is empty\n");
		return -1;
	}

	structuringElement = Mat::ones(3, 3, CV_8UC1);
	out = close(image, structuringElement);

	resize(image, image, Size(4 * image.cols, 4 * image.rows), 0, 0, INTER_NEAREST);
	resize(out, out, Size(4 * out.cols, 4 * out.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	imshow("Closing", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_extract_boundary(String imagePath)
{
	Mat image;
	Mat out;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_extract_boundary: image is empty\n");
		return -1;
	}

	out = extract_boundary(image);

	resize(image, image, Size(4 * image.cols, 4 * image.rows), 0, 0, INTER_NEAREST);
	resize(out, out, Size(4 * out.cols, 4 * out.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	imshow("Boundary Extract", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_fill_region(String imagePath, int startRow, int startCol)
{
	Mat image;
	Mat out;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_fill_region: image is empty\n");
		return -1;
	}

	out = fill_region(image, startRow, startCol);

	resize(image, image, Size(4 * image.cols, 4 * image.rows), 0, 0, INTER_NEAREST);
	resize(out, out, Size(4 * out.cols, 4 * out.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	imshow("Region Fill", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_statistical_properties(String imagePath)
{
	int ret;
	int histogram[256], cumulativeHistogram[256];
	float mean;
	float standardDeviation;
	Mat image, histImage, cumulativeHistImage;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_statistical_properties: image is empty\n");
		return -1;
	}

	ret = compute_histogram(image, histogram);
	if (ret) {
		perror("display_statistical_properties: compute_histogram() failed\n");
		return -1;
	}

	mean = compute_mean(histogram, image.rows * image.cols);
	std::cout << "Mean = " << mean << std::endl;

	standardDeviation = compute_standard_deviation(image, mean);
	std::cout << "Standard Deviation = " << standardDeviation << std::endl;

	histImage = create_histogram_image("Histogram", histogram, 256, 256);

	ret = compute_cumulative_histogram(histogram, cumulativeHistogram);
	if (ret) {
		perror("display_statistical_properties: compute_cumulative_histogram() failed\n");
		return -1;
	}

	cumulativeHistImage = create_histogram_image("Cumulative Histogram", cumulativeHistogram, 256, 256);

	resize(image, image, Size(4 * image.cols, 4 * image.rows), 0, 0, INTER_NEAREST);
	resize(histImage, histImage, Size(4 * histImage.cols, 4 * histImage.rows), 0, 0, INTER_NEAREST);
	resize(cumulativeHistImage, cumulativeHistImage, Size(4 * cumulativeHistImage.cols, 4 * cumulativeHistImage.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	imshow("Histogram", histImage);
	imshow("Cumulative Histogram", cumulativeHistImage);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_automatic_tresholding(String imagePath)
{
	Mat image, out;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_automatic_tresholding: image is empty\n");
		return -1;
	}

	out = automatic_thresholding(image);
	if (out.empty()) {
		perror("display_automatic_tresholding: out is empty\n");
		return -1;
	}

	resize(image, image, Size(4 * image.cols, 4 * image.rows), 0, 0, INTER_NEAREST);
	resize(out, out, Size(4 * out.cols, 4 * out.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	imshow("Automatic Tresholding", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_histogram_equalization(String imagePath)
{
	Mat image, out;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_histogram_equalization: image is empty\n");
		return -1;
	}

	out = histogram_equalization(image);
	if (out.empty()) {
		perror("display_histogram_equalization: out is empty\n");
		return -1;
	}

	resize(image, image, Size(4 * image.cols, 4 * image.rows), 0, 0, INTER_NEAREST);
	resize(out, out, Size(4 * out.cols, 4 * out.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	imshow("Histogram Equalization", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_gamma_correction(String imagePath, float gamma)
{
	Mat image, out;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_gamma_correction: image is empty\n");
		return -1;
	}

	out = gamma_correction(image, gamma);
	if (out.empty()) {
		perror("display_gamma_correction: out is empty\n");
		return -1;
	}

	resize(image, image, Size(4 * image.cols, 4 * image.rows), 0, 0, INTER_NEAREST);
	resize(out, out, Size(4 * out.cols, 4 * out.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	imshow("Gamma Correction", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_stretch_shrink(String imagePath, int newMin, int newMax)
{
	Mat image, out;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_stretch_shrink: image is empty\n");
		return -1;
	}

	out = histogram_stretch_shrink(image, newMin, newMax);
	if (out.empty()) {
		perror("display_stretch_shrink: out is empty\n");
		return -1;
	}

	resize(image, image, Size(4 * image.cols, 4 * image.rows), 0, 0, INTER_NEAREST);
	resize(out, out, Size(4 * out.cols, 4 * out.rows), 0, 0, INTER_NEAREST);

	imshow("Image", image);
	imshow("Stretch Shrink", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_median_filter(String imagePath, int kernelSize)
{
	Mat image, out;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty()) {
		perror("display_median_filter: image is empty\n");
		return -1;
	}

	out = filter_median(image, kernelSize);
	if (out.empty()) {
		perror("display_median_filter: out is empty\n");
		return -1;
	}

	resize(image, image, Size(), 4, 4, INTER_NEAREST);
	resize(out, out, Size(), 4, 4, INTER_NEAREST);

	imshow("Image", image);
	imshow("Median Filter", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_filter_gaussian_2d(String imagePath, int kernelSize)
{
	Mat image, out;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty())
	{
		perror("display_filter_gaussian_2d: image is empty\n");
		return -1;
	}

	out = filter_gaussian_2d(image, kernelSize);
	if (out.empty())
	{
		perror("display_filter_gaussian_2d: out is empty\n");
		return -1;
	}

	resize(image, image, Size(), 4, 4, INTER_NEAREST);
	resize(out, out, Size(), 4, 4, INTER_NEAREST);

	imshow("Image", image);
	imshow("Gaussian Filter", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int display_filter_gaussian_vec(String imagePath, int kernelSize)
{
	Mat image, out;

	image = imread(imagePath, IMREAD_GRAYSCALE);
	if (image.empty())
	{
		perror("display_filter_gaussian_vec: image is empty\n");
		return -1;
	}

	out = filter_gaussian_vec(image, kernelSize);
	if (out.empty())
	{
		perror("display_filter_gaussian_vec: out is empty\n");
		return -1;
	}

	resize(image, image, Size(), 4, 4, INTER_NEAREST);
	resize(out, out, Size(), 4, 4, INTER_NEAREST);

	imshow("Image", image);
	imshow("Gaussian Filter Vector", out);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

int main(int argc, char **argv)
{
	int op;
	int ret = 0;
	String imagesPath, imageName, imagePath;
	String inputsPath, inputName, inputPath;
	char name[255];
	int val;
	float floatVal;
	char c;
	bool option;
	int startRow, startCol;
	int min, max;

	imagesPath = "src/images/";
	imageName = "noise/balloons_gauss.bmp";
	imagePath = imagesPath + imageName;

	inputsPath = "src/input/";
	inputName = "reconstruct.txt";
	inputPath = inputsPath + inputName;

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
		case 14:
			std::cout << "Mouse callback " << imageName << std::endl;
			ret = mouse_callback(imagePath);
			if (ret)
				return -1;
			break;
		case 15:
			std::cout << "Object features " << imageName << std::endl;
			ret = object_features(imagePath, false);
			if (ret)
				return -1;
			break;
		case 16:
			std::cout << "Draw object features " << imageName << std::endl;
			ret = object_features(imagePath, true);
			if (ret)
				return -1;
			break;
		case 17:
			std::cout << "Filter objects by area and orentation " << imageName << std::endl;
			int maxArea;
			float minPhi, maxPhi;
			std::cout << "Max area = ";
			scanf("%d", &maxArea);
			std::cout << "Min phi = ";
			scanf("%f", &minPhi);
			std::cout << "Max phi = ";
			scanf("%f", &maxPhi);
			ret = filter_objects_by_area_and_orientation(imagePath, maxArea, minPhi, maxPhi);
			if (ret)
				return -1;
			break;
		case 18:
			std::cout << "Breadth first traversal labeling algorithm " << imageName << std::endl;
			ret = display_breadth_first_traversal_labeling(imagePath);
			if (ret)
				return -1;
			break;
		case 19:
			std::cout << "Two-pass labeling algorithm " << imageName << std::endl;
			ret = display_two_pass_labeling(imagePath);
			if (ret)
				return -1;
			break;
		case 20:
			std::cout << "Border of single object " << imageName << std::endl;
			ret = display_border_of_single_object(imagePath);
			if (ret)
				return -1;
			break;
		case 21:
			std::cout << "Chain code of border of single object " << imageName << std::endl;
			ret = display_chain_code_single_object(imagePath);
			if (ret)
				return -1;
			break;
		case 22:
			std::cout << "Object reconstruction from chain code " << imageName << std::endl;
			ret = display_object_reconstruction_from_chain_code(inputPath);
			if (ret)
				return -1;
			break;
		case 23:
			std::cout << "Dilate n times " << imageName << std::endl;
			std::cout << "Number of dilations = ";
			scanf("%d", &val);
			ret = display_dilate_n_times(imagePath, val);
			if (ret)
				return -1;
			break;
		case 24:
			std::cout << "Erode n times " << imageName << std::endl;
			std::cout << "Number of erosions = ";
			scanf("%d", &val);
			ret = display_erode_n_times(imagePath, val);
			if (ret)
				return -1;
			break;
		case 25:
			std::cout << "Opening " << imageName << std::endl;
			ret = display_opening(imagePath);
			if (ret)
				return -1;
			break;
		case 26:
			std::cout << "Closing " << imageName << std::endl;
			ret = display_closing(imagePath);
			if (ret)
				return -1;
			break;
		case 27:
			std::cout << "Boundary extract " << imageName << std::endl;
			ret = display_extract_boundary(imagePath);
			if (ret)
				return -1;
			break;
		case 28:
			std::cout << "Region fill " << imageName << std::endl;
			std::cout << "Start row = ";
			scanf("%d", &startRow);
			std::cout << "Start col = ";
			scanf("%d", &startCol);
			ret = display_fill_region(imagePath, startRow, startCol);
			if (ret)
				return -1;
			break;
		case 29:
			std::cout << "Statistical properties " << imageName << std::endl;
			ret = display_statistical_properties(imagePath);
			if (ret)
				return -1;
			break;
		case 30:
			std::cout << "Automatic tresholding " << imageName << std::endl;
			ret = display_automatic_tresholding(imagePath);
			if (ret)
				return -1;
			break;
		case 31:
			std::cout << "Histogram equalization " << imageName << std::endl;
			ret = display_histogram_equalization(imagePath);
			if (ret)
				return -1;
			break;
		case 32:
			std::cout << "Gamma correction " << imageName << std::endl;
			std::cout << "Gamma = ";
			scanf("%f", &floatVal);
			ret = display_gamma_correction(imagePath, floatVal);
			if (ret)
				return -1;
			break;
		case 33:
			std::cout << "Stretch/shrink " << imageName << std::endl;
			std::cout << "New min = ";
			scanf("%d", &min);
			std::cout << "New max = ";
			scanf("%d", &max);
			ret = display_stretch_shrink(imagePath, min, max);
			if (ret)
				return -1;
			break;
		case 50:
			std::cout << "Median filter " << imageName << std::endl;
			std::cout << "Filter size (3, 5, 7) = ";
			scanf("%d", &val);
			ret = display_median_filter(imagePath, val);
			if (ret)
				return -1;
			break;
		case 51:
			std::cout << "Gaussian 2D filter " << imageName << std::endl;
			std::cout << "Filter size (3, 5, 7) = ";
			scanf("%d", &val);
			ret = display_filter_gaussian_2d(imagePath, val);
			if (ret)
				return -1;
			break;
		case 52:
			std::cout << "Gaussian filter with vectors " << imageName << std::endl;
			std::cout << "Filter size (3, 5, 7) = ";
			scanf("%d", &val);
			ret = display_filter_gaussian_vec(imagePath, val);
			if (ret)
				return -1;
			break;
		case 100:
			std::cout << "Store correspondences " << std::endl;
			ret = store_correspondences();
			if (ret)
				return -1;
			break;
		case 101:
			std::cout << "Display correspondences " << std::endl;
			ret = display_correspondences();
			if (ret)
				return -1;
			break;
		case 102:
			std::cout << "Show morphing process " << std::endl;
			std::cout << "t = ";
			scanf("%f", &floatVal);
			ret = show_morphing_process(floatVal);
			if (ret)
				return -1;
			break;
		case 103:
			std::cout << "Save morphing frames " << std::endl;
			std::cout << "Number of frames = ";
			scanf("%d", &val);
			ret = save_morphing_frames(val);
			if (ret)
				return -1;
			break;
		case 104:
			std::cout << "Add correspondences " << std::endl;
			ret = add_correspondences();
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
