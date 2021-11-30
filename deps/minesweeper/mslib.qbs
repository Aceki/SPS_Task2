Library {
    type: "staticlibrary"
    name: "mslib"
    files: [
        "include/Minesweeper/cell.h",
        "include/Minesweeper/exceptions.h",
        "include/Minesweeper/game.h",
        "src/game.cpp"
    ]
    cpp.includePaths: [ "/include/Minesweeper", "/include" ]
    Depends { name: "cpp" }
    Export {
        cpp.includePaths: [ product.sourceDirectory + "/include" ]
        Depends { name: "cpp" }
    }
}
