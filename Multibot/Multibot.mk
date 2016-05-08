##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug_64bit
ProjectName            :=Multibot
ConfigurationName      :=Debug_64bit
WorkspacePath          := "/home/karol/Dokumenty/Mój stolik"
ProjectPath            := "/home/karol/Dokumenty/Mój stolik/Multibot"
IntermediateDirectory  :=./Debug-x64
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Karol Krupa
Date                   :=29/03/16
CodeLitePath           :="/home/karol/.codelite"
LinkerName             :=/usr/bin/g++-4.9
SharedObjectLinkerName :=/usr/bin/g++-4.9 -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Multibot.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -m64
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./Functions $(IncludeSwitch)./Functions/WelcomeMessage $(IncludeSwitch)./Functions/AntyVPN $(IncludeSwitch)./Functions/ChannelCreator $(IncludeSwitch)./Loger $(IncludeSwitch)./TeamSpeak3_API $(IncludeSwitch)./TeamSpeak3_API/Socket $(IncludeSwitch)./TeamSpeak3_API/Structs $(IncludeSwitch)./Extras $(IncludeSwitch)./Extras/ConfigReader $(IncludeSwitch)./Extras/Menu $(IncludeSwitch)./ConfigCreator 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)pthread 
ArLibs                 :=  "pthread" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++-4.9
CC       := /usr/bin/gcc-4.9
CXXFLAGS :=  -g -O0 -std=c++11 -Wall -m64 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Functions_Function.cpp$(ObjectSuffix) $(IntermediateDirectory)/Loger_Loger.cpp$(ObjectSuffix) $(IntermediateDirectory)/TeamSpeak3_API_Ts3API.cpp$(ObjectSuffix) $(IntermediateDirectory)/ConfigCreator_ConfigCreator.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/WelcomeMessage_WelcomeMessage.cpp$(ObjectSuffix) $(IntermediateDirectory)/AntyVPN_AntyVPN.cpp$(ObjectSuffix) $(IntermediateDirectory)/PokeBot_PokeBot.cpp$(ObjectSuffix) $(IntermediateDirectory)/ChannelCreator_ChannelCreator.cpp$(ObjectSuffix) $(IntermediateDirectory)/Socket_Ts3Socket.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Structs_Ts3Structs.cpp$(ObjectSuffix) $(IntermediateDirectory)/ConfigReader_ConfigFile.cpp$(ObjectSuffix) $(IntermediateDirectory)/Menu_Menu.cpp$(ObjectSuffix) $(IntermediateDirectory)/wwwReader_www.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug-x64 || $(MakeDirCommand) ./Debug-x64


$(IntermediateDirectory)/.d:
	@test -d ./Debug-x64 || $(MakeDirCommand) ./Debug-x64

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Functions_Function.cpp$(ObjectSuffix): Functions/Function.cpp $(IntermediateDirectory)/Functions_Function.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/Functions/Function.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Functions_Function.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Functions_Function.cpp$(DependSuffix): Functions/Function.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Functions_Function.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Functions_Function.cpp$(DependSuffix) -MM "Functions/Function.cpp"

$(IntermediateDirectory)/Functions_Function.cpp$(PreprocessSuffix): Functions/Function.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Functions_Function.cpp$(PreprocessSuffix) "Functions/Function.cpp"

$(IntermediateDirectory)/Loger_Loger.cpp$(ObjectSuffix): Loger/Loger.cpp $(IntermediateDirectory)/Loger_Loger.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/Loger/Loger.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Loger_Loger.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Loger_Loger.cpp$(DependSuffix): Loger/Loger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Loger_Loger.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Loger_Loger.cpp$(DependSuffix) -MM "Loger/Loger.cpp"

$(IntermediateDirectory)/Loger_Loger.cpp$(PreprocessSuffix): Loger/Loger.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Loger_Loger.cpp$(PreprocessSuffix) "Loger/Loger.cpp"

$(IntermediateDirectory)/TeamSpeak3_API_Ts3API.cpp$(ObjectSuffix): TeamSpeak3_API/Ts3API.cpp $(IntermediateDirectory)/TeamSpeak3_API_Ts3API.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/TeamSpeak3_API/Ts3API.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TeamSpeak3_API_Ts3API.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TeamSpeak3_API_Ts3API.cpp$(DependSuffix): TeamSpeak3_API/Ts3API.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TeamSpeak3_API_Ts3API.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TeamSpeak3_API_Ts3API.cpp$(DependSuffix) -MM "TeamSpeak3_API/Ts3API.cpp"

$(IntermediateDirectory)/TeamSpeak3_API_Ts3API.cpp$(PreprocessSuffix): TeamSpeak3_API/Ts3API.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TeamSpeak3_API_Ts3API.cpp$(PreprocessSuffix) "TeamSpeak3_API/Ts3API.cpp"

$(IntermediateDirectory)/ConfigCreator_ConfigCreator.cpp$(ObjectSuffix): ConfigCreator/ConfigCreator.cpp $(IntermediateDirectory)/ConfigCreator_ConfigCreator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/ConfigCreator/ConfigCreator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ConfigCreator_ConfigCreator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ConfigCreator_ConfigCreator.cpp$(DependSuffix): ConfigCreator/ConfigCreator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ConfigCreator_ConfigCreator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ConfigCreator_ConfigCreator.cpp$(DependSuffix) -MM "ConfigCreator/ConfigCreator.cpp"

$(IntermediateDirectory)/ConfigCreator_ConfigCreator.cpp$(PreprocessSuffix): ConfigCreator/ConfigCreator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ConfigCreator_ConfigCreator.cpp$(PreprocessSuffix) "ConfigCreator/ConfigCreator.cpp"

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/WelcomeMessage_WelcomeMessage.cpp$(ObjectSuffix): Functions/WelcomeMessage/WelcomeMessage.cpp $(IntermediateDirectory)/WelcomeMessage_WelcomeMessage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/Functions/WelcomeMessage/WelcomeMessage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/WelcomeMessage_WelcomeMessage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/WelcomeMessage_WelcomeMessage.cpp$(DependSuffix): Functions/WelcomeMessage/WelcomeMessage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/WelcomeMessage_WelcomeMessage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/WelcomeMessage_WelcomeMessage.cpp$(DependSuffix) -MM "Functions/WelcomeMessage/WelcomeMessage.cpp"

$(IntermediateDirectory)/WelcomeMessage_WelcomeMessage.cpp$(PreprocessSuffix): Functions/WelcomeMessage/WelcomeMessage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/WelcomeMessage_WelcomeMessage.cpp$(PreprocessSuffix) "Functions/WelcomeMessage/WelcomeMessage.cpp"

$(IntermediateDirectory)/AntyVPN_AntyVPN.cpp$(ObjectSuffix): Functions/AntyVPN/AntyVPN.cpp $(IntermediateDirectory)/AntyVPN_AntyVPN.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/Functions/AntyVPN/AntyVPN.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AntyVPN_AntyVPN.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AntyVPN_AntyVPN.cpp$(DependSuffix): Functions/AntyVPN/AntyVPN.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AntyVPN_AntyVPN.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/AntyVPN_AntyVPN.cpp$(DependSuffix) -MM "Functions/AntyVPN/AntyVPN.cpp"

$(IntermediateDirectory)/AntyVPN_AntyVPN.cpp$(PreprocessSuffix): Functions/AntyVPN/AntyVPN.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AntyVPN_AntyVPN.cpp$(PreprocessSuffix) "Functions/AntyVPN/AntyVPN.cpp"

$(IntermediateDirectory)/PokeBot_PokeBot.cpp$(ObjectSuffix): Functions/PokeBot/PokeBot.cpp $(IntermediateDirectory)/PokeBot_PokeBot.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/Functions/PokeBot/PokeBot.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PokeBot_PokeBot.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PokeBot_PokeBot.cpp$(DependSuffix): Functions/PokeBot/PokeBot.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PokeBot_PokeBot.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PokeBot_PokeBot.cpp$(DependSuffix) -MM "Functions/PokeBot/PokeBot.cpp"

$(IntermediateDirectory)/PokeBot_PokeBot.cpp$(PreprocessSuffix): Functions/PokeBot/PokeBot.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PokeBot_PokeBot.cpp$(PreprocessSuffix) "Functions/PokeBot/PokeBot.cpp"

$(IntermediateDirectory)/ChannelCreator_ChannelCreator.cpp$(ObjectSuffix): Functions/ChannelCreator/ChannelCreator.cpp $(IntermediateDirectory)/ChannelCreator_ChannelCreator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/Functions/ChannelCreator/ChannelCreator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ChannelCreator_ChannelCreator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ChannelCreator_ChannelCreator.cpp$(DependSuffix): Functions/ChannelCreator/ChannelCreator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ChannelCreator_ChannelCreator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ChannelCreator_ChannelCreator.cpp$(DependSuffix) -MM "Functions/ChannelCreator/ChannelCreator.cpp"

$(IntermediateDirectory)/ChannelCreator_ChannelCreator.cpp$(PreprocessSuffix): Functions/ChannelCreator/ChannelCreator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ChannelCreator_ChannelCreator.cpp$(PreprocessSuffix) "Functions/ChannelCreator/ChannelCreator.cpp"

$(IntermediateDirectory)/Socket_Ts3Socket.cpp$(ObjectSuffix): TeamSpeak3_API/Socket/Ts3Socket.cpp $(IntermediateDirectory)/Socket_Ts3Socket.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/TeamSpeak3_API/Socket/Ts3Socket.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Socket_Ts3Socket.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Socket_Ts3Socket.cpp$(DependSuffix): TeamSpeak3_API/Socket/Ts3Socket.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Socket_Ts3Socket.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Socket_Ts3Socket.cpp$(DependSuffix) -MM "TeamSpeak3_API/Socket/Ts3Socket.cpp"

$(IntermediateDirectory)/Socket_Ts3Socket.cpp$(PreprocessSuffix): TeamSpeak3_API/Socket/Ts3Socket.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Socket_Ts3Socket.cpp$(PreprocessSuffix) "TeamSpeak3_API/Socket/Ts3Socket.cpp"

$(IntermediateDirectory)/Structs_Ts3Structs.cpp$(ObjectSuffix): TeamSpeak3_API/Structs/Ts3Structs.cpp $(IntermediateDirectory)/Structs_Ts3Structs.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/TeamSpeak3_API/Structs/Ts3Structs.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Structs_Ts3Structs.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Structs_Ts3Structs.cpp$(DependSuffix): TeamSpeak3_API/Structs/Ts3Structs.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Structs_Ts3Structs.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Structs_Ts3Structs.cpp$(DependSuffix) -MM "TeamSpeak3_API/Structs/Ts3Structs.cpp"

$(IntermediateDirectory)/Structs_Ts3Structs.cpp$(PreprocessSuffix): TeamSpeak3_API/Structs/Ts3Structs.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Structs_Ts3Structs.cpp$(PreprocessSuffix) "TeamSpeak3_API/Structs/Ts3Structs.cpp"

$(IntermediateDirectory)/ConfigReader_ConfigFile.cpp$(ObjectSuffix): Extras/ConfigReader/ConfigFile.cpp $(IntermediateDirectory)/ConfigReader_ConfigFile.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/Extras/ConfigReader/ConfigFile.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ConfigReader_ConfigFile.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ConfigReader_ConfigFile.cpp$(DependSuffix): Extras/ConfigReader/ConfigFile.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ConfigReader_ConfigFile.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ConfigReader_ConfigFile.cpp$(DependSuffix) -MM "Extras/ConfigReader/ConfigFile.cpp"

$(IntermediateDirectory)/ConfigReader_ConfigFile.cpp$(PreprocessSuffix): Extras/ConfigReader/ConfigFile.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ConfigReader_ConfigFile.cpp$(PreprocessSuffix) "Extras/ConfigReader/ConfigFile.cpp"

$(IntermediateDirectory)/Menu_Menu.cpp$(ObjectSuffix): Extras/Menu/Menu.cpp $(IntermediateDirectory)/Menu_Menu.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/Extras/Menu/Menu.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Menu_Menu.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Menu_Menu.cpp$(DependSuffix): Extras/Menu/Menu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Menu_Menu.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Menu_Menu.cpp$(DependSuffix) -MM "Extras/Menu/Menu.cpp"

$(IntermediateDirectory)/Menu_Menu.cpp$(PreprocessSuffix): Extras/Menu/Menu.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Menu_Menu.cpp$(PreprocessSuffix) "Extras/Menu/Menu.cpp"

$(IntermediateDirectory)/wwwReader_www.cpp$(ObjectSuffix): Extras/wwwReader/www.cpp $(IntermediateDirectory)/wwwReader_www.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/karol/Dokumenty/Mój stolik/Multibot/Extras/wwwReader/www.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wwwReader_www.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wwwReader_www.cpp$(DependSuffix): Extras/wwwReader/www.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wwwReader_www.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wwwReader_www.cpp$(DependSuffix) -MM "Extras/wwwReader/www.cpp"

$(IntermediateDirectory)/wwwReader_www.cpp$(PreprocessSuffix): Extras/wwwReader/www.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wwwReader_www.cpp$(PreprocessSuffix) "Extras/wwwReader/www.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug-x64/


