#include "PluginEditor.h"
#include "PluginProcessor.h"


AutoWahProjectAudioProcessorEditor::AutoWahProjectAudioProcessorEditor(AutoWahProjectAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    setSize(600, 600);

    // Sensitivity knob
    sensKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    sensKnob.setRange(1, 4, 0.5);
    sensKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    sensKnob.setPopupDisplayEnabled(true, false, this);
    sensKnob.setTextValueSuffix(" sensitivity");
    sensKnob.setValue(1);
    sensLabel.setText("Sensitivity", juce::dontSendNotification);
    sensLabel.setColour(juce::Label::textColourId, juce::Colours::darkgreen);
    sensLabel.attachToComponent(&sensKnob, true);
    addAndMakeVisible(&sensKnob);
    addAndMakeVisible(&sensLabel);
    sensKnob.addListener(this);

    // Release knob
    releaseKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    releaseKnob.setRange(0.001, 0.01, 0.001);
    releaseKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    releaseKnob.setPopupDisplayEnabled(true, false, this);
    releaseKnob.setTextValueSuffix(" release");
    releaseKnob.setValue(processor.getGain());
    releaseLabel.setText("Release", juce::dontSendNotification);
    releaseLabel.setColour(juce::Label::textColourId, juce::Colours::darkgreen);
    releaseLabel.attachToComponent(&releaseKnob, true);
    addAndMakeVisible(&releaseKnob);
    addAndMakeVisible(&releaseLabel);
    releaseKnob.addListener(this);

    // Gain knob
    gainKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainKnob.setRange(1, 30, 1);
    gainKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    gainKnob.setPopupDisplayEnabled(true, false, this);
    gainKnob.setTextValueSuffix(" gain");
    gainKnob.setValue(processor.getGain());
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.setColour(juce::Label::textColourId, juce::Colours::darkgreen);
    gainLabel.attachToComponent(&gainKnob, true);
    addAndMakeVisible(&gainKnob);
    addAndMakeVisible(&gainLabel);
    gainKnob.addListener(this);
}

void AutoWahProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &releaseKnob)
        processor.setRelease(releaseKnob.getValue());
    else if (slider == &gainKnob)
        processor.setGain(gainKnob.getValue());
    else if (slider == &sensKnob)
        processor.setSensitivity(sensKnob.getValue());
}

AutoWahProjectAudioProcessorEditor::~AutoWahProjectAudioProcessorEditor()
{
}

void AutoWahProjectAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::skyblue); // Fill the background with sky blue color
    g.setColour(juce::Colours::black);
    g.setFont(25.0f);
    g.drawText("WahMorph", getLocalBounds(), juce::Justification::centred, true); // Draw centered text
}

void AutoWahProjectAudioProcessorEditor::resized()
{
    const int sliderWidth = 100;
    const int sliderHeight = 100;
    const int gap = 60; // Adjust the gap between sliders as needed

    // Adjust component positions and sizes
    releaseKnob.setBounds(80, 200, sliderWidth, sliderHeight);
    gainKnob.setBounds(releaseKnob.getRight() + gap, 200, sliderWidth, sliderHeight);
    sensKnob.setBounds(gainKnob.getRight() + gap, 200, sliderWidth, sliderHeight);
}
