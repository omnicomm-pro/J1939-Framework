/*
 * CanSniffer.h
 *
 *  Created on: Jun 5, 2018
 *      Author: fernado
 */

#ifndef CANSNIFFER_H_
#define CANSNIFFER_H_

#include <vector>

#include "CommonCanReceiver.h"


typedef void (*OnReceiveFramePtr)(const Can::CanFrame& frame, const Utils::TimeStamp& tStamp, const std::string& interface, void* data);
typedef bool (*OnTimeoutPtr)();

namespace Can {

class CanSniffer {
private:
	OnReceiveFramePtr mRcvCB = nullptr;
	OnTimeoutPtr mTimeoutCB = nullptr;
	void* mData = nullptr;		//Data to be passed to the OnReceiveFramePtr callback
	std::vector<CommonCanReceiver*> mReceivers;

public:
	CanSniffer(OnReceiveFramePtr recvCB, OnTimeoutPtr timeoutCB, void* data = nullptr);
	virtual ~CanSniffer();
	void addReceiver(CommonCanReceiver *receiver) { mReceivers.push_back(receiver); }
	void sniff(u32 timeout);
	void setFilters(std::set<CanFilter> filters);
	int getNumberOfReceivers() const { return mReceivers.size(); }

};

} /* namespace Can */

#endif /* CANSNIFFER_H_ */
