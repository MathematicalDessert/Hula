<h1 align="center">
  <a href="https://github.com/MathematicalDessert/Hula">Hula Editor</a>
</h1>

<h4 align="center">A Luau IDE written in Luau.</h4>

Hula is a ***WIP*** IDE written in Luau with power and simplicity in mind. It will make use of the powerful foundations
laid by Roblox with [Luau](https://github.com/Roblox/luau), including but not limited to: **code debugging**, **disassembly**, and **intelligent type-checking**.

Hula aims to be:

* 🔧***Extensible***. Adding features should be easy for both experienced and non-experienced Luau users.
* 💨***Performant***. As a showcase of the performance of Luau, Hula should also highly performant in all areas.
* ✔️***Reliable***. Using Hula should be a smooth experience with no unexpected hangs or crashes.
* 💻***Native***. Hula should run on all platforms equally with similar performance.
* 🪶***Lightweight***. Shouldn't have many dependencies, and any dependencies (or plugins) should be decoupleable.
* 🪟***Simple, but beautiful***. A clean user interface with minimal clutter and powerful tools.

Hula does **NOT** aim to be:

* ❌***A replacement*** to your normal Luau environment, be that Roblox Studio or Visual Studio Code.
* ❌***A general purpose*** editor like Visual Studio Code and Co.

If you're interested in working on the project or just want to talk with developers, please join the Discord: https://discord.gg/Mc72duvKMP.

## Components

### Bedrock
Bedrock is the C++ backbone of the project. It is here that Luau is incorporated into the project. It is also where any high-performance methods are included.

### Core
The core is the true editor code. It is written in Luau and is in the folder [core](core). This is where the majority of the logic necessary for the editor will be, excluding what necessarily needs to be implemented in C++.

The core is structured into multiple subdirectories with descriptive names. Every file is a module.

## Design Philosophy
Powerful simplicity is the name of the game.

Whenever possible, we would prefer code be written in Luau and use the exported API. If a feature requires high performance with zero abstraction penalty, then implementation in C++ and export is acceptable.

## Planned Features

💚 - Definitely (not in development yet).
🔜 - In development.
🤷‍♀️ - Not certain.

Features:
- [ ] 💚 Full Luau Debugger
- [ ] 💚 Visual Disassembler (Similar to https://www.luac.nl/)
- [ ] 💚 Luau Plugin Support
- [ ] 🤷‍♀️ Intelligent Auto-Completion
- [ ] 🤷‍♀️ Integration with Roblox tools(?)

## Contributing

The project is still in its infancy, and as such making contributions may be difficult. Despite this, all contributions are welcome!

It may be better to discuss potential features and implementations in the [Discord](https://discord.gg/Mc72duvKMP), [Discussions](https://github.com/MathematicalDessert/Hula/discussions), or an issue.

More information on contributing will come soon.

## License
Hula is distributed under the terms of the [MIT License](LICENSE). It takes inspiration from [rxi/lite](https://github.com/rxi/lite) and implements Luau which are both also distributed under MIT. You are permitted to redistribute Hula and/or modify it under the aforementioned terms of the license.
