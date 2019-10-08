##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=ImageClass
ConfigurationName      :=Release
WorkspacePath          :=/Users/Pinho/Documents/Doc/PRGBAIXONIVEL/Testes
ProjectPath            :=/Users/Pinho/Documents/CG/OpenGL/MediaClass/ImageClass
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Marcio Sarroglia Pinho
Date                   :=09/06/2017
CodeLitePath           :="/Users/Pinho/Library/Application Support/codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -dynamiclib -fPIC
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
ObjectsFileList        :="ImageClass.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O2 -framework CoreFoundation -framework OpenGL -framework GLUT
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=   $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/Applications/codelite2.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/ExemploDeManipulacaoDeImagens-PRONTA.cpp$(ObjectSuffix) $(IntermediateDirectory)/ImageClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/SOIL_image_DXT.cpp$(ObjectSuffix) $(IntermediateDirectory)/SOIL_image_helper.cpp$(ObjectSuffix) $(IntermediateDirectory)/SOIL_SOIL.cpp$(ObjectSuffix) $(IntermediateDirectory)/SOIL_stb_image_aug.cpp$(ObjectSuffix) 



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
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/ExemploDeManipulacaoDeImagens-PRONTA.cpp$(ObjectSuffix): ExemploDeManipulacaoDeImagens-PRONTA.cpp $(IntermediateDirectory)/ExemploDeManipulacaoDeImagens-PRONTA.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/Pinho/Documents/CG/OpenGL/MediaClass/ImageClass/ExemploDeManipulacaoDeImagens-PRONTA.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ExemploDeManipulacaoDeImagens-PRONTA.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ExemploDeManipulacaoDeImagens-PRONTA.cpp$(DependSuffix): ExemploDeManipulacaoDeImagens-PRONTA.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ExemploDeManipulacaoDeImagens-PRONTA.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ExemploDeManipulacaoDeImagens-PRONTA.cpp$(DependSuffix) -MM ExemploDeManipulacaoDeImagens-PRONTA.cpp

$(IntermediateDirectory)/ExemploDeManipulacaoDeImagens-PRONTA.cpp$(PreprocessSuffix): ExemploDeManipulacaoDeImagens-PRONTA.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ExemploDeManipulacaoDeImagens-PRONTA.cpp$(PreprocessSuffix) ExemploDeManipulacaoDeImagens-PRONTA.cpp

$(IntermediateDirectory)/ImageClass.cpp$(ObjectSuffix): ImageClass.cpp $(IntermediateDirectory)/ImageClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/Pinho/Documents/CG/OpenGL/MediaClass/ImageClass/ImageClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ImageClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ImageClass.cpp$(DependSuffix): ImageClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ImageClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ImageClass.cpp$(DependSuffix) -MM ImageClass.cpp

$(IntermediateDirectory)/ImageClass.cpp$(PreprocessSuffix): ImageClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ImageClass.cpp$(PreprocessSuffix) ImageClass.cpp

$(IntermediateDirectory)/SOIL_image_DXT.cpp$(ObjectSuffix): SOIL/image_DXT.cpp $(IntermediateDirectory)/SOIL_image_DXT.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/Pinho/Documents/CG/OpenGL/MediaClass/ImageClass/SOIL/image_DXT.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SOIL_image_DXT.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SOIL_image_DXT.cpp$(DependSuffix): SOIL/image_DXT.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SOIL_image_DXT.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SOIL_image_DXT.cpp$(DependSuffix) -MM SOIL/image_DXT.cpp

$(IntermediateDirectory)/SOIL_image_DXT.cpp$(PreprocessSuffix): SOIL/image_DXT.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SOIL_image_DXT.cpp$(PreprocessSuffix) SOIL/image_DXT.cpp

$(IntermediateDirectory)/SOIL_image_helper.cpp$(ObjectSuffix): SOIL/image_helper.cpp $(IntermediateDirectory)/SOIL_image_helper.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/Pinho/Documents/CG/OpenGL/MediaClass/ImageClass/SOIL/image_helper.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SOIL_image_helper.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SOIL_image_helper.cpp$(DependSuffix): SOIL/image_helper.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SOIL_image_helper.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SOIL_image_helper.cpp$(DependSuffix) -MM SOIL/image_helper.cpp

$(IntermediateDirectory)/SOIL_image_helper.cpp$(PreprocessSuffix): SOIL/image_helper.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SOIL_image_helper.cpp$(PreprocessSuffix) SOIL/image_helper.cpp

$(IntermediateDirectory)/SOIL_SOIL.cpp$(ObjectSuffix): SOIL/SOIL.cpp $(IntermediateDirectory)/SOIL_SOIL.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/Pinho/Documents/CG/OpenGL/MediaClass/ImageClass/SOIL/SOIL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SOIL_SOIL.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SOIL_SOIL.cpp$(DependSuffix): SOIL/SOIL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SOIL_SOIL.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SOIL_SOIL.cpp$(DependSuffix) -MM SOIL/SOIL.cpp

$(IntermediateDirectory)/SOIL_SOIL.cpp$(PreprocessSuffix): SOIL/SOIL.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SOIL_SOIL.cpp$(PreprocessSuffix) SOIL/SOIL.cpp

$(IntermediateDirectory)/SOIL_stb_image_aug.cpp$(ObjectSuffix): SOIL/stb_image_aug.cpp $(IntermediateDirectory)/SOIL_stb_image_aug.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/Pinho/Documents/CG/OpenGL/MediaClass/ImageClass/SOIL/stb_image_aug.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SOIL_stb_image_aug.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SOIL_stb_image_aug.cpp$(DependSuffix): SOIL/stb_image_aug.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SOIL_stb_image_aug.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SOIL_stb_image_aug.cpp$(DependSuffix) -MM SOIL/stb_image_aug.cpp

$(IntermediateDirectory)/SOIL_stb_image_aug.cpp$(PreprocessSuffix): SOIL/stb_image_aug.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SOIL_stb_image_aug.cpp$(PreprocessSuffix) SOIL/stb_image_aug.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


