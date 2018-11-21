/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

using namespace juce::dsp;

class SFXAudioProcessorEditor;
//==============================================================================
class SFXAudioProcessor : public gin::GinProcessor
{
public:
    //==============================================================================
    SFXAudioProcessor();
    ~SFXAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    void stateUpdated() override;
    void updateState() override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

private:
    //==============================================================================
    
    CriticalSection lock;    
    Component::SafePointer<SFXAudioProcessorEditor> editor;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SFXAudioProcessor)
};
