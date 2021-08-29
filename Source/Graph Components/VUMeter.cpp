/*
  ==============================================================================

    VUMeter.cpp
    Created: 25 Jan 2021 2:55:04pm
    Author:  羽翼深蓝Wings

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VUMeter.h"
#include "../GUI/InterfaceDefines.h"
#include "../Utility/AudioHelpers.h"

//==============================================================================
VUMeter::VUMeter(FireAudioProcessor* inProcessor)
:   mProcessor(inProcessor),
    mParameterId(-1),
    mCh0Level(0),
    mCh1Level(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

VUMeter::~VUMeter()
{
}

void VUMeter::paint (juce::Graphics& g)
{
    
    g.setColour(COLOUR6);
    const int meterWidth = getWidth() / 3;
    
    // left
    g.fillRect(0, 0, meterWidth, getHeight());
    // right
    g.fillRect(meterWidth * 2, 0, meterWidth, getHeight());
    
    int ch0fill = getHeight() - (getHeight() * mCh0Level);
    int ch1fill = getHeight() - (getHeight() * mCh1Level);
    
    if (ch0fill < 0)
    {
        ch0fill = 0;
    }
    if (ch1fill < 0)
    {
        ch1fill = 0;
    }
    
    g.setColour(COLOUR5);
    
    g.fillRect(0, ch0fill, meterWidth, getHeight());
    g.fillRect(meterWidth * 2, ch1fill, meterWidth, getHeight());
}

void VUMeter::resized()
{
}

void VUMeter::setParameterId(int inParameterId)
{
    mParameterId = inParameterId;
    startTimerHz(15); //30
}

void VUMeter::timerCallback()
{
    float updatedCh0Level = 0.0f;
    float updatedCh1Level = 0.0f;
    switch (mParameterId)
    {
        case 1:
        {
            updatedCh0Level = 0.75f;
            updatedCh1Level = 0.75f;
        }
            break;
            
        case 2:
        {
            updatedCh0Level = 0.35f;
            updatedCh1Level = 0.35f;
        }
            break;
    }
    
    if (updatedCh0Level > mCh0Level)
    {
        mCh0Level = updatedCh0Level;
    }
    else
    {
        mCh0Level = 0.2 * (mCh0Level - updatedCh0Level) + updatedCh0Level; // 0.2 is smoothing coefficient
    }
    
    if (updatedCh1Level > mCh1Level)
    {
        mCh1Level = updatedCh1Level;
    }
    else
    {
        mCh1Level = 0.2 * (mCh1Level - updatedCh1Level) + updatedCh1Level; // 0.2 is smoothing coefficient
    }
    
    mCh0Level = helper_denormalize(mCh0Level);
    mCh1Level = helper_denormalize(mCh1Level);
    
    // repaint if not equal to 0
    if (mCh0Level && mCh1Level)
    {
        repaint();
    }
}
