// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __RESOURCE_PROVIDER_MESSAGE_HPP__
#define __RESOURCE_PROVIDER_MESSAGE_HPP__

#include <ostream>

#include <mesos/mesos.hpp>
#include <mesos/resources.hpp>

#include <stout/check.hpp>
#include <stout/option.hpp>
#include <stout/unreachable.hpp>

namespace mesos {
namespace internal {

struct ResourceProviderMessage
{
  enum class Type
  {
    UPDATE_TOTAL_RESOURCES
  };

  struct UpdateTotalResources {
    ResourceProviderID id;
    Resources total;
  };

  Type type;

  Option<UpdateTotalResources> updateTotalResources;
};


inline std::ostream& operator<<(
    std::ostream& stream,
    const ResourceProviderMessage& resourceProviderMessage)
{
  switch (resourceProviderMessage.type) {
    case ResourceProviderMessage::Type::UPDATE_TOTAL_RESOURCES:
      const Option<ResourceProviderMessage::UpdateTotalResources>&
        updateTotalResources = resourceProviderMessage.updateTotalResources;

      CHECK_SOME(updateTotalResources);

      return stream
          << "UPDATE_TOTAL_RESOURCES: "
          << updateTotalResources->id << " "
          << updateTotalResources->total;
  }

  UNREACHABLE();
}

} // namespace internal {
} // namespace mesos {

#endif // __RESOURCE_PROVIDER_MESSAGE_HPP__
