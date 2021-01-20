#ifndef ANIMATABLE_H
#define ANIMATABLE_H

#include <QPixmap>

class Animatable
{
public:
    /*
     * QString : chemin de base avec formatteur
     * int : nombre de frames
     * int : delta t frames
     */
    Animatable();
    Animatable(QString, int, int);

    bool update(int);
    void reset(int value = 0);

    /* getters */
    QPixmap getCurrentPixmap();

private:
    /* settings / data */
    int _frameCount;
    int _frameDt;
    QPixmap *_frames;

    /* helper */
    int _currentFrame;
    int _lastElapsed;
};

#endif // ANIMATABLE_H
