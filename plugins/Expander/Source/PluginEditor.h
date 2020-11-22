/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ExpanderAudioProcessorEditor : public gin::ProcessorEditor,
                                     private gin::Parameter::Listener
{
public:
    ExpanderAudioProcessorEditor (ExpanderAudioProcessor&);
    ~ExpanderAudioProcessorEditor() override;

    //==============================================================================
    void resized() override;
    void parameterChanged (gin::Parameter* param) override;

private:
    ExpanderAudioProcessor& proc;

    gin::DynamicsMeter meter {proc.expander};
    gin::TriggeredScope scope {proc.fifo};

    gin::LevelMeter inputMeter {proc.expander.getInputTracker()};
    gin::LevelMeter outputMeter {proc.expander.getOutputTracker()};
    gin::LevelMeter reductionMeter {proc.expander.getReductionTracker(), {-30, 0}};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExpanderAudioProcessorEditor)
};
