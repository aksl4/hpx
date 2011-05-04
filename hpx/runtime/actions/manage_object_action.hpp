//  Copyright (c) 2007-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_RUNTIME_ACTIONS_MANAGE_OBJECT_ACTION_JAN_26_2010_0141PM)
#define HPX_RUNTIME_ACTIONS_MANAGE_OBJECT_ACTION_JAN_26_2010_0141PM

#include <cstring>
#include <boost/config.hpp>
#include <boost/serialization/serialization.hpp>

#include <hpx/config/warnings_prefix.hpp>
#include <hpx/runtime/actions/action_support.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace actions
{
    ///////////////////////////////////////////////////////////////////////////
    struct HPX_API_EXPORT manage_object_action_base
    {
        typedef void (*construct_function)(void*, std::size_t);
        typedef void (*clone_function)(void*, void const*, std::size_t);
        typedef void (*destruct_function)(void*);
#if HPX_USE_PORTABLE_ARCHIVES != 0
        typedef util::portable_binary_oarchive oarchive_type;
        typedef util::portable_binary_iarchive iarchive_type;
#else
        typedef boost::archive::binary_oarchive oarchive_type;
        typedef boost::archive::binary_iarchive iarchive_type;
#endif
        typedef void (*serialize_save_function)(boost::uint8_t*, std::size_t, 
            oarchive_type&, const unsigned int);
        typedef void (*serialize_load_function)(boost::uint8_t*, std::size_t,
            iarchive_type&, const unsigned int);

    private:
        static void construct_(void*, std::size_t) {}
        static void clone_(void* dest, void const* src, std::size_t size)
        {
            using namespace std;    // some systems have memcpy in std
            memcpy(dest, src, size);
        }
        static void destruct_(void*) {}

        static void save_(boost::uint8_t* data, std::size_t size, 
            oarchive_type& ar, const unsigned int version)
        {
            using boost::serialization::make_array;
            ar << make_array(data, size);
        }
        static void load_(boost::uint8_t* data, std::size_t size, 
            iarchive_type& ar, const unsigned int version)
        {
            using boost::serialization::make_array;
            ar >> make_array(data, size);
        }

    public:
        manage_object_action_base() {}
        virtual ~manage_object_action_base() {}

        // support for construction, copying, destruction
        virtual construct_function construct() const 
        { 
            return &manage_object_action_base::construct_; 
        }
        virtual clone_function clone() const 
        { 
            return &manage_object_action_base::clone_; 
        }
        virtual destruct_function destruct() const 
        { 
            return &manage_object_action_base::destruct_; 
        }

        virtual manage_object_action_base const& get_instance() const;

        // serialization support
        virtual serialize_save_function save() const
        { 
            return &manage_object_action_base::save_; 
        }
        virtual serialize_load_function load() const
        { 
            return &manage_object_action_base::load_; 
        }

    private:
        // serialization support, just serialize the type
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {}
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct manage_object_action : manage_object_action_base
    {
        manage_object_action() {}
        ~manage_object_action() {}

    private:
        static void construct_(void* memory, std::size_t size)
        {
            BOOST_ASSERT(size == sizeof(T));
            new (memory) T;
        }
        static void clone_(void* dest, void const* src, std::size_t size)
        {
            BOOST_ASSERT(size == sizeof(T));
            new (dest) T (*reinterpret_cast<T const*>(src));
        }
        static void destruct_(void* memory)
        {
            reinterpret_cast<T*>(memory)->~T();
        }

        static void save_(boost::uint8_t* data, std::size_t size, 
            oarchive_type& ar, const unsigned int version)
        {
            ar << *reinterpret_cast<T*>(data);
        }
        static void load_(boost::uint8_t* data, std::size_t size, 
            iarchive_type& ar, const unsigned int version)
        {
            ar >> *reinterpret_cast<T*>(data);
        }

    private:
        // support for construction, copying, destruction
        construct_function construct() const 
        { 
            return &manage_object_action::construct_; 
        }
        clone_function clone() const
        {
            return &manage_object_action::clone_; 
        }
        destruct_function destruct() const
        {
            return &manage_object_action::destruct_; 
        }

        // serialization support
        virtual serialize_save_function save() const
        { 
            return &manage_object_action::save_; 
        }
        virtual serialize_load_function load() const
        { 
            return &manage_object_action::load_; 
        }

    public:
        manage_object_action_base const& get_instance() const
        {
            static manage_object_action const instance =
                manage_object_action();
            return instance;
        }

        /// serialization support
        static void register_base()
        {
            using namespace boost::serialization;
            void_cast_register<manage_object_action, manage_object_action_base>();
        }

    private:
        // serialization support, just serialize the type
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) 
        {
            using namespace boost::serialization;
            ar & base_object<manage_object_action_base>(*this);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct manage_object_action<boost::uint8_t> : manage_object_action_base
    {
        manage_object_action() {}

        /// serialization support
        static void register_base()
        {
            using namespace boost::serialization;
            void_cast_register<manage_object_action, manage_object_action_base>();
        }

    private:
        // serialization support, just serialize the type
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) 
        {
            using namespace boost::serialization;
            ar & base_object<manage_object_action_base>(*this);
        }
    };

    inline manage_object_action_base const& 
    manage_object_action_base::get_instance() const
    {
        static manage_object_action<boost::uint8_t> const instance =
                manage_object_action<boost::uint8_t>();
        return instance;
    }
}}

#define HPX_REGISTER_MANAGE_OBJECT_ACTION(object_action, name)                \
        BOOST_CLASS_EXPORT(object_action)                                     \
        HPX_REGISTER_BASE_HELPER(object_action, name)                         \
    /***/

#include <hpx/config/warnings_suffix.hpp>

#endif


