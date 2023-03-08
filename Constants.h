#ifndef CONSTANTS
#define CONSTANTS

#include <QString>

namespace SSw
{

// Global names
const QString APP               = "Super Saper";


// Icon path
const QString SMALL_MINE_PATH      = ":/images/mine.png";
const QString SMALL_BOOM_PATH      = ":/images/boom.png";
const QString BIG_MINE_PATH        = ":/images/logo.png";
const QString DISARMED_PATH         = ":/images/green.png";
const QString DISARMED_RED_PATH     = ":/images/red.png";
const QString QUESTION_PATH         = ":/images/question.png";
const QString SAD_FACE              = "://images/sad.png";
const QString NORMAL_FACE           = "://images/normal.png";
const QString FEAR_FACE             = "://images/click.png";
const QString HAPPY_FACE            = "://images/happy.png";

// Icon size
const int32_t FIELD_SIZE        = 24;
const int32_t ICON_SIZE         = 16;

// Default game preferences
const int32_t DEFAULT_HEIGHT    = 8;
const int32_t DEFAULT_WIDTH     = 8;
const int32_t DEFAULT_MINE     = 10;

const int32_t MSG_TIMEOUT       = 1000;

const double MIN_DENSITY        = 0.05;
const double MAX_DENSITY        = 0.95;

} // namespace SSw

#endif // CONSTANTS
