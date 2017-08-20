/*
 * ad9850.h
 *
 *  Created on: 17 de ago de 2017
 *      Author: jrfo
 */

#ifndef AD9850_H_
#define AD9850_H_

#include "Arduino.h"

namespace hc_sr08 {

class ad9850
{
	public:
  	ad9850();

	void begin(int w_clk, int fq_ud, int data, int reset);
	void setfreq(double f, uint8_t p);
	void down();
	void up();
	void calibrate(double TrimFreq);

	private:
	int W_CLK;
	int FQ_UD;
	int DATA;
	int RESET;
	uint32_t deltaphase;
	uint8_t phase;
	void update();
	void begin_priv();
	void pulse(int pin);
	double calibFreq;
};

} /* namespace hc_sr08 */

#endif /* AD9850_H_ */
