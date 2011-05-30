//
// "$Id$"
//
// Simple threading API for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

// Inline classes to provide portable support for threads and mutexes.
//
// FLTK does not use this (it has an internal mutex implementation
// that is used if fltk3::lock() is called). This header file's only
// purpose is so we can write portable demo programs. It may be useful
// or an inspiration to people who want to try writing multithreaded
// programs themselves.
//
// FLTK has no multithreaded support unless the main thread calls fltk3::lock().
// This main thread is the only thread allowed to call fltk3::run() or fltk3::wait().
// From then on FLTK will be locked except when the main thread is actually
// waiting for events from the user. Other threads must call fltk3::lock() and
// fltk3::unlock() to surround calls to FLTK (such as to change widgets or
// redraw them).

#ifndef Threads_H
#  define Threads_H

#  if HAVE_PTHREAD_H
// Use POSIX threading...

#    include <pthread.h>

namespace fltk3 {

typedef pthread_t Thread;

static int create_thread(Thread& t, void *(*f) (void *), void* p) {
  return pthread_create((pthread_t*)&t, 0, f, p);
} // create_thread

} // namespace fltk3

#  elif defined(WIN32) && !defined(__WATCOMC__) // Use Windows threading...

#    include <windows.h>
#    include <process.h>

namespace fltk3 {

typedef unsigned long Thread;

static int create_thread(Thread& t, void *(*f) (void *), void* p) {
  return t = (Thread)_beginthread((void( __cdecl * )( void * ))f, 0, p);
} // create_thread

} // namespace fltk3

#  elif defined(__WATCOMC__)
#    include <process.h>

namespace fltk3 {

typedef unsigned long Thread;

static int create_thread(Thread& t, void *(*f) (void *), void* p) {
  return t = (Thread)_beginthread((void(* )( void * ))f, 32000, p);
} // create_thread

} // namespace fltk3

#  endif // !HAVE_PTHREAD_H

#endif // !Threads_h

//
// End of "$Id$".
//
