#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(24);
	ofBackground(255);
	ofSetWindowShape(200,200);
	ofSetWindowPosition(100, 0);
//	ofSetLogLevel(OF_LOG_VERBOSE);
    
    client.connect("192.168.99.100:4040");
	
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = 115200;
	//serial.setup(1, baud); //open the first device
	//serial.setup("COM4", baud); // windows example
	//serial.setup("/dev/tty.usbserial-FTG7QFLS", baud); // mac osx example
	serial.setup("/dev/ttyUSB0", baud); //linux example
	
	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 4);
    
    
        client.addListener(this);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // we want to read the 52 bytes
    int bytesRequired = 100;
    unsigned char bytes[bytesRequired];
    int bytesRemaining = bytesRequired;

    bool inPayload = false;
    std::string payload = "";

    int arrayOffset = 0;	
    // loop until we've read everything
    while ( bytesRemaining > 0 )
    {
        // check for data
        if ( serial.available() > 0 ){
            // try to read - note offset into the bytes[] array, this is so
            // that we don't overwrite the bytes we already have
            int bytesArrayOffset = bytesRequired - bytesRemaining;
            int result = serial.readBytes( &bytes[bytesArrayOffset],
                                          bytesRemaining );
            if( bytesArrayOffset > 52 ){
		arrayOffset = bytesArrayOffset - (52 - bytesArrayOffset);
	    }
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
		//serial.flush();
		cout << "flushing";
            }
            else
            {
                // we read some data!
                bytesRemaining -= result;
                for(int i = arrayOffset; i<bytesArrayOffset; i++){
                    cout << "bytes: " << ofToHex( bytes[i] ) << "\n";
		    /*
		    if ( ofToHex( bytes[i] ) == "0a" ) {
			inPayload = !inPayload;
		    }*/
		    if( inPayload && payload == "" && ofToHex( bytes[i] ) == "0a" ){
			serial.flush(true, true);
			//serial.drain();
			cout << "flushed";
		    } else if( inPayload && payload !="" && ofToHex( bytes[i] )=="0a" ){
			cout << payload << endl;
			payload = "";
			//serial.flush();
			return;
			inPayload = false;
			
		    } else if ( inPayload ) {
			payload += ofToHex( bytes[i] ) ;
		    }

		    if ( ofToHex( bytes [i] ) == "0a" ){
			inPayload = !inPayload;
		    }
                }
                //cout << "end stream with " << payload << "\n";
		// serial.flush();
            }
            
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
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

