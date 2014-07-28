#ifndef HEADERBoOmTEST_test_macros
#define HEADERBoOmTEST_test_macros

#define BOOMST_CHECK_APPROX_EQUAL( X, Y ) BOOST_CHECK_MESSAGE( equals_about( (X), (Y) ), "check equals_about( " <<#X <<", " <<#Y <<" ) failed [!equals_about( " <<(X) <<", " <<(Y) <<" )]" )

#endif


