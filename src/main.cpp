#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include "map"
#include "opennurbs_public.h"
#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


PYBIND11_MAKE_OPAQUE(std::vector<double>);
PYBIND11_MAKE_OPAQUE(std::map<std::string, double>);

// ...

int add(int i, int j) {
    return i + j;
}


double dist(const ON_3dPoint& point_a,const ON_3dPoint& point_b){
    return point_a.DistanceTo(point_b);
}


ON_3dPoint VectorToON_3dPoint(const std::vector<double>& point){
    return ON_3dPoint(point[0], point[1], point[2]);
}





class PyOnPoint {
public:
    PyOnPoint(const double &x, const double &y, const double &z) : xyz({x,y,z}) {}

    void XYZ_Setter(double &x_,
                    double &y_,
                    double &z_){
        xyz=std::vector<double>({x_, y_, z_});
    }

    std::vector<double> XYZ_Getter(){
        return xyz;
    }

    double Distance(const PyOnPoint &other){

        auto on_pt_a = this->toON();
        auto on_ptb = VectorToON_3dPoint(other.xyz);
        return dist(on_pt_a, on_ptb);


    }
private:
    std::vector<double> xyz;
    ON_3dPoint toON( ){
        return VectorToON_3dPoint(xyz);
    }
};


namespace py = pybind11;


PYBIND11_MODULE(nurbstools, m) {
    py::bind_vector<std::vector<double>>(m, "VectorDouble");
    py::bind_map<std::map<std::string, double>>(m, "MapStringDouble");
    py::class_<PyOnPoint>(m, "Point")
            .def(py::init<const double & ,const double &, const double &>())
            .def_property("xyz", &PyOnPoint::XYZ_Getter, &PyOnPoint::XYZ_Setter)
            .def("distance",&PyOnPoint::Distance);

    m.doc() = R"pbdoc(
    Pybind11 nurbstools plugin
        -----------------------

        .. currentmodule:: nurbstools

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
