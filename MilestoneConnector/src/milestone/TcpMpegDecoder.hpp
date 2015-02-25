/*
 * MpegDecoder.hpp
 *
 *  Created on: Sep 28, 2014
 *      Author: lakindu
 */

#ifndef MPEGDECODER_HPP_
#define MPEGDECODER_HPP_

#include <vector>
//#include "../tcpsocket/TcpClient.hpp"
#include "../tcpsocket/Tcpstream.hpp"
#include "../ThreadSafeQueue.hpp"
#include "../Image.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
//using namespace tcpsocket;

namespace milestone
{
class TcpMpegDecoder
{
private:
	vector<unsigned char> currentImageData;
	unsigned int currentContentLength;
	string currentImageTimeStamp;
	TCPStream* tcpClientPtr;
	bool decodeEnable;
	bool stillProcessing;
	const string CONT_LEN_HEADER = "Content-length: ";
	const string CUR_TIME_HEADER = "Current: ";
	unsigned int decodedImageCount;
	void extractStreamHeaderData(const string& streamHeaders);
public:
	TcpMpegDecoder(TCPStream* tcpClientPtr);
	void startDecoding(ThreadSafeQueue<Image>* pQueue);
	void stopDecoding();
	~TcpMpegDecoder();
	bool isStillProcessing();
};
} /* namespace milestone */

#endif /* MPEGDECODER_HPP_ */
