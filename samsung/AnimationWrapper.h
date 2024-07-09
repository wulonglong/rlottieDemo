/***
 * AnimationWrapper 交互层
 *
 */

#ifndef ANIMATIONWRAPPER_H
#define ANIMATIONWRAPPER_H

#include <QObject>
#include "rlottie.h"

using namespace rlottie;

class AnimationWrapper : public QObject
{
    Q_OBJECT
public:
    explicit AnimationWrapper(QObject *parent = nullptr);
public:
    bool      SetAnimation(char* path, size_t* w, size_t* h);
    bool      SetAnimationSize(size_t w, size_t h);
    uint32_t* RenderAnimation(uint32_t frameNum);
    size_t    GetTotalFrame();
    double    GetFrameRate();
    bool      IsAnimNULL();
    void      SetAnimationColor(int r, int g, int b);
    void      FreeAnimation();
signals:
private:
    std::unique_ptr<Animation> panim_;
    uint32_t *buffer_;
    size_t width_;
    size_t height_;
    size_t bytes_per_line_;
    uint32_t cur_color_ = UINT32_MAX;
};

#endif // ANIMATIONWRAPPER_H
