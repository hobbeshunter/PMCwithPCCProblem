# PMCwithPCCProblem

This Unreal Engine Project was created to provide a minimal breaking example. It is to showcase a bug that makes dynamically added (using C++) ProceduralMeshComponents not working with PhysicsConstraintComponents. When you start the Default Level you should see 3 pairs of cubes. The left one is a C++ actor spawned through the GameMode. It uses StaticMeshComponents. There the Physics Constraint is working. The one in the middle is created through a Blueprint. It uses ProceduralMeshComponents. There the Physics Constraint is working too. On the right hand side you should see 2 cubes without a working Physics Constraint. Those two get spawned through the GameMode as well and use the ProceduralMeshComponent.

The Project was build using Unreal 4.22.1. The bug seems also to exist in 4.20.3.
