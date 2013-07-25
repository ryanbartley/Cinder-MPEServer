#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "MPEServer.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderTCPServerApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    MPE::MPEServerRef mpe;
};

void CinderTCPServerApp::setup()
{
}

void CinderTCPServerApp::mouseDown( MouseEvent event )
{
}

void CinderTCPServerApp::update()
{
}

void CinderTCPServerApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( CinderTCPServerApp, RendererGl )
