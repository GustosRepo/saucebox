cmake_minimum_required(VERSION 3.22)

project(SauceBox VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  juce
  URL https://github.com/juce-framework/JUCE/archive/refs/tags/8.0.2.tar.gz
)
FetchContent_MakeAvailable(juce)

juce_add_plugin(SauceBox
  COMPANY_NAME "808Bytes"
  BUNDLE_ID "com.saucebox.plugin"
  IS_SYNTH FALSE
  NEEDS_MIDI_INPUT FALSE
  NEEDS_MIDI_OUTPUT FALSE
  IS_MIDI_EFFECT FALSE
  EDITOR_WANTS_KEYBOARD_FOCUS FALSE
  COPY_PLUGIN_AFTER_BUILD TRUE
  PLUGIN_MANUFACTURER_CODE SaBx
  PLUGIN_CODE SBox
  FORMATS AU VST3 Standalone
  PRODUCT_NAME "Hot Packet"
)

target_sources(SauceBox
  PRIVATE
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
)

juce_generate_juce_header(SauceBox)

target_compile_definitions(SauceBox
  PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(SauceBox
  PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
  PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)
