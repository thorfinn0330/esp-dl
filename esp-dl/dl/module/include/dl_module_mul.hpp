#pragma once
#include "dl_base_mul.hpp"
#include "dl_base_mul2d.hpp"
#include "dl_base_mul4d.hpp"
#include "dl_base_shape.hpp"
#include "dl_module_base.hpp"

namespace dl {
namespace module {
/**
 * NOTE: multiplication is element-wise, i.e., output[i,j,k] = input0[i,j,k] * input1[i,j,k]
 *
 * @tparam feature_t supports int16_t and int8_t,
 *         - int16_t: stands for operation in int16_t quantize
 *         - int8_t: stands for operation in int8_t quantize
 */
// class Mul2D : public Module {
// public:
//     /**
//      * @brief Construct a new Mul2D object.
//      *
//      * @param name            name of module
//      * @param inplace         inplace type.
//      */
//     Mul2D(const char *name = NULL,
//           module_inplace_t inplace = MODULE_NON_INPLACE,
//           quant_type_t quant_type = QUANT_TYPE_NONE) :
//         Module(name, inplace, quant_type)
//     {
//     }

//     /**
//      * @brief Destroy the Mul2D object.
//      */
//     ~Mul2D() {}

//     std::vector<std::vector<int>> get_output_shape(std::vector<std::vector<int>> &input_shapes)
//     {
//         assert(input_shapes.size() == 2);

//         // support multidirectional broadcasting
//         std::vector<int> output_shape = base::get_multidirectional_broadcasting_shape(input_shapes[0],
//         input_shapes[1]);

//         return std::vector<std::vector<int>>(1, output_shape);
//     }

//     void forward(std::vector<dl::TensorBase *> &tensors, runtime_mode_t mode)
//     {
//         DL_LOG_LAYER_LATENCY_INIT();
//         DL_LOG_LAYER_LATENCY_START();
//         if (quant_type == QUANT_TYPE_SYMM_8BIT) {
//             forward_template<int8_t>(tensors, mode);
//         } else if (quant_type == QUANT_TYPE_SYMM_16BIT) {
//             forward_template<int16_t>(tensors, mode);
//         }
//         DL_LOG_LAYER_LATENCY_END(this->name, "Mul2D");
//     }

//     void forward_args(void *args)
//     {
//         if (quant_type == QUANT_TYPE_SYMM_8BIT) {
//             base::mul2d<int8_t>(args);
//         } else if (quant_type == QUANT_TYPE_SYMM_16BIT) {
//             base::mul2d<int16_t>(args);
//         }
//     }

//     template <typename T>
//     void forward_template(std::vector<TensorBase *> &tensors, runtime_mode_t mode)
//     {
//         TensorBase *input0 = tensors[m_inputs_index[0]];
//         TensorBase *input1 = tensors[m_inputs_index[1]];
//         TensorBase *output = tensors[m_outputs_index[0]];

//         std::vector<base::arithArgsType<T>> m_args =
//             base::get_arith_operation_args<T>(output, input0, input1, Linear, nullptr, mode);
//         int task_size = m_args.size();
//         if (task_size == 1) { // single task
//             forward_args((void *)&m_args[0]);
//         } else if (task_size == 2) { // multi task, use semaphore to maintain synchronization.
//             module_forward_dual_core(this, (void *)&m_args[0], (void *)&m_args[1]);
//         } else {
//             ESP_LOGE("Mul2D", "Only support task size is 1 or 2, currently task size is %d", task_size);
//         }
//     }

//     /**
//      * @brief deserialize Mul2D module instance by node serialization information
//      */
//     static Module *deserialize(fbs::FbsModel *fbs_model, std::string node_name)
//     {
//         Module *op = nullptr;
//         quant_type_t quant_type;
//         fbs_model->get_operation_attribute(node_name, "quant_type", quant_type);

//         // Create module
//         if (quant_type == QUANT_TYPE_SYMM_8BIT || quant_type == QUANT_TYPE_SYMM_16BIT) {
//             op = new Mul2D(node_name.c_str(), MODULE_INPLACE_CHANGED_BUFFER, quant_type);
//         }
//         return op;
//     }

//     void print() { ESP_LOGI("Mul2D", "quant_type: %s.", quant_type_to_string(quant_type)); }
// };

/**
 * NOTE: addition is element-wise, i.e., output[i,j,k] = input0[i,j,k] + input1[i,j,k]
 *
 * @tparam feature_t supports int16_t and int8_t,
 *         - int16_t: stands for operation in int16_t quantize
 *         - int8_t: stands for operation in int8_t quantize
 */
// class Mul4D : public Module {
// public:
//     /**
//      * @brief Construct a new Mul4D object.
//      *
//      * @param name            name of module
//      * @param inplace         inplace type.
//      */
//     Mul4D(const char *name = NULL,
//           module_inplace_t inplace = MODULE_NON_INPLACE,
//           quant_type_t quant_type = QUANT_TYPE_NONE) :
//         Module(name, inplace, quant_type) // 调用基类构造函数
//     {
//     }

//     /**
//      * @brief Destroy the Mul4D object.
//      */
//     ~Mul4D() {}

//     std::vector<std::vector<int>> get_output_shape(std::vector<std::vector<int>> &input_shapes)
//     {
//         assert(input_shapes.size() == 2);

//         // 调用基类的多方向广播函数来支持4D
//         std::vector<int> output_shape = base::get_multidirectional_broadcasting_shape(input_shapes[0],
//         input_shapes[1]);

//         return std::vector<std::vector<int>>(1, output_shape);
//     }

//     void forward(std::vector<dl::TensorBase *> &tensors, runtime_mode_t mode)
//     {
//         if (quant_type == QUANT_TYPE_SYMM_8BIT) {
//             forward_template<int8_t>(tensors, mode);
//         } else if (quant_type == QUANT_TYPE_SYMM_16BIT) {
//             forward_template<int16_t>(tensors, mode);
//         }
//     }

//     void forward_args(void *args)
//     {
//         if (quant_type == QUANT_TYPE_SYMM_8BIT) {
//             base::mul4d<int8_t>(args); // 4D 版本的 add 运算
//         } else if (quant_type == QUANT_TYPE_SYMM_16BIT) {
//             base::mul4d<int16_t>(args); // 4D 版本的 add 运算
//         }
//     }

//     template <typename T>
//     void forward_template(std::vector<TensorBase *> &tensors, runtime_mode_t mode)
//     {
//         TensorBase *input0 = tensors[m_inputs_index[0]];
//         TensorBase *input1 = tensors[m_inputs_index[1]];
//         TensorBase *output = tensors[m_outputs_index[0]];

//         // 获取用于4D加法运算的参数
//         std::vector<base::arithArgsType<T>> m_args =
//             base::get_arith_operation_args<T>(output, input0, input1, Linear, nullptr, mode);
//         int task_size = m_args.size();
//         if (task_size == 1) {
//             forward_args((void *)&m_args[0]); // 单任务
//         } else if (task_size == 2) {
//             module_forward_dual_core(this, (void *)&m_args[0], (void *)&m_args[1]); // 多任务
//         } else {
//             ESP_LOGE("Mul4D", "Only support task size is 1 or 2, currently task size is %d", task_size);
//         }
//     }

//     /**
//      * @brief deserialize Mul4D module instance by node serialization information
//      */
//     static Module *deserialize(fbs::FbsModel *fbs_model, std::string node_name)
//     {
//         Module *op = nullptr;
//         quant_type_t quant_type;
//         fbs_model->get_operation_attribute(node_name, "quant_type", quant_type);

//         //
//         if (quant_type == QUANT_TYPE_SYMM_8BIT || quant_type == QUANT_TYPE_SYMM_16BIT) {
//             op = new Mul4D(NULL, MODULE_NON_INPLACE, quant_type); // test1234
//         }
//         return op;
//     }

//     void print() { ESP_LOGI("Mul4D", "quant_type: %s.", quant_type_to_string(quant_type)); }
// };

class Mul : public Module {
public:
    /**
     * @brief Construct a new Mul object.
     *
     * @param name            name of module
     * @param inplace         inplace type.
     */
    Mul(const char *name = NULL,
        module_inplace_t inplace = MODULE_NON_INPLACE,
        quant_type_t quant_type = QUANT_TYPE_NONE) :
        Module(name, inplace, quant_type)
    {
    }

    /**
     * @brief Destroy the Mul object.
     */
    ~Mul() {}

    std::vector<std::vector<int>> get_output_shape(std::vector<std::vector<int>> &input_shapes)
    {
        assert(input_shapes.size() == 2);

        std::vector<int> output_shape = base::get_multidirectional_broadcasting_shape(input_shapes[0], input_shapes[1]);

        return std::vector<std::vector<int>>(1, output_shape);
    }

    void forward(std::vector<dl::TensorBase *> &tensors, runtime_mode_t mode)
    {
        if (quant_type == QUANT_TYPE_SYMM_8BIT) {
            forward_template<int8_t>(tensors, mode);
        } else if (quant_type == QUANT_TYPE_SYMM_16BIT) {
            forward_template<int16_t>(tensors, mode);
        }
    }

    void forward_args(void *args)
    {
        if (quant_type == QUANT_TYPE_SYMM_8BIT) {
            base::elemwise_mul((base::elemwiseArgsType<int8_t> *)args);
        } else if (quant_type == QUANT_TYPE_SYMM_16BIT) {
            base::elemwise_mul((base::elemwiseArgsType<int16_t> *)args);
        }
    }

    template <typename T>
    void forward_template(std::vector<TensorBase *> &tensors, runtime_mode_t mode)
    {
        TensorBase *input0 = tensors[m_inputs_index[0]];
        TensorBase *input1 = tensors[m_inputs_index[1]];
        TensorBase *output = tensors[m_outputs_index[0]];

        std::vector<base::elemwiseArgsType<T>> m_args =
            base::get_elemwise_operation_args<T>(output, input0, input1, mode); // get element-wise operation args
        int task_size = m_args.size();
        if (task_size == 1) {
            forward_args((void *)&m_args[0]); // single task
        } else if (task_size == 2) {
            module_forward_dual_core(this, (void *)&m_args[0], (void *)&m_args[1]); // two task
        } else {
            ESP_LOGE("Mul", "Only support task size is 1 or 2, currently task size is %d", task_size);
        }
    }

    /**
     * @brief deserialize Mul module instance by node serialization information
     */
    static Module *deserialize(fbs::FbsModel *fbs_model, std::string node_name)
    {
        Module *op = nullptr;
        quant_type_t quant_type;
        fbs_model->get_operation_attribute(node_name, "quant_type", quant_type);

        //
        if (quant_type == QUANT_TYPE_SYMM_8BIT || quant_type == QUANT_TYPE_SYMM_16BIT) {
            op = new Mul(NULL, MODULE_NON_INPLACE, quant_type);
        }
        return op;
    }

    void print() { ESP_LOGI("Mul", "quant_type: %s.", quant_type_to_string(quant_type)); }
    // void print() { ESP_LOGI("Mul", "quant_type: %s, input0_sahep: %s.", quant_type_to_string(quant_type),
    // shape_to_string().c_str()); }
};

} // namespace module
} // namespace dl
