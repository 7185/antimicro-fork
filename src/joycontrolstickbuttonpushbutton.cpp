#include <QDebug>
#include <QStyle>

#include "joycontrolstickbuttonpushbutton.h"

JoyControlStickButtonPushButton::JoyControlStickButtonPushButton(QWidget *parent) :
    QPushButton(parent)
{
    this->button = 0;
}

JoyControlStickButtonPushButton::JoyControlStickButtonPushButton(JoyControlStickButton *button, QWidget *parent) :
    QPushButton(parent)
{
    this->button = button;

    connect(button, SIGNAL(clicked(int)), this, SLOT(flash()));
    connect(button, SIGNAL(released(int)), this, SLOT(unflash()));
}

JoyControlStickButton* JoyControlStickButtonPushButton::getButton()
{
    return button;
}

void JoyControlStickButtonPushButton::JoyControlStickButtonPushButton::setButton(JoyControlStickButton *button)
{
    disableFlashes();
    this->button = button;
    enableFlashes();
}

bool JoyControlStickButtonPushButton::isButtonFlashing()
{
    return isflashing;
}

void JoyControlStickButtonPushButton::flash()
{
    isflashing = true;

    this->style()->unpolish(this);
    this->style()->polish(this);

    emit flashed(isflashing);
}

void JoyControlStickButtonPushButton::unflash()
{
    isflashing = false;

    this->style()->unpolish(this);
    this->style()->polish(this);

    emit flashed(isflashing);
}

void JoyControlStickButtonPushButton::refreshLabel()
{
    if (button)
    {
        setText(button->getName().replace("&", "&&"));
    }
}

void JoyControlStickButtonPushButton::disableFlashes()
{
    if (button)
    {
        disconnect(button, SIGNAL(clicked(int)), 0, 0);
        disconnect(button, SIGNAL(released(int)), 0, 0);
    }
    this->unflash();
}

void JoyControlStickButtonPushButton::enableFlashes()
{
    if (button)
    {
        connect(button, SIGNAL(clicked(int)), this, SLOT(flash()));
        connect(button, SIGNAL(released(int)), this, SLOT(unflash()));
    }
}