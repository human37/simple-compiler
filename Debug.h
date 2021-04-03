#if !defined(DEBUG_H)
#define DEBUG_H

#include <iostream>

#if !defined(ShowMessages)
#define ShowMessages 1
#endif // ShowMessages

#if ShowMessages
#define MSG(X) std::cout << X << std::endl;
#else
#define MSG(X);
#endif // MSG

#endif // DEBUG_H