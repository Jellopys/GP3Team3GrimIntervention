// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

template<typename ElementType>
class TArray2D
{
public:
	void Init(const ElementType& Element, int D1Size, int D2Size)
	{
		SizeD1 = D1Size;
		SizeD2 = D2Size;
		InnerArray.Init(Element, D1Size*D2Size);
	}

	FORCEINLINE ElementType& GetElement(const int D1, const int D2)
	{
		return InnerArray[(D1 * SizeD1) + D2];
	}

	FORCEINLINE void SetElement(const int D1, const int D2, const ElementType& Item)
	{
		InnerArray[(D1 * SizeD1) + D2] = Item;
	}

	void ForEachElement(void (*Func)(const int D1, const int D2, const ElementType& Item))
	{
		for(int i = 0; i < InnerArray.Num(); ++i)
		{
			int Y = i / SizeD1;
			int X = i % SizeD2;
			Func(Y, X, InnerArray[i]);
		}
	}

	int Num() const
	{
		return SizeD1*SizeD2;
	}

private:
	int SizeD1=0;
	int SizeD2=0;
	TArray<ElementType> InnerArray;
};
