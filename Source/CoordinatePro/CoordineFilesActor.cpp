// Fill out your copyright notice in the Description page of Project Settings.


#include "CoordineFilesActor.h"
#include "Kismet/KismetStringLibrary.h"
#include "stdlib.h"
#include "iostream"
#include "fstream"
#include "string"

// Sets default values
ACoordineFilesActor::ACoordineFilesActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoordineFilesActor::BeginPlay()
{
	Super::BeginPlay();



	
	
}

// Called every frame
void ACoordineFilesActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoordineFilesActor::InitCoordineFilesInsv(FString FloderAddress)
{
	TArray<FString>FileNames;
	TArray<FString>FilesArray;
	FileNames.Empty();
	FilesArray.Empty();
	CategoryPath="";

	FString AddressStr="\\";
	CategoryPath=FloderAddress+AddressStr;
	
	IFileManager& MyFileManager=IFileManager::Get();
	MyFileManager.FindFilesRecursive(FileNames,*CategoryPath,TEXT("*.insv"),true,false,true);
	for(auto Index:FileNames)
	{
		FilesArray.Add(Index);
	}

	TArray<FString>FinalFileNames;
	TArray<FString>FinalGPXNames;
	
	for(int32 Index=0;Index<FileNames.Num();Index++)
	{
		TArray<FString>localParse=UKismetStringLibrary::ParseIntoArray(FileNames[Index],"\\",true);
		
		TArray<FString>localFileNumbers=UKismetStringLibrary::ParseIntoArray(localParse[localParse.Num()-1],"_",true);

		for(int32 localIndex=0;localIndex<localFileNumbers.Num();localIndex++)
		{
			if(localFileNumbers[localIndex]=="VID")
			{
				for(auto localNumberIndex:localFileNumbers)
				{
					if(localNumberIndex=="00")
					{
						FinalFileNames.Add(FileNames[Index]);

						FString localGPX=".gpx";

						TArray<FString>localCutNames=UKismetStringLibrary::ParseIntoArray(FileNames[Index],".insv",true);
						for(auto gpxIndex:localCutNames)
						{
							FString localAppendGPX=gpxIndex+localGPX;
							
							FinalGPXNames.Add(localAppendGPX);
						}
						
					}
				}
			}
		}
		
	}
	
	FString gpxString="gpx.fmt";
	
	FString GPXFMTString=CategoryPath+gpxString;
	
	FString ExcelA="exiftool -p ";
	FString ExcelB=" -ee2 ";
	FString ExcelC=" > ";
	
	CreateFile(GPXFMTString);
	
	
	for(int32 Index=0;Index<FinalFileNames.Num();Index++)
	{
		FString TransmissionString=ExcelA+GPXFMTString+ExcelB+FinalFileNames[Index]+ExcelC+FinalGPXNames[Index];
		
		UE_LOG(LogTemp,Error,TEXT("%s"),*TransmissionString);
		
		AddUECommondAddress(TransmissionString,0);
	}
}

void ACoordineFilesActor::InitCoordineFilesMp4(FString FloderAddress)
{
	TArray<FString>FileNames;
	TArray<FString>FilesArray;
	FileNames.Empty();
	FilesArray.Empty();
	CategoryPath="";

	FString AddressStr="\\";
	CategoryPath=FloderAddress+AddressStr;
	
	IFileManager& MyFileManager=IFileManager::Get();
	MyFileManager.FindFilesRecursive(FileNames,*CategoryPath,TEXT("*.mp4"),true,false,true);
	for(auto Index:FileNames)
	{
		FilesArray.Add(Index);
	}

	TArray<FString>FinalFileNames;
	TArray<FString>FinalGPXNames;
	
	for(int32 Index=0;Index<FileNames.Num();Index++)
	{
		TArray<FString>localParse=UKismetStringLibrary::ParseIntoArray(FileNames[Index],"\\",true);
		
		TArray<FString>localFileNumbers=UKismetStringLibrary::ParseIntoArray(localParse[localParse.Num()-1],"_",true);

		for(int32 localIndex=0;localIndex<localFileNumbers.Num();localIndex++)
		{
			if(localFileNumbers[localIndex]=="VID")
			{
				for(auto localNumberIndex:localFileNumbers)
				{
					if(localNumberIndex=="10")
					{
						FinalFileNames.Add(FileNames[Index]);

						FString localGPX=".gpx";

						TArray<FString>localCutNames=UKismetStringLibrary::ParseIntoArray(FileNames[Index],".mp4",true);
						for(auto gpxIndex:localCutNames)
						{
							FString localAppendGPX=gpxIndex+localGPX;
							
							FinalGPXNames.Add(localAppendGPX);
						}
						
					}
				}
			}
		}
		
	}
	
	FString gpxString="gpx.fmt";
	
	FString GPXFMTString=CategoryPath+gpxString;
	
	FString ExcelA="exiftool -p ";
	FString ExcelB=" -ee2 ";
	FString ExcelC=" > ";
	
	CreateFile(GPXFMTString);
	
	
	for(int32 Index=0;Index<FinalFileNames.Num();Index++)
	{
		FString TransmissionString=ExcelA+GPXFMTString+ExcelB+FinalFileNames[Index]+ExcelC+FinalGPXNames[Index];
		
		UE_LOG(LogTemp,Error,TEXT("%s"),*TransmissionString);
		
		AddUECommondAddress(TransmissionString,0);
	}
}

float ACoordineFilesActor::AddUECommondAddress(FString UECommondAddress, float Number)
{
	std::string CommondAddress(TCHAR_TO_UTF8(*UECommondAddress));
	system(CommondAddress.c_str());
	return Number+1;
}

void ACoordineFilesActor::CreateFile(FString UEFileAddress)
{
	const char* FileAddress(TCHAR_TO_ANSI(*UEFileAddress));
	std::ofstream MakeFile;
	MakeFile.open(FileAddress);

	MakeFile << "#------------------------------------------------------------------------------" << std::endl;
	MakeFile << "# File:         gpx.fmt" << std::endl;
	MakeFile << "#" << std::endl;
	MakeFile << "# Description:  Example ExifTool print format file to generate a GPX track log" << std::endl;
	MakeFile << "#" << std::endl;
	MakeFile << "# Usage:        exiftool -p gpx.fmt -ee3 FILE [...] > out.gpx" << std::endl;
	MakeFile << "#" << std::endl;
	MakeFile << "# Requires:     ExifTool version 10.49 or later" << std::endl;
	MakeFile << "#" << std::endl;
	MakeFile << "# Revisions:    2010/02/05 - P. Harvey created" << std::endl;
	MakeFile << "#               2018/01/04 - PH Added IF to be sure position exists" << std::endl;
	MakeFile << "#               2018/01/06 - PH Use DateFmt function instead of -d option" << std::endl;
	MakeFile << "#               2019/10/24 - PH Preserve sub-seconds in GPSDateTime value" << std::endl;
	MakeFile << "#" << std::endl;
	MakeFile << "# Notes:     1) Input file(s) must contain GPSLatitude and GPSLongitude." << std::endl;
	MakeFile << "#            2) The -ee3 option is to extract the full track from video files." << std::endl;
	MakeFile << "#            3) The -fileOrder option may be used to control the order of the" << std::endl;
	MakeFile << "#               generated track points when processing multiple files." << std::endl;
	MakeFile << "#------------------------------------------------------------------------------" << std::endl;
	MakeFile << "#[HEAD]<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
	MakeFile << "#[HEAD]<gpx version=\"1.0\"" << std::endl;
	MakeFile << "#[HEAD] creator=\"ExifTool $ExifToolVersion\"" << std::endl;
	MakeFile << "#[HEAD] xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << std::endl;
	MakeFile << "#[HEAD] xmlns=\"http://www.topografix.com/GPX/1/0\"" << std::endl;
	MakeFile << "#[HEAD] xsi:schemaLocation=\"http://www.topografix.com/GPX/1/0 http://www.topografix.com/GPX/1/0/gpx.xsd\">" << std::endl;
	MakeFile << "#[HEAD]<trk>" << std::endl;
	MakeFile << "#[HEAD]<number>1</number>" << std::endl;
	MakeFile << "#[HEAD]<trkseg>" << std::endl;
	MakeFile << "#[IF]  $gpslatitude $gpslongitude" << std::endl;
	MakeFile << "#[BODY]<trkpt lat=\"$gpslatitude#\" lon=\"$gpslongitude#\">" << std::endl;
	MakeFile << "#[BODY]  <ele>$gpsaltitude#</ele>" << std::endl;
	MakeFile << "#[BODY]  <time>${gpsdatetime#;my ($ss)=/\\.\\d+/g;DateFmt(\"%Y-%m-%dT%H:%M:%SZ\");s/Z/${ss}Z/ if $ss}</time>" << std::endl;
	MakeFile << "#[BODY]</trkpt>" << std::endl;
	MakeFile << "#[TAIL]</trkseg>" << std::endl;
	MakeFile << "#[TAIL]</trk>" << std::endl;
	MakeFile << "#[TAIL]</gpx>";

	MakeFile.close();

	return;
}
