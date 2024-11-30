#pragma once

class UserLCD {

    virtual void display(const char *msg);
    virtual void clear();
    virtual void turnDisplayOn();
    virtual void turnDisplayOff();

};
