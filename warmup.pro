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
    libs/glew-1.10.0/src/glew.c \
    src/engine/Screen.cpp \
    src/engine/Application.cpp \
    src/engine/camera/Camera.cpp \
    src/util/Settings.cpp \
    src/engine/shape/Shape.cpp \
    src/engine/light/Light.cpp \
    src/engine/shape/CompositeShape.cpp \
    src/engine/graphics/Controller.cpp \
    src/engine/graphics/VertexData.cpp \
    src/engine/shape/Cylinder.cpp \
    src/engine/entity/Entity.cpp \
    src/engine/shape/TexturedQuad.cpp \
    src/warmup/WarmupApplication.cpp \
    src/warmup/GameScreen.cpp \
    src/warmup/entity/Player.cpp \
    src/warmup/entity/Floor.cpp \
    src/warmup/shape/TiledQuad.cpp \
    src/warmup/entity/WelcomeMessage.cpp \
    src/engine/camera/SimpleCamera.cpp \
    src/engine/camera/PerspectiveCamera.cpp \
    src/engine/shape/FullscreenQuad.cpp \
    src/engine/world/World.cpp \
    src/warmup/world/GameWorld.cpp \
    src/warmup/world/WelcomeWorld.cpp \
    src/warmup/WelcomeScreen.cpp \
    src/engine/intersect/Intersector.cpp \
    src/engine/entity/BackgroundEntity.cpp \
    src/engine/entity/ActiveEntity.cpp \
    src/engine/intersect/BoundingShape.cpp \
    src/engine/intersect/BoundingCylinder.cpp \
    src/engine/intersect/BoundingPlane.cpp

HEADERS += \
    libs/glew-1.10.0/include/GL/glew.h \
    src/mainwindow.h \
    src/view.h \
    src/util/CommonIncludes.h \
    src/util/ResourceLoader.h \
    src/util/CylinderData.h \
    src/util/Settings.h \
    src/engine/camera/Camera.h \
    src/engine/Application.h \
    src/engine/Screen.h \
    src/engine/shape/Shape.h \
    src/engine/light/Light.h \
    src/engine/shape/CompositeShape.h \
    src/engine/graphics/Controller.h \
    src/engine/graphics/VertexData.h \
    src/engine/shape/Cylinder.h \
    src/engine/entity/Entity.h \
    src/engine/shape/TexturedQuad.h \
    src/warmup/WarmupApplication.h \
    src/warmup/GameScreen.h \
    src/warmup/entity/Player.h \
    src/warmup/entity/Floor.h \
    src/warmup/shape/TiledQuad.h \
    src/util/QuadData.h \
    src/warmup/entity/WelcomeMessage.h \
    src/engine/camera/SimpleCamera.h \
    src/engine/camera/PerspectiveCamera.h \
    src/engine/shape/FullscreenQuad.h \
    src/engine/world/World.h \
    src/warmup/world/GameWorld.h \
    src/warmup/world/WelcomeWorld.h \
    src/warmup/WelcomeScreen.h \
    src/engine/intersect/Intersector.h \
    src/engine/entity/BackgroundEntity.h \
    src/engine/entity/ActiveEntity.h \
    src/engine/intersect/BoundingShape.h \
    src/engine/intersect/BoundingCylinder.h \
    src/engine/intersect/BoundingPlane.h


FORMS += src/mainwindow.ui

RESOURCES += \
    res/shaders/shaders.qrc \
    res/images/images.qrc

OTHER_FILES += \
    res/images/grass.png \

DISTFILES += \
    res/shaders/shader.vert \
    res/shaders/shader.frag \
    res/other/TODO
