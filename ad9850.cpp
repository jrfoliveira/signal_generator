/*
 * ad9850.cpp
 *
 *  Created on: 17 de ago de 2017
 *      Author: jrfo
 */

#include "ad9850.h"

namespace hc_sr08 {

ad9850::ad9850() {

}

void ad9850::begin(int w_clk, int fq_ud, int data, int reset) {
	W_CLK = w_clk;
	FQ_UD = fq_ud;
	DATA = data;
	RESET = reset;
	deltaphase = 0;
	phase = 0;
	calibFreq = 125000000;
	begin_priv();
}

void ad9850::begin_priv() {
	pinMode(W_CLK, OUTPUT);
	pinMode(FQ_UD, OUTPUT);
	pinMode(DATA, OUTPUT);
	pinMode(RESET, OUTPUT);

	pulse(RESET);
	pulse(W_CLK);
	pulse(FQ_UD);
}

void ad9850::update() {

    for (int i=0; i<4; i++, deltaphase>>=8) {
     shiftOut(DATA, W_CLK, LSBFIRST, deltaphase & 0xFF);
    }
    shiftOut(DATA, W_CLK, LSBFIRST, phase & 0xFF);
    pulse(FQ_UD);
}


void ad9850::setfreq(double f, uint8_t p) {
	deltaphase = f * 4294967296.0 / calibFreq;
	phase = p << 3;
	update();
}


void ad9850::down() {
	pulse(FQ_UD);
	shiftOut(DATA, W_CLK, LSBFIRST, 0x04);
	pulse(FQ_UD);
}


void ad9850::up() {
	update();
}


void ad9850::calibrate(double TrimFreq)
{
	calibFreq = TrimFreq;
}


void ad9850::pulse(int pin) {
	digitalWrite(pin, HIGH);
	digitalWrite(pin, LOW);
}

} /* namespace hc_sr08 */
