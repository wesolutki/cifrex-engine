#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>

#include <Engine.hpp>

#include <iostream>

using namespace boost::python;
using namespace std;

struct iterable_converter
{
    /// @note Registers converter from a python interable type to the
    ///       provided type.
    template <typename Container>
    iterable_converter&
    from_python()
    {
        boost::python::converter::registry::push_back(
                    &iterable_converter::convertible,
                    &iterable_converter::construct<Container>,
                    boost::python::type_id<Container>());

        // Support chaining.
        return *this;
    }

    /// @brief Check if PyObject is iterable.
    static void* convertible(PyObject* object)
    {
        return PyObject_GetIter(object) ? object : NULL;
    }

    /// @brief Convert iterable PyObject to C++ container type.
    ///
    /// Container Concept requirements:
    ///
    ///   * Container::value_type is CopyConstructable.
    ///   * Container can be constructed and populated with two iterators.
    ///     I.e. Container(begin, end)
    template <typename Container>
    static void construct(
            PyObject* object,
            boost::python::converter::rvalue_from_python_stage1_data* data)
    {
        namespace python = boost::python;
        // Object is a borrowed reference, so create a handle indicting it is
        // borrowed for proper reference counting.
        python::handle<> handle(python::borrowed(object));

        // Obtain a handle to the memory block that the converter has allocated
        // for the C++ type.
        typedef python::converter::rvalue_from_python_storage<Container>
                storage_type;
        void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes;

        typedef python::stl_input_iterator<typename Container::value_type>
                iterator;

        // Allocate the C++ type into the converter's memory block, and assign
        // its handle to the converter's convertible variable.  The C++
        // container is populated by passing the begin and end iterators of
        // the python object to the container's constructor.
        new (storage) Container(
                    iterator(python::object(handle)), // begin
                    iterator());                      // end
        data->convertible = storage;
    }
};

template<class T>
struct VecToList
{
    static PyObject* convert(const std::vector<T>& vec)
    {
        cout << "VecToList" << endl;
        boost::python::list* l = new boost::python::list();
        for(size_t i = 0; i < vec.size(); i++)
            (*l).append(vec[i]);

        return l->ptr();
    }
};

template<class T>
struct VecOfTuplesToListOfTuples
{
    static PyObject* convert(const std::vector<T>& vec)
    {
        boost::python::list* l = new boost::python::list();
        for(size_t i = 0; i < vec.size(); i++)
        {
            boost::python::list* l2 = new boost::python::list();
            (*l2).append(std::get<0>(vec[i]));
            (*l2).append(std::get<1>(vec[i]));
            (*l2).append(std::get<2>(vec[i]));
            (*l).append(*l2);
        }

        return l->ptr();
    }

    static boost::python::list* convert2(const std::vector<T>& vec)
    {
        boost::python::list* l = new boost::python::list();
        for(size_t i = 0; i < vec.size(); i++)
        {
            boost::python::list* l2 = new boost::python::list();
            (*l2).append(std::get<0>(vec[i]));
            (*l).append(*l2);
        }

        return l;
    }
};

struct FileMatchesConverter
{
    static boost::python::list* convert2(Matches const& vec)
    {
        boost::python::list* l = new boost::python::list();
        for(size_t i = 0; i < vec.size(); i++)
        {
            boost::python::list* l2 = new boost::python::list();
            (*l2).append(std::get<0>(vec[i]));
            (*l2).append(std::get<1>(vec[i]));
            (*l2).append(std::get<2>(vec[i]));
            (*l).append(*l2);
        }

        return l;
    }

    static PyObject* convert(FileMatches const& files)
    {
        boost::python::list* l = new boost::python::list();
        for(size_t i = 0; i < files.size(); i++)
        {
            boost::python::list* l2 = new boost::python::list();
            (*l2).append(std::get<0>(files[i]));
            (*l2).append(*convert2(std::get<1>(files[i])));

            (*l).append(*l2);
        }

        return l->ptr();
    }
};

BOOST_PYTHON_MODULE(libpycifrex)
{
    to_python_converter<FileMatches, FileMatchesConverter>();
    to_python_converter<Matches, VecOfTuplesToListOfTuples<Match>>();
    to_python_converter<Extensions, VecToList<std::string> >();

    iterable_converter()
            .from_python<Matches>()
            .from_python<Extensions>()
            .from_python<std::vector<Vex> >()
            ;

    class_<Vex>("Vex")
            .def(init<std::string const&>())
            .def("match", &Vex::match)
            ;

    class_<Engine>("Engine")
            .def(init<std::vector<Vex> const&>())
            .def("ok", &Engine::ok)
            .def("search", &Engine::search)
            .def("searchInFile", &Engine::searchInFile)
            ;
}
