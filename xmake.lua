add_rules("mode.debug", "mode.release", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

if is_mode("release") then
    set_runtimes("MD")
else
    set_runtimes("MDd")
end

add_requires("nlohmann_json")
add_requires("leveldb")
add_requires("cpp-httplib", {configs = {ssl = true}})
add_requireconfs("cpp-httplib.openssl3", {override = true, version = "3.3.1"})

target("MandarinLexicon")
    add_cxflags(
        "/utf-8",
        "/W4",
        "/INCREMENTAL"
    )
    add_packages(
        "nlohmann_json",
        "leveldb",
        "cpp-httplib"
    )
    set_kind("binary")
    add_includedirs("src")
    add_headerfiles("src**/*.h")
    add_files("src**/*.cpp")
    set_languages("clatest", "cxxlatest")
    set_symbols("debug", "debug", "edit")
