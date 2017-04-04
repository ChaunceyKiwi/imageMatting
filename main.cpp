#include "Image.hpp"
#include "ImageReader.hpp"
#include "MattingPerformer.hpp"
#include "ImagePrinter.hpp"

// File path
std::string path_prefix = "/Users/Chauncey/Workspace/imageMatting";
std::string img_path = path_prefix + "/bmp/peacock/peacock.bmp";
std::string img_m_path = path_prefix + "/bmp/peacock/peacock_m.bmp";

// Global variable
int lambda = 100; // Weight of scribbled piexel obedience
int win_size = 1; // The distance between center and border
double epsilon = 0.0000001;
double thresholdForScribble = 0.001;

int main(void)
{
  // Read image
  ImageReader imageReader;
  Image img(imageReader.readImage(img_path));
  Image img_m(imageReader.readImage(img_m_path));
  
  // Perform image matting
  MattingPerformer mattingPerformer(lambda, win_size, epsilon, thresholdForScribble, img.getMatrix(), img_m.getMatrix());
  mattingPerformer.performMatting();
  cv::Mat mattingResultF = mattingPerformer.getMattingResultF();
  cv::Mat mattingResultB = mattingPerformer.getMattingResultB();
  
  // Print matting result
  Image_Printer imagePrinter;
  imagePrinter.showImage(mattingResultF, "FrontObject");
  imagePrinter.showImage(mattingResultB, "Background");
  cv::waitKey(0); // Wait for a keystroke in the window
  
  return 0;
}