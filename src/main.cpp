#include "ImageViewer.h"

int main() {
    std::unique_ptr<ImView::ImageViewer> imageViewer {std::make_unique<ImView::ImageViewer>()};
    imageViewer->Run();

    return 0;
}