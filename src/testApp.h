#pragma once

#include "ofMain.h"
#include "ofxParticles.h"
#include <vector>

#define NB_SERVEURS 255

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void addPoint(float x, float y, float z,float size);
    void updatesize(float size,int position);
    
    ofxParticleSystem particleSystem,particleSystem2;
    int pmouseX, pmouseY;
    ofVec2f pmouseVel;
    vector < ofxParticleEmitter > tabEmitter;
    ofPoint attracteur;
    
    // vector to store all values
    struct pointstruct {
        ofVec3f vecstruct ;
        int nb_point;
    };
    
    vector < ofVec3f > points;
    
    
    vector < ofVec3f > sizes;
    
    ofVbo vbo,vbo_static;

    
    ofShader shader;
    ofEasyCam camera;
    
    float s;
    ofxParticleEmitter mouseEmitter , leftEmitter;
    float rotAcc, gravAcc, fieldMult, drag;
    ofFloatPixels vectorField;
    ofTexture pTex, p1Tex, p2Tex , p3Tex;
    int displayMode;
    int compteur;
    int randnumber[30];
    

    float tabLoca [225][2] = {
        {50.8333,	4.3333},
        {4.7324     ,-74.2642},
        {41.0877    ,-73.7768},
        {40.4495    ,-79.9880},
        {38.7667    ,-90.4201},
        {37.7312    ,-122.382},
        {40.7528    ,-73.9725},
        {41.9491	,-79.4448},
        {40.5516	,-74.4637},
        {42.5669	,-77.1325},
        {42.8509	,-72.5579},
        {42.4585	,-71.2752},
        {36.1473	,-86.7770},
        {41.3807	,-73.3915},
        {40.7148	,-73.7939},
        {40.7214	,-74.0052},
        {43.4312	,-83.9337},
        {37.3239	,-121.914},
        {42.7530	,-71.0861},
        {40.4426	,-79.9770},
        {41.9288	,-87.6315},
        {37.5858	,-77.4888},
        {40.4981	,-74.5245},
        {39.4611	,-83.8172},
        {40.7662	,-73.9862},
        {33.2542	,-96.6863},
        {30.5174	,-97.6304},
        {40.6763	,-73.7752},
        {42.3295	,-83.1908},
        {40.7449	,-73.9782},
        {40.7605	,-73.9933},
        {40.7588	,-73.9680},
        {40.7235	,-73.8612},
        {40.8483	,-73.9725},
        {40.7482	,-73.9068},
        {40.6934	,-75.4712},
        {39.1626	,-76.6316},
        {42.3496	,-71.0746},
        {37.0627	,-76.4052},
        {33.0958	,-117.272},
        {39.9524	,-75.1653},
        {41.8998	,-87.6368},
        {41.0821	,-73.6636},
        {39.2904	,-76.6122},
        {33.0735	,-96.9032},
        { 40.8767	,-74.2974},
        { 35.9216	,-77.7315},
        { 37.2555	,-121.924},
        { 38.9599	,-77.3428},
        { 40.1071	,-82.8981},
        { 29.8729	,-98.0140},
        { 30.2058	,-97.8002},
        { 40.7637	,-73.9727},
        { 39.7930	,-86.2853},
        { 40.7514	,-73.9785},
        { 33.3233	,-111.824},
        { 40.5918	,-74.7050},
        { 40.7553	,-73.9924},
        { 40.1576	,-75.2757},
        { 41.2563	,-89.2220},
        { 34.0607	,-118.403},
        { 39.0649	,-76.9798},
        { 42.1759	,-88.4608},
        { 44.4235	,-73.0854},
        { 32.7825	,-96.8207},
        { 26.4095	,-80.0942},
        { 42.8541	,-70.9521},
        { 40.4835	,-74.4432},
        { 34.0396	,-118.266},
        { 40.5186	,-74.3499},
        { 38.9834	,-74.9025},
        {40.4086	,-3.6922},
        {12.5667,-86.1833 },
        {20.4833,-90.0833 },
        {19.5167,-102.4167},
        {27.3167,-112.2833},
        {22.6167,-102.7667},
        {22.8167,-103.1167},
        {20.4333,-101.7333},
        {22.8500,-105.8000},
        {24.3203,-107.3603},
        {24.5875,-107.3875},
        {19.9333,-105.2500},
        {29.0333,-111.1833},
        {28.8333,-111.9333},
        {32.2641	,74.6634}   ,
        {31.7558	,72.9197}   ,
        {-33.7333,	115.9333}   ,
        {37.1497	,127.1303}  ,
        {-35.3333,	138.4667}   ,
        {37.3694	,127.098}   ,
        {36.1183	,127.375}   ,
        {36.7000	,127.3667}  ,
        {-36.9833,	149.8500}   ,
        {-41.6667,	147.2833}   ,
        {-38.2833,	145.9333}   ,
        {-36.6895,	147.1421}   ,
        {-34.0667,	138.6833}   ,
        {-37.4167,	144.2833}   ,
        {-37.3333,	145.7167}   ,
        {-37.3667,	144.0833}   ,
        {-34.8833,	149.3333}   ,
        {-25.9167,	144.6000}   ,
        {-24.2667,	144.4333}   ,
        {-26.6135,	144.2695}   ,
        {-32.8667,	148.5000}   ,
        {-38.1667,	145.3167}   ,
        {-34.0500,	137.5667}   ,
        {-35.9969,	148.7697}   ,
        {-36.2500,	145.4333}   ,
        {-26.5952,	118.4939}   ,
        {-28.1000,	153.4500}   ,
        {-37.6015,	145.2724}   ,
        {-37.5500,	143.8333}   ,
        {-37.9368,	145.4938}   ,
        {-34.0500,	150.5167}   ,
        {-36.8000,	144.5167}   ,
        {-34.4500,	145.0000}   ,
        {-37.5833,	146.2500}   ,
        {-28.7000,	153.0333},
        {18.6833	,105.4333},
        {10.6500	,106.4833},
        {26.8136	,116.8886},
        {27.4772	,110.9475},
        {22.7837	,113.1445},
        {41.8578	,124.4086},
        {42.5397	,128.9972},
        {10.3833	,105.4500},
        {21.0667	,105.7167},
        {0.3833	,106.3500},
        {4.4167	,116.4667},
        {3.7669	,112.3375},
        {5.5117	,101.2364},
        {0.9500	,75.2333 },
        {4.4793	,112.6421},
        {12.1367	,119.8683},
        {17.7167	,121.9000},
        {19.7500	,105.7167},
        {36.7667	,111.5333},
        {30.4833	,115.9833},
        {37.1936	,122.0511},
        {29.9358	,120.5458},
        {25.5714	,117.2394},
        {36.3275	,114.8197},
        {34.0500	,119.7583},
        {18.6403	,109.6994},
        {26.9772	,109.6964},
        {28.7675	,107.7244},
        {41.2261	,123.0561},
        {35.8722	,119.7547},
        {23.5914	,117.3797},
        {27.3122	,110.4069},
        {29.5375	,121.0061},
        {38.4000	,141.0167},
        {38.5167	,139.7833},
        {38.3011	,140.9375},
        {36.3833	,140.6167},
        {22.7000	,120.4333},
        {24.1433	,120.6814},
        {35.6850	,139.7514},
        {34.6667	,135.5000},
        {47.3151,	5.3646},
        {50.8000,	3.4667},
        {45.3000,	9.6500},
        {49.4594,	12.808},
        {51.1667,	13.400},
        {40.1000,	8.6500},
        {51.2000,	-1.150},
        {44.3428,	0.3937},
        {44.3127,	0.6831},
        {47.2833,	1.7833},
        {50.3061,	3.3047},
        {64.7667,	25.400},
        {43.1234,	-1.978},
        {48.1667,	8.5167},
        {42.7333,	13.850},
        {47.3390,	17.551},
        {51.0833,	-0.933},
        {52.7667,	-1.333},
        {37.9997,	-8.379},
        {42.6995,	-6.512},
        {53.6833,	15.600},
        {45.3000,	10.316},
        {50.9333,	-1.000},
        {43.0597,	22.411},
        {54.0983,	28.332},
        {52.7333,	27.466},
        {48.3667,	15.550},
        {47.3660,	4.9938},
        {50.4765,	2.9093},
        {50.4054,	3.1249},
        {50.2929,	2.9606},
        {46.1489,	4.6247},
        {49.7130,	3.1915},
        {47.1580,	0.9948},
        {45.9510,	0.1172},
        {44.1876,	5.9462},
        {47.3833,	4.1333},
        {44.7484,	4.6749},
        {48.0111,	1.5523},
        {46.6790,	5.2509},
        {48.4983,	1.3100},
        {48.9530,	0.2670},
        {44.4415,	5.0237},
        {46.3336,	3.4485},
        {49.0068,	1.2768},
        {48.1667,	5.9515},
        {44.3858,	5.9432},
        {43.7173,	4.7846},
        {45.1167,	2.4667},
        {43.3061,	1.0174},
        {47.2022,	0.6350},
        {48.2825,	2.3283},
        {47.9557,	2.3093},
        {47.9696,	3.0709},
        {44.3167,	3.3000},
        {43.1500,	1.9667},
        {48.5126,	0.3550},
        {47.9014,	-3.440},
        {44.3702,	5.2677},
        {47.8678,	7.4517},
        {45.3333,	0.3000},
        {44.0641,	0.4283},
        {44.3913,	1.3174},
        {45.7115,	3.2729},
        
        
    };



};
