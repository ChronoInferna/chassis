from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class titleRecipe(ConanFile):  # TODO
    name = "title"  # TODO
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    # This recipe is aimed at a consumer scenario. If you want to create
    # a package, then you should add the following attributes/methods:
    #   * exports_sources attribute (https://docs.conan.io/2/reference/conanfile/attributes.html#exports-sources)
    #   * package method (https://docs.conan.io/2/reference/conanfile/methods/package.html)
    #   * package_info method (https://docs.conan.io/2/reference/conanfile/methods/package_info.html)
