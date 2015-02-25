/*
 * MilestoneConnector.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: marikhu
 */

#include "MilestoneClient.hpp"

namespace milestone {

MilestoneClient::MilestoneClient() : VmsClient()
{}

bool MilestoneClient::init(VmsConnectInfo info) {
//	TcpClient* pTcpClient = new TcpClient(info.sServerIp, info.iServerPort);
	TCPConnector* connector = new TCPConnector();
	TCPStream* stream = connector->connect(info.sServerIp.c_str(), info.iServerPort);
	pDecoder = new TcpMpegDecoder(stream);
	string connectMsg = MilestoneMessage::getConnectMessage(0, info.sUsername,
			info.sPassword, info.sCameraId, info.iWidth, info.iHeight,
			info.bKeepAspectRatio, info.bAllowUpsizing);
//	(*pTcpClient).write(connectMsg);
	stream->send(connectMsg.c_str(), connectMsg.size());
	char line[2048];
	int len = stream->receive(line, sizeof(line));
	line[len] = '\0';
	string connectResponse(line);
	if (MilestoneMessage::isConnectionSuccessful(connectResponse)) {
		string liveMsg = MilestoneMessage::getLiveMessage(1, info.iCompressionRate);
		stream->send(liveMsg.c_str(), liveMsg.size());
		return true;
	}
	return false;
}

int MilestoneClient::produceImageObject(ThreadSafeQueue<Image>* pQueue)
{
	pDecoder->startDecoding(pQueue);
	return 1;
}

bool MilestoneClient::isStillProducingImages()
{
	return pDecoder->isStillProcessing();
}

MilestoneClient::~MilestoneClient()
{}

} /* namespace milestone */
