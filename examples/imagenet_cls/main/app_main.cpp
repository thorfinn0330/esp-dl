#include "esp_log.h"
#include "imagenet_cls.hpp"

extern const uint8_t cat_jpg_start[] asm("_binary_cat_jpg_start");
extern const uint8_t cat_jpg_end[] asm("_binary_cat_jpg_end");
const char *TAG = "imagenet_cls";

extern "C" void app_main(void)
{
    dl::image::jpeg_img_t jpeg_img = {
        .data = (uint8_t *)cat_jpg_start,
        .width = 300,
        .height = 300,
        .data_size = (uint32_t)(cat_jpg_end - cat_jpg_start),
    };
    dl::image::img_t img;
    img.pix_type = dl::image::DL_IMAGE_PIX_TYPE_RGB888;
    sw_decode_jpeg(jpeg_img, img);
    ImageNetCls *cls = new ImageNetCls();
    auto &results = cls->run(img);
    for (const auto &res : results) {
        ESP_LOGI(TAG, "category: %s, score: %f\n", res.cat_name, res.score);
    }
    delete cls;
    heap_caps_free(img.data);
}
