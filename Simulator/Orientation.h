#ifndef ORIENTATION_H
#define ORIENTATION_H

enum ORIENTATION{

    From_bottom_To_top = 0,
    From_top_To_bottom = 1,
    From_left_To_right = 2,
    From_right_To_left = 3
};

enum Orientation_lemp{
    horizontally = 0,
    vertically = 1

};

enum Orientation_selector{
    horV = 2,
    horN = 3,

    verL = 4,
    verR = 5,

    //Подлежат удалению.
    hor = 0,
    ver = 1
};

enum Orientation_battery{
    BTR_horV = 2,
    BTR_horN = 3,

    BTR_verL = 4,
    BTR_verR = 5,

    //Подлежат удалению.
    BTR_hor = 0,
    BTR_ver = 1
};

#endif // ORIENTATION_H

