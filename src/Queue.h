/*
  Flutter is a lightweight wireless library for embedded systems.
  Copyright (c) 2015 Flutter Wireless. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  The license is also available here:
  https://www.gnu.org/licenses/lgpl-2.1.html
*/

#ifndef Queue_h
#define Queue_h

#include "Arduino.h"

#define QUEUESIZE			(128)

class Queue
{
public:
	Queue();
	~Queue();

	int read();
	int peek(size_t at) const;
	boolean write(byte);

	void clear();
	size_t capacity() const;

	/* this returns how much space is left in the queue */
	size_t bytesAvailable() const;

	/* this is basically a 'size' function */
	size_t bytesEnd() const;

protected:
	byte array[QUEUESIZE];
	size_t readptr, writeptr;
};

#endif
