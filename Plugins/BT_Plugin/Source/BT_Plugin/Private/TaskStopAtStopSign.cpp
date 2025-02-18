// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskStopAtStopSign.h"
#include "VehicleController.h"



#define BRAKE_START_DISTANCE 800
#define SLOWDOWN_DISTANCE 1200
#define BRAKE_INC_RATE 0.01



EBTNodeResult::Type UTaskStopAtStopSign::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//PrintLog("Task Stop at stop sign");
	UBehaviorTreeComponent& MyComp = OwnerComp;
	AVehicleController* MyController = &MyComp ? Cast<AVehicleController>(MyComp.GetOwner()) : NULL;

	FVector VehicleLocation = MyController->BlackboardComponent->GetValueAsVector("VehicleWorldLocation");
	FVector VehicleLocationOnSpline = MyController->WayPoint->SplineComponent->FindLocationClosestToWorldLocation(VehicleLocation, ESplineCoordinateSpace::World);

	FVector StopSignLocation = MyController->WayPoint->StopSignLocation;
	FVector StopLocationOnSpline = MyController->WayPoint->SplineComponent->FindLocationClosestToWorldLocation(MyController->WayPoint->StopSignLocation, ESplineCoordinateSpace::World);
	
	float Distance = FVector::Distance(VehicleLocationOnSpline, StopLocationOnSpline);
	//PrintLog("Distnace " + FString::SanitizeFloat(Distance));
	if (Distance < SLOWDOWN_DISTANCE && Distance > BRAKE_START_DISTANCE)
	{
		MyController->BlackboardComponent->SetValueAsInt("VelocityStatus", -1);
		return EBTNodeResult::Failed;
	}
	if (Distance < BRAKE_START_DISTANCE)
	{
		//PrintLog("Braking..l... success");
		float ThrottleValue = MyController->BlackboardComponent->GetValueAsFloat("ThrottleValue");
		MyController->BlackboardComponent->SetValueAsFloat("BrakeValue", ThrottleValue);
		MyController->BlackboardComponent->SetValueAsFloat("ThrottleValue", 0);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
