QT += core gui opengl

TARGET = warmup
TEMPLATE = app

win32 {
    DEFINES += GLEW_STATIC
    LIBS += -lopengl32
}

INCLUDEPATH += src libs glm libs/glew-1.10.0/include
DEPENDPATH += src libs glm libs/glew-1.10.0/include

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/view.cpp \
    src/util/ResourceLoader.cpp \
    src/util/obj.cpp \
    libs/glew-1.10.0/src/glew.c \
    src/engine/Screen.cpp \
    src/engine/Application.cpp \
    src/engine/camera/Camera.cpp \
    src/engine/shape/Shape.cpp \
    src/engine/graphics/Controller.cpp \
    src/engine/graphics/VertexData.cpp \
    src/engine/shape/Cylinder.cpp \
    src/engine/entity/Entity.cpp \
    src/warmup/WarmupApplication.cpp \
    src/warmup/GameScreen.cpp \
    src/warmup/entity/Player.cpp \
    src/warmup/entity/Floor.cpp \
    src/warmup/shape/TiledQuad.cpp \
    src/warmup/entity/WelcomeMessage.cpp \
    src/engine/camera/SimpleCamera.cpp \
    src/engine/shape/FullscreenQuad.cpp \
    src/engine/world/World.cpp \
    src/warmup/world/GameWorld.cpp \
    src/warmup/world/WelcomeWorld.cpp \
    src/warmup/WelcomeScreen.cpp \
    src/engine/entity/BackgroundEntity.cpp \
    src/engine/entity/ActiveEntity.cpp \
    src/engine/intersect/BoundingShape.cpp \
    src/engine/intersect/BoundingCylinder.cpp \
    src/warmup/entity/Bomb.cpp \
    src/warmup/entity/Zombie.cpp \
    src/warmup/entity/WarmupEntity.cpp \
    src/engine/voxel/chunk/Chunk.cpp \
    src/minecraft/MinecraftApplication.cpp \
    src/minecraft/manager/MinecraftManager.cpp \
    src/minecraft/noise/Noise.cpp \
    src/engine/voxel/entity/VoxelEntity.cpp \
    src/engine/voxel/shape/BlockFace.cpp \
    src/engine/voxel/terrain/Terrain.cpp \
    src/minecraft/terrain/ValueTerrain.cpp \
    src/minecraft/entity/MinecraftPlayer.cpp \
    src/minecraft/MinecraftScreen.cpp \
    src/engine/voxel/shape/VoxelCube.cpp \
    src/engine/intersect/AABoundingBox.cpp \
    src/engine/shape/Quad.cpp \
    src/minecraft/entity/MinecraftEnemy.cpp \
    src/minecraft/MinecraftWelcomeScreen.cpp \
    src/minecraft/manager/MinecraftWelcomeWorld.cpp \
    src/engine/voxel/manager/VoxelManager.cpp \
    src/engine/manager/Manager.cpp \
    src/engine/manager/ModuleManager.cpp \
    src/engine/manager/CollisionManager.cpp \
    src/engine/manager/CylinderCollisionManager.cpp \
    src/engine/voxel/manager/VoxelCollisionManager.cpp \
    src/engine/voxel/manager/ChunkManager.cpp

HEADERS += \
    libs/glew-1.10.0/include/GL/glew.h \
    src/mainwindow.h \
    src/view.h \
    src/util/CommonIncludes.h \
    src/util/ResourceLoader.h \
    src/util/CylinderData.h \
    src/util/obj.h \
    src/engine/camera/Camera.h \
    src/engine/Application.h \
    src/engine/Screen.h \
    src/engine/shape/Shape.h \
    src/engine/graphics/Controller.h \
    src/engine/graphics/VertexData.h \
    src/engine/shape/Cylinder.h \
    src/engine/entity/Entity.h \
    src/warmup/WarmupApplication.h \
    src/warmup/GameScreen.h \
    src/warmup/entity/Player.h \
    src/warmup/entity/Floor.h \
    src/warmup/shape/TiledQuad.h \
    src/util/QuadData.h \
    src/warmup/entity/WelcomeMessage.h \
    src/engine/camera/SimpleCamera.h \
    src/engine/shape/FullscreenQuad.h \
    src/engine/world/World.h \
    src/warmup/world/GameWorld.h \
    src/warmup/world/WelcomeWorld.h \
    src/warmup/WelcomeScreen.h \
    src/engine/entity/BackgroundEntity.h \
    src/engine/entity/ActiveEntity.h \
    src/engine/intersect/BoundingShape.h \
    src/engine/intersect/BoundingCylinder.h \
    src/warmup/entity/Bomb.h \
    src/warmup/entity/Zombie.h \
    src/warmup/entity/WarmupEntity.h \
    src/engine/voxel/chunk/Chunk.h \
    src/engine/voxel/block/Block.h \
    src/minecraft/MinecraftApplication.h \
    src/minecraft/manager/MinecraftManager.h \
    src/minecraft/noise/Noise.h \
    src/engine/voxel/entity/VoxelEntity.h \
    src/engine/voxel/shape/BlockFace.h \
    src/engine/voxel/terrain/Terrain.h \
    src/minecraft/terrain/ValueTerrain.h \
    src/minecraft/entity/MinecraftPlayer.h \
    src/minecraft/MinecraftScreen.h \
    src/engine/voxel/shape/VoxelCube.h \
    src/engine/voxel/shape/CubeData.h \
    src/engine/world/WorldConstants.h \
    src/engine/intersect/AABoundingBox.h \
    src/engine/shape/Quad.h \
    src/minecraft/entity/MinecraftEnemy.h \
    src/minecraft/MinecraftWelcomeScreen.h \
    src/minecraft/manager/MinecraftWelcomeWorld.h \
    src/engine/voxel/manager/VoxelManager.h \
    src/engine/manager/Manager.h \
    src/engine/manager/ModuleManager.h \
    src/engine/manager/CollisionManager.h \
    src/engine/manager/CylinderCollisionManager.h \
    src/engine/voxel/manager/VoxelCollisionManager.h \
    src/engine/voxel/manager/ChunkManager.h


FORMS += src/mainwindow.ui

RESOURCES += \
    res/shaders/shaders.qrc \
    res/images/images.qrc \
    res/obj/obj.qrc \

OTHER_FILES += \
    res/images/grass.png \
    res/images/level_easy.png \
    res/images/level_easy_channels.png \
    res/images/level_hard.png \
    res/images/level_hard_channels.png \
    res/images/level_island.png \
    res/images/level_island_channels.png

DISTFILES += \
    res/shaders/shader.vert \
    res/shaders/shader.frag \
    res/other/TODO
