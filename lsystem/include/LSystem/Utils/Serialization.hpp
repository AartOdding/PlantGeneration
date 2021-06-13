#pragma once

#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/vector.hpp>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>



namespace cereal
{

    template<class Archive>
    void serialize(Archive& archive, glm::vec2& vec)
    {
        archive(vec.x, vec.y);
    }

    template<class Archive>
    void serialize(Archive& archive, glm::vec3& vec)
    {
        archive(vec.x, vec.y, vec.z);
    }

    template<class Archive>
    void serialize(Archive& archive, glm::vec4& vec)
    {
        archive(vec.x, vec.y, vec.z, vec.w);
    }

}
