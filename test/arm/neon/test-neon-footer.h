#if defined(SIMDE_TEST_BARE)
  int main(void) {
    fprintf(stdout, "1..%zu\n", (sizeof(test_suite_tests) / sizeof(test_suite_tests[0])));
    for (size_t i = 0 ; i < (sizeof(test_suite_tests) / sizeof(test_suite_tests[0])) ; i++) {
      int res = test_suite_tests[i].func();
      if (res != 0) {
        fprintf(stdout, "not ok %zu " HEDLEY_STRINGIFY(SIMDE_TEST_ARM_NEON_INSN) "/%s\n", i + 1, test_suite_tests[i].name);
      } else {
        fprintf(stdout, "ok %zu " HEDLEY_STRINGIFY(SIMDE_TEST_ARM_NEON_INSN) "/%s\n", i + 1, test_suite_tests[i].name);
      }
    }

    return 0;
  }
#else
  #if defined(__cplusplus)
    static MunitSuite suite = { const_cast<char*>("/" HEDLEY_STRINGIFY(SIMDE_TEST_ARM_NEON_INSN)), test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };
  #else
    static MunitSuite suite = { (char*) "/" HEDLEY_STRINGIFY(SIMDE_TEST_ARM_NEON_INSN), test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };
  #endif

  HEDLEY_C_DECL MunitSuite*
  SIMDE_TEST_GENERATE_VARIANT_SYMBOL_CURRENT(HEDLEY_CONCAT(simde_test_arm_neon_get_suite_,SIMDE_TEST_ARM_NEON_INSN)) (void) {
    return &suite;
  }
#endif
