/*
    Do some simple test here, which is not strict unit test.
*/

#include <iostream>

#include "tensor/shape.h"
#include "tensor/storage.h"
#include "tensor/tensor_impl.h"
#include "utils/base_config.h"
#include "utils/array.h"
#include "tensor/shape.h"
#include "utils/exception.h"  // CHECK_XXX is defined here.

using std::cout;
using std::endl;

void test_tensor() {
    using namespace st;

    data_t data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    index_t idata[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    cout << "check 1" << endl;
    st::Tensor t1(data, {3, 4});
    cout << t1 << endl;
    for(index_t i = 0, idx = -1; i < 3; ++i) {
        for(index_t j = 0; j < 4; ++j) {
            // Tensor::operator[](initilize_list<index_t>) will return a result of type data_t,
            // but as we know, we can't check whether two double vars are equal.
            int value = t1[{i, j}];
            CHECK_EQUAL(value, data[++idx], "check 1");
        }
    }
    
    cout << "check 2" << endl;
    auto t2 = t1.transpose(0, 1);
    cout << t2 << endl;
    for(index_t i = 0; i < 4; ++i) {
        for(index_t j = 0; j < 3; ++j) {
            int value1 = t1[{j, i}];
            int value2 = t2[{i, j}];
            CHECK_EQUAL(value1, value2, "check 2");
        }
    }

    cout << "check 3" << endl;
    auto t3 = t2.slice(/*start=*/1, /*end=*/3, /*dim=*/1);
    auto shape_t3 = t3.size();
    cout << shape_t3 << endl;
    CHECK_TRUE(shape_t3[0] == 4 && shape_t3[1] == 2, "check 3");
    cout << t3 << endl;
    for(index_t i = 0; i < 4; ++i) {
        for(index_t j = 0; j < 2; ++j) {
            int value1 = t2[{i, j+1}];
            int value2 = t3[{i, j}];
            CHECK_EQUAL(value1, value2, "check 3");
        }
    }

    cout << "check 4" << endl;
    auto t4 = t1.view({3, 2, 2});
    auto shape_t4 = t4.size();
    cout << shape_t4 << endl;
    cout << t4 << endl;
    for(index_t i = 0; i < 3; ++i) {
        for(index_t j = 0; j < 2; ++j) {
            for(index_t k = 0; k < 2; ++k) {
                int value1 = t1[{i, j*2+k}];
                int value2 = t4[{i, j, k}];
                CHECK_EQUAL(value1, value2, "check 4");
            }
        }
    }

    cout << "check 5" << endl;
    auto t5 = t4.unsqueeze(/*dim=*/0).unsqueeze(/*dim=*/2);
    CHECK_EQUAL(t5.ndim(), 5, "check 5");
    cout << t5 << endl;
    Shape shape_t5({1, 3, 1, 2, 2});
    for(index_t i = 0; i < 5; ++i)
        CHECK_EQUAL(t5.size(i), shape_t5[i], "check 5");
    for(index_t i = 0; i < 3; ++i) {
        for(index_t j = 0; j < 2; ++j) {
            for(index_t k = 0; k < 2; ++k) {
                int value1 = t4[{i, j, k}];
                int value2 = t5[{0, i, 0, j, k}];
                CHECK_EQUAL(value1, value2, "check 5");
            }
        }
    }

    cout << "check 6" << endl;
    auto t6 = t5.squeeze();
    cout << t6 << endl;
    CHECK_EQUAL(t6.ndim(), t4.ndim(), "check 6");
    for(index_t i = 0; i < 3; ++i) {
        for(index_t j = 0; j < 2; ++j) {
            for(index_t k = 0; k < 2; ++k) {
                int value1 = t4[{i, j, k}];
                int value2 = t6[{i, j, k}];
                CHECK_EQUAL(value1, value2, "check 6");
            }
        }
    }
}


int main() {
    cout << "test_tensor()" << endl;
    test_tensor();


    return 0;
}
