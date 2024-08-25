// Generated using https://github.com/a2x/cs2-dumper
// 2024-08-25 08:13:46.872145900 UTC

#![allow(non_upper_case_globals, non_camel_case_types, non_snake_case, unused)]

pub mod cs2_dumper {
    pub mod schemas {
        // Module: worldrenderer.dll
        // Class count: 23
        // Enum count: 1
        pub mod worldrenderer_dll {
            // Alignment: 4
            // Member count: 13
            #[repr(u32)]
            pub enum ObjectTypeFlags_t {
                OBJECT_TYPE_NONE = 0x0,
                OBJECT_TYPE_MODEL = 0x8,
                OBJECT_TYPE_BLOCK_LIGHT = 0x10,
                OBJECT_TYPE_NO_SHADOWS = 0x20,
                OBJECT_TYPE_WORLDSPACE_TEXURE_BLEND = 0x40,
                OBJECT_TYPE_DISABLED_IN_LOW_QUALITY = 0x80,
                OBJECT_TYPE_NO_SUN_SHADOWS = 0x100,
                OBJECT_TYPE_RENDER_WITH_DYNAMIC = 0x200,
                OBJECT_TYPE_RENDER_TO_CUBEMAPS = 0x400,
                OBJECT_TYPE_MODEL_HAS_LODS = 0x800,
                OBJECT_TYPE_OVERLAY = 0x2000,
                OBJECT_TYPE_PRECOMPUTED_VISMEMBERS = 0x4000,
                OBJECT_TYPE_STATIC_CUBE_MAP = 0x8000
            }
            // Parent: None
            // Field count: 14
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod SceneObject_t {
                pub const m_nObjectID: usize = 0x0; // 
                pub const m_vTransform: usize = 0x4; // 
                pub const m_flFadeStartDistance: usize = 0x34; // 
                pub const m_flFadeEndDistance: usize = 0x38; // 
                pub const m_vTintColor: usize = 0x3C; // 
                pub const m_skin: usize = 0x50; // 
                pub const m_nObjectTypeFlags: usize = 0x58; // 
                pub const m_vLightingOrigin: usize = 0x5C; // 
                pub const m_nOverlayRenderOrder: usize = 0x68; // 
                pub const m_nLODOverride: usize = 0x6A; // 
                pub const m_nCubeMapPrecomputedHandshake: usize = 0x6C; // 
                pub const m_nLightProbeVolumePrecomputedHandshake: usize = 0x70; // 
                pub const m_renderableModel: usize = 0x78; // 
                pub const m_renderable: usize = 0x80; // CStrongHandle<InfoForResourceTypeCRenderMesh>
            }
            // Parent: None
            // Field count: 3
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod AggregateLODSetup_t {
                pub const m_vLODOrigin: usize = 0x0; // 
                pub const m_fMaxObjectScale: usize = 0xC; // 
                pub const m_fSwitchDistances: usize = 0x10; // 
            }
            // Parent: BaseSceneObjectOverride_t
            // Field count: 4
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod ExtraVertexStreamOverride_t {
                pub const m_nSubSceneObject: usize = 0x4; // 
                pub const m_nDrawCallIndex: usize = 0x8; // 
                pub const m_nAdditionalMeshDrawPrimitiveFlags: usize = 0xC; // 
                pub const m_extraBufferBinding: usize = 0x10; // 
            }
            // Parent: None
            // Field count: 3
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod ClutterTile_t {
                pub const m_nFirstInstance: usize = 0x0; // 
                pub const m_nLastInstance: usize = 0x4; // 
                pub const m_BoundsWs: usize = 0x8; // 
            }
            // Parent: None
            // Field count: 8
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod AggregateSceneObject_t {
                pub const m_allFlags: usize = 0x0; // 
                pub const m_anyFlags: usize = 0x4; // 
                pub const m_nLayer: usize = 0x8; // 
                pub const m_aggregateMeshes: usize = 0x10; // 
                pub const m_lodSetups: usize = 0x28; // 
                pub const m_visClusterMembership: usize = 0x40; // 
                pub const m_fragmentTransforms: usize = 0x58; // 
                pub const m_renderableModel: usize = 0x70; // 
            }
            // Parent: None
            // Field count: 7
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod NodeData_t {
                pub const m_nParent: usize = 0x0; // 
                pub const m_vOrigin: usize = 0x4; // 
                pub const m_vMinBounds: usize = 0x10; // 
                pub const m_vMaxBounds: usize = 0x1C; // 
                pub const m_flMinimumDistance: usize = 0x28; // 
                pub const m_ChildNodeIndices: usize = 0x30; // 
                pub const m_worldNodePrefix: usize = 0x48; // 
            }
            // Parent: None
            // Field count: 0
            pub mod VMapResourceData_t {
            }
            // Parent: None
            // Field count: 8
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod ClutterSceneObject_t {
                pub const m_Bounds: usize = 0x0; // 
                pub const m_flags: usize = 0x18; // 
                pub const m_nLayer: usize = 0x1C; // 
                pub const m_instancePositions: usize = 0x20; // 
                pub const m_instanceScales: usize = 0x50; // 
                pub const m_instanceTintSrgb: usize = 0x68; // 
                pub const m_tiles: usize = 0x80; // 
                pub const m_renderableModel: usize = 0x98; // 
            }
            // Parent: None
            // Field count: 5
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod WorldBuilderParams_t {
                pub const m_flMinDrawVolumeSize: usize = 0x0; // 
                pub const m_bBuildBakedLighting: usize = 0x4; // 
                pub const m_bakedLightingInfo: usize = 0x8; // 
                pub const m_nCompileTimestamp: usize = 0x38; // 
                pub const m_nCompileFingerprint: usize = 0x40; // 
            }
            // Parent: None
            // Field count: 3
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod PermEntityLumpData_t {
                pub const m_name: usize = 0x8; // 
                pub const m_childLumps: usize = 0x10; // CUtlVector<CStrongHandleCopyable<InfoForResourceTypeCEntityLump>>
                pub const m_entityKeyValues: usize = 0x28; // 
            }
            // Parent: None
            // Field count: 13
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod WorldNode_t {
                pub const m_sceneObjects: usize = 0x0; // 
                pub const m_infoOverlays: usize = 0x18; // 
                pub const m_visClusterMembership: usize = 0x30; // 
                pub const m_aggregateSceneObjects: usize = 0x48; // 
                pub const m_clutterSceneObjects: usize = 0x60; // 
                pub const m_extraVertexStreamOverrides: usize = 0x78; // 
                pub const m_materialOverrides: usize = 0x90; // 
                pub const m_extraVertexStreams: usize = 0xA8; // 
                pub const m_layerNames: usize = 0xC0; // 
                pub const m_sceneObjectLayerIndices: usize = 0xD8; // 
                pub const m_overlayLayerIndices: usize = 0xF0; // 
                pub const m_grassFileName: usize = 0x108; // 
                pub const m_nodeLightingInfo: usize = 0x110; // 
            }
            // Parent: None
            // Field count: 1
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod BaseSceneObjectOverride_t {
                pub const m_nSceneObjectIndex: usize = 0x0; // 
            }
            // Parent: None
            // Field count: 7
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod EntityIOConnectionData_t {
                pub const m_outputName: usize = 0x0; // 
                pub const m_targetType: usize = 0x8; // 
                pub const m_targetName: usize = 0x10; // 
                pub const m_inputName: usize = 0x18; // 
                pub const m_overrideParam: usize = 0x20; // 
                pub const m_flDelay: usize = 0x28; // 
                pub const m_nTimesToFire: usize = 0x2C; // 
            }
            // Parent: None
            // Field count: 9
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod BakedLightingInfo_t {
                pub const m_nLightmapVersionNumber: usize = 0x0; // 
                pub const m_nLightmapGameVersionNumber: usize = 0x4; // 
                pub const m_vLightmapUvScale: usize = 0x8; // 
                pub const m_bHasLightmaps: usize = 0x10; // 
                pub const m_bBakedShadowsGamma20: usize = 0x11; // 
                pub const m_bCompressionEnabled: usize = 0x12; // 
                pub const m_nChartPackIterations: usize = 0x13; // 
                pub const m_nVradQuality: usize = 0x14; // 
                pub const m_lightMaps: usize = 0x18; // 
            }
            // Parent: None
            // Field count: 2
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod VoxelVisBlockOffset_t {
                pub const m_nOffset: usize = 0x0; // 
                pub const m_nElementCount: usize = 0x4; // 
            }
            // Parent: None
            // Field count: 0
            //
            // Metadata:
            // MResourceTypeForInfoType
            pub mod InfoForResourceTypeVMapResourceData_t {
            }
            // Parent: None
            // Field count: 4
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod WorldNodeOnDiskBufferData_t {
                pub const m_nElementCount: usize = 0x0; // 
                pub const m_nElementSizeInBytes: usize = 0x4; // 
                pub const m_inputLayoutFields: usize = 0x8; // 
                pub const m_pData: usize = 0x20; // 
            }
            // Parent: None
            // Field count: 9
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod AggregateMeshInfo_t {
                pub const m_nVisClusterMemberOffset: usize = 0x0; // 
                pub const m_nVisClusterMemberCount: usize = 0x4; // 
                pub const m_bHasTransform: usize = 0x5; // 
                pub const m_nDrawCallIndex: usize = 0x6; // 
                pub const m_nLODSetupIndex: usize = 0x8; // 
                pub const m_nLODGroupMask: usize = 0xA; // 
                pub const m_vTintColor: usize = 0xB; // 
                pub const m_objectFlags: usize = 0x10; // 
                pub const m_nLightProbeVolumePrecomputedHandshake: usize = 0x14; // 
            }
            // Parent: None
            // Field count: 4
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod World_t {
                pub const m_builderParams: usize = 0x0; // 
                pub const m_worldNodes: usize = 0x48; // 
                pub const m_worldLightingInfo: usize = 0x60; // 
                pub const m_entityLumps: usize = 0x90; // CUtlVector<CStrongHandleCopyable<InfoForResourceTypeCEntityLump>>
            }
            // Parent: None
            // Field count: 10
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod InfoOverlayData_t {
                pub const m_transform: usize = 0x0; // 
                pub const m_flWidth: usize = 0x30; // 
                pub const m_flHeight: usize = 0x34; // 
                pub const m_flDepth: usize = 0x38; // 
                pub const m_vUVStart: usize = 0x3C; // 
                pub const m_vUVEnd: usize = 0x44; // 
                pub const m_pMaterial: usize = 0x50; // 
                pub const m_nRenderOrder: usize = 0x58; // 
                pub const m_vTintColor: usize = 0x5C; // 
                pub const m_nSequenceOverride: usize = 0x6C; // 
            }
            // Parent: BaseSceneObjectOverride_t
            // Field count: 3
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod MaterialOverride_t {
                pub const m_nSubSceneObject: usize = 0x4; // 
                pub const m_nDrawCallIndex: usize = 0x8; // 
                pub const m_pMaterial: usize = 0x10; // 
            }
            // Parent: None
            // Field count: 2
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod EntityKeyValueData_t {
                pub const m_connections: usize = 0x8; // 
                pub const m_keyValuesData: usize = 0x20; // 
            }
            // Parent: None
            // Field count: 13
            //
            // Metadata:
            // MGetKV3ClassDefaults
            pub mod CVoxelVisibility {
                pub const m_nBaseClusterCount: usize = 0x40; // 
                pub const m_nPVSBytesPerCluster: usize = 0x44; // 
                pub const m_vMinBounds: usize = 0x48; // 
                pub const m_vMaxBounds: usize = 0x54; // 
                pub const m_flGridSize: usize = 0x60; // 
                pub const m_nSkyVisibilityCluster: usize = 0x64; // 
                pub const m_nSunVisibilityCluster: usize = 0x68; // 
                pub const m_NodeBlock: usize = 0x6C; // 
                pub const m_RegionBlock: usize = 0x74; // 
                pub const m_EnclosedClusterListBlock: usize = 0x7C; // 
                pub const m_EnclosedClustersBlock: usize = 0x84; // 
                pub const m_MasksBlock: usize = 0x8C; // 
                pub const m_nVisBlocks: usize = 0x94; // 
            }
        }
    }
}