/*
  ==============================================================================

    FreqTextLabel.cpp
    Created: 2 Dec 2020 7:53:08pm
    Author:  羽翼深蓝Wings

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FreqTextLabel.h"

//==============================================================================
FreqTextLabel::FreqTextLabel(VerticalLine &v) : verticalLine(v)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    mFrequency = -1;
    mState = false;
    setEditable(true);
}

FreqTextLabel::~FreqTextLabel()
{
}

void FreqTextLabel::paint (juce::Graphics& g)
{
    g.setColour (COLOUR1.withAlpha(0.2f));
    //g.setColour (juce::Colours::white);
    g.fillAll();
    g.setColour (COLOUR1);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setFont (14.0f * mScale);
    g.drawText (static_cast<juce::String>(mFrequency) + " Hz", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void FreqTextLabel::resized()
{
}

void FreqTextLabel::setFreq(int freq)
{
    mFrequency = freq;
}

int FreqTextLabel::getFreq()
{
    return mFrequency;
}

void FreqTextLabel::setScale(float scale)
{
    mScale = scale;
}
