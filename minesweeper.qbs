Project {
    name: "Minesweeper"
    buildDirectory: "build"
    Product {
        type: "application"
        name: "GUI" 
        targetName: "prog" 
        files: [
            "src/main.cpp",
            "src/gamewindow.h",
            "src/gamewindow.cpp",
            "src/settingswindow.h",
            "src/settingswindow.cpp",
            "src/field.h",
            "src/field.cpp",
            "src/cell.h",
            "src/cell.cpp"
        ]
        Depends { name: "cpp" }
        Depends { name: "mslib" }
        Depends { name: "Qt.widgets" }
    }
    Library {
        type: "staticlibrary"
        name: "mslib"
        sourceDirectory: "deps/minesweeper"
        files: [
            "deps/minesweeper/include/Minesweeper/exceptions.h",
            "deps/minesweeper/include/Minesweeper/game.h",
            "deps/minesweeper/src/game.cpp",
            "deps/minesweeper/include/Minesweeper/cell.h",
            "deps/minesweeper/src/cell.cpp"
        ]
        cpp.includePaths: [ "deps/minesweeper/include", "deps/minesweeper/include/Minesweeper" ]
        Depends { name: "cpp" }
        Depends { name: "Qt.core" }
        Export {
            cpp.includePaths: [ "deps/minesweeper/include" ]
            Depends { name: "cpp" }
        }
    }
}
