#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

class PRISMAudioProcessor;

class PRISMAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    PRISMAudioProcessorEditor(PRISMAudioProcessor&);
    ~PRISMAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    PRISMAudioProcessor& processor;
    juce::Slider tilt, width, drive;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> tiltAtt, widthAtt, driveAtt;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PRISMAudioProcessorEditor)
};
