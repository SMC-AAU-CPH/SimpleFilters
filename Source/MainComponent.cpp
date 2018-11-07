/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
//#include <math.h>
//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize(800, 600);

    // specify the number of input and output channels that we want to open
    setAudioChannels(0, 2);

    setWantsKeyboardFocus(true);
    addKeyListener(this);

    addAndMakeVisible(frequencySlider);
    frequencySlider.setRange(50, 5000.0);      // [1]
    frequencySlider.setTextValueSuffix(" Hz"); // [2]
    frequencySlider.addListener(this);         // [3]

    addAndMakeVisible(frequencyLabel);
    frequencyLabel.setText("Frequency", dontSendNotification);
    frequencyLabel.attachToComponent(&frequencySlider, true); // [4]

    addAndMakeVisible(gainSlider);
    gainSlider.setRange(0.0, 1.0);        // [1]
    gainSlider.setTextValueSuffix(" Db"); // [2]
    gainSlider.addListener(this);         // [3]

    addAndMakeVisible(gainLabel);
    gainLabel.setText("Amplitude", dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, true); // [4]

    addAndMakeVisible(qSlider);
    qSlider.setRange(0.5, 10.0);      // [1]
    qSlider.setTextValueSuffix(" Q"); // [2]
    qSlider.addListener(this);        // [3]

    addAndMakeVisible(qLabel);
    qLabel.setText("Resonance", dontSendNotification);
    qLabel.attachToComponent(&qSlider, true); // [4]
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    T = 1.0 / sampleRate;

    filter.setSampleRate(sampleRate);
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
    auto gain = gainSlider.getValue();
    auto cutoff = frequencySlider.getValue();
    auto Q = qSlider.getValue();
    

    filter.setCutoff(cutoff);
    //double wd = 2.0 * double_Pi * cutoff;
    //double wa = (2.0 / T) * tan(wd * T / 2.0);
    //double g = wa * T / 2.0;
    //double R = 1.0 / (2 * Q);
    //auto G = g / (1 + g);
    //double G = 1.0 / (1.0 + 2.0 * R * g + g * g);
    // Your audio-processing code goes here!
    for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
    {
        float *const channelData = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

        if (channel == 0) // only mono right now
        {
            for (int i = 0; i < bufferToFill.buffer->getNumSamples(); i++)
            {
                /* One pole ZDF Filter
                // Make noise
                float input = (2 * r.nextFloat() - 1) * 0.5 * gain;
                
                // Filter
                double v = (input - state)*G; 
                double output = v + state; 
                state = v + output; 

                // Output
                channelData[i] = input - output;
                */
                /* SVF 
                // Make noise
                float input = (2 * r.nextFloat() - 1) * 0.5 * gain;

                // Filter
                double yHP = (input - s1 * (2 * R + g) - s2) * G;
                double yBP = yHP * g + s1;
                double yLP = yBP * g + s2;

                double output = yLP;
                // update state
                s1 = yHP * g + yBP;
                s2 = yBP * g + yLP;

                // Output
                channelData[i] = output;*/

                // Make noise
                float input = (2 * r.nextFloat() - 1) * 0.5 * gain;
                // Output
                channelData[i] = filter.process(input);
            }
        }
        else // copy left to right channel
        {
            memcpy(channelData,
                   bufferToFill.buffer->getReadPointer(0),
                   bufferToFill.numSamples * sizeof(float));
        }
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint(Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    auto sliderLeft = 120;
    frequencySlider.setBounds(sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    gainSlider.setBounds(sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
    qSlider.setBounds(sliderLeft, 80, getWidth() - sliderLeft - 10, 20);
}

void MainComponent::mouseDown(const MouseEvent &e)
{
    std::cout << "Mouse pressed: ";
    std::cout << "x: " << e.getScreenX() << " y:" << e.getScreenY() << "\n";
}
void MainComponent::mouseDrag(const MouseEvent &e)
{
}
void MainComponent::mouseUp(const MouseEvent &e)
{
}

void MainComponent::sliderValueChanged(Slider *slider)
{
    //slider->setValue(slider->getValue());
}

bool MainComponent::keyStateChanged(bool isKeyDown, Component *originatingComponent)
{
    if (KeyPress::isKeyCurrentlyDown(' ')) // check for space
    {
        std::cout << "Key down"
                  << "\n";
    }
    else
    {
        std::cout << "Key up"
                  << "\n";
    }

    return 0;
}

bool MainComponent::keyPressed(const KeyPress &key, Component *originatingComponent)
{
    //std::cout << key.getTextDescription() << "\n";

    switch (key.getKeyCode())
    {
    case 'A':
        std::cout << key.getTextDescription() << "\n";
        break;
    case 'W':
        std::cout << key.getTextDescription() << "\n";
        break;
    case 'S':
        std::cout << key.getTextDescription() << "\n";
        break;
    case ' ':
        std::cout << key.getTextDescription() << "\n";
        break;
    }
    return 1;
}
