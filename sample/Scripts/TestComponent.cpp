#include "TestComponent.h"
#include "Object/GameObject.h"
#include "Object/Transform.h"
#include "Core/Log.h"
#include "Core/Time.h"
#include "Math/Quaternion.h"

TestComponent::TestComponent(gore::GameObject* gameObject) :
    Component(gameObject)
{
    LOG_STREAM(DEBUG) << "Created TestComponent in GameObject " << gameObject->GetName() << std::endl;
}

TestComponent::~TestComponent()
{
    LOG_STREAM(DEBUG) << "Destroyed TestComponent in GameObject " << GetGameObject()->GetName() << std::endl;
}

void TestComponent::Start()
{
    LOG_STREAM(DEBUG) << "Start TestComponent in GameObject " << GetGameObject()->GetName() << std::endl;
}

void TestComponent::Update()
{
    float deltaTime = GetDeltaTime();
    float totalTime = GetTotalTime();

    gore::Transform* transform = m_GameObject->GetComponent<gore::Transform>();

    gore::Quaternion rot = transform->GetLocalRotation();
    rot = gore::Quaternion::CreateFromAxisAngle(gore::Vector3::Up, totalTime);
    transform->SetLocalRotation(rot);

    // m_GameObject->GetComponent<gore::Transform>()->RotateAroundAxis(gore::Vector3::Up, deltaTime);
}
