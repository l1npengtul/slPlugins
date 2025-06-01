/*
  ==============================================================================

    Voice.cpp
    Created: 4 Jul 2019 8:25:21pm
    Author:  Roland Rabien

  ==============================================================================
*/

#include "Voice.h"
#include "PluginProcessor.h"

void Voice::noteStarted()
{
    if (auto p = synth.getPadForNote (currentlyPlayingNote.initialNote))
    {
        if (resamplingFifo != nullptr)
            resamplingFifo->reset();

        p->fromPluginParams();
        sfxr.setSampleRate (44100.0f);
        sfxr.setParams (p->params);
        sfxr.reset (true);
    }
    else
    {
        clearCurrentNote();
    }
}

void Voice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (currentSampleRate == 44100.0)
    {
        float* work = (float*) alloca (size_t (numSamples) * sizeof (float));
        memset (work, 0, size_t (numSamples) * sizeof (float));

        if (sfxr.synthWave (work, 0, numSamples))
            clearCurrentNote();

        for (int ch = 0; ch < outputBuffer.getNumChannels(); ch++)
            juce::FloatVectorOperations::add (outputBuffer.getWritePointer (ch, startSample), work, numSamples);
    }
    else
    {
        auto work = (float*) alloca (size_t (numSamples) * sizeof (float));
        while (resamplingFifo->samplesReady() < numSamples)
        {
            memset (work, 0, size_t (numSamples) * sizeof (float));

            if (sfxr.synthWave (work, 0, numSamples))
                clearCurrentNote();

            float* rawData[] = { work, nullptr };
            juce::AudioSampleBuffer temp (rawData, 1, numSamples);

            resamplingFifo->pushAudioBuffer (temp);
        }

        {
            memset (work, 0, size_t (numSamples) * sizeof (float));
            float* rawData[] = { work, nullptr };
            juce::AudioSampleBuffer temp (rawData, 1, numSamples);

            resamplingFifo->popAudioBuffer (temp);

            for (int ch = 0; ch < outputBuffer.getNumChannels(); ch++)
                juce::FloatVectorOperations::add (outputBuffer.getWritePointer (ch, startSample), work, numSamples);
        }
    }
}
