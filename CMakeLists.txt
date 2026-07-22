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

set(SAUCE_SHARED_SOURCES
  Source/PluginEditor.cpp
  Source/PluginEditor.h
  Source/PluginProcessor.cpp
  Source/PluginProcessor.h
  Source/Products/ActiveProduct.h
  Source/Products/ProductCatalog.h
  Source/Products/DripSauce/DripSauceManifest.h
  Source/Products/DripSauce/DripSaucePresets.h
  Source/Products/DripSauce/DripSauceTheme.h
  Source/Products/ExtraSauce/ExtraSauceManifest.h
  Source/Products/ExtraSauce/ExtraSaucePresets.h
  Source/Products/ExtraSauce/ExtraSauceTheme.h
  Source/Products/GlueSauce/GlueSauceManifest.h
  Source/Products/GlueSauce/GlueSaucePresets.h
  Source/Products/GlueSauce/GlueSauceTheme.h
  Source/Products/HotPacket/HotPacketManifest.h
  Source/Products/HotPacket/HotPacketPresets.h
  Source/Products/HotPacket/HotPacketTheme.h
  Source/Products/LightSauce/LightSauceManifest.h
  Source/Products/LightSauce/LightSaucePresets.h
  Source/Products/LightSauce/LightSauceTheme.h
  Source/Products/SauceBox/SauceBoxManifest.h
  Source/Products/SauceBox/SauceBoxPresets.h
  Source/Products/SauceBox/SauceBoxTheme.h
  Source/Products/SecretSauce/SecretSauceManifest.h
  Source/Products/SecretSauce/SecretSaucePresets.h
  Source/Products/SecretSauce/SecretSauceTheme.h
  Source/Products/SweetSauce/SweetSauceManifest.h
  Source/Products/SweetSauce/SweetSaucePresets.h
  Source/Products/SweetSauce/SweetSauceTheme.h
  Source/Products/ThickSauce/ThickSauceManifest.h
  Source/Products/ThickSauce/ThickSaucePresets.h
  Source/Products/ThickSauce/ThickSauceTheme.h
)

function(add_sauce_product)
  set(options COPY_PLUGIN_AFTER_BUILD)
  set(one_value_args TARGET PRODUCT_NAME BUNDLE_ID MANUFACTURER_CODE PLUGIN_CODE PRODUCT_DEFINE)
  cmake_parse_arguments(SAUCE_PRODUCT "${options}" "${one_value_args}" "" ${ARGN})

  juce_add_plugin(${SAUCE_PRODUCT_TARGET}
    COMPANY_NAME "808Bytes"
    BUNDLE_ID "${SAUCE_PRODUCT_BUNDLE_ID}"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD ${SAUCE_PRODUCT_COPY_PLUGIN_AFTER_BUILD}
    PLUGIN_MANUFACTURER_CODE ${SAUCE_PRODUCT_MANUFACTURER_CODE}
    PLUGIN_CODE ${SAUCE_PRODUCT_PLUGIN_CODE}
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "${SAUCE_PRODUCT_PRODUCT_NAME}"
  )

  target_sources(${SAUCE_PRODUCT_TARGET}
    PRIVATE
      ${SAUCE_SHARED_SOURCES}
  )

  juce_generate_juce_header(${SAUCE_PRODUCT_TARGET})

  target_compile_definitions(${SAUCE_PRODUCT_TARGET}
    PUBLIC
      JUCE_WEB_BROWSER=0
      JUCE_USE_CURL=0
      ${SAUCE_PRODUCT_PRODUCT_DEFINE}
  )

  target_link_libraries(${SAUCE_PRODUCT_TARGET}
    PRIVATE
      juce::juce_audio_utils
      juce::juce_dsp
    PUBLIC
      juce::juce_recommended_config_flags
      juce::juce_recommended_lto_flags
      juce::juce_recommended_warning_flags
  )
endfunction()

add_sauce_product(
  TARGET SauceBox
  PRODUCT_NAME "Hot Packet"
  BUNDLE_ID "com.saucebox.plugin"
  MANUFACTURER_CODE SaBx
  PLUGIN_CODE SBox
  PRODUCT_DEFINE SAUCE_PRODUCT_HOT_PACKET=1
  COPY_PLUGIN_AFTER_BUILD
)

add_sauce_product(
  TARGET SecretSauce
  PRODUCT_NAME "Secret Sauce"
  BUNDLE_ID "com.808bytes.secretsauce"
  MANUFACTURER_CODE EByt
  PLUGIN_CODE SeSc
  PRODUCT_DEFINE SAUCE_PRODUCT_SECRET_SAUCE=1
  COPY_PLUGIN_AFTER_BUILD
)
