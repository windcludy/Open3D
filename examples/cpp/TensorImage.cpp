// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include <cstdio>

#include "open3d/Open3D.h"

using namespace open3d;

int main(int argc, char **argv) {

    utility::SetVerbosityLevel(utility::VerbosityLevel::Debug);

    const core::Device device = core::Device(argv[1]);
    const std::string filename_rgb(argv[2]);
    // const std::string filename_depth(argv[2]);

    // As device transfer is currently not supported in geometry::Image
    // and IO does not support CUDA, therefore copy to legacy image
    // for checking output.
    geometry::Image output_legacy;

    t::geometry::Image color_image(0,0,3,core::Dtype::UInt16, device);
    if (t::io::ReadImage(filename_rgb, color_image)) {
        utility::LogDebug("RGB image size : {:d} x {:d}",
                          color_image.GetRows(), color_image.GetCols());

        // Saving original image
        utility::LogDebug("Saving original input RGB image");
        output_legacy = color_image.ToLegacyImage();
        io::WriteImageToPNG("output01.png", output_legacy);
        utility::LogDebug("    Saved");

        // Dilate operation
        utility::LogDebug("Dilate Image");
        int half_kernel_size = 1;
        t::geometry::Image dilate_image = color_image.Dilate(half_kernel_size);
        output_legacy = dilate_image.ToLegacyImage();
        utility::LogDebug("Saving Dilated output image");
        io::WriteImageToPNG("output02.png", output_legacy);
        utility::LogDebug("    Saved");

        // Gaussian operation
        utility::LogDebug("Gaussian Filter");
        t::geometry::Image gauss_image = color_image.Filter(t::geometry::Image::FilterType::Gaussian15x15);
        output_legacy = gauss_image.ToLegacyImage();
        utility::LogDebug("Saving Gaussian output filter");
        io::WriteImageToPNG("output03.png", output_legacy);
        utility::LogDebug("    Saved");

        // Sobel operation
        utility::LogDebug("Sobel Horizontal Filter");
        t::geometry::Image sobelx_image = color_image.Filter(t::geometry::Image::FilterType::SobelHorizontal);
        output_legacy = sobelx_image.ToLegacyImage();
        utility::LogDebug("Saving Sobel-horizontal filter output.");
        io::WriteImageToPNG("output04.png", output_legacy);
        utility::LogDebug("    Saved");

        utility::LogDebug("Sobel Vertical Filter");
        t::geometry::Image sobely_image = color_image.Filter(t::geometry::Image::FilterType::SobelVertical);
        output_legacy = sobely_image.ToLegacyImage();
        utility::LogDebug("Saving Sobel-vertical filter output.");
        io::WriteImageToPNG("output05.png", output_legacy);
        utility::LogDebug("    Saved");

        // Bilateral operation
        // utility::LogDebug("Bilateral Filter");
        // t::geometry::Image bilateral_image = color_image.Filter(t::geometry::Image::FilterType::BilateralGauss);
        // output_legacy = bilateral_image.ToLegacyImage();
        // utility::LogDebug("Saving Sobel-vertical filter output.");
        // io::WriteImageToPNG("output06.png", output_legacy);
        // utility::LogDebug("    Saved");

        utility::LogDebug("All operations performed successfully...");
    }



        // auto gray_image = color_image.CreateFloatImage();
        // io::WriteImage("gray.png",
        //                *gray_image->CreateImageFromFloatImage<uint8_t>());

    //     utility::LogDebug("Gaussian Filtering");
    //     auto gray_image_b3 =
    //             gray_image->Filter(geometry::Image::FilterType::Gaussian3);
    //     io::WriteImage("gray_blur3.png",
    //                    *gray_image_b3->CreateImageFromFloatImage<uint8_t>());
    //     auto gray_image_b5 =
    //             gray_image->Filter(geometry::Image::FilterType::Gaussian5);
    //     io::WriteImage("gray_blur5.png",
    //                    *gray_image_b5->CreateImageFromFloatImage<uint8_t>());
    //     auto gray_image_b7 =
    //             gray_image->Filter(geometry::Image::FilterType::Gaussian7);
    //     io::WriteImage("gray_blur7.png",
    //                    *gray_image_b7->CreateImageFromFloatImage<uint8_t>());

    //     utility::LogDebug("Sobel Filtering");
    //     auto gray_image_dx =
    //             gray_image->Filter(geometry::Image::FilterType::Sobel3Dx);
    //     // make [-1,1] to [0,1].
    //     gray_image_dx->LinearTransform(0.5, 0.5);
    //     gray_image_dx->ClipIntensity();
    //     io::WriteImage("gray_sobel_dx.png",
    //                    *gray_image_dx->CreateImageFromFloatImage<uint8_t>());
    //     auto gray_image_dy =
    //             gray_image->Filter(geometry::Image::FilterType::Sobel3Dy);
    //     gray_image_dy->LinearTransform(0.5, 0.5);
    //     gray_image_dy->ClipIntensity();
    //     io::WriteImage("gray_sobel_dy.png",
    //                    *gray_image_dy->CreateImageFromFloatImage<uint8_t>());

    //     utility::LogDebug("Build Pyramid");
    //     auto pyramid = gray_image->CreatePyramid(4);
    //     for (int i = 0; i < 4; i++) {
    //         auto level = pyramid[i];
    //         auto level = level->CreateImageFromFloatImage<uint8_t>();
    //         std::string outputname =
    //                 "gray_pyramid_level" + std::to_string(i) + ".png";
    //         io::WriteImage(outputname, *level);
    //     }
    // } 
    else {
        utility::LogWarning("Failed to read {}", filename_rgb);
        return 1;
    }

    return 0;
}
