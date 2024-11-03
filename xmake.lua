add_rules("mode.debug", "mode.release", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

if is_mode("debug") then
    set_runtimes("MDd")
else
    set_runtimes("MD")
end

add_requires("icu4c", {debug = true})
add_requires("nlohmann_json", {debug = true})
add_requires("leveldb", {debug = true})
add_requires("cpp-httplib", {configs = {ssl = true}, debug = true})
add_requireconfs("cpp-httplib.openssl3", {override = true, version = "3.3.1", debug = true})

target("MandarinLexicon")
    add_cxflags(
        "/utf-8",
        "/W4",
        "/INCREMENTAL"
    )
    add_packages(
        "icu4c",
        "nlohmann_json",
        "leveldb",
        "cpp-httplib"
    )
    if is_mode("debug") then
        add_defines("_DEBUG")
    end
    set_kind("binary")
    add_includedirs("src")
    add_headerfiles("src**/*.h")
    add_files("src**/*.cpp")
    set_languages("clatest", "cxxlatest")
    set_symbols("debug", "debug", "edit")
