add_rules("mode.debug", "mode.release", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

if is_mode("release") then
    set_runtimes("MD")
else
    set_runtimes("MDd")
end

target("MandarinLexicon")
    add_cxflags(
        "/utf-8",
        "/W4"
    )
    set_kind("binary")
    -- add_headerfiles("src/**.h")
    add_files("src/**.cpp")
    set_languages("clatest", "cxxlatest")
    set_symbols("debug", "debug", "edit")
