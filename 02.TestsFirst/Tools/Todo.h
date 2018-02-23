#pragma once

// To allow #pragma TODO(blah blah) to give a 'clickable' message in the build window.

#define TODOSTRINGIZE(L) #L
#define TODOMAKESTRING(M,L) M(L)
#define TODOLINE TODOMAKESTRING( TODOSTRINGIZE, __LINE__) 
#define TODO(_msg) message(__FILE__ "(" TODOLINE ") : TODO : " _msg)

#define BUG(_msg) message(__FILE__ "(" TODOLINE ") : BUG : " _msg)
