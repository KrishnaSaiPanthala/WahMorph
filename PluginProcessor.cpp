#include "PluginProcessor.h"
#include "PluginEditor.h" 

AutoWahProjectAudioProcessor::AutoWahProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
    // Initialize variables
    minFrequency_ = 400.0;
    maxFrequency_ = 2500.0;
    centerFrequency_ = 1250.0;
    minBandwidth_ = 70.0;
    bandwidth_ = 300.0;
    maxBandwidth_ = 700.0;
    Q_ = 18.0;
    gain_ = 25.0f;
    attackTime_ = 0.001f;
    sensitivity_ = 1.5f;

}

void AutoWahProjectAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    filters_.clear();
    for (int i = 0; i < getTotalNumInputChannels(); ++i) {
        juce::IIRFilter* filter = new juce::IIRFilter();
        filters_.add(filter);
    }
    envelopes_.clear();
    for (int i = 0; i < getTotalNumInputChannels(); ++i)
        envelopes_.add(0.0f);
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AutoWahProjectAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;


#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void AutoWahProjectAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;


    for (int channel = 0; channel < getTotalNumInputChannels(); ++channel) {
        float* channelData = buffer.getWritePointer(channel);

        for (int n = 0; n < buffer.getNumSamples(); ++n) {

            const float x = channelData[n];


            float envelope;
            attackCoefficient_ = std::exp(-1.0f / (attackTime_ * getSampleRate()));
            releaseCoefficient_ = std::exp(-1.0f / (AutoWahProjectAudioProcessor::getRelease() * getSampleRate()));


            if (std::fabs(x) > envelopes_[channel]) {
                envelope = attackCoefficient_ * envelopes_[channel] + (1.0f - attackCoefficient_) * std::fabs(x); // Attack
            }
            else {
                envelope = releaseCoefficient_ * envelopes_[channel] + (1.0f - releaseCoefficient_) * std::fabs(x); // Release
            }

            envelopes_.set(channel, envelope);


            centerFrequency_ = minFrequency_ + (maxFrequency_ - minFrequency_) * envelopes_[channel];
            bandwidth_ = minBandwidth_ + (maxBandwidth_ - minBandwidth_) * envelopes_[channel];
            Q_ = centerFrequency_ / bandwidth_;


            for (int i = 0; i < filters_.size(); ++i) {
                filters_[i]->setCoefficients(juce::IIRCoefficients::makePeakFilter(getSampleRate(), centerFrequency_, Q_, gain_));
            }


            float filtered = filters_[channel]->processSingleSampleRaw(x);
            channelData[n] = sensitivity_ * filtered; // Output
        }
    }
}

void AutoWahProjectAudioProcessor::releaseResources()
{
}

AutoWahProjectAudioProcessor::~AutoWahProjectAudioProcessor()
{
}

const juce::String AutoWahProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AutoWahProjectAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool AutoWahProjectAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool AutoWahProjectAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double AutoWahProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AutoWahProjectAudioProcessor::getNumPrograms()
{
    return 1;
}

int AutoWahProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AutoWahProjectAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String AutoWahProjectAudioProcessor::getProgramName(int index)
{
    return {};
}

void AutoWahProjectAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

juce::AudioProcessorEditor* AutoWahProjectAudioProcessor::createEditor()
{
    return new AutoWahProjectAudioProcessorEditor(*this);
}

bool AutoWahProjectAudioProcessor::hasEditor() const
{
    return true;
}

void AutoWahProjectAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
}

void AutoWahProjectAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AutoWahProjectAudioProcessor();
}