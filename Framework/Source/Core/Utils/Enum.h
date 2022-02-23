#pragma once

namespace VS
{
	//! A base class for providing artificial enum inheritance.
	template<typename T>
	class EEnum
	{
	public:
		enum class EEnumType : T
		{
			None
		};
	};

	//! Used ONLY for enum generation. You should never have to use this explicitly.
	template<typename T>
	using Enum_BASE = EEnum<T>;

	//! Used in all other cases.
	template<typename T>
	using Enum = EEnum<T>::EEnumType;

#define VS_ENUM(EnumName, Parent, ...) \
	template<typename T> \
	class GENERATED_##EnumName : public Parent##_BASE<T>\
	{ \
	public: \
		enum class EEnumType : T \
		{ \
			__VA_ARGS__ \
		}; \
	}; \
	template<typename T> \
	using EnumName##_BASE = GENERATED_##EnumName<T>; \
	template<typename T> \
	using EnumName = GENERATED_##EnumName<T>::EEnumType;

}