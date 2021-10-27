#include "pch.h"
#include "GameObject.h"

TEST(TestCaseName, TestName)
{
	Transform t1, t2;
	t2.SetParent(&t1);
	t1.RotateLocalY(45);
	t1.TranslateV(Vector3f(0, 23, 45));

	EXPECT_FLOAT_EQ(t1.GetRelativeOrientation().GetX(), t2.GetWorldTransform().GetRelativeOrientation().GetX());
	EXPECT_FLOAT_EQ(t1.GetRelativeOrientation().GetY(), t2.GetWorldTransform().GetRelativeOrientation().GetY());
	EXPECT_FLOAT_EQ(t1.GetRelativeOrientation().GetZ(), t2.GetWorldTransform().GetRelativeOrientation().GetZ());
	EXPECT_FLOAT_EQ(t1.GetRelativeOrientation().GetW(), t2.GetWorldTransform().GetRelativeOrientation().GetW());
	EXPECT_TRUE(true);
}

TEST(QuaternionClass, EulerAngles)
{
	Quaternion q;
	EXPECT_FLOAT_EQ(q.GetEulerAnglesDegrees().GetX(), 0.f);
	EXPECT_FLOAT_EQ(q.GetEulerAnglesDegrees().GetY(), 0.f);
	EXPECT_FLOAT_EQ(q.GetEulerAnglesDegrees().GetZ(), 0.f);
	q.Rotate(45, Vector3f(0, 1, 0));
	EXPECT_FLOAT_EQ(q.GetEulerAnglesDegrees().GetX(), 0.f);
	EXPECT_FLOAT_EQ(q.GetEulerAnglesDegrees().GetY(), 45.f);
	EXPECT_FLOAT_EQ(q.GetEulerAnglesDegrees().GetZ(), 0.f);
}

TEST(QuaternionClass, AddScaledVector)
{
	Quaternion q;
	Vector3f angVel(0, 6.28319f, 0);
	q.IntegrateAngVel(angVel, 0.25f);
	EXPECT_FLOAT_EQ(q.GetEulerAnglesDegrees().GetX(), 0.f);
	EXPECT_FLOAT_EQ(q.GetEulerAnglesDegrees().GetY(), 90.f);
	EXPECT_FLOAT_EQ(q.GetEulerAnglesDegrees().GetZ(), 0.f);
}

TEST(QuaternionClass, GetYTest)
{
	Quaternion q;
	EXPECT_FLOAT_EQ(q.GetY(), 0.f);
	//q.Rotate()
	//EXPECT_FLOAT_EQ(q.GetEulerAnglesDegrees().GetY(), 180.f);
	//EXPECT_FLOAT_EQ(q.GetEulerAnglesDegrees().GetZ(), 0.f);
}


TEST(InertiaTensor, InertiaTensor1)
{
	GameObject obj;
	//CCollider &col = *obj.AddCCollider();
	//col.AddBoxCollider(0.5, 0.5, 0.1, 0, 0, 0, false, 0, true, 31);
}
