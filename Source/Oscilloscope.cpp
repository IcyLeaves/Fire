/*
  ==============================================================================

    Oscilloscope.cpp
    Created: 25 Oct 2020 7:26:35pm
    Author:  羽翼深蓝Wings

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscilloscope.h"


//==============================================================================
Oscilloscope::Oscilloscope(FireAudioProcessor &p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
}

Oscilloscope::~Oscilloscope()
{
}

void Oscilloscope::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.setColour (juce::Colours::green);

    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    float drive = processor.getNewDrive();
    int colour_r = 244;
    int colour_g = (208 - drive * 2 < 0) ? 0 : (208 - drive * 2);
    int colour_b = 63;
    
    juce::ColourGradient grad(juce::Colour(colour_r, colour_g, colour_b), getWidth() / 2, getHeight() / 2,
                              COLOUR6, 0, getHeight() / 2, true);
    g.setGradientFill(grad);
    
    juce::AudioBuffer<float> history = processor.getHistoryBuffer();
    float* dataL = history.getWritePointer (0);
    float* dataR = history.getWritePointer (1);
    
    juce::Path pathL;
    juce::Path pathR;
    
    float amp = getHeight() / 4;
    
    //TODO: this may cause high CPU usage! maybe use i += 2?
    for (int i = 0; i < getWidth(); i++) {

        float valL = dataL[i];
        float valR = dataR[i];
        
        valL = juce::jlimit<float>(-1, 1, valL);
        valR = juce::jlimit<float>(-1, 1, valR);

        if (i == 0)
        {
            pathL.startNewSubPath(0, amp);
            pathL.startNewSubPath(0, amp * 3);
        }
        else
        {
            pathL.lineTo(i, amp - valL * amp);
            pathR.lineTo(i, amp * 3 - valR * amp);
        }
    }

    g.strokePath(pathL, juce::PathStrokeType(2.0));
    g.strokePath(pathR, juce::PathStrokeType(2.0));
    
}

void Oscilloscope::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
