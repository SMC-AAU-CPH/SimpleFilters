/*
  ==============================================================================

    DSP.h
    Created: 7 Nov 2018 10:15:42am
    Author:  Nikolaj Andersson

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class OnePole
{
public:
  void setSampleRate(double sampleRate)
  {

    T = 1.0 / sampleRate;
  
  }

  void setCutoff(double cutoff)
  {

    double wd = 2.0 * double_Pi * cutoff;
    double wa = (2.0 / T) * tan(wd * T / 2.0);
    double g = wa * T / 2.0;
    G = g / (1 + g);

  }

  double process(double input)
  {

    double v = (input - state) * G;
    double output = v + state;
    state = v + output;

    return output;
  }

private:
  double G = 0.0; 
  double T = 1.0 / 44100.0;
  double state = 0.0;
};
