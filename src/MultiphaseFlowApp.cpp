#include "MultiphaseFlowApp.h"

MultiphaseFlowApp::MultiphaseFlowApp() :
    fluid(this)
{
}

//--------------------------------------------------------------
void MultiphaseFlowApp::setup()
{
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);

}

//--------------------------------------------------------------
void MultiphaseFlowApp::update()
{
    fluid.update();
}

//--------------------------------------------------------------
void MultiphaseFlowApp::draw()
{
    fluid.draw();
}

//--------------------------------------------------------------
void MultiphaseFlowApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void MultiphaseFlowApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void MultiphaseFlowApp::mouseMoved(int x, int y )
{
}

//--------------------------------------------------------------
void MultiphaseFlowApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void MultiphaseFlowApp::mousePressed(int x, int y, int button)
{
    fluid.pourOn = true;
}

//--------------------------------------------------------------
void MultiphaseFlowApp::mouseReleased(int x, int y, int button)
{
    fluid.pourOn = false;
}

//--------------------------------------------------------------
void MultiphaseFlowApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void MultiphaseFlowApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void MultiphaseFlowApp::dragEvent(ofDragInfo dragInfo)
{
}
