#include "PluginEditor.h"
#include "PluginProcessor.h"

PRISMAudioProcessorEditor::PRISMAudioProcessorEditor(PRISMAudioProcessor& p)
: juce::AudioProcessorEditor(&p), processor(p)
{
    tilt.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    width.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    drive.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    tilt.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    width.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    drive.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(tilt);
    addAndMakeVisible(width);
    addAndMakeVisible(drive);

    tiltAtt.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(processor.getAPVTS(), "tilt", tilt));
    widthAtt.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(processor.getAPVTS(), "width", width));
    driveAtt.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(processor.getAPVTS(), "drive", drive));

    setSize(500, 500);
}

PRISMAudioProcessorEditor::~PRISMAudioProcessorEditor() {}

void PRISMAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void PRISMAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    auto deck = area.removeFromBottom(area.getHeight() * 3 / 10);
    auto w = deck.getWidth();
    auto h = deck.getHeight();
    auto szLarge = juce::jmin(h, w) * 0.6f;
    auto szSmall = szLarge * 0.7f;

    auto left = deck.removeFromLeft(deck.getWidth() / 3);
    auto center = deck.removeFromLeft(deck.getWidth() / 2);
    auto right = deck;

    tilt.setBounds(center.withSizeKeepingCentre((int)szLarge, (int)szLarge));
    width.setBounds(left.withSizeKeepingCentre((int)szSmall, (int)szSmall));
    drive.setBounds(right.withSizeKeepingCentre((int)szSmall, (int)szSmall));
}

