#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	ofBackground(255);	
//	ofSetLogLevel(OF_LOG_VERBOSE);
    
    client.connect("echo.websocket.org");
	
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = 115200;
	//serial.setup(1, baud); //open the first device
	//serial.setup("COM4", baud); // windows example
	serial.setup("/dev/tty.usbserial-FTG7QFLS", baud); // mac osx example
	//serial.setup("/dev/ttyUSB0", baud); //linux example
	
	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 4);
    
    
    client.addListener(this);
}

//--------------------------------------------------------------
void ofApp::update(){
    // read
	// now we try to read 3 bytes
	// since we might not get them all the time 3 - but sometimes 0, 6, or something else,
	// we will try to read three bytes, as much as we can
	// otherwise, we may have a "lag" if we don't read fast enough
	// or just read three every time. now, we will be sure to
	// read as much as we can in groups of three...
	/*
	nTimesRead = 0;
	nBytesRead = 0;
	int nRead  = 0;  // a temp variable to keep count per read
	
	unsigned char bytesReturned[3];
	
	memset(bytesReadString, 0, 4);
	memset(bytesReturned, 0, 3);
	
	while( (nRead = serial.readBytes( bytesReturned, 3)) > 0){
		nTimesRead++;
		nBytesRead = nRead;
	};
		
	memcpy(bytesReadString, bytesReturned, 3);*/
	
    
    // we want to read the 52 bytes
    int bytesRequired = 52;
    unsigned char bytes[bytesRequired];
    int bytesRemaining = bytesRequired;
    // loop until we've read everything
    while ( bytesRemaining > 0 )
    {
        // check for data
        if ( serial.available() > 0 )
        {
            // try to read - note offset into the bytes[] array, this is so
            // that we don't overwrite the bytes we already have
            int bytesArrayOffset = bytesRequired - bytesRemaining;
            int result = serial.readBytes( &bytes[bytesArrayOffset],
                                          bytesRemaining );
            
            // check for error code
            if ( result == OF_SERIAL_ERROR )
            {
                // something bad happened
                ofLog( OF_LOG_ERROR, "unrecoverable error reading from serial" );
                // bail out
                break;
            }
            else if ( result == OF_SERIAL_NO_DATA )
            {
                // nothing was read, try again
            }
            else
            {
                // we read some data!
                bytesRemaining -= result;
                for(int i = 0; i<bytesArrayOffset; i++){
                    cout << "bytes: " << ofToHex( bytes[i] ) << "\n";
                }
                cout << "end stream" << "\n";
            }
            
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (nBytesRead > 0){
		ofSetColor(0);
	} else {
		ofSetColor(220);
	}/*
	string msg;
	msg += "click to test serial:\n";
	msg += "read: " + ofToString(bytesReadString) + "\n";
    if(ofToHex(bytesReadString) != "00000000"){
        cout << bytesReadString << "\n";
    }*/
    ofDrawBitmapString(client.isConnected() ? "Client is connected" : "Client disconnected :(", 10,50);
    //ofDrawBitmapString(msg, 10, 80);
}
//--------------------------------------------------------------
void ofApp::onConnect( ofxLibwebsockets::Event& args ){
    cout<<"on connected"<<endl;
}

//--------------------------------------------------------------
void ofApp::onOpen( ofxLibwebsockets::Event& args ){
    cout<<"on open"<<endl;
}

//--------------------------------------------------------------
void ofApp::onClose( ofxLibwebsockets::Event& args ){
    cout<<"on close"<<endl;
}

//--------------------------------------------------------------
void ofApp::onIdle( ofxLibwebsockets::Event& args ){
    cout<<"on idle"<<endl;
}

//--------------------------------------------------------------
void ofApp::onMessage( ofxLibwebsockets::Event& args ){
    cout<<"got message "<<args.message<<endl;
}

//--------------------------------------------------------------
void ofApp::onBroadcast( ofxLibwebsockets::Event& args ){
    cout<<"got broadcast "<<args.message<<endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}

