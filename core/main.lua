--!strict

type CommandLineArguments = { [number]: string }

--[[ Entry Point ]]--
return function(c_args: CommandLineArguments)
    print("[Hula] Initializing Core!")
    print(string.format("Number of Command Line Arguments: %d\n", #c_args))
end
