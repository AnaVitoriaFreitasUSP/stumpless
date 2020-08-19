// SPDX-License-Identifier: Apache-2.0

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

#include <cstdlib>
#include <gtest/gtest.h>
#include <sstream>
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int ITERATION_COUNT = 1000;

  void
  read_element( const struct stumpless_element *element ) {
    std::thread::id thread_id = std::this_thread::get_id(  );
    struct stumpless_element *copy;
    const char *name;

    std::ostringstream param_name_stream;
    param_name_stream << "param-name-" << thread_id;
    std::string param_name( param_name_stream.str(  ) );

    std::ostringstream param_value_stream;
    param_value_stream << "param-value-" << thread_id;
    std::string param_value( param_value_stream.str(  ) );

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      copy = stumpless_copy_element( element );

      name = stumpless_get_element_name( element );

      stumpless_element_has_param( element, param_name.c_str(  ) );

      stumpless_get_param_by_index( element, i % THREAD_COUNT );
      stumpless_get_param_by_name( element, param_name.c_str(  ) );
      stumpless_get_param_index( element, param_name.c_str(  ) );
      stumpless_get_param_name_by_index( element, i % THREAD_COUNT );
      stumpless_get_param_name_count( element, param_name.c_str(  ) );
      stumpless_get_param_value_by_index( element, i % THREAD_COUNT );
      stumpless_get_param_value_by_name( element, param_name.c_str(  ) );

      stumpless_destroy_element_and_contents( copy );
      free( ( void * ) name );
    }
  }

  void
  write_element( struct stumpless_element *element ) {
    struct stumpless_param *thread_param;

    std::thread::id thread_id = std::this_thread::get_id(  );

    std::ostringstream element_name_stream;
    element_name_stream << "element-name-" << thread_id;
    std::string element_name( element_name_stream.str(  ) );

    std::ostringstream param_name_stream;
    param_name_stream << "param-name-" << thread_id;
    std::string param_name( param_name_stream.str(  ) );

    std::ostringstream param_value_stream;
    param_value_stream << "param-value-" << thread_id;
    std::string param_value( param_value_stream.str(  ) );

    thread_param = stumpless_new_param( param_name.c_str(  ),
                                        param_name.c_str(  ) );

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      size_t index = i % THREAD_COUNT;

      stumpless_add_param( element, thread_param );

      stumpless_set_element_name( element, element_name.c_str(  ) );
      stumpless_set_param_value_by_index( element,
                                          index,
                                          param_value.c_str(  ) );
      stumpless_set_param_value_by_name( element,
                                         param_name.c_str(  ),
                                         param_value.c_str(  ) );

      stumpless_set_param( element, index, thread_param );
    }

    stumpless_destroy_param( thread_param );
  }

  TEST( ElementConsistency, SimultaneousReadsAndWrites ) {
    struct stumpless_element *element;
    int i;
    std::thread *reader_threads[THREAD_COUNT];
    std::thread *writer_threads[THREAD_COUNT];

    element = stumpless_new_element( "initial-name" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( element );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i] = new std::thread( read_element, element );
      writer_threads[i] = new std::thread( write_element, element );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i]->join(  );
      delete reader_threads[i];
      writer_threads[i]->join(  );
      delete writer_threads[i];
    }

    // cleanup after the test
    stumpless_destroy_element_only( element );
    stumpless_free_all(  );
  }
}
