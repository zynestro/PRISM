#include "PluginProcessor.h"
#include "PluginEditor.h"

PRISMAudioProcessor::PRISMAudioProcessor()
: AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                 .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
  apvts(*this, nullptr, "Params", createParameterLayout())
{}

PRISMAudioProcessor::~PRISMAudioProcessor() {}

const juce::String PRISMAudioProcessor::getName() const { return "Project SQ-3"; }
bool PRISMAudioProcessor::acceptsMidi() const { return false; }
bool PRISMAudioProcessor::producesMidi() const { return false; }
bool PRISMAudioProcessor::isMidiEffect() const { return false; }
double PRISMAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int PRISMAudioProcessor::getNumPrograms() { return 1; }
int PRISMAudioProcessor::getCurrentProgram() { return 0; }
void PRISMAudioProcessor::setCurrentProgram(int) {}
const juce::String PRISMAudioProcessor::getProgramName(int) { return {}; }
void PRISMAudioProcessor::changeProgramName(int, const juce::String&) {}

void PRISMAudioProcessor::prepareToPlay(double, int) {}
void PRISMAudioProcessor::releaseResources() {}
bool PRISMAudioProcessor::isBusesLayoutSupported(const juce::AudioProcessor::BusesLayout& layouts) const
{
    auto in = layouts.getMainInputChannelSet();
    auto out = layouts.getMainOutputChannelSet();
    if (in == juce::AudioChannelSet::disabled() || out == juce::AudioChannelSet::disabled()) return false;
    return in == out;
}

void PRISMAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals snd;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto ch = totalNumInputChannels; ch < totalNumOutputChannels; ++ch) buffer.clear(ch, 0, buffer.getNumSamples());

    auto* tiltParam = apvts.getRawParameterValue("tilt");
    auto* widthParam = apvts.getRawParameterValue("width");
    auto* driveParam = apvts.getRawParameterValue("drive");
    auto W = widthParam->load();
    auto D = driveParam->load();

    auto numSamples = buffer.getNumSamples();
    if (getTotalNumOutputChannels() >= 2)
    {
        auto* L = buffer.getWritePointer(0);
        auto* R = buffer.getWritePointer(1);
        for (int i = 0; i < numSamples; ++i)
        {
            auto M = 0.5f * (L[i] + R[i]);
            auto S = 0.5f * (L[i] - R[i]);
            S *= (float)W;
            auto Lin = M + S;
            auto Rin = M - S;
            auto xL = Lin * (float)D;
            auto xR = Rin * (float)D;
            auto yL = std::tanh(xL);
            auto yR = std::tanh(xR);
            L[i] = yL;
            R[i] = yR;
        }
    }
}

juce::AudioProcessorEditor* PRISMAudioProcessor::createEditor() { return new PRISMAudioProcessorEditor(*this); }
bool PRISMAudioProcessor::hasEditor() const { return true; }

void PRISMAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PRISMAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr) apvts.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessorValueTreeState::ParameterLayout PRISMAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back(std::make_unique<juce::AudioParameterFloat>("tilt", "Tilt", juce::NormalisableRange<float>(-1.0f, 1.0f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("width", "Width", juce::NormalisableRange<float>(0.0f, 2.0f), 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("drive", "Drive", juce::NormalisableRange<float>(0.0f, 1.0f), 0.0f));
    return { params.begin(), params.end() };
}

juce::AudioProcessorValueTreeState& PRISMAudioProcessor::getAPVTS() { return apvts; }

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PRISMAudioProcessor();
}
