| Supported Targets | ESP32-S3 | ESP32-P4 |
| ----------------- | -------- | -------- |


input_shape : h * w * c  
mobilenetv2 : 224 * 224 * 3  

|                          | preprocess(us) | model(us)   | postprocess(us) |
|--------------------------|----------------|-------------|-----------------|
| mobilenetv2_s8_v1_s3     | 26430          | 1286254     | 1187            |
| mobilenetv2_s8_v1_p4     | 13649          | 350109      | 686             |