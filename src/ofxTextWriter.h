/*
 *  ofxTextWriter.h
 *  CFText
 *
 *  Created by Artem Titoulenko on 1/6/10.
 *  Copyright 2010 Artem Titoulenko. All rights reserved.
 *
 */

class ofxTextWriter {
	string text;
	float timeToRender;
	float timeBegan;
	bool  timeSet, done;
	
public:
	
	//for use if you just want a blank TextWriter, for whatever reason.
	void init() {
		text = "";
		timeToRender = 0;
		timeSet = done = false;
	}
	
	ofxTextWriter() {
		init();
	}
	
	ofxTextWriter(string _text, float _timeToRender = 5) {
		text = _text;
		timeToRender= _timeToRender;
		done = false;
	}
	
	string whatToRender() {
		if(!done) {
			if(!timeSet) {
				timeBegan = ofGetElapsedTimef();
				timeSet = true;
			} 
			
			//Lets not draw it, that's too many resources we dont have.
			//Lets just return what part of the string should be already drawn.
			//That way people can decide what they want to do with it and how.
			int n = (int)((ofGetElapsedTimef() / (timeSet+timeToRender)) * text.length());
			
			if (n + 1 == (int)text.length() ) done = true;
			
			return text.substr(0, min( n, (int)text.length()) ); //lets not access outside the buffer, eh?
		} else {
			return text;
		}
	}
	
	/* -------- HELPER FUNCTIONS --------- */
	void resetTime() {
		timeSet = false;
	}
	
	void setTimeToRender(float _timeToRender) {
		resetTime();
		timeToRender = _timeToRender;
		done = false;
	}
	
	void setTextToRender(string _text) {
		text = _text;
	}
	
	bool isDone() {
		return done;
	}
};