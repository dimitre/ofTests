#include "ofApp.h"

uint8_t data[40] = { 0 };
void ofApp::setup(){
	serial.setup("/dev/cu.usbserial-xel_sipeed0", 9600);
}

void ofApp::update(){
}

void ofApp::draw(){	

}

void ofApp::keyPressed(int key){
	if (key == 'a') {
		string dados = "Shatnara\nEnotyoblame";
		memcpy(&data, &dados, dados.size());
		serial.writeBytes(data, dados.size());
	}
	if (key == 's') {
		string dados = "Yougivelove\nabadname";
		memcpy(&data, &dados, dados.size());
		serial.writeBytes(data, dados.size());
	}
	if (key == 'd') {
//#define XOFFL                   0x53
//#define YOFFL                   0x54
//		{ XOFFL,   0x00 }, /* OFFSET_X[7:0] */
//		{ YOFFL,   0x00 }, /* OFFSET_Y[7:0] */
		uint8_t regs[] = {
			0x53, 0b00011111,
			0x54, 0b00011111
		};
		data[0] = 0xDD;
		memcpy(&data[1], &regs, 4);
		serial.writeBytes(data, 5);
	}
	
}

void ofApp::exit() {
	serial.close();
}
