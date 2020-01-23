// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>
#include <stddef.h>
#include <stumpless.h>

namespace {

  TEST( GetDefaultTarget, SocketSupported ) {
    struct stumpless_target *target;

    target = stumpless_get_default_target(  );

    EXPECT_TRUE( target != NULL );

    if( target ) {
      EXPECT_EQ( target->type, STUMPLESS_SOCKET_TARGET );
      EXPECT_STREQ( target->name, STUMPLESS_DEFAULT_SOCKET );
    }

    stumpless_free_all(  );
  }
}