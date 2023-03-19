# TCsys_public
The public ver of tcsys. The last stable version is a1.03. You shall find it in branch alpha.
Actually all source code is in alpha, this main is for read.

For help, it's compiled by VS and I left the sln in the realise.
It should be fine if compiled by other ODE but better to use at least c++ 14.

To acquire the list of useful functions, read help and datafile example in tcsys.h
The DEBUG can be de-define to avoid see these system messages.
There are some function not working and some weird logics (like you have to select person before create a new event), that would be fine someday. maybe.

you can always directly delete or modify the data.txt and config.txt to avoid all-in-console input.

As a supp note, this undoredo class is in general type, not just for this projet. other hand, there is a linear relationship of main---tcsys---person---bill.
Reaction and tdp.h is nothing but a blueprint help to design and wasted.

Well, that's it.
