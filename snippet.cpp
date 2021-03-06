

//    pcl::PointCloud<pcl::PointXYZRGB>::Ptr generatePointCloud(Ptr<cv::datasets::MSM_middlebury> &dataset, const int img1_num, const int img2_num, bool opencv_rec){
//
//        Mat img1;
//        Mat img2;
//
//        // images path
//
//        // load images data
//        Ptr<cv::datasets::MSM_middleburyObj> data_img1 =
//                static_cast< Ptr<cv::datasets::MSM_middleburyObj> >  (dataset->getTrain()[img1_num]);
//        Ptr<cv::datasets::MSM_middleburyObj> data_img2 =
//                static_cast< Ptr<cv::datasets::MSM_middleburyObj> >  (dataset->getTrain()[img2_num]);
//
//
//        Ptr<cv::datasets::MSM_middleburyObj> data_img_origin =
//                static_cast< Ptr<cv::datasets::MSM_middleburyObj> >  (dataset->getTrain()[1]);
//
//
//        Mat r_origin = Mat(data_img_origin->r);
//        // init translation vectors from dataset
//        Mat t_origin = Mat(3, 1, CV_64FC1, &data_img_origin->t);
//        Mat P_origin_inv = stereo_util::createPINVFromRT(r_origin, t_origin);
//
//
//        // load images
//        img1 = dataset->loadImage(img1_num);
//        img2 = dataset->loadImage(img2_num);
//
//
//        // init
//        Mat R1,R2,P1,P2,Q;
//
//        // zero distiorsions
//        Mat D1 = Mat::zeros(1, 5, CV_64F);
//        Mat D2 = Mat::zeros(1, 5, CV_64F);
//
//        // load K and R from dataset info
//        Mat M1 = Mat(data_img1->k);
//        Mat M2 = Mat(data_img2->k);
//
//        // First image
//        Mat r1 = Mat(data_img1->r);
//        Mat t1 = Mat(3, 1, CV_64FC1, &data_img1->t);
//        // create P = KT for image 1
////        Mat p1_ = Mat(3, 4, CV_64FC1);
////        cv::hconcat(r1, t1, p1_);
//////        Mat vect = Mat::zeros(1, 4, CV_64F);
//////        cv::vconcat(p1_, vect, p1_);
////        // move p1*P_origin_inv
////        p1_ = p1_*P_origin_inv;
////        // extract new r1 and t1
////        r1 = p1_(cv::Rect(0,0,3,3));
////        t1 = p1_(cv::Rect(3,0,1,3));
////
//
//        // Second image
//        Mat r2 = Mat(data_img2->r);
//        Mat t2 = Mat(3, 1, CV_64FC1, &data_img2->t);
//        // create P = KT for image 1
////        Mat p2_ = Mat(3, 4, CV_64FC1);
////        cv::hconcat(r2, t2, p2_);
//////        Mat vect2 = Mat::zeros(1, 4, CV_64F);
//////        cv::vconcat(p2_, vect2, p2_);
////        p2_ = p2_*P_origin_inv;
////        r2 = p2_(cv::Rect(0,0,3,3));
////        t2 = p2_(cv::Rect(3,0,1,3));
//
//
//
////        Mat h_concat;
////        cv::hconcat(r_origin, t_origin, h_concat);
////        Mat vect = Mat::zeros(1, 4, CV_64F);
////        vect.at<CV_64FC1>(0, 3) = 1;
////        cv::vconcat(h_concat, vect, P_origin);
////        Mat P_origin_inv = P_origin.inv();
//
//
//
//
//
//        // rotation between img2 and img1
//        cv::Mat R = r2*r1.t();
//        // translation between img2 and img1
//        cv::Mat T = t1 - (R.t()*t2 );
//        FILE_LOG(logINFO) << "TRASLAZIONE AAAAAA " << T;
//
//        //    double tx = atan2 (R.at<double>(3,2), R.at<double>(3,3));
//        //    double ty = - asin(R.at<double>(3,1));
//        //    double tz = atan2 (R.at<double>(2,1), R.at<double>(1,1));
//        //    FILE_LOG(logDEBUG) << "ROTATION " << img1_num << "-" <<img2_num<< " tx="<< tx <<" ty=" << ty << "tz= " << tz;
//
//        //    theta_x = arctan(r_{3,2}/r_{3,3})
//        //    \theta_y = -arcsin(r_{3,1})
//        //    \theta_z = arctan(r_{2,1}/r_{1,1})
//
//        cv:Mat img1_segm_mask;
////
////        std::tuple<cv::Mat, cv::Mat> segm_tuple1 = stereo_util::segmentation(img1);
////        img1 = std::get<0>(segm_tuple1);
////        img1_segm_mask = std::get<1>(segm_tuple1);
////
////        std::tuple<cv::Mat, cv::Mat> segm_tuple2 = stereo_util::segmentation(img2);
////        img2 = std::get<0>(segm_tuple2);
//
//        // SEGMENTATION
////        img1 = stereo_util::segmentationGrabcut(img1);
////        img2 = stereo_util::segmentationGrabcut(img2);
////
////
////        std::ostringstream ss;
////        ss << std::setw(2) << std::setfill('0') << img1_num;
////        std::string img_path = "templeR00"+ ss.str() +"_segm.png";
////        imwrite(img_path, img1);
////
////        ss.str(std::string());
////        ss.clear();
////        ss << std::setw(2) << std::setfill('0') << img2_num;
////        img_path = "templeR00"+ ss.str() +"_segm.png";
////        imwrite(img_path, img1);
//
//        cv::Mat img1_original = img1.clone();
//        cv::Mat img2_original = img2.clone();
//
//        FILE_LOG(logINFO) << "Rectifying images...";
//        Rect roi1,roi2;
//        stereo::rectifyImages(img1, img2, M1, D1, M2, D2, R, T, R1, R2, P1, P2, Q, roi1, roi2, 1.f);
//
//        //    cv::Mat img_roi(img1);
//        //    rectangle(img_roi, roi1.tl(), roi1.br(), CV_RGB(255, 0,0), 10, 8, 0);
////        imshow("rect", img1 );
//
//        FILE_LOG(logINFO) << "Computing Disparity map Dense Stereo";
//        Mat disp(img1.size(), CV_32F);
//        FILE_LOG(logDEBUG) << "imgsize " << stereo_util::infoMatrix(img1);
//        FILE_LOG(logDEBUG) << "dispsize " << stereo_util::infoMatrix(disp);
//
//        stereo::computeDisparity(img1_num, img2_num, img1_original, img2_original, disp,1,roi1,roi2);
//
////        stereo::display(img1, img2, disp);
//        //
//
//
//        FILE_LOG(logINFO) << "Creating point cloud..";
//        Mat recons3D(disp.size(), CV_32FC3);
//        FILE_LOG(logINFO) << "recons3Dsize " << stereo_util::infoMatrix(recons3D);
//
//        // stereo::storePointCloud(disp, Q, recons3D);
//
//        //std::cout << "Creating Point Cloud..." <<std::endl;
//        pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_ptr (new pcl::PointCloud<pcl::PointXYZRGB>);
//
//        if (opencv_rec)
//            stereo::createPointCloudOpenCV(img1, img2, img1_segm_mask, Q, disp, recons3D, point_cloud_ptr);
//        else
//            stereo::createPointCloudCustom(img1, img2, img1_segm_mask, Q, disp, recons3D, point_cloud_ptr);
//
//        return point_cloud_ptr;
//
//    }



//    void createAllClouds(Ptr<cv::datasets::MSM_middlebury> &dataset, std::vector<pcl::PointCloud<pcl::PointXYZRGB>::Ptr> & clouds){
//
//
//        int img1_num;
//        int img2_num;
//
//
//        std::stringstream ss;
//        std::string path;
//
//        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;// = generatePointCloud(dataset, img1_num, img2_num,false);
////        clouds.push_back(cloud);
//
////        pcl::io::savePCDFileASCII ("./cloud1.pcd", *cloud);
//        unsigned int dataset_size = (unsigned int)dataset->getTrain().size();
//
//
//
//        libconfig::Config cfg;
//        // Read the file. If there is an error, report it and exit.
//        try
//        {
//            cfg.readFile("../config/config.cfg");
//        }
//        catch(const libconfig::FileIOException &fioex)
//        {
//            std::cerr << "I/O error while reading file." << std::endl;
//            exit(EXIT_FAILURE);
//        }
//        catch(const libconfig::ParseException &pex)
//        {
//            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
//                    << " - " << pex.getError() << std::endl;
//            exit(EXIT_FAILURE);
//        }
//
//        const libconfig::Setting & root = cfg.getRoot();
//        const libconfig::Setting & DatasetSettings  = root["Dataset"];
//
//        libconfig::Setting & lista = DatasetSettings["associations"];
//
//        int image_reference = (int) lista[0][0];
//
//        for (int i=0; i<lista.getLength(); i++){
//
//            img1_num = (int) lista[i][0];
//            img2_num = (int) lista[i][1];
//            cloud = generatePointCloud(dataset, img1_num, img2_num, true);
//            if(!(*cloud).empty()){
//
//                if (img1_num != image_reference) {
////                    Eigen::Matrix4f transf = stereo_util::getTransformBetweenClouds(dataset, image_reference, img1_num);
////                    // Executing the transformation
////                    pcl::PointCloud<pcl::PointXYZRGB>::Ptr transformed_cloud (new pcl::PointCloud<pcl::PointXYZRGB> ());
////                    // You can either apply transform_1 or transform_2; they are the same
////                    pcl::transformPointCloud (*cloud, *transformed_cloud, transf);
////
////                    clouds.push_back(transformed_cloud);
//
////                } else {
//                clouds.push_back(cloud);
//
////                }
//
//                // save
//                ss.str( std::string() );
//                ss.clear();
//                ss << img1_num<< "-" << img2_num ;
//                path = "./cloud"+ ss.str() +".pcd";
//                pcl::io::savePCDFileASCII (path, *cloud);
//                }
//
//            }
//
//        }
////        for(std::vector<std::tuple<int,int>>::iterator it = dataset->getAssociation().begin();
////            it != dataset->getAssociation().end(); ++it) {
////            img1_num = std::get<0>(*it);
////            img2_num = std::get<1>(*it);
////            cloud = generatePointCloud(dataset, img1_num, img2_num, true);
////            if(!(*cloud).empty()){
////
//////                if (img1_num != 1) {
//////                    Eigen::Matrix4f transf = stereo_util::getTransformBetweenClouds(dataset, image_reference, img1_num);
//////                    // Executing the transformation
//////                    pcl::PointCloud<pcl::PointXYZRGB>::Ptr transformed_cloud (new pcl::PointCloud<pcl::PointXYZRGB> ());
//////                    // You can either apply transform_1 or transform_2; they are the same
//////                    pcl::transformPointCloud (*cloud, *transformed_cloud, transf);
//////
//////                    clouds.push_back(transformed_cloud);
//////
//////                } else {
////                    clouds.push_back(cloud);
////
//////                }
////
////                // save
////                ss.str( std::string() );
////                ss.clear();
////                ss << img1_num<< "-" << img2_num ;
////                path = "./cloud"+ ss.str() +".pcd";
////                pcl::io::savePCDFileASCII (path, *cloud);
////            }
////
////            /* std::cout << *it; ... */
//
//
//        FILE_LOG(logINFO) << "cloud size" <<clouds.size();
//
//    }

void createPointCloudCustom (Mat& img1, Mat& img2, Mat img_1_segm, Mat& Q, Mat& disp, Mat& recons3D, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &point_cloud_ptr) {

    //     VERSIONE CUSTOM REPROJECT
    double Q03, Q13, Q23, Q32, Q33;
    Q03 = Q.at<double>(0, 3);
    Q13 = Q.at<double>(1, 3);
    Q23 = Q.at<double>(2, 3);
    Q32 = Q.at<double>(3, 2);
    Q33 = Q.at<double>(3, 3);

    double px, py, pz;
    uchar pr, pg, pb;

//        FILE_LOG(logINFO) << "imgsize " << stereo_util::infoMatrix(img1);
//        FILE_LOG(logINFO) << "imgsize " << stereo_util::infoMatrix(img_1_segm);
//        FILE_LOG(logINFO) << "imgsize i:" <<img_1_segm.at<unsigned int>(479, 588);

    for (int i = 0; i < img1.rows; i++) {

        uchar *rgb_ptr = img1.ptr<uchar>(i);

        // VERSIONE CUSTOM REPROJECT
        uchar *disp_ptr = disp.ptr<uchar>(i);


        for (int j = 0; j < img1.cols; j++) {

            //Get 3D coordinates
            // VERSIONE CUSTOM REPROJECT
            uchar d = disp_ptr[j];
            if (d == 0) continue; //Discard bad pixels
            double pw = -1.0 * static_cast<double>(d) * Q32 + Q33;
            px = static_cast<double>(j) + Q03;
            py = static_cast<double>(i) + Q13;
            pz = Q23;

            px = px / pw;
            py = py / pw;
            pz = pz / pw;

            //Get RGB info
            pb = rgb_ptr[3 * j];
            pg = rgb_ptr[3 * j + 1];
            pr = rgb_ptr[3 * j + 2];

            //Insert info into point cloud structure
            pcl::PointXYZRGB point;
            point.x = static_cast<float>(px);
            point.y = static_cast<float>(py);
            point.z = static_cast<float>(pz);

            uint32_t rgb = (static_cast<uint32_t>(pr) << 16 |
                            static_cast<uint32_t>(pg) << 8 | static_cast<uint32_t>(pb));
            point.rgb = *reinterpret_cast<float *>(&rgb);


//                if (img_1_segm.at<unsigned int>(i, j) != 0)
            point_cloud_ptr->points.push_back(point);
        }
    }
    point_cloud_ptr->width = (int) point_cloud_ptr->points.size();
    point_cloud_ptr->height = 1;

}


void storePointCloud(Mat& disp, Mat& Q,/*const char* filename,*/ Mat& recons3D){

    FILE_LOG(logINFO) << "storing the point cloud..";

//        printf("storing the point cloud...");
//        fflush(stdout);

    reprojectImageTo3D(disp, recons3D, Q, true);
    //reprojectImageTo3D( disp, xyz, Q, false, CV_32F );

//        const double max_z = 1.0e4;
//        FILE* fp = fopen(filename, "wt");
//        for(int y = 0; y < recons3D.rows; y++)
//        {
//            for(int x = 0; x < recons3D.cols; x++)
//            {
//                Vec3f point = recons3D.at<Vec3f>(y, x);
//                if(fabs(point[2] - max_z) < FLT_EPSILON || fabs(point[2]) > max_z) continue;
//                fprintf(fp, "%f %f %f\n", point[0], point[1], point[2]);
//            }
//        }
//        fclose(fp);
//        printf("\n");

}


void display(const int img1_num, const int img2_num, Mat& img1, Mat& img2,Mat& disp){

//        namedWindow("left ", 1);
    imshow("left "+std::to_string(img1_num), img1);
//        namedWindow("right", 1);
    imshow("right"+std::to_string(img2_num), img2);
//        namedWindow("disparity", 0);
    imshow("disparity", disp);
    printf("press any key to continue...");

    fflush(stdout);
    waitKey();
    destroyAllWindows();

    printf("\n");

}


void computeDisparity(const int img1_num, const int img2_num, Mat& img_left, Mat& img_right,Mat& disp,int alg,Rect & roi1,Rect &roi2){


        std::string tipo = "BM";

        Mat g1, g2;

        ///da provare
        cvtColor(img_left, g1, CV_BGR2GRAY);
        cvtColor(img_right, g2, CV_BGR2GRAY);

        // ROTATE IMAGES
        if (img1_num < 32)
            stereo_util::rotate_clockwise(g1, g1, false);
        else
            stereo_util::rotate_clockwise(g1, g1, true);

        if (img2_num < 32)
            stereo_util::rotate_clockwise(g2, g2, false);
        else
            stereo_util::rotate_clockwise(g2, g2, true);


        libconfig::Config cfg;
        // Read the file. If there is an error, report it and exit.
        try
        {
            cfg.readFile("../config/config.cfg");
        }
        catch(const libconfig::FileIOException &fioex)
        {
            std::cerr << "I/O error while reading file." << std::endl;
            exit(EXIT_FAILURE);
        }
        catch(const libconfig::ParseException &pex)
        {
            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                    << " - " << pex.getError() << std::endl;
            exit(EXIT_FAILURE);
        }


        if (tipo == "BM")
        {

            StereoBM sbm;

            // Get the store name.
            try
            {
                const libconfig::Setting & root = cfg.getRoot();
                const libconfig::Setting & StereoBMSettings  = root["StereoBM"];

                sbm.state->SADWindowSize = (int) StereoBMSettings["SADWindowSize"];
                sbm.state->numberOfDisparities = (int) StereoBMSettings["numberOfDisparities"];
                sbm.state->preFilterSize = (int) StereoBMSettings["preFilterSize"];
                sbm.state->preFilterCap = (int) StereoBMSettings["preFilterCap"];
                sbm.state->minDisparity = (int) StereoBMSettings["minDisparity"];
                sbm.state->textureThreshold = (int) StereoBMSettings["textureThreshold"];
                sbm.state->uniquenessRatio = (int) StereoBMSettings["uniquenessRatio"];
                sbm.state->speckleWindowSize = (int) StereoBMSettings["speckleWindowSize"];
                sbm.state->speckleRange = (int) StereoBMSettings["speckleRange"];
                sbm.state->disp12MaxDiff = (int) StereoBMSettings["disp12MaxDiff"];


            }
            catch(const libconfig::SettingNotFoundException &nfex)
            {
                sbm.state->SADWindowSize = 5;
                sbm.state->numberOfDisparities = 192;
                sbm.state->preFilterSize = 5;
                sbm.state->preFilterCap = 51;
                sbm.state->minDisparity = 25;
                sbm.state->textureThreshold = 223;
                sbm.state->uniquenessRatio = 0;
                sbm.state->speckleWindowSize = 0;
                sbm.state->speckleRange = 0;
                sbm.state->disp12MaxDiff = 0;

            }

            sbm(g1, g2, disp, CV_32F);

        }
        else if (tipo == "SGBM")
        {
            StereoSGBM sbm;
            sbm.SADWindowSize = 5;
            sbm.numberOfDisparities = 112;
            sbm.preFilterCap = 63;
            sbm.minDisparity = 0;
            sbm.uniquenessRatio = 10;
            sbm.speckleWindowSize = 0;
            sbm.speckleRange = 0;
            sbm.disp12MaxDiff = 1;
            sbm.fullDP = false;
            sbm.P1 = 8*3*5*5;
            sbm.P2 = 8*3*5*5;
            sbm(g1, g2, disp);
        }



        bool show_disparity_smooth = false;
        cv::Mat disp_smooth, disp8;

        // apply smoothing
//        normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);

        int smooth_kernel_size;
        double smooth_sigma_color, smooth_sigma_space;
        try
        {
            const libconfig::Setting & root = cfg.getRoot();
            const libconfig::Setting & SmoothingSettings  = root["Smoothing"];

//            cv::bilateralFilter ( disp, disp_smooth,
//                    (int) SmoothingSettings["kernel"],
//                    (double) SmoothingSettings["sigmaColor"],
//                    (double) SmoothingSettings["sigmaSpace"] );

            smooth_kernel_size = (int) SmoothingSettings["kernel"];
            smooth_sigma_color = (double) SmoothingSettings["sigmaColor"];
            smooth_sigma_space =  (double) SmoothingSettings["sigmaSpace"];

            show_disparity_smooth = (bool) SmoothingSettings["show"];

        }
        catch(const libconfig::SettingNotFoundException &nfex)
        {
//            cv::bilateralFilter ( disp, disp_smooth, 9, 60, 30 );
            smooth_kernel_size = 5;
            smooth_sigma_color = 20.;
            smooth_sigma_space =  20.;
        }

        cv::bilateralFilter ( disp, disp_smooth,
                    smooth_kernel_size,
                    smooth_sigma_color,
                    smooth_sigma_space );

        // apply bilateral filtering
//        cv::adaptiveBilateralFilter(disp8, disp_smooth,
//                cv::Size(smooth_kernel_size, smooth_kernel_size),
//                smooth_sigma_space, smooth_sigma_color); // size sigmaspace sigmacolor

//
//        //APPLY INPAINTING
//        Mat inpaintMask;
//        Mat img = Mat(disp_smooth.rows, disp_smooth.cols, CV_8U);
//        img = disp_smooth.clone();
//        inpaintMask = Mat::zeros(img.size(), CV_8U);
//        for (int rows = 0; rows < img.rows; ++rows) {
//            for (int cols = 0; cols < img.cols; ++cols) {
//                if ((img.at<unsigned char>(rows, cols)) > 150)
//                    inpaintMask.at<unsigned char>(rows, cols) = 255;
//            }
//
//        }
//        Mat inpainted;
//        cv::inpaint(img, inpaintMask, inpainted, 3, INPAINT_TELEA);
//
//        // apply bilateral filtering
//        cv::adaptiveBilateralFilter(disp8, disp_smooth,
//                cv::Size(smooth_kernel_size, smooth_kernel_size),
//                smooth_sigma_space, smooth_sigma_color);


        imwrite("disp_"+std::to_string(img1_num)+"_"+std::to_string(img2_num)+".png", disp_smooth);


        if (show_disparity_smooth){

            cv::Mat dispHeath;
            applyColorMap(disp_smooth, dispHeath, COLORMAP_JET);

            imshow("inpainted image- smooth", dispHeath);
//            Mat dispSGBMn,dispSGBMnSmooth, dispSGBMheat, dispSGBMheatSmooth;
//
//            // prepare disparity
//            normalize(disp, dispSGBMn, 0, 255, CV_MINMAX, CV_8U); // form 0-255
//            applyColorMap(dispSGBMn, dispSGBMheat, COLORMAP_JET);
//
//            // prepare disparity smoothed
//            normalize(disp_smooth, dispSGBMnSmooth, 0, 255, CV_MINMAX, CV_8U); // form 0-255
//            applyColorMap(dispSGBMnSmooth, dispSGBMheatSmooth, COLORMAP_JET);
//
//            // create single view
//            Size sz1 = dispSGBMheat.size();
//            Size sz2 = dispSGBMheatSmooth.size();
//            Mat im3(sz1.height, sz1.width+sz2.width, CV_8UC3);
//            Mat left(im3, Rect(0, 0, sz1.width, sz1.height));
//            dispSGBMheat.copyTo(left);
//            Mat right(im3, Rect(sz1.width, 0, sz2.width, sz2.height));
//            dispSGBMheatSmooth.copyTo(right);
//            imshow("Disparity - Disparity Smoothed "+std::to_string(img1_num)+"_"+std::to_string(img2_num), im3);
//

            fflush(stdout);
            waitKey();
            destroyAllWindows();
        }


        disp_smooth.copyTo(disp);

        // RESTORE ROTATION
        if (img1_num < 32)
            stereo_util::rotate_clockwise(disp, disp, true);
        else
            stereo_util::rotate_clockwise(disp, disp, false);


    }





//    ////////////////////////////////////////////////////////////////////////////////
//    void
//    findCorrespondences (  pcl::PointCloud<pcl::PointNormal>::Ptr  &src,
//            pcl::PointCloud<pcl::PointNormal>::Ptr  &tgt,
//            pcl::Correspondences &all_correspondences)
//    {
//        //CorrespondenceEstimationNormalShooting<PointT, PointT, PointT> est;
//        //CorrespondenceEstimation<PointT, PointT> est;
//        CorrespondenceEstimationBackProjection<PointNormal, PointNormal, PointNormal> est;
//        est.setInputSource (src);
//        est.setInputTarget (tgt);
//
//        est.setSourceNormals (src);
//        est.setTargetNormals (tgt);
//        est.setKSearch (10);
//        est.determineCorrespondences (all_correspondences);
//        //est.determineReciprocalCorrespondences (all_correspondences);
//    }
//
//    ////////////////////////////////////////////////////////////////////////////////
//    void
//    rejectBadCorrespondences (  pcl::CorrespondencesPtr &all_correspondences,
//            pcl::PointCloud<pcl::PointNormal>::Ptr  &src,
//            pcl::PointCloud<pcl::PointNormal>::Ptr  &tgt,
//            pcl::Correspondences &remaining_correspondences)
//    {
//        CorrespondenceRejectorMedianDistance rej;
//        rej.setMedianFactor (8.79241104);
//        rej.setInputCorrespondences (all_correspondences);
//
//        rej.getCorrespondences (remaining_correspondences);
//        return;
//
//        CorrespondencesPtr remaining_correspondences_temp (new Correspondences);
//        rej.getCorrespondences (*remaining_correspondences_temp);
//        PCL_DEBUG ("[rejectBadCorrespondences] Number of correspondences remaining after rejection: %d\n", remaining_correspondences_temp->size ());
//
//        // Reject if the angle between the normals is really off
//        CorrespondenceRejectorSurfaceNormal rej_normals;
//        rej_normals.setThreshold (acos (deg2rad (45.0)));
//        rej_normals.initializeDataContainer<PointNormal, PointNormal> ();
//        rej_normals.setInputCloud<PointNormal> (src);
//        rej_normals.setInputNormals<PointNormal, PointNormal> (src);
//        rej_normals.setInputTarget<PointNormal> (tgt);
//        rej_normals.setTargetNormals<PointNormal, PointNormal> (tgt);
//        rej_normals.setInputCorrespondences (remaining_correspondences_temp);
//        rej_normals.getCorrespondences (remaining_correspondences);
//    }
//
//    ////////////////////////////////////////////////////////////////////////////////
//    void
//    findTransformation (  pcl::PointCloud<pcl::PointNormal>::Ptr  &src,
//            pcl::PointCloud<pcl::PointNormal>::Ptr  &tgt,
//            pcl::CorrespondencesPtr &correspondences,
//            Eigen::Matrix4d &transform)
//    {
//        TransformationEstimationPointToPlaneLLS<PointNormal, PointNormal, double> trans_est;
//        trans_est.estimateRigidTransformation (*src, *tgt, *correspondences, transform);
//    }
//
//    ////////////////////////////////////////////////////////////////////////////////
//    void
//    view (  pcl::PointCloud<pcl::PointNormal>::Ptr &src,   pcl::PointCloud<pcl::PointNormal>::Ptr &tgt,   pcl::CorrespondencesPtr &correspondences)
//    {
//        if (!visualize || !vis) return;
//        PointCloudColorHandlerCustom<PointNormal> green (tgt, 0, 255, 0);
//        if (!vis->updatePointCloud<PointNormal> (src, "source"))
//        {
//            vis->addPointCloud<PointNormal> (src, "source");
//            vis->resetCameraViewpoint ("source");
//        }
//        if (!vis->updatePointCloud<PointNormal> (tgt, green, "target")) vis->addPointCloud<PointNormal> (tgt, green, "target");
//        vis->setPointCloudRenderingProperties (PCL_VISUALIZER_OPACITY, 0.5, "source");
//        vis->setPointCloudRenderingProperties (PCL_VISUALIZER_OPACITY, 0.7, "target");
//        vis->setPointCloudRenderingProperties (PCL_VISUALIZER_POINT_SIZE, 6, "source");
//        pcl::console::TicToc tt;
//        tt.tic ();
//        if (!vis->updateCorrespondences<PointNormal> (src, tgt, *correspondences, 1))
//            vis->addCorrespondences<PointNormal> (src, tgt, *correspondences, 1, "correspondences");
//        tt.toc_print ();
//        vis->setShapeRenderingProperties (PCL_VISUALIZER_LINE_WIDTH, 5, "correspondences");
//        //vis->setShapeRenderingProperties (PCL_VISUALIZER_COLOR, 1.0, 0.0, 0.0, "correspondences");
//        vis->spin ();
//    }
//
//    ////////////////////////////////////////////////////////////////////////////////
//    void
//    icp (  pcl::PointCloud<pcl::PointNormal>::Ptr &src,
//            pcl::PointCloud<pcl::PointNormal>::Ptr &tgt,
//            Eigen::Matrix4d &transform)
//    {
//
//        vis.reset (new PCLVisualizer ("Registration example"));
//
//        pcl::CorrespondencesPtr all_correspondences (new  pcl::Correspondences);
//        pcl::CorrespondencesPtr good_correspondences (new  pcl::Correspondences);
//
//        pcl::PointCloud<pcl::PointNormal>::Ptr output (new  pcl::PointCloud<pcl::PointNormal>);
//        *output = *src;
//
//        Eigen::Matrix4d final_transform (Eigen::Matrix4d::Identity ());
//
//        int iterations = 0;
//        DefaultConvergenceCriteria<double> converged (iterations, transform, *good_correspondences);
//
//        // ICP loop
//        do
//        {
//            // Find correspondences
//            findCorrespondences (output, tgt, *all_correspondences);
//            PCL_DEBUG ("Number of correspondences found: %d\n", all_correspondences->size ());
//
//            if (rejection)
//            {
//                // Reject correspondences
//                rejectBadCorrespondences (all_correspondences, output, tgt, *good_correspondences);
//                PCL_DEBUG ("Number of correspondences remaining after rejection: %d\n", good_correspondences->size ());
//            }
//            else
//                *good_correspondences = *all_correspondences;
//
//            // Find transformation
//            findTransformation (output, tgt, good_correspondences, transform);
//
//            // Obtain the final transformation
//            final_transform = transform * final_transform;
//
//            // Transform the data
//            transformPointCloudWithNormals (*src, *output, final_transform.cast<float> ());
//
//            // Check if convergence has been reached
//            ++iterations;
//
//            // Visualize the results
//            view (output, tgt, good_correspondences);
//        }
//        while (!converged);
//        transform = final_transform;
//    }
//
//
//}