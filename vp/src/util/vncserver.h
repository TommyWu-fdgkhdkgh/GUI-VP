#ifndef RISCV_VP_VNCSERVER_H
#define RISCV_VP_VNCSERVER_H

#include <stdint.h>
#include <rfb/rfb.h>

class VNCServer {
public:
	VNCServer(void);
	~VNCServer(void);

	bool start(void);
	void stop(void);

	void setScreenProperties(int width, int height, int bitsPerSample,
			int samplesPerPixel, int bytesPerPixel) {

		this->width = width;
		this->height = height;
		this->bitsPerSample = bitsPerSample;
		this->samplesPerPixel = samplesPerPixel;
		this->bytesPerPixel = bytesPerPixel;
	}

	inline rfbScreenInfoPtr getScreen(void) {
		return rfbScreen;
	}

	/* only allowed between start() and stop() */
	inline uint8_t *getFrameBuffer(void) {
		return (uint8_t*) rfbScreen->frameBuffer;
	}

	inline void markRectAsModified(int x1, int y1, int x2, int y2) {
		rfbMarkRectAsModified(rfbScreen, x1, y1, x2, y2);
	}

	inline bool isActive(void) {
		return rfbIsActive(rfbScreen);
	}

	/* callbacks */
	enum rfbNewClientAction newClient(rfbClientPtr cl);
	void clientGone(rfbClientPtr cl);

private:
	int width, height, bitsPerSample, samplesPerPixel, bytesPerPixel;
	rfbScreenInfoPtr rfbScreen;
};

#endif  /* RISCV_VP_VNCSERVER_H */
