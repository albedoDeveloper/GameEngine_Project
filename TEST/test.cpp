#include "pch.h"
#include "Transform.h"

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
