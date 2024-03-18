# WahMorph 

## Description

WahMorph is a C++ audio plugin developed using the JUCE framework. It implements an auto-wah effect, a type of guitar pedal effect commonly used in music production. The auto-wah effect dynamically adjusts a band-pass filter's center frequency and bandwidth based on the input signal's envelope, creating a "wah" effect that responds to the dynamics of the input signal.

## Building and Running the Project

To build and run the project, follow these steps:

1. Clone the repository to your local machine.
2. Make sure you have the JUCE framework installed.
3. Open the project in your preferred C++ IDE that supports JUCE.
4. Build the project according to your IDE's instructions.
5. Once built, you can use the plugin in your digital audio workstation (DAW) or audio editing software that supports VST or AU plugins.

## Testing

Testing for the AutoWahProject was primarily done through manual testing and listening tests. The plugin was tested with various audio sources to ensure that the auto-wah effect responds accurately to different input signals. Additionally, unit tests were implemented for critical components, such as the envelope follower and filter parameter calculations, to verify their correctness.

## Example
WahMorph plugin serves as a versatile tool for guitarists, allowing them to add expressive effects to their performances and captivate their audience with dynamic soundscapes.


## What Worked and What Did Not
I was able to implement gain,release and sensitivity. Although in the proposal I proposed to do a dynamic cutoff frequency, it proved to be much difficult and was giving me not compiling but runtime errors. For the most part things do what they are supposed to do. Not a huge GUI person and this was my first time coding with JUCE framework so that's a learning curve. Some calculations could be a bit better and future improvements could be that dynamic cutoff frequency now its just a constant value.


## Reflection
The AutoWahProject achieved its intended function of implementing an auto-wah effect using C++ and the JUCE framework. The project successfully responds to the dynamics of the input signal, creating a recognizable "wah" effect. However, there are areas for improvement, such as optimizing filter calculations for better performance and adding more user interface controls for enhanced usability. Overall, I am satisfied with the result after a lot of laborious work, but there is room for further refinement and expansion in future iterations.

