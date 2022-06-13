/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace gin;

//==============================================================================
slToneAudioProcessorEditor::slToneAudioProcessorEditor (slToneAudioProcessor& p)
    : gin::ProcessorEditor (p), toneProcessor (p)
{
    addAndMakeVisible (&scope);
    
    for (auto pp : p.getPluginParameters())
    {
        ParamComponent* pc;
        
        if (pp->isOnOff())
            pc = new Switch (pp);
        else
            pc = new Knob (pp);
        
        addAndMakeVisible (pc);
        controls.add (pc);
    }
    
    setGridSize (7, 3);
    
    scope.setNumSamplesPerPixel (2);
    scope.setVerticalZoomFactor (1.0f);
    scope.setColour (gin::TriggeredScope::lineColourId, findColour (gin::PluginLookAndFeel::grey45ColourId));
    scope.setColour (gin::TriggeredScope::traceColourId + 0, findColour (gin::PluginLookAndFeel::accentColourId));
    scope.setColour (gin::TriggeredScope::envelopeColourId + 0, juce::Colours::transparentBlack);
    scope.setColour (gin::TriggeredScope::traceColourId + 1, findColour (gin::PluginLookAndFeel::accentColourId));
    scope.setColour (gin::TriggeredScope::envelopeColourId + 1, juce::Colours::transparentBlack);
}

slToneAudioProcessorEditor::~slToneAudioProcessorEditor()
{
}

//==============================================================================
void slToneAudioProcessorEditor::resized()
{
    gin::ProcessorEditor::resized();

    componentForId (PARAM_ENABLE)->setBounds (getGridArea (0, 0));
    componentForId (PARAM_BANDLIMIT)->setBounds (getGridArea (0, 1));
    componentForId (PARAM_FREQ)->setBounds (getGridArea (0, 2));
    
    scope.setBounds (getGridArea (1, 0, 4, 3));
    
    componentForId (PARAM_SINE_LEVEL)->setBounds (getGridArea (5, 0));
    componentForId (PARAM_TRI_LEVEL)->setBounds (getGridArea (5, 1));
    componentForId (PARAM_SQUARE_LEVEL)->setBounds (getGridArea (5, 2));
    componentForId (PARAM_SAW_UP_LEVEL)->setBounds (getGridArea (6, 0));
    componentForId (PARAM_SAW_DN_LEVEL)->setBounds (getGridArea (6, 1));
    componentForId (PARAM_NOISE_LEVEL)->setBounds (getGridArea (6, 2));
}
