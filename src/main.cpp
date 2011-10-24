#include "ofMain.h"
#include "MultiphaseFlowApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main(int argc, char* argv[] )
{
    ofAppGlutWindow window;
    ofSetupOpenGL(&window, 465, 465, OF_WINDOW);
    ofRunApp(new MultiphaseFlowApp());
    return EXIT_SUCCESS;
}
