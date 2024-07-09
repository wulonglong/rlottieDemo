#ifndef ANIMATIONFORM_H
#define ANIMATIONFORM_H

#include <QWidget>
#include <QTimer>


class AnimationWrapper;

namespace Ui {
class AnimationForm;
}
class AnimationForm : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationForm(QWidget *parent = nullptr);
    ~AnimationForm();

    void LoadAnimationFile(const QString &file_path);
    void StartPlayAnimation();
    void StopPlayAnimation();

public:
   void paintEvent(QPaintEvent *e);
private slots:
    void OnTimerRender();

private:
    Ui::AnimationForm *ui;
    QTimer timer_player_;
    size_t anim_width_;
    size_t anim_height_;
    double frame_rate_;
    int total_frame_;
    int cur_frame_;
    QString play_file_;
    std::shared_ptr<AnimationWrapper> animation_wrapper_;
};

#endif // ANIMATIONFORM_H
