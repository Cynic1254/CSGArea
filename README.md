Unreal engine plugin for masking levels over other levels, allows for creation of Skyward Sword's Timeshift Stone's.

# Dependencies

-   GeometryScripting plugin (build-in)

# How to use

-   Creating a new CSG type:\
    To create a new CSG type simply create a new component inherited from `CSGBaseComponent` To give the component custom geometry and collision overwrite the `GetVisualMesh` and `GetCollisionMesh` functions, both functions work the same but one is responsible for the visual mesh while the other is in charge of the collision. Both functions have a `OutMesh` variable which is what you will need to write the mesh to.

-   Using the plugin:\
    To use the plugin simply place Actors in the world that have a CSG component. to properly use the base component the actor does have to have a component that collides with the configured CSG channel (This channel can be changed in the project settings under Plugins->CSGArea Settings). now any CSG component that collides with a CSG Area component will have proper csg applied to it.

-   Settings:
    -   Plugin Settings:\
         Plugin settings can be found at Project (Settings->Plugins->CSGArea Settings)
        -   Collision Channel: determines the main collision channel that will be used to check for CSG, only used for the construction of the CSGArea component and doesn't need to be used, as long as the area component collides with a component on a CSG actor it will work
        -   Default Area Material: Editor only, material used for rendering the CSG Area in the editor.
    -   CSGBase Component:\
        Base settings for CSG components
        -   Collision Options: found under "Collision->CSG" these are the options used for transforming the collision mesh from a mesh into collision.
        -   Do Reverse CSG: found under "Collision->CSG" if true meshes will only show when outside of the CSG Area
        -   Materials: found under "Visual" array of all the materials the mesh uses, this is where you should set your mesh materials
        -   CSGMaterial: found under "Visual" The material to use for the "cut" part of a mesh, the material will be inserted at the end of the Materials list during runtime.
    -   CSGStatic Mesh Component:\
        settings for the Static Mesh component
        -   Mesh: found under "Mesh" sets the csg mesh of the component. Be carefull, due to how the CSG works the `Allow CPU Access` option must be true on the mesh before cooking the asset.
