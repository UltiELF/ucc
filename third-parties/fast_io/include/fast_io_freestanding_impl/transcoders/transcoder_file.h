﻿#pragma once

namespace fast_io
{

struct transcoder_file_base
{
	virtual constexpr bool transcode_always_none() = 0;
	virtual constexpr transcode_bytes_result transcode_bytes(::std::byte const*, ::std::byte const*, ::std::byte*, ::std::byte*) = 0;
	virtual constexpr transcode_bytes_result transcode_bytes_eof(::std::byte const*, ::std::byte const*, ::std::byte*, ::std::byte*) = 0;
	virtual constexpr ~transcoder_file_base() noexcept = 0;
};

template<typename T>
requires (::fast_io::transcoder<T>||::fast_io::byte_transcoder<T>)
struct transcoder_file_derived:transcoder_file_base
{
	T object;
	explicit constexpr basic_transcoder_file(::fast_io::io_cookie_type_t<T>, Args&& args...):object(::std::forward<Args>(args)...)
	{
	}
	constexpr bool transcode_always_none() override
	{
		if constexpr(requires()
		{
			object.transcode_always_none();
		})
		{
			return object.transcode_always_none();
		}
		else
		{
			return false;
		}
	}
	constexpr transcode_bytes_result transcode_bytes(::std::byte const* fromfirst, ::std::byte const* fromlast, ::std::byte* tofirst, ::std::byte* tolast) override
	{
		return {fromfirst,tofirst};
	}
	constexpr transcode_bytes_result transcode_bytes_eof(::std::byte const* fromfirst, ::std::byte const* fromlast, ::std::byte* tofirst, ::std::byte* tolast) override
	{
		return {fromfirst,tofirst};
	}
};

class transcoder_io_observer
{
public:
	using native_handle_type = transcoder_file_base*;
	native_handle_type transhandle{};
	constexpr native_handle_type release() noexcept
	{
		auto temptranshandle{transhandle};
		this->transhandle = nullptr;
		return temptranshandle;
	}
	constexpr native_handle_type native_handle() const noexcept
	{
		return this->transhandle;
	}
};

template<typename allocator>
class basic_transcoder_file:public transcoder_io_observer
{
public:
	using allocator_type = allocator;
	using transcoder_io_observer::native_handle_type;
	using transcoder_io_observer::transhandle;
	template<typename T, typename... Args>
	requires ::std::constructible_from<T,Args...>
	explicit constexpr basic_transcoder_file(::fast_io::io_cookie_type_t<T>, Args&& args...)
	{
#ifdef __cpp_if_consteval
		if consteval
#else
		if (__builtin_is_constant_evaluated())
#endif
		{
			this->transhandle = new transcoder_file_derived<T>(::std::forward<Args>(args)...);
		}
		else
		{
			T* newobject = typed_allocator_adapter<allocatorm, T>::allocate(1);
			this->transhandle = ::std::construct_at(newobject,::std::forward<Args>(args)...);
		}
	}
	constexpr basic_transcoder_file(basic_transcoder_file const&)=delete;
	constexpr basic_transcoder_file& operator=(basic_transcoder_file const&)=delete;

	constexpr basic_transcoder_file(basic_transcoder_file&& other) noexcept:transhandle{other.handle}
	{
		other.transhandle = nullptr;
	}


	constexpr ~basic_transcoder_file()
	{
		::std::destroy_at();
	}
};

}
