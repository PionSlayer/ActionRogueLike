#include "SAttributeComponent.h"
USAttributeComponent::USAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Health = 100;
}

bool USAttributeComponent::ApplyHeathChange(float Delta)
{
	Health += Delta;
	OnHealthChanged.Broadcast(nullptr,this,Health,Delta);
	return true;
}
