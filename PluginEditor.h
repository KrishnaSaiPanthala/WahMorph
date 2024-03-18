#include "JuceHeader.h"
#include "PluginProcessor.h"
class AutoWahProjectAudioProcessorEditor : public juce::AudioProcessorEditor,
    private juce::Slider::Listener
{
public:
    AutoWahProjectAudioProcessorEditor(AutoWahProjectAudioProcessor&);
    ~AutoWahProjectAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged(juce::Slider* slider) override;

    AutoWahProjectAudioProcessor& processor;

    juce::Slider releaseKnob; // Change to juce::Slider for knobs
    juce::Label releaseLabel;
    juce::Slider gainKnob; // Change to juce::Slider for knobs
    juce::Label gainLabel;
    juce::Slider sensKnob; // Change to juce::Slider for knobs
    juce::Label sensLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AutoWahProjectAudioProcessorEditor)
};
