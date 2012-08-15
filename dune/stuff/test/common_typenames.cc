#include "test_common.hh"

#include <iostream>

#include <dune/stuff/common/type_utils.hh>

STUFF_TYPENAME(Dune::MPIHelper)

using namespace Dune::Stuff::Common;
using namespace std;

TEST(Typename, Knowns)
{
  EXPECT_EQ(Typename<unsigned long>::value(), "unsigned long");
  EXPECT_EQ(Typename<unsigned long>::value(), "unsigned long");
  EXPECT_EQ(Typename<int>::value(), "int");
  EXPECT_EQ(Typename<double>::value(), "double");
  EXPECT_EQ(Typename<float>::value(), "float");
  EXPECT_EQ(Typename<long>::value(), "long");
  EXPECT_EQ(Typename<unsigned int>::value(), "unsigned int");
  EXPECT_EQ(Typename<unsigned long>::value(), "unsigned long");
  EXPECT_EQ(Typename<char>::value(), "char");
}

TEST(Typename, Unknowns)
{
  EXPECT_NE(Typename<Dune::Exception>::value(), string());
}

TEST(Typename, Extended)
{
  EXPECT_EQ(Typename<Dune::MPIHelper>::value(), string("MPIHelper"));
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  Dune::MPIHelper::instance(argc, argv);
  return RUN_ALL_TESTS();
}
