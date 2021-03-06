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
#ifndef SRC_FLOW_FLOWCACHE_H_
#define SRC_FLOW_FLOWCACHE_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Cache.h" 
#include "Flow.h"
#include <iomanip> // setw
#include <boost/ptr_container/ptr_vector.hpp>

namespace aiengine {

// Simple wrapper for hide the flow management
class FlowCache {
public:
    	explicit FlowCache(): fc_(new Cache<Flow>("FlowCache")) {}
    	virtual ~FlowCache() {}

	static constexpr int flowSize = sizeof(Flow) + sizeof(SharedPointer<Flow>);

	void releaseFlow(const SharedPointer<Flow> &flow) { fc_->release(flow);}
	SharedPointer<Flow> acquireFlow() { return fc_->acquire();}

	void createFlows(int number) { fc_->create(number);}
	void destroyFlows(int number) { fc_->destroy(number);}

        void statistics(std::basic_ostream<char> &out) {

		const char *units[] = { "KBytes", "MBytes", "GBytes" };
		const char *unit = "Bytes";
		int alloc_memory = getAllocatedMemory();

		for(auto i: units) {
			if (alloc_memory > 1024) {
				unit = i;
				alloc_memory = alloc_memory / 1024;
			} else {
				break;
			}
		}

		out << "FlowCache statistics" << std::endl;
		out << "\t" << "Total flows:            " << std::setw(10) << getTotalFlows() <<std::endl;
		out << "\t" << "Total allocated:        " << std::setw(9 - std::strlen(unit)) << alloc_memory << " " << unit <<std::endl;
		out << "\t" << "Total acquires:         " << std::setw(10) << getTotalAcquires() <<std::endl;
		out << "\t" << "Total releases:         " << std::setw(10) << getTotalReleases() <<std::endl;
		out << "\t" << "Total fails:            " << std::setw(10) << getTotalFails() <<std::endl;
	}

        void statistics() { statistics(std::cout);}

	int32_t getTotalFlows() const { return fc_->getTotal();}
	int32_t getTotalAcquires() const { return fc_->getTotalAcquires();}
	int32_t getTotalReleases() const { return fc_->getTotalReleases();}
	int32_t getTotalFails() const { return fc_->getTotalFails();}

	int32_t getCurrentUseMemory() const { return fc_->getCurrentUseMemory(); }
	int32_t getAllocatedMemory() const { return (getTotalFlows() * flowSize); }
	int32_t getAllocatedMemory(int value) const { return (value * flowSize); }
	
        void setDynamicAllocatedMemory(bool value) { fc_->setDynamicAllocatedMemory(value); }
        bool isDynamicAllocatedMemory() const { return fc_->isDynamicAllocatedMemory(); }

#if defined(STAND_ALONE_TEST) || defined(TESTING)
	void setGenerateBadAllocException(bool value) { fc_->generate_bad_alloc_exception = value; }
#endif
private:
	Cache<Flow>::CachePtr fc_;
};

typedef std::shared_ptr<FlowCache> FlowCachePtr;
typedef std::weak_ptr<FlowCache> FlowCachePtrWeak;

} // namespace aiengine

#endif  // SRC_FLOW_FLOWCACHE_H_
