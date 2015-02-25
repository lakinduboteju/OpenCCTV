/*
 * MilestoneConnector.hpp
 *
 *  Created on: Feb 25, 2015
 *      Author: marikhu
 */

#ifndef MILESTONECONNECTOR_HPP_
#define MILESTONECONNECTOR_HPP_

#include "../VmsClient.hpp"
#include "TcpMpegDecoder.hpp"
//#include "../tcpsocket/TcpClient.hpp"
#include "../tcpsocket/Tcpconnector.hpp"
#include "MilestoneMessage.hpp"

//using namespace tcpsocket;

namespace milestone {

class MilestoneClient : public VmsClient
{
private:
	TcpMpegDecoder* pDecoder;
public:
	MilestoneClient();
	virtual ~MilestoneClient();
	bool init(VmsConnectInfo info);
	int produceImageObject(ThreadSafeQueue<Image>* pQueue);
	bool isStillProducingImages();
};

// the class factories
extern "C" VmsClient* create() {
    return new MilestoneClient;
}

extern "C" void destroy(VmsClient* p) {
    delete p; p = 0;
}

} /* namespace milestone */

#endif /* MILESTONECONNECTOR_HPP_ */
