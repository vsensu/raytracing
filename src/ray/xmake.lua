add_requires("glm")

target("ray")
    set_kind("binary")
    add_files("*.cpp")
    add_packages("glm")
    