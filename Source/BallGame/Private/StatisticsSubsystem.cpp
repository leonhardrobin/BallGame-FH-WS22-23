// Fill out your copyright notice in the Description page of Project Settings.


#include "StatisticsSubsystem.h"

// *** *** Cube Information *** *** //

FString FMovingCubeInformation::ToCSVLine()
{
	FString Line = "";
	Line.Append(FString::Printf(TEXT("%.2f,"), Size.X));
	Line.Append(FString::Printf(TEXT("%.2f,"), Size.Y));
	Line.Append(FString::Printf(TEXT("%.2f,"), Size.Z));
	Line.Append(FString::Printf(TEXT("%.2f,"), Velocity.X));
	Line.Append(FString::Printf(TEXT("%.2f,"), Velocity.Y));
	Line.Append(FString::Printf(TEXT("%.2f,"), Velocity.Z));
	Line.Append(FString::Printf(TEXT("%.2f,"), InitialDistanceToPlayer));
	Line.Append(FString::Printf(TEXT("%.2f,"), ShotDistanceToPlayer));
	Line.Append(FString::FromInt(NumFailedAttempts) + ","); 
	Line.Append(FString::Printf(TEXT("%.1f\n"), TimeUntilShot));
	
	return Line; 
}

FString FMovingCubeInformation::ToCSVHeadline()
{
	FString Headline = "Cube Size X,Cube Size Y,Cube Size Z,Velocity X,Velocity Y,Velocity Z,Initial Distance To Player,Distance to Player When Shot,Number of Failed Attempts,Time Until Shot\n";
	return Headline; 
}

// *** *** SubSystem *** *** //

void UStatisticsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	M_ID = "";
	M_FilePath = "C:\\BallGameStatistics\\";
	M_Content.Empty();
}

void UStatisticsSubsystem::CacheCubeInfo(FMovingCubeInformation& CubeInfo)
{
	if (M_Content.IsEmpty())
	{
		M_Content.Append(FMovingCubeInformation::ToCSVHeadline());
	}
	M_Content.Append(CubeInfo.ToCSVLine());
}

void UStatisticsSubsystem::WriteCachedCubeInfo()
{
	FString FileName = "CubeInformation_";
	FileName.Append(M_ID);
	FileName.Append(".csv");
	FString Path = M_FilePath + FileName;
	
	if (FFileHelper::SaveStringToFile(M_Content, *Path))
	{
		FString Str = "Successfully stored file: " + Path;
		UE_LOG(LogTemp, Display, TEXT("%s"), *Str);
	} else
	{
		FString Str = "Could not store file: " + Path;
		UE_LOG(LogTemp, Error, TEXT("%s"), *Str);
	}
	
	M_Content.Empty();
}

void UStatisticsSubsystem::SetFilePath(FString FilePath)
{
	M_FilePath = FilePath;
}

void UStatisticsSubsystem::SetID(FString ID)
{
	this->M_ID = ID;
}
