#include "animatable.h"

#include <QDebug>

Animatable::Animatable()
    : _frameCount(0), _frameDt(0), _frames(nullptr)
{}

Animatable::Animatable(QString basePathFormatted, int frameCount, int frameDt)
    : _frameCount(frameCount), _frameDt(frameDt), _lastElapsed(0)
{
    qDebug() << "loading new animatable using name structure '" + basePathFormatted + "'";

    _frames = new QPixmap[frameCount];
    for (int i = 0; i < frameCount; i++) {
        _frames[i] = QPixmap(QString::asprintf(basePathFormatted.toStdString().c_str(), i));
    }
}

/* return : true if done animating */
bool Animatable::update(int elapsed)
{
    if (elapsed - _lastElapsed > _frameDt) {
        _lastElapsed = elapsed;
        _currentFrame = (_currentFrame + 1) % _frameCount;
    }
    return (_currentFrame + 1) >= _frameCount;
}

QPixmap Animatable::getCurrentPixmap()
{
    return _frames[_currentFrame % _frameCount];
}

void Animatable::reset(int value)
{
    _currentFrame = value;
    _lastElapsed = 0;
}
