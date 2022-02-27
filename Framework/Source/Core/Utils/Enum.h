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
			Last
		};
		constexpr EEnum() : Val(EEnumType::Last) {}
		constexpr EEnum(const T Val) : Val(Val) { }
		constexpr EEnum(const EEnum& Other) { Val = Other.Val; }
		constexpr EEnum(EEnumType E) { Val = E; }
		constexpr EEnum& operator=(T Other) { Val = static_cast<EEnumType>(Other); }
		constexpr EEnum& operator=(const EEnum<T>& Other) { Val = static_cast<EEnumType>(Other.Val); }
		constexpr operator T() { return static_cast<T>(Val); }

		EEnumType Val;
	};

#define VS_ENUM(EnumName, Parent, ...) \
	template<typename T> \
	class GENERATED_##EnumName : public Parent<T>\
	{ \
	public: \
		enum class EEnumType : T \
		{ \
			First = Parent<T>::EEnumType::Last, \
			__VA_ARGS__, \
			Last \
		}; \
		constexpr GENERATED_##EnumName() : Val(EEnumType::Last) {} \
		constexpr GENERATED_##EnumName(const T Val) : Val(Val) {} \
		constexpr GENERATED_##EnumName(const GENERATED_##EnumName& Other) { Val = Other.Val; } \
		constexpr GENERATED_##EnumName(EEnumType E) { Val = E; } \
		constexpr GENERATED_##EnumName& operator=(const T Other) { Val = static_cast<EEnumType>(Other); } \
		constexpr GENERATED_##EnumName& operator=(const EEnum<T>& Other) { Val = static_cast<EEnumType>(Other.Val); } \
		constexpr operator T() { return static_cast<T>(Val); } \
		EEnumType Val; \
	}; \
	template<typename T> \
	using EnumName = GENERATED_##EnumName<T>;

	/*
	//! A base class for providing artificial enum inheritance.
	template<typename T>
	class EEnum
	{
	public:
		enum class EEnumType : T
		{
			Last
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
			First = Parent<T>::Last, \
			__VA_ARGS__ \
		}; \
	}; \
	template<typename T> \
	using EnumName##_BASE = GENERATED_##EnumName<T>; \
	template<typename T> \
	using EnumName = GENERATED_##EnumName<T>::EEnumType;
	*/
}