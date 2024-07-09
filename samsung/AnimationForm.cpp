#include "AnimationForm.h"
#include "ui_AnimationForm.h"
#include "AnimationWrapper.h"
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <QFile>

AnimationForm::AnimationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationForm)
   ,animation_wrapper_(nullptr)
   ,anim_width_(0)
   ,anim_height_(0)
   ,frame_rate_(0)
   ,total_frame_(0)
   ,cur_frame_(0)
   ,play_file_("")
{
    ui->setupUi(this);
  //  setAutoFillBackground(true);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground, true); // 设置透明背景

    animation_wrapper_ = std::make_shared<AnimationWrapper>();
    connect(&timer_player_,&QTimer::timeout,this,&AnimationForm::OnTimerRender);
}

AnimationForm::~AnimationForm()
{
    StopPlayAnimation();
    delete ui;
}
void AnimationForm::LoadAnimationFile(const QString & file_path)
{
    if(animation_wrapper_ == nullptr)
        return;
    QFile file(file_path);
    if (!file.exists(file_path)) {        
        return;
    }
    if (file_path.compare(play_file_) != 0) {
        StopPlayAnimation();
    }
    play_file_ = file_path;
	bool res = animation_wrapper_->SetAnimation(file_path.toLocal8Bit().data(), &anim_width_, &anim_height_);
    if(!res)
        return;

    frame_rate_ = animation_wrapper_->GetFrameRate();
    total_frame_ = animation_wrapper_->GetTotalFrame();

    if(frame_rate_>0){
        timer_player_.setInterval(1000*1.0/frame_rate_);
    }else{ // 设置默认帧率
         timer_player_.setInterval(1000*1.0/30);
    }
    if (anim_width_ > 0 && anim_height_ > 0) {
        this->resize(anim_width_, anim_height_);
    }
}

void AnimationForm::StartPlayAnimation()
{
    timer_player_.start();
}
void AnimationForm::StopPlayAnimation()
{
    if(timer_player_.isActive())
        timer_player_.stop();
    total_frame_ = 0;
    cur_frame_ = 0;
    if(animation_wrapper_ == nullptr)
        return;
    animation_wrapper_->FreeAnimation();
    this->close();
}
void AnimationForm::paintEvent(QPaintEvent *e)
{
    if(animation_wrapper_ == nullptr)
        return;
    if (!timer_player_.isActive()) {        
        return;
    }   
    
     uint32_t *data = animation_wrapper_->RenderAnimation(cur_frame_);
     if(data){
         QPainter pt(this);
		 pt.fillRect(rect(), Qt::transparent); // 填充透明背景

         QImage image = QImage(anim_width_, anim_height_, QImage::Format_ARGB32);

         qDebug()<<Q_FUNC_INFO<<"anim_width_:"<<anim_width_<<" anim_height_:"<<anim_height_
                <<" data:"<<*data;
         memcpy(image.bits(), data, anim_width_ * anim_height_ * sizeof(uint32_t));
        // image = image.scaled(this->width(),this->height());
         pt.drawImage(rect(),image);
     }
     qDebug()<<Q_FUNC_INFO<<" cur_frame_:"<<cur_frame_<<" total_frame_:"<<total_frame_;
     if(cur_frame_ == total_frame_){ // 最后一帧停止
         qDebug()<<"stop StopPlayAnimation";
         StopPlayAnimation();
         return;
     }
     cur_frame_++;
}
void AnimationForm::OnTimerRender()
{
    this->update();
//    if(animation_wrapper_ == nullptr)
//        return;
//     animation_wrapper_->RenderAnimation(cur_frame_);
//     if(cur_frame_ == total_frame_){ // 最后一帧停止
//         StopPlayAnimation();
//         return;
//     }
//     cur_frame_++;
}
