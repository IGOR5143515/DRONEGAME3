// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnvQueryTest_Pickup.h"
#include "PichUps/BasePuckUp.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"

UEnvQueryTest_Pickup::UEnvQueryTest_Pickup(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTest_Pickup::RunTest(FEnvQueryInstance& QueryInstance) const
{

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It) {

		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		auto PickUpActor = Cast<ABasePuckUp>(ItemActor);

		if (!PickUpActor) continue;

		auto CoulBeTaken = PickUpActor->CouldBeTaken();

		if (CoulBeTaken) {

			It.SetScore(TestPurpose, FilterType, true, true);
		}
		else
			It.ForceItemState(EEnvItemStatus::Failed);
	}
	 

}
