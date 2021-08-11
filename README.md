


# Shepherding Library for Swarm Guidance



## Project Aim

This project aims at providing a library for shepherding behaviours that can be used by a multi-agent system to model context-aware swarm intelligence. The shepherding behaviours library shall include different behaviours by different actors in a shepherding environment, which allows flexibility in setting up different agents with different behavioural characteristics. A simulation environment is also provided to model how these behaviours can be imported and used by the different agents. Concepts, and model design, and details are found in the following publications by our research team:

[1] El-Fiqi, H., Campbell, B., Elsayed, S., Perry, A., Singh, H. K., Hunjet, R., & Abbass, H. A. (2020). The Limits of Reactive Shepherding Approaches for Swarm Guidance. IEEE Access, 8, 214658-214671.

[2] El-Fiqi, H., Campbell, B., Elsayed, S., Perry, A., Singh, H. K., Hunjet, R., & Abbass, H. (2020, July). A preliminary study towards an improved shepherding model. In Proceedings of the 2020 Genetic and Evolutionary Computation Conference Companion (pp. 75-76).

## Project File Structure

The project has two sub-projects: a library project (**ShepherdingLibC**), and a simulation project (**ShepherdingSimC_V1**) that uses the library project.

The Visual Studio Solution is configured to start using the simulation project. The main function of the simulation project is in *“ShepherdingSimC_V1.cpp”* file.

#### Input Files

The simulation project starts by loading the XML configuration files. There are two configuration files that a user can use to configure the simulation: One for the simulation parameters *“config.xml”* and the second for the visualization parameters *"VisualizationOptions.xml"*.  These two files are located in the "InputFiles" directory.

#### Output Files

The output files will be written to the same directory as “Config.xml” file location.

Output files format and contents:

1. Config_CompletionTimeOnly.txt: A single row of two fields: total number of steps, a binary index {1: for successful tasks, 0: for not successful tasks}

2. Config_RunConfigurationSaved.txt: A copy of the input configuration saved for records keeping.

3. Config_StaticObstaclesOutputFile.csv: a comma-separated values file. Each row refers to a single static obstacle. Each row contains three values that define an obstacle {x,y, radius}

4. Config_OutPutData.csv: locations and forces for each agent at each time step. Each row contains the information for the different agent at a single time step.

5. Config_OutPutDataHeaders.csv: the headers for Config_OutPutData.csv file is saved to this separate file.

#### ShepherdingSimC

1. Sim.h  *<span style="color:green"> % This is the main simulation class  </span>*
        
2. CLI.h  *<span style="color:green"> % handles calling the main simulation class and recording metadata if no visualization is required. </span>*
    
3. Visualization.h *<span style="color:green"> % handles the visualization aspects of the simulation and records metadata as well. </span>*
    
4. SupportingCalc.h   *<span style="color:green"> % provides repetitive calculations functions required by the different classes. </span>*
    
5. Vector2.h   *<span style="color:green"> % provides a definition of a vector class to be used within the simulation. </span>*

#### ShepherdingLibC

1. Agents.h  *<span style="color:green"> % this class provides the definition of the different type of agents’ classes and their different methods. </span>*

2. Behaviors.h   *<span style="color:green">% a class that includes a definition for the different behavioural characteristics of an agent. </span>*

3. Environment.h  *<span style="color:green"> % the environment definition class. </span>*

4. Flock.h  *<span style="color:green"> % this class provides the definition of the flock class and its different methods. </span>*

5. Terrain.h  *<span style="color:green"> % this class provides the definition of the environment’s terrain class and its different methods. </span>*

6. Traits.h  *<span style="color:green"> % a class that describes the physical characteristics of an agent. </span>* 

7. Utilities.h  *<span style="color:green"> % a class that provides common functions required by the other classes. </span>*

## Technologies

The programming language for both the simulation and the shepherding library is in C++.

The tool used to build this project is visual studio.

The simulation subproject uses SDL2 library in C++ ([http://libsdl.org/](http://libsdl.org/)). 



## Launch

#### If you are a user:

You will need the *"executables"* and *"InputFiles"* directories only. The executable directory includes a compiled and ready to run file *“ShepherdingSimC_V1.exe”*, and updated DLL library files.

Before running the executable file, make sure that you check if the current configuration XML files, located in the *"InputFiles"* directory, match your requirements. The XML files have comments that explain all the parameters that will be used within the simulation. The metadata files will be outputted to the same folder.

You can also make your own copy of the *“Config.xml”* file, and edit it. The custom configuration file can be called by navigating to the executable folder, and use:

*ShepherdingSimC_V1.exe  <<YourCustomeConfigFileName.xml>>*

#### If you are a developer:
##### Prerequisites:

 1. Visual Studio installed

##### Steps:
1. Download the project, or clone it using the command

*git clone https://github.com/husseinaabbass/Shepherding.git*

2. Download and unpack the SDL2 development libraries (the .zip files with VC in the name) from:
   -   http://www.libsdl.org/download-2.0.php
   -   http://www.libsdl.org/projects/SDL_image
   -  http://www.libsdl.org/projects/SDL_ttf
   
  	Under the current versions, the most recent files links are:
	
	- https://www.libsdl.org/release/SDL2-devel-2.0.12-VC.zip
	- https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip
	- https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-VC.zip

3. Create a new directory "SDL2", and place it at the same path as Shepherding directory.

4. Copy the *"lib"* and *"include"* subdirectories from the three packages to the newly created directory "SDL2". 
  
        - The project is currently configured to access *"lib"* and *"include"* subdirectories located under "SDL2" directory if it is located at the same level as the "Shepherding" directory. 
  
        - If you would like to locate the SDL2 directory at a different location, you will need to update the IncludePath, LibraryPath, post build events command in the project configurations with the new paths. 
  
5. Open *"ClassLibraryProjects.sln"* using Visual Studio
6. In the *"Solution Explorer"* window, select *"ClassLibraryProjects"*.
7. In the *"Properties"* window, set *"Startup Project"* to *"ShepherdingSimC_V1"*
8. Build the solution. That will also build the sub-project.
9. Run the generated binary *"ShepherdingSimC_V1.exe"*

## Project status
The project now has a complete initial setup that covers many aspects of the shepherding problem. However, new modules will be added as the project evolves.
For now, the following aspects were completed:

#### Under Agents:
1. SheepAgent
2. SheepDogAgent

#### Under Behaviours:
1. Collision Avoidance Friends
2. Collision Avoidance Obstacles
3. Attraction to Local centre of mass
4. Previous heading effect 
5. Escaping Predator
6. Jittering
7. Driving
8. Collecting

