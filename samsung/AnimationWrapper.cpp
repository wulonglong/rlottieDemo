#include "AnimationWrapper.h"


AnimationWrapper::AnimationWrapper(QObject *parent)
    : QObject{parent}
    ,panim_(nullptr)
    ,buffer_(nullptr)
    ,width_(0)
    ,height_(0)
    ,bytes_per_line_(0)
    ,cur_color_(UINT_MAX)
{

}

bool AnimationWrapper::SetAnimationSize(size_t w, size_t h)
{
    if(w<=0||h<=0)
        return false;
    width_ = w;
    height_ = h;
    bytes_per_line_ = width_ * sizeof(uint32_t);

    if (buffer_ != NULL)
        FreeAnimation();
    buffer_ = (uint32_t*)calloc(bytes_per_line_ * height_, sizeof(uint32_t));
    if(buffer_){
        return true;
    }
    return false;
}

bool AnimationWrapper::SetAnimation(char* path, size_t* w, size_t* h)
{
    if(path == nullptr || w == nullptr || h == nullptr)
        return false;
    panim_ = Animation::loadFromFile(path);
    panim_->size(*w, *h);
    SetAnimationSize(*w, *h);
    return true;
}

uint32_t* AnimationWrapper::RenderAnimation(uint32_t frameNum)
{
    if(panim_ == nullptr|| buffer_ == nullptr)
        return nullptr;
    Surface surface = Surface(buffer_, width_, height_, bytes_per_line_);
    panim_->renderSync(frameNum, surface);
    // background color
   /* for (int i = 0; i < height_; i++){
        for (int j = 0; j < width_; ++j)
        {
            uint32_t* v = buffer_ + i * width_ + j;
            if (*v == 0) *v = cur_color_;
        }
    }*/
    return buffer_;
}

void AnimationWrapper::SetAnimationColor(int r, int g, int b)
{
    cur_color_ = ((255 << 16) * r) + ((255 << 8) * g) + 255 * b;
}

size_t AnimationWrapper::GetTotalFrame()
{
    if(panim_ == nullptr)
        return 0;
    return panim_->totalFrame();
}
double AnimationWrapper::GetFrameRate()
{
    if(panim_ == nullptr)
        return 0;
    return panim_->frameRate();
}

bool AnimationWrapper::IsAnimNULL()
{
    return panim_ == NULL;
}

void AnimationWrapper::FreeAnimation()
{
    
    if(buffer_){
        free(buffer_);
        buffer_ = nullptr;
    }
}
