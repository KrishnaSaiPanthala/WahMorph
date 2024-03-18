#pragma once

#include "JuceHeader.h"
#include <cmath>

//==============================================================================
/**
*/
class AutoWahProjectAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    AutoWahProjectAudioProcessor();
    ~AutoWahProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    // Access methods for private members
    float getGain() const { return gain_; }
    void setGain(float newGain) { gain_ = newGain; }

    float getSensitivity() const { return sensitivity_; }
    void setSensitivity(float newSensitivity) { sensitivity_ = newSensitivity; }

    float getRelease() const { return release_; }
    void setRelease(float value) { release_ = value; }

private:
    //==============================================================================
    juce::OwnedArray<juce::IIRFilter> filters_;
    juce::Array<float> envelopes_;

    double minFrequency_, maxFrequency_, minBandwidth_, maxBandwidth_, attackTime_, Q_, attackCoefficient_, releaseCoefficient_, centerFrequency_, bandwidth_;
    float gain_, sensitivity_;

    const double PI_ = std::atan(1.0) * 4;

    float release_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AutoWahProjectAudioProcessor)
};
