#include "animatable.h"

Animatable::Animatable()
    : _frameCount(0), _frameDt(0), _frames(nullptr)
{}

Animatable::Animatable(QString basePathFormatted, int frameCount, int frameDt)
    : _frameCount(frameCount), _frameDt(frameDt)
{
    _frames = new QPixmap[frameCount];
    for (int i = 0; i < frameCount; i++) {
        _frames[i] = QPixmap(QString::asprintf(basePathFormatted.toStdString().c_str(), i));
    }
}

/* return : true if done animating */
bool Animatable::update(int elapsed, bool once)
{
    if (elapsed - _lastElapsed > _frameDt) {
        _lastElapsed = elapsed;
        _currentFrame = (_currentFrame + 1) % _frameCount;
    }
    return (_currentFrame + 1) >= _frameCount;
}

QPixmap Animatable::currentPixmap()
{
    return _frames[_currentFrame % _frameCount];
}

void Animatable::reset(int value)
{
    _currentFrame = value;
}
