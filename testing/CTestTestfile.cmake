# CMake generated Testfile for 
# Source directory: C:/Users/brianweis/code/IMPACT/testing
# Build directory: C:/Users/brianweis/code/IMPACT/testing
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(IMPACT::RunUnitTests "C:/Users/brianweis/code/IMPACT/bin/impact_test" "-o" "impact_testresults.txt")
add_test(IMPACT::RunTestScripts "C:/Users/brianweis/code/IMPACT/bin/runtest" "-l" "C:/Users/brianweis/code/IMPACT/testing/scripts/tests.list" "-s" "C:/Users/brianweis/code/IMPACT/testing" "-b" "C:/Users/brianweis/code/IMPACT/bin" "-v" "2" "-o" "impact_testresults.txt")
add_test(IMPACT::RunPlatformSpecificTests "C:/Users/brianweis/code/IMPACT/bin/runtest" "-p" "C:/Users/brianweis/code/IMPACT/testing/platforms/platforms" "-s" "C:/Users/brianweis/code/IMPACT/testing" "-b" "C:/Users/brianweis/code/IMPACT/bin" "-v" "2" "-o" "impact_testresults.txt")
add_test(IMPACT::RunSpecificTestScript "C:/Users/brianweis/code/IMPACT/bin/runtest" "-f" "C:/Users/brianweis/code/IMPACT/testing/scripts/test_stub.csh" "-s" "C:/Users/brianweis/code/IMPACT/testing" "-b" "C:/Users/brianweis/code/IMPACT/bin" "-v" "3" "-o" "impact_testresults.txt")
add_test(IMPACT::ExampleProgram:Runs "C:/Users/brianweis/code/IMPACT/bin/sep" "Makefile")
add_test(IMPACT::TestStubWorks "C:/Users/brianweis/code/IMPACT/bin/testresults" "TestStubWorks" "impact_testresults.txt")
add_test(IMPACT::ExampleProgram:Works "C:/Users/brianweis/code/IMPACT/bin/testresults" "ExampleProgram:Works" "impact_testresults.txt")
add_test(IMPACT::ExampleFunction:Works "C:/Users/brianweis/code/IMPACT/bin/testresults" "ExampleFunction:Works" "impact_testresults.txt")
add_test(IMPACT::TrapezoidQuadrature:Runs "C:/Users/brianweis/code/IMPACT/bin/testresults" "TrapezoidQuadrature:Runs" "impact_testresults.txt")
add_test(IMPACT::TrapezoidQuadrature:Accurate "C:/Users/brianweis/code/IMPACT/bin/testresults" "TrapezoidQuadrature:Accurate" "impact_testresults.txt")
add_test(IMPACT::TrapezoidQuadrature:Order "C:/Users/brianweis/code/IMPACT/bin/testresults" "TrapezoidQuadrature:Order2" "impact_testresults.txt")
add_test(IMPACT::MidPointQuadrature:Runs "C:/Users/brianweis/code/IMPACT/bin/testresults" "MidPointQuadrature:Runs" "impact_testresults.txt")
add_test(IMPACT::MidPointQuadrature:Accurate "C:/Users/brianweis/code/IMPACT/bin/testresults" "MidPointQuadrature:Accurate" "impact_testresults.txt")
add_test(IMPACT::MidPointQuadrature:Order "C:/Users/brianweis/code/IMPACT/bin/testresults" "MidPointQuadrature:Order2" "impact_testresults.txt")
add_test(IMPACT::TestModuleDriver:Runs "C:/Users/brianweis/code/IMPACT/bin/testresults" "TestModuleDriver:Runs" "impact_testresults.txt")
add_test(IMPACT::TestModuleDriver:Passes "C:/Users/brianweis/code/IMPACT/bin/testresults" "TestModuleDriver:Passes" "impact_testresults.txt")
add_test(IMPACT::TestModuleDriverF:Runs "C:/Users/brianweis/code/IMPACT/bin/testresults" "TestModuleDriverF:Runs" "impact_testresults.txt")
add_test(IMPACT::TestModuleDriverF:Passes "C:/Users/brianweis/code/IMPACT/bin/testresults" "TestModuleDriverF:Passes" "impact_testresults.txt")
