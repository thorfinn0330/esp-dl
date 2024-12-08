#pragma once

#include "dl_detect_define.hpp"
#include "dl_feat_base.hpp"
#include "dl_recognition_database.hpp"
#include "dl_tensor_base.hpp"
namespace human_face_recognition {
class MFN : public dl::feat::FeatImpl {
public:
    MFN(const char *model_name);
};

using MBF = MFN;
} // namespace human_face_recognition

class HumanFaceFeat : public dl::feat::FeatWrapper {
public:
    typedef enum {
        MFN_S8_V1,
        MBF_S8_V1,
    } model_type_t;
    HumanFaceFeat(model_type_t model_type = static_cast<model_type_t>(CONFIG_HUMAN_FACE_FEAT_MODEL_TYPE));
};

class HumanFaceRecognizer : public dl::recognition::DB {
private:
    HumanFaceFeat *m_feat_extract;
    float m_thr;
    int m_top_k;

public:
    HumanFaceRecognizer(dl::recognition::db_type_t db_type = dl::recognition::DB_FATFS_FLASH,
                        HumanFaceFeat::model_type_t model_type =
                            static_cast<HumanFaceFeat::model_type_t>(CONFIG_HUMAN_FACE_FEAT_MODEL_TYPE),
                        float thr = 0.5,
                        int top_k = 1) :
        dl::recognition::DB(db_type, 512, "face"),
        m_feat_extract(new HumanFaceFeat(model_type)),
        m_thr(thr),
        m_top_k(top_k)
    {
    }

    ~HumanFaceRecognizer();

    std::vector<dl::recognition::result_t> recognize(const dl::image::img_t &img,
                                                     std::list<dl::detect::result_t> &detect_res);
    esp_err_t enroll(const dl::image::img_t &img, std::list<dl::detect::result_t> &detect_res);
};
