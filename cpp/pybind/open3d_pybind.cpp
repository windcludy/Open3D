// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// Copyright (c) 2018-2023 www.open3d.org
// SPDX-License-Identifier: MIT
// ----------------------------------------------------------------------------

#include "pybind/open3d_pybind.h"

#include "open3d/core/MemoryManagerStatistic.h"
#include "open3d/utility/Logging.h"
#include "pybind/camera/camera.h"
#include "pybind/core/core.h"
#include "pybind/data/dataset.h"
#include "pybind/geometry/geometry.h"
#include "pybind/io/io.h"
#include "pybind/ml/ml.h"
#include "pybind/pipelines/pipelines.h"
#include "pybind/t/t.h"
#include "pybind/utility/utility.h"
#include <TargetConditionals.h>
#if !TARGET_OS_IOS
#include "pybind/visualization/visualization.h"
#endif

namespace open3d {

namespace docstring {
void init_static_property();
}

PYBIND11_MODULE(pybind, m) {
    docstring::init_static_property();
    
    utility::Logger::GetInstance().SetPrintFunction([](const std::string& msg) {
        py::gil_scoped_acquire acquire;
        py::print(msg);
    });

    m.doc() = "Python binding of Open3D";

    // Check Open3D CXX11_ABI with
    // import open3d as o3d; print(o3d.open3d_pybind._GLIBCXX_USE_CXX11_ABI)
    m.add_object("_GLIBCXX_USE_CXX11_ABI",
                 _GLIBCXX_USE_CXX11_ABI ? Py_True : Py_False);

    // The binding order matters: if a class haven't been binded, binding the
    // user of this class will result in "could not convert default argument
    // into a Python object" error.
    utility::pybind_utility(m);

    camera::pybind_camera(m);
    core::pybind_core(m);
    data::pybind_data(m);
    geometry::pybind_geometry(m);
#if !TARGET_OS_IOS
    t::pybind_t(m);
#endif
    ml::pybind_ml(m);
    io::pybind_io(m);
    pipelines::pybind_pipelines(m);
#if !TARGET_OS_IOS
    visualization::pybind_visualization(m);
#endif

    // pybind11 will internally manage the lifetime of default arguments for
    // function bindings. Since these objects will live longer than the memory
    // manager statistics, the latter will report leaks. Reset the statistics to
    // ignore them and transfer the responsibility to pybind11.
    core::MemoryManagerStatistic::GetInstance().Reset();
}

}  // namespace open3d
