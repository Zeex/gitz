#include "pch.h"
#include "MainWindow.h"
#include "MainWindow.g.cpp"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::Gitz::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        // myButton().Content(box_value(L"Clicked"));
    }
}
