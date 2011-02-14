#ifndef __MOEIMAGE_DATA_MATRIX3_H__
#define __MOEIMAGE_DATA_MATRIX3_H__

#include <QColor>

namespace data {

    struct Matrix3
    {
        typedef int ValueType;

        QRgb transform(QRgb original) const;

        Matrix3(ValueType _00_, ValueType _01_, ValueType _02_
              , ValueType _10_, ValueType _11_, ValueType _12_
              , ValueType _20_, ValueType _21_, ValueType _22_)
            : _00(_00_)
            , _01(_01_)
            , _02(_02_)
            , _10(_10_)
            , _11(_11_)
            , _12(_12_)
            , _20(_20_)
            , _21(_21_)
            , _22(_22_)
        {}
    private:
        ValueType _00, _01, _02;
        ValueType _10, _11, _12;
        ValueType _20, _21, _22;
    };

    Matrix3 const& rgSwapMatrix();
    Matrix3 const& gbSwapMatrix();
    Matrix3 const& rbSwapMatrix();

}

#endif /* __MOEIMAGE_DATA_MATRIX3_H__ */
