/*
 * AIEngine a new generation network intrusion detection system.
 *
 * Copyright (C) 2013-2018  Luis Campo Giralte
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Ryadnology Team; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Ryadnology Team, 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 * Written by Luis Campo Giralte <me@ryadpasha.com> 
 *
 */
#ifndef SRC_JAICALLBACK_H_
#define SRC_JAICALLBACK_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>

namespace aiengine {

#if defined(JAVA_BINDING)

class Flow;
// Abstract class for inherit for Callbacks in Java
class JaiCallback {
public:
        JaiCallback() {}
        virtual ~JaiCallback() {}

	virtual void call(Flow *flow) = 0;
};

#endif

} // namespace aiengine

#endif  // SRC_JAICALLBACK_H_

