/*
 * SimpleRTPSink.cpp
 *
 *  Created on: Aug 13, 2018
 *      Author: jhb
 */

#include "SimpleRTPSink.h"
#include "strDup.h"

SimpleRTPSink::SimpleRTPSink(UsageEnvironment& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat, unsigned rtpTimestampFrequency,
		char const* sdpMediaTypeString, char const* rtpPayloadFormatName,
		unsigned numChannels, Boolean allowMultipleFramesPerPacket,
		Boolean doNormalMBitRule) :
		MultiFramedRTPSink(env, RTPgs, rtpPayloadFormat, rtpTimestampFrequency,
				rtpPayloadFormatName, numChannels), fAllowMultipleFramesPerPacket(
				allowMultipleFramesPerPacket), fSetMBitOnNextPacket(False) {
	fSDPMediaTypeString = strDup(
			sdpMediaTypeString == NULL ? "unknown" : sdpMediaTypeString);
	fSetMBitOnLastFrames = doNormalMBitRule
			&& strcmp(fSDPMediaTypeString, "audio") != 0;
}

SimpleRTPSink::~SimpleRTPSink() {
	delete[] (char*) fSDPMediaTypeString;
}

SimpleRTPSink*
SimpleRTPSink::createNew(UsageEnvironment& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat, unsigned rtpTimestampFrequency,
		char const* sdpMediaTypeString, char const* rtpPayloadFormatName,
		unsigned numChannels, Boolean allowMultipleFramesPerPacket,
		Boolean doNormalMBitRule) {
	return new SimpleRTPSink(env, RTPgs, rtpPayloadFormat,
			rtpTimestampFrequency, sdpMediaTypeString, rtpPayloadFormatName,
			numChannels, allowMultipleFramesPerPacket, doNormalMBitRule);
}

void SimpleRTPSink::doSpecialFrameHandling(unsigned fragmentationOffset,
		unsigned char* frameStart, unsigned numBytesInFrame,
		struct timeval framePresentationTime, unsigned numRemainingBytes) {
	if (numRemainingBytes == 0) {
		// This packet contains the last (or only) fragment of the frame.
		// Set the RTP 'M' ('marker') bit, if appropriate:
		if (fSetMBitOnLastFrames)
			setMarkerBit();
	}
	if (fSetMBitOnNextPacket) {
		// An external object has asked for the 'M' bit to be set on the next packet:
		setMarkerBit();
		fSetMBitOnNextPacket = False;
	}

	// Important: Also call our base class's doSpecialFrameHandling(),
	// to set the packet's timestamp:
	MultiFramedRTPSink::doSpecialFrameHandling(fragmentationOffset, frameStart,
			numBytesInFrame, framePresentationTime, numRemainingBytes);
}

Boolean SimpleRTPSink::frameCanAppearAfterPacketStart(
		unsigned char const* /*frameStart*/,
		unsigned /*numBytesInFrame*/) const {
	return fAllowMultipleFramesPerPacket;
}

char const* SimpleRTPSink::sdpMediaType() const {
	return fSDPMediaTypeString;
}

