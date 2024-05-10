static float r2x (float a, float m) { return m * cos(ofDegToRad(a)); }
static float r2y (float a, float m) { return m * sin(ofDegToRad(a)); }


struct relogio {
	ofFbo fbo;
	ofTrueTypeFont type;

	void setup() {
		fbo.allocate(30, 30, GL_RGB);
		//	bool ofTrueTypeFont::load(const filesystem::path &filename, int fontsize, bool _bAntiAliased=true, bool _bFullCharacterSet=true, bool makeContours=false, float simplifyAmt=0.3f, int dpi=0)

//		type.load("DINNextW1G-Medium.otf", 9, false, true, true);
		type.load("DINNextW1G-Regular.otf", 9, false, true, true);
	}
	
	void draw2() {
		ofFill();
		type.drawStringAsShapes("23:59", 0, 50);
		
		type.drawString("23:59", 0, 60);
	}

	void draw() {
		fbo.begin();
		ofClear(0, 255);
		drawRelogio();
		fbo.end();
		ofSetColor(255);
		fbo.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		fbo.draw(0,0, fbo.getWidth() * 4, fbo.getHeight() * 4);
		// drawRelogio();
	}
	
	
	void drawRelogio() {
//		ofPushStyle();
		ofPushMatrix();
		ofNoFill();
		ofTranslate(fbo.getWidth() * .5, fbo.getHeight() * .5);
		float raio = 14;
		ofDrawCircle(0, 0, raio);
		float angleOffset = -90;
		{
			float t = ofGetHours() + (float)ofGetMinutes()/60.0;
			float a = t * 360.0 / 12.0 + angleOffset;
			float m = raio * 0.5;
			float x = r2x(a, m);
			float y = r2y(a, m);
			ofSetLineWidth(2);
			ofDrawLine(0, 0, x, y);
			ofSetLineWidth(1);
		}

		{
			float t = ofGetMinutes();
			float a = t * 360.0 / 60.0 + angleOffset;
			float m = raio * 0.8;
			float x = r2x(a, m);
			float y = r2y(a, m);
			ofDrawLine(0, 0, x, y);
		}


		if (2==3)
		{
			for (int t=0; t<12; t++) {
				float a = t * 360.0 / 12.0 + angleOffset;
				float m = 11;
				float x = r2x(a, m);
				float y = r2y(a, m);
				ofDrawCircle(x, y, 0.5);
	//				ofDrawLine(0, 0, x, y);
			}
		}

		if (2==3)
		{
			float t = ofGetSeconds();
			float a = t * 360.0 / 60.0 + angleOffset;
			float m = 13;
			float x = r2x(a, m);
			float y = r2y(a, m);
			ofDrawLine(0, 0, x, y);
		}
		ofPopMatrix();
//		ofPopStyle();
	}



} rel;



struct cairoR {
	shared_ptr<ofBaseGLRenderer> opengl;
	shared_ptr<ofCairoRenderer> cairo;
	ofTexture render;
	void setup() {
		render.allocate(30, 60, GL_RGBA32F);
		opengl = ofGetGLRenderer();
		cairo = make_shared<ofCairoRenderer>();
		ofRectangle rect = ofRectangle(0, 0, render.getWidth(), render.getHeight());

		cairo->setupMemoryOnly(ofCairoRenderer::IMAGE, false, false, rect);
	}
	
	void begin() {
		ofSetCurrentRenderer(cairo);
		ofPushMatrix();
	}
	
	void end() {
		ofPopMatrix();
		cairo->flush();
		render.loadData(cairo->getImageSurfacePixels());
//   render.loadData(cairo->getImageSurfacePixels(), GL_RGBA);
		ofSetCurrentRenderer(opengl, true);

	}
	
	void draw() {
		render.draw(0, 0, render.getWidth()*2, render.getHeight()*2);
	}
	
} cairo;
