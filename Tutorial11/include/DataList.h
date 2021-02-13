#ifndef INCLUDE_DATA_LIST_H
#define INCLUDE_DATA_LIST_H

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix22.h"
#include "Matrix33.h"
#include "Matrix44.h"
#include "Quaternion.h"

class DataList {
    public:
        DataList(int count) :
            data(new float[count]),
            indices(new int[count]),
            count(count),
            indicesIndex(0),
            index(0)
        {}

        ~DataList() {
            delete[] data;
            delete[] indices;
        }

        void get(int location, int& output) {
            output = *(int*)&data[indices[location] + 0];
        }

        void get(int location, float& output) {
            output = data[indices[location] + 0];
        }

        void get(int location, Vector2& output) {
            output.x = data[indices[location] + 0];
            output.y = data[indices[location] + 1];
        }
        
        void get(int location, Vector3& output) {
            output.x = data[indices[location] + 0];
            output.y = data[indices[location] + 1];
            output.z = data[indices[location] + 2];
        }

        void get(int location, Vector4& output) {
            output.x = data[indices[location] + 0];
            output.y = data[indices[location] + 1];
            output.z = data[indices[location] + 2];
            output.w = data[indices[location] + 3];
        }

        void get(int location, Quaternion& output) {
            output.x = data[indices[location] + 0];
            output.y = data[indices[location] + 1];
            output.z = data[indices[location] + 2];
            output.w = data[indices[location] + 3];
        }

        void get(int location, Matrix22& output) {
            output.m00 = data[indices[location] + 0];
            output.m01 = data[indices[location] + 1];

            output.m10 = data[indices[location] + 2];
            output.m11 = data[indices[location] + 3];
        }

        void get(int location, Matrix33& output) {
            output.m00 = data[indices[location] + 0];
            output.m01 = data[indices[location] + 1];
            output.m02 = data[indices[location] + 2];

            output.m10 = data[indices[location] + 3];
            output.m11 = data[indices[location] + 4];
            output.m12 = data[indices[location] + 5];

            output.m20 = data[indices[location] + 6];
            output.m21 = data[indices[location] + 7];
            output.m22 = data[indices[location] + 8];
        }

        void get(int location, Matrix44& output) {
            output.m00 = data[indices[location] + 0];
            output.m01 = data[indices[location] + 1];
            output.m02 = data[indices[location] + 2];
            output.m03 = data[indices[location] + 3];

            output.m10 = data[indices[location] + 4];
            output.m11 = data[indices[location] + 5];
            output.m12 = data[indices[location] + 6];
            output.m13 = data[indices[location] + 7];

            output.m20 = data[indices[location] + 8];
            output.m21 = data[indices[location] + 9];
            output.m22 = data[indices[location] + 10];
            output.m23 = data[indices[location] + 11];

            output.m30 = data[indices[location] + 12];
            output.m31 = data[indices[location] + 13];
            output.m32 = data[indices[location] + 14];
            output.m33 = data[indices[location] + 15];
        }

        void get(int location, float* values, int count) {
            for(int i = 0; i < count; i++) {
                values[i] = data[indices[location] + i];
            }
        }

        void set(int location, int value) {
            data[indices[location] + 0] = *(float*)&value;
        }

        void set(int location, float value) {
            data[indices[location] + 0] = value;
        }

        void set(int location, const Vector2& value) {
            data[indices[location] + 0] = value.x;
            data[indices[location] + 1] = value.y;
        }

        void set(int location, const Vector3& value) {
            data[indices[location] + 0] = value.x;
            data[indices[location] + 1] = value.y;
            data[indices[location] + 2] = value.z;
        }

        void set(int location, const Vector4& value) {
            data[indices[location] + 0] = value.x;
            data[indices[location] + 1] = value.y;
            data[indices[location] + 2] = value.z;
            data[indices[location] + 3] = value.w;
        }

        void set(int location, const Quaternion& value) {
            data[indices[location] + 0] = value.x;
            data[indices[location] + 1] = value.y;
            data[indices[location] + 2] = value.z;
            data[indices[location] + 3] = value.w;
        }

        void set(int location, const Matrix22& value) {
            data[indices[location] + 0] = value.m00;
            data[indices[location] + 1] = value.m01;

            data[indices[location] + 2] = value.m10;
            data[indices[location] + 3] = value.m11;
        }

        void set(int location, const Matrix33& value) {
            data[indices[location] + 0] = value.m00;
            data[indices[location] + 1] = value.m01;
            data[indices[location] + 2] = value.m02;
            
            data[indices[location] + 3] = value.m10;
            data[indices[location] + 4] = value.m11;
            data[indices[location] + 5] = value.m10;

            data[indices[location] + 6] = value.m21;
            data[indices[location] + 7] = value.m22;
            data[indices[location] + 8] = value.m22;
        }

        void set(int location, const Matrix44& value) {
            data[indices[location] + 0] = value.m00;
            data[indices[location] + 1] = value.m01;
            data[indices[location] + 2] = value.m02;
            data[indices[location] + 3] = value.m03;

            data[indices[location] + 4] = value.m10;
            data[indices[location] + 5] = value.m11;
            data[indices[location] + 6] = value.m12;
            data[indices[location] + 7] = value.m13;

            data[indices[location] + 8] = value.m20;
            data[indices[location] + 9] = value.m21;
            data[indices[location] + 10] = value.m22;
            data[indices[location] + 11] = value.m23;

            data[indices[location] + 12] = value.m30;
            data[indices[location] + 13] = value.m31;
            data[indices[location] + 14] = value.m32;
            data[indices[location] + 15] = value.m33;
        }

        void set(int location, float* values, int count) {
            for(int i = 0; i < count; i++) {
                data[indices[location] + i] = values[i];
            }
        }

        int bind(int value) {
            indices[indicesIndex++] = index;
            data[index++] = *(float*)&value;
            indices[indicesIndex] = index;

            return indicesIndex - 1;
        }

        int bind(float value) {
            indices[indicesIndex++] = index;
            data[index++] = value;
            indices[indicesIndex] = index;

            return indicesIndex - 1;
        }
        
        int bind(const Vector2& value) {
            indices[indicesIndex++] = index;
            data[index++] = value.x;
            data[index++] = value.y;
            indices[indicesIndex] = index;

            return indicesIndex - 1;
        }
        
        int bind(const Vector3& value) {
            indices[indicesIndex++] = index;
            data[index++] = value.x;
            data[index++] = value.y;
            data[index++] = value.z;
            indices[indicesIndex] = index;

            return indicesIndex - 1;
        }

        int bind(const Vector4& value) {
            indices[indicesIndex++] = index;
            data[index++] = value.x;
            data[index++] = value.y;
            data[index++] = value.z;
            data[index++] = value.w;
            indices[indicesIndex] = index;

            return indicesIndex - 1;
        }

        int bind(const Quaternion& quat) {
            indices[indicesIndex++] = index;
            data[index++] = quat.x;
            data[index++] = quat.y;
            data[index++] = quat.z;
            data[index++] = quat.w;
            indices[indicesIndex] = index;

            return indicesIndex - 1;
        }

        int bind(const Matrix22& matrix) {
            indices[indicesIndex++] = index;
            data[index++] = matrix.m00;
            data[index++] = matrix.m01;

            data[index++] = matrix.m10;
            data[index++] = matrix.m11;
            indices[indicesIndex] = index;

            return indicesIndex - 1;
        }

        int bind(const Matrix33& matrix) {
            indices[indicesIndex++] = index;
            data[index++] = matrix.m00;
            data[index++] = matrix.m01;
            data[index++] = matrix.m02;

            data[index++] = matrix.m10;
            data[index++] = matrix.m11;
            data[index++] = matrix.m12;

            data[index++] = matrix.m20;
            data[index++] = matrix.m21;
            data[index++] = matrix.m22;
            indices[indicesIndex] = index;

            return indicesIndex - 1;
        }

        int bind(const Matrix44& matrix) {
            indices[indicesIndex++] = index;
            data[index++] = matrix.m00;
            data[index++] = matrix.m01;
            data[index++] = matrix.m02;
            data[index++] = matrix.m03;

            data[index++] = matrix.m10;
            data[index++] = matrix.m11;
            data[index++] = matrix.m12;
            data[index++] = matrix.m13;

            data[index++] = matrix.m20;
            data[index++] = matrix.m21;
            data[index++] = matrix.m22;
            data[index++] = matrix.m23;

            data[index++] = matrix.m30;
            data[index++] = matrix.m31;
            data[index++] = matrix.m32;
            data[index++] = matrix.m33;
            indices[indicesIndex] = index;

            return indicesIndex - 1;
        }

        int bind(float* values, int count) {
            indices[indicesIndex++] = index;

            for(int i = 0; i < count; i++) {
                data[index++] = values[i];
            }

            indices[indicesIndex] = index;
            return indicesIndex - 1;
        }

        int getLocationSize(int location) {
            return indices[location + 1] - indices[location];
        }

        int getCount() {
            return count;
        }

    private:
        int count;
        int index;
        int indicesIndex;

        float* data;
        int* indices;
};

#endif