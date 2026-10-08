# Repository instructions

## Project structure

This repository is a collection of independent programming exercises, not a
single application. Most source files in the repository root are standalone
examples in Python, JavaScript, Java, C++, or C#. Several demonstrate the same
idea in more than one language: sorting algorithms, array/matrix conversion,
and checkers. Treat each source file as its own program; there is no shared
runtime or cross-language build.

The sorting examples generally mutate their input array in place. The checkers
programs are separate implementations: `damas.java` is the more complete
interactive game and records moves in memory, with an option to save them to
`partida_damas.txt`; `dama.cpp` is another standalone implementation.

The root-level exercise files are the project sources. `oracleJdk-26/` is a
bundled JDK, not an application module; avoid editing its contents for changes
to the exercises.

## Build and run

There is no repository-wide build system, dependency manifest, automated test
suite, or configured linter. Run the one standalone program being changed and
check its output; do not assume running one file exercises the others.

Examples from the repository root (PowerShell):

```powershell
python .\heapsort.py
node .\orden14.js
g++ .\ordenamiento14.cpp -o .\ordenamiento14.exe
.\ordenamiento14.exe
.\oracleJdk-26\bin\javac.exe .\damas.java
.\oracleJdk-26\bin\java.exe damas
```

For Java examples, compile the individual source file and run its class; the
class name is not always the same casing as the source filename. For C#,
compile the chosen `.cs` file with an available C# compiler, then run the
resulting executable. No project-level test or lint command is defined.

## Code conventions and behavior

- User-facing prompts and output are generally in Spanish. Preserve that
  language when extending an exercise.
- Examples are intentionally small and self-contained. Similar algorithms in
  different files/languages are separate demonstrations, not shared modules;
  keep a change scoped to the relevant implementation unless the request calls
  for matching examples to be updated too.
- Python entry-point conventions vary: some demos use an
  `if __name__ == "__main__":` guard, while others run their demonstration at
  module load. Run those files as scripts rather than importing them casually.
- Preserve each language's existing standalone style and, for Java, keep the
  public class name consistent with its source filename.
