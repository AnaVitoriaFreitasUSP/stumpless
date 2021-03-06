/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_VALIDATE_H
#  define __STUMPLESS_PRIVATE_VALIDATE_H

#  include <stddef.h>
#  include <stdbool.h>
#  include "private/config/locale/wrapper.h"
#  include "private/error.h"

#  define VALIDATE_ARG_NOT_NULL( ARG_NAME )                         \
if( ARG_NAME == NULL ) {                                            \
  raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( #ARG_NAME ) ); \
  return NULL;                                                      \
}

/**
 * Checks the char length of msgid.
 *
 * @param the msgid.
 * 
 * @return True if the msgid is at or below the maximum allowed length, otherwise
 * it will return false and raise the appropriate error.
 */
bool validate_msgid_length(const char* msgid );

/**
 * Checks the format of msgid.
 *
 * @param the msgid.
 *
 * @return True if the msgid has the correct format, otherwise
 * it will return false and raise STUMPLESS_INVALID_ENCODING error.
 */
bool validate_msgid_format( const char* msgid );

#endif /* __STUMPLESS_PRIVATE_VALIDATE_H */
