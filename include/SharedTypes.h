﻿/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#ifndef IH_SHAREDTYPES_H
#define IH_SHAREDTYPES_H

namespace Interhaptics
{
	namespace HapticBodyMapping
	{	
		enum Operator : int
		{
			Minus = -1,
			Neutral = 0,
			Plus = 1,
		};

		enum LateralFlag : int
		{
			UnknowPosition = -1,
			Global = 0,
			Right = 1,
			Left = 2,
			Center = 3
		};

		enum GroupID : int
		{
			Unknown = -1,
			All = 0,
			Top = 100,
			Down = 101,
			Arm = 200,
			Head = 201,
			Chest = 202,
			Waist = 203,
			Leg = 204,
			Upper_arm = 300,
			Lower_arm = 301,
			Hand = 302,
			Skull = 303,
			Neck = 304,
			Upper_leg = 305,
			Lower_leg = 306,
			Foot = 307,
			Palm = 400,
			Finger = 401,
			Sole = 402,
			Toe = 403,
			Thumb = 500,
			Index = 501,
			Middle = 502,
			Ring = 503,
			Pinky = 504,
			Hallux = 505,
			Index_toe = 506,
			Middle_toe = 507,
			Ring_toe = 508,
			Pinky_toe = 509,
			First = 600,
			Second = 601,
			Third = 602,
		};

		/// <summary>
		/// represent an instruction, useful to find on which bodypart you need to render
		/// </summary>
		struct CommandData {

			// Constructors and heritage --------------------------------------------------------------------

			/// <summary>
			/// recommanded constructor 
			/// </summary>
			/// <param name="_sign">sign of the command (minus or plus)</param>
			/// <param name="_group">group targueted</param>
			/// <param name="_side">side targeted</param>
			CommandData(Operator _sign, GroupID _group, LateralFlag _side = Global)
			{
				Sign = _sign;
				Group = _group;
				Side = _side;
			}

			// Variables ------------------------------------------------------------------------------------

			/// <summary>
			/// sign of the operation (+/-)
			/// </summary>
			Operator Sign;

			/// <summary>
			/// group targeted
			/// </summary>
			GroupID Group;

			/// <summary>
			/// Side targeted
			/// </summary>
			LateralFlag Side;


		};
	}
}

#endif