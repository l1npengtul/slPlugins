/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

using namespace juce::dsp;

class PluginEditor;

#define PARAM_SAMPLES_PER_PIXEL     "samplesPerPixel"
#define PARAM_VERTICAL_ZOOM         "zoom"
#define PARAM_VERTICAL_OFFSET_L     "offset_l"
#define PARAM_VERTICAL_OFFSET_R     "offset_r"
#define PARAM_TRIGGER_CHANNEL       "trigger_chan"
#define PARAM_TRIGGER_MODE          "trigger_mode"
#define PARAM_TRIGGER_RUN           "trigger_run"
#define PARAM_TRIGGER_RESET         "trigger_reset"
#define PARAM_TRIGGER_LEVEL         "trigger_level"
#define PARAM_TRIGGER_POS           "trigger_pos"

//==============================================================================
/**
*/
class PluginProcessor : public gin::Processor
{
public:
    //==============================================================================
    PluginProcessor();
    ~PluginProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void numChannelsChanged() override;
    
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================    
    gin::AudioFifo fifo;

private:    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};
