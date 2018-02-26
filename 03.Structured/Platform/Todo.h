#pragma once

// To allow #pragma TODO(blah blah) to give a 'clickable' message in the build
// window.

#define TODOSTRINGIZE(L) #L
#define TODOMAKESTRING(M,L) M(L)
#define TODOLINE TODOMAKESTRING( TODOSTRINGIZE, __LINE__) 
#define MACROASSTRING(x) TODOMAKESTRING( TODOSTRINGIZE, x) 

#if !defined(NDEBUG)

#if (AMSTELTECH_SHOW_TODO == 1)
/// TODO(message) - leave yourself notes that show up in the build window
/// like warnings
#define TODO(_msg) message(__FILE__ "(" TODOLINE ") : TODO : " _msg)
#else 
/// TODO(message) - leave yourself notes that show up in the build window
/// like warnings
#define TODO(x)
#endif // AMSTELTECH_SHOW_TODO

/// Don't document a bug with this, fix it!
#define BUG(_msg) message(__FILE__ "(" TODOLINE ") : BUG : " _msg)

/// Just a message
#define MESSAGE(_msg) message(__FILE__ "(" TODOLINE ") : " _msg)

/// Just an error
#define STOP(_msg) error(__FILE__ "(" TODOLINE ") : " _msg)

#else

#define TODO(x)
#define BUG(x)
#define MESSAGE(_msg) message(__FILE__ "(" TODOLINE ") : " _msg)
#define STOP(_msg) error(__FILE__ "(" TODOLINE ") : " _msg)

#endif // NDEBUG && AMSTELTECH_SHOW_TODO