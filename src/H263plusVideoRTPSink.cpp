/*
 * H263plusVideoRTPSink.cpp
 *
 *  Created on: Aug 13, 2018
 *      Author: jhb
 */



#include "H263plusVideoRTPSink.h"

H263plusVideoRTPSink
::H263plusVideoRTPSink(UsageEnvironment& env, Groupsock* RTPgs,
		       unsigned char rtpPayloadFormat,
		       u_int32_t rtpTimestampFrequency)
  : VideoRTPSink(env, RTPgs, rtpPayloadFormat, rtpTimestampFrequency, "H263-1998") {
}

H263plusVideoRTPSink::~H263plusVideoRTPSink() {
}

H263plusVideoRTPSink*
H263plusVideoRTPSink::createNew(UsageEnvironment& env, Groupsock* RTPgs,
				unsigned char rtpPayloadFormat,
				u_int32_t rtpTimestampFrequency) {
  return new H263plusVideoRTPSink(env, RTPgs, rtpPayloadFormat, rtpTimestampFrequency);
}

Boolean H263plusVideoRTPSink
::frameCanAppearAfterPacketStart(unsigned char const* /*frameStart*/,
				 unsigned /*numBytesInFrame*/) const {
  // A packet can contain only one frame
  return False;
}

void H263plusVideoRTPSink
::doSpecialFrameHandling(unsigned fragmentationOffset,
			 unsigned char* frameStart,
			 unsigned numBytesInFrame,
			 struct timeval framePresentationTime,
			 unsigned numRemainingBytes) {
  if (fragmentationOffset == 0) {
    // This packet contains the first (or only) fragment of the frame.
    // Set the 'P' bit in the special header:
    unsigned short specialHeader = 0x0400;

    // Also, reuse the first two bytes of the payload for this special
    // header.  (They should both have been zero.)
    if (numBytesInFrame < 2) {
      envir() << "H263plusVideoRTPSink::doSpecialFrameHandling(): bad frame size "
	      << numBytesInFrame << "\n";
      return;
    }
    if (frameStart[0] != 0 || frameStart[1] != 0) {
      envir() << "H263plusVideoRTPSink::doSpecialFrameHandling(): unexpected non-zero first two bytes!\n";
    }
    frameStart[0] = specialHeader>>8;
    frameStart[1] = (unsigned char)specialHeader;
  } else {
    unsigned short specialHeader = 0;
    setSpecialHeaderBytes((unsigned char*)&specialHeader, 2);
  }

  if (numRemainingBytes == 0) {
    // This packet contains the last (or only) fragment of the frame.
    // Set the RTP 'M' ('marker') bit:
    setMarkerBit();
  }

  // Also set the RTP timestamp:
  setTimestamp(framePresentationTime);
}


unsigned H263plusVideoRTPSink::specialHeaderSize() const {
  // There's a 2-byte special video header.  However, if we're the first
  // (or only) fragment of a frame, then we reuse the first 2 bytes of
  // the payload instead.
  return (curFragmentationOffset() == 0) ? 0 : 2;
}


