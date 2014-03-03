#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){
    
    s=10.0; // taille des points représentants les serveurs
    
    ofSetFrameRate(60.0);
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    
    ofVec3f p_temp;
    
    ofVec3f computer,s_computer;
    
    ofFloatColor ofcolor;
    
    ofxParticleEmitter temp_emitter;
    attracteur.set(950.,250.,0.);
    
    computer.set(950.,270,0.);
    s_computer.set(50.);
    ofcolor.set(0.,0.,255.);
    
    for(int i=0;i<NB_SERVEURS;i++){
        
        temp_emitter.setPosition(ofVec3f((float)(((tabLoca[i][1]+180)/360)*ofGetWidth()),(float)((1-(tabLoca[i][0]+90)/180)*ofGetHeight())));
        temp_emitter.setVelocity(ofVec3f(0.0,50.0));
        temp_emitter.posSpread = ofVec3f(0,0.0);
        temp_emitter.velSpread = ofVec3f(10.0,10.0);
        temp_emitter.life = 100;
        temp_emitter.lifeSpread = 25.0;
        temp_emitter.numPars = 4;
        temp_emitter.color = ofColor(200,50,50);
        temp_emitter.colorSpread = ofColor(50,50,50);
        temp_emitter.size = 32;
        
        tabEmitter.push_back(temp_emitter);
        
        p_temp.x = (float)(((tabLoca[i][1]+180)/360)*ofGetWidth());
        p_temp.y =(float)((1-(tabLoca[i][0]+90)/180)*ofGetHeight());
        p_temp.z = 0.0;
        
        addPoint(p_temp.x,p_temp.y,p_temp.z,0.0);
    }
    

    
    // upload the data to the vbo
	int total = (int)points.size();
	
        // Points représentants les points d'accès internet
    vbo.setVertexData(&points[0], total,GL_DYNAMIC_DRAW);
	vbo.setNormalData(&sizes[0], total, GL_DYNAMIC_DRAW);
    
        //Point représentant l'ordinateur
    vbo_static.setVertexData(&computer, 1, GL_STATIC_DRAW);
    vbo_static.setNormalData(&s_computer, 1, GL_STATIC_DRAW);
    vbo_static.setColorData(&ofcolor, 1, GL_STATIC_DRAW);
    
    // load the shader
#ifdef TARGET_OPENGLES
    shader.load("shaders_gles/shader");
#else
    shader.load("shaders/shader");
#endif
    
    compteur = 0 ;
    
    
    vectorField.allocate(128, 128, 3);
    ofDisableArbTex();
    ofLoadImage(pTex, "p.png");
    ofLoadImage(p1Tex, "p1.png");
    ofLoadImage(p2Tex, "p2.png");
    ofLoadImage(p3Tex, "dot.png");
    
    
    rotAcc = 0;
    gravAcc = 0;
    drag = 0;
    fieldMult = 40.0;
    displayMode = 0;
    for(int j = 0 ; j<5 ;j++){
        randnumber[j]=0;
    }
    ofEnableBlendMode(OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void testApp::update(){
    
    s=30.0;
    ofVec3f computer (950.0,250.0,0.0);

//    for(int y = 0; y < vectorField.getHeight(); y++){
//        for(int x=0; x< vectorField.getWidth(); x++){
//            int index = vectorField.getPixelIndex(x, y);
//            float angle = ofNoise(x/(float)vectorField.getWidth()*4.0, y/(float)vectorField.getHeight()*4.0,ofGetElapsedTimef()*0.05)*TWO_PI*2.0;
//            ofVec2f dir(cos(angle), sin(angle));
//            dir.normalize().scale(ofNoise(x/(float)vectorField.getWidth()*4.0, y/(float)vectorField.getHeight()*4.0,ofGetElapsedTimef()*0.05+10.0));
//            vectorField.setColor(x, y, ofColor_<float>(dir.x,dir.y, 0));
//        }
//    }
    
    float dt = min(ofGetLastFrameTime(), 1.0/10.0);
//    particleSystem.gravitateTo(ofPoint(ofGetWidth()/2,ofGetHeight()/2), gravAcc, 1, 10.0, false);
//    particleSystem.rotateAround(ofPoint(ofGetWidth()/2,ofGetHeight()/2), rotAcc, 10.0, false);
    //particleSystem.applyVectorField(vectorField.getPixels(), vectorField.getWidth(), vectorField.getHeight(), vectorField.getNumChannels(), ofGetWindowRect(), fieldMult);
    if(ofGetMousePressed(2)){
        particleSystem.gravitateTo(ofPoint(mouseX,mouseY), gravAcc, 1, 10.0, false);
    }
    
    particleSystem.update(dt, drag);
    
    
    //tous les 10 tours de calcul :
    if(compteur == 1){
       
        // on diminue la taille des points serveurs
        for(int k=0 ; k < NB_SERVEURS ; k++ ){
            if(sizes[k].x>0 && sizes[k].x!=10){
                updatesize( sizes[k].x - 10.0 , k);
            }
        }
        
        //tableau de nombre aléatoire pour piocher un point serveur
        for(int i = NB_SERVEURS - 1; i > 0 ; i--){
            randnumber[i]=randnumber[i-1];
            }
        randnumber[0] = (int) rand()%NB_SERVEURS;
        compteur = 0;
   
    }
    compteur++;
   
    particleSystem.addParticles(tabEmitter[randnumber[0]]);
    
    // La taille du point tiré augment en fonction de combien de fois il est apparu dans les 1000 dernier tour de calcul
    for(int j = 1 ; j < 1000 ; j++){
        if(randnumber[0] == randnumber[j]){
            s+=10;
        }
    
    }
    
    // on actualise la taille du point tiré
    updatesize( s , randnumber[0] );
    
    // les particules émisent sont attirés par l'endroit ou il y a l'ordinateur
    particleSystem.attractTo(attracteur, 500, 25, true);
    
    
//    for (int i = 0 ; i < 5 ; i++){
//        particleSystem.addParticles(tabEmitter[randnumber[i]]);
//    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    glDepthMask(GL_FALSE);
    
    ofSetColor(255, 0, 0);
    
    // this makes everything look glowy :)
    
	ofEnablePointSprites();
    
    shader.begin();
    //camera.begin();
    p3Tex.bind();
    vbo.draw(GL_POINTS, 0, (int)points.size());
    vbo_static.draw(GL_POINTS, 0 ,1);
	p3Tex.unbind();
    shader.end();
    
   
    glDepthMask(GL_TRUE);

    
    
//      ofNoFill();
//      ofSetCircleResolution(180);
//      ofSetColor(0, 0, 255);
//      ofCircle(ofGetWidth()/2, ofGetHeight()/2, 20);
    

    
    ofSetLineWidth(2.0);
    if (displayMode == 1) {
        particleSystem.draw(pTex);
        //particleSystem2.draw(pTex);
    }
    else if(displayMode == 2) {
        particleSystem.draw(p1Tex, p2Tex);
        //particleSystem2.draw(p1Tex,p2Tex);
    }
    else {
        particleSystem.draw();
        //particleSystem2.draw();
    }
    ofSetColor(255, 255, 255);
    //camera.end();
    
    
    ofDrawBitmapString(ofToString(particleSystem.getNumParticles()) + "\n" + ofToString(ofGetFrameRate()) +
                       "\n(G/g) gravitation: " + ofToString(gravAcc) +
                       "\n(R/r) rotational acceleration: " + ofToString(rotAcc) +
                       "\n(F/f) vector field multiplier: " + ofToString(fieldMult) +
                       "\n(D/d) drag constant: " + ofToString(drag) +
                       "\n(v) show vector field" +
                       "\n(1-3) particle display modes" +
                       "Xpos = "+ ofToString(mouseX) +
                       "Ypos = "+ ofToString(mouseY) , 20,20);
    
    
   
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
        case 'r':
            if(rotAcc > 1.1)
                rotAcc /= 1.1;
            break;
        case 'R':
            rotAcc *= 1.1;
            break;
            
        case 'g':
            if(gravAcc > 1.1)
                gravAcc /= 1.1;
            break;
        case 'G':
            gravAcc *= 1.1;
            break;
            
        case 'd':
            if(drag > 0.01)
                drag /= 1.01;
            break;
        case 'D':
            drag *= 1.01;
            if(drag > 1.0) drag = 1.0;
            break;
        case 'f':
            if(fieldMult > 0.1)
                fieldMult /= 1.1;
            break;
        case 'F':
            fieldMult *= 1.1;
            break;
        case '1':
            displayMode = 0;
            break;
        case '2':
            displayMode = 1;
            break;
        case '3':
            displayMode = 2;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::addPoint(float x, float y, float z,float size) {
	ofVec3f po (x,y,z);
    points.push_back(po);
	
	// we are passing the size in as a normal x position
	
	sizes.push_back(ofVec3f(size));
}

//--------------------------------------------------------------
// change la taille des points en fonction de la lecture des lieux de serveurs
void testApp::updatesize(float s,int position) {
	sizes[position] = ofVec3f(s);
    vbo.updateNormalData(&sizes[0],(int)sizes.size());
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    }

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
//    tabLoca[5].setPosition(ofVec3f(0,h/3));
//    leftEmitter.setPosition(ofVec3f(0,h/3));
//    rightEmitter.setPosition(ofVec3f(w-1,h*2/3));
//    topEmitter.setPosition(ofVec3f(w*2/3,0));
//    botEmitter.setPosition(ofVec3f(w/3,h-1));
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
