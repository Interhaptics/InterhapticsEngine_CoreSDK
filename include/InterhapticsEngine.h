/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#ifndef IH_ENGINE_PUBLIC
#define IH_ENGINE_PUBLIC

#include <vector>
#include <include/SharedTypes.h>

using namespace Interhaptics::HapticBodyMapping;

extern "C"
{

	#pragma region Engine Control

	/// <summary>
	/// Initializes the different components and modules of the Interhaptics Engine:
	/// - Haptic Material Manager: module in charge of loading and storing haptic effects
	/// - Human Avatar Manager: module in charge of mapping between device, human avatar, and experience
	/// - Haptic Event Manager: module in charge of the control of haptic sources
	/// </summary>
	/// <returns>Always true even if a module is not properly initialized.</returns>
	DLLExport bool Init();

	/// <summary>
	/// Cleans the different components and modules of the Interhaptics Engine.
	/// To be called before the application is quit.
	/// </summary>
	DLLExport void Quit();

	/// <summary>
	/// Sets the global rendering intensity factor for the whole engine.
	/// </summary>
	/// <param name="_intensity">Positive value. 0 is nothing. Base value is 1.</param>
	/// <returns></returns>
	DLLExport void SetGlobalIntensity(double _intensity);

	/// <summary>
	/// Gets the global rendering intensity factor for the whole engine.
	/// </summary>
	/// <returns>The global intensity. -1 if mixer is not initialized.</returns>
	DLLExport double GetGlobalIntensity();

	/// <summary>
	/// Adds the content of an .haps file to the Interhaptics Engine for future use.
	/// </summary>
	/// <param name="_content">JSON content of the .haps file to be loaded. Needs to follow Interhaptics .haps format.</param>
	/// <returns>ID of the haptic effect to be used in other engine calls. -1 if loading failed.</returns>
	DLLExport int AddHM(const char* _content);

	/// <summary>
	/// Create an effect using _amplitude, pitch parameters and transients data
	/// </summary>
	/// <param name="_amplitude">Array of amplitude values. Should be formatted as Time - Value - Time - Value. Value is between 0 and 1</param>
	/// <param name="_amplitudeSize">Size of the amplitude array</param>
	/// <param name="_pitch">Array of frequency values. Should be formatted as Time - Value - Time - Value. Value is between 0 and 1</param>
	/// <param name="_pitchSize">Size of the frequency array</param>
	/// <param name="_pitchMin">Minimum frequency range</param>
	/// <param name="_pitchMax">Maximum frequency range</param>
	/// <param name="_transient">Array of transients values. Should be formatted as Time - Amp - Frequency - Time - Amp - Frequency. Value and Frequency are between 0 and 1</param>
	/// <param name="_transientSize">Size of the transient array</param>
	/// <param name="_isLooping">Should the source loop the effect</param>
	/// <returns>ID of the haptic source created.</returns>
	DLLExport int AddParametricEffect(double* _amplitude, int _amplitudeSize, double* _pitch, int _pitchSize, double _pitchMin, double _pitchMax, double* _transient, int _transientSize, bool _isLooping);

	DLLExport bool DeleteHM(int _HMaterialID);

	/// <summary>
	/// Replaces the content of an already loaded haptic effect. 
	/// Useful when the ID of the haptic effect needs to be persistent. 
	/// </summary>
	/// <param name="_hMaterialID">ID of the haptic effect to be replaced.</param>
	/// <param name="_content">JSON content of the .haps file to be loaded. Needs to follow Interhaptisc .haps format.</param>
	/// <returns>true if the effect was properly updated. false otherwise</returns>
	DLLExport bool UpdateHM(int _hMaterialID, const char* _content);

	/// <summary>
	/// Return true if at least one active event targeting the given bodyparts contains transients
	/// </summary>
	/// <param name="_perception">perception to play</param>
	/// <param name="_bodyparts">Ids of bodyparts targeted</param>
	/// <param name="_numberOfBodyparts">size of _bodyparts</param>
	/// <returns>true if at least one transient in a file</returns>
	DLLExport bool TransientsPlayedOnThoseBodyparts(int _perception, int* _bodyparts, int _numberOfBodyparts);

	#pragma endregion


	#pragma region Engine Events

	/// <summary>
	/// Starts the rendering playback of a haptic source. 
	/// Sets the starting time to 0 + different offsets. 
	/// If the event is already playing, it restarts with the new offets.
	/// If the source does not already exist, it will be created.
	/// </summary>
	/// <param name="_hMaterialID">ID of the source to play. Same as the attached haptic effect.</param>
	/// <returns></returns>
	DLLExport void PlayEvent(int _hMaterialID, double _vibrationOffset, double _textureOffset, double _stiffnessOffset);

	/// <summary>
	/// Stops the rendering playback of a haptic source.
	/// </summary>
	/// <param name="_hMaterialID">ID of the source to stop. Same as the attached haptic effect.</param>
	/// <returns></returns>
	DLLExport void StopEvent(int _hMaterialID);

	/// <summary>
	/// Stops the rendering playback of all haptic sources.
	/// </summary>
	/// <returns></returns>
	DLLExport void StopAllEvents(); 

	/// <summary>
	/// Adds a target in range of the source. 
	/// The Interhaptics Engine will remap device endpoints and in-range target
	/// to the device management layer for haptic playback. 
	/// </summary>
	/// <param name="_hMaterialID">ID of the source to add a target to. Same as the attached haptic effect.</param>
	/// <param name="_target">Vector of CommandData to build a target. A target contains a group of bodyparts, lateral flags, and exclusion flags.</param>
	/// <returns></returns>
	DLLExport void AddTargetToEvent(int _hMaterialID, std::vector<CommandData> _target);

	/// <summary>
	/// Marshal version of the AddTargetToEvent function.
	/// Adds a target in range of the source. 
	/// The Interhaptics Engine will remap device endpoints and in-range target
	/// to the device management layer for haptic playback. 
	/// </summary>
	/// <param name="_hMaterialID">ID of the source to add a target to. Same as the attached haptic effect.</param>
	/// <param name="_target">Pointer of CommandData to build a target. A target contains a group of bodyparts, lateral flags, and exclusion flags. Memory must be allocated before calling this entrypoint.</param>
	/// <param name="_size">Size of the _target array.</param>
	/// <returns></returns>
	DLLExport void AddTargetToEventMarshal(int _hMaterialID, CommandData* _target, int _size);

	/// <summary>
	/// Removes a target from a source range. 
	/// The Interhaptics Engine will remap device endpoints and in-range target
	/// to the device management layer for haptic playback. 
	/// </summary>
	/// <param name="_hMaterialID">ID of the source to remove a target from. Same as the attached haptic effect.</param>
	/// <param name="_target">Vector of CommandData to build a target. A target contains a group of bodyparts, lateral flags, and exclusion flags. Only perfectly matching targets will be removed.</param>
	/// <returns></returns>
	DLLExport void RemoveTargetFromEvent(int _hMaterialID, std::vector<CommandData> _target);

	/// <summary>
	/// Marshal version of the RemoveTargetFromEvent function.
	/// Removes a target from a source range. 
	/// The Interhaptics Engine will remap device endpoints and in-range target
	/// to the device management layer for haptic playback. 
	/// </summary>
	/// <param name="_hMaterialID">ID of the source to remove a target from. Same as the attached haptic effect.</param>
	/// <param name="_target">Vector of CommandData to build a target. A target contains a group of bodyparts, lateral flags, and exclusion flags. Only perfectly matching targets will be removed. Memory must be allocated before calling this entrypoint.</param>
	/// <param name="_size">Size of the _target array.</param>
	/// <returns></returns>
	DLLExport void RemoveTargetFromEventMarshal(int _hMaterialID, CommandData* _target, int _size);

	/// <summary>
	/// Removes all targets from a source range.
	/// The Interhaptics Engine will remap device endpoints and in-range target
	/// to the device management layer for haptic playback. 
	/// </summary>
	/// <param name="_hMaterialID">ID of the source to remove a targets. Same as the attached haptic effect.</param>
	/// <returns></returns>
	DLLExport void RemoveAllTargetsFromEvent(int _hMaterialID);

	/// <summary>
	/// To be called in the application main loop to trigger the rendering of all haptic buffer
	/// at a specific time. The Interhaptics Engine will compare the current time with the last
	/// know value to build buffer large enough to cover frame drops. 
	/// Can be called from the main thread or in a parallel loop. 
	/// Must be called at least once before triggering the device update event. 
	/// </summary>
	/// <param name="_curTime">Current time in seconds.</param>
	/// <returns></returns>
	DLLExport void ComputeAllEvents(double _curTime);

	/// <summary>
	/// Updates spatial positions for a specific source target.
	/// </summary>
	/// <param name="_hMaterialID">ID of the source. Same as the attached haptic effect.</param>
	/// <param name="_target">Vector of CommandData to build a target. A target contains a group of bodyparts, lateral flags, and exclusion flags. Only perfectly matching targets will be updated.</param>
	/// <param name="_texturePosition">New texture position.</param>
	/// <param name="_stiffnessPosition">New stiffness position.</param>
	/// <returns></returns>
	DLLExport void UpdateEventPositions(int _hMaterialID, std::vector<CommandData> _target, double _texturePosition, double _stiffnessPosition);

	/// <summary>
	/// Marshal version of the UpdateEventPositions function.
	/// Updates spatial positions for a specific source target.
	/// </summary>
	/// <param name="_hMaterialID">ID of the source. Same as the attached haptic effect.</param>
	/// <param name="_target">Pointer of CommandData to build a target. A target contains a group of bodyparts, lateral flags, and exclusion flags. Only perfectly matching targets will be updated. Memory must be allocated before calling this function.</param>
	/// <param name="_size">Size of the _target array.</param>
	/// <param name="_texturePosition">New texture position.</param>
	/// <param name="_stiffnessPosition">New stiffness position.</param>
	/// <returns></returns>
	DLLExport void UpdateEventPositionsMarshal(int _hMaterialID, CommandData* _target, int _size, double _texturePosition, double _stiffnessPosition);

	/// <summary>
	/// Sets the offsets for a specific haptic source.
	/// </summary>
	/// <param name="_hMaterialID">ID of the source. Same as the attached haptic effect.</param>
	/// <returns></returns>
	DLLExport void SetEventOffsets(int _hMaterialID, double _vibrationOffset, double _textureOffset, double _stiffnessOffet);

	/// <summary>
	/// Sets the haptics intensity factor for a specific source.
	/// </summary>
	/// <param name="_hMaterialID">ID of the source. Same as the attached haptic effect.</param>
	/// <param name="_intensity">Intensity factor value. Always clamped above 0.</param>
	/// <returns></returns>
	DLLExport void SetEventIntensity(int _hMaterialID, double _intensity);

	/// <summary>
	/// Sets the loop flag for a specific source
	/// </summary>
	/// <param name="_hMaterialID">ID of the source. Same as the attached haptic effect.</param>
	/// <param name="_numberOfLoop">Number of loop for the event. <= 1 is one iteration.</param>
	/// <returns></returns>
	DLLExport void SetEventLoop(int _hMaterialID, int _numberOfLoop);

	/// <summary>
	/// Sets the haptics intensity factor for a specific target of a source.
	/// </summary>
	/// <param name="_hMaterialID">ID of the source. Same as the attached haptic effect.</param>
	/// <param name="_target">Target to change intensity.</param>
	/// <param name="_intensity">Intensity factor value. Always clamped above 0.</param>
	/// <returns></returns>
	DLLExport void SetTargetIntensity(int _hMaterialID, std::vector<CommandData> _target, double _intensity);

	/// <summary>
	/// Sets the haptics intensity factor for a specific target of a source.
	/// </summary>
	/// <param name="_hMaterialID">ID of the source. Same as the attached haptic effect.</param>
	/// <param name="_target">Target to change intensity.</param>
	/// <param name="_intensity">Intensity factor value. Always clamped above 0.</param>
	/// <returns></returns>
	DLLExport void SetTargetIntensityMarshal(int _hMaterialID, CommandData* _target, int _size, double _intensity);

	/// <summary>
	/// Clears all inactive sources from the memory. 
	/// Inactive sources are kept in memory to avoid deletion and creation when playing and stopping a source. 
	/// </summary>
	/// <returns></returns>
	DLLExport void ClearInactiveEvents();

	/// <summary>
	/// Clears all active sources from the memory.
	/// Deleted sources can be recreated by calling the PlayEvent function.
	/// </summary>
	/// <returns></returns>
	DLLExport void ClearActiveEvents();

	/// <summary>
	/// Clears a specific haptic source whether it is active or not. 
	/// </summary>
	/// <param name="_hMaterialID">ID of the source. Same as the attached haptic effect.</param>
	/// <returns></returns>
	DLLExport void ClearEvent(int _hMaterialID);

	#pragma endregion
}

#endif