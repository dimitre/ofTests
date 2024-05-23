void testSetup() {
	ofSetVerticalSync(0);
	ofSetFrameRate(120);
}

void testDraw() {
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 40);
}
