/**
 * @file   copymakeborder.h
 * @brief  Interface declarations of forming a border around an image.
 * @author Liheng Jian(jianliheng@sensetime.com)
 *
 * @copyright Copyright (c) 2014-2021 SenseTime Group Limited.
 */

#ifndef _ST_HPC_PPL3_CV_CUDA_COPY_MAKE_BORDER_H_
#define _ST_HPC_PPL3_CV_CUDA_COPY_MAKE_BORDER_H_

#include "cuda_runtime.h"

#include "ppl/common/retcode.h"
#include "ppl/cv/types.h"

namespace ppl {
namespace cv {
namespace cuda {

/**
 * @brief Forms a border around an image.
 * @tparam T The data type of input and output image, uint8_t(uchar) and float
 *         are supported.
 * @tparam channels The number of channels of input image, 1, 3 and 4 are
 *         supported.
 * @param stream         cuda stream object.
 * @param height         input and output image's height.
 * @param width          input and output image's width need to be processed.
 * @param inWidthStride  input image's width stride, it is `width * channels`
 *                       for cudaMalloc() allocated data, `pitch / sizeof(T)`
 *                       for 2D cudaMallocPitch() allocated data.
 * @param inData         input image data.
 * @param outWidthStride width stride of output image, similar to inWidthStride.
 * @param outData        output image data.
 * @param top            number of top pixels.
 * @param bottom         number of bottom pixels.
 * @param left           number of left pixels.
 * @param right          number of right pixels.
 * @param border_type    ways to deal with border. BORDER_TYPE_CONSTANT,
 *                       BORDER_TYPE_REPLICATE, BORDER_TYPE_REFLECT,
 *                       BORDER_TYPE_WRAP, BORDER_TYPE_REFLECT_101 and
 *                       BORDER_TYPE_DEFAULT are supported now.
 * @param border_value   value for BORDER_TYPE_CONSTANT.
 * @return The execution status, succeeds or fails with an error code.
 * @note For best performance, a 2D array allocated by cudaMallocPitch() is
 *       recommended.
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
 * <tr><td>CUDA platforms supported <td>CUDA 7.0
 * <tr><td>Header files <td>#include "ppl/cv/cuda/copymakeborder.h"
 * <tr><td>Project      <td>ppl.cv
 * </table>
 * @since ppl.cv-v1.0.0
 * ###Example
 * @code{.cpp}
 * #include "ppl/cv/cuda/copymakeborder.h"
 * using namespace ppl::cv::cuda;
 *
 * int main(int argc, char** argv) {
 *   int width    = 640;
 *   int height   = 480;
 *   int channels = 3;
 *   int border   = 16;
 *
 *   float* dev_input;
 *   float* dev_output;
 *   size_t input_pitch, output_pitch;
 *   cudaMallocPitch(&dev_input, &input_pitch,
 *                   width * channels * sizeof(float), height);
 *   cudaMallocPitch(&dev_output, &output_pitch,
 *                   (width + border * 2) * channels * sizeof(float),
 *                   (height + border * 2));
 *
 *   cudaStream_t stream;
 *   cudaStreamCreate(&stream);
 *   CopyMakeBorder<float, 3>(stream, height, width,
 *                            input_pitch / sizeof(float), dev_input,
 *                            output_pitch / sizeof(float), dev_output,
 *                            border, border, border, border,
 *                            ppl::cv::BORDER_TYPE_DEFAULT);
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
ppl::common::RetCode CopyMakeBorder(cudaStream_t stream,
                                    int height,
                                    int width,
                                    int inWidthStride,
                                    const T* inData,
                                    int outWidthStride,
                                    T* outData,
                                    int top,
                                    int bottom,
                                    int left,
                                    int right,
                                    BorderType border_type,
                                    T border_value = 0);

}  // namespace cuda
}  // namespace cv
}  // namespace ppl

#endif // _ST_HPC_PPL3_CV_CUDA_COPY_MAKE_BORDER_H_