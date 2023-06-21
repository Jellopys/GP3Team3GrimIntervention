// Fill out your copyright notice in the Description page of Project Settings.


#include "TileType.h"

FTileTypeArrays::FTileTypeArrays()
{
	LevelOneU = {ETileType::LevelOne, ETileType::StairUp, ETileType::StairLeft, ETileType::StairRight};
	LevelOneD = {ETileType::LevelOne, ETileType::StairDown, ETileType::StairLeft, ETileType::StairRight};
	LevelOneL = {ETileType::LevelOne, ETileType::StairLeft, ETileType::StairUp, ETileType::StairDown};
	LevelOneR = {ETileType::LevelOne, ETileType::StairRight, ETileType::StairUp, ETileType::StairDown};
	
	LevelTwoU = {ETileType::LevelTwo, ETileType::LevelOne, ETileType::StairDown, ETileType::StairLeft, ETileType::StairRight};
	LevelTwoD = {ETileType::LevelTwo, ETileType::LevelOne, ETileType::StairUp, ETileType::StairLeft, ETileType::StairRight};
	LevelTwoL = {ETileType::LevelTwo, ETileType::LevelOne, ETileType::StairRight, ETileType::StairUp, ETileType::StairDown};
	LevelTwoR = {ETileType::LevelTwo, ETileType::LevelOne, ETileType::StairLeft, ETileType::StairUp, ETileType::StairDown};

	StairUpU = {ETileType::LevelTwo};
	StairUpD = {ETileType::LevelOne};
	StairUpL = {ETileType::LevelOne, ETileType::LevelTwo, ETileType::StairLeft};
	StairUpR = {ETileType::LevelOne, ETileType::LevelTwo, ETileType::StairRight};

	StairDownU = {ETileType::LevelOne};
	StairDownD = {ETileType::LevelTwo};
	StairDownL = {ETileType::LevelOne, ETileType::LevelTwo, ETileType::StairLeft};
	StairDownR = {ETileType::LevelOne, ETileType::LevelTwo, ETileType::StairRight};

	StairLeftU = {ETileType::LevelOne, ETileType::LevelTwo, ETileType::StairUp};
	StairLeftD = {ETileType::LevelOne, ETileType::LevelTwo, ETileType::StairDown};
	StairLeftL = {ETileType::LevelTwo};
	StairLeftR = {ETileType::LevelOne};

	StairRightU = {ETileType::LevelOne, ETileType::LevelTwo, ETileType::StairUp};
	StairRightD = {ETileType::LevelOne, ETileType::LevelTwo, ETileType::StairDown};
	StairRightL = {ETileType::LevelOne};
	StairRightR = {ETileType::LevelTwo};

	VoidU = {ETileType::LevelTwo, ETileType::LevelOne, ETileType::StairDown, ETileType::StairLeft, ETileType::StairRight};
	VoidD = {ETileType::LevelTwo, ETileType::LevelOne, ETileType::StairUp, ETileType::StairLeft, ETileType::StairRight};
	VoidL = {ETileType::LevelTwo, ETileType::LevelOne, ETileType::StairRight, ETileType::StairUp, ETileType::StairDown};
	VoidR = {ETileType::LevelTwo, ETileType::LevelOne, ETileType::StairLeft, ETileType::StairUp, ETileType::StairDown};
}
