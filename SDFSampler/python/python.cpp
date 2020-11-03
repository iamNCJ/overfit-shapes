#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include "AABB_tree/AABB_tree.h"
#include "IO/MeshLoader.h"
#include "SDFSampler/PointSampler.h"
#include "NormalizeMesh.h"

using namespace SDFSampler;
namespace py = pybind11;
PYBIND11_MODULE(SDFSampler, m) {
    py::class_<AABB_tree<float>>(m, "AABB_tree")
        .def(py::init<const Eigen::Ref<const Eigen::MatrixXf>&,
            const Eigen::Ref<const Eigen::Matrix<int, Eigen::Dynamic, 3, Eigen::RowMajor>>&>())
        .def("closestFace", &AABB_tree<float>::closestFace)
        .def("closestPoint", &AABB_tree<float>::closestPoint);

    py::class_<MeshLoader>(m, "MeshLoader")
        .def(py::init<>())
        .def("read", &MeshLoader::read);

    py::class_<PointSampler>(m, "PointSampler")
        .def(py::init<const Eigen::Ref<const Eigen::MatrixXf>,
            const Eigen::Ref<const Eigen::Matrix<int, Eigen::Dynamic, 3, Eigen::RowMajor>>,
            int>(), py::arg("vertices"), py::arg("faces"), py::arg("seed") = -1)
        .def("sample", &PointSampler::sample, py::arg("numPoints") = 1, py::arg("sampleSetScale") = 10)
        .def_readwrite("beta", &PointSampler::beta_)
        .def_readwrite("seed", &PointSampler::seed_);

    m.def("normalizeMeshToUnitSphere", &normalizeMeshToUnitSphere, "Normalizes a mesh to the unit sphere at origin");
}