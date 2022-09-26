# nurbstools


|      CI              | status |
|----------------------|--------|
| MSVC 2015            | [![AppVeyor][appveyor-badge]][appveyor-link] |



## Prerequisites

* A compiler with C++11 support
* Pip 10+ or CMake >= 3.4 (or 3.8+ on Windows, which was the first version to support VS 2015)
* Ninja or Pip 10+


## Installation

Just clone this repository and pip install. Note the `--recursive` option which is
needed for the pybind11 submodule:

```bash
git clone --recursive https://github.com/pybind/nurbstools.git
pip install ./nurbstools
```

With the `setup.py` file included in this example, the `pip install` command will
invoke CMake and build the pybind11 module as specified in `CMakeLists.txt`.



## Building the documentation

Documentation for the example project is generated using Sphinx. Sphinx has the
ability to automatically inspect the signatures and documentation strings in
the extension module to generate beautiful documentation in a variety formats.
The following command generates HTML-based reference documentation; for other
formats please refer to the Sphinx manual:

 - `cd nurbstools/docs`
 - `make html`


## License

Pybind11 is provided under a BSD-style license that can be found in the LICENSE
file. By using, distributing, or contributing to this project, you agree to the
terms and conditions of this license.


## Test call

```python
import nurbstools
nurbstools.add(1, 2)
```

[`cibuildwheel`]:          https://cibuildwheel.readthedocs.io
[FAQ]: http://pybind11.rtfd.io/en/latest/faq.html#working-with-ancient-visual-studio-2009-builds-on-windows
[vs2015_runtime]: https://www.microsoft.com/en-us/download/details.aspx?id=48145
[scikit-build]: https://scikit-build.readthedocs.io/en/latest/
