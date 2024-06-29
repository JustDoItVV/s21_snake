#include "tetris_cli_test.h"

int main() {
  SRunner *runner = srunner_create(tetris_suite());

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? 0 : 1;
}