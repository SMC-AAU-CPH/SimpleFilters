/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DSP.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent, public KeyListener, public Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* slider) override;
private:
    bool keyPressed (const KeyPress &key, Component *originatingComponent) override;
    bool keyStateChanged(bool isKeyDown, Component *originatingComponent) override;

    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;
    //==============================================================================
    // Your private member variables go here...
    Random r;
    OnePole filter; 
    double state = 0.0;
    double s1 = 0.0;
    double s2 = 0.0;

    double T  = 1.0/44100.0;

    Slider frequencySlider;
    Label frequencyLabel;
    Slider qSlider;
    Label qLabel;
    Slider gainSlider;
    Label gainLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
