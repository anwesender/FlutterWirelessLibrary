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

#include "Queue.h"

Queue::Queue()
	: readptr(0), writeptr(0)
{
}

Queue::~Queue()
{
}

boolean Queue::write(byte data)
{
	if(((writeptr < readptr) /* Case 1: write < read */
            && ((writeptr + 1) >= readptr))
            || ((writeptr > readptr) /* Case 2: write > read */
                && ((readptr == 0) &&
					(writeptr + 1) == QUEUESIZE))) /* with datasize == 1 (byte) this is fine */
    /* Case 3: write == read means queue is empty => no check necessary. */
	{
		/* queue full */
		return false;
	}

	array[writeptr] = data;
	++writeptr;
	/* hopefully optimized by the compiler to &= (QUEUESIZE - 1) */
	writeptr %= QUEUESIZE;

	return true;
}

void Queue::clear()
{
	readptr = writeptr;
}


int Queue::read()
{
	if(readptr == writeptr)
	{
		/* empty queue */
		return -1;
	}

	byte e;
	e = array[readptr];

	++readptr;
	/* hopefully optimized by the compiler to &= (QUEUESIZE - 1) */
	readptr %= QUEUESIZE;

	return e;

}

int Queue::peek(size_t at) const
{
	if(at >= bytesEnd())
	{
		/* not enough bytes in queue */
		return -1;
	}
	size_t at_p = at + readptr;
	at_p %= QUEUESIZE;
	return array[at_p];
}

size_t Queue::bytesAvailable() const
{
	/* -1 because one element is lost to prevent rolling-over */
	return QUEUESIZE - bytesEnd() - 1;
}

size_t Queue::bytesEnd() const
{
	if(writeptr >= readptr)
	{
		return writeptr - readptr;
	}
	else
	{
		return QUEUESIZE - readptr;
	}
}

size_t Queue::capacity() const
{
	return QUEUESIZE;
}
