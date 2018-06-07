/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FormulaAudioProcessorEditor  : public gin::GinAudioProcessorEditor
{
public:
    FormulaAudioProcessorEditor (FormulaAudioProcessor&);
    ~FormulaAudioProcessorEditor();

    //==============================================================================
    void resized() override;
    
    drow::TriggeredScope scope;

private:
    FormulaAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FormulaAudioProcessorEditor)
};
