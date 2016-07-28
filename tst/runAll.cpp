#include <gtest/gtest.h>


typedef struct SPlanTypeInfo
{
  float basicMonthlyRate;
  float additionalRate;
  float excessMinutesRate;
  float discountRate;
  int   discountLineThreshold;
  int   includedMinutes;

  SPlanTypeInfo(float _basicMonthlyRate,
                float _additionalRate,
                float _excessMinutesRate,
                float _discountRate,
                int   _discountLineThreshold,
                int   _includedMinutes)
  {
    basicMonthlyRate      = _basicMonthlyRate;
    additionalRate        = _additionalRate;
    excessMinutesRate     = _excessMinutesRate;
    discountRate          = _discountRate;
    discountLineThreshold = _discountLineThreshold;
    includedMinutes       = _includedMinutes;
  }
};

typedef struct SFamilyfamilyLineInfo
{
  int additionalLines;
  int usedMinutes;

  SFamilyfamilyLineInfo(int _additionalLines,
            int _usedMinutes)
  {
    additionalLines = _additionalLines;
    usedMinutes    = _usedMinutes;
  }
};

class PhonePayment
{
public:
  PhonePayment(SPlanTypeInfo _planTypeInfo, SFamilyfamilyLineInfo _familyLineInfo)
  : planTypeInfo(_planTypeInfo),
    familyLineInfo(_familyLineInfo)
  {}

  float calcPlanTypeBill()
  {
    float result = 0.0f;

    result += planTypeInfo.basicMonthlyRate;
    if(familyLineInfo.additionalLines > planTypeInfo.discountLineThreshold)
    {
      result += planTypeInfo.additionalRate * planTypeInfo.discountLineThreshold
                + planTypeInfo.discountRate * (familyLineInfo.additionalLines - planTypeInfo.discountLineThreshold);
    }
    else
    {
      result += planTypeInfo.additionalRate * familyLineInfo.additionalLines;
    }

    if(familyLineInfo.usedMinutes > planTypeInfo.includedMinutes)
    {
      result += (familyLineInfo.usedMinutes - planTypeInfo.includedMinutes) * planTypeInfo.excessMinutesRate;
    }

    return result;
  }

private:
  const SPlanTypeInfo planTypeInfo;
  SFamilyfamilyLineInfo familyLineInfo;
};

class TestGame : public ::testing::Test{
public:
  void SetUp(){
    //code here be executed before test case
  }

  void TearDown(){
    //Code here be executed after test case
  }
};

TEST(TestGame, GoldPlanTypeWithAdditionLines)
{
  PhonePayment phonePayment(SPlanTypeInfo(49.95f, 14.50f, 0.45f, 5.0f, 2, 1000),
                            SFamilyfamilyLineInfo(1, 999));
  EXPECT_EQ(64.45f, phonePayment.calcPlanTypeBill());
}

TEST(TestGame, SilverPlanTypeWithAdditionLines)
{
  PhonePayment phonePayment(SPlanTypeInfo(29.95f, 21.50f, 0.54f, 5.0f, 2, 500),
                            SFamilyfamilyLineInfo(2, 499));
  EXPECT_EQ(72.95f, phonePayment.calcPlanTypeBill());
}

TEST(TestGame, GoldPlanTypeWithExcessMinutes)
{
  PhonePayment phonePayment(SPlanTypeInfo(49.95f, 14.50f, 0.45f, 5.0f, 2, 1000),
                            SFamilyfamilyLineInfo(0, 1010));
  EXPECT_EQ(54.45f, phonePayment.calcPlanTypeBill());
}

TEST(TestGame, SilverPlanTypeWithExcessMinutes)
{
  PhonePayment phonePayment(SPlanTypeInfo(29.95f, 21.50f, 0.54f, 5.0f, 2, 500),
                            SFamilyfamilyLineInfo(0, 520));
  EXPECT_EQ(40.75f, phonePayment.calcPlanTypeBill());
}

TEST(TestGame, GoldPlanTypeWithFamilyDiscount)
{
  PhonePayment phonePayment(SPlanTypeInfo(49.95f, 14.50f, 0.45f, 5.0f, 2, 1000),
                            SFamilyfamilyLineInfo(3, 999));
  EXPECT_EQ(83.95f, phonePayment.calcPlanTypeBill());
}

TEST(TestGame, SilverPlanTypeWithFamilyDiscount)
{
  PhonePayment phonePayment(SPlanTypeInfo(29.95f, 21.50f, 0.54f, 5.0f, 2, 500),
                            SFamilyfamilyLineInfo(4, 499));
  EXPECT_EQ(82.95f, phonePayment.calcPlanTypeBill());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
