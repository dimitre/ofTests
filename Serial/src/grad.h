
struct gradiente {
public:
	
	ofShader shader;

	string vert = R""""(
varying vec2 texcoord0;
varying vec2 texdim0;
varying vec2 texorient0;

void main()
{
	gl_Position = ftransform();
	texcoord0 = vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);
	texdim0 = vec2 (abs(gl_TextureMatrix[0][0][0]),abs(gl_TextureMatrix[0][1][1]));
	texorient0 = vec2 (gl_TextureMatrix[0][0][0]/texdim0.x,gl_TextureMatrix[0][1][1]/texdim0.y);
}

)"""";
	string frag = R""""(

varying vec2 texcoord0;
varying vec2 texdim0;

//varying vec2 texcoord0;
const vec4 c1 = vec4( 1.0, 0.0, 0.5, 1.0 );
const vec4 c2 = vec4( 0.0, 0.0, 0.5, 1.0 );

void main (void) {
//	float m = 1.0 - texcoord0.x;
	vec2 point = texcoord0 / texdim0; //normalize coordinates 0. 1.

//	gl_FragColor = mix(c1, c2, m);
	vec2 xy = point;
	gl_FragColor = vec4(xy.x , xy.y, 0.3, 1.0);
}

)"""";
	ofFbo fbo;

	void setup() {
		fbo.allocate(500, 500, GL_RGBA);
		fbo.begin();
		ofClear(127, 255);
		fbo.end();
		reload();
//		shader.setupShaderFromSource( GL_VERTEX_SHADER, vert );
//		shader.setupShaderFromSource( GL_FRAGMENT_SHADER, frag );
//		shader.bindDefaults();
//		shader.linkProgram();
	}
	
	
	void draw() {
		shader.begin();
		shader.setUniform1f("tempo", ofGetElapsedTimef() * .1);
		shader.setUniform1f("angle", ofGetElapsedTimef() * 0.2);
		shader.setUniform1f("mult", ofMap(sin(ofGetElapsedTimef()*0.2), -1, 1, .5, 2.0));
		shader.setUniform2f("outputDimensions", 500.0, 500.0);
		fbo.draw(50, 50);
//		ofDrawRectangle(100, 100, 500, 500);
		shader.end();
	}
	
	void reload() {
		shader.load("grad");
	}
	
} grad;
