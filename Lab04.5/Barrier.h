/* Barrier.h --- 
 * 
 * Filename: Barrier.h
 * Description: 
 * Author: Tomas Phelan
 * Maintainer: 
 * Created: Sat Nov  4 20:08:04 2017 (+0000)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Nov  4 20:11:13 2017 (+0000)
 *           By: Tomas Phelan
 *     Update #: 1
 * URL: 
 * Doc URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Code: */
#pragma once
#include <mutex>
#include "Semaphore.h"
/*!
  Barrier Class 
 */
class Barrier{
public:
 	int count;
	int numberOfThreads;
	std::shared_ptr<Semaphore>  mutex;
	std::shared_ptr<Semaphore>  turnstileA;
	std::shared_ptr<Semaphore>  turnstileB;
	void FirstTurnstile();
	void SecondTurnstile();
	Barrier(int count);
	void Wait();
	
};


/* Barrier.h ends here */
