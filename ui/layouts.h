#ifndef __MOEIMAGE_UI_LAYOUTS_H__
#define __MOEIMAGE_UI_LAYOUTS_H__

#include <QWidget>
#include <QLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace ui {

    template <typename _FinalType, typename _ParentType>
    struct LayoutBase
    {
        typedef LayoutBase<_FinalType, _ParentType> ThisType;

        template <template <typename> class _SubLayoutTemplate>
        _SubLayoutTemplate<_FinalType> begin()
        {
            _SubLayoutTemplate<_FinalType> sub(final());
            final().layout->addItem(sub.layout);
            return sub;
        }

        _ParentType& end()
        {
            return parent;
        }

        _ParentType& parent;
    protected:
        explicit LayoutBase(_ParentType& p)
            : parent(p)
        {}
    private:
        _FinalType& final()
        {
            return *static_cast<_FinalType*>(this);
        }

        _FinalType const& final() const
        {
            return *static_cast<_FinalType const*>(this);
        }
    };

    template <typename _ParentType>
    struct HoriLayout
        : public LayoutBase<HoriLayout<_ParentType>, _ParentType>
    {
        HoriLayout& operator()(QWidget* widget)
        {
            layout->addWidget(widget);
            return *this;
        }

        explicit HoriLayout(_ParentType& p)
            : LayoutBase<HoriLayout<_ParentType>, _ParentType>(p)
            , layout(new QHBoxLayout)
        {}

        QHBoxLayout* const layout;
    };

    template <typename _ParentType>
    struct VertLayout
        : public LayoutBase<VertLayout<_ParentType>, _ParentType>
    {
        VertLayout& operator()(QWidget* widget)
        {
            layout->addWidget(widget);
            return *this;
        }

        explicit VertLayout(_ParentType& p)
            : LayoutBase<VertLayout<_ParentType>, _ParentType>(p)
            , layout(new QVBoxLayout)
        {}

        QVBoxLayout* const layout;
    };

    template <typename _ParentType>
    struct GridLayout
        : public LayoutBase<GridLayout<_ParentType>, _ParentType>
    {
        GridLayout& operator()()
        {
            ++column;
            return *this;
        }

        GridLayout& operator()(QWidget* widget)
        {
            layout->addWidget(widget, row, column);
            ++column;
            return *this;
        }

        GridLayout& operator[](int)
        {
            ++row;
            column = 0;
            return *this;
        }

        GridLayout(_ParentType& p)
            : LayoutBase<GridLayout<_ParentType>, _ParentType>(p)
            , layout(new QGridLayout)
            , column(0)
            , row(0)
        {}

        QGridLayout* const layout;
    private:
        int column;
        int row;
    };

    struct MainLayoutWrapper
    {
        MainLayoutWrapper& operator()(QWidget* member)
        {
            layout->addWidget(member);
            return *this;
        }

        template <template <typename> class _SubLayoutTemplate>
        _SubLayoutTemplate<MainLayoutWrapper> begin()
        {
            _SubLayoutTemplate<MainLayoutWrapper> sub(*this);
            layout->addItem(sub.layout);
            return sub;
        }

        QWidget* end() const
        {
            return widget;
        }

        explicit MainLayoutWrapper(QWidget* w)
            : widget(w)
            , layout(new QVBoxLayout(w))
        {
            widget->setLayout(layout);
        }

        QWidget* const widget;
        QVBoxLayout* const layout;
    };

}

#endif /* __MOEIMAGE_UI_LAYOUTS_H__ */
