/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2014, Itseez Inc, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Itseez Inc or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/highgui/highgui.hpp"



// local includes
#include "msm_middlebury.hpp"
#include "util.hpp"
#include "../logger/log.h"


namespace cv {
    namespace datasets {

        using namespace std;

        class MSM_middleburyImp : public MSM_middlebury {
        public:
            MSM_middleburyImp() {

                photo_association =
                        {
//                                std::make_tuple(1,2),   std::make_tuple(2,3),   std::make_tuple(3,4),
//                                std::make_tuple(4,5),
//
//                                std::make_tuple(6,7),   std::make_tuple(7,8),   std::make_tuple(8,9),
//                                std::make_tuple(9,10),  std::make_tuple(10,11), std::make_tuple(11,12),
//
//                                std::make_tuple(13,14), std::make_tuple(14,15), std::make_tuple(15,16),
//                                std::make_tuple(16,17), std::make_tuple(17,18), std::make_tuple(18,19),
//                                std::make_tuple(19,20), std::make_tuple(20,21), std::make_tuple(21,22),
//                                std::make_tuple(22,23), std::make_tuple(23,24), std::make_tuple(24,25),
//                                std::make_tuple(25,26), std::make_tuple(26,27), std::make_tuple(27,28),
//                                std::make_tuple(28,29), std::make_tuple(29,30), std::make_tuple(30,31),
//
//                                std::make_tuple(32,33), std::make_tuple(33,34), std::make_tuple(34,35),
//                                std::make_tuple(35,36), std::make_tuple(36,37), std::make_tuple(37,38),
//                                std::make_tuple(38,39),
//
//                                std::make_tuple(40,41),

                                // ricostruiscono solo una colonna
                                // allineati sinistra <----
                                std::make_tuple(42,43), std::make_tuple(43,44), std::make_tuple(44,45),
                                std::make_tuple(45,46)

                        };

            }

            //MSM_middleburyImp(const string &path);
            virtual ~MSM_middleburyImp() {
            }

            virtual void load(const string &path);

            virtual cv::Mat loadImage(const int num_img);

        private:
            void loadDataset(const string &path);
        };




        void MSM_middleburyImp::load(const string &path) {
            loadDataset(path);
        }

        void MSM_middleburyImp::loadDataset(const string &path) {
            dataset_path = path;

            train.push_back(vector<Ptr<Object> >());
            test.push_back(vector<Ptr<Object> >());
            validation.push_back(vector<Ptr<Object> >());

            string name(path.substr(0, path.length() - 1));
            size_t start = name.rfind('/');
            name = name.substr(start + 1, name.length() - start);

            string angName(path + "templeR_ang.txt");
            string parName(path + "templeR_par.txt");

            FILE_LOG(logINFO) << "Loading dataset : " << name << " in path: " << path;

            ifstream infile(parName.c_str());
            string imageName;
            infile >> imageName; // skip header
            while (infile >> imageName) {
                Ptr<MSM_middleburyObj> curr(new MSM_middleburyObj);
                curr->imageName = imageName;

                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        infile >> curr->k(i, j);
                    }
                }
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        infile >> curr->r(i, j);
                    }
                }
                for (int i = 0; i < 3; ++i) {

                    infile >> curr->t[i];
                }

                train.back().push_back(curr);
            }
        }

        /*
            input : images number img1_num, img2_num
            output: cv:Mat matrices
        */
        cv::Mat MSM_middleburyImp::loadImage(const int img_num) {


            std::ostringstream ss;
            ss << std::setw(2) << std::setfill('0') << img_num;

            std::string img_path = dataset_path + "templeR00"+ ss.str() +".png";

            FILE_LOG(logINFO) << " loading " << img_path;


            // clear string stream
//            ss.str(std::string());
//            ss << std::setw(2) << std::setfill('0') << img2_num;
//            std::string img2_path = "../dataset/dataset_templeRing/templeR00"+ ss.str() +".png";
//            FILE_LOG(logINFO) << " loading " << img2_path;

            int color_mode = -1; // = alg == STEREO_BM ? 0 : -1;

            cv::Mat img1 = imread(img_path);

            float scale = 1.f; // TODO check
            if (1.f != scale) {
                Mat temp1;
                int method = scale < 1 ? INTER_AREA : INTER_CUBIC;
                resize(img1, temp1, Size(), scale, scale, method);
                img1 = temp1;

            }
            return img1;

        }

        Ptr<MSM_middlebury> MSM_middlebury::create() {
            return Ptr<MSM_middleburyImp>(new MSM_middleburyImp);
        }

    }
}
