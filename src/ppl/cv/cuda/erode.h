/**
 * @file   erode.h
 * @brief  Interface declarations of image eroding operation.
 * @author Liheng Jian(jianliheng@sensetime.com)
 *
 * @copyright Copyright (c) 2014-2021 SenseTime Group Limited.
 */

#ifndef _ST_HPC_PPL3_CV_CUDA_ERODE_H_
#define _ST_HPC_PPL3_CV_CUDA_ERODE_H_

#include <cfloat>

#include "cuda_runtime.h"

#include "ppl/common/retcode.h"
#include "ppl/cv/types.h"

namespace ppl {
namespace cv {
namespace cuda {

/**
 * @brief Erodes an image by using a specific structuring element.
 * @tparam T The data type of input and output image, currently only
 *         uint8_t(uchar) and float are supported.
 * @tparam channels The number of channels of input image, 1, 3 and 4 are
 *         supported.
 * @param stream         cuda stream object.
 * @param inHeight       input image's height.
 * @param inWidth        input image's width need to be processed.
 * @param inWidthStride  input image's width stride, it is `width * channels`
 *                       for cudaMalloc() allocated data, `pitch / sizeof(T)`
 *                       for 2D cudaMallocPitch() allocated data.
 * @param inData         input image data.
 * @param kernelx_len    the length of mask, x direction.
 * @param kernely_len    the length of mask, y direction.
 * @param kernel         the mask used for erosion.
 * @param outWidthStride the width stride of output image, similar to
 *                       inWidthStride.
 * @param outData        output image data.
 * @param border_type    ways to deal with border. BORDER_TYPE_CONSTANT,
 *                       BORDER_TYPE_TYPE_REPLICATE, BORDER_TYPE_REFLECT,
 *                       BORDER_TYPE_WRAP and BORDER_TYPE_REFLECT_101 are
 *                       supported now.
 * @param border_value   value for BORDER_TYPE_CONSTANT.
 * @return The execution status, succeeds or fails with an error code.
 * @note 1 For best performance, a 2D array allocated by cudaMallocPitch() is
 *         recommended.
 *       2 The destination matrix has the same data type, size, stride, and
 *         channels as the source matrix.
 *       3 kernel must be a single channel matrix and stored in host memory as
 *         an uchar 1D array.
 *       4 The anchor is at the kernel center.
 * @warning All parameters must be valid, or undefined behaviour may occur.
 * @remark The fllowing table show which data type and channels are supported.
 * <table>
 * <tr><th>Data type(T)<th>channels
 * <tr><td>uint8_t(uchar)<td>1
 * <tr><td>uint8_t(uchar)<td>3
 * <tr><td>uint8_t(uchar)<td>4
 * <tr><td>float<td>1
 * <tr><td>float<td>3
 * <tr><td>float<td>4
 * </table>
 * <table>
 * <caption align="left">Requirements</caption>
 * <tr><td>CUDA platforms supported<td>CUDA 7.0
 * <tr><td>Header files <td>#include "ppl/cv/cuda/erode.h"
 * <tr><td>Project      <td>ppl.cv
 * </table>
 * @since ppl.cv-v1.0.0
 * ###Example
 * @code{.cpp}
 * #include "ppl/cv/cuda/erode.h"
 * using namespace ppl::cv::cuda;
 *
 * int main(int argc, char** argv) {
 *   int width    = 640;
 *   int height   = 480;
 *   int channels = 3;
 *
 *   float* dev_input;
 *   float* dev_output;
 *   size_t input_pitch, output_pitch;
 *   cudaMallocPitch(&dev_input, &input_pitch,
 *                   width * channels * sizeof(float), height);
 *   cudaMallocPitch(&dev_output, &output_pitch,
 *                   width * channels * sizeof(float), height);
 *
 *   cudaStream_t stream;
 *   cudaStreamCreate(&stream);
 *   Erode<float, 3>(stream, height, width, input_pitch / sizeof(float),
 *                   dev_input, 3, 3, NULL, output_pitch / sizeof(float),
 *                   dev_output, ppl::cv::BORDER_TYPE_REPLICATE);
 *   cudaStreamSynchronize(stream);
 *
 *   cudaFree(dev_input);
 *   cudaFree(dev_output);
 *
 *   return 0;
 * }
 * @endcode
 */
template <typename T, int channels>
ppl::common::RetCode Erode(cudaStream_t stream,
                           int inHeight,
                           int inWidth,
                           int inWidthStride,
                           const T* inData,
                           int kernelx_len,
                           int kernely_len,
                           const uchar* kernel,
                           int outWidthStride,
                           T* outData,
                           BorderType border_type = BORDER_TYPE_CONSTANT,
                           const T border_value = FLT_MAX);

}  // namespace cuda
}  // namespace cv
}  // namespace ppl

#endif // _ST_HPC_PPL3_CV_CUDA_ERODE_H_