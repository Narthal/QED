#ifndef NUMERIC_H
#define NUMERIC_H

#include <glm/glm.hpp>

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			namespace Type
			{
				namespace Numeric
				{
					using ByteUInt	= uint8_t;
					using ShortUInt	= uint16_t;
					using UInt		= uint32_t;
					using LongUInt	= uint64_t;

					using ByteInt	= int8_t;
					using ShortInt	= int16_t;
					using Int		= int32_t;
					using LongInt	= int64_t;

					using Float		= float;
					using Double	= double;

					using Vec2		= glm::vec2;
					using Vec3		= glm::vec3;
					using Vec4		= glm::vec4;

					using Mat3		= glm::mat3;
					using Mat4		= glm::mat4;
				}
			}
		}
	}

	using namespace QED::Engine::Core::Type::Numeric;
}


#endif // !NUMERIC_H
