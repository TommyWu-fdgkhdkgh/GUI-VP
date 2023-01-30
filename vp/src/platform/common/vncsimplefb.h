#ifndef RISCV_VP_VNCSIMPLEFB_H
#define RISCV_VP_VNCSIMPLEFB_H

#include "util/vncserver.h"

#include <systemc>
#include <tlm_utils/simple_target_socket.h>

#include "util/tlm_map.h"

/*
 * Simple framebuffer modules using libvncserver
 * (use with linux simple-framebuffer
 */
class VNCSimpleFB : public sc_core::sc_module {
public:
	tlm_utils::simple_target_socket<VNCSimpleFB> tsock;

	VNCSimpleFB(sc_core::sc_module_name, VNCServer& vncServer);
	~VNCSimpleFB(void);

	SC_HAS_PROCESS(VNCSimpleFB);

private:
	VNCServer& vncServer;
	uint8_t *frameBuffer;
	uint8_t *vncFrameBuffer;
	sc_core::sc_mutex mutex;
	bool areaChanged;
	uint32_t xMin, yMin, xMax, yMax;

	void fb_access_callback(tlm::tlm_generic_payload &trans, sc_core::sc_time);
	void transport(tlm::tlm_generic_payload &, sc_core::sc_time &);

	void areaChangedReset();
	void areaChangedSet(uint32_t addr, uint32_t len);

	void updateScreen();
	void updateProcess();

	vp::map::LocalRouter router = {"VNCSimpleFB"};
};

#endif  /* RISCV_VP_VNCSIMPLEFB_H */
